#include "random.h"


int rand_a_b(int a, int b){ //Retourne un entier rand compris entre a et b (exlus)
  static i = 1;
  if(i){
    srand(time(NULL));
    i = 0;
  }
  return a < b ?  (rand()%(b-a) +a) :  (rand()%(a-b) +b);
}

double frand_a_b(double a, double b){//Retourne un float rand compris entre a et b
  static i = 1;
  if(i){
    srand(time(NULL));
    i = 0;
  }
  return a < b ? ( rand()/(double)RAND_MAX ) * (b-a) + a : ( rand()/(double)RAND_MAX ) * (a-b) + b;
}

int randBin(){
  static i = 1;
  if(i){
    srand(time(NULL));
    i = 0;
  }
  return rand()%2;
}

int* init_sans_doublons(int a, int b){
	int taille = b-a;
	int* resultat=calloc( taille, sizeof (int));
  if (resultat == NULL) { printf("Erreur init. tab. aléa"); exit(1);}

	int i=0;
	// On remplit le tableau de manière à ce qu'il soit trié
	for(i = 0; i< taille; i++){
		resultat[i]=i+a;
	}
	return resultat;
}

void melanger(int* tableau, int taille){
	int i=0;
	int nombre_tire=0;
	int temp=0;

	for(i = 0; i< taille;i++){
		nombre_tire=rand_a_b(0,taille);
		// On échange les contenus des cases i et nombre_tire
		temp = tableau[i];
		tableau[i] = tableau[nombre_tire];
		tableau[nombre_tire]=temp;
	}
}


int *tabRand(int a, int b, const int size){
  if (a > b){
    int tmp = a;
    a = b;
    b = tmp;
  }

  if( size > (b-a)) //si taille trop grande pour l'intervalle
  {
    printf("\nTaille trop petite pour l'intervalle. Taille gardée, mais intervalle pris entre [%i,%i[\n", a, a+size);
    b = a+size;
  }

  int *tab = init_sans_doublons(a, b);
  melanger( tab, b-a);
  int i;
  for(i = 0; i < size; i++){
    printf("%d ", tab[i]);
  }
  printf("\n");
  return tab;
}


/*int main(void){
	long long unsigned int i = 0;
	int nombre_aleatoire = 0; // initialisation de rand
  srand(time(NULL)); // initialisation de rand
  long long unsigned int nb0;
	for(i=0; i<50; i++){
		nombre_aleatoire = rand_a_b(0,1);
    if(nombre_aleatoire)
      nb0++;
    printf("%i\n", rand_a_b(0,5));
	}
  tabRand(-20, -4, 8);

  //printf("%llu",nb0);
	return 0;
}*/
