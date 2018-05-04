all :  Generateur_carte_alea.o Generateur_chemin.o Generateur_object.o Generateur_salle_alea.o Afficher_carte.o enregistrer_carte.o main.o manage_SDL.o menu.o Move_character.o
		gcc Generateur_carte_alea.o Generateur_chemin.o Generateur_object.o Generateur_salle_alea.o Afficher_carte.o enregistrer_carte.o main.o manage_SDL.o menu.o Move_character.o -lSDL2main -lSDL2 -lSDL2_ttf -lSDL2_image -o bin/Trapped-Hero

Generateur_carte_alea.o : src/generator/Generateur_carte_alea.c src/generator/Generateur_chemin.c src/generator/Generateur_object.c src/generator/Generateur_salle_alea.c src/Afficher_carte.c src/enregistrer_carte.c src/main.c src/manage_SDL.c src/menu.c src/Move_character.c
		gcc -c src/generator/Generateur_carte_alea.c -o Generateur_carte_alea.o

Generateur_chemin.o : src/generator/Generateur_carte_alea.c src/generator/Generateur_chemin.c src/generator/Generateur_object.c src/generator/Generateur_salle_alea.c src/Afficher_carte.c src/enregistrer_carte.c src/main.c src/manage_SDL.c src/menu.c src/Move_character.c
		gcc -c src/generator/Generateur_chemin.c -o Generateur_chemin.o

Generateur_object.o : src/generator/Generateur_carte_alea.c src/generator/Generateur_chemin.c src/generator/Generateur_object.c src/generator/Generateur_salle_alea.c src/Afficher_carte.c src/enregistrer_carte.c src/main.c src/manage_SDL.c src/menu.c src/Move_character.c
		gcc -c src/generator/Generateur_object.c -o Generateur_object.o

Generateur_salle_alea.o : src/generator/Generateur_carte_alea.c src/generator/Generateur_chemin.c src/generator/Generateur_object.c src/generator/Generateur_salle_alea.c src/Afficher_carte.c src/enregistrer_carte.c src/main.c src/manage_SDL.c src/menu.c src/Move_character.c
		gcc -c src/generator/Generateur_salle_alea.c -o Generateur_salle_alea.o

Afficher_carte.o : src/generator/Generateur_carte_alea.c src/generator/Generateur_chemin.c src/generator/Generateur_object.c src/generator/Generateur_salle_alea.c src/Afficher_carte.c src/enregistrer_carte.c src/main.c src/manage_SDL.c src/menu.c src/Move_character.c
		gcc -lSDL2 -lSDL2main -lSDL2_ttf -lSDL2_image -c src/Afficher_carte.c -o Afficher_carte.o

enregistrer_carte.o : src/generator/Generateur_carte_alea.c src/generator/Generateur_chemin.c src/generator/Generateur_object.c src/generator/Generateur_salle_alea.c src/Afficher_carte.c src/enregistrer_carte.c src/main.c src/manage_SDL.c src/menu.c src/Move_character.c
		gcc -lSDL2 -lSDL2main -lSDL2_ttf -lSDL2_image -c src/enregistrer_carte.c -o enregistrer_carte.o

main.o : src/generator/Generateur_carte_alea.c src/generator/Generateur_chemin.c src/generator/Generateur_object.c src/generator/Generateur_salle_alea.c src/Afficher_carte.c src/enregistrer_carte.c src/main.c src/manage_SDL.c src/menu.c src/Move_character.c
		gcc -lSDL2 -lSDL2main -lSDL2_ttf -lSDL2_image -c src/main.c -o main.o

manage_SDL.o : src/generator/Generateur_carte_alea.c src/generator/Generateur_chemin.c src/generator/Generateur_object.c src/generator/Generateur_salle_alea.c src/Afficher_carte.c src/enregistrer_carte.c src/main.c src/manage_SDL.c src/menu.c src/Move_character.c
		gcc -lSDL2 -lSDL2main -lSDL2_ttf -lSDL2_image -c src/manage_SDL.c -o manage_SDL.o

menu.o : src/generator/Generateur_carte_alea.c src/generator/Generateur_chemin.c src/generator/Generateur_object.c src/generator/Generateur_salle_alea.c src/Afficher_carte.c src/enregistrer_carte.c src/main.c src/manage_SDL.c src/menu.c src/Move_character.c
		gcc -lSDL2 -lSDL2main -lSDL2_ttf -lSDL2_image -c src/menu.c -o menu.o

Move_character.o : src/generator/Generateur_carte_alea.c src/generator/Generateur_chemin.c src/generator/Generateur_object.c src/generator/Generateur_salle_alea.c src/Afficher_carte.c src/enregistrer_carte.c src/main.c src/manage_SDL.c src/menu.c src/Move_character.c
		gcc -lSDL2 -lSDL2main -lSDL2_ttf -lSDL2_image -c src/Move_character.c -o Move_character.o


#Cleanage des fichiers objets
clean:
		rm -rf *.o


#Suppression du fichier executable
mrproper: clean
		rm -rf Trapped-Hero
