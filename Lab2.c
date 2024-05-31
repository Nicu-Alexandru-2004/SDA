#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct product {
  int id;
  char *name;
  float price;
  int quatity;
  struct product *next;
};

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
void read_list(FILE *f, struct product **list, int nrLines) {
  rewind(f);
  f = fopen("produse.txt", "r");
  if (*list == NULL) {
    struct product *temp = NULL;
    char name[50];

    for (int i = 0; i <= nrLines; i++) {
      temp = (struct product *)malloc(sizeof(struct product));
      fscanf(f, "%d", &temp->id);
      fscanf(f, "%s", name);
      temp->name = strdup(name);
      fscanf(f, "%f", &temp->price);
      fscanf(f, "%d", &temp->quatity);
      temp->next = *list;

      *list = temp;
    }
  }
  printf("Elementele au fost citite\n");
}
void write_list(struct product *list) {
  struct product *temp = list;

  while (temp != NULL) {
    printf("%d %s %.2f %d\n", temp->id, temp->name, temp->price, temp->quatity);
    temp = temp->next;
  }
}
void search_product(struct product *list) {
  int option, searchID, searchQuantiti, found, position = 0;
  char searchName[50];
  float searchPrice;
  struct product *temp = list;

  printf("Dupa ce cautai productul: \n");
  printf("1:Cod\n2:Pret\n3:Nume\n4:Cantitate\n");
  scanf("%d", &option);
  switch (option) {
  case 1:
    found = 0;
    printf("Scrie codul productului: ");
    scanf("%d", &searchID);
    while (temp != NULL) {
      if (temp->id == searchID) {
        printf("Elementul se afla pe pozitia %d", position);
        found = 1;
      }
      temp = temp->next;
      position++;
    }
    if (found == 0) {
      printf("productul nu a fost gasit\n");
    }
    break;
  case 2:
    found = 0;
    printf("Scrie price productului: ");
    scanf("%f", &searchPrice);
    while (temp != NULL) {
      if (temp->price == searchPrice) {
        printf("Elementul se afla pe pozitia %d", position);
        found = 1;
      }
      temp = temp->next;
      position++;
    }
    if (found == 0) {
      printf("productul nu a fost gasit\n");
    }
    break;
  case 3:
    found = 0;
    printf("Scrie  name productului: ");
    scanf("%s", searchName);
    while (temp != NULL) {
      if (strcmp(searchName, list->name) == 0) {
        printf("Elementul se afla pe pozitia %d", position);
        found = 1;
      }
      temp = temp->next;
      position++;
    }
    if (found == 0) {
      printf("productul nu a fost gasit\n");
    }
    break;
  case 4:
    found = 0;
    printf("Scrie quatity productului: ");
    scanf("%d", &searchQuantiti);
    while (temp != NULL) {
      if (temp->quatity == searchQuantiti) {
        printf("Elementul se afla pe pozitia %d", position);
        found = 1;
      }
      temp = temp->next;
      position++;
    }
    if (found == 0) {
      printf("productul nu a fost gasit\n");
    }
    break;
  }
}
void free_memory(struct product **list) {
  struct product *temp, *following;

  if (*list != NULL) {
    temp = *list;
    while (temp != NULL) {
      following = temp->next;
      free(temp->name);
      free(temp);
      temp = following;
    }
    *list = NULL;
    printf("Memoria a fost eliberata\n");
  } else {
    printf("Lista este goala\n");
  }
}
void sort_elemets(struct product **list) {
  struct product *current = *list;
  struct product *following = NULL;
  int option, searchID, searchQuantiti;
  char searchName[50];
  float searchPrice;

  printf("Dupa ce sortati: \n");
  printf("1:Cod\n2:Pret\n3:Nume\n4:Cantitate\n");
  scanf("%d", &option);
  switch (option) {
  case 1:
    while (current->next != NULL) {
      following = current->next;
      while (following != NULL) {
        if (current->id > following->id) {
          int tempCod = current->id;
          current->id = following->id;
          following->id = tempCod;
        }
        following = following->next;
      }
      current = current->next;
    }
    break;

  case 2:
    while (current->next != NULL) {
      following = current->next;
      while (following != NULL) {
        if (current->price > following->price) {
          float tempPret = current->price;
          current->price = following->price;
          following->price = tempPret;
        }
        following = following->next;
      }
      current = current->next;
    }
    break;
  case 3:
    while (current->next != NULL) {
      following = current->next;
      while (following != NULL) {
        if (strcmp(current->name, following->name) > 0) {
          char *tempNume = current->name;
          current->name = following->name;
          following->name = tempNume;
        }
        following = following->next;
      }
      current = current->next;
    }
    break;
  case 4:
    while (current->next != NULL) {
      following = current->next;
      while (following != NULL) {
        if (current->quatity > following->quatity) {
          int tempCantitate = current->quatity;
          current->quatity = following->quatity;
          following->quatity = tempCantitate;
        }
        following = following->next;
      }
      current = current->next;
    }
    break;
  }
}
void insert_end(struct product **list) {
  struct product *temp, *last;

  temp = (struct product *)malloc(sizeof(struct product));
  if (temp == NULL) {
    printf("Eroare la alocarea de memorie\n");
    return;
  }

  char name[50];
  printf("Introduceti date pentru noul product: \n");
  printf("Cod: ");
  scanf("%d", &temp->id);
  printf("Nume: ");
  scanf("%s", name);
  temp->name = strdup(name);
  printf("Pret: ");
  scanf("%f", &temp->price);
  printf("Cantitate: ");
  scanf("%d", &temp->quatity);
  temp->next = NULL;

  if (*list == NULL) {
    *list = temp;
  } else {
    last = *list;
    while (last->next != NULL) {
      last = last->next;
    }
    last->next = temp;
  }
}
void insert_start(struct product **list) {
  struct product *temp;
  char name[20];

  temp = (struct product *)malloc(sizeof(struct product));
  printf("Introduceti date pentru nou product: \n");
  printf("Cod: ");
  scanf("%d", &temp->id);
  printf("Nume: ");
  scanf("%s", name);
  temp->name = strdup(name);
  printf("Pret: ");
  scanf("%f", &temp->price);
  printf("Cantitate: ");
  scanf("%d", &temp->quatity);
  temp->next = *list;

  *list = temp;
}
void insert_position(struct product **list) {
  struct product *temp, *previous, *current;
  char name[20];
  int position, count = 1;

  printf("Introduceti pozitia: ");
  scanf("%d", &position);

  temp = (struct product *)malloc(sizeof(struct product));
  temp->next = NULL;


  printf("Introduceti date pentru noul produs: \n");
  printf("Cod: ");
  scanf("%d", &temp->id);
  printf("Nume: ");
  scanf("%s", name);
  temp->name = strdup(name);
  printf("Pret: ");
  scanf("%f", &temp->price);
  printf("Cantitate: ");
  scanf("%d", &temp->quatity);

  if (position == 1) {
    temp->next = *list;
    *list = temp;
  } else {
    current = *list;
    previous = NULL;

    while (current != NULL && count < position) {
      previous = current;
      current = current->next;
      count++;
    }

    if (count != position) {
      printf("Pozitia specificata depaseste lungimea listei\n");
      free(temp->name);
      free(temp);
      return;
    }

    if (current == NULL) {
      previous->next = temp;
    } else {
      previous->next = temp;
      temp->next = current;
    }
  }
}
void delete_position(struct product **list) {
  struct product *temp, *precedent;
  int count = 1, position;

  printf("Introduceti pozitia: ");
  scanf("%d", &position);

  if (position == 1) {
    temp = *list;
    *list = (*list)->next;
    free(temp);
  } else {
    temp = *list;
    precedent = NULL;
    while (temp != NULL && count <= position) {
      precedent = temp;
      temp = temp->next;
      count++;
    }
    if (temp != NULL) {
      precedent->next = temp->next;
      free(temp);
    }
  }
}
void invert_list(struct product **list) {
  struct product *precedent, *current, *following;

  precedent = NULL;
  current = *list;

  while (current != NULL) {
    following = current->next;
    current->next = precedent;
    precedent = current;
    current = following;
  }

  *list = precedent;

  printf("Lista a fost inversata\n");
}
void clean_list(struct product **list) {
  struct product *current, *following;

  current = *list;

  while (current != NULL) {
    following = current->next;
    free(current->name);
    free(current);
    current = following;
  }

  *list = NULL;
  printf("Lista a fost curatita\n");
}

