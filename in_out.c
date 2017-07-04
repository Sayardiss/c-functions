#include "in_out.h"

int oui_non(){ /*Permet de remplir un oui ou non*/
   char c = saisie_char();
   return (c == 'y' || c == 'o' || c == 'O' || c == 'Y');
}

void vider_buffer(){ /*Permet de vider le buffer clavier jusqu'au '\n' ou jusqu'à la fin du buffer*/
   int c = getchar(); while (c != '\n' && c != EOF) {c = getchar();}  }

char saisie_char(){
  char tab[2] = {0};
  if( !saisie_texte(tab, 2) ){
    return tab[0];
  }
  else{ fprintf(stderr, "Erreur saisie caractere"); return -1;}
}

int saisie_texte(char * chaine, const int taille){
/* Permet la saisie securisee d'un texte de taille <taille - 1> (pour le \0)
   Chaine est le tableau de caractère, et taille comprend '\0'
   Retourne 0 si OK, retourne 1 sinon */

   //vider_buffer(); /*Vider ce qu'il y avait avant CAUSE UN BUG OU IL FAUT ENTRER AVANT DE TAPER TXT*/
   char *posEntree = NULL; /*Pointeur pour chercher si il y a un '\n'*/

   if ( fgets(chaine, taille, stdin) != NULL) /*Si l'insertion n'a pas echoué !*/
   {
      posEntree = strchr(chaine, '\n'); /*Chercher la position du '\n'*/
      if (posEntree != NULL) /*Si trouvé*/
         *posEntree = '\0'; /*On remplace le \n par un \0 pour terminer le message*/
      else
         vider_buffer(); /*On vide le surplus qui reste après fgets*/

      //printf("La chaine de caractère vaut : %s\n", chaine);
      return 0; /* OK */
   }
   else /*Il faut vider le buffer par securite*/
   {
      fprintf(stderr, "Erreur lors de la saisie du texte");
      vider_buffer();
      return -1;
   }
}

int text_to_int(char * chaine){
  long int i;
  if ( (i = strtol(chaine, NULL, 10) > INT_MAX)){
    fprintf(stderr, "text_to_int : entier trop long (overflow) : retourne INT_MAX\n");
    return INT_MAX;
  }
  else if (i < INT_MIN){
    fprintf(stderr, "text_to_int : entier trop long (underflow) : retourne INT_MIN\n");
    return INT_MIN;
  }
  return (int)i;
}

long int text_to_long(char * chaine){
  long long int i;
  if ( (i = strtoll(chaine, NULL, 10) > LONG_MAX)){
    fprintf(stderr, "text_to_long : entier trop long (overflow) : retourne LONG_MAX\n");
    return LONG_MAX;
  }
  else if (i < LONG_MIN){
    fprintf(stderr, "text_to_long : entier trop long (underflow) : retourne LONG_MIN\n");
    return LONG_MIN;
  }
  return (long int)i;
}

long long int text_to_llong(char * chaine){
  long long int i;
  if ( (i = strtoll(chaine, NULL, 10) == LLONG_MAX)){
    fprintf(stderr, "text_to_LLONG : entier trop long (overflow) : retourne LLONG_MAX\n");
    return LLONG_MAX;
  }
  else if (i == LLONG_MIN){
    fprintf(stderr, "text_to_LLONG : entier trop long (underflow) : retourne LLONG_MIN\n");
    return LLONG_MIN;
  }
  return i;
}

double text_to_double(char * chaine){
  char * virgule = strchr(chaine, ',');
  if (virgule != NULL)
    *virgule = '.';
  return strtod(chaine, NULL);
}

int saisie_int(){
  char s[100] = {0};
  saisie_texte(s, 100);
  return (text_to_int(s));
}

int saisie_long(){
  char s[100] = {0};
  saisie_texte(s, 100);
  return (text_to_long(s));
}

int saisie_llong(){
  char s[100] = {0};
  saisie_texte(s, 100);
  return (text_to_llong(s));
}

double saisie_double(){
  char s[100] = {0};
  saisie_texte(s, 100);
  return text_to_double(s);
}

/*int main(){
  char c;
  c = saisie_char();
  printf("\nc vaut : -%c-\n\n", c);

  c = saisie_char();
  printf("\nc vaut : -%c-\n\n", c);


  printf("\nX vaut : -%lf-\n\n", saisie_double());

  printf("Size of int : %lu", sizeof(int));

  return 0;
}*/
