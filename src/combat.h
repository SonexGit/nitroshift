#ifndef _COMBAT_H_
#define _COMBAT_H_

#include "header.h"

/* Fonctions */
void boutonPasserTour();
void statsMaximum(entite * e);
int estUnBoss(entite * e);
int recherchePorteeSort(entite * e);
int rechercheDegatSort(entite * e);
int rechercheCoutNitroSort(entite * e);
int rechercheCoutPaBoost(entite * e);
int rechercheRelanceBoost(entite * e);
int boostEnnemi(entite * e);
void attaqueEnnemi(entite * e);
void iaEnnemi(entite * e);
void actionEnnemi(entite * e);
void tourPersonnage(entite * ee1, entite * ee2);
void deroulementCombat(int level);

#endif // _COMBAT_H_