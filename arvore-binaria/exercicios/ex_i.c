#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

typedef struct tree_node_t{
    int data;
    struct tree_node_t *left;
    struct tree_node_t *right;
} tree_node_t;

typedef struct tree_t{
    tree_node_t *root;
} tree_t;

typedef struct queue_t {
    size_t front;
    size_t back;
    size_t size;
    size_t capacity;
    tree_node_t **queue;
} queue_t;

void queue_initialize(queue_t **q) {
    (*q) = malloc(sizeof(queue_t));
    (*q)->front = 0;
    (*q)->back = 3;
    (*q)->size = 0;
    (*q)->capacity = 4;
    (*q)->queue = malloc(sizeof(tree_node_t*) * 4);
}

void queue_delete(queue_t **q) {
    free((*q)->queue);
    free(*q);
    *q = NULL;
}

static void queue_expand(queue_t *q) {
    size_t old_capacity = q->capacity;
    q->capacity *= 2;
    q->queue = realloc(q->queue, sizeof(tree_node_t) * q->capacity);
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
    q->queue = realloc(q->queue, q->capacity * sizeof(tree_node_t));
}

void queue_push(queue_t *q, tree_node_t *data) {
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

tree_node_t* queue_front(queue_t *q) {
    assert(q->front < q->capacity);
    return q->queue[q->front];
}

size_t queue_size(queue_t *q) {
    return q->size;
}

bool queue_empty(queue_t *q) {
    return queue_size(q) == 0;
}

tree_node_t *new_node(){
    tree_node_t *n = malloc(sizeof(tree_node_t));
    n->data = -1; // Valor padrão
    n->left = NULL;
    n->right = NULL;
    return n;
}

tree_node_t *parse(char *topology, int *i){ // (((..)((..).))((.(..)).))
    // Estamos no caractere '(' — abre o nó
    (*i)++; // consome o '('

    tree_node_t *node = new_node();

    // filho esquerdo: ou é '.', ou é outra árvore inteira '(...)'
    if(topology[*i] == '.'){
        (*i)++;          // consome o '.'
        node->left = NULL;
    } else { // é '('
        node->left = parse(topology, i);
    }

    // filho direito: mesma lógica
    if(topology[*i] == '.'){
        (*i)++;
        node->right = NULL;
    } else {
        node->right = parse(topology, i);
    }

    // fecha o nó
    (*i)++; // consome o ')'

    return node;
}

void fill_values(int *values, tree_node_t *root, int *i){
    if(root == NULL) return;
    root->data = values[(*i)++];
    fill_values(values, root->left, i);
    fill_values(values, root->right, i);
}

void show_tree_bfs(tree_node_t *root){
    queue_t *queue;
    queue_initialize(&queue);

    if(root != NULL){
        queue_push(queue, root);
    }

    while(!queue_empty(queue)){
        tree_node_t *n = queue_front(queue);
        printf("%d ", n->data);

        if(n->left != NULL){
            queue_push(queue, n->left);
        }
        if(n->right != NULL){
            queue_push(queue, n->right);
        }
        queue_pop(queue);
    }
    queue_delete(&queue);
}

int main(){
    int n;
    scanf("%d", &n);

    int values[n];

    char topology[3*n+1];
    scanf("%s", topology);
    
    for(int i = 0; i < n; i++){
        scanf("%d", &values[i]);
    }

    int k = 0;
    tree_node_t *root = parse(topology, &k);

    int l = 0;
    fill_values(values, root, &l);
    show_tree_bfs(root);

    return 0;
}