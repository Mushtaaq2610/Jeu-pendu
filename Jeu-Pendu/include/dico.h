/*
dico.h
------

Contient les prototypes des fonctions de dico.c
*/


#ifndef DEF_DICO
#define DEF_DICO


int piocherMot(char *motPioche);
int nombreAleatoire(int nombreMax);

int gagne(int lettreTrouvee[], long tailleMot);
int rechercheLettre(char lettre, char motSecret[], int lettreTrouvee[]);
char lireCaractere();

char hint(char z);

#endif

