#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "../include/structure.h"
#include "../include/Afficher_carte.h"

int ecrireTextSDL(CarteSDL* carteSDL , char* file,char* text ,int size ,  SDL_Texture** texture , SDL_Color *colorFg , SDL_Color *colorBg){
    SDL_Surface *surface=NULL;
    TTF_Font*font=NULL;
    int out=0;
    font=TTF_OpenFont(file , size);
    if(font==NULL){
        fprintf(stderr , "Erreur TTF_OpenFont : %s" , TTF_GetError());
        out=-1;
        goto QuitEcrireTextSDL;
    }
    if(colorBg==NULL){
        surface=TTF_RenderUTF8_Blended(font , text  , *colorFg );
        if(surface==NULL){
            fprintf(stderr , "Erreur TTF_RenderUTF8_Blended() : %s" , TTF_GetError());
            out=-1;
            goto QuitEcrireTextSDL;
        }
    }
    else{
        surface=TTF_RenderUTF8_Shaded(font , text , *colorFg , *colorBg);
        if(surface==NULL){
            fprintf(stderr , "Erreur TTF_RenderUTF8_Shaded() : %s" , TTF_GetError());
            out=-1;
            goto QuitEcrireTextSDL;
        }
    }
    *texture=SDL_CreateTextureFromSurface(carteSDL->renderer , surface);
    if(*texture==NULL){
        fprintf(stderr , "Erreur SDL_CreateTextureFromSurface() : %s" , SDL_GetError());
        out=-1;
        goto QuitEcrireTextSDL;
    }
    QuitEcrireTextSDL :
    if(font!=NULL){
        TTF_CloseFont(font);
    }
    if(surface!=NULL){
        SDL_FreeSurface(surface);
    }
    return out;
}
void demarrage(CarteSDL* sdlVar){
    SDL_Texture *imageSDL=NULL , *textSDL=NULL , *specialThank=NULL;
    int h=0 , w=0;
    SDL_Rect rectImage1 , rectTextSDL , rectSpecialThank;
    SDL_Color colorFg={255 , 255 , 255 , 255};
    loadIMG(sdlVar , "image/logoSDL.png" , &imageSDL);
    SDL_QueryTexture(imageSDL , NULL , NULL , &rectImage1.w , &rectImage1.h);
    SDL_GetWindowSize(sdlVar->window , &w , &h);
    rectImage1.x=(w/2)-(rectImage1.w/2);
    rectImage1.y=(h/2)-(rectImage1.h/2);
    ecrireTextSDL(sdlVar , "police/OpenSans-Regular.ttf" , "Created by Linux with :", 80  , &textSDL , &colorFg , NULL );
    SDL_QueryTexture(textSDL , NULL , NULL , &rectTextSDL.w , &rectTextSDL.h);
    rectTextSDL.x=(w/2)-(rectTextSDL.w/2);
    rectTextSDL.y=((rectImage1.y)/2)-rectTextSDL.h;
    ecrireTextSDL(sdlVar , "police/OpenSans-Regular.ttf" , "Special thanks to Mr Dator for the compilation on windows", 40  , &specialThank , &colorFg , NULL );
    SDL_QueryTexture(specialThank , NULL , NULL , &rectSpecialThank.w , &rectSpecialThank.h);
    rectSpecialThank.x=(w/2)-(rectSpecialThank.w/2);
    rectSpecialThank.y=h-(h/10);
    SDL_SetRenderDrawColor(sdlVar->renderer , 38 , 38 , 38 , 0);
    SDL_RenderClear(sdlVar->renderer);
    SDL_RenderCopy(sdlVar->renderer , imageSDL , NULL , &rectImage1);
    SDL_RenderCopy(sdlVar->renderer , textSDL , NULL , &rectTextSDL);
    SDL_RenderCopy(sdlVar->renderer , specialThank , NULL , &rectSpecialThank);
    SDL_RenderPresent(sdlVar->renderer);
    SDL_Delay(2000);
    SDL_DestroyTexture(imageSDL);
    SDL_DestroyTexture(textSDL);
    SDL_DestroyTexture(specialThank);
}
void quitterMenuSave(Button *button1 , Button *button2 , Button *button3){
    if(button1!=NULL){
        if(button1->text!=NULL){
            SDL_DestroyTexture(button1->text);
        }
    free(button1);
    }
    if(button2!=NULL){
        if(button2->text!=NULL){
            SDL_DestroyTexture(button2->text);
        }
    free(button2);
    }
    if(button3!=NULL){
        if(button3->text!=NULL){
            SDL_DestroyTexture(button3->text);
        }
    free(button3);
    }
}
int initMenuSave(CarteSDL *carteSDL , Button *game1 , Button *game2 , Button *game3){
    SDL_Color colorfg={0 , 0 , 0 , 255};
    int w=0 , h=0;
    if(0!=ecrireTextSDL(carteSDL , "police/OpenSans-Regular.ttf" , "Game 1" , 50 , &game1->text , &colorfg , NULL)){
        fprintf(stderr , "\nErreur write text for button\n");
        return -1;
    }
    if(0!=ecrireTextSDL(carteSDL , "police/OpenSans-Regular.ttf" , "Game 2" , 50 , &game2->text , &colorfg , NULL)){
        fprintf(stderr , "\nErreur write text for button\n");
        return -1;
    }
    if(0!=ecrireTextSDL(carteSDL , "police/OpenSans-Regular.ttf" , "Game 3" , 50 , &game3->text , &colorfg , NULL)){
        fprintf(stderr , "\nErreur write text for button\n");
        return -1;
    }
    /*Now set the rect of texture*/
    SDL_QueryTexture(game1->text , NULL , NULL , &game1->rectText.w , &game1->rectText.h);
    SDL_QueryTexture(game2->text , NULL , NULL , &game2->rectText.w , &game2->rectText.h);
    SDL_QueryTexture(game3->text , NULL , NULL , &game3->rectText.w , &game3->rectText.h);
    SDL_GetWindowSize(carteSDL->window , &w , &h);
    game1->rectSelect.y=20;
    game1->rectSelect.h=h-40;
    game1->rectSelect.w=(w-80)/3;
    game1->rectSelect.x=20*1+game1->rectSelect.w*0;
    game1->rectText.x=(game1->rectSelect.x+(game1->rectSelect.w/2))-game1->rectText.w/2;
    game1->rectText.y=(game1->rectSelect.y+(game1->rectSelect.h/2))-game1->rectText.h/2;
    game1->select=0;
    game2->rectSelect.y=20;
    game2->rectSelect.h=h-40;
    game2->rectSelect.w=(w-80)/3;
    game2->rectSelect.x=20*2+game2->rectSelect.w*1;
    game2->rectText.x=(game2->rectSelect.x+(game2->rectSelect.w/2))-game2->rectText.w/2;
    game2->rectText.y=(game2->rectSelect.y+(game2->rectSelect.h/2))-game2->rectText.h/2;
    game2->select=0;
    game3->rectSelect.y=20;
    game3->rectSelect.h=h-40;
    game3->rectSelect.w=(w-80)/3;
    game3->rectSelect.x=20*3+game3->rectSelect.w*2;
    game3->rectText.x=(game3->rectSelect.x+(game3->rectSelect.w/2))-game3->rectText.w/2;
    game3->rectText.y=(game3->rectSelect.y+(game3->rectSelect.h/2))-game3->rectText.h/2;
    game3->select=0;
    return 0;
}
int printMenuSave(CarteSDL *carteSDL , Button *game1 , Button *game2 , Button *game3){
    SDL_SetRenderDrawColor(carteSDL->renderer , 88 , 40 , 0 , 255);
    SDL_RenderClear(carteSDL->renderer);
    if(0!=SDL_RenderCopy(carteSDL->renderer , game1->text , NULL  , &game1->rectText)){
        fprintf(stderr , "Erreur SDL_RenderCopy() : %s \n" , SDL_GetError());
        return -1;
    }
    if(0!=SDL_RenderCopy(carteSDL->renderer , game2->text , NULL  , &game2->rectText)){
        fprintf(stderr , "Erreur SDL_RenderCopy() : %s \n" , SDL_GetError());
        return -1;
    }
    if(0!=SDL_RenderCopy(carteSDL->renderer , game3->text , NULL  , &game3->rectText)){
        fprintf(stderr , "Erreur SDL_RenderCopy() : %s \n" , SDL_GetError());
        return -1;
    }
}
int menuSave(CarteSDL* carteSDL){
    Button *game1=NULL , *game2=NULL , *game3=NULL;
    SDL_Point mousePos;
    SDL_Event event;
    int continuer=1 , out=0;
    game1=malloc(sizeof(Button));
    if(game1==NULL){
        fprintf(stderr , "Erreur d'allocation de mémoire\n");
        quitterMenuSave(game1 , game2 , game3);
        return -1;
    }
    game2=malloc(sizeof(Button));
    if(game2==NULL){
        fprintf(stderr , "Erreur d'allocation de mémoire\n");
        quitterMenuSave(game1 , game2 , game3);
        return -1;
    }
    game3=malloc(sizeof(Button));
    if(game3==NULL){
        fprintf(stderr , "Erreur d'allocation de mémoire\n");
        quitterMenuSave(game1 , game2 , game3);
        return -1;
    }
    if(0!=initMenuSave(carteSDL , game1 , game2 , game3)){
        fprintf(stderr , "Erreur initMenuSave()\n");
        quitterMenuSave(game1 , game2 , game3);
        return -1;
    }
    if(0!=printMenuSave(carteSDL , game1 , game2 , game3)){
        fprintf(stderr , "Erreur printMenuSave()\n");
        quitterMenuSave(game1 , game2 , game3);
        return -1;
    }
    SDL_RenderPresent(carteSDL->renderer);
    SDL_GetMouseState(&mousePos.x , &mousePos.y);
    while(continuer){
        if(SDL_PollEvent(&event)){
            switch(event.type){
                case SDL_MOUSEMOTION :
                    SDL_GetMouseState(&mousePos.x , &mousePos.y);
                    break;
                case SDL_MOUSEBUTTONDOWN :
                        if(game1->select==1){
                            continuer=0;
                            out=1;
                        }
                        if(game2->select==1){
                            continuer=0;
                            out=2;
                        }
                        if(game3->select==1){
                            continuer=0;
                            out=3;
                        }
                        break;
            }
        }
        else{
            SDL_Delay(10);
        }
        if(SDL_PointInRect(&mousePos , &game1->rectSelect)==SDL_TRUE){
            if(game1->select!=1){
                game1->select=1;
                SDL_SetRenderDrawColor(carteSDL->renderer , 0 , 0 , 0 , 255);
                SDL_RenderDrawRect(carteSDL->renderer , &game1->rectSelect);
                SDL_RenderPresent(carteSDL->renderer);
            }
        }
        else{
            if(game1->select!=0){
                game1->select=0;
                if(0!=printMenuSave(carteSDL , game1 , game2 , game3)){
                    fprintf(stderr , "Erreur printMenuSave()\n");
                    quitterMenuSave(game1 , game2 , game3);
                    return -1;
                }
                SDL_RenderPresent(carteSDL->renderer);
            }
        }
        if(SDL_PointInRect(&mousePos , &game2->rectSelect)==SDL_TRUE){
            if(game2->select!=1){
                game2->select=1;
                SDL_SetRenderDrawColor(carteSDL->renderer , 0 , 0 , 0 , 255);
                SDL_RenderDrawRect(carteSDL->renderer  , &game2->rectSelect);
                SDL_RenderPresent(carteSDL->renderer);
            }
        }
        else{
            if(game2->select!=0){
                game2->select=0;
                if(0!=printMenuSave(carteSDL , game1 , game2 , game3)){
                    fprintf(stderr , "Erreur printMenuSave()\n");
                    quitterMenuSave(game1 , game2 , game3);
                    return -1;
                }
                SDL_RenderPresent(carteSDL->renderer);
            }
        }
        if(SDL_PointInRect(&mousePos , &game3->rectSelect)==SDL_TRUE){
            if(game3->select!=1){
                game3->select=1;
                SDL_SetRenderDrawColor(carteSDL->renderer , 0 , 0 , 0 , 255);
                SDL_RenderDrawRect(carteSDL->renderer  , &game3->rectSelect);
                SDL_RenderPresent(carteSDL->renderer);
            }
        }
        else{
            if(game3->select!=0){
                game3->select=0;
                if(0!=printMenuSave(carteSDL , game1 , game2 , game3)){
                    fprintf(stderr , "Erreur printMenuSave()\n");
                    quitterMenuSave(game1 , game2 , game3);
                    return -1;
                }
                SDL_RenderPresent(carteSDL->renderer);
            }
        }
    }
    quitterMenuSave(game1 , game2 , game3);
    return out;
}
int dessinerMenu(CarteSDL* carteSDL , SDL_Texture **menu , SDL_Rect *rectMenu ,
                Button *play , Button *quit , Button *load){
    SDL_Color colorfg={0 , 0 , 0 , 255} , colorbg={0 , 0 , 255 , 255};
    *menu=SDL_CreateTexture(carteSDL->renderer  , SDL_PIXELFORMAT_RGBA8888 , SDL_TEXTUREACCESS_TARGET , rectMenu->w , rectMenu->h);
    if(menu==NULL){
        fprintf(stderr , "Erreur SDL_CreateTexture : %s" , SDL_GetError());
        return -1;
    }
    if(0!=SDL_SetRenderTarget(carteSDL->renderer , *menu)){
        fprintf(stderr , "Erreur SDL_SetRenderTarget : %s" , SDL_GetError());
        return -1;
    }
    SDL_SetRenderDrawColor(carteSDL->renderer , 88 , 41 , 0 , 255);
    SDL_RenderClear(carteSDL->renderer);
    if(0!=ecrireTextSDL(carteSDL , "police/OpenSans-Regular.ttf" , "Quit" , 40 , &quit->text , &colorfg , NULL)){
        fprintf(stderr , "\nErreur SDL ttf");
        return -1;
    }
    SDL_QueryTexture(quit->text ,  NULL , NULL , &quit->rectText.w , &quit->rectText.h);
    quit->rectText.x=(rectMenu->w/4)*3-quit->rectText.w/2;
    quit->rectText.y=rectMenu->h/2-quit->rectText.h/2;
    if(0!=ecrireTextSDL(carteSDL , "police/OpenSans-Regular.ttf" , "New Game" , 40 , &play->text , &colorfg , NULL)){
        fprintf(stderr , "\nErreur SDL ttf");
        return -1;
    }
    SDL_QueryTexture(play->text , NULL , NULL , &play->rectText.w , &play->rectText.h);
    play->rectText.x=(rectMenu->w/4)*2-play->rectText.w/2;
    play->rectText.y=rectMenu->h/2-play->rectText.h/2;
    if(0!=ecrireTextSDL(carteSDL , "police/OpenSans-Regular.ttf" , "Load Game" , 40 , &load->text , &colorfg , NULL)){
        fprintf(stderr , "\nErreur SDL ttf");
        return -1;
    }
    SDL_QueryTexture(load->text , NULL , NULL , &load->rectText.w , &load->rectText.h);
    load->rectText.x=(rectMenu->w/4)*1
    -play->rectText.w/2;
    load->rectText.y=rectMenu->h/2-play->rectText.h/2;
    SDL_RenderCopy(carteSDL->renderer , quit->text , NULL , &quit->rectText);
    SDL_RenderCopy(carteSDL->renderer ,play->text , NULL , &play->rectText);
    SDL_RenderCopy(carteSDL->renderer ,load->text , NULL , &load->rectText);
    if(0!=SDL_SetRenderTarget(carteSDL->renderer , NULL)){
        fprintf(stderr , "Erreur SDL_SetRenderTarget : %s" , SDL_GetError());
        return -1;
    }
    SDL_RenderCopy(carteSDL->renderer , *menu , NULL , rectMenu);
    return 0;
}
int redessinerMenu(CarteSDL *carteSDL ,
                    SDL_Texture *menu , SDL_Texture *title ,
                    SDL_Rect *rectMenu , SDL_Rect *rectTitle ,
                    Button *play , Button *quit , Button *load){
    SDL_SetRenderDrawColor(carteSDL->renderer , 38 , 38 , 38, 255);
    SDL_RenderClear(carteSDL->renderer );
    if(0!=SDL_RenderCopy(carteSDL->renderer , title , NULL , rectTitle)){
        fprintf(stderr , "Erreur SDL_RenderCopy() : %s" , SDL_GetError());
        return -1;
    }
    if(0!=SDL_SetRenderTarget(carteSDL->renderer , menu)){
        fprintf(stderr , "Erreur SDL_SetRenderTarget() : %s" , SDL_GetError());
        return -1;
    }
    SDL_SetRenderDrawColor(carteSDL->renderer , 88 , 41 , 0 , 255);
    SDL_RenderClear(carteSDL->renderer);
    if(0!=SDL_SetRenderTarget(carteSDL->renderer , NULL)){
        fprintf(stderr , "Erreur SDL_SetRenderTarget() : %s" , SDL_GetError());
        return -1;
    }
    if(0!=SDL_RenderCopy(carteSDL->renderer , menu ,  NULL , rectMenu)){
        fprintf(stderr , "Erreur SDL_RenderCopy() : %s" , SDL_GetError());
        return -1;
    }
    if(0!=SDL_RenderCopy(carteSDL->renderer , play->text , NULL , &play->rectText)){
        fprintf(stderr , "Erreur SDL_RenderCopy() : %s" , SDL_GetError());
        return -1;
    }
    if(0!=SDL_RenderCopy(carteSDL->renderer , quit->text , NULL , &quit->rectText)){
        fprintf(stderr , "Erreur SDL_RenderCopy() : %s" , SDL_GetError());
        return -1;
    }
    if(0!=SDL_RenderCopy(carteSDL->renderer , load->text , NULL , &load->rectText)){
        fprintf(stderr , "Erreur SDL_RenderCopy() : %s" , SDL_GetError());
        return -1;
    }
    return 0;
    }
