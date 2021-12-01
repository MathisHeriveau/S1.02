/**
 * @file sousProgramme.h
 * @author Mathis Heriveau, Tom Planche
 * @brief Fichier d'entête du module sousProgramme
 * @date 27 octobre 2021
 * todo dire les procédures l.46
 */
#ifndef SOUSPROGRAMME_H
#define SOUSPROGRAMME_H



// . Importation Des Bibliothèques Nécessaires
#include <windows.h> // pour afficher du texte en couleur
#include <iostream>


using namespace std;


//.  ------------------------------ DECLARATION DES TYPES ENUMERE ----------------------------------

/**
 * @brief Liste des possibilitées de case
 * procedures // todo dire les procédures
 */

enum Case
{
    caseVide = 0,
    pionJaune,
    pionRouge
};

enum TypeDeVictoire{
    horizontalement,
    verticalement,
    diagonalement
};

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

//.  ----------------------------- DECLARATION DES SOUS-PROGRAMMES ---------------------------------

/**
 * @brief Permet d'afficher l'interface
 *
 * @param [in] tableau le tableau de taille 6x7 qui va etre afficher 
 * 
 */
void afficherJeu(Case tableau[6][7]);

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
 * @param [in] min borne minimum
 * @param [in] max borne maximum
 */
int random(int min, int max);



/**
 * @brief Permet de verifier si la ligne horizontal est gagnante pour le joueur 1 ou 2
 *
 * @param [in] ligne le numero de la ligne a verifier
 * @param [in] nombreAverifier Comme chaque joueur a un numero, on verifiera qu'un seul joueur a la fois
 * @param [in] tableau le tableau contenant toutes les informations du jeu
 */
bool verificationHorizontale(unsigned short int ligne, Case caseDuJeu, Case tableau[6][7]);

/**
 * @brief Permet de verifier si la ligne vertical est gagnante pour le joueur 1 ou 2
 *
 * @param [in] colonne le numero de la colonne a verifier
 * @param [in] nombreAverifier Comme chaque joueur a un numero, on verifiera qu'un seul joueur a la fois
 * @param [in] tableau le tableau contenant toutes les informations du jeu
 */
bool verificationVertical(unsigned short int colonne, Case caseDuJeu, Case tableau[6][7]);


/**
 * @brief Permet la verification de la diagonal de haut en bas de gauche a droite
 *
 * @param [in] ligne permet de localisé la diagonal a verifier
 * @param [in] colonne permet de localisé la diagonal a verifier
 * @param [in] nombreAverifier Comme chaque joueur a un numero, on verifiera qu'un seul joueur a la fois
 * @param [in] tableau le tableau contenant toutes les informations du jeu
 */
bool verificationDiagonalDroite(unsigned short int colonne, unsigned short int ligne, Case caseDuJeu, Case tableau[6][7]);


/**
 * @brief Permet la verification de la diagonal de haut en bas de droite a gauche
 *
 * @param [in] ligne permet de localisé la diagonal a verifier
 * @param [in] colonne permet de localisé la diagonal a verifier
 * @param [in] nombreAverifier Comme chaque joueur a un numero, on verifiera qu'un seul joueur a la fois
 * @param [in] tableau le tableau contenant toutes les informations du jeu
 */
bool verificationDiagonalGauche(unsigned short int colonne, unsigned short int ligne, Case caseDuJeu, Case tableau[6][7]);





#endif
