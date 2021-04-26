/*
main.c
------

Fonctions principales de gestion du jeu
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "../include/dico.h"


int main(int argc, char* argv[])
{
    char lettre = 0; // Stocke la lettre proposée par l'utilisateur (retour du scanf)
    char motSecret[100] = {0}; // Ce sera le mot à trouver
    int *lettreTrouvee = NULL; // Un tableau de booléens. Chaque case correspond à une lettre du mot secret. 0 = lettre non trouvée, 1 = lettre trouvée
    long coupsRestants = 8; // Compteur de coups restants (0 = mort)
    long i = 0; // Une petite variable pour parcourir les tableaux
    long tailleMot = 0;
    char lettre_hint = 1;
    char z;
    int x;


    

    printf("Bienvenue dans le Pendu !\n\n");
    printf("Regles Du jeux\n\n");
    

    if (!piocherMot(motSecret))
        exit(0);

    tailleMot = strlen(motSecret);

    lettreTrouvee = malloc(tailleMot * sizeof(int)); // On alloue dynamiquement le tableau lettreTrouvee (dont on ne connaissait pas la taille au départ)
    if (lettreTrouvee == NULL)
        exit(0);

    for (i = 0 ; i < tailleMot ; i++)
        lettreTrouvee[i] = 0;

    // On continue à jouer tant qu'il reste au moins un coup à jouer ou qu'on
    // n'a pas gagné
    while (coupsRestants > 0 && !gagne(lettreTrouvee, tailleMot))
    {
        
        printf("\n\nIl vous reste %ld coups a jouer", coupsRestants);
        printf("\nQuel est le mot secret ? ");


        /* On affiche le mot secret en masquant les lettres non trouvées
        Exemple : A*ON */

        for (i=0 ; i < tailleMot ; i++)
        {

            if (lettreTrouvee[i]) // Si on a trouvé la lettre n°i
                printf("%c", motSecret[i]); // On l'affiche

            
                
            else
                printf("_"); // Sinon, on affiche une étoile pour les lettres non trouvées
        }

            char indice[50];

            

                                printf("\nVoudriez vous avoir un indice [y/n] : ");
                                scanf("%s",indice);

                                if(strcmp(indice,"y") == 0)
                                {
                                    z = motSecret[rand()% tailleMot];
                                    //printf("Hint : %c \n", z);
                                    //on revoie la valeur de z a lettre
                                    lettre = hint(z);
                                   // printf("%c\n", lettre);

                                }

                                else if(strcmp(indice,"n") == 0)
                                {
                                        do 
                                        {
                                            printf("Entrer uniquement des alphabets : ");
                                            lettre = lireCaractere();
                                        }while((isalpha(lettre) == 0));
                                    
                                }


        // Si ce n'était PAS la bonne lettre
        if (!rechercheLettre(lettre, motSecret, lettreTrouvee))
        {
            coupsRestants--; // On enlève un coup au joueur
        }

        
    }


    if (gagne(lettreTrouvee, tailleMot))
        printf("\n\nGagner ! Le mot secret etait bien : %s", motSecret);
    else
        printf("\n\nPerdu ! Le mot secret etait : %s", motSecret);

    free(lettreTrouvee); // On libère la mémoire allouée manuellement (par malloc)
    
    printf("\n");

        return 0;
}
