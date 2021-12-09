/**
 * @file main.cpp
 * @author Mathis Heriveau
 * @brief Corps du module sousProgramme.h
 * @date 27 octobre 2021
 */
#include "sousProgramme.h"
#include <iostream>
using namespace std;

int main()
{

    //.  ===========================================================================================
    //.                                      INITIALISATION                                         
    //.  ===========================================================================================

    
    //.  ------------------------------- DECLARATIONS VARIABLES ------------------------------------

    //. Constantes Utilisees Dans Le Programme Principal
    const unsigned short int NB_DE_LIGNE = 6; //Le nombre de ligne dans la grille du puissance 4
    const unsigned short int NB_DE_COLONNE = 7; //Le nombre de colonne dans la grille du puissance 4
    
    //. Types Utilisés Dans Le Programme Principal
    Case grilleDeJeu[NB_DE_LIGNE][NB_DE_COLONNE] = {caseVide}; // La grille de jeu contenant l'ensemble des jetons
    
    Case jeton; // Jeton du joueur 1 et du joueur 2
    
    TypeDeVictoire maniereDeGagner; // Manière dont le gagnant aligne les jetons

    //. Constantes Utilisees Dans Le Programme Principal
    string nomDuGagnant;  //Nom du joueur au tour donné
    string nomJoueurUn;   //Correspond au nom du joueur 1
    string nomJoueurDeux; //Correspond au nom du joueur 2 

    bool statutPartie; //Caractérise le statut de la partie : true = en jeu, false = fin du jeu 
    bool egalite;      //Cette variable ce mets a true dès lors qu’il y a une égalité 

    unsigned short int nbTours;              // Permet de compter le nombre de tour, permettant de savoir qui joue et quand Est-ce qu'il y a une égalité 
    unsigned short int choixDuJoueur;        // Le choix de la colonne du jeton
    unsigned short int positionCase;         // Permet de savoir a qu’elle hauteur le jeton doit être positionné dans la colonne 
    unsigned short int choixDuPremierJoueur; // Grace a un random, la valeur indique le premier joueur qui commencera la partie : 0 pour le joueur rouge et 1 pour le joueur jaune. 
    

    //.  -------------------------------- DEFINITIONS VARIABLES ------------------------------------
    statutPartie = true;
    egalite = false;
    nbTours = 0;
    positionCase = 0;
    choixDuPremierJoueur = static_cast<unsigned short int>(random(0, 1));

    //.  ------------------------------- AFFICHAGE REGLES DU JEU -----------------------------------
    afficherTitre();
    cout << "Ce programme est un jeu de puisssance 4." << endl;
    cout << "Il est concu avec le langage C++." << endl;
    cout << "Le but de ce jeu est de reussir a aligner quatre de ces jetons horizontalement, verticalement ou encore diagonalement." << endl;
    cout << "Le premier joueur a reussir cela gagne automatiquement." << endl;

    //.  ------------------------------- INITIALISATION DES NOMS -----------------------------------
    cout << "Saisissez le nom du joueur 1 : "; //Demande le nom du joueur 1
    cin >> nomJoueurUn;
    cout << "Saisissez le nom du joueur 2 : "; //Demande le nom du joueur 2
    cin >> nomJoueurDeux;



    //.  ===========================================================================================
    //.                                        TRAITEMENTS                                          
    //.  ===========================================================================================

    // Bouble do-while simulant le jeu.
    do
    {
        // Réinitialisation des variables à chaque tour
        positionCase = 0; // Position du jeton quand il tombe
        nbTours++;  // Tour de jeu

        // Affichage de l'interface
        afficherTitre();
        afficherJeu(grilleDeJeu);

        // Si le nombre de tours est pair, c'est au tour du joueur qui a commencé.
        if (nbTours % 2 == choixDuPremierJoueur)
        {
            nomDuGagnant = nomJoueurUn; // Nom du joueur
            jeton = pionRouge;          // Numéro du joueur

            // Affichage des informations sur le tour actuel
            cout << "\n\nC'est a " << nomJoueurUn << " de jouer." << endl; // Affiche le nom du joueur
            cout << "Vous avez les jetons de couleur "; // Affichage des informations sur le jeton du joueur
            afficherTexteEnCouleur("rouge", rouge, true);
        }
        else // Sinon, c'est à l'autre joueur
        {
            nomDuGagnant = nomJoueurDeux; // Nom du joueur
            jeton = pionJaune;            // Numéro du joueur

            // Affichage des informations sur le tour actuel
            cout << "\n\nC'est a " << nomJoueurDeux << " de jouer." << endl; // Affiche le nom du joueur
            cout << "Vous avez les jetons de couleur "; // Affichage des informations sur le jeton du joueur
            afficherTexteEnCouleur("jaune", jaune, true);
        }

        // Saisie-vérif du numéro de la case
        do
        {
            cout << "Saisissez une case : "; // Annonce la saisie
            cin >> choixDuJoueur;
            if (choixDuJoueur == 999)
            {
                statutPartie = false;
                break;
            }

        } while (choixDuJoueur > 6 || grilleDeJeu[0][choixDuJoueur] != caseVide);

        if (choixDuJoueur != 999)
        {

            while (true) //Mettre le jeton a la bonne case (bonne position de hauteur et de colonne)
            {
                //Si on tombe sur un jeton ou on en trouve pas
                if (positionCase == 6 || grilleDeJeu[positionCase][choixDuJoueur] > 0)
                {
                    positionCase--;                                   //On remonte d'un crant
                    grilleDeJeu[positionCase][choixDuJoueur] = jeton; //On met le jeton avec le numéro du joueur
                    break;                                        //On sort de la boucle
                }
                positionCase++; //On descend de case
            }

            //Verif
            if (!verificationHorizontale(positionCase, jeton, grilleDeJeu)) //Si il trouve quelque chose on sort.
            {
                statutPartie = false;
                maniereDeGagner = horizontalement;
            }

            //Verif Vertical
            if (!verificationVertical(choixDuJoueur, jeton, grilleDeJeu)) //Si il trouve quelque chose on sort.
            {
                statutPartie = false;
                maniereDeGagner = verticalement;
            }

            //Verif de haut en bas de gauche a droite
            if (!verificationDiagonalDroite(choixDuJoueur, positionCase, jeton, grilleDeJeu)) //Si il trouve quelque chose on sort.
            {
                statutPartie = false;
                maniereDeGagner = diagonalement;
            }

            //Verif de haut en bas de droite a gauche
            if (!verificationDiagonalGauche(choixDuJoueur, positionCase, jeton, grilleDeJeu)) //Si il trouve quelque chose on sort.
            {
                statutPartie = false;
                maniereDeGagner = diagonalement;
            }

            if (statutPartie == false)
            {
                break;
            }

            if (nbTours == 42)
            {
                statutPartie = false;
                egalite = true;
            } //Si il n'y a plus de case libre il y a egalite
            //Fin de la manche
        }

    } while (statutPartie != false);

    // Fin du jeu
    //-------------------------------------------------------
    if (choixDuJoueur != 999)
    {
        afficherTitre();
        afficherJeu(grilleDeJeu); //Affiche le jeu

        //Si il y un gagnant
        if (egalite == false)
        {
            afficherTexteEnCouleur("\n\nNOUS AVONS UN GAGNANT ! ! !\n", rouge, true); //Gagnant
            //Affichage de la position du jeton clef
            cout << nomDuGagnant ;
            switch (maniereDeGagner)
            {
            case horizontalement: cout << " gagne la partie en alignant 4 jetons horizontalement.";
                break;
            case verticalement: cout << " gagne la partie en alignant 4 jetons verticalement.";
                break;
            case diagonalement: cout << " gagne la partie en alignant 4 jetons diagonalement.";
                break;
            }
        }
        else
        {
            afficherTexteEnCouleur("\n\nEGALITE ! ! !\n", rouge, true); //Egalité
        }

        cout << endl;
    }
}