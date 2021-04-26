/*
dico.c
------

Ces fonctions piochent au hasard un mot dans un fichier dictionnaire
pour le jeu du pendu
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#include "../include/dico.h"


int piocherMot(char *motPioche)
{
    FILE* dico = NULL; // Le pointeur de fichier qui va contenir notre fichier
    int nombreMots = 0, numMotChoisi = 0, i = 0;
    int caractereLu = 0;
    char ans[10];

    printf("Chosissez votre mode de difficulte [ facile(f), moyen(m), difficile(d) ] : "); 
    scanf("%s", ans);   


    if(strcmp(ans,"f") == 0){

        dico = fopen("../resource/dicofacile.txt", "r"); // On ouvre le dictionnaire en lecture seule
    }

    else if (strcmp(ans,"m") == 0) {
        dico = fopen("../resource/dicomoyen.txt", "r"); // On ouvre le dictionnaire en lecture seule 
    }

    else if (strcmp(ans,"d") == 0) {
        dico = fopen("../resource/dicodifficile.txt", "r"); // On ouvre le dictionnaire en lecture seule 
    }

    else {printf("Erreur\n");}



    // On vérifie si on a réussi à ouvrir le dictionnaire
    if (dico == NULL) // Si on n'a PAS réussi à ouvrir le fichier
    {
        printf("\nImpossible de charger le dictionnaire de mots");
        return 0; // On retourne 0 pour indiquer que la fonction a échoué
        // A la lecture du return, la fonction s'arrête immédiatement.
    }

    // On compte le nombre de mots dans le fichier (il suffit de compter les
    // entrées \n
    do
    {
        caractereLu = fgetc(dico);
        if (caractereLu == '\n')
            nombreMots++;
    } while(caractereLu != EOF);


    numMotChoisi = nombreAleatoire(nombreMots); // On pioche un mot au hasard
    // On recommence à lire le fichier depuis le début. On s'arrête lorsqu'on est arrivés au bon mot
    rewind(dico);
    while (numMotChoisi > 0)
    {
        caractereLu = fgetc(dico);
        if (caractereLu == '\n')
            numMotChoisi--;
    }

    /* Le curseur du fichier est positionné au bon endroit.
    On n'a plus qu'à faire un fgets qui lira la ligne */
    fgets(motPioche, 100, dico);

    // On vire l'\n à la fin
    motPioche[strlen(motPioche) - 1] = '\0';
    fclose(dico);

    return 1; // Tout s'est bien passé, on retourne 1
}

int nombreAleatoire(int nombreMax)
{
    srand(time(NULL));
    return (rand() % nombreMax);
}


char lireCaractere()
{
    char caractere = 0;

    while (getchar() != '\n') ;

    
    caractere = getchar(); // On lit le premier caractère
    caractere = toupper(caractere); // On met la lettre en majuscule si elle ne l'est pas déjà

    // On lit les autres caractères mémorisés un à un jusqu'à l'\n
    

    return caractere; // On retourne le premier caractère qu'on a lu
}



char hint(char z)
{
    char caractere = 0;

    caractere = z; // On lit le premier caractère
    caractere = toupper(caractere); // On met la lettre en majuscule si elle ne l'est pas déjà

    return caractere; // On retourne le premier caractère qu'on a lu
}

int gagne(int lettreTrouvee[], long tailleMot)
{
    long i = 0;
    int joueurGagne = 1;

    for (i = 0 ; i < tailleMot ; i++)
    {
        if (lettreTrouvee[i] == 0)
            joueurGagne = 0;
    }

    return joueurGagne;
}

int rechercheLettre(char lettre, char motSecret[], int lettreTrouvee[])
{
    long i = 0;
    int bonneLettre = 0;

    // On parcourt motSecret pour vérifier si la lettre proposée y est
    for (i = 0 ; motSecret[i] != '\0' ; i++)
    {
        if (lettre == motSecret[i]) // Si la lettre y est
        {
            bonneLettre = 1; // On mémorise que c'était une bonne lettre
            lettreTrouvee[i] = 1; // On met à 1 le case du tableau de booléens correspondant à la lettre actuelle
        }
    }

    return bonneLettre;
}

