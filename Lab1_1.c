#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Produs{
  int cod;
  char nume[50];
  float pret;
  int cantitate;
};

int count_lines(FILE *f) {
  char ch;
  int lines = 0;
  
  while(!feof(f)){
    ch = fgetc(f);
    if(ch == '\n')
    {
      lines++;
    }
  }
    rewind(f);
    return lines;
}


int main(){

  FILE *f;
  int nrLines, option;
  char searchNume[50];
  int searchCod, searchCantitate;
  float searchPret;
  
  f = fopen( "produse.txt", "r" );
  nrLines = count_lines(f);

  struct Produs listaProduse[nrLines];

  for(int i = 0; i < nrLines; i++){
    fscanf(f, "%d %s %f %d", &listaProduse[i].cod, listaProduse[i].nume, &listaProduse[i].pret,
      &listaProduse[i].cantitate);
  }

  for(int i = 0; i < nrLines; i++){
    printf("%d %s %.2f %d\n", listaProduse[i].cod, listaProduse[i].nume, listaProduse[i].pret, 
            listaProduse[i].cantitate);
  }
  int found;
  do{
  printf("Dupa ce cautai produsul: \n");
  printf("1:Cod\n2:Pret\n3:Nume\n4:Cantitate\n0:Iesire\n");
  scanf("%d",&option);
  switch(option){
    case 1:
      found = 0;
      printf("Scrie codul produsului: ");
      scanf("%d", &searchCod);
      for(int i = 0; i < nrLines; i++){
        if(listaProduse[i].cod == searchCod){
         printf("Produsul se afla pe pozitia %d : %s %.2f %d\n",i+1,listaProduse[i].nume,         
              listaProduse[i].pret, listaProduse[i].cantitate);
          found = 1;
        }
      }
      if(found == 0){
        printf("Nu am gasit produsul\n");
      }
    break;
    case 2:
      found = 0;
      printf("Scrieti pretul produsului: ");
      scanf("%f", &searchPret);
      for(int i = 0; i < nrLines; i++){
        if(listaProduse[i].pret == searchPret){
          printf("Produsul se afla pe pozitia %d : %s %d %d\n",i+1,listaProduse[i].nume,         
              listaProduse[i].cod, listaProduse[i].cantitate);
          found = 1;
        }
      }
      if(found == 0){
        printf("Nu am gasit produsul\n");
      }
    break;
    case 3:
      found = 0;
      printf("Scrieti numele produsului: ");
      scanf("%s", searchNume);
      for(int i = 0; i < nrLines; i++){
        if(strcmp(searchNume, listaProduse[i].nume) == 0){
          printf("Produsul se afla pe pozitia %d : %f %d %d\n",i+1,listaProduse[i].pret,         
              listaProduse[i].cod, listaProduse[i].cantitate);
          found = 1;
        }

    }
      if(found == 0){
        printf("Nu am gasit produsul\n");
      }
    break;
    case 4:
      found = 0;
      printf("Scrieti cantitatea produsului: ");
      scanf("%d", &searchCantitate);
      for(int i = 0; i < nrLines; i++){
        if(listaProduse[i].cantitate == searchCantitate){
          printf("Produsul se afla pe pozitia %d : %s %d %f\n",i+1,listaProduse[i].nume,         
              listaProduse[i].cod, listaProduse[i].pret);
          found = 1;
        } 
      }
      if(found == 0){
        printf("Nu am gasit produsul\n");
      }
    break;
    case 0:
      break;
  }
  }while(option != 0);
    
  
    
  
  return 0;
}
