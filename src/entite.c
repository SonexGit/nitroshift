#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_mixer.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "entite.h"
#include "render.h"
#include "header.h"

/**
 * \file entite.c
 * \brief Programme qui gère toutes les entités
 * \author Allan Lucas Léo Enzo
 * \version 1.0
 * \date 10 avril 2021
*/

// ==============================================
// Personnage
// ==============================================

/**
  * \fn void creationPersonnage()
  * \brief Fonction qui permet de créer un personnage, les stats sont différentes en fonction de la classe choisie
*/
/* Création du personnage */
void creationPersonnage(){

    v1.classe = malloc(sizeof(char)*10);

    v1.id = 1;
    v1.equipe = ALLIES;
    v1.niveau = 1;
    v1.paMax = 6;
    v1.pmMax = 3;
    v1.experience = 0;
    v1.nitroDollars = 0;

    if(v1.etiquetteClasse == 10){ // Soldat
        v1.hpMax = 4000;
        v1.nitroMax = 100;
        v1.attaque = 30;
        v1.defense = 10;
    }
    else if(v1.etiquetteClasse == 20){ // Tank
        v1.hpMax = 200;
        v1.nitroMax = 100;
        v1.attaque = 15;
        v1.defense = 20;
    }
    else if(v1.etiquetteClasse == 30){ // Sniper
        v1.hpMax = 50;
        v1.nitroMax = 100;
        v1.attaque = 60;
        v1.defense = 2;
    }
    else if(v1.etiquetteClasse == 40){ // Assassin
        v1.hpMax = 80;
        v1.nitroMax = 100;
        v1.attaque = 60;
        v1.defense = 5;
    }
    rechercheClasse();
    creationAcces();
}

/**
  * \fn void free_classe_perso()
  * \brief Fonction qui permet de free la classe
*/
void free_classe_perso(){

    free(v1.classe);
}

/**
  * \fn void creationAcces()
  * \brief Fonction qui permet de créer les accès du personnage
*/
/* Accès ou non aux zones et niveaux par le personnage */
void creationAcces(){

    /* 0 = Non Accès */
    /* 1 = Accès */

    a1.zone1 = 1;
    a1.z1.niveau1 = 1; /* Cela signifie : Niveau 1 de la zone 1 par exemple */
    a1.z1.niveau2 = 0;
    a1.z1.niveau3 = 0;

    a1.zone2 = 0;
    a1.z2.niveau1 = 0;
    a1.z2.niveau2 = 0; /* Cela signifie : Niveau 2 de la zone 2 par exemple */
    a1.z2.niveau3 = 0;

    a1.zone3 = 0;
    a1.z3.niveau1 = 0;
    a1.z3.niveau2 = 0;
    a1.z3.niveau3 = 0;
}

/**
  * \fn void init_textures_personnage()
  * \brief Fonction qui permet d'initialiser la texture du personnage en fonction de la classe
*/
// Textures du personnage
void init_textures_personnage() {
    if(strcmp(v1.classe,"Soldat") == 0){
        v1.surface = IMG_Load("../data/personnages/personnageDPS.png");
    }
    else if(strcmp(v1.classe,"Tank") == 0){
        v1.surface = IMG_Load("../data/personnages/personnageTank.png");
    }
    else if(strcmp(v1.classe,"Sniper") == 0){
        v1.surface = IMG_Load("../data/personnages/personnageSniper.png");
    }
    else if(strcmp(v1.classe,"Assassin") == 0){
        v1.surface = IMG_Load("../data/personnages/personnageHealer.png");
    }

	v1.texture = SDL_CreateTextureFromSurface(ren, v1.surface);

	int i = 0, j = 0, k = 0;

	while (i < perso_col) {
		for(; j < perso_row; j++) {
			src_perso[j].w = 30;
			src_perso[j].h = 80;
			src_perso[j].x = j * src_perso[j].w;
			src_perso[j].y = i * src_perso[j].h;
			k++;
		}
		k = 0;
		i++;
	}
}

