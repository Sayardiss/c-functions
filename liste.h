#ifndef _LISTE_H_
  #define _LISTE_H_

  #define TYPE int
  #define __PRINT_CELL

  #include <stdlib.h>
  #include <stdio.h>
  #include <stdarg.h>

  struct Cell{
    TYPE data;
    struct Cell *next;
  };

  typedef struct Cell cell;

  struct Liste{
    struct Cell *tete;
    struct Cell *queue;
  };

  void afficherCell(cell* C);

  typedef struct Liste liste;

  void initListe(liste *L);

  cell* initCell();

  cell* creerCell(TYPE data);

  void ajouterEltT(liste *L, TYPE data);

  void ajouterEltQ(liste *L, TYPE data);

  void afficherListe(liste *L, ...);

  int listeVide(liste const *L);

  TYPE delisterT(liste *L);

  TYPE delisterQ(liste *L);

#endif
