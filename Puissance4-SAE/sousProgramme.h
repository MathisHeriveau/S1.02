/**\
  * @file sousProgramme.h
  * @author Mathis Heriveau, Tom Planche
  * @brief Fichier d'entête du module sousProgramme
  * @date 27-10-2021
  * 
\**/


#ifndef SOUSPROGRAMME_H
#define SOUSPROGRAMME_H



// . Importation Des Bibliothèques Nécessaires
# if defined(WIN32) || defined(_WIN32) || defined(__WIN32) 
    #include <windows.h>
# endif

#include <iostream>
#include <regex>
#include <chrono>

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::flush;
using std::regex;

using namespace std::chrono;


//.  ------------------------------ DECLARATION DES TYPES ENUMERE ----------------------------------

/**\
  * @brief Tous les différents cas pour une case.
  * Utilisé dans les procédures suivantes :
  *     afficherJeu
  *     verificationVerticale
  *     verificationHorizontale
  *     verificationDiagonalGauche
  *     verificationDiagonalDroite
  * 
\**/
enum Case {
    caseVide = 0,
    pionJaune,
    pionRouge
};


/**\
  * @brief Tous les différents cas de victoire.
  * 
\**/
enum TypeDeVictoire {
    horizontalement,
    verticalement,
    diagonalement
};


/**\
  * @brief Différents cas pour une couleur
  * Utilisé dans la procédure afficherTexteEnCouleur
  * 
\**/
enum Couleur {
    /** La couleur gris a pour code couleur 7*/
    gris = 7,
    /** La couleur bleu a pour code couleur 9*/
    bleu = 9,
    /** La couleur vert a pour code couleur 10*/
    vert = 10,
    /** La couleur cyan a pour code couleur 11*/
    cyan = 11,
    /** La couleur rouge a pour code couleur 12*/
    rouge = 12,
    /** La couleur violet a pour code couleur 13*/
    violet = 13,
    /** La couleur jaune a pour code couleur 14*/
    jaune = 14,
    /** La couleur blanc a pour code couleur 15*/
    blanc = 15
};


//.  ----------------------------- DECLARATION DES SOUS-PROGRAMMES ---------------------------------

/**\
  * @brief Permet d'afficher la grille de jeu.
  * 
  * @param tableau tableau entier du jeu.
\**/
void afficherJeu(Case tableau[6][7]);


/**\
  * @brief Affiche le titre "puissance 4" en couleur.
  * 
\**/
void afficherTitre();


/**\
  * @brief Permet d'afficher une chaîne de caractères en couleur
  * 
  * @param chaine Chaîne de caractère à afficher.
  * @param couleur Couleur à utiliser pour afficher la chaîne. Doit faire partie du type Couleur défini au dessus.
  * @param retourALaLigne Définit sur false, si true ajoute un retour à la ligne.
\**/
void afficherTexteEnCouleur(string chaine, Couleur couleur, bool retourALaLigne = false);


/**\
  * @brief Efface le terminal
  * 
\**/
void effacer();


/**\
  * @brief Retourne un nombre aléatoire entre min et max.
  * 
  * @param min Borne basse.
  * @param max Borne haute.
  * @return int Entier choisi aléatoirement entre min et max.
\**/
int random(int min, int max);


/**\
  * @brief Permet la saisie et véfification d'un numéro de case (entier compris entre 0 et 6 inclus).
  * 
  * @return unsigned short int numéro de case bien saisi.
\**/
unsigned short int saisieVerifCase();


/**\
  * @brief Permet de verifier si la ligne horizontal est gagnante pour le joueur 1 ou 2.
  * 
  * @param ligne Numéro de la ligne à vérifier.
  * @param caseDuJeu Dernière case jouée.
  * @param tableau Tableau entier du jeu.
  * @return true Quatres pions sont alignés horizontalement sur la ligne.
  * @return false Il n'y a pas quatres pions alignés dans cette ligne.
\**/
bool verificationHorizontale(unsigned short int ligne, Case caseDuJeu, Case tableau[6][7]);


/**\
  * @brief Permet de vérifier si il y a quatre pions alignés dans la colonne indiquée.
  * 
  * @param colonne numéro de la colonne à vérifier.
  * @param caseDuJeu Dernière case jouée
  * @param tableau tableau entier du jeu
  * @return true Quatres pions sont alignés verticalement, fin de la partie.
  * @return false Il n'y a pas de pions alignés verticalement.
\**/
bool verificationVerticale(unsigned short int colonne, Case caseDuJeu, Case tableau[6][7]);


/**\
  * @brief Permet une vérification diagonale d'en haut à droite vers en bas à gauche.
  * 
  * @param colonne cooronée sur x de la diagonale à vérifier
  * @param ligne cooronée sur y de la diagonale à vérifier
  * @param caseDuJeu dernière case en jeu
  * @param tableau tableau entier du jeu
  * @return true Quatres pions sont alignés diagonalement, fin de la partie.
  * @return false Il n'y a pas de pions alignés diagonalement.
\**/
bool verificationDiagonaleDroite(unsigned short int colonne, unsigned short int ligne, Case caseDuJeu, Case tableau[6][7]);


/**\
  * @brief Permet une vérification diagonale d'en haut à gauche vers en bas à droite.
  * 
  * @param colonne cooronée sur x de la diagonale à vérifier
  * @param ligne cooronée sur y de la diagonale à vérifier
  * @param caseDuJeu dernière case en jeu
  * @param tableau tableau entier du jeu
  * @return true Quatres pions sont alignés diagonalelent, fin de la partie.
  * @return false Il n'y a pas de pions alignés diagonalement.
\**/
bool verificationDiagonaleGauche(unsigned short int colonne, unsigned short int ligne, Case caseDuJeu, Case tableau[6][7]);





#endif