/**
  * \fn void dessiner_personnage(entite p, int case_x, int case_y, cell_T plat[plateau_y][plateau_x], int sprite)
  * \brief Fonction qui permet de dessiner le personnage sur le plateau
  * \param p de type entite, case_x et case_y de type int, plat de type cell_T et sprite de type int
*/
// Dessiner le personnage sur le plateau
void dessiner_personnage(entite p, int case_x, int case_y, cell_T plat[plateau_y][plateau_x], int sprite) {
	int pos_x, pos_y, img_w, img_h;
	img_w = p.surface->w;
	img_h = p.surface->h;
	pos_x = plat[case_y][case_x].pc.x - (img_w / (perso_row * 2));
	pos_y = plat[case_y][case_x].pc.y - img_h + 5;
	dest_perso.x = pos_x;
	dest_perso.y = pos_y;
	dest_perso.w = img_w / perso_row;
	dest_perso.h = img_h / perso_col;
	SDL_RenderCopy(ren, p.texture, &src_perso[sprite], &dest_perso);
}

/**
  * \fn void free_personnage_c()
  * \brief Fonction qui permet de détruire la surface et la texture du personnage
*/
// Free général des fonctions personnage
void free_personnage_c() {
	SDL_DestroyTexture(v1.texture);
	SDL_FreeSurface(v1.surface);
}

/**
  * \fn void deplacements_personnage(int direction)
  * \brief Fonction qui permet de déplacer un personnage sur le plateau
  * \param direction de type int
*/
// Déplacements du personnage
void deplacements_personnage(int direction) {
	/*
	printf("AVANT DEPLACEMENTS\n");
	for (int i = 0; i < plateau_x; i++) {
		for (int j = 0; j < plateau_y; j++) {
			printf("%d ", plateau[i][j].solide);
		}
		printf("\n");
	}
	*/
	if (v1.pm > 0) {
		switch (direction) {
			case UP:
				sprite = STAND_UP;
				if (!plateau[v1.positionY-1][v1.positionX].solide) {
					if (v1.positionY == 0 && v1.positionX == 14);
					else if (v1.positionY == 0);
					else {
						plateau[v1.positionY][v1.positionX].solide = 0;
						v1.positionY--;
						plateau[v1.positionY][v1.positionX].solide = 1;
					}
					v1.pm--;
				}
				break;
			case RIGHT:
				sprite = STAND_RIGHT;
				if (!plateau[v1.positionY][v1.positionX+1].solide) {
					if (v1.positionX == 14);
					else {
						plateau[v1.positionY][v1.positionX].solide = 0;
						v1.positionX++;
						plateau[v1.positionY][v1.positionX].solide = 1;
					}
					v1.pm--;
				}
				break;
			case DOWN:
				sprite = STAND_DOWN;
				if (!plateau[v1.positionY+1][v1.positionX].solide) {
					if (v1.positionY == 14);
					else {
						plateau[v1.positionY][v1.positionX].solide = 0;
						v1.positionY++;
						plateau[v1.positionY][v1.positionX].solide = 1;
					}
					v1.pm--;
				}
				break;
			case LEFT:
				sprite = STAND_LEFT;
				if (!plateau[v1.positionY][v1.positionX-1].solide) {
					if (v1.positionX == 0);
					else {
						plateau[v1.positionY][v1.positionX].solide = 0;
						v1.positionX--;
						plateau[v1.positionY][v1.positionX].solide = 1;
					}
					v1.pm--;
				}
				break;
		}
	}
	else {
		printf("v1 n'a plus de pm\n");
	}
	/*
	printf("APRES DEPLACEMENTS\n");
	for (int i = 0; i < plateau_x; i++) {
		for (int j = 0; j < plateau_y; j++) {
			printf("%d ", plateau[i][j].solide);
		}
		printf("\n");
	}
	*/
}

// ==============================================
// Ennemis
// ==============================================