void quitterMenu(SDL_Texture *texture1 , SDL_Texture *texture2 ,
                Button *button1 , Button *button2 , Button *button3){
    if(texture1!=NULL){
        SDL_DestroyTexture(texture1);
    }
    if(texture2!=NULL){
        SDL_DestroyTexture(texture2);
    }
    if(button1!=NULL&&button2!=NULL&&button3!=NULL){
        if(button1->text!=NULL){
            SDL_DestroyTexture(button1->text);
        }
        if(button2->text!=NULL){
            SDL_DestroyTexture(button2->text);
        }
        if(button3->text!=NULL){
            SDL_DestroyTexture(button3->text);
        }
    free(button3);
    free(button1);
    free(button2);
    }
}
int menu(CarteSDL *carteSDL , int *choice){
    SDL_Texture *title=NULL , *menu=NULL;
    SDL_Color fontColor={255 , 255 , 255 , 255};
    SDL_Rect rectTitle={0 , 0 , 0 , 0} , rectMenu={0 , 0 , 0 , 0} ;
    Button *play=NULL , *quit=NULL , *load=NULL;
    SDL_Event event;
    SDL_Point mousePos={0 , 0};
    int w=0 , h=0 , continuer=1 , out=0;
    *choice=0;
    play=malloc(sizeof(Button));
    if(play==NULL){
        fprintf(stderr , "Erreur allocation memoire\n");
        quitterMenu(title , menu , quit , play , load);
        return -1;
    }
    quit=malloc(sizeof(Button));
    if(quit==NULL){
        fprintf(stderr , "Erreur allocation memoire\n");
        quitterMenu(title , menu , quit , play , load);
        return -1;
    }
    load=malloc(sizeof(Button));
    if(load==NULL){
        fprintf(stderr , "Erreur allocation memoire\n");
        quitterMenu(title , menu , quit , play , load);
        return -1;
    }
    if(0!=ecrireTextSDL(carteSDL , "police/OpenSans-Regular.ttf" , "Trapped Hero" , 200 , &title , &fontColor , NULL)){
        fprintf(stderr , "\nErreur SDL_ttf\n");
        quitterMenu(title , menu , quit , play , load);
        return -1;
    }
    SDL_GetWindowSize(carteSDL->window , &w , &h);
    rectMenu.x=0;
    rectMenu.y=h-200;
    rectMenu.w=w;
    rectMenu.h=200;
    SDL_SetRenderDrawColor(carteSDL->renderer , 38 , 38 , 38 , 38);
    SDL_RenderClear(carteSDL->renderer);
    SDL_QueryTexture(title , NULL , NULL , &rectTitle.w , &rectTitle.h);
    rectTitle.x=(w/2)-(rectTitle.w/2);
    rectTitle.y=((h-rectMenu.h)/2)-(rectTitle.h/2);
    SDL_RenderCopy(carteSDL->renderer  , title , NULL , &rectTitle);
    if(0!=dessinerMenu(carteSDL , &menu , &rectMenu , play , quit , load)){
        fprintf(stderr , "\nError print menu");
        quitterMenu(title , menu , quit , play , load);
        return -1;
    }
    /*Set absolute position*/
    play->rectText.y=play->rectText.y+(h-rectMenu.h);
    quit->rectText.y=quit->rectText.y+(h-rectMenu.h);
    load->rectText.y=load->rectText.y+(h-rectMenu.h);
    /*Set rect for select the button*/
    play->rectSelect.x=play->rectText.x-10;
    play->rectSelect.y=play->rectText.y-5;
    play->rectSelect.w=play->rectText.w+20;
    play->rectSelect.h=play->rectText.h+10;
    quit->rectSelect.x=quit->rectText.x-10;
    quit->rectSelect.y=quit->rectText.y-5;
    quit->rectSelect.w=quit->rectText.w+20;
    quit->rectSelect.h=quit->rectText.h+10;
    load->rectSelect.x=load->rectText.x-10;
    load->rectSelect.y=load->rectText.y-5;
    load->rectSelect.w=load->rectText.w+20;
    load->rectSelect.h=load->rectText.h+10;
    SDL_RenderPresent(carteSDL->renderer);
    while(continuer){
        if(SDL_PollEvent(&event)){
            switch(event.type){
                case SDL_KEYDOWN :
                    switch(event.key.keysym.sym){
                        case SDLK_c :
                            continuer=0;
                            break;
                    }
                    break;
                case SDL_MOUSEMOTION :
                    SDL_GetMouseState(&mousePos.x , &mousePos.y);
                    break;
                case SDL_MOUSEBUTTONDOWN :
                        if(play->select==1){
                            continuer=0;
                            out=PLAY;
                            *choice=menuSave(carteSDL);
                        }
                        if(quit->select==1){
                            continuer=0;
                            out=QUIT;
                        }
                        if(load->select==1){
                            continuer=0;
                            out=LOAD;
                            *choice=menuSave(carteSDL);
                        }
                        break;
            }
        }
        else{
            SDL_Delay(10);
        }
        if(SDL_PointInRect(&mousePos , &play->rectSelect)==SDL_TRUE){
            if(play->select!=1){
                play->select=1;
                SDL_SetRenderDrawColor(carteSDL->renderer , 0 , 0 , 0 , 255);
                SDL_RenderDrawRect(carteSDL->renderer , &play->rectSelect);
                SDL_RenderPresent(carteSDL->renderer);
            }
        }
        else if(SDL_PointInRect(&mousePos , &quit->rectSelect)==SDL_TRUE){
            if(quit->select!=1){
                quit->select=1;
                SDL_SetRenderDrawColor(carteSDL->renderer , 0 , 0 , 0 , 255);
                SDL_RenderDrawRect(carteSDL->renderer  , &quit->rectSelect);
                SDL_RenderPresent(carteSDL->renderer);
            }
        }
        else if(SDL_PointInRect(&mousePos , &load->rectSelect)==SDL_TRUE){
            if(load->select!=1){
                load->select=1;
                SDL_SetRenderDrawColor(carteSDL->renderer , 0 , 0 , 0 , 255);
                SDL_RenderDrawRect(carteSDL->renderer  , &load->rectSelect);
                SDL_RenderPresent(carteSDL->renderer);
            }
        }
        else{
            load->select=0;
            play->select=0;
            quit->select=0;
            if(0!=redessinerMenu(carteSDL , menu , title , &rectMenu , &rectTitle ,play , quit , load)){
                quitterMenu(title , menu , play , quit , load);
                fprintf(stderr , "Erreur redessinerMenu()");
                return -1;
            }
            SDL_RenderPresent(carteSDL->renderer);
        }
    }
    quitterMenu(title , menu , play , quit , load);
    return out;
}
