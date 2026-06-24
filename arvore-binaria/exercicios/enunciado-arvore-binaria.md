# Exercício: Implementação de Árvore Binária Genérica

**Disciplina:** Estrutura de Dados e Algoritmos
**Tema:** Árvores Binárias — Terminologia, Estrutura e Percurso

## Contexto

Você já estudou a definição estrutural de uma árvore binária em C:

```c
typedef struct tree_node{
    void* data;               /* Dado da árvore */
    struct tree_node* left;   /* Ponteiro para subárvore da esquerda */
    struct tree_node* right;  /* Ponteiro para subárvore da direita */
} tree_node;

typedef struct arvore{
    tree_node* root;          /* Raiz da Árvore */
} arvore;
```

Note que `data` é `void*` — um ponteiro genérico. Isso significa que a árvore não sabe, e não precisa saber, que tipo de dado ela guarda. Quem decide isso é o código que **usa** a árvore, através de alocação manual de memória e casts explícitos.

Nesse exercício, você vai implementar duas funções: uma para criar um nó individual contendo um inteiro, e outra para montar, à mão, uma árvore de exemplo inteira ligando vários nós entre si.

---

## Parte 1 — `new_node`

### Objetivo

Implementar uma função que recebe um valor inteiro e devolve um **novo nó de árvore**, já alocado em memória e pronto para uso (sem filhos ainda).

### Assinatura

```c
tree_node* new_node(int valor);
```

### Requisitos

1. A função deve alocar memória **dinamicamente** para um `tree_node` (use `malloc`).
2. Como `data` é `void*`, ela não pode guardar um `int` diretamente — você precisa alocar memória **separadamente** para guardar o valor inteiro, e fazer `data` apontar para esse espaço.
3. Os campos `left` e `right` do nó novo devem começar como `NULL` (nó recém-criado não tem filhos).
4. A função deve devolver o ponteiro para o nó criado.

### Perguntas para te guiar (responda antes de codar)

- Quantas chamadas a `malloc` você vai precisar dentro dessa função? Por quê?
- Depois de alocar espaço para o inteiro, como você escreve o `valor` recebido dentro desse espaço? (Lembre-se do operador de desreferência `*`.)
- Por que `node->data = ponteiro_para_o_inteiro;` não precisa de cast, mesmo `data` sendo `void*` e o outro ponteiro sendo `int*`?

### Teste rápido

Depois de implementar, teste assim:

```c
tree_node* n = new_node(10);
printf("%d\n", *(int*)n->data);  // deve imprimir 10
printf("%p\n", n->left);          // deve imprimir (nil) ou 0x0
```

---

## Parte 2 — `create_example_tree`

### Objetivo

Usando `new_node`, montar manualmente (nó por nó, ligação por ligação) a seguinte árvore, que é a mesma usada nos exemplos de percurso do material (slides de BFS e DFS):

```
                  2
                /   \
               7      5
             /   \      \
            2     6      9
                /   \    /
               5     11  4
```

### Assinatura

```c
arvore* create_example_tree(void);
```

### Requisitos

1. Aloque a struct `arvore` com `malloc`.
2. Crie cada um dos 9 nós chamando `new_node` com o valor correspondente. **Atenção:** a árvore tem dois nós com valor `2` e dois nós com valor `5` — eles são nós **diferentes** (endereços de memória diferentes), mesmo guardando o mesmo número. Dê nomes de variável diferentes para não confundi-los (ex: `n2_filho`, `n2_raiz`).
3. Ligue os nós entre si através dos campos `left`/`right`, seguindo exatamente o desenho acima. Preste atenção especial a:
   - O nó `5` à direita da raiz só tem filho à **direita** (o `9`).
   - O nó `9` só tem filho à **esquerda** (o `4`).
4. Atribua o nó raiz (valor `2`, no topo) ao campo `root` da struct `arvore`.
5. Devolva o ponteiro para a `arvore` montada.

### Como validar se você acertou

Depois de implementar `create_example_tree`, rode os 4 percursos que vocês já estudaram (BFS, pré-ordem, em-ordem, pós-ordem) sobre a árvore criada, e confira se os resultados batem com os valores abaixo:

| Percurso | Resultado esperado |
|---|---|
| BFS (largura) | `2, 7, 5, 2, 6, 9, 5, 11, 4` |
| DFS pré-ordem | `2, 7, 2, 6, 5, 11, 5, 9, 4` |
| DFS em-ordem | `2, 7, 5, 6, 11, 2, 5, 4, 9` |
| DFS pós-ordem | `2, 5, 11, 6, 7, 4, 9, 5, 2` |

Se algum desses não bater, revise as ligações `left`/`right` dos nós — é provável que algum filho esteja no lado errado (esquerda no lugar de direita, ou vice-versa).

### Dica de organização

Não existe uma única forma "certa" de escrever essa função, mas uma abordagem comum é:

1. Primeiro, declare e crie todos os 9 nós com `new_node` (um de cada vez).
2. Depois, em um bloco separado, escreva todas as atribuições de `left`/`right` para ligar os nós entre si.
3. Por fim, monte a struct `arvore` e devolva.

---

## Entregável

Um arquivo `.c` contendo:
- A struct `tree_node` e `arvore` (já fornecidas).
- Sua implementação de `new_node`.
- Sua implementação de `create_example_tree`.
- Uma função `main` que chama `create_example_tree`, roda os 4 percursos sobre ela, e imprime os resultados para você mesmo conferir contra a tabela acima.

Você pode reaproveitar as implementações de `bfs`, `dfs_pre_ordem`, `dfs_em_ordem`, `dfs_pos_ordem` e `process` já estudadas — o foco deste exercício é treinar a criação e montagem manual da árvore, não os percursos em si.