/**
  * \fn void creationEnnemi()
  * \brief Fonction qui permet de créer les ennemis
*/
/* Création de l'ennemi */
void creationEnnemi(){

    e1.nom = "Vesta";
    e1.id = 101;
    e1.hpMax = 150;
    e1.nitroMax = 100;
    e1.paMax = 6;
    e1.pmMax = 3;
    e1.attaque = 20;
    e1.defense = 20;
    e1.flag = 0;
    e1.mort = 0;
    e1.equipe = ENNEMIS;

    e2.nom = "Chronos";
    e2.id = 102;
    e2.hpMax = 150;
    e2.nitroMax = 100;
    e2.paMax = 6;
    e2.pmMax = 3;
    e2.attaque = 20;
    e2.defense = 20;
    e2.flag = 0;
    e2.mort = 0;
    e2.equipe = ENNEMIS;

    e3.nom = "Lucifer";
    e3.id = 201;
    e3.hpMax = 250;
    e3.nitroMax = 100;
    e3.paMax = 6;
    e3.pmMax = 4;
    e3.attaque = 30;
    e3.defense = 30;
    e3.flag = 0;
    e3.mort = 0;
    e3.equipe = ENNEMIS;

    e4.nom = "Artemis";
    e4.id = 202;
    e4.hpMax = 250;
    e4.nitroMax = 100;
    e4.paMax = 6;
    e4.pmMax = 4;
    e4.attaque = 30;
    e4.defense = 30;
    e4.flag = 0;
    e4.mort = 0;
    e4.equipe = ENNEMIS;

    e5.nom = "Apollo";
    e5.id = 301;
    e5.hpMax = 350;
    e5.nitroMax = 100;
    e5.paMax = 9;
    e5.pmMax = 4;
    e5.attaque = 35;
    e5.defense = 50;
    e5.flag = 0;
    e5.mort = 0;
    e5.equipe = ENNEMIS;

    b1.nom = "Joker";
    b1.id = 100;
    b1.hpMax = 300;
    b1.nitroMax = 100;
    b1.paMax = 6;
    b1.pmMax = 4;
    b1.attaque = 25;
    b1.defense = 20;
    b1.flag = 0;
    b1.mort = 0;
    b1.equipe = ENNEMIS;

    b2.nom = "Scorpio";
    b2.id = 200;
    b2.hpMax = 400;
    b3.nitroMax = 150;
    b2.paMax = 6;
    b2.pmMax = 4;
    b2.attaque = 35;
    b2.defense = 30;
    b2.flag = 0;
    b2.mort = 0;
    b2.equipe = ENNEMIS;

    b3.nom = "Rudolf";
    b3.id = 300;
    b3.hpMax = 50;
    b3.nitroMax = 200;
    b3.paMax = 6;
    b3.pmMax = 5;
    b3.attaque = 45;
    b3.defense = 40;
    b3.flag = 0;
    b3.mort = 0;
    b3.equipe = ENNEMIS;
}

/**
  * \fn void init_textures_ennemis(int lev)
  * \brief Fonction qui permet d'initialiser les textures des ennemis en fonction du niveau de combat passé en paramètre
  * \param lev de type int
*/
// Textures des ennemis
void init_textures_ennemis(int lev) {

    switch(lev){
        case 1 :
            e1.surface = IMG_Load("../data/ennemis/ennemi1.png");
            e1.texture = SDL_CreateTextureFromSurface(ren, e1.surface);
            e2.surface = IMG_Load("../data/ennemis/ennemi2.png");
            e2.texture = SDL_CreateTextureFromSurface(ren, e2.surface);
            break;
        case 2 :
            e1.surface = IMG_Load("../data/ennemis/ennemi1.png");
            e1.texture = SDL_CreateTextureFromSurface(ren, e1.surface);
            e2.surface = IMG_Load("../data/ennemis/ennemi2.png");
            e2.texture = SDL_CreateTextureFromSurface(ren, e2.surface);
            break;
        case 3 :
            b1.surface = IMG_Load("../data/ennemis/boss1.png");
            b1.texture = SDL_CreateTextureFromSurface(ren, b1.surface);
            break;
        case 4 :
            e3.surface = IMG_Load("../data/ennemis/ennemi3.png");
            e3.texture = SDL_CreateTextureFromSurface(ren, e3.surface);
            e4.surface = IMG_Load("../data/ennemis/ennemi4.png");
            e4.texture = SDL_CreateTextureFromSurface(ren, e4.surface);
            break;
        case 5 :
            e3.surface = IMG_Load("../data/ennemis/ennemi3.png");
            e3.texture = SDL_CreateTextureFromSurface(ren, e3.surface);
            e4.surface = IMG_Load("../data/ennemis/ennemi4.png");
            e4.texture = SDL_CreateTextureFromSurface(ren, e4.surface);
            break;
        case 6 :
            b2.surface = IMG_Load("../data/ennemis/boss2.png");
            b2.texture = SDL_CreateTextureFromSurface(ren, b2.surface);
            break;
        case 7 :
            e4.surface = IMG_Load("../data/ennemis/ennemi6.png");
            e4.texture = SDL_CreateTextureFromSurface(ren, e4.surface);
            e5.surface = IMG_Load("../data/ennemis/ennemi5.png");
            e5.texture = SDL_CreateTextureFromSurface(ren, e5.surface);
            break;
        case 8 :
            e4.surface = IMG_Load("../data/ennemis/ennemi6.png");
            e4.texture = SDL_CreateTextureFromSurface(ren, e4.surface);
            e5.surface = IMG_Load("../data/ennemis/ennemi5.png");
            e5.texture = SDL_CreateTextureFromSurface(ren, e5.surface);
            break;
        case 9 :
            b3.surface = IMG_Load("../data/ennemis/boss3.png");
            b3.texture = SDL_CreateTextureFromSurface(ren, b3.surface);
            break;
        default :
            printf("Erreur du niveau : Impossible d'initialiser la surface et la texture de l'ennemi...\n");
    }

	int i = 0, j = 0, k = 0;

	while (i < ennemi_col) {
		for(; j < ennemi_row; j++) {
			src_ennemi[j].w = 40;
			src_ennemi[j].h = 80;
			src_ennemi[j].x = j * src_ennemi[j].w;
			src_ennemi[j].y = i * src_ennemi[j].h;
			k++;
		}
		k = 0;
		i++;
	}
}

