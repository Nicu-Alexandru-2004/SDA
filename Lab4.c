#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct productNode {
  int key;
  char *name;
  float price;
  int quantity;
  struct productNode *left;
  struct productNode *right;
} productNode;

enum MenuOption {
  CITIRE_PRODUCTE = 1,
  CAUTARE_PRODUCTE,
  AFISARE_INORDINE,
  PARCURGERE_PREORDINE,
  PARCURGERE_POSTORDINE,
  PARCURGERE_DFS,
  PARCURGERE_BFS,
  BALANSARE_ARBORA,
  IESIRE
};
/*
Functie pentru calcularea randrrilor din file
@parm fisier - fisierul din care se citesc randurile
@return lines - numarul de randuri din fisier
*/
int count_lines(FILE *f) {
  char ch;
  int lines = 0;

  while (!feof(f)) {
    ch = fgetc(f);
    if (ch == '\n') {
      lines++;
    }
  }
  rewind(f);
  return lines;
}
/*
Functie ajutatoare pentru introducerea datelor din fisier intr-un nod al
arborelui
@param id - id-ul produsului
@param name - numele produsului
@param price - pretul produsului
@param quantity - cantitatea produsului
@return newNode - nodul cu datele introduse
*/
productNode *create_product_node(int key, const char *name, float price,
                                 int quantity) {
  productNode *newNode = (productNode *)malloc(sizeof(productNode));
  newNode->key = key;
  newNode->name = strdup(name);
  newNode->price = price;
  newNode->quantity = quantity;
  newNode->left = NULL;
  newNode->right = NULL;
  return newNode;
}
/*
Functie pentru a introduce datele arborelui cu folosirea fuctiei
create_product_node
@param id - id-ul produsului
@param name - numele produsului
@param price - pretul produsului
@param quantity - cantitatea produsului
@return root - arborele
*/
productNode *insert_product_node(productNode *root, int key, const char *name,
                                 float price, int quantity) {
  if (root == NULL) {
    return create_product_node(key, name, price, quantity);
  } else {
    if (key <= root->key) {
      root->left = insert_product_node(root->left, key, name, price, quantity);
    } else {
      root->right =
          insert_product_node(root->right, key, name, price, quantity);
    }
    return root;
  }
}
/*
Procedura pentru citirea datelor din fisier
@param file - fisierul din care se citesc datele
@param root - arborele
@return void
*/
void read_product_tree(productNode **root, FILE *file) {
  if (file == NULL) {
    printf("Eroare la deschiderea fișierului!");
  }

  int key, quantity;
  char name[100];
  float price;

  int numLines = count_lines(file);

  for (int i = 0; i <= numLines; ++i) {
    fscanf(file, "%d %s %f %d", &key, name, &price, &quantity);
    *root = insert_product_node(*root, key, name, price, quantity);
  }

  fclose(file);
  printf("Produsele au fost citite");
}
/*
Functie pentru cautarea unui nodului folosind o cheie
@param root - arborele
@param key - cheia cautata
@return root
*/
struct productNode *search(struct productNode *root, int key) {
  if (root == NULL || root->key == key) {
    if (root != NULL) {
      printf("Nodul a fost găsit\n");
      printf("-------------------\n");
      printf("Key: %d\n", root->key);
      printf("Nume: %s\n", root->name);
      printf("Pret: %.2f\n", root->price);
      printf("Cantitate: %d\n", root->quantity);
    } else {
      printf("Nodul nu a fost găsit.\n");
    }
    return root;
  }
  if (root->key < key)
    return search(root->right, key);
  return search(root->left, key);
}
/*
Functie pentru afisrea a arobrelui in inordine
@param root - arborele
@return NULL
*/
void inorder(productNode *root) {
  if (root != NULL) {
    inorder(root->left);
    printf("Key: %d, Nume: %s, Pret: %.2f, Cantitate: %d\n", root->key,
           root->name, root->price, root->quantity);
    inorder(root->right);
  }
}
/*
Functie pentru afisrea a arobrelui in preordine
@param root - arborele
@return NULL
*/
void preorder(productNode *root) {
  if (root != NULL) {
    printf("Key: %d, Nume: %s, Pret: %.2f, Cantitate: %d\n", root->key,
           root->name, root->price, root->quantity);
    preorder(root->left);
    preorder(root->right);
  }
}
/*
Functie pentru afisrea a arobrelui in postordine
@param root - arborele
@return NULL
*/
void postorder(productNode *root) {
  if (root != NULL) {
    postorder(root->left);
    postorder(root->right);
    printf("Key: %d, Nume: %s, Pret: %.2f, Cantitate: %d\n", root->key,
           root->name, root->price, root->quantity);
  }
}
/*
Functie pentru pargurge a roborelui in adancime
@param root - arborele
@return NULL
*/
void DFS(productNode *root) {
  if (root != NULL) {
    printf("Key: %d, Nume: %s, Pret: %.2f, Cantitate: %d\n", root->key,
           root->name, root->price, root->quantity);
    DFS(root->left);
    DFS(root->right);
  }
}

typedef struct QueueNode {
  productNode *product;
  struct QueueNode *next;
} QueueNode;

