#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct productNode {
  int id;
  char *name;
  float price;
  int quantity;
  struct productNode *left;
  struct productNode *right;
} productNode;

enum MenuOption {
    CITIRE_PRODUCTE = 1,
    AFISARE_PRODUCTE,
    CALCUL_ADANCIME_ARBOR,
    CALCUL_ADANCIME_NOD,
    CALCUL_INALTIME_NOD,
    CAUTARE_NOD,
    AFISARE_FRUNZE,
    ELIBERARE_MEMORIE,
    CURATARE_ARBOR,
    IESIRE
};
enum MenuSearchOption{
  SEARCH_ID = 1,
  SEARCH_NAME,
  SEARCH_PRICE,
  SEARCH_QUANTITY,
};
/*
Functie pentru calcularea randrrilor din file
@parm fisier - fisierul din care se citesc randurile
@return randuri - numarul de randuri din fisier
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
Functie ajutatoare pentru introducerea datelor din fisier intr-un nod al arborelui
@param id - id-ul produsului
@param name - numele produsului
@param price - pretul produsului
@param quantity - cantitatea produsului
@return newNode - nodul cu datele introduse
*/
productNode *create_product_node(int id, const char *name, float price, int quantity) {
    productNode *newNode = (productNode*)malloc(sizeof(productNode));
    newNode->id = id;
    newNode->name = strdup(name);
    newNode->price = price;
    newNode->quantity = quantity;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}
