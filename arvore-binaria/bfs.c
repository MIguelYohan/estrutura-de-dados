#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>

// Para a busca em amplitude/largura é necessário implementar uma pilha
// EXPLICAÇÃO: A busca em amplitude precisa que os nós da arvore sejam processados sequencialmente de nivel em nivel
// portanto é necessário uma fila para que nenhum nó "fique para trás"

typedef struct queue_t {
    size_t front;
    size_t back;
    size_t size;
    size_t capacity;
    int *queue;
} queue_t;

void queue_initialize(queue_t **q) {
    (*q) = mallocx(sizeof(queue_t));
    (*q)->front = 0;
    (*q)->back = 3;
    (*q)->size = 0;
    (*q)->capacity = 4;
    (*q)->queue = mallocx(sizeof(int) * 4);
}

void queue_delete(queue_t **q) {
    free((*q)->queue);
    free(*q);
    *q = NULL;
}

static void queue_expand(queue_t *q) {
    size_t old_capacity = q->capacity;
    q->capacity *= 2;
    q->queue = reallocx(q->queue, sizeof(int) * q->capacity);
    if (q->front > q->back) {
        for (size_t i = q->front; i < old_capacity; i++) {
            q->queue[i + old_capacity] = q->queue[i];
        }
        q->front = q->front + old_capacity;
    }
}

static void queue_shrink(queue_t *q) {
    size_t new_capacity = q->capacity / 2;
    if (q->front <= q->back) {
        for (size_t i = q->front, j = 0; i <= q->back; i++, j++) {
            q->queue[j] = q->queue[i];
        }
    } else {
        size_t front_len = q->capacity - q->front;
        for (int i = q->back; i >= 0; i--) {
            q->queue[i + front_len] = q->queue[i];
        }
        for (size_t i = q->front, j = 0; i < q->capacity; i++, j++) {
            q->queue[j] = q->queue[i];
        }
    }
    q->front = 0;
    q->back = q->size - 1;
    q->capacity = new_capacity;
    q->queue = reallocx(q->queue, q->capacity * sizeof(int));
}

void queue_push(queue_t *q, int data) {
    if (q->size == q->capacity) {
        queue_expand(q);
    }
    q->back++;
    if (q->back == q->capacity)
        q->back = 0;
    q->queue[q->back] = data;
    q->size++;
}

void queue_pop(queue_t *q) {
    assert(q->size > 0);
    if (q->size == q->capacity / 4 && q->capacity > 4) {
        queue_shrink(q);
    }
    q->front++;
    q->size--;
    if (q->front == q->capacity) {
        q->front = 0;
    }
}

int queue_front(queue_t *q) {
    assert(q->front < q->capacity);
    return q->queue[q->front];
}

size_t queue_size(queue_t *q) {
    return q->size;
}

bool queue_empty(queue_t *q) {
    return queue_size(q) == 0;
}

typedef struct tree_node{
    void *data;
    struct tree_node *left;
    struct tree_node *right;
}tree_node;

typedef struct tree{
    tree_node *root;
}tree;

// Busca em largura (BFS)
void bfs(tree_node *root){
    // Criando e inicializando a fila
    queue_t* queue;
    queue_initialize(&queue);

    // Começa colocando a raiz (primeiro nó) na fila, se ele existir. 
    if(root!=NULL){
        queue_push(queue, root);
    }
    while(!queue_empty(queue)){
        // Guarda o nó da frente da fila para processa-lo
        tree_node *v = queue_front(queue);
        process(v);
        // Ordem de processo de nós: esquerda -> direita
        // Pois na fila o da esquerda vai ser processado primeiro

        // Coloca os filhos na fila
        if(v->left != NULL){
            queue_push(queue, v->left);
        }
        if(v->right != NULL){
            queue_push(queue, v->right);
        }
        // Tira o pai da fila pois já o processou
        queue_pop(queue);
    }
    queue_delete(&queue);
}