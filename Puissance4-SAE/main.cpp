/**\
  * @file main.cpp
  * @author Mathis Hériveau, Tom Planche
  * @brief Fichier principal
  * @date 25-11-2021
  * 
\**/

#include "sousProgramme.h"

int main()
{

    //.  ===========================================================================================
    //.                                      INITIALISATION                                         
    //.  ===========================================================================================


    //.  ------------------------------- DÉCLARATIONS VARIABLES ------------------------------------

    //. Constantes Utilisées Dans Le Programme Principal
    const unsigned short int NB_DE_LIGNE = 6; // Nombre de lignes dans la grille du puissance 4.
    const unsigned short int NB_DE_COLONNE = 7; // Nombre de colonnes dans la grille du puissance 4.
    

    Case grilleDeJeu[NB_DE_LIGNE][NB_DE_COLONNE] = {caseVide}; // La grille du jeu contenant l'ensemble des jetons.
    
    Case jeton; // Jeton en jeu.
    
    TypeDeVictoire maniereDeGagner; // Manière dont le gagnant aligne les jetons


    string nomDuGagnant;  // Nom du joueur gagnant.
    string nomJoueurUn;   // Nom du joueur 1
    string nomJoueurDeux; // Nom du joueur 2 

    bool statutPartie;    // Définit le statut de la partie, s'il passe  à false, la partie est finie.
    bool egalite;         // Passe à true s'il y a une égalité.

    unsigned short int nbTours;              // Compte le nombre de tours, permettant de savoir qui joue et quand il y a une égalité.
    unsigned short int choixDuJoueur;        // Choix de la colonne du joueur en cours.
    unsigned short int positionCase;         // Dernière position du dernier jeton posé, permet de faire une vérification que pour les bonnes zones 
    unsigned short int choixDuPremierJoueur; // Grace a un random, la valeur indique le premier joueur qui commencera la partie : 0 pour le joueur rouge et 1 pour le joueur jaune. 
    

    //.  -------------------------------- DÉFINITIONS VARIABLES ------------------------------------
    statutPartie = true;
    egalite = false;
    nbTours = 0;
    positionCase = 0;
    choixDuPremierJoueur = static_cast<unsigned short int>(random(0, 1)); // static_cast force la conversion du random en unsigned short int

    //.  ------------------------------- AFFICHAGE RÈGLES DU JEU -----------------------------------
    afficherTitre();
    cout << "Ce programme est un jeu de puisssance 4." << endl;
    cout << "Il est concu avec le langage C++." << endl;
    cout << "Le but de ce jeu est de reussir a aligner quatre de ces jetons horizontalement, verticalement ou encore diagonalement." << endl;
    cout << "Le premier joueur a reussir cela gagne automatiquement." << endl;

    //.  ------------------------- INITIALISATION DES NOMS DES JOUEURS -----------------------------
    cout << "\nSaisissez le nom du joueur 1 : "; // Demande le nom du joueur 1
    cin >> nomJoueurUn;
    cout << "Saisissez le nom du joueur 2 : ";   // Demande le nom du joueur 2
    cin >> nomJoueurDeux;



    //.  ===========================================================================================
    //.                                            JEU                                              
    //.  ===========================================================================================

    // do-while simulant le jeu.
    do
    {
        //.  ------------------ RÉINITIALISATION DES PARAMÈTRES À CHAQUE TOUR ----------------------
        positionCase = 0; // Position du jeton quand il tombe
        nbTours++;  // Tour de jeu

        //.  -------------------------------- AFFICHAGE DU JEU -------------------------------------
        afficherTitre();
        afficherJeu(grilleDeJeu);

        //.  --------------------------------- TOUR DU JOUEUR --------------------------------------
        if (nbTours % 2 == choixDuPremierJoueur)
        {
            nomDuGagnant = nomJoueurUn; // Nom du joueur
            jeton = pionRouge;          // Numéro du joueur

            // Affichage des informations sur le tour actuel
            cout << "\n\nC'est à " << nomJoueurUn << " de jouer." << endl; // Affiche le nom du joueur
            cout << "Vous avez les jetons de couleur ";                    // Affichage des informations sur le jeton du joueur
            afficherTexteEnCouleur("rouge", rouge, true);
        }
        else // Sinon, c'est à l'autre joueur
        {
            nomDuGagnant = nomJoueurDeux; // Nom du joueur
            jeton = pionJaune;            // Numéro du joueur

            // Affichage des informations sur le tour actuel
            cout << "\n\nC'est a " << nomJoueurDeux << " de jouer." << endl; // Affiche le nom du joueur
            cout << "Vous avez les jetons de couleur ";                      // Affichage des informations sur le jeton du joueur
            afficherTexteEnCouleur("jaune", jaune, true);
        }


        //.  ---------------------------------- SAISIE/VÉRIF ---------------------------------------
        do {
            choixDuJoueur = saisieVerifCase();
            // On indique au joueur que s'il veut quitter la partie, il peut saisir 999.
            if (choixDuJoueur == 999) {
                statutPartie = false;
                break;
            }
        // On ne sort pas de la boucle si la colonne choisie n'est pas pleine.
        } while (grilleDeJeu[0][choixDuJoueur] != caseVide);

        //.  --------------------------- LE JOUEUR N'ABAONDONNE PAS --------------------------------
        if (choixDuJoueur != 999)
        {

            while (true) // Permet de mettre le jeton sur la bonne case.
            {
                // Si on tombe sur un jeton ou on en trouve pas
                if (positionCase == 6 || grilleDeJeu[positionCase][choixDuJoueur] > 0)
                {
                    positionCase--;                                   // On remonte d'un crant
                    grilleDeJeu[positionCase][choixDuJoueur] = jeton; // On met le jeton avec le numéro du joueur
                    break;                                            // On sort de la boucle
                }
                positionCase++; // On descend de case
            }

            // Vérification Horizontale
            if (verificationHorizontale(positionCase, jeton, grilleDeJeu)) //Si il trouve quelque chose on sort.
            {
                statutPartie = false;
                maniereDeGagner = horizontalement;
            }

            // Vérification Verticale
            if (verificationVerticale(choixDuJoueur, jeton, grilleDeJeu)) //Si il trouve quelque chose on sort.
            {
                statutPartie = false;
                maniereDeGagner = verticalement;
            }

            // Vérification des diagonales
            if (verificationDiagonaleDroite(choixDuJoueur, positionCase, jeton, grilleDeJeu) || verificationDiagonaleGauche(choixDuJoueur, positionCase, jeton, grilleDeJeu)) //Si il trouve quelque chose on sort.
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
            } // S'il n'y a plus de case libre, alors il y a égalité
            // Fin de la manche
        }

    } while (statutPartie != false);

    //.  ===========================================================================================
    //.                                     FIN DE LA PARTIE                                        
    //.  ===========================================================================================
    if (choixDuJoueur != 999)
    {
        afficherTitre();
        afficherJeu(grilleDeJeu); // Affiche le jeu

        // S'il y un gagnant
        if (egalite == false)
        {
            afficherTexteEnCouleur("\n\nNOUS AVONS UN GAGNANT ! ! !\n", rouge, true); // Gagnant
            // Affichage de la position du jeton clé
            cout << nomDuGagnant ;
            switch (maniereDeGagner) {
                case horizontalement:
                    cout << " gagne la partie en alignant 4 jetons horizontalement.";
                    break;
                case verticalement:
                    cout << " gagne la partie en alignant 4 jetons verticalement.";
                    break;
                case diagonalement:
                    cout << " gagne la partie en alignant 4 jetons diagonalement.";
                    break;
            }
        }
        else
        {
            afficherTexteEnCouleur("\n\nEGALITE ! ! !\n", rouge, true); // Égalité
        }

        cout << endl;
    }
}