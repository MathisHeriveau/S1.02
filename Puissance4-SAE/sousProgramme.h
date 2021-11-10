/**
 * @file sousProgramme.h
 * @author Mathis Heriveau
 * @brief Fichier d'entête du module sousProgramme
 * @date 27 octobre 2021
 */
#ifndef SOUSPROGRAMME_H
#define SOUSPROGRAMME_H

#include <windows.h> // pour afficher du texte en couleur
#include <iostream>
using namespace std;


/**
 * @brief Permettre de jouer au puissance 4 avec un ami
 *
 * @param [in] joueur1 la couleur du joueur numero 1
 * @param [in] joueur2 la couleur du joueur numero 2
 * 
 */
void jeuDuo(unsigned short int joueur1, unsigned short int joueur2, string NomJoueurUn, string NomJoueurDeux);


/**
 * @brief Permettre de modifier la couleur du titre, des joueur et de la console
 *
 * @param [in] joueur1 la couleur du joueur numero 1
 * @param [in] joueur2 la couleur du joueur numero 2
 * 
 */
void option(unsigned short int& joueur1, unsigned short int& joueur2);

//! DECLARATION DES TYPES ENUMERE
//!-------------------------------------------------------

/**
 * @brief Liste de couleurs utilisables avec les
 * procedures #afficherTexteEnCouleur
 *
 */
enum Couleur
{
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

//! DECLARATION DES SOUS-PROGRAMMES
//!-------------------------------------------------------

/**
 * @brief Permet d'afficher l'interface
 *
 * @param [in] tableau le tableau de taille 6x7 qui va etre afficher 
 * 
 */
void afficherJeu(unsigned short int tableau[6][7], unsigned short int joueur1, unsigned short int joueur2);


/**
 * @brief Permet d'afficher l'interface
 *
 * @param [in] couleur la couleur du joueur
 * 
 */
void afficherOcouleur(unsigned short int couleur);

/**
 * @brief Permet d'afficher l'interface
 *
 * @param [in] couleur la couleur du joueur
 * 
 */
void afficherCouleurJoueur(unsigned short int couleur);

/**
 * 
 * @brief Permet d'afficher le titre
 * 
 */
void afficherTitre();

/**
 * @brief Permet d'afficher une chaine de caractères en couleur.
 *
 * @param [in] chaine la chaine à afficher.
 * @param [in] couleur la couleur à utiliser pour afficher la chaine. La couleur doit faire partie
 * des valeurs proposées par le type #Couleur
 * @param [in] retourALaLigne indique si l'affichage de la chaine doit être suivi d'un
 * retour à la ligne (true) ou pas (false).
 */
void afficherTexteEnCouleur(string chaine, Couleur couleur, bool retourALaLigne = false);


/**
 * @brief Permet de verifier la ligne horizontale/verticale et la diagonale gauche/droite
 *
 * @param [in] ligne permet de localisé la diagonal a verifier
 * @param [in] colonne permet de localisé la diagonal a verifier
 * @param [in] nombreAverifier Comme chaque joueur a un numero, on verifiera qu'un seul joueur a la fois
 * @param [in] tableau le tableau contenant toutes les informations du jeu
 */
void verificationJeu(unsigned short int colonne, unsigned short int ligne, unsigned short int nombreAverifier, unsigned short int tableau[6][7], bool& etatVerification, string& nomDeLaVerif);


/**
 * @brief Permet de verifier si la ligne horizontal est gagnante pour le joueur 1 ou 2
 *
 * @param [in] ligne le numero de la ligne a verifier
 * @param [in] nombreAverifier Comme chaque joueur a un numero, on verifiera qu'un seul joueur a la fois
 * @param [in] tableau le tableau contenant toutes les informations du jeu
 */
bool verificationHorizontale(unsigned short int ligne, unsigned short int nombreAverifier, unsigned short int tableau[6][7]);

/**
 * @brief Permet de verifier si la ligne vertical est gagnante pour le joueur 1 ou 2
 *
 * @param [in] colonne le numero de la colonne a verifier
 * @param [in] nombreAverifier Comme chaque joueur a un numero, on verifiera qu'un seul joueur a la fois
 * @param [in] tableau le tableau contenant toutes les informations du jeu
 */
bool verificationVertical(unsigned short int colonne, unsigned short int nombreAverifier, unsigned short int tableau[6][7]);


/**
 * @brief Permet la verification de la diagonal de haut en bas de gauche a droite
 *
 * @param [in] ligne permet de localisé la diagonal a verifier
 * @param [in] colonne permet de localisé la diagonal a verifier
 * @param [in] nombreAverifier Comme chaque joueur a un numero, on verifiera qu'un seul joueur a la fois
 * @param [in] tableau le tableau contenant toutes les informations du jeu
 */
bool verificationDiagonalDroite(unsigned short int colonne, unsigned short int ligne, unsigned short int nombreAverifier, unsigned short int tableau[6][7]);


/**
 * @brief Permet la verification de la diagonal de haut en bas de droite a gauche
 *
 * @param [in] ligne permet de localisé la diagonal a verifier
 * @param [in] colonne permet de localisé la diagonal a verifier
 * @param [in] nombreAverifier Comme chaque joueur a un numero, on verifiera qu'un seul joueur a la fois
 * @param [in] tableau le tableau contenant toutes les informations du jeu
 */
bool verificationDiagonalGauche(unsigned short int colonne, unsigned short int ligne, unsigned short int nombreAverifier, unsigned short int tableau[6][7]);





#endif