/*
Functie pentru a introduce datele arborelui cu folosirea fuctiei create_product_node
@param id - id-ul produsului
@param name - numele produsului
@param price - pretul produsului
@param quantity - cantitatea produsului
@return root - arborele
*/
productNode *insert_product_node(productNode* root, int id, const char *name, float price,int quantity){
    if (root == NULL) {
        return create_product_node(id, name, price, quantity);
    } else {
        if (id <= root->id) {
            root->left = insert_product_node(root->left, id, name, price, quantity);
        } else {
            root->right = insert_product_node(root->right, id, name, price, quantity);
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
void read_product_tree(productNode** root, FILE *file) {
    if (file == NULL) {
        printf("Eroare la deschiderea fișierului!");
    }

    int id, quantity;
    char name[100];
    float price;

    int numLines = count_lines(file);

    for (int i = 0; i <= numLines; ++i) {
        fscanf(file, "%d %s %f %d", &id, name, &price, &quantity);
        *root = insert_product_node(*root, id, name, price, quantity);
    }

    fclose(file);
  printf("Produsele au fost citite");
}
/*
Functia pentru afisarea arborelui
@param root - arborele
@return void
*/
void print_product_tree(productNode* root) {
    if (root == NULL) {
        printf("Arborele este gol.\n");
        return;
    }

    productNode* queue[100];
    int front = 0, rear = 0;
    queue[rear++] = root;

    printf("Arborele de produse:\n");

    while (front < rear) {
        productNode* current = queue[front++];

        printf("%d, %s, %.2f, %d\n", current->id, current->name, current->price, current->quantity);

        if (current->left != NULL) {
            queue[rear++] = current->left;
        }
        if (current->right != NULL) {
            queue[rear++] = current->right;
        }
    }
}
/*
Functia pentru aflarea maximuylui din doua numere
@param a - primul numar
@param b - al doilea numar
@return max - maximul dintre cele doua numere
*/
int max(int a, int b) {
    return (a > b) ? a : b;
}
/*
Functia pentru aflarea adamcimea arborelui
@param root - arborele
@return adancime - adancimea arborelui
*/
int calculate_tree_depth(productNode* root) {
    if (root == NULL) {
        return 0;
    } else {
        int left_depth = calculate_tree_depth(root->left);
        int right_depth = calculate_tree_depth(root->right);
        return 1 + max(left_depth, right_depth);
    }
}
/*
Functia pentru aflarea adancimei nodului
@param root - arborele
@param key - id-ul nodului
@param depth - adancimea nodului
@return adancime - adancimea nodului
*/
int calculate_node_depth(productNode* root, int key, int depth) {
    if (root == NULL) {
        return -1; 
    }
    if (root->id == key) {
        return depth; 
    }
    if (key < root->id) {
        return calculate_node_depth(root->left, key, depth + 1);
    }
    return calculate_node_depth(root->right, key, depth + 1);
}
/*
Functie pntru aflarea inaltimei nodului
@param root - arborele
@param key - id-ul nodului
@param height - inaltimea noduluiâ
@return inaltimea - inaltimea nodului
*/
void calculate_node_height(productNode* root, int key, int* height) {
    if (root->id == key) {
        *height = 0; 
        return;
    }
    int left_height = -1, right_height = -1;
    if (key < root->id && root->left != NULL) {
        calculate_node_height(root->left, key, &left_height);
    }
    if (key > root->id && root->right != NULL) {
        calculate_node_height(root->right, key, &right_height);
    }
    if (left_height != -1) {
        *height = left_height + 1;
        return;
    }
    if (right_height != -1) {
        *height = right_height + 1;
        return;
    }
    *height = -1; 
}
/*
Functie pentru cautarea nodului
@param root - arborele
@return NULL
*/
void search_node(productNode* root) {
  productNode* result = NULL;
  int option, idKey,quantityKey;
  char nameKey[100];
  float priceKey;
  
  printf("Dupa ce cautai productul: \n");
  printf("%d:Cod\n%d:Nume\n%d:Pret\n%d:Cantitate\n",SEARCH_ID,SEARCH_NAME,SEARCH_PRICE,SEARCH_QUANTITY);
  scanf("%d", &option);
  
  switch ((enum MenuSearchOption)option) {
    case SEARCH_ID:
      printf("Id: ");
      scanf("%d", &idKey);
      while (root != NULL) {
          if (root->id == idKey) {
              result = root;
              break;
          }

          else if (idKey < root->id) {
              root = root->left;
          }
          else {
              root = root->right;
          }
      }
    break;
    case SEARCH_NAME:
      printf("Nume: ");
      scanf("%s", nameKey);
      while (root != NULL) {
        if (strcmp(nameKey, root->name) == 0) {
            result = root;
            break;
          }

          else if (idKey < root->id) {
              root = root->left;
          }
          else {
              root = root->right;
          }
      }
    break;
    case SEARCH_PRICE:
      printf("Pret: ");
      scanf("%f", &priceKey);
      while (root != NULL) {
        if (root->price == priceKey) {
            result = root;
            break;
          }

          else if (idKey < root->id) {
              root = root->left;
          }
          else {
              root = root->right;
          }
      }
    break;
    case SEARCH_QUANTITY:
      printf("Cantitate: ");
      scanf("%d", &quantityKey);
      while (root != NULL) {
        if (root->quantity == quantityKey) {
            result = root;
            break;
          }

          else if (idKey < root->id) {
              root = root->left;
          }
          else {
              root = root->right;
          }
      }
    break;
    default:
    printf("Optiune invalida! Va rugam sa alegeti din nou.\n");
  }
  


    if (result != NULL) {
        printf("\nNodul a fost gasit:\n");
        printf("ID: %d\n", result->id);
        printf("Nume: %s\n", result->name);
        printf("Preț: %.2f\n", result->price);
        printf("Cantitate: %d\n", result->quantity);
    } else {
        printf("Nodul nu a fost gasit.\n");
    }
}
/*
Functie pentru afisarea frunzelor arborelui
@param root - arborele
@return NULL
*/
void print_leaves(productNode* root) {
    if (root == NULL) {
        return;
    }
    if (root->left == NULL && root->right == NULL) {
        printf("%d, %s, %.2f, %d\n", root->id, root->name, root->price, root->quantity);
    }
    print_leaves(root->left);
    print_leaves(root->right);
}
/*
Functie pentru eliberarea memoirie arborelui
@param root - arborele
@return NULL
*/
void free_tree(productNode* root) {
    if (root == NULL) {
        return;
    }
    free_tree(root->left);
    free_tree(root->right);
    free(root->name);
    free(root);
}
/*
Functie pentru curatirea arborelui
@param root - arborele
@return NULL
*/
void clear_tree(productNode* root) {
    productNode* queue[100];
    int front = 0, rear = 0;
    queue[rear++] = root;

    while (front < rear) {
        productNode* current = queue[front++];

        current->id = 0;
        current->name = NULL;
        current->price = 0.0;
        current->quantity = 0;

        if (current->left != NULL) {
            queue[rear++] = current->left;
        }
        if (current->right != NULL) {
            queue[rear++] = current->right;
        }
    }
  printf("Arborele a fost curatit");
}

int main() {
    productNode *root = NULL;
    FILE *file = fopen("produse.txt", "r");
    int searchKey, nodeHeight;

    int option;
    do {
      printf("\nMeniu:\n");
      printf("%d. Citire producte\n", CITIRE_PRODUCTE);
      printf("%d. Afisare producte\n",AFISARE_PRODUCTE);
      printf("%d. Calcularea adincimi arborelui\n",CALCUL_ADANCIME_ARBOR);
      printf("%d. Calcularea adincimii nodului\n",CALCUL_ADANCIME_NOD);
      printf("%d. Calcularea inaltimi nodului\n",CALCUL_INALTIME_NOD);
      printf("%d. Cautarea unui nod\n",CAUTARE_NOD);
      printf("%d. Afisarea frunzelor\n",AFISARE_FRUNZE);
      printf("%d. Eliberarea memoriei\n",ELIBERARE_MEMORIE);
      printf("%d. Curatirea arborelui\n",CURATARE_ARBOR);
      printf("%d.Iesire\n",IESIRE);
      
      scanf("%d", &option);
      switch ((enum MenuOption)option) {
      case CITIRE_PRODUCTE:
        read_product_tree(&root, file);
        break;
      case AFISARE_PRODUCTE:
        print_product_tree(root);
        break;
      case CALCUL_ADANCIME_ARBOR:
        printf("Adincimea arborelui este: %d\n", calculate_tree_depth(root));
        break;
      case CALCUL_ADANCIME_NOD:
        printf("Introduceti id-ul nodului: ");
        scanf("%d",&searchKey);
        printf("Adancimea nodului %d este %d",searchKey,calculate_node_depth(root, searchKey, 0));
        break;
      case CALCUL_INALTIME_NOD:
        printf("Introduceti id-ul nodului: ");
        scanf("%d",&searchKey);
        calculate_node_height(root, searchKey, &nodeHeight);
        printf("Inaltimea nodului %d este %d\n", searchKey, nodeHeight);
        break;
      case CAUTARE_NOD:
        search_node(root);
        break;
      case AFISARE_FRUNZE:
        print_leaves(root);
        break;
      case ELIBERARE_MEMORIE:
        free_tree(root);
        break;
      case CURATARE_ARBOR:
        clear_tree(root);
      case IESIRE:
        break;
      default:
        printf("Optiune invalida! Va rugam sa alegeti din nou.\n");
        
      }
    } while (option != 0);
    return 0;
}
