#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_mixer.h"
#include "SDL2/SDL_ttf.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "header.h"
#include "render.h"
#include "entite.h"
#include "sorts.h"
#include "initialisation.h"
#include "combat.h"
#include "mesmodif.h"
#include "pile.h"
#include "shifumi.h"
#include "menujeu.h"
#include "amelioration.h"
#include "shop.h"

 /**
   *\file perdu.c
  * \author lucas allan leo enzo
  * \version 1.0
  * \brief programme contenant la fonction si l'on perd un combat
  * \date 19 avril 2021
   */

  ///Initialisation des images avec une texture\n
  ///positionnement des images et de la musique\n
  ///annonce de fin combat avec comme choix un retour au menu principal\n


  /**
   * \fn void findujeu(void)
   * \brief fonction qui permet de créer la fenetre de fin de combat lors d'une défaite
   * \param aucun parametre
   * \return la fenetre avec la musique, une image et un bouton retour
   */

void findujeu()
{
  SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
  SDL_RenderClear(ren);
  SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
    Mix_Music *myMus;

    /* On initialise le son */
    SDL_Init(SDL_INIT_AUDIO);

    /* On ouvre un device audio */
    Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 1024);
    Mix_VolumeMusic(MIX_MAX_VOLUME / 40);
    /* On charge un fichier musical */
    myMus = Mix_LoadMUS("../data/music/Coffin-Dance.mp3");

    /* On lance la musique */
    Mix_PlayMusic(myMus, 1);

    if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 1024) == -1) //Initialisation de l'API Mixer
    {
        printf("%s", Mix_GetError());
    }



    SDL_Surface *icon = IMG_Load("../data/icon.png");
    SDL_SetWindowIcon(win, icon);

    SDL_Surface *surface_perdu = IMG_Load("../data/combat/test.png");
    SDL_Texture *texture_perdu = SDL_CreateTextureFromSurface(ren, surface_perdu);

    SDL_Surface *imageretour = NULL;
    SDL_Texture *textureretour = NULL;

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

    if (surface_perdu == NULL)
    {
        SDL_DestroyRenderer(ren);
        SDL_DestroyWindow(win);
        SDLError("Erreur lors du chargement de l'image");
    }
    texture_perdu = SDL_CreateTextureFromSurface(ren, surface_perdu);

    //libération de la surface car plus besoin
    SDL_FreeSurface(surface_perdu);

    if (texture_perdu == NULL)
    {
        SDL_DestroyRenderer(ren);
        SDL_DestroyWindow(win);
        SDLError("Erreur lors de la création de la texture bouton abandon");
    }
    //l'image est chargé en mémoire

    //chargement de la texture
    SDL_Rect rectangleperdu;
    if (SDL_QueryTexture(texture_perdu, NULL, NULL, &rectangleperdu.w, &rectangleperdu.h) != 0)
    {
        SDL_DestroyRenderer(ren);
        SDL_DestroyWindow(win);
        SDLError("Erreur lors de l'affichage de l'image");
    }
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
    //positionnement du bouton
    rectangleperdu.x = 300;
    rectangleperdu.y = 150;
    rectangleperdu.w = surface_perdu->w / 1.2;
    rectangleperdu.h = surface_perdu->h / 1.2;
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
    //affichage de l'image
    if (SDL_RenderCopy(ren, texture_perdu, NULL, &rectangleperdu) != 0)
    {
        SDL_DestroyRenderer(ren);
        SDL_DestroyWindow(win);
        SDLError("Erreur lors de l'affichage de l'image");
    }

    SDL_RenderPresent(ren);

    SDL_Surface *imageperdant = NULL;
    SDL_Texture *textureperdant = NULL;

    imageperdant = IMG_Load("../data/combat/perdant.png");
    if (imageperdant == NULL)
    {
        SDL_DestroyRenderer(ren);
        SDL_DestroyWindow(win);
        SDLError("Erreur lors du chargement de l'image");
    }
    textureperdant = SDL_CreateTextureFromSurface(ren, imageperdant);

    //libération de la surface car plus besoin
    SDL_FreeSurface(imageperdant);

    if (textureperdant == NULL)
    {
        SDL_DestroyRenderer(ren);
        SDL_DestroyWindow(win);
        SDLError("Erreur lors de la création de la texture bouton abandon");
    }
    //l'image est chargé en mémoire

    //chargement de la texture
    SDL_Rect rectangleperdant;
    if (SDL_QueryTexture(textureperdant, NULL, NULL, &rectangleperdant.w, &rectangleperdant.h) != 0)
    {
        SDL_DestroyRenderer(ren);
        SDL_DestroyWindow(win);
        SDLError("Erreur lors de l'affichage de l'image");
    }

    //positionnement du bouton
    rectangleperdant.x = 650;
    rectangleperdant.y = 20;
    //
    //affichage de l'image
    if (SDL_RenderCopy(ren, textureperdant, NULL, &rectangleperdant) != 0)
    {
        SDL_DestroyRenderer(ren);
        SDL_DestroyWindow(win);
        SDLError("Erreur lors de l'affichage de l'image");
    }

    SDL_RenderPresent(ren);
    imageretour = IMG_Load("../data/menu/bouton_retour.png");
    if (imageretour == NULL)
    {
        SDL_DestroyRenderer(ren);
        SDL_DestroyWindow(win);
        SDLError("Erreur lors du chargement de l'image");
    }
    textureretour = SDL_CreateTextureFromSurface(ren, imageretour);

    //libération de la surface car plus besoin
    SDL_FreeSurface(imageretour);

    if (textureretour == NULL)
    {
        SDL_DestroyRenderer(ren);
        SDL_DestroyWindow(win);
        SDLError("Erreur lors de la création de la texture bouton abandon");
    }
    //l'image est chargé en mémoire

    //chargement de la texture
    SDL_Rect rectangleretour;
    if (SDL_QueryTexture(textureretour, NULL, NULL, &rectangleretour.w, &rectangleretour.h) != 0)
    {
        SDL_DestroyRenderer(ren);
        SDL_DestroyWindow(win);
        SDLError("Erreur lors de l'affichage de l'image");
    }

    //positionnement du bouton
    rectangleretour.x = 20;
    rectangleretour.y = 10;
    //
    //affichage de l'image
    if (SDL_RenderCopy(ren, textureretour, NULL, &rectangleretour) != 0)
    {
        SDL_DestroyRenderer(ren);
        SDL_DestroyWindow(win);
        SDLError("Erreur lors de l'affichage de l'image");
    }

    SDL_RenderPresent(ren);
    SDL_bool mouse_hover = SDL_FALSE;
    int continuer = 3;
    SDL_Event event;
    int clicx;
    int clicy;

    while (continuer)
    {
        while (SDL_PollEvent(&event))
        {

            switch (event.type)
            {
            case SDL_QUIT:
                SDL_DestroyRenderer(ren);
                SDL_DestroyWindow(win);
                break;
            //gestion clavier
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym)
                {
                case SDLK_ESCAPE:
                    SDL_DestroyRenderer(ren);
                    SDL_DestroyWindow(win);
                    break;

                default:
                    break;
                }
            case SDL_MOUSEBUTTONDOWN:
                if (event.button.x >= 20 && event.button.x <= 221 && event.button.y >= 600 && event.button.y <= 639)
                {
                    /*texte = TTf_RenderText_Blended(police,"Bienvenue a vous joueur de Nitroshift");

                  positionTxt.x=500;
                  positionTxt.y=600;
                  SDL_BlitSurface(texte,NULL,ren,&positionTxt);
                  SDL_Flip(ren);
*/

                    printf("Bienvenue a vous joueur de Nitroshift,\n");
                    printf("Ce jeu a ete cree par Leo Trottier, Allan Vannier, Enzo Rault et Lucas Renard.\n");
                    printf("Voici les regles du jeu:\n");
                    printf("Vous allez choisir un niveau allant de 1 a 4 avec comme niveau 1 la difficulte sera plus faible que celle du niveau 4.\n");
                    printf("Pour chaque niveau, vous allez avoir 3 combat avec des monstres et un 4eme combat sera le boss du niveau.\n");
                    printf("L'equipe de Nitroshift\n");
                }
                if (event.button.x >= 20 && event.button.x <= 162 && event.button.y >= 10 && event.button.y <= 101)
                {
                    SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
                    SDL_RenderClear(ren);
                    SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
                    showmenu();
                }
                if (event.button.x >= 0 && event.button.x <= 380 && event.button.y >= 250 && event.button.y <= 322)
                {
                    Mix_FreeMusic(myMus);
                    Mix_CloseAudio();
                    Mix_Quit();
                    SDL_RenderClear(ren);
                    showtest();
                }
                if (event.button.x >= 1250 && event.button.x <= 1378 && event.button.y >= 375 && event.button.y <= 426)
                {
                    SDL_RenderClear(ren);
                    showshop();
                }
                break;
            }
        }
    }

    SDL_DestroyTexture(texture_perdu);
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);

    /* La musique est terminée, on la libère */
    Mix_FreeMusic(myMus);
    /* On libère le matériel */
    Mix_CloseAudio();
    Mix_Quit();

    SDL_Quit();

    return EXIT_SUCCESS;
}
