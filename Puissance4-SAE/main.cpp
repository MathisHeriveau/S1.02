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

    // TYPES UTILISES DANS LE PROGRAMME PRINCIPAL
    //-------------------------------------------------------
    const unsigned short int NB_DE_LIGNE = 6;
    const unsigned short int NB_DE_COLONNE = 7;
    Case grilleDeJeu[NB_DE_LIGNE][NB_DE_COLONNE] = {caseVide}; //grille du jeu

    // VARIABLES UTILISEES DANS LE PROGRAMME PRINCIPA
    //-------------------------------------------------------
    Case jeton; //Le numero qui sera implementé dans le grille de jeu

    TypeDeVictoire maniereDeGagner; //Maniere dont le gagant aligne les jetons

    string nomDuGagnant;  //Nom du joueur au tour donné
    string nomJoueurUn;   //Nom du joueur un
    string nomJoueurDeux; //Nom du joueur deux

    bool trouve;       //Permettant de savoir si il y a de la place dans la colonne
    bool statutPartie; //Le statut de la partie : true = en jeu ; false = fin du jeu
    bool egalite;      //En cas d'egalité on mets en true

    unsigned short int tourDeJeu;            //Le nombre de tour de jeu
    unsigned short int choixDuJoueur;        //Le choix de la colonne du jeton
    unsigned short int position;             //Permettant de positionner la propriete a verifier
    unsigned short int choixDuPremierJoueur; //Le choix du premier joueur : 1 = joueur1 ; 2 = joueur2.

    //Initialisation
    trouve = false;
    statutPartie = true;
    egalite = false;
    tourDeJeu = 0;
    position = 0;
    choixDuPremierJoueur = static_cast<unsigned short int>(random(0, 1));

    // Regles du jeu
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

    // TRAITEMENTS
    //-------------------------------------------------------
    //On mets une pause entre l'interface
    do
    {
        //Rinitialisation des variables a chaque tour
        position = 0; //position du jeton quand il tombe
        tourDeJeu++;  //Tour de jeu

        //Affiche de l'interface
        afficherTitre();
        afficherJeu(grilleDeJeu);

        //
        if (tourDeJeu % 2 == choixDuPremierJoueur)
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

            while (trouve != true) //Mettre le jeton a la bonne case (bonne position de hauteur et de colonne)
            {
                //Si on tombe sur un jeton ou on en trouve pas
                if (position == 6 || grilleDeJeu[position][choixDuJoueur] > 0)
                {
                    position--;                                   //On remonte d'un crant
                    grilleDeJeu[position][choixDuJoueur] = jeton; //On met le jeton avec le numero du joueur
                    break;                                        //On sort de la boucle
                }
                position++; //On descend de case
            }

            //Verif
            if (!verificationHorizontale(position, jeton, grilleDeJeu)) //Si il trouve quelque chose on sort.
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
            if (!verificationDiagonalDroite(choixDuJoueur, position, jeton, grilleDeJeu)) //Si il trouve quelque chose on sort.
            {
                statutPartie = false;
                maniereDeGagner = diagonalement;
            }

            //Verif de haut en bas de droite a gauche
            if (!verificationDiagonalGauche(choixDuJoueur, position, jeton, grilleDeJeu)) //Si il trouve quelque chose on sort.
            {
                statutPartie = false;
                maniereDeGagner = diagonalement;
            }

            if (statutPartie == false)
            {
                break;
            }

            if (tourDeJeu == 42)
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