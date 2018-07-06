#include <stdlib.h>
#include <stdio.h>
#include "../include/structure.h"

int takeObject(CarteSDL* carteSDL , Carte* carte, int objet  , int position){//Return the object on the floor or noting (-1)
    printf("ICI je suis\n");
    Type type;
    int i=0;
    type=carteSDL->listeObjet[i].type;
    if(carteSDL->perso->masseObjet+carteSDL->listeObjet[objet].poids<=carteSDL->perso->poidsMax&&carteSDL->perso->nbObjets<50){
      printf("ICI je suis encore\n");
      if(type==Epe||type==Arc||type==Massue||type==Fleche){
          while(carteSDL->perso->inventaireArme[i]!=0){
              i++;
          }
          carteSDL->perso->inventaireArme[i]=objet;
      }
      if(type==Baton||type==BatonMagique){
          while(carteSDL->perso->inventaireBaton[i]!=0){
              i++;
          }
          carteSDL->perso->inventaireBaton[i]=objet;
      }
      if(type==Armure){
          while(carteSDL->perso->inventaireArmure[i]!=0){
              i++;
          }
          carteSDL->perso->inventaireArmure[i]=objet;
      }
      if(type==Potion){
          while(carteSDL->perso->inventairePotion[i]!=0){
              i++;
          }
          carteSDL->perso->inventairePotion[i]=objet;
      }
      if(type==Parchemin){
          while(carteSDL->perso->inventaireParchemin[i]!=0){
              i++;
          }
          carteSDL->perso->inventaireParchemin[i]=objet;
      }
      carte->terrain[position].objet=-1;
      carteSDL->perso->masseObjet=carteSDL->perso->masseObjet+carteSDL->listeObjet[objet].poids;
      carteSDL->perso->nbObjets++;
      return -1;
    }
    else{
      return objet;
    }
}
int initialiserPersonnage(CarteSDL* carteSDL){
    int i=0;
    carteSDL->perso=malloc(sizeof(Personnage));
    carteSDL->perso->inventaireArme=malloc(sizeof(int)*50);
    if(carteSDL->perso->inventaireArme==NULL){
        return -1;
    }
    for(i=0;i<50;i++){
        carteSDL->perso->inventaireArme[i]=0;
    }
    carteSDL->perso->inventaireBaton=malloc(sizeof(int)*50);
    if(carteSDL->perso->inventaireBaton==NULL){
        return -1;
    }
    for(i=0;i<50;i++){
        carteSDL->perso->inventaireBaton[i]=0;
    }
    carteSDL->perso->inventaireArmure=malloc(sizeof(int)*50);
    if(carteSDL->perso->inventaireArmure==NULL){
        return -1;
    }
    for(i=0;i<50;i++){
        carteSDL->perso->inventaireArmure[i]=0;
    }
    carteSDL->perso->inventairePotion=malloc(sizeof(int)*50);
    if(carteSDL->perso->inventairePotion==NULL){
        return -1;
    }
    for(i=0;i<50;i++){
        carteSDL->perso->inventairePotion[i]=0;
    }
    carteSDL->perso->inventaireParchemin=malloc(sizeof(int)*50);
    if(carteSDL->perso->inventaireParchemin==NULL){
        return -1;
    }
    for(i=0;i<50;i++){
        carteSDL->perso->inventaireParchemin[i]=0;
    }
    carteSDL->perso->masseObjet=0;
    carteSDL->perso->vie=0;
    carteSDL->perso->force=0;
    carteSDL->perso->habilete=0;
    carteSDL->perso->precision=0;
    carteSDL->perso->magie=0;
    carteSDL->perso->agilite=0;
    carteSDL->perso->nbObjets=0;
    carteSDL->perso->poidsMax=50;
    carteSDL->perso->texture=carteSDL->personnage;
    return 0;
}
