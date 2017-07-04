#include "liste.h"

void afficherCell(cell* C){
  switch((int)sizeof(C->data))
  {
    case ((int)sizeof(int)):
      printf("%i", C->data);
    break;
    case ((int)sizeof(double)):
      printf("%f", (double)C->data);
    break;
    default:
      printf("Format non générique; merci d'utiliser le define correspondant à votre format.");
      __PRINT_CELL
  }
}

void initListe(liste *L){
  L->tete = NULL;  L->queue = NULL;
}

cell* initCell(){
  cell *cellule = NULL;
  if ( (cellule = calloc(1, sizeof(TYPE) + sizeof(*cellule) ) ) == NULL)
  {
    fprintf(stderr, "Erreur init. cell");
    exit(1);
  }
  cellule->next = NULL;
  return cellule;
}

cell* creerCell(TYPE data){
  cell *cellule = initCell();
  cellule->data = data;
  cellule->next = NULL;
  return cellule;
}

void ajouterEltT(liste *L, TYPE data){
  cell *cellule = creerCell(data);
  if (L->tete == NULL)
    L->queue = cellule;
  cellule->next = L->tete;
  L->tete = cellule;
}

void ajouterEltQ(liste *L, TYPE data){
  cell *cellule = creerCell(data);
  L->queue->next = cellule;
  L->queue = cellule;
}

void afficherListe(liste *L, ...){
  if(L == NULL) return;

  va_list choix;
  va_start(choix, L);
  int ch = va_arg(choix,int);
  va_end(choix);


  cell *C = L->tete;
  switch(ch)
  {
    case 0:
    case -1: //si pas d'argument, par defaut c'est lui
      while ( C != NULL)
      {
        afficherCell(C);
        printf(" --> ");
        C = C->next;
      }
      printf("[]\n");
    break;
    case 1:
      while ( C != NULL)
      {
        printf("+-- ");
        afficherCell(C);
        printf("\n|\n");
        C = C->next;
      }
      printf("+--[]\n");
    break;
    default:
      fprintf(stderr, "Unreconized format");
  }
}

int listeVide(liste const *L){
  return (L->tete == NULL);
}

TYPE delisterT(liste *L){
  if ( !listeVide(L) ){
    cell *C = L->tete;
    TYPE data = C->data;
    if (L->queue == C)
      L->queue = NULL;
    L->tete = L->tete->next;
    free(C);
    return data;
  }
  else{
    fprintf(stderr, "Erreur : Liste vide");
    return;
  }
}

TYPE delisterQ(liste *L){
  if ( !listeVide(L) ){
    cell *C = L->queue;
    TYPE data = C->data;
    if (L->tete == C){
      L->tete = NULL;
      L->queue = NULL;
    }

    cell *newQ = L->tete;
    while( newQ != NULL){
      if ( newQ->next == L->queue )
      {
        printf("Trouve\n");
        break;
      }
      newQ = newQ->next;
    }

    L->queue = newQ;
    L->queue->next = NULL;
    free(C);
    return data;
  }
  else {
    fprintf(stderr, "Erreur : Liste vide");
    return;
  }
}

unsigned int tailleListe(liste const *L){
  if (L == NULL)
    return 0;
  unsigned int n = 0;
  cell *C;
  for (C = L->tete ; C != NULL; C = C->next)
    n++;
  return n;
}

TYPE* listeToTab(liste const *L){





}

void main(){
  liste L;
  initListe(&L);
  tailleListe(&L);

  ajouterEltT(&L, 45);
  ajouterEltT(&L, 22);
  ajouterEltQ(&L, 33);
  ajouterEltQ(&L, 34);
  ajouterEltQ(&L, 35);
  ajouterEltQ(&L, 36);

  ajouterEltT(&L, 48);
  ajouterEltT(&L, 29);



  afficherListe(&L);
  tailleListe(&L);
  delisterT(&L);
  TYPE a = delisterQ(&L);
  afficherListe(&L);
  tailleListe(&L);
  printf("Queue de liste : %i\n", L.queue->data);
  printf("deliste : %i\n", a);
}