/**
  * \fn void dessiner_ennemi(entite e, int case_x, int case_y, cell_T plat[plateau_y][plateau_x], int sprite)
  * \brief Fonction qui permet de dessiner l'ennemi sur le plateau
  * \param e de type entite, case_x et case_y de type int, plat de type cell_T et sprite de type int
*/
// Dessiner l'ennemi sur le plateau
void dessiner_ennemi(entite e, int case_x, int case_y, cell_T plat[plateau_y][plateau_x], int sprite) {

    if(e.mort == 0){
        int pos_x, pos_y, img_w, img_h;
        img_w = e.surface->w;
        img_h = e.surface->h;
        pos_x = plat[case_y][case_x].pc.x - (img_w / (ennemi_row * 2));
        pos_y = plat[case_y][case_x].pc.y - img_h + 5;
        dest_ennemi.x = pos_x;
        dest_ennemi.y = pos_y;
        dest_ennemi.w = img_w / ennemi_row;
        dest_ennemi.h = img_h / ennemi_col;

		int i = 0, j = 0, k = 0;
		int temp_w, temp_h;
		SDL_QueryTexture(e.texture, NULL, NULL, &temp_w, &temp_h);

		while (i < ennemi_col) {
			for(; j < ennemi_row; j++) {
				src_ennemi[j].w = temp_w / ennemi_row;
				src_ennemi[j].h = temp_h / ennemi_col;
				src_ennemi[j].x = j * src_ennemi[j].w;
				src_ennemi[j].y = i * src_ennemi[j].h;
				k++;
			}
			k = 0;
			i++;
		}

        SDL_RenderCopy(ren, e.texture, &src_ennemi[sprite], &dest_ennemi);
    }
}

/**
  * \fn void free_ennemi_c(int lev)
  * \brief Fonction qui permet de détruire la texture et la surface des ennemis en fonction du niveau de combat passé en paramètre
  * \param lev de type int
*/
// Free général des fonctions ennemis
void free_ennemi_c(int lev) {

    switch(lev){
        case 1 :
            SDL_DestroyTexture(e1.texture);
            SDL_FreeSurface(e1.surface);
            SDL_DestroyTexture(e2.texture);
            SDL_FreeSurface(e2.surface);
            break;
        case 2 :
            SDL_DestroyTexture(e1.texture);
            SDL_FreeSurface(e1.surface);
            SDL_DestroyTexture(e2.texture);
            SDL_FreeSurface(e2.surface);
            break;
        case 3 :
            SDL_DestroyTexture(b1.texture);
            SDL_FreeSurface(b1.surface);
            break;
        case 4 :
            SDL_DestroyTexture(e3.texture);
            SDL_FreeSurface(e3.surface);
            SDL_DestroyTexture(e4.texture);
            SDL_FreeSurface(e4.surface);
            break;
        case 5 :
            SDL_DestroyTexture(e3.texture);
            SDL_FreeSurface(e3.surface);
            SDL_DestroyTexture(e4.texture);
            SDL_FreeSurface(e4.surface);
            break;
        case 6 :
            SDL_DestroyTexture(b2.texture);
            SDL_FreeSurface(b2.surface);
            break;
        case 7 :
            SDL_DestroyTexture(e4.texture);
            SDL_FreeSurface(e4.surface);
            SDL_DestroyTexture(e5.texture);
            SDL_FreeSurface(e5.surface);
            break;
        case 8 :
            SDL_DestroyTexture(e4.texture);
            SDL_FreeSurface(e4.surface);
            SDL_DestroyTexture(e5.texture);
            SDL_FreeSurface(e5.surface);
            break;
        case 9 :
            SDL_DestroyTexture(b3.texture);
            SDL_FreeSurface(b3.surface);
            break;
    }
}

// Entités

/**
  * \fn void dessiner_entite(entite e, int case_x, int case_y, cell_T plat[plateau_y][plateau_x], int sprite)
  * \brief Fonction qui permet de dessiner une entite, si l'equipe est ALLIES on dessine le personnage et si l'equipe est ENNEMIS on dessingne l'ennemi
  * \param e de type entite, case_x et case_y de type int, plat de type cell_T et sprite de type int
*/
void dessiner_entite(entite e, int case_x, int case_y, cell_T plat[plateau_y][plateau_x], int sprite) {
	if (e.equipe == ALLIES) {
		dessiner_personnage(e, case_x, case_y, plat, sprite);
	}
	else if (e.equipe == ENNEMIS) {
		dessiner_ennemi(e, case_x, case_y, plat, 2); // il faudra remplacer 0 à un moment
	}
	else {
		// Ne rien faire
	}
}

/**
  * \fn void rechercheClasse()
  * \brief Fonction qui permet de déterminer la classe du personnage en fonction de l'étiquette
*/
void rechercheClasse(){
    if(v1.etiquetteClasse == 10){
        v1.classe = "Soldat";
    }
    else if(v1.etiquetteClasse == 20){
        v1.classe = "Tank";
    }
    else if(v1.etiquetteClasse == 30){
        v1.classe = "Sniper";
    }
    else if(v1.etiquetteClasse == 40){
        v1.classe = "Assassin";
    }
}

/**
  * \fn void gestionNiveaux(int niv)
  * \brief Fonction qui permet d'ajouter les stats en fonction du niveau du personnage (cette fonction est appelée lorsque le personnage a pris un niveau supplémentaire)
*/
// Niveaux
void gestionNiveaux(int niv){

    switch(niv){
        case 2 :
            v1.hpMax += 20;
            v1.nitroMax += 100;
            v1.attaque += 5;
            v1.defense += 5;
            break;
        case 3 :
            v1.hpMax += 20;
            v1.nitroMax += 100;
            v1.attaque += 5;
            v1.defense += 5;
            break;
        case 4 :
            v1.hpMax += 20;
            v1.nitroMax += 100;
            v1.attaque += 5;
            v1.defense += 5;
            break;
        case 5 :
            v1.hpMax += 20;
            v1.nitroMax += 100;
            v1.attaque += 5;
            v1.defense += 5;
            break;
        case 6 :
            v1.hpMax += 20;
            v1.nitroMax += 100;
            v1.attaque += 5;
            v1.defense += 5;
            break;
        case 7 :
            v1.hpMax += 20;
            v1.nitroMax += 100;
            v1.attaque += 5;
            v1.defense += 5;
            break;
        case 8 :
            v1.hpMax += 20;
            v1.nitroMax += 100;
            v1.attaque += 5;
            v1.defense += 5;
            break;
        case 9 :
            v1.hpMax += 20;
            v1.nitroMax += 100;
            v1.attaque += 5;
            v1.defense += 5;
            break;
        case 10 :
            v1.hpMax += 20;
            v1.nitroMax += 100;
            v1.attaque += 5;
            v1.defense += 5;
            break;
        default :
            printf("Erreur du niveau...\n");
            break;
    }
}

/**
  * \fn void levelUp()
  * \brief Fonction qui permet de vérifier si le personnage a pris un niveau supplémentaire en fonction de l'expérience
*/
void levelUp(){

    int maxExp[10] = {0, 100, 300, 700, 1300, 2100, 3100, 4300, 5700, 7300}; // Niveau de 1 à 10

    if(v1.experience > maxExp[v1.niveau]){
        printf("\n! LEVEL UP !\n");
        v1.niveau++;
        gestionNiveaux(v1.niveau);
        printf("Vous venez de passer niveau %i\n", v1.niveau);
        printf("Voici vos nouvelles statistiques :\n");
        printf("HP : %i\n", v1.hpMax);
        printf("Nitro : %i\n", v1.nitroMax);
        printf("Attaque : %i\n", v1.attaque);
        printf("Defense : %i\n", v1.defense);
    }
}