typedef struct Queue {
  QueueNode *front;
  QueueNode *rear;
} Queue;
/*
Functie pentru a aduga valoari in coada
@param q - coada
@return NULL
*/
void enqueue(Queue *q, productNode *product) {
  QueueNode *newNode = (QueueNode *)malloc(sizeof(QueueNode));
  newNode->product = product;
  newNode->next = NULL;
  if (q->rear == NULL) {
    q->front = q->rear = newNode;
    return;
  }
  q->rear->next = newNode;
  q->rear = newNode;
}
/*
Functie pentru a socate o valoarea din coada
@param q - coada
@return NULL
*/
productNode *dequeue(Queue *q) {
  if (q->front == NULL) {
    return NULL;
  }
  QueueNode *temp = q->front;
  productNode *product = temp->product;
  q->front = q->front->next;
  if (q->front == NULL) {
    q->rear = NULL;
  }
  free(temp);
  return product;
}
/*
Verificarea daca coada este goala
@param q - coada
@return true daca coada este goala, false in caz contrar
*/
bool isEmpty(Queue *q) { return q->front == NULL; }
/*
Functie pentru pargurge a roborelui in largimea
@param root - arborele
@return NULL
*/
void BFS(productNode *root) {
  if (root == NULL) {
    return;
  }

  Queue q = {NULL, NULL};
  enqueue(&q, root);

  while (!isEmpty(&q)) {
    productNode *current = dequeue(&q);
    printf("Key: %d, Nume: %s, Pret: %.2f, Cantitate: %d\n", current->key,
           current->name, current->price, current->quantity);

    if (current->left != NULL) {
      enqueue(&q, current->left);
    }
    if (current->right != NULL) {
      enqueue(&q, current->right);
    }
  }
}
/*
Functie pentru stocarea datelor intr-un vector
@parma root - arborele
@param nodes - vectorul in care se stoca datele
@parma index - pozitia pe care se stocheaza datele
@param capacity - marimea vectorului
@return NULL
*/
void storeNodes(productNode *root, productNode **nodes, int *index,
                int *capacity) {
  if (root == NULL) {
    return;
  }

  if (*index >= *capacity) {
    *capacity *= 2;
    nodes = realloc(nodes, (*capacity) * sizeof(productNode *));
    if (nodes == NULL) {
      printf("Eroare la realocarea memoriei!\n");
      exit(1);
    }
  }
  nodes[*index] = root;
  (*index)++;

  storeNodes(root->left, nodes, index, capacity);
  storeNodes(root->right, nodes, index, capacity);
}
/*
Functia de sortare vectorului de noduri
@param nodes - vectorul de noduri
@param n - marimea vectorului
@return NULL
*/
void insertionSort(productNode **nodes, int n) {
  for (int i = 1; i < n; i++) {
    productNode *key = nodes[i];
    int j = i - 1;

    while (j >= 0 && nodes[j]->key > key->key) {
      nodes[j + 1] = nodes[j];
      j = j - 1;
    }
    nodes[j + 1] = key;
  }
}
/*
Funcția pentru construirea arborelului balansat din vector
@parma inorder - vectorul sortat
@param start - pozitia de inceput al vectorului
@param end - pozitia finala al vectorului
@return root - arborele balansat
*/
productNode *buildBalancedTree(productNode **nodes, int start, int end) {
  if (start > end) {
    return NULL;
  }

  int mid = (start + end) / 2;
  productNode *node = nodes[mid];

  node->left = buildBalancedTree(nodes, start, mid - 1);
  node->right = buildBalancedTree(nodes, mid + 1, end);

  return node;
}
/*
Functie pentru balansarea arborelui
@param root - arborele
@return balancedRoot - arborele balansat
*/
productNode *balanceTree(productNode *root) {
  if (root == NULL) {
    return NULL;
  }

  int capacity = 10;
  int index = 0;
  productNode **nodes =
      (productNode **)malloc(capacity * sizeof(productNode *));
  if (nodes == NULL) {
    printf("Eroare la alocarea memoriei!\n");
    exit(1);
  }

  storeNodes(root, nodes, &index, &capacity);

  insertionSort(nodes, index);

  productNode *balancedRoot = buildBalancedTree(nodes, 0, index - 1);
  free(nodes);

  return balancedRoot;
}
/*
Functia pentru afisrea meniului de optiuni
@param root -arborele
@param file -fisierul cu date
@return NULL
*/
void mainMenu(productNode *root, FILE *file) {
  int option;
  int searchKey;
  do {

    printf("\nMeniu:\n");
    printf("%d. Citire producte\n", CITIRE_PRODUCTE);
    printf("%d. Cautarea unui nod\n", CAUTARE_PRODUCTE);
    printf("%d. Afisarea inordine\n", AFISARE_INORDINE);
    printf("%d. Parcurgerea preordine\n", PARCURGERE_PREORDINE);
    printf("%d. Parcurgerea postordine\n", PARCURGERE_POSTORDINE);
    printf("%d. Parcurgerea DFS\n", PARCURGERE_DFS);
    printf("%d. Parcurgerea BFS\n", PARCURGERE_BFS);
    printf("%d. Balansare arbore\n", BALANSARE_ARBORA);
    printf("%d.Iesire\n", IESIRE);

    scanf("%d", &option);
    switch ((enum MenuOption)option) {
    case CITIRE_PRODUCTE:
      read_product_tree(&root, file);
      break;
    case CAUTARE_PRODUCTE:
      printf("Introduceti cheia nodului cautat: ");
      scanf("%d", &searchKey);
      search(root, searchKey);
      break;
    case AFISARE_INORDINE:
      inorder(root);
      break;
    case PARCURGERE_PREORDINE:
      preorder(root);
      break;
    case PARCURGERE_POSTORDINE:
      postorder(root);
      break;
    case PARCURGERE_DFS:
      DFS(root);
      break;
    case PARCURGERE_BFS:
      BFS(root);
      break;
    case BALANSARE_ARBORA:
      root = balanceTree(root);
      printf("Arborele a fost balansat.\n");
      break;
    case IESIRE:
      break;
    default:
      printf("Optiune invalida! Va rugam sa alegeti din nou.\n");
    }
  } while (option != IESIRE);
}

int main() {

  productNode *root = NULL;
  FILE *file = fopen("produse.txt", "r");

  mainMenu(root, file);
}