int main() {
  struct product *list = NULL;
  int nrLines;
  FILE *f;
  int option;

  f = fopen("produse.txt", "r");
  nrLines = count_lines(f);

  do {
    printf("\nMeniu:\n");
    printf("1. Citire producte\n");
    printf("2. Afisare producte\n");
    printf("3. Cautare producte\n");
    printf("4. Eliberarea memorie\n");
    printf("5. Sortare producte\n");
    printf("6. Inserarea product sfarsit\n");
    printf("7. Inserarea product inceput\n");
    printf("8. Inserarea product dupa position\n");
    printf("9. Stergerea product dupa position\n");
    printf("10. Inversarea listei\n");
    printf("11. Curatire listei\n");
    printf("0.Iesire\n");

    scanf("%d", &option);
    switch (option) {
    case 1:
      read_list(f, &list, nrLines);
      break;
    case 2:
      write_list(list);
      break;
    case 3:
      search_product(list);
      break;
    case 4:
      free_memory(&list);
      break;
    case 5:
      sort_elemets(&list);
      break;
    case 6:
      insert_end(&list);
      break;
    case 7:
      insert_start(&list);
      break;
    case 8:
      insert_position(&list);
      break;
    case 9:
      delete_position(&list);
      break;
    case 10:
      invert_list(&list);
      break;
    case 11:
      clean_list(&list);
      break;
    case 0:
      break;
    }
  } while (option != 0);

  fclose(f);
  return 0;
}
