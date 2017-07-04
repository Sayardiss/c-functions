#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "tableau.h"
#include "in_out.h"
#include "time.h"

#define TAILLE_NOM 100

FILE* ouvrir_fichier(const char* nomDuFichier, const char* modeOuverture) /*Permet d'ouvrir un fichier et tester si l'ouverture/creation OK !*/
{
    FILE* fichier = NULL;  /*Pointeur qui contiendra le fichier*/
    fichier = fopen(nomDuFichier, "r"); /*Ouverture du fichier en lecture seule pour voir si il existe deja*/

    printf("MODE OUVERTURE : %s\n", modeOuverture);

    if(fichier == NULL) /*Si le fichier est inexistant*/
    {
        printf("Fichier inexistant... Creation du fichier en cours...\n");
        fichier = fopen(nomDuFichier, modeOuverture); /*Ouverture (+creation si mode OK) du fichier*/
        if (fichier != NULL)
        {
            printf("OK !\n");
        }
        else /*Le modeOuverture n'est pas suffisant pour creer le fichier*/
        {
            printf("Erreur lors de la creation du fichier !\nVerifiez les modes d'ouverture (est ce que [ %s ] est correcte ?\n"
                   "Peut-etre est-il necessaire que le fichier existe deja pour ce mode d'ouverture !\n", modeOuverture);
            perror("Erreur ");
            exit(EXIT_FAILURE);
        }
    }

    else /*Si le fichier existe deja*/
    {
      if (*modeOuverture == 'r')
      {
         printf("Fichier trouve, lecture possible\n");
      }
      else
      {
        printf("\n\nLe fichier existe deja, etes vous sur d'en creer un nouveau ? Cela supprimera le fichier existant !!! (O/N) : ");

        if (oui_non())
        {
            fclose(fichier);
            fichier = fopen(nomDuFichier, modeOuverture);
            if (fichier != NULL)
            {
                printf("Fichier ecrase et recree... OK.\n");
            }
            else
            {
                printf("Erreur lors de la creation du fichier\nVerifiez le mode d'ouverture (est ce que [ %s ] est correct) ?\n", modeOuverture);
                perror("Erreur ");
                exit(EXIT_FAILURE);
            }
        }
        else
        {
            printf("Sortie du programme de creation...\n");
            exit(EXIT_FAILURE);
        }
      }
    }

    return fichier;
}

void afficher (FILE* fichier, char **contenu)
{
  /*Permet d'afficher le contenu d'un fichier
  et retourne en prime le contenu sous forme de caracteres*/

    int taille = 9999;
    *contenu = (char*)creer_tab( taille ); /*transformation en tableau de caracteres*/



    char caractere_actuel = fgetc(fichier);
    int compteur_acco = 0, i_tab = 0;

    while (caractere_actuel != EOF)
    {
      if (caractere_actuel == '}') compteur_acco--;
      if (caractere_actuel == '{') compteur_acco++;

      if (compteur_acco == 0)
      {
         if (caractere_actuel != '}') /*Si l'on n'est pas sur une accolade fermante de fonction*/
         {
          //printf("%c", caractere_actuel);

             (*(contenu))[i_tab] = caractere_actuel;
             i_tab++;
         }
         else /*Si c'est une accolade fermante*/
         {
            //printf(";");
            (*(contenu))[i_tab] = ';';
            i_tab++;
         }
      }


      caractere_actuel = fgetc(fichier);

      if (i_tab > taille - 200)
      {
         agrandir_tab((int**)contenu, taille, 10000);
         taille = taille + 10000;
      }

    }
    (*(contenu))[i_tab] = '\0';
    printf("Le contenu du tableau vaut :\n\n%s", *contenu);
    //return contenu;
}

void nomCversH(const char* nom_fich_c, char ** nom_h)
{
  /*Modification du nom.c en nom.h*/
  int i = 0;
  *nom_h = (char*)calloc(TAILLE_NOM, sizeof(char));
  while ( (i<TAILLE_NOM) && nom_fich_c[i] != '\0' ) /*on cherche la position du .c*/
  {
     i++;
  }
  //i pointe maintenant vers le dernier caractere (\0)

  if (nom_fich_c[i] == '\0' && nom_fich_c[i-1] == 'c' && nom_fich_c[i-2] == '.') /*Si fichier de la forme ****.c */
  {
     /*On copie le contenu de nom_fich_c dans nom_fich_h*/

     int j;
     for (j = 0; j < (TAILLE_NOM - 1) && j <= i; j++)
     {
        (*nom_h)[j] = nom_fich_c[j];
     }
     (*nom_h)[i] = '\0';
     (*nom_h)[i-1] = 'h';
     printf("\nNom du fichier .h : %s\n", *nom_h);
  }
  else
  {
     printf("\nErreur : nom de fichier source (*.c) incorrect, merci de vérifier\n");
     exit(2);
  }
  /*Fin modification .c -> .h*/
}

void nomConstDef(const char *nom_h, char **constDef)
{
  (*constDef)[0] = '_';
  int i = 0;
  while((nom_h[i] != '\0') && i<(TAILLE_NOM + 2))
  {
    if (nom_h[i] >= 'a' && nom_h[i] <= 'z')
    {
      (*constDef)[i+1] = nom_h[i] - ('a' - 'A'); //decalage du code ASCII pour le mettre en majuscule
    }
    else
    {
      if (nom_h[i] >= 'A' && nom_h[i] <= 'Z')
        (*constDef)[i+1] = nom_h[i];
      else
        (*constDef)[i+1] = '_';
    }
    i++;
  }
  (*constDef)[i+1] = '_';
  (*constDef)[i+2] = '\0';
  printf("DEFINE : %s", *constDef);
}


void ecriture_str_fichier(FILE *fichier_h, const char * contenu, const char *constDef)
{
   printf("\nEcriture dans le fichier en cours...");

   fputs( "#ifndef ", fichier_h);
   fputs( constDef, fichier_h);
   fputs( "\n#define ", fichier_h);
   fputs( constDef, fichier_h);
   fputs( "\n\n\n\n", fichier_h);

   if(fputs(contenu, fichier_h) != EOF)
   {
      printf("\nOK !");
   }
   else
   {
      printf("Erreur lors de l'écriture");
   }

   fputs("\n\n\n\n#endif", fichier_h);
}

int sauvegarder_fichier (const char* nom_h) /*copie un fichier en ajouter dd-mm-yy-hh:mm:ss~ a la fin*/
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

}

int main()
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
    {
      printf("Erreur lors de la sauvegarde du fichier\n");
      perror("Erreur ");
      exit(EXIT_FAILURE);
    }
    else
    {
      remove(nom_h);
    }

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
}
