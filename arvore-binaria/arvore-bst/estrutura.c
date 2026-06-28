#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>

typedef struct bst_node_t{
    int data;
    struct bst_node_t *left;
    struct bst_node_t *right;
} bst_node_t;

typedef struct bst_t{
    bst_node_t *root;
    size_t size;
} bst_t;

/* mallocx: malloc que aborta o programa em caso de falha de alocacao */
static void *mallocx(size_t size) {
    void *ptr = malloc(size);
    if (ptr == NULL) {
        fprintf(stderr, "erro: falha de alocacao de memoria\n");
        exit(EXIT_FAILURE);
    }
    return ptr;
}

/* ===================== Inicializacao ===================== */

void bst_initialize(bst_t **t) {
    (*t) = mallocx(sizeof(bst_t));
    (*t)->size = 0;
    (*t)->root = NULL;
}

/* ===================== Funcoes auxiliares ===================== */

static bst_node_t *bst_new_node(int data) {
    bst_node_t *ptr = mallocx(sizeof(bst_node_t));
    ptr->left = NULL;
    ptr->right = NULL;
    ptr->data = data;
    return ptr;
}

static void bst_delete_node(bst_node_t *node) {
    free(node);
}

size_t bst_size(bst_t *t) {
    return t->size;
}

/* Acha o no mais a direita a partir de v (o maior valor daquela subarvore).
 * Usado na remocao para achar o predecessor de um no com dois filhos. */
static bst_node_t *bst_find_rightmost(bst_node_t *v) {
    if (v == NULL || v->right == NULL) {
        return v;
    } else {
        return bst_find_rightmost(v->right);
    }
}

/* ===================== Busca ===================== */

static bool bst_find_helper(bst_node_t *x, int data) {
    if (x == NULL)
        return false;
    if (data == x->data)
        return true;
    if (data < x->data)
        return bst_find_helper(x->left, data);
    return bst_find_helper(x->right, data);
}

bool bst_find(bst_t *t, int data) {
    return bst_find_helper(t->root, data);
}

/* ===================== Insercao ===================== */

/* Premissa: a chave 'data' ainda nao existe na arvore (sem duplicatas). */
static bst_node_t *bst_insert_helper(bst_node_t *x, int data) {
    if (x == NULL)
        return bst_new_node(data);

    assert(x->data != data);

    if (data < x->data) {
        x->left = bst_insert_helper(x->left, data);
    } else {
        x->right = bst_insert_helper(x->right, data);
    }
    /* devolve x para o nivel anterior reconectar a subarvore (ela nao mudou de raiz aqui) */
    return x;
}

void bst_insert(bst_t *t, int data) {
    t->root = bst_insert_helper(t->root, data);
    t->size++;
}

/* ===================== Remocao ===================== */

/* Premissa: a chave 'data' existe na arvore.
 * Cada chamada devolve a raiz (possivelmente nova) da subarvore que comecou
 * em x, para que o chamador possa reconectar (ex: x->left = bst_remove_helper(...)). */
static bst_node_t *bst_remove_helper(bst_node_t *x, int data) {
    assert(x != NULL);

    if (data < x->data) {
        x->left = bst_remove_helper(x->left, data);
    } else if (data > x->data) {
        x->right = bst_remove_helper(x->right, data);
    } else {
        /* achou o no a ser removido (data == x->data) */
        if (x->left == NULL) {
            /* sem filho esquerdo: o filho direito (ou NULL) toma o lugar de x */
            bst_node_t *y = x->right;
            bst_delete_node(x);
            x = y;
        } else if (x->right == NULL) {
            /* sem filho direito: o filho esquerdo toma o lugar de x */
            bst_node_t *y = x->left;
            bst_delete_node(x);
            x = y;
        } else {
            /* dois filhos: caso mais dificil.
             * Transforma-se em um caso facil trocando x pelo seu predecessor
             * (o maior valor da subarvore esquerda) e removendo o predecessor
             * recursivamente -- ele, por ser o mais a direita, nunca tem filho
             * direito, entao cai em um dos casos simples acima. */
            bst_node_t *previous_x = bst_find_rightmost(x->left);
            int aux = x->data;
            x->data = previous_x->data;
            previous_x->data = aux;
            x->left = bst_remove_helper(x->left, data);
        }
    }

    /* devolve o no que deve ocupar essa posicao agora (o mesmo x, ou seu substituto) */
    return x;
}

void bst_remove(bst_t *t, int data) {
    t->root = bst_remove_helper(t->root, data);
    t->size--;
}

/* ===================== Limpeza ===================== */

static void bst_delete_helper(bst_node_t *x) {
    if (x != NULL) {
        bst_delete_helper(x->left);
        bst_delete_helper(x->right);
        bst_delete_node(x);
    }
}

void bst_delete(bst_t **t) {
    bst_delete_helper((*t)->root);
    free(*t);
    (*t) = NULL;
}