#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>

typedef struct tree_node_t{
    int data;
    struct tree_node_t *left;
    struct tree_node_t *right;
}tree_node_t;

typedef struct tree_t{
    tree_node_t *root;
}tree_t;

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

bool is_full_node(tree_node_t *root){
    queue_t* queue;
    queue_initialize(&queue);

    if(root!=NULL){
        queue_push(queue, root);
    }
    while(!queue_empty(queue)){
        tree_node_t *v = queue_front(queue);
        if((v->left == NULL) != (v->right == NULL)){
            queue_delete(&queue);
            return false;
        }

        if(v->left != NULL){
            queue_push(queue, v->left);
        }
        if(v->right != NULL){
            queue_push(queue, v->right);
        }
        queue_pop(queue);
    }
    queue_delete(&queue);
    return true;
}

bool is_full(tree_t *t){
    return is_full_node(t->root);
}

// PODEMOS UTILIZAR UMA RECURSAO MAIS SIMPLES
bool is_full_node(tree_node_t *n){
    if((n->left == NULL) != (n->right == NULL)) return false;
    if(n->left == NULL && n->right == NULL) return true;

    return is_full_node(n->left) && is_full_node(n->right);
}