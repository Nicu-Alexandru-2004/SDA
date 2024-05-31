#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Produs {
  char data[11];
  int Id;
  char nume[50];
  char categorie[50];
  char subCategorie[50];
  double pret;
  int cantitate;
  char tara[50];
  char oras[50];
  double venit;
} products;
typedef struct VenitLunar {
  char luna[3];
  double venitTotal;
} LunarIncome;
typedef struct fiveBest {
  char nume[50];
  double venit;
} fiveBest;
typedef struct fiveBestTemp{
  double venit;
  char nume[50];
}fiveBestTemp;
typedef struct categor{
  char categorie[50];
  double venit;
}catergoryGroup;
typedef struct city{
  char oras[50];
  char tara[50];
  double venit;
}cityIncome;

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
void read_list(FILE *f, products **lista, int nrLines) {
  rewind(f);
  *lista = (products *)malloc(nrLines * sizeof(products));
  for (int i = 0; i < nrLines; i++) {
    fscanf(f, " %10[^,],%d,%49[^,],%49[^,],%49[^,],%lf,%d,%49[^,],%49[^\n]",
           (*lista)[i].data, &(*lista)[i].Id, (*lista)[i].nume,
           (*lista)[i].categorie, (*lista)[i].subCategorie, &(*lista)[i].pret,
           &(*lista)[i].cantitate, (*lista)[i].tara, (*lista)[i].oras);
    (*lista)[i].venit = (*lista)[i].pret * (*lista)[i].cantitate;
  }
}
void print_list(products *lista, int nrLines) {
  printf("Lista de produse:\n");
  for (int i = 0; i < nrLines; i++) {
    printf("%s, %d, %s, %s, %s, %2.lf, %d, %s, %s", lista[i].data, lista[i].Id,
           lista[i].nume, lista[i].categorie, lista[i].subCategorie,
           lista[i].pret, lista[i].cantitate, lista[i].tara, lista[i].oras);
    printf("\n");
  }
}
void print_Income(products *lista, int nrLines){
  printf("\nVenitul: \n");
  for (int i = 0; i < nrLines; i++) {
    printf("%d %2.lf \n", lista[i].Id, lista[i].venit);
  }
}

