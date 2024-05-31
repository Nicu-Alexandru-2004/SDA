#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Produs {
  int cod;
  char *nume;
  float pret;
  int cantitate;
};

typedef struct Produs produs;

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

void citeste_lista(FILE *f, produs **lista, int nrLines) {
  char nume[50];
  rewind(f);
  *lista = (produs *)malloc(nrLines * sizeof(produs));
  for (int i = 0; i < nrLines; i++) {
    fscanf(f, "%d", &((*lista)[i].cod));
    fscanf(f, "%s", nume);
    (*lista)[i].nume = strdup(nume);
    fscanf(f, "%f %d", &((*lista)[i].pret), &((*lista)[i].cantitate));
  }
  printf("Elementele au fost citite\n");
}
void afisare_lista(FILE *f, produs *lista, int nrLines) {

  if (lista != NULL) {
    printf("Lista de produse:\n");
    for (int i = 0; i < nrLines; i++) {
      printf("%d %s %.2f %d\n", lista[i].cod, lista[i].nume, lista[i].pret,
             lista[i].cantitate);
    }
  } else {
    printf("Lista este goala\n");
  }
}
void cautarea_element(FILE *f, produs *lista, int nrLines) {
  rewind(f);
  int option, searchCod, searchCantitate, found;
  char searchNume[50];
  float searchPret;

  printf("Dupa ce cautai produsul: \n");
  printf("1:Cod\n2:Pret\n3:Nume\n4:Cantitate\n");
  scanf("%d", &option);
  switch (option) {
  case 1:
    found = 0;
    printf("Scrie codul produsului: ");
    scanf("%d", &searchCod);
    for (int i = 0; i < nrLines; i++) {
      if (lista[i].cod == searchCod) {
        printf("Produsul se afla pe pozitia %d : %s %.2f %d\n", i + 1,
               lista[i].nume, lista[i].pret, lista[i].cantitate);
        found = 1;
      }
    }
    if (found == 0) {
      printf("Produsul nu a fost gasit\n");
    }
    break;
  case 2:
    found = 0;
    printf("Scrieti pretul produsului: ");
    scanf("%f", &searchPret);
    for (int i = 0; i < nrLines; i++) {
      if (lista[i].pret == searchPret) {
        printf("Produsul se afla pe pozitia %d : %s %d %d\n", i + 1,
               lista[i].nume, lista[i].cod, lista[i].cantitate);
        found = 1;
      }
    }
    if (found == 0) {
      printf("Produsul nu a fost gasit\n");
    }
    break;
  case 3:
    found = 0;
    printf("Scrieti numele produsului: ");
    scanf("%s", searchNume);
    for (int i = 0; i < nrLines; i++) {
      if (strcmp(searchNume, lista[i].nume) == 0) {
        printf("Produsul se afla pe pozitia %d : %f %d %d\n", i + 1,
               lista[i].pret, lista[i].cod, lista[i].cantitate);
        found = 1;
      }
    }
    if (found == 0) {
      printf("Produsul nu a fost gasit\n");
    }
    break;
  case 4:
    found = 0;
    printf("Scrieti cantitatea produsului: ");
    scanf("%d", &searchCantitate);
    for (int i = 0; i < nrLines; i++) {
      if (lista[i].cantitate == searchCantitate) {
        printf("Produsul se afla pe pozitia %d : %s %d %f\n", i + 1,
               lista[i].nume, lista[i].cod, lista[i].pret);
        found = 1;
      }
    }
    break;
  }
}
void eliberare_memorie(produs **lista, int nrLines) {
  if (*lista != NULL) {
    for (int i = 0; i < nrLines; i++) {
      free((*lista)[i].nume);
    }
    free(*lista);
    *lista = NULL;
    printf("Memoria a fost eliberata\n");
  } else {
    printf("Memeoria este deja goala\n");
  }
}
void sortare_elemtelor(produs *lista, int nrLines) {
  int option;

  printf("Dupa ce sortati: \n");
  printf("1:Cod\n2:Pret\n3:Nume\n4:Cantitate\n");
  scanf("%d", &option);
  switch (option) {
  case 1:
    for (int i = 0; i < nrLines - 1; i++) {
      for (int j = 0; j < nrLines - i - 1; j++) {
        if (lista[j].cod > lista[j + 1].cod) {
          produs temp = lista[j];
          lista[j] = lista[j + 1];
          lista[j + 1] = temp;
        }
      }
    }
    break;
  case 2:
    for (int i = 0; i < nrLines - 1; i++) {
      for (int j = 0; j < nrLines - i - 1; j++) {
        if (lista[j].pret < lista[j + 1].pret) {
          produs temp = lista[j];
          lista[j] = lista[j + 1];
          lista[j + 1] = temp;
        }
      }
    }
    break;
  case 3:
    for (int i = 0; i < nrLines - 1; i++) {
      for (int j = 0; j < nrLines - i - 1; j++) {
        if (strcmp(lista[j].nume, lista[j + 1].nume) > 0) {
          produs temp = lista[j];
          lista[j] = lista[j + 1];
          lista[j + 1] = temp;
        }
      }
    }
    break;
  case 4:
    for (int i = 0; i < nrLines - 1; i++) {
      for (int j = 0; j < nrLines - i - 1; j++) {
        if (lista[j].cantitate > lista[j + 1].cantitate) {
          produs temp = lista[j];
          lista[j] = lista[j + 1];
          lista[j + 1] = temp;
        }
      }
    }
    break;
  }
}
void inserarea_sfarsit(produs **lista, int *nrLines) {
  char nume[20];
  (*nrLines)++;
  *lista = (produs *)realloc(*lista, (*nrLines) * sizeof(produs));
  printf("Introduceti date pentru nou produs: \n");
  printf("Cod: ");
  scanf("%d", &((*lista)[*nrLines - 1].cod));
  printf("Nume: ");
  scanf("%s", nume);
  (*lista)[*nrLines-1].nume = strdup(nume);
  printf("Pret: ");
  scanf("%f", &((*lista)[*nrLines - 1].pret));
  printf("Cantitate: ");
  scanf("%d", &((*lista)[*nrLines - 1].cantitate));
}
void inserarea_inceput(produs **lista, int *nrLines) {
  char nume[20];
  (*nrLines)++;
  *lista = (produs *)realloc(*lista, (*nrLines) * sizeof(produs));

  for (int i = (*nrLines) - 1; i > 0; i--) {
    (*lista)[i] = (*lista)[i - 1];
  }
  printf("Introduceti date pentru nou produs: \n");
  printf("Cod: ");
  scanf("%d", &((*lista)[0].cod));
  printf("Nume: ");
  scanf("%s", nume);
  (*lista)[0].nume = strdup(nume);
  printf("Pret: ");
  scanf("%f", &((*lista)[0].pret));
  printf("Cantitate: ");
  scanf("%d", &((*lista)[0].cantitate));
}
void inserare_pozitie(produs **lista, int *nrLines) {
  char nume[20];
  int pozitie;
  printf("Introduceti pozitia: ");
  scanf("%d", &pozitie);
  if (pozitie >= 1 && pozitie <= *nrLines + 1) {
    (*nrLines)++;
    *lista = (produs *)realloc(*lista, (*nrLines) * sizeof(produs));
    for (int i = (*nrLines) - 1; i > pozitie - 1; i--) {
      (*lista)[i] = (*lista)[i - 1];
    }
    printf("Introduceti date pentru nou produs: \n");
    printf("Cod: ");
    scanf("%d", &((*lista)[pozitie - 1].cod));
    printf("Nume: ");
    scanf("%s", nume);
    (*lista)[pozitie - 1].nume = strdup(nume);
    printf("Pret: ");
    scanf("%f", &((*lista)[pozitie - 1].pret));
    printf("Cantitate: ");
    scanf("%d", &((*lista)[pozitie - 1].cantitate));
  }
}
void sterger_produs(produs **lista, int *nrLines) {
  int pozitie;
  printf("Introduceti pozitia: ");
  scanf("%d", &pozitie);
  free((*lista)[pozitie - 1].nume);
  if (pozitie >= 1 && pozitie <= *nrLines) {
    for (int i = pozitie - 1; i < *nrLines - 1; i++) {
      (*lista)[i] = (*lista)[i + 1];
    }
    (*nrLines)--;
    *lista = (produs *)realloc(*lista, (*nrLines) * sizeof(produs));
  }
}

