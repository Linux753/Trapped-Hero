#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../../include/structure.h"
#include "../../include/Generateur_chemin.h"
#include "../../include/Generateur_carte_alea.h"
void murChemin(Carte *carte , int position , int orientation){
    //printf("murChemin");
    if(orientation==VERTICALE){
        if(carte->terrain[position+1].type==VIDE||carte->terrain[position+1].type==SOL_SALLE){
            carte->terrain[position+1].type=MUR_CHEMIN;
        }
        if(carte->terrain[position-1].type==VIDE||carte->terrain[position-1].type==SOL_SALLE){
            carte->terrain[position-1].type=MUR_CHEMIN;
        }
    }
    else if(orientation==HORIZONTALE){
        if(carte->terrain[position+carte->largeur].type==VIDE||carte->terrain[position+carte->largeur].type==SOL_SALLE){
            carte->terrain[position+carte->largeur].type=MUR_CHEMIN;
        }
        if(carte->terrain[position-carte->largeur].type==VIDE||carte->terrain[position-carte->largeur].type==SOL_SALLE){
            carte->terrain[position-carte->largeur].type=MUR_CHEMIN;
        }
    }
}
void murCheminSalle(Carte *carte , int position , int orientation){
    if(orientation==VERTICALE){
        if(carte->terrain[position+1].type==VIDE||carte->terrain[position+1].type==SOL_SALLE){
            carte->terrain[position+1].type=MUR_SALLE;
        }
        if(carte->terrain[position-1].type==VIDE||carte->terrain[position-1].type==SOL_SALLE){
            carte->terrain[position-1].type=MUR_SALLE;
        }
    }
    else if(orientation==HORIZONTALE){
        if(carte->terrain[position+carte->largeur].type==VIDE||carte->terrain[position+carte->largeur].type==SOL_SALLE){
            carte->terrain[position+carte->largeur].type=MUR_SALLE;
        }
        if(carte->terrain[position-carte->largeur].type==VIDE||carte->terrain[position-carte->largeur].type==SOL_SALLE){
            carte->terrain[position-carte->largeur].type=MUR_SALLE;
        }
    }
}
void fermerCheminSalle(Carte *carte , int position , int direction){
        if(direction==HAUT||direction==BAS){
        murCheminSalle(carte , position , VERTICALE);
        if(direction==HAUT){
            position=position-carte->largeur;
        }
        else{
            position=position+carte->largeur;
        }
        if(carte->terrain[position].type==VIDE){
            carte->terrain[position].type=MUR_CHEMIN;
        }
        if(carte->terrain[position+1].type==VIDE){
            carte->terrain[position+1].type=MUR_CHEMIN;
        }
        if(carte->terrain[position-1].type==VIDE){
            carte->terrain[position-1].type=MUR_CHEMIN;
        }
    }
    if(direction==GAUCHE||direction==DROITE){
        murCheminSalle(carte , position , HORIZONTALE);
        if(direction==GAUCHE){
            position--;
        }
        else{
            position++;
        }
        if(carte->terrain[position].type==VIDE){
            carte->terrain[position].type=MUR_CHEMIN;
        }
        if(carte->terrain[position+carte->largeur].type==VIDE){
            carte->terrain[position+carte->largeur].type=MUR_CHEMIN;
        }
        if(carte->terrain[position-carte->largeur].type==VIDE){
            carte->terrain[position-carte->largeur].type=MUR_CHEMIN;
        }
    }
}
void fermerChemin(Carte *carte , int position , int direction){
    if(direction==HAUT||direction==BAS){
        murChemin(carte , position , VERTICALE);
        if(direction==HAUT){
            position=position-carte->largeur;
        }
        else{
            position=position+carte->largeur;
        }
        if(carte->terrain[position].type==VIDE){
            carte->terrain[position].type=MUR_CHEMIN;
        }
        if(carte->terrain[position+1].type==VIDE){
            carte->terrain[position+1].type=MUR_CHEMIN;
        }
        if(carte->terrain[position-1].type==VIDE){
            carte->terrain[position-1].type=MUR_CHEMIN;
        }
    }
    if(direction==GAUCHE||direction==DROITE){
        murChemin(carte , position , HORIZONTALE);
        if(direction==GAUCHE){
            position--;
        }
        else{
            position++;
        }
        if(carte->terrain[position].type==VIDE){
            carte->terrain[position].type=MUR_CHEMIN;
        }
        if(carte->terrain[position+carte->largeur].type==VIDE){
            carte->terrain[position+carte->largeur].type=MUR_CHEMIN;
        }
        if(carte->terrain[position-carte->largeur].type==VIDE){
            carte->terrain[position-carte->largeur].type=MUR_CHEMIN;
        }
    }
}
int rand_a_b(int minimum , int maximum){
    return rand()%(maximum-minimum)+minimum;
}
int dessinerChemin(Carte *carte , int position , int nbCase,  int direction , int *collision , int numero){
    //printf("dessinerChemin");
    int i=0 , continuer=1;
    if(direction == HAUT){
        for(i=position-carte->largeur; i>=position-(carte->largeur*nbCase)&&continuer; i=i -carte->largeur ){
            if(i>=0&&i<=((carte->largeur*carte->hauteur)-1)){
                if(carte->terrain[i].type==VIDE||carte->terrain[i].type==MUR_CHEMIN||carte->terrain[i].type==CHEMIN){
                    carte->terrain[i].type=1;
                    carte->terrain[i].numeroSalle=numero;
                    murChemin(carte , i , VERTICALE);
                    *collision=0;
                }
                else{
                    continuer=0;
                    *collision=HAUT;
                    i=i+carte->largeur;
                }
            }
        }
        i=i+carte->largeur;
    }
    else if(direction == BAS){
        for(i=position+carte->largeur; i<=position+(carte->largeur*nbCase)&&continuer; i=i +carte->largeur ){
            if(i>=0&&i<=((carte->largeur*carte->hauteur)-1)){
                if(carte->terrain[i].type==VIDE||carte->terrain[i].type==MUR_CHEMIN||carte->terrain[i].type==CHEMIN){
                    carte->terrain[i].type=1;
                    carte->terrain[i].numeroSalle=numero;
                    murChemin(carte , i , VERTICALE);
                    *collision=0;
                }
                else{
                    continuer=0;
                    *collision=BAS;
                    i=i-carte->largeur;
                }
            }
        }
        i=i-carte->largeur;
    }
    else if(direction == GAUCHE){
        for(i=position-1; i>=position-nbCase&&continuer; i-- ){
            if(i>=0&&i<=((carte->largeur*carte->hauteur)-1)){
                if(carte->terrain[i].type==VIDE||carte->terrain[i].type==MUR_CHEMIN||carte->terrain[i].type==CHEMIN){
                    carte->terrain[i].type=1;
                    carte->terrain[i].numeroSalle=numero;
                    murChemin(carte , i , HORIZONTALE);
                    *collision=0;
                }
                else{
                    *collision=GAUCHE;
                    continuer=0;
                    i++;
                }
            }
        }
        i++;
    }
    else if(direction == DROITE){
        for(i=position+1; i<=position+nbCase&&continuer; i++ ){
            if(i>=0&&i<=((carte->largeur*carte->hauteur)-1)){
                if(carte->terrain[i].type==VIDE||carte->terrain[i].type==MUR_CHEMIN||carte->terrain[i].type==CHEMIN){
                    carte->terrain[i].type=1;
                    carte->terrain[i].numeroSalle=numero;
                    murChemin(carte , i , HORIZONTALE);
                    *collision=0;
                }
                else{
                    *collision=DROITE;
                    continuer=0;
                    i--;
                }
            }
        }
        i--;
    }
    fermerChemin(carte , i , direction);
    return i;
}
void dessinerPorte(Carte* carte){
    int i=0  , salleNb=carte->nbSalle , compteurPorte=0, compteur=0 , *posMur=NULL , position=0 , continuer=0 , compteur2 = 0 , porte1=0 , porte2=0 , verificateur=0 , numero=100 , nb=60;
    for(salleNb=carte->nbSalle; salleNb>0; salleNb--){
        compteur=0 , compteur2=0;
        posMur = malloc((carte->largeur/5)*(carte->largeur/5)*sizeof(int));
        for(i=0;i<(carte->largeur/5)*(carte->largeur/5); i++){
            posMur[i]=0;
        }
        for(i=1; i<carte->hauteur*carte->largeur; i++){
            if(carte->terrain[i].type==MUR_SALLE&&carte->terrain[i].numeroSalle==salleNb){
                posMur[compteur]=i;
                compteur++;
            }
        }
        if(compteur!=0){
            do{
                position = rand_a_b(0 , compteur);
                carte->terrain[posMur[position]].type= PORTE;
                if(compteur2>compteur){
                    continuer=0;
                    carte->terrain[posMur[position]].type=MUR_SALLE;
                }
                else if(carte->terrain[posMur[position]+1].type==MUR_SALLE&&carte->terrain[posMur[position]-1].type==MUR_SALLE&&(carte->terrain[posMur[position]-carte->largeur].type==MUR_SALLE||carte->terrain[posMur[position]+carte->largeur].type==MUR_SALLE)){
                    carte->terrain[posMur[position]].type= MUR_SALLE;
                    continuer=1;
                    compteur2++;
                }
                else if(carte->terrain[posMur[position]+carte->largeur].type==MUR_SALLE&&carte->terrain[posMur[position]-carte->largeur].type==MUR_SALLE&&(carte->terrain[posMur[position]-1].type==MUR_SALLE||carte->terrain[posMur[position]+1].type==MUR_SALLE)){
                    carte->terrain[posMur[position]].type= MUR_SALLE;
                    continuer=1;
                    compteur2++;
                }
                else if(carte->terrain[posMur[position]+1].type==MUR_SALLE&&carte->terrain[posMur[position]-1].type==MUR_SALLE&&(carte->terrain[posMur[position]-carte->largeur].type==MUR||carte->terrain[posMur[position]+carte->largeur].type==MUR)){
                    carte->terrain[posMur[position]].type= MUR_SALLE;
                    continuer=1;
                    compteur2++;
                }
                else if(carte->terrain[posMur[position]+carte->largeur].type==MUR_SALLE&&carte->terrain[posMur[position]-carte->largeur].type==MUR_SALLE&&(carte->terrain[posMur[position]-1].type==MUR||carte->terrain[posMur[position]+1].type==MUR)){
                    carte->terrain[posMur[position]].type= MUR_SALLE;
                    continuer=1;
                    compteur2++;
                }
                else if(carte->terrain[posMur[position]+1].type==MUR_SALLE&&carte->terrain[posMur[position]-1].type==MUR_SALLE){
                    carte->terrain[posMur[position]].orientation=HORIZONTALE;
                    continuer=0;
                }
                else if(carte->terrain[posMur[position]+carte->largeur].type==MUR_SALLE&&carte->terrain[posMur[position]-carte->largeur].type==MUR_SALLE){
                    carte->terrain[posMur[position]].orientation=VERTICALE;
                    continuer=0;
                }
                else{
                    carte->terrain[posMur[position]].type= MUR_SALLE;
                    continuer=1;
                    compteur2++;
                }
            }while(continuer);
        }
        if(carte->terrain[posMur[position]].orientation==HORIZONTALE){
            if(carte->terrain[posMur[position]+carte->largeur].type==SOL_SALLE&&carte->terrain[posMur[position]-carte->largeur].type==SOL_SALLE){
                carte->terrain[posMur[position]].type=MUR_SALLE;
            }
        }
        else if(carte->terrain[posMur[position]].orientation==VERTICALE){
            if(carte->terrain[posMur[position]+1].type==SOL_SALLE&&carte->terrain[posMur[position]-1].type==SOL_SALLE){
                carte->terrain[posMur[position]].type=MUR_SALLE;
            }
        }
        if(carte->terrain[posMur[position]].type==PORTE){
            if(verificateur){
                carte->blackListRoom[carte->nbBlackListRoom]=carte->terrain[porte1].numeroSalle;
                carte->nbBlackListRoom++;
                porte1=posMur[position];
                verificateur=0;
                printf("\nverificateur\n");
            }
            else{
                porte2=porte1;
                porte1=posMur[position];
            }
            if(porte2!=0){
                if(carte->terrain[porte2].orientation==HORIZONTALE){
                    if(carte->terrain[porte2+carte->largeur].type==SOL_SALLE){
                        porte2=porte2-carte->largeur;
                    }
                    else{
                        porte2=porte2+carte->largeur;
                    }
                }
                else{
                    if(carte->terrain[porte2+1].type==SOL_SALLE){
                        porte2=porte2-1;
                    }
                    else{
                        porte2=porte2+1;
                    }
                }
                compteurPorte++;
                verificateur=aller(carte , porte1 , porte2 , &numero);
                //printf("%d verif =%d\n"  , compteurPorte , verificateur);
                //scanf("%d" , &compteurPorte);
            }
        }
        free(posMur);
        posMur = NULL;
    }
}
int eloignerPorte(Carte *carte ,int *position , int *direction) {
    int sortie=0 ;
    if((carte->terrain[*position+1].type==VIDE||carte->terrain[*position+1].type==CHEMIN||carte->terrain[*position+1].type==MUR_CHEMIN)&&carte->terrain[*position-1].type==SOL_SALLE){
        *position=*position+1;
        carte->terrain[*position].type=CHEMIN;
        fermerChemin(carte , *position , DROITE);
        *direction=DROITE;
        sortie=0;
        //afficherCarte(carte);
        //scanf("%d" , &test);
    }
    else if((carte->terrain[*position-1].type==VIDE||carte->terrain[*position-1].type==CHEMIN||carte->terrain[*position-1].type==MUR_CHEMIN)&&carte->terrain[*position+1].type==SOL_SALLE){
        *position=*position-1;
        carte->terrain[*position].type=CHEMIN;
        fermerChemin(carte , *position , GAUCHE);
        *direction=GAUCHE;
        sortie=0;
        //afficherCarte(carte);
        //scanf("%d" , &test);
    }
    else if((carte->terrain[*position+carte->largeur].type==VIDE||carte->terrain[*position+carte->largeur].type==CHEMIN||carte->terrain[*position+carte->largeur].type==MUR_CHEMIN)&&carte->terrain[*position-carte->largeur].type==SOL_SALLE){
        *position=*position+carte->largeur;
        carte->terrain[*position].type=CHEMIN;
        fermerChemin(carte , *position , BAS);
        *direction=BAS;
        sortie=0;
        //afficherCarte(carte);
        //scanf("%d" , &test);
    }
    else if((carte->terrain[*position-carte->largeur].type==VIDE||carte->terrain[*position-carte->largeur].type==CHEMIN||carte->terrain[*position-carte->largeur].type==MUR_CHEMIN)&&carte->terrain[*position+carte->largeur].type==SOL_SALLE){
        *position=*position-carte->largeur;
        carte->terrain[*position].type=CHEMIN;
        fermerChemin(carte , *position , HAUT);
        *direction=HAUT;
        sortie=0;
        //afficherCarte(carte);
        //scanf("%d" , &test);
    }
    else{
        sortie=1;
    }
    return sortie;
}
int contourner(Carte *carte , int position , int directionDest , int destination , int numeroContourner){
    int direction=0 , collision=0 , continuer=1 ,  nouvellePos=position , continuer2=0;//1 , test=0;
    if(directionDest==HAUT){
        if(destination%carte->largeur>nouvellePos%carte->largeur){
            if(carte->terrain[nouvellePos+1].type==VIDE||carte->terrain[nouvellePos+1].type==CHEMIN||carte->terrain[nouvellePos+1].type==MUR_CHEMIN){
                direction=DROITE;
            }
            else{
                direction=GAUCHE;
            }
        }
        else if(nouvellePos%carte->largeur>destination%carte->largeur){
            if(carte->terrain[nouvellePos-1].type==VIDE||carte->terrain[nouvellePos-1].type==CHEMIN||carte->terrain[nouvellePos-1].type==MUR_CHEMIN){
                direction=GAUCHE;
            }
            else{
                direction=DROITE;
            }
        }
        else{
            direction=rand_a_b(GAUCHE , 5);
        }
        while(continuer){
            //printf("contourner");
            //afficherCarte(carte);
            nouvellePos=dessinerChemin(carte , nouvellePos , 1 , direction , &collision , numeroContourner);
            murChemin(carte , nouvellePos , HORIZONTALE);
            if(nouvellePos==destination){
                continuer=0;
            }
            else{
                if(carte->terrain[nouvellePos].numeroSalle==numeroContourner){
                    carte->terrain[nouvellePos].numeroSalle=99;
                }
                else if(carte->terrain[nouvellePos].numeroSalle==50){
                    printf("\nnouvellePos=%d" , nouvellePos);
                    carte->terrain[nouvellePos].numeroSalle=100;
                    return -1;
                }
                else if(carte->terrain[nouvellePos].numeroSalle<=99){
                    carte->terrain[nouvellePos].numeroSalle--;
                }
                if((collision&&carte->terrain[nouvellePos-1].type==MUR)||(collision&&carte->terrain[nouvellePos+1].type==MUR)){
                    nouvellePos=nouvellePos-carte->largeur;
                    continuer2=1;
                    while(carte->terrain[nouvellePos].type!=VIDE&&continuer2){
                        if(carte->terrain[nouvellePos].type==MUR){
                            nouvellePos=nouvellePos+carte->largeur;
                            return nouvellePos;
                        }
                        carte->terrain[nouvellePos].type=CHEMIN;
                        carte->terrain[nouvellePos].numeroSalle=numeroContourner;
                        if(nouvellePos==destination){
                            continuer2=0;
                            continuer=0;
                        }
                        murCheminSalle(carte , nouvellePos , VERTICALE);
                        nouvellePos=nouvellePos-carte->largeur;
                    }
                    nouvellePos=nouvellePos+carte->largeur;
                    fermerChemin(carte , nouvellePos , HAUT);
                }
                else if(collision){
                    //printf("contourner = %d\n" , numeroContourner);
                    //afficherCarte(carte);
                    //scanf("%d" , &test);
                    nouvellePos=contourner(carte , nouvellePos , collision , destination , numeroContourner);
                    if(nouvellePos==-1){
                        return -1;
                    }
                }
                if(carte->terrain[nouvellePos-carte->largeur].type==VIDE||carte->terrain[nouvellePos-carte->largeur].type==MUR_CHEMIN||carte->terrain[nouvellePos-carte->largeur].type==CHEMIN){
                    continuer=0;
                    nouvellePos=nouvellePos-carte->largeur;
                    carte->terrain[nouvellePos].type=CHEMIN;
                    fermerChemin(carte , nouvellePos , HAUT);
                }
            }
        }
    }
    if(directionDest==BAS){
        if(destination%carte->largeur>nouvellePos%carte->largeur){
            if(carte->terrain[nouvellePos+1].type==VIDE||carte->terrain[nouvellePos+1].type==CHEMIN||carte->terrain[nouvellePos+1].type==MUR_CHEMIN){
                direction=DROITE;
            }
            else{
                direction=GAUCHE;
            }
        }
        else if(nouvellePos%carte->largeur>destination%carte->largeur){
            if(carte->terrain[nouvellePos-1].type==VIDE||carte->terrain[nouvellePos-1].type==CHEMIN||carte->terrain[nouvellePos-1].type==MUR_CHEMIN){
                direction=GAUCHE;
            }
            else{
                direction=DROITE;
            }
        }
        else{
            direction=rand_a_b(GAUCHE , 5);
        }
        while(continuer){
            //printf("contourner");
            //afficherCarte(carte);
            nouvellePos=dessinerChemin(carte , nouvellePos , 1 , direction , &collision , numeroContourner);
            murChemin(carte , nouvellePos , HORIZONTALE);
            if(nouvellePos==destination){
                continuer=0;
            }
            else{
                if(carte->terrain[nouvellePos].numeroSalle==numeroContourner){
                    carte->terrain[nouvellePos].numeroSalle=99;
                }
                else if(carte->terrain[nouvellePos].numeroSalle==50){
                    printf("\nnouvellePos=%d" , nouvellePos);
                    carte->terrain[nouvellePos].numeroSalle=100;
                    return -1;
                }
                else if(carte->terrain[nouvellePos].numeroSalle<=99){
                    carte->terrain[nouvellePos].numeroSalle--;
                }
                if((collision&&carte->terrain[nouvellePos-1].type==MUR)||(collision&&carte->terrain[nouvellePos+1].type==MUR)){
                    nouvellePos=nouvellePos+carte->largeur;
                    continuer2=1;
                    while(carte->terrain[nouvellePos].type!=VIDE&&continuer2){
                        if(carte->terrain[nouvellePos].type==MUR){
                            nouvellePos=nouvellePos-carte->largeur;
                            return nouvellePos;
                        }
                        carte->terrain[nouvellePos].type=CHEMIN;
                        carte->terrain[nouvellePos].numeroSalle=numeroContourner;
                        if(nouvellePos==destination){
                            continuer2=0;
                            continuer=0;
                        }
                        murCheminSalle(carte , nouvellePos , VERTICALE);
                        nouvellePos=nouvellePos+carte->largeur;
                    }
                    nouvellePos=nouvellePos-carte->largeur;
                    fermerChemin(carte , nouvellePos , BAS);
                }
                else if(collision){
                    //printf("contourner = %d\n" , numeroContourner);
                    //afficherCarte(carte);
                    //scanf("%d" , &test);
                    nouvellePos=contourner(carte , nouvellePos , collision , destination , numeroContourner);
                    if(nouvellePos==-1){
                        return -1;
                    }
                }
                if(carte->terrain[nouvellePos+carte->largeur].type==VIDE||carte->terrain[nouvellePos+carte->largeur].type==MUR_CHEMIN||carte->terrain[nouvellePos+carte->largeur].type==CHEMIN){
                    continuer=0;
                    nouvellePos=nouvellePos+carte->largeur;
                    carte->terrain[nouvellePos].type=CHEMIN;
                    fermerChemin(carte , nouvellePos , BAS);
                }
            }
        }
    }
    if(directionDest==GAUCHE){
       if(destination/carte->largeur>nouvellePos/carte->largeur){
            if(carte->terrain[nouvellePos+carte->largeur].type==VIDE||carte->terrain[nouvellePos+carte->largeur].type==CHEMIN||carte->terrain[nouvellePos+carte->largeur].type==MUR_CHEMIN){
                direction=BAS;
            }
            else{
                direction=HAUT;
            }
        }
        else if(nouvellePos/carte->largeur>destination/carte->largeur){
            if(carte->terrain[nouvellePos-carte->largeur].type==VIDE||carte->terrain[nouvellePos-carte->largeur].type==CHEMIN||carte->terrain[nouvellePos-carte->largeur].type==MUR_CHEMIN){
                direction=HAUT;
            }
            else{
                direction=BAS;
            }
        }
        else{
            direction=rand_a_b(HAUT , 3);
        }
        while(continuer){
            //printf("contourner");
            //afficherCarte(carte);
            nouvellePos=dessinerChemin(carte , nouvellePos , 1 , direction , &collision , numeroContourner);
            murChemin(carte , nouvellePos , VERTICALE);
            if(nouvellePos==destination){
                continuer=0;
            }
            else{
                if(carte->terrain[nouvellePos].numeroSalle==numeroContourner){
                    carte->terrain[nouvellePos].numeroSalle=99;
                }
                else if(carte->terrain[nouvellePos].numeroSalle==50){
                    printf("\nnouvellePos=%d" , nouvellePos);
                    carte->terrain[nouvellePos].numeroSalle=100;
                    return -1;
                }
                else if(carte->terrain[nouvellePos].numeroSalle<=99){
                    carte->terrain[nouvellePos].numeroSalle--;
                }
                if((collision&&carte->terrain[nouvellePos-carte->largeur].type==MUR)||(collision&&carte->terrain[nouvellePos+carte->largeur].type==MUR)){
                    nouvellePos=nouvellePos-1;
                    continuer2=1;
                    while(carte->terrain[nouvellePos].type!=VIDE&&continuer2){
                        if(carte->terrain[nouvellePos].type==MUR){
                            nouvellePos=nouvellePos+1;
                            return nouvellePos;
                        }
                        carte->terrain[nouvellePos].type=CHEMIN;
                        carte->terrain[nouvellePos].numeroSalle=numeroContourner;
                        if(nouvellePos==destination){
                            continuer2=0;
                            continuer=0;
                        }
                        murCheminSalle(carte , nouvellePos , HORIZONTALE);
                        nouvellePos=nouvellePos-1;
                    }
                    nouvellePos=nouvellePos+1;
                    fermerChemin(carte , nouvellePos , GAUCHE);
                }
                else if(collision){
                    //printf("contourner = %d\n" , numeroContourner);
                    //afficherCarte(carte);
                    //scanf("%d" , &test);
                    nouvellePos=contourner(carte , nouvellePos , collision , destination , numeroContourner);
                    if(nouvellePos==-1){
                        return -1;
                    }
                }
                if(carte->terrain[nouvellePos-1].type==VIDE||carte->terrain[nouvellePos-1].type==MUR_CHEMIN||carte->terrain[nouvellePos-1].type==CHEMIN){
                    continuer=0;
                    nouvellePos=nouvellePos-1;
                    carte->terrain[nouvellePos].type=CHEMIN;
                    fermerChemin(carte , nouvellePos , GAUCHE);
                }
            }
        }
    }
    if(directionDest==DROITE){
        if(destination/carte->largeur>nouvellePos/carte->largeur){
            if(carte->terrain[nouvellePos+carte->largeur].type==VIDE||carte->terrain[nouvellePos+carte->largeur].type==CHEMIN||carte->terrain[nouvellePos+carte->largeur].type==MUR_CHEMIN){
                direction=BAS;
            }
            else{
                direction=HAUT;
            }
        }
        else if(nouvellePos/carte->largeur>destination/carte->largeur){
            if(carte->terrain[nouvellePos-carte->largeur].type==VIDE||carte->terrain[nouvellePos-carte->largeur].type==CHEMIN||carte->terrain[nouvellePos-carte->largeur].type==MUR_CHEMIN){
                direction=HAUT;
            }
            else{
                direction=BAS;
            }
        }
        else{
            direction=rand_a_b(HAUT , 3);
        }
        while(continuer){
            //printf("contourner");
            //afficherCarte(carte);
            nouvellePos=dessinerChemin(carte , nouvellePos , 1 , direction , &collision , numeroContourner);
            murChemin(carte , nouvellePos , VERTICALE);
            if(nouvellePos==destination){
                continuer=0;
            }
            else{
                if(carte->terrain[nouvellePos].numeroSalle==numeroContourner){
                    carte->terrain[nouvellePos].numeroSalle=99;
                }
                else if(carte->terrain[nouvellePos].numeroSalle==50){
                    printf("\nnouvellePos=%d" , nouvellePos);
                    carte->terrain[nouvellePos].numeroSalle=100;
                    return -1;
                }
                else if(carte->terrain[nouvellePos].numeroSalle<=99){
                    carte->terrain[nouvellePos].numeroSalle--;
                }
                if((collision&&carte->terrain[nouvellePos-carte->largeur].type==MUR)||(collision&&carte->terrain[nouvellePos+carte->largeur].type==MUR)){
                    nouvellePos=nouvellePos+1;
                    continuer2=1;
                    while(carte->terrain[nouvellePos].type!=VIDE&&continuer2){
                        if(carte->terrain[nouvellePos].type==MUR){
                            nouvellePos=nouvellePos-1;
                            return nouvellePos;
                        }
                        carte->terrain[nouvellePos].type=CHEMIN;
                        carte->terrain[nouvellePos].numeroSalle=numeroContourner;
                        if(nouvellePos==destination){
                            continuer2=0;
                            continuer=0;
                        }
                        murCheminSalle(carte , nouvellePos , HORIZONTALE);
                        nouvellePos=nouvellePos+1;
                    }
                    nouvellePos=nouvellePos-1;
                    fermerChemin(carte , nouvellePos , DROITE);
                }
                else if(collision){
                    //printf("contourner = %d\n" , numeroContourner);
                    //afficherCarte(carte);
                    //scanf("%d" , &test);
                    nouvellePos=contourner(carte , nouvellePos , collision , destination , numeroContourner);
                    if(nouvellePos==-1){
                        return -1;
                    }
                }
                if(carte->terrain[nouvellePos+1].type==VIDE||carte->terrain[nouvellePos+1].type==MUR_CHEMIN||carte->terrain[nouvellePos+1].type==CHEMIN){
                    continuer=0;
                    nouvellePos=nouvellePos+1;
                    carte->terrain[nouvellePos].type=CHEMIN;
                    fermerChemin(carte , nouvellePos , DROITE);
                }
            }
        }
    }
    return nouvellePos;
}
int aller(Carte *carte , int position , int destination , int *numero ){
    //printf("aller");
    int  nouvellePos=position , collision=0, direction=0 , directionDestVerticale=0 , directionDestHorizontale=0  , numeroContourner=*numero;
    int compteurHorizon = 0 , compteurVerticale=0 , bonVerticale=1 , bonHorizontale=1;
    eloignerPorte(carte , &nouvellePos ,&direction );
    while(nouvellePos!=destination){
        if(numeroContourner>1000){
            *numero=numeroContourner;
            return 1;
        }
        bonHorizontale=1;
        collision=0;
        if(destination/carte->largeur>nouvellePos/carte->largeur){
            directionDestVerticale=BAS;
        }
        else if(nouvellePos/carte->largeur>destination/carte->largeur){
            directionDestVerticale=HAUT;
        }
        else {
            directionDestVerticale=0;
        }
        if(destination%carte->largeur>nouvellePos%carte->largeur){
            directionDestHorizontale=DROITE;
        }
        else if(nouvellePos%carte->largeur>destination%carte->largeur){
            directionDestHorizontale=GAUCHE;
        }
        else {
            directionDestHorizontale=0;
        }
        if(directionDestVerticale==HAUT&&bonVerticale){
            if(direction==BAS){
                /*nouvellePos=*/contourner(carte , nouvellePos , HAUT , destination , numeroContourner);
                if(nouvellePos==-1){
                    *numero=numeroContourner;
                    return 1;
                }
                numeroContourner++;
            }
            //if(carte->terrain[nouvellePos-carte->largeur].numeroSalle<99){
            compteurVerticale=0;
            nouvellePos=dessinerChemin(carte , nouvellePos , ((nouvellePos/carte->largeur)-(destination/carte->largeur)) , HAUT , &collision , 0);
            //}
            //afficherCarte(carte);
            if(collision){
                nouvellePos=contourner(carte , nouvellePos , directionDestVerticale , destination , numeroContourner);
                numeroContourner++;
                if(nouvellePos==-1){
                    *numero=numeroContourner;
                    return 1;
                }
                bonHorizontale=0;
                collision=0;
            }
            compteurVerticale++;
            //afficherCarte(carte);
        }
        else if(directionDestVerticale==BAS&&bonVerticale){
            if(direction==HAUT){
                /*nouvellePos=*/contourner(carte , nouvellePos , BAS , destination , numeroContourner);
                if(nouvellePos==-1){
                    *numero=numeroContourner;
                    return 1;
                }
                numeroContourner++;
            }
            //if(carte->terrain[nouvellePos+carte->largeur].numeroSalle<99){
            compteurVerticale=0;
            nouvellePos=dessinerChemin(carte , nouvellePos , ((destination/carte->largeur)-(nouvellePos/carte->largeur)) , BAS , &collision , 0);
            //}
            //afficherCarte(carte);
            if(collision){
                nouvellePos=contourner(carte , nouvellePos , directionDestVerticale , destination , numeroContourner);
                numeroContourner++;
                if(nouvellePos==-1){
                    *numero=numeroContourner;
                    return 1;
                }
                bonHorizontale=0;
                collision=0;
            }
            compteurVerticale++;
            //afficherCarte(carte);
        }
        bonVerticale=1;
        if(directionDestHorizontale==GAUCHE&&bonHorizontale){
            if(direction==DROITE){
                /*nouvellePos=*/contourner(carte , nouvellePos , GAUCHE , destination , numeroContourner);
                if(nouvellePos==-1){
                    *numero=numeroContourner;
                    return 1;
                }
                numeroContourner++;
            }
            //if(carte->terrain[nouvellePos-1].numeroSalle<99){
            compteurHorizon=0;
            nouvellePos=dessinerChemin(carte , nouvellePos , ((nouvellePos%carte->largeur)-(destination%carte->largeur)) , GAUCHE , &collision , 0);
            //}
            //afficherCarte(carte);
            if(collision){
                nouvellePos=contourner(carte , nouvellePos , directionDestHorizontale , destination , numeroContourner);
                numeroContourner++;
                if(nouvellePos==-1){
                    *numero=numeroContourner;
                    return 1;
                }
                bonVerticale=0;
                collision=0;
            }
            compteurHorizon++;
            //afficherCarte(carte);
        }
        if(directionDestHorizontale==DROITE&&bonHorizontale){
            if(direction==GAUCHE){
                /*nouvellePos=*/contourner(carte , nouvellePos , DROITE , destination , numeroContourner);
                if(nouvellePos==-1){
                    *numero=numeroContourner;
                    return 1;
                }
                numeroContourner++;
            }
            //if(carte->terrain[nouvellePos+1].numeroSalle<99){
            compteurHorizon=0;
            nouvellePos=dessinerChemin(carte , nouvellePos , ((destination%carte->largeur)-(nouvellePos%carte->largeur)) , DROITE , &collision , 0);
            //}
            //afficherCarte(carte);
            if(collision){
                nouvellePos=contourner(carte , nouvellePos , directionDestHorizontale , destination , numeroContourner);
                numeroContourner++;
                if(nouvellePos==-1){
                    *numero=numeroContourner;
                    return 1;
                }
                bonVerticale=0;
                collision=0;
            }
            compteurHorizon++;
            //afficherCarte(carte);
        }
        direction=0;
    }
    *numero=numeroContourner;
    return 0;
}

