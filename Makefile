all :  obj/Generateur_carte_alea.o obj/Generateur_chemin.o obj/Generateur_object.o obj/Generateur_salle_alea.o obj/Afficher_carte.o obj/enregistrer_carte.o obj/main.o obj/manage_SDL.o obj/menu.o obj/Move_character.o obj/listeObjet.o
		gcc obj/Generateur_carte_alea.o obj/Generateur_chemin.o obj/Generateur_object.o obj/Generateur_salle_alea.o obj/Afficher_carte.o obj/enregistrer_carte.o obj/main.o obj/manage_SDL.o obj/menu.o obj/Move_character.o obj/listeObjet.o -lSDL2main -lSDL2 -lSDL2_ttf -lSDL2_image -o bin/Trapped-Hero

obj/Generateur_carte_alea.o : src/generator/Generateur_carte_alea.c src/generator/Generateur_chemin.c src/generator/Generateur_object.c src/generator/Generateur_salle_alea.c src/Afficher_carte.c src/enregistrer_carte.c src/main.c src/manage_SDL.c src/menu.c src/Move_character.c src/listeObjet.c
		gcc -c src/generator/Generateur_carte_alea.c -o obj/Generateur_carte_alea.o

obj/Generateur_chemin.o : src/generator/Generateur_carte_alea.c src/generator/Generateur_chemin.c src/generator/Generateur_object.c src/generator/Generateur_salle_alea.c src/Afficher_carte.c src/enregistrer_carte.c src/main.c src/manage_SDL.c src/menu.c src/Move_character.c src/listeObjet.c
		gcc -c src/generator/Generateur_chemin.c -o obj/Generateur_chemin.o

obj/Generateur_object.o : src/generator/Generateur_carte_alea.c src/generator/Generateur_chemin.c src/generator/Generateur_object.c src/generator/Generateur_salle_alea.c src/Afficher_carte.c src/enregistrer_carte.c src/main.c src/manage_SDL.c src/menu.c src/Move_character.c src/listeObjet.c
		gcc -c src/generator/Generateur_object.c -o obj/Generateur_object.o

obj/Generateur_salle_alea.o : src/generator/Generateur_carte_alea.c src/generator/Generateur_chemin.c src/generator/Generateur_object.c src/generator/Generateur_salle_alea.c src/Afficher_carte.c src/enregistrer_carte.c src/main.c src/manage_SDL.c src/menu.c src/Move_character.c src/listeObjet.c
		gcc -c src/generator/Generateur_salle_alea.c -o obj/Generateur_salle_alea.o

obj/Afficher_carte.o : src/generator/Generateur_carte_alea.c src/generator/Generateur_chemin.c src/generator/Generateur_object.c src/generator/Generateur_salle_alea.c src/Afficher_carte.c src/enregistrer_carte.c src/main.c src/manage_SDL.c src/menu.c src/Move_character.c src/listeObjet.c
		gcc -c src/Afficher_carte.c -o obj/Afficher_carte.o

obj/enregistrer_carte.o : src/generator/Generateur_carte_alea.c src/generator/Generateur_chemin.c src/generator/Generateur_object.c src/generator/Generateur_salle_alea.c src/Afficher_carte.c src/enregistrer_carte.c src/main.c src/manage_SDL.c src/menu.c src/Move_character.c src/listeObjet.c
		gcc -c src/enregistrer_carte.c -o obj/enregistrer_carte.o

obj/main.o : src/generator/Generateur_carte_alea.c src/generator/Generateur_chemin.c src/generator/Generateur_object.c src/generator/Generateur_salle_alea.c src/Afficher_carte.c src/enregistrer_carte.c src/main.c src/manage_SDL.c src/menu.c src/Move_character.c src/listeObjet.c
		gcc -c src/main.c -o obj/main.o

obj/manage_SDL.o : src/generator/Generateur_carte_alea.c src/generator/Generateur_chemin.c src/generator/Generateur_object.c src/generator/Generateur_salle_alea.c src/Afficher_carte.c src/enregistrer_carte.c src/main.c src/manage_SDL.c src/menu.c src/Move_character.c src/listeObjet.c
		gcc -c src/manage_SDL.c -o obj/manage_SDL.o

obj/menu.o : src/generator/Generateur_carte_alea.c src/generator/Generateur_chemin.c src/generator/Generateur_object.c src/generator/Generateur_salle_alea.c src/Afficher_carte.c src/enregistrer_carte.c src/main.c src/manage_SDL.c src/menu.c src/Move_character.c src/listeObjet.c
		gcc -c src/menu.c -o obj/menu.o

obj/Move_character.o : src/generator/Generateur_carte_alea.c src/generator/Generateur_chemin.c src/generator/Generateur_object.c src/generator/Generateur_salle_alea.c src/Afficher_carte.c src/enregistrer_carte.c src/main.c src/manage_SDL.c src/menu.c src/Move_character.c src/listeObjet.c
		gcc -c src/Move_character.c -o obj/Move_character.o
obj/listeObjet.o : src/generator/Generateur_carte_alea.c src/generator/Generateur_chemin.c src/generator/Generateur_object.c src/generator/Generateur_salle_alea.c src/Afficher_carte.c src/enregistrer_carte.c src/main.c src/manage_SDL.c src/menu.c src/Move_character.c src/listeObjet.c
		gcc -c src/listeObjet.c -o obj/listeObjet.o

#Cleanage des fichiers objets
clean:
		rm -rf obj/*.o


#Suppression du fichier executable
mrproper: clean
		rm -rf Trapped-Hero
