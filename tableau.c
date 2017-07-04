#include <stdio.h>
#include <stdlib.h>
#include "tableau.h"
#include "in_out.h"


void affiche_tab(const int * tab, const int taille){ /*Permet d'afficher un tableau 1D d'entiers*/
   int i;
   printf("[");
   for (i=0; i < taille -1; i++){
      printf(" %i ,", *(tab + i));
   }
   printf(" %i ]\n", *(tab + taille - 1));
}

int* creer_tab(const int taille){  /*Permet de creer et de verifier un tableau d'entier, avec la taille*/
   int * tab = NULL;
   tab = (int*)calloc(taille, sizeof(int));
   if (tab == NULL){
      printf("Erreur lors de la creation du tableau");
      exit(0);
   }
   else
   {
     return tab;
   }
}

void init_tab(int * tab, const int taille){  /*Initialiser les valeurs du tableau d'entier*/
   int i;
   for (i = 0; i<taille; i++){
      printf("Valeur case %i : ", i);
      scanf("%d", tab + i);
   }
}

void copie_tab(int ** old_tab, const int taille_av, const int taille_ap){
/*Copie le contenu d'un tableau dans un nouveau
  ATTENTION : cette fonction change l'adresse du tableau, ne pas l'avoir stocke dans une autre var !*/
   int i;
   int * new_tab = NULL;
   new_tab = creer_tab(taille_ap);

   if (taille_av >= taille_ap) /*Nouveau tableau plus petit que l'ancien*/
   {
      for (i = 0; i < taille_ap; i++)
      {
         *(new_tab + i) = *(*(old_tab) + i);
      }
   }
   else /*Nouveau tableau + grand*/
   {
      for (i = 0; i < taille_ap; i++)
      {
         *(new_tab + i) = *(*(old_tab) + i);
      }
      printf("Il y a les %i dernières cases du tableau qui ne sont pas remplies. Les remplir ? y/n", taille_ap - taille_av);
      if (oui_non())
      {
         init_tab(new_tab + taille_av, taille_ap - taille_av);
      }
   }
   free(*old_tab); /*Liberer l'ancien tableau*/
   *(old_tab) = new_tab; /*On redirige l'ancien tableau vers le nouveau*/
}

void agrandir_tab(int ** old_tab, const int taille_av, int ajout){
/*Agrandie un tableau de "ajout" cases
Change l'adresse du tableau !*/
   if (ajout < 0)
   {
      printf("\nErreur : ajout négatif impossible, correction !\n");
      ajout = -ajout;
   }
   int i;
   int * new_tab = NULL;
   new_tab = creer_tab(taille_av + ajout);

   for (i = 0; i < taille_av; i++)
   {
      *(new_tab + i) = *(*(old_tab) + i);
   }
/*Les autres cases sont déjà à 0 grace a l'initialisation !*/
   free(*old_tab); /*Liberer l'ancien tableau*/
   *(old_tab) = new_tab; /*On redirige l'ancien tableau vers le nouveau*/
}

unsigned long long int* cribleErato(unsigned long long int N){ //retourne le tableau contenant les nombres premiers jusqu'à N
  unsigned long long int i,j;
  unsigned long long int *primes;
  unsigned long long int z = 0, a = 0;
  N++;

  primes = calloc(N, sizeof(unsigned long long int));

  for (i=2;i<N;i++)
      primes[i]=1;

  for (i=2;i*i<N;i++)
      if (primes[i])
          for (j=i;i*j<N;j++){
              primes[i*j]=0;
          }

  for (i=2;i<N;i++)
      if (primes[i])
        z++;
  unsigned long long int *premiers = calloc(z, sizeof(unsigned long long int));

  for (i=2; i < N; i++) //copie des nombres premiers dans un tableau
      if (primes[i]){
        premiers[a] = i;
        a++;
      }

  //for (i = 0; i < z; i++)
  //  printf("%llu\n", premiers[i]);

  return premiers;
}

int estPremier(const long int n){
  if (n <= 1){
    return 0;
  }
  else if (n <= 3){
    return 1;
  }
  else if ( !(n%2) || !(n%3) ){
    return 0;
  }
  unsigned long int i = 5;
  while (i*i <= n)
  {
    if ( !(n%i) || !(n%(i+2)))
      return 0;
    i += 6;
  }
  return 1;
}
