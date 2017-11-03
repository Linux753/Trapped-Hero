#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../../include/structure.h"
#include "../../include/Generateur_chemin.h"
#include "../../include/Generateur_carte_alea.h"
int *calculOccupe(int hauteur , int largeur , int position , Carte *carte , Salle *salle){
    //printf("calculOccupe");
    int i=0 , compteur=0 , sauvegardePosition=position , continuer1 = 0 , continuer2 = 0 ;
    int *occupe = malloc(largeur*hauteur*sizeof(int));
    if(occupe==NULL){
            printf("Erreur d'allouage de mémoire");
            exit(1);
    }
    do{
        if(position+(salle->hauteur*carte->largeur)>(carte->largeur*carte->hauteur)-1){
            position=position-carte->largeur;
            continuer1=1;
        }else{
            continuer1=0;
        }
    }while(continuer1);
    do{
        if(position+(salle->hauteur*carte->largeur)+(salle->largeur-1)>(carte->largeur*carte->hauteur)-1){
            position=position-1;
            continuer2=1;
        }
        else{
            continuer2=0;
        }
    }while(continuer2);
    sauvegardePosition=position;
    for(position=position; position<sauvegardePosition+(carte->largeur*hauteur); position =position+carte->largeur){
        for(i=0;i<largeur; i++){
            if(position+i>(carte->largeur*carte->hauteur)){
                printf("ERREUR");
                exit(1);
            }
            occupe[compteur]= position+i;
            compteur++;
        }
    }
    return occupe;
}
Salle creerSalle(int position , int largeur , int hauteur , int numeroSalle , Carte *carte ){
    //printf("creerSalle");
    Salle salle;
    salle.position = position;
    salle.largeur = largeur;
    salle.hauteur = hauteur;
    salle.numeroSalle = numeroSalle;
    salle.occupeAvecMur = calculOccupe(salle.hauteur , salle.largeur, salle.position , carte  , &salle);
    salle.occupeSansMur = calculOccupe(salle.hauteur-2 , salle.largeur-2, salle.position+1+carte->largeur , carte,  &salle);
    return salle;
}

void detruireOccupeMur(Salle *salle){
    //printf("detruireOccupeMur");
    free(salle->occupeAvecMur);
    salle->occupeAvecMur=NULL;
    free(salle->occupeSansMur);
    salle->occupeSansMur=NULL;
}
void collision(Salle *salle , Carte *carte){
        //printf("collision");
        int i=0;
        for(i=0; i<salle->largeur*salle->hauteur; i++){
        if(carte->terrain[salle->occupeAvecMur[i]].type==MUR){
            if(i%salle->largeur==0){

            }
            else if(i<salle->largeur){
                salle->position=salle->position-(i+1);
                if(salle->occupeAvecMur!=NULL&&salle->occupeSansMur!=NULL){
                    detruireOccupeMur(salle);
                }
                salle->occupeAvecMur = calculOccupe(salle->hauteur , salle->largeur, salle->position , carte , salle);
                salle->occupeSansMur = calculOccupe(salle->hauteur-2 , salle->largeur-2, salle->position+1+carte->largeur , carte, salle);
            }
            else{
                salle->position=salle->position+(salle->largeur*(salle->hauteur-(((i/salle->largeur)+1))));
                if(salle->occupeAvecMur!=NULL&&salle->occupeSansMur!=NULL){
                    detruireOccupeMur(salle);
                }
                salle->occupeAvecMur = calculOccupe(salle->hauteur , salle->largeur, salle->position , carte , salle);
                salle->occupeSansMur = calculOccupe(salle->hauteur-2 , salle->largeur-2, salle->position+1+carte->largeur , carte , salle);
            }
        }
    }
}

void dessinerSalle(Salle *salle , Carte *carte){
    //printf("dessinerSalle");
    int i=0;
    collision(salle , carte);
    for(i=0; i<salle->largeur*salle->hauteur; i++){
        if(carte->terrain[salle->occupeAvecMur[i]].type==VIDE||carte->terrain[salle->occupeAvecMur[i]].type==MUR_SALLE){
            carte->terrain[salle->occupeAvecMur[i]].type=MUR_SALLE;
            carte->terrain[salle->occupeAvecMur[i]].numeroSalle = salle->numeroSalle;
        }
    }
    for(i=0; i<(salle->largeur-2)*(salle->hauteur-2); i++){
        if(carte->terrain[salle->occupeSansMur[i]].type!=MUR){
            carte->terrain[salle->occupeSansMur[i]].type=SOL_SALLE;
            carte->terrain[salle->occupeSansMur[i]].numeroSalle = salle->numeroSalle;
        }
    }
}
void genererSalleAlea(Carte *carte){
    //printf("genererSalleAlea");
    int position=0 , i=0;
    for(i=0; i<=carte->largeur/5; i++){
        Salle *salle= malloc(sizeof(Salle));
        if(salle==NULL){
            printf("Erreur d'allouage de mémoire");
            exit(1);
        }
        position =rand_a_b(carte->largeur+1 , carte->largeur*carte->hauteur-(carte->largeur+2));
        *salle = creerSalle(position , rand_a_b(5 , carte->largeur/5) , rand_a_b(5 , carte->largeur/5) , i+1 , carte);
        dessinerSalle(salle , carte);
        detruireOccupeMur(salle);
        free(salle);
        salle=NULL;
    }
    carte->nbSalle=i;
}
void fermerSalle(Carte *carte){
    //printf("fermerSalle");
    int i=0 , compteur=0 , *murSuppr=NULL;
    murSuppr= malloc(carte->largeur*carte->hauteur*sizeof(int));
    for(i=0; i<carte->largeur*carte->hauteur; i++){
        if(carte->terrain[i].type==SOL_SALLE){
            if(carte->terrain[i+carte->largeur].type==VIDE){
                carte->terrain[i].type=MUR_SALLE;
            }
            else if(carte->terrain[i+1].type==VIDE){
                carte->terrain[i].type=MUR_SALLE;
            }
            else if(carte->terrain[i-1].type==VIDE){
                carte->terrain[i].type=MUR_SALLE;
            }
            else if(carte->terrain[i-carte->largeur].type==VIDE){
                carte->terrain[i].type=MUR_SALLE;
            }
        }
        if(carte->terrain[i].type==MUR_SALLE){
            if(carte->terrain[i+1].type==MUR_SALLE&&carte->terrain[i-1].type==MUR_SALLE&&carte->terrain[i-carte->largeur].type==SOL_SALLE&&carte->terrain[i+carte->largeur].type==MUR_SALLE){
                if(carte->terrain[i+1+carte->largeur].type!=VIDE&&carte->terrain[i-1+carte->largeur].type!=VIDE&&carte->terrain[i+1-carte->largeur].type!=VIDE&&carte->terrain[i-1-carte->largeur].type!=VIDE){
                    murSuppr[compteur]=i;
                    compteur++;
                }
            }
        }
    }
    for(i=0; i<compteur; i++){
        carte->terrain[murSuppr[i]].type=SOL_SALLE;
    }
    free(murSuppr);
}


