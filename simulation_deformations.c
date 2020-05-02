#include "rapport_deformations.h"
#include <stdio.h>
#include <stdlib.h>
#define LONGUEUR_CABLE 1000000 /* en m */
#define NOMBRE_DEFORMATIONS 100000 /* en nombre de déformations */




int main()
{
    /* paramètres */
    int nombre_positions = LONGUEUR_CABLE/PRECISION;
    int nombre_deformations = NOMBRE_DEFORMATIONS;
    Simulation simulation = UNIFORME;
    srand( time(NULL));
    int max;
    int taillepaquet = 1000;
    int temps_ecoule; /* pour chronométrer */
    printf("Simulation de %i deformations sur %i positions, configuration "
        "%i... ", nombre_deformations, nombre_positions, simulation);
    redemarrer_chronometre();
    Position* paquet = simuler_deformations(nombre_positions,
        nombre_deformations, simulation);
    printf("terminee.\n");


    const char* nom_fichier = "simulation_deformations.dat";
    printf("Ecriture du paquet de deformations dans %s... ", nom_fichier);
    int i;
    FILE* file = fopen(nom_fichier, "w");
    for (i = 0; i < nombre_deformations; i++){
        fprintf(file, "%i ", paquet[i]);
    }
    fclose(file);
    printf("terminee.\n");

    temps_ecoule = relever_chronometre_ms();
    printf("Temps ecoule : %i ms.\n", temps_ecoule);

    int j;

    max= max_deform(paquet, taillepaquet);

    for(j=0;j<=taillepaquet;j++){
        printf("%i\n",paquet[j]);
    }

    fct_tritableau(paquet,taillepaquet);

    printf("\n");
    printf("\n");

    for(j=0;j<=taillepaquet;j++){
        printf("%i\n",paquet[j]);
    }

    int db[max];

    printf("\n\n");

    compte_doublon(paquet,taillepaquet,max,db);

    for(j=0;j<=max;j++){
        if(db[j]!=0)
        {
            printf("db n %i = %i\n", j, db[j]);
        }
    }

    detruire_deformations(paquet);

    return 0;
}