void group_Income_per_Month(int nrLines, LunarIncome **lunarIncome, products *list){
  *lunarIncome = (LunarIncome *)malloc(12 * sizeof(LunarIncome));
  char first1 = '0';
  char first2 = '0';

   for(int i = 0; i < 12; i++){
     (*lunarIncome)[i].venitTotal = 0;
   }

  for(int i = 0; i < 12; i++){
    if(i<9){
      first1++;
      (*lunarIncome)[i].luna[0] = '0';
      (*lunarIncome)[i].luna[1] = first1;
    }
    else{
      (*lunarIncome)[i].luna[0] = '1';
      (*lunarIncome)[i].luna[1] = first2;
      first2++;
    }
  }

  for(int i = 0; i<nrLines;i++){
    for(int j = 0; j<12;j++){
      if(strncmp(list[i].data+3, (*lunarIncome)[j].luna,2) == 0){
        (*lunarIncome)[j].venitTotal += list[i].venit;
      }
    }
  }
  printf("\nVenit pe luna: \n");
  for(int i = 0; i < 12; i++){
    printf("%s %2.lf \n", (*lunarIncome)[i].luna, (*lunarIncome)[i].venitTotal);
  }
  
} 
void group_five_best_income(int nrLines, products *list, fiveBest **bestProducts) {
  *bestProducts = (fiveBest *)malloc(5 * sizeof(fiveBest));
  fiveBestTemp *bestProductsTemp = (fiveBestTemp *)malloc(nrLines * sizeof(fiveBestTemp));
  int count = 0;

  for (int i = 0; i < 5; i++) {
    strcpy((*bestProducts)[i].nume, "");
    (*bestProducts)[i].venit = 0.0;
  }

  for (int i = 0; i < 5; i++) {
    strcpy(bestProductsTemp[i].nume, "");
    bestProductsTemp[i].venit = 0.0;
  }

  for (int i = 0; i < nrLines; i++) {
    int found = 0;

    for (int j = 0; j < nrLines; j++) {
      if (strcmp(bestProductsTemp[j].nume, list[i].nume) == 0) {
        bestProductsTemp[j].venit += list[i].venit;  
        found = 1;
        break;
      }
    }

    if (!found) {
      for (int j = 0; j < nrLines; j++) {
        if (strcmp(bestProductsTemp[j].nume, "") == 0) {
          strcpy(bestProductsTemp[j].nume, list[i].nume);
          bestProductsTemp[j].venit += list[i].venit;
          count++;
          break;
        }
      }
    }
  }

  for (int i = 0; i < count - 1; i++) {
    for (int j = 0; j < count - i - 1; j++) {
      if (bestProductsTemp[j].venit < bestProductsTemp[j + 1].venit) {
        fiveBestTemp temp = bestProductsTemp[j];
        bestProductsTemp[j] = bestProductsTemp[j + 1];
        bestProductsTemp[j + 1] = temp;
      }
    }
  }
  
  printf("\nCele cinci produse cu cel mai mare venit acumulat\n");
  for (int i = 0; i < 5; i++) {
    strcpy((*bestProducts)[i].nume, bestProductsTemp[i].nume);
    (*bestProducts)[i].venit += bestProductsTemp[i].venit;
    printf("%s - %2.lf\n", (*bestProducts)[i].nume, (*bestProducts)[i].venit);
  }
  free(bestProductsTemp);
}
void group_category(int nrLines, products *list, catergoryGroup **caterG){
  (*caterG)= (catergoryGroup *)malloc(nrLines * sizeof(catergoryGroup));
  for (int i = 0; i < nrLines; i++) {
    strcpy((*caterG)[i].categorie, "");
    (*caterG)[i].venit = 0;
  }
  for (int i = 0; i < nrLines; i++){

    int found = 0;
    for (int j = 0; j < nrLines; j++){
      if(strcmp((*caterG)[j].categorie, list[i].categorie) == 0){
        (*caterG)[j].venit += list[i].venit;
        found = 1;
        break;
      }
    }

    if(!found){
      for(int j = 0; j<nrLines; j++){
        if(strcmp((*caterG)[j].categorie, "") == 0){
          strcpy((*caterG)[j].categorie, list[i].categorie);
          (*caterG)[j].venit +=list[i].venit;
          break;
        }
      }
    }

  }
  int i =0;
  printf("\nClasificarea pe categorii\n");
  while(strcmp((*caterG)[i].categorie, "") != 0){
    printf("%s - %2.lf\n",(*caterG)[i].categorie, (*caterG)[i].venit);
    i++;
  }
}
void group_best_city_income(int nrLines, products *list, cityIncome **bestCityIncome) {
  *bestCityIncome = (cityIncome *)malloc(nrLines * sizeof(cityIncome));

  for (int i = 0; i < nrLines; i++) {
    strcpy((*bestCityIncome)[i].oras, "");
    strcpy((*bestCityIncome)[i].tara, "");
    (*bestCityIncome)[i].venit = 0;
  }

  for (int i = 0; i < nrLines; i++) {
    int found = 0;

    for (int j = 0; j < nrLines; j++) {
      if (strcmp((*bestCityIncome)[j].tara, list[i].tara) == 0) {
        if (list[i].venit > (*bestCityIncome)[j].venit) {
          strcpy((*bestCityIncome)[j].oras, list[i].oras);
          (*bestCityIncome)[j].venit = list[i].venit;
        }
        found = 1;
        break;
      }
    }

    if (!found) {
      for (int j = 0; j < nrLines; j++) {
        if (strcmp((*bestCityIncome)[j].tara, "") == 0) {
          strcpy((*bestCityIncome)[j].tara, list[i].tara);
          strcpy((*bestCityIncome)[j].oras, list[i].oras);
          (*bestCityIncome)[j].venit = list[i].venit;
          break;
        }
      }
    }
  }


  int i = 0;
  printf("\nClasificarea pe orase\n");
  while (strcmp((*bestCityIncome)[i].tara, "") != 0) {
    printf("%s %s - %2.lf\n", (*bestCityIncome)[i].tara, (*bestCityIncome)[i].oras, (*bestCityIncome)[i].venit);
    i++;
  }
}


int main() {
  FILE *f;
  int nrLines, option;
  products *list = NULL;
  LunarIncome *lunarIncome = NULL;
  fiveBest *bestProducts = NULL;
  catergoryGroup *caterG = NULL;
  cityIncome *bestCityIncome = NULL;

  f = fopen("produse.txt", "r");
  nrLines = count_lines(f) + 1;

  read_list(f, &list, nrLines);





  do{
    printf("\nMeniu:\n");
    printf("Printati lista de produse: 1\n");
    printf("Printati venitul produselor\n");
    printf("Printati venitul pe luna: 3\n");
    printf("Printati clasificarea pe categorii: 4\n");
    printf("Printa orasele cu cel mai bun venit: 5\n");
    printf("Cele cinci produse cu cel mai mare venit acumulat: 6\n");
    printf("Iesire: 0\n");
    scanf("%d", &option);
    switch (option) {
      case 1:
      print_list( list,nrLines);
      break;
      case 3:
        group_Income_per_Month(nrLines, &lunarIncome, list);
      break;
      case 4:
        group_category(nrLines, list, &caterG);
      break;
      case 5:
        group_best_city_income(nrLines, list,&bestCityIncome);
      break;
      case 6:
        group_five_best_income(nrLines, list, &bestProducts);
      break;
      case 0:
      break;
    }
  }while(option !=0);
  
  return 0;
}
