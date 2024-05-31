#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct Document {
  int id;
  char name[50];
  int total_rows;
  int remaining_rows;
  struct Document *next;
};

struct Printer {
  int id;
  int print_time_per_row;
  struct Document *current_document;
  struct Printer *next;
};

enum MenuOption {
  PRINTARE_IMPRIMATE = 1,
  PRINTARE_DOCUMENTE,
  NEW_DOCUMENT,
  DISTRI_DOCUMENTS,
  IESIRE
};

// Pentru timpul de tiparire va fi un timp de la 1 la 10 secunde
void initial_random_printers(struct Printer **queue, int numPrinters) {
  srand(time(NULL));

  for (int i = 0; i < numPrinters; i++) {
    struct Printer *printer = (struct Printer *)malloc(sizeof(struct Printer));
    printer->id = i + 1;
    printer->print_time_per_row = rand() % 10 + 1;
    printer->current_document = NULL;
    printer->next = NULL;

    if (*queue == NULL) {
      *queue = printer;
    } else {
      struct Printer *temp = *queue;
      while (temp->next != NULL) {
        temp = temp->next;
      }
      temp->next = printer;
    }
  }
}
void printPrinters(struct Printer *head) {
  printf("Lista de imprimante:\n");
  printf("---------------------\n");
  struct Printer *current = head;
  while (current != NULL) {
    printf("ID: %d\n", current->id);
    printf("Timp de tiparire per rand: %d\n", current->print_time_per_row);
    printf("\n");
    current = current->next;
  }
}

// Pentru numarul de randuri vor fi de la 1 la 100
void initial_random_documets(struct Document **queue, int num_documents) {
  for (int i = 1; i <= num_documents; i++) {
    struct Document *doc = (struct Document *)malloc(sizeof(struct Document));
    doc->id = i;
    sprintf(doc->name, "Document%d", i);
    doc->total_rows = rand() % 100 + 1;
    doc->remaining_rows = doc->total_rows;
    doc->next = NULL;

    if (*queue == NULL) {
      *queue = doc;
    } else {
      struct Document *temp = *queue;
      while (temp->next != NULL) {
        temp = temp->next;
      }
      temp->next = doc;
    }
  }
}

void add_new_document(struct Document **queue) {
  struct Document *doc = (struct Document *)malloc(sizeof(struct Document));

  struct Document *last_document = *queue;
  if (last_document != NULL) {
    while (last_document->next != NULL) {
      last_document = last_document->next;
    }
  }

  if (last_document == NULL) {
    doc->id = 1;
  } else {
    doc->id = last_document->id + 1;
  }

  printf("Introduceți numele documentului: ");
  scanf("%s", doc->name);

  printf("Introduceți numărul total de rânduri: ");
  scanf("%d", &doc->total_rows);
  doc->remaining_rows = doc->total_rows;

  doc->next = NULL;

  if (*queue == NULL) {
    *queue = doc;
  } else {
    struct Document *temp = *queue;
    while (temp->next != NULL) {
      temp = temp->next;
    }
    temp->next = doc;
  }
}
void printDocuments(struct Document *head) {
  printf("Lista de Documente:\n");
  printf("---------------------\n");
  struct Document *current = head;
  while (current != NULL) {
    printf("ID: %d\n", current->id);
    printf("Numele: %s\n", current->name);
    printf("Numarul de randuri: %d\n", current->total_rows);
    printf("Numarul de randuri ramase de tipari: %d\n",
           current->remaining_rows);
    printf("\n");
    current = current->next;
  }
}

void distribute_documents(struct Document *documents,
                          struct Printer *printers) {
  struct Document *current_doc = documents;

  while (current_doc != NULL) {
    struct Printer *selected_printer = NULL;
    int min_print_time = 999;

    struct Printer *current_printer = printers;
    while (current_printer != NULL) {
      int estimated_print_time =
          current_doc->total_rows * current_printer->print_time_per_row;

      if (estimated_print_time < min_print_time) {
        min_print_time = estimated_print_time;
        selected_printer = current_printer;
      }

      current_printer = current_printer->next;
    }

    if (selected_printer != NULL) {
      current_doc->remaining_rows = 0;
      selected_printer->current_document = current_doc;

      printf("Imprimanta ID: %d\n", selected_printer->id);
      printf("Document printat:\n");
      printf("Nume document: %s\n", current_doc->name);
      printf("Numarul de randuri ramase de tiparit: %d\n",
             current_doc->remaining_rows);
      printf("\n");
    }

    current_doc = current_doc->next;
  }
}

int main() {
  int numPrinters, num_documents;
  struct Printer *printer_list = NULL;
  struct Document *document_list = NULL;

  printf("Introduceti numarul de imprimante: ");
  scanf("%d", &numPrinters);
  printf("Introduceti numarul de documente initiale: ");
  scanf("%d", &num_documents);

  initial_random_printers(&printer_list, numPrinters);
  initial_random_documets(&document_list, num_documents);

  int option;
  do {
    printf("\nMeniu:\n");
    printf("%d. Afisare lista de imprimante\n", PRINTARE_IMPRIMATE);
    printf("%d. Afisare lista de documente\n", PRINTARE_DOCUMENTE);
    printf("%d. Adaugarea unui document nou\n", NEW_DOCUMENT);
    printf("%d. Incepe Distribuirea documentelor\n", DISTRI_DOCUMENTS);
    printf("%d.Iesire\n", IESIRE);

    scanf("%d", &option);
    switch ((enum MenuOption)option) {
    case PRINTARE_IMPRIMATE:
      printPrinters(printer_list);
      break;
    case PRINTARE_DOCUMENTE:
      printDocuments(document_list);
      break;
    case NEW_DOCUMENT:
      add_new_document(&document_list);
      break;
    case DISTRI_DOCUMENTS:
      distribute_documents(document_list, printer_list);
      break;
    case IESIRE:
      break;
    default:
      printf("Optiune invalida! Va rugam sa alegeti din nou.\n");
    }
  } while (option != 0);
  return 0;
}
