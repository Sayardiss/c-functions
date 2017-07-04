#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tableau.h"
#include <math.h>


/* C * u + M * v = 1 */

typedef struct
{
    int x;
    int y;
} cle;


void init_cle(int P, int Q, cle *publique, cle *prive){
    int M = (Q-1)*(P-1);
    int N = P*Q;

    //printf("\nDonner un C, tel qu'il soit premier avec M (%d) : ", M);
    int C = 7;
    //scanf("%d", &C);

    int u = bezout(C, M);


    publique->x = N;
    publique->y = C;

    prive->x = u;
    prive->y = N;
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
  long int i = 5;
  while (i*i <= n)
  {
    if ( !(n%i) || !(n%(i+2)))
      return 0;
    i += 6;
  }
  return 1;
}

long long int power(int a, int b) /*Retourne a^b*/
{
    int i;
    long long int sum = 1;
    for (i = 0; i < b; i++){
        sum = sum * a;
    }
    return sum;
}

int chiffrer_c(char lettre, int C, int N) /*permet de chiffrer un caractère, par la formule (ASCII)^C mod(N) */
{
    int ascii = lettre;
    return (int)(power(ascii, C)%N);
}



int bezout(int C, int M){ /*Permet de trouver les coefficients de Bezout, connaissant C et M*/
    int u = 2;
    int v;
    int trouve = 0;
    while ((u <= M) && (trouve == 0)){
        for(v = -M; (v <= M) && (trouve == 0); v++){
            if ((C * u + M * v) == 1){
                //printf("\n-------> U = %d <--------\n\n", u);
                printf("C = %d, U = %d, M = %d, V = %d", C, u, M, v);
                //trouve = 1;
                return u;
            }
        }
    u++;
    }
    return 0; /*pas trouve*/
}

void crypter_mess(char * mess, cle publique, cle prive)
{
   int * crypted = creer_tab( strlen(mess) ); /*tableau d'entier de taille du message*/
   int i=0;

   while(mess[i] != '\0')
   {
      crypted[i] = chiffrer_c( mess[i] , publique.y, publique.x);
      i++;
   }

   affiche_tab(crypted, strlen(mess));
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

void afficherChiffrageC(char car, cle pub){
  printf("\nLa valeur de '%c' vaut : %d\n", car, car);
  printf("%d a la puissance %d = %lld", car, pub.y, power(car, pub.y));

  printf("\nLe chiffrage de %c vaut : %d", car, chiffrer_c(car, pub.y, pub.x));
}



int main()
{
//printf("Entrer deux nombres entiers : ");
/* A DECOMMENTER POUR DEMANDER LES VALEURS   scanf("%d %d", &P, &Q); */

    int P = 97, Q=53;
    cribleErato(29);
    return 0;

    cle pub, priv; /*declaration des cles publiques et prives*/
    init_cle(P,Q, &pub, &priv);


    printf("\n\nCle publique : (N = %d, C = %d)\n", pub.x, pub.y);
    printf("Cle privee : (U = %d, N = %d)\n", priv.x, priv.y);




    char texte[100];

    scanf("%s", texte);
    getchar();
    printf("\n%s", texte);

   crypter_mess(texte, pub, priv);




    return 0;
}
