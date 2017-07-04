#ifndef _CREER_HEADER_H_
#define _CREER_HEADER_H_



#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "tableau.h"
#include "in_out.h"
#include "time.h"

#define TAILLE_NOM 100

FILE* ouvrir_fichier(const char* nomDuFichier, const char* modeOuverture) /*Permet d'ouvrir un fichier et tester si l'ouverture/creation OK !*/
;

void afficher (FILE* fichier, char **contenu)
;
    (*(contenu))[i_tab] = '\0';
    printf("Le contenu du tableau vaut :\n\n%s", *contenu);
    //return contenu;
{
  /*Modification du nom.c en nom.h*/
  int i = 0;
  *nom_h = (char*)calloc(TAILLE_NOM, sizeof(char));
  while ( (i<TAILLE_NOM) && nom_fich_c[i] != '\0' ) /*on cherche la position du .c*/
  ;
  //i pointe maintenant vers le dernier caractere (\0)

  if (nom_fich_c[i] == '\0' && nom_fich_c[i-1] == 'c' && nom_fich_c[i-2] == '.') /*Si fichier de la forme ****.c */
  ;
  else
  ;
  /*Fin modification .c -> .h*/
{
  (*constDef)[0] = '_';
  int i = 0;
  while((nom_h[i] != '\0') && i<(TAILLE_NOM + 2))
  ;
  (*constDef)[i+1] = '_';
  (*constDef)[i+2] = '\0';
  printf("DEFINE : %s", *constDef);
{
   printf("\nEcriture dans le fichier en cours...");

   fputs( "#ifndef ", fichier_h);
   fputs( constDef, fichier_h);
   fputs( "\n#define ", fichier_h);
   fputs( constDef, fichier_h);
   fputs( "\n\n\n\n", fichier_h);

   if(fputs(contenu, fichier_h) != EOF)
   ;
   else
   ;

   fputs("\n\n\n\n#endif", fichier_h);
{
  char nomSave[TAILLE_NOM];

  sprintf(nomSave, "%s.%d-%d-%d.%dh%dm%ds~%c", nom_h, getTime('D'), getTime('M'), getTime('Y'), getTime('h'), getTime('m'), getTime('s'), '\0');
  nomSave[TAILLE_NOM - 1] = '\0'; //par securite
  printf("\n%s\n", nomSave);

  FILE *old = NULL, *new = NULL;
  old = ouvrir_fichier(nom_h, "w");
  new = ouvrir_fichier(nomSave, "w");

  char c;
  while((c = fgetc(old)) != EOF)
    fputc(c, new);
  printf("Sauvegarde OK; nom de la sauvegarde : %s\n", nomSave);
  fclose(old);
  fclose(new);
  return 0;

{
    char nom_fich[TAILLE_NOM]; //contient le nom du fichier
    //char mode[3]; //contient le mode d'ouverture (2 lettres)
    printf("Entrer le nom du fichier a ouvrir : ");
    saisie_texte(nom_fich, TAILLE_NOM);
    //printf("Mode d'ouverture ? : ");
    //saisie_texte(mode, 3);

    char *nom_h;
    nomCversH(nom_fich, &nom_h);


    FILE *fichier = NULL;
    fichier = ouvrir_fichier(nom_fich, "r");

    if(sauvegarder_fichier(nom_h) != 0)
    ;
    else
    ;

    char* contenu = NULL;
    afficher(fichier, &contenu); /*Contient la chaine de caractère*/

    FILE *fich_h = NULL;
    fich_h = ouvrir_fichier(nom_h, "w");

    //char constDef[TAILLE_NOM+2]; // creer_header.h devient _CREER_HEADER_H_
    char *constDef = (char*)creer_tab(TAILLE_NOM + 2);


    nomConstDef(nom_h, &constDef);

    ecriture_str_fichier(fich_h, contenu, constDef);




    fclose(fichier);

    return 0;




#endif