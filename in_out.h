#ifndef _IN_OUT_H_
#define _IN_OUT_H_



  #include <stdio.h>
  #include <string.h>
  #include <stdlib.h>
  #include <limits.h>

  int oui_non();

  void vider_buffer();

  char saisie_char();

  int saisie_texte(char * chaine, const int taille);

  int text_to_int(char * chaine);

  long int text_to_long(char * chaine);

  long long int text_to_llong(char * chaine);

  double text_to_double(char * chaine);

  int saisie_int();

  int saisie_long();

  int saisie_llong();

  double saisie_double();

#endif
