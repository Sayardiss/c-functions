#ifndef _TABLEAU_H_
#define _TABLEAU_H_



#include <stdio.h>
#include <stdlib.h>
#include "tableau.h"
#include "in_out.h"


void affiche_tab(const int * tab, const int taille);

int* creer_tab(const int taille);

void init_tab(int * tab, const int taille);

void copie_tab(int ** old_tab, const int taille_av, const int taille_ap);

void agrandir_tab(int ** old_tab, const int taille_av, int ajout);




#endif
