#ifndef _RANDOM_H_
#define _RANDOM_H_

  #include <stdio.h>
  #include <stdlib.h>
  #include <time.h> //Ne pas oublier d'inclure le fichier time.h


  int rand_a_b(int a, int b); //Retourne un entier rand compris entre a et b (exlus)

  double frand_a_b(double a, double b);//Retourne un float rand compris entre a et b

  int randBin(); //genere 0 ou 1

  int* init_sans_doublons(int a, int b); //initialiser tableau (a = 3, b = 6) -> 3 4 5

  void melanger(int* tableau, int taille); //melanger un tableau en mode rand


  int *tabRand(int a, int b, const int size); //génere un tableau de taille Size d'entiers entre a et b

#endif