int main() {
  produs *lista = NULL;
  int nrLines;
  FILE *f;
  int option;

  f = fopen("produse.txt", "r");
  nrLines = count_lines(f);

  do {
    printf("\nMeniu:\n");
    printf("1. Citire produse\n");
    printf("2. Afisare produse\n");
    printf("3. Cautare produs dupa criteriu\n");
    printf("4. Eliberare memorie\n");
    printf("5. Sortare produs dupa criteriu\n");
    printf("6. Inserare produs la capat\n");
    printf("7. Inserare produs la inceput\n");
    printf("8. Inserare produs la o anumita pozitie\n");
    printf("9. Stergere produs de la o anumita pozitie\n");
    printf("0. Iesire\n");

    scanf("%d", &option);
    switch (option) {
    case 1:
      citeste_lista(f, &lista, nrLines);
      break;
    case 2:
      afisare_lista(f, lista, nrLines);
      break;
    case 3:
      cautarea_element(f, lista, nrLines);
      break;
    case 4:
      eliberare_memorie(&lista, nrLines);
      break;
    case 5:
      sortare_elemtelor(lista, nrLines);
      break;

    case 6:
      inserarea_sfarsit(&lista, &nrLines);
      break;

    case 7:
      inserarea_inceput(&lista, &nrLines);
      break;

    case 8:
      inserare_pozitie(&lista, &nrLines);
      break;

    case 9:
      sterger_produs(&lista, &nrLines);
      break;

    case 0:
      break;
    }
  } while (option != 0);
}
