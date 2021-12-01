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
    const unsigned short int NB_DE_LIGNE = 6;
    const unsigned short int NB_DE_COLONNE = 7;
    
    //. Types Utilisés Dans Le Programme Principal
    Case grilleDeJeu[NB_DE_LIGNE][NB_DE_COLONNE] = {caseVide}; // grille du jeu
    
    Case jeton; // Jeton du joueur 1 et du joueur 2
    
    TypeDeVictoire maniereDeGagner; // Manière dont le gagnant aligne les jetons

    //. Constantes Utilisees Dans Le Programme Principal
    string nomDuGagnant;  //Nom du joueur au tour donné
    string nomJoueurUn;   //Nom du joueur un
    string nomJoueurDeux; //Nom du joueur deux

    bool statutPartie; //Le statut de la partie : true = en jeu ; false = fin du jeu
    bool egalite;      //En cas d'egalité on mets en true

    unsigned short int nbTours;              // Le nombre de tour de jeu
    unsigned short int choixDuJoueur;        // Le choix de la colonne du jeton
    unsigned short int positionCase;             // Permettant de positionner la propriete a verifier
    unsigned short int choixDuPremierJoueur; // Le choix du premier joueur : 1 = joueur1 ; 2 = joueur2.
    

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

    // Initialisation des noms
    cout << "Saisissez le nom du joueur 1 : "; //Demande le nom du joueur 1
    cin >> nomJoueurUn;
    cout << "Saisissez le nom du joueur 2 : "; //Demande le nom du joueur 2
    cin >> nomJoueurDeux;



    //.  ===========================================================================================
    //.                                        TRAITEMENTS                                          
    //.  ===========================================================================================
    //On mets une pause entre l'interface
    do
    {
        //Rinitialisation des variables a chaque tour
        positionCase = 0; //position du jeton quand il tombe
        nbTours++;  //Tour de jeu

        //Affiche de l'interface
        afficherTitre();
        afficherJeu(grilleDeJeu);

        //
        if (nbTours % 2 == choixDuPremierJoueur)
        {
            nomDuGagnant = nomJoueurUn; //Nom du joueur
            jeton = pionRouge;          //Numero du joueur

            //Affichage du tour
            cout << "\n\nC'est a " << nomJoueurUn << " de jouer." << endl; //Affiche le nom du joueur
            cout << "Vous avez les jetons de couleur ";
            afficherTexteEnCouleur("rouge", rouge, true);
        }
        else
        {
            nomDuGagnant = nomJoueurDeux; //Nom du joueur
            jeton = pionJaune;            //Numero du joueur

            //Affichage du tour
            cout << "\n\nC'est a " << nomJoueurDeux << " de jouer." << endl; //Affiche le nom du joueur
            cout << "Vous avez les jetons de couleur ";
            afficherTexteEnCouleur("jaune", jaune, true);
        }

        //verification si la colonne est pleine
        do
        {
            cout << "Saisissez une case : "; //Annonce la saisie
            cin >> choixDuJoueur;
            if (choixDuJoueur == 999)
            {
                statutPartie = false;
                break;
            }

        } while (choixDuJoueur > 6 || grilleDeJeu[0][choixDuJoueur] > 0);

        if (choixDuJoueur != 999)
        {

            while (true) //Mettre le jeton a la bonne case (bonne position de hauteur et de colonne)
            {
                //Si on tombe sur un jeton ou on en trouve pas
                if (positionCase == 6 || grilleDeJeu[positionCase][choixDuJoueur] > 0)
                {
                    positionCase--;                                   //On remonte d'un crant
                    grilleDeJeu[positionCase][choixDuJoueur] = jeton; //On met le jeton avec le numero du joueur
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
            cout << nomDuGagnant << " gagne la partie en alignant 4 jetons " ;
            switch (maniereDeGagner)
            {
            case horizontalement: cout << "horizontalement.";
                break;
            case verticalement: cout << "verticalement.";
                break;
            case diagonalement: cout << "diagonalement.";
                break;
            }
        }
        else
        {
            afficherTexteEnCouleur("\n\nEGALITE ! ! !\n", rouge, true); //Egalité
        }
    }
}