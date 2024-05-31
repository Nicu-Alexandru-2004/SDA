#include <stdio.h>
#include <stdlib.h>
#include <time.h>

enum MenuOption {
  AFISARE_TABLOU = 1,
  ELIBERAREA_MEMORIEI,
  SORTATREA_TABLOULUI,
  CAUTARE_TABLOU_LINIAR,
  CAUTARE_TABLOU_BINAR,
  IESIRE
};
/*
Functia pentru generarea numerelor aliatoare in tablou
@param tab - tabloul unidimensional
@param lungime - lungimea tabloului
@return NULL
*/
void randomNumberGeneration(int *tab, int lungime) {
  srand(time(NULL));
  for (int i = 0; i < lungime; i++) {
    tab[i] = rand() % 100;
  }
}
/*
Functia pentru afisare tabloului
@param tab - tabloul unidimensional
@param lungime - lungimea tabloului
@return NULL
*/
void afisareTablou(int *tab, int lungime) {
  printf("Tabloul este: ");
  for (int i = 0; i < lungime; i++) {
    printf("%d ", tab[i]);
  }
  printf("\n");
}
/*
Functia pentru eliberearea memorie tabloului
@param tab - tabloul unidimensional
@return NULL
*/
void freeMemory(int *tab) { free(tab); }
/*
Functia sortarea tabloului prin SelectionSort
@param tab - tabloul unidimensional
@param lungime - lungimea tabloului
@return NULL
*/
void selectionSort(int *tab, int lungime) {
  clock_t start = clock();

  for (int i = 0; i < lungime - 1; i++) {
    int min_index = i;
    for (int j = i + 1; j < lungime; j++) {
      if (tab[j] < tab[min_index]) {
        min_index = j;
      }
    }
    int temp = tab[min_index];
    tab[min_index] = tab[i];
    tab[i] = temp;
  }

  clock_t end = clock();
  printf("\nSelection sort a fost executat in %f secunde.\n",
         (double)(end - start) / CLOCKS_PER_SEC);
}
/*
Functia sortarea tabloului prin InsertionSort
@param tab - tabloul unidimensional
@param lungime - lungimea tabloului
@return NULL
*/
void insertionSort(int *tab, int lungime) {
  clock_t start = clock();

  for (int i = 1; i < lungime; i++) {
    int key = tab[i];
    int j = i - 1;
    while (j >= 0 && tab[j] > key) {
      tab[j + 1] = tab[j];
      j = j - 1;
    }
    tab[j + 1] = key;
  }

  clock_t end = clock();
  printf("Insertion sort a fost executat in %f secunde.\n",
         (double)(end - start) / CLOCKS_PER_SEC);
}
/*
Functia sortarea tabloului prin BubbleSort
@param tab - tabloul unidimensional
@param lungime - lungimea tabloului
@return NULL
*/
void bubbleSort(int *tab, int lungime) {
  clock_t start = clock();

  for (int i = 0; i < lungime - 1; i++) {
    for (int j = 0; j < lungime - i - 1; j++) {
      if (tab[j] > tab[j + 1]) {
        int temp = tab[j];
        tab[j] = tab[j + 1];
        tab[j + 1] = temp;
      }
    }
  }

  clock_t end = clock();
  printf("Bubble sort a fost executat in %f secunde.\n",
         (double)(end - start) / CLOCKS_PER_SEC);
}
/*
Functie de ajutor pentru QuickSort
@param tab -abloul de numere întregi care trebuie sortat.
@param st - indexul de început al porțiunii de tablou
@param dr - indexul de final al porțiunii de tablou
return i+1 -indexul
*/
int partition(int *tab, int st, int dr) {
  int pivot = tab[dr];
  int i = (st - 1);

  for (int j = st; j <= dr - 1; j++) {
    if (tab[j] < pivot) {
      i++;
      int temp = tab[i];
      tab[i] = tab[j];
      tab[j] = temp;
    }
  }
  int temp = tab[i + 1];
  tab[i + 1] = tab[dr];
  tab[dr] = temp;
  return (i + 1);
}
/*
Functia sortarea tabloului prin QuickSort
@param tab - tabloul unidimensional
@param st - indexul de început al porțiunii de tablou
@param dr - indexul de final al porțiunii de tablou
@param timpTotal - timpul total de executie
@return NULL
*/
void quickSort(int *tab, int st, int dr, double *timpTotal) {
  if (st < dr) {
    int pi = partition(tab, st, dr);
    quickSort(tab, st, pi - 1, timpTotal);
    quickSort(tab, pi + 1, dr, timpTotal);
  }
}
/*
Functia de apelare a sortari tabloului prin QuickSort
@param tab - tabloul unidimensional
@param lungime - lungimea tabloului
@return NULL
*/
void callQuickSort(int *tab, int lungime) {
  clock_t start = clock();
  double timpTotal;

  quickSort(tab, 0, lungime - 1, &timpTotal);

  clock_t end = clock();
  timpTotal += (double)(end - start) / CLOCKS_PER_SEC;
  printf("Quick sort a fost executat in %f secunde.\n", timpTotal);
}
/*
Functia ajutaotre pentru MergeSort
@param tab - tabloul unidimensional
@param st -indedul de început al porțiunii de tablou
@param dr - indexul de final al porțiunii de tablou
@parm mijloc - indexul de mijloc al porțiunii de tablou
@return NULL
*/
void merge(int *tab, int st, int mijloc, int dr) {
  int i, j, k;
  int n1 = mijloc - st + 1;
  int n2 = dr - mijloc;

  int *L = (int *)malloc(n1 * sizeof(int));
  int *R = (int *)malloc(n2 * sizeof(int));

  for (i = 0; i < n1; i++)
    L[i] = tab[st + i];
  for (j = 0; j < n2; j++)
    R[j] = tab[mijloc + 1 + j];

  i = 0;
  j = 0;
  k = st;
  while (i < n1 && j < n2) {
    if (L[i] <= R[j]) {
      tab[k] = L[i];
      i++;
    } else {
      tab[k] = R[j];
      j++;
    }
    k++;
  }

  while (i < n1) {
    tab[k] = L[i];
    i++;
    k++;
  }

  while (j < n2) {
    tab[k] = R[j];
    j++;
    k++;
  }

  free(L);
  free(R);
}
/*
Functia pentru sortarea tbloului prin MergeSort
@param tab - tabloul unidimensional
@param st -indedul de început al porțiunii de tablou
@param dr - indexul de final al porțiunii de tablou
@parm timpTotal - timpul de executie
@return NULL
*/
void mergeSort(int *tab, int st, int dr, double *timpTotal) {
  if (st < dr) {
    int mijloc = st + (dr - st) / 2;
    mergeSort(tab, st, mijloc, timpTotal);
    mergeSort(tab, mijloc + 1, dr, timpTotal);
    merge(tab, st, mijloc, dr);
  }
}
/*
Functia de apelare a sortari tabloului prin MergeSort
@param tab - tabloul unidimensional
@param lungime - lungimea tabloului
@return NULL
*/
void callMergeSort(int *tab, int lungime) {
  clock_t start = clock();
  double timpTotal;

  mergeSort(tab, 0, lungime - 1, &timpTotal);

  clock_t end = clock();
  timpTotal += (double)(end - start) / CLOCKS_PER_SEC;
  printf("Merge sort a fost executat in %f secunde.\n", timpTotal);
}
/*
Functia de cautarea a unui element  prin LiniarSearch
@param tab - tabloul unidimensional
@param lungime - lungimea tabloului
@param valoareaCautata - vloarea cautata
@return NULL
*/
double linearSearch(int *tab, int lungime, int valoareCautata) {
  clock_t start = clock();
  for (int i = 0; i < lungime; i++) {
    if (tab[i] == valoareCautata) {
      clock_t end = clock();
      return ((double)(end - start)) / CLOCKS_PER_SEC;
    }
  }
  return -1;
}
/*
Functia pentru apelarea cautarii unui element prin LiniarSearch
@param tab - tabloul unidimensional
@param lungime - lungimea tabloului
@return NULL
*/
void callLinearSearch(int *tablou, int lungime) {
  int valoareCautata;
  double timp;

  printf("Introdu valoarea pe care doresti sa o cauti: ");
  scanf("%d", &valoareCautata);
  timp = linearSearch(tablou, lungime, valoareCautata);
  if (timp != -1) {
    printf("Valoarea a fost gasita in %.6f secunde.\n", timp);
  } else {
    printf("Valoarea nu a fost gasita.\n");
  }
}
double binarySearch(int *tablou, int lungime, int valoareCautata) {
  clock_t start = clock();
  int stanga = 0, dreapta = lungime - 1;

  while (stanga <= dreapta) {
    int mijloc = stanga + (dreapta - stanga) / 2;

    if (tablou[mijloc] == valoareCautata) {
      clock_t end = clock();
      return ((double)(end - start)) / CLOCKS_PER_SEC;
    }

    if (tablou[mijloc] < valoareCautata) {
      stanga = mijloc + 1;
    }

    else {
      dreapta = mijloc - 1;
    }
  }
  return -1;
}
void callBinarySearch(int *tablou, int lungime) {
  int valoareCautata;
  double timp;

  printf("Introdu valoarea pe care doresti sa o cauti: ");
  scanf("%d", &valoareCautata);
  timp = binarySearch(tablou, lungime, valoareCautata);
  if (timp != -1) {
    printf("Valoarea a fost gasita in %.6f secunde.\n", timp);
  } else {
    printf("Valoarea nu a fost gasita.\n");
  }
}

void mainMenu(int *tab, int lungime) {
  int option;
  do {
    printf("\n");
    printf("%d. Afisare tablou\n", AFISARE_TABLOU);
    printf("%d. Eliberare memorie\n", ELIBERAREA_MEMORIEI);
    printf("%d. Sortare tabloului\n", SORTATREA_TABLOULUI);
    printf("%d. Cautare elemente liniar search\n", CAUTARE_TABLOU_LINIAR);
    printf("%d. Cautare elemente binar search\n", CAUTARE_TABLOU_BINAR);
    printf("%d. Iesire\n", IESIRE);
    printf("\nIntroduceti optiunea: ");
    scanf("%d", &option);
    switch ((enum MenuOption)option) {
    case AFISARE_TABLOU:
      afisareTablou(tab, lungime);
      break;
    case ELIBERAREA_MEMORIEI:
      freeMemory(tab);
      break;
    case SORTATREA_TABLOULUI:
      selectionSort(tab, lungime);
      insertionSort(tab, lungime);
      bubbleSort(tab, lungime);
      callQuickSort(tab, lungime);
      callMergeSort(tab, lungime);
      break;
    case CAUTARE_TABLOU_LINIAR:
      callLinearSearch(tab, lungime);
      break;
    case CAUTARE_TABLOU_BINAR:
      callBinarySearch(tab, lungime);
      break;
    case IESIRE:
      break;
    default:
      printf("Optiune invalida!\n");
    }
  } while (option != IESIRE);
}

int main() {
  int *tab, lungime;

  printf("Introduceti lungimea tabloului: ");
  scanf("%d", &lungime);

  tab = (int *)malloc(lungime * sizeof(int));

  randomNumberGeneration(tab, lungime);

  mainMenu(tab, lungime);
  return 0;
}
