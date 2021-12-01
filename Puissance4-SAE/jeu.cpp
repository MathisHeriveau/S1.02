/**
 * @file jeuEnDuo.cpp
 * @author Mathis Heriveau
 * @brief Corps du module sousProgramme.h
 * @date 27 octobre 2021
 */
#include "sousProgramme.h"
#include <iostream>
using namespace std;

void jeu(unsigned short int couleurDuJoueurUn, unsigned short int couleurDuJoueurDeux, string nomJoueurUn, string nomJoueurDeux){
    
    // TYPES UTILISES DANS LE PROGRAMME PRINCIPAL
    //-------------------------------------------------------
    const unsigned short int NB_DE_LIGNE = 6;
    const unsigned short int NB_DE_COLONNE = 7;
    unsigned short int tableauDeJeu[NB_DE_LIGNE][NB_DE_COLONNE] = {caseVide}; //Tableau du jeu

    // VARIABLES UTILISEES DANS LE PROGRAMME PRINCIPA
    //-------------------------------------------------------
    char choixDeRenouvellerLaPartie;      //L'utilisateur choisi de continuer ou pas le jeux

    string nomDuGagnant;   //Nom du joueur au tour donné

    bool trouve;        //Permettant de savoir si il y a de la place dans la colonne
    bool statutPartie;  //Le statut de la partie : true = en jeu ; false = fin du jeu
    bool egalite;       //En cas d'egalité on mets en true

    unsigned short int tourDeJeu;  //Le nombre de tour de jeu
    unsigned short int numeroDeLaCase; //Le numero qui sera implementé dans le tableau de jeu
    unsigned short int choixDuJoueur;  //Le choix de la colonne du jeton
    unsigned short int position;  //Permettant de positionner la propriete a verifier
    unsigned short int choixDuPremierJoueur; //Le choix du premier joueur : 1 = joueur1 ; 2 = joueur2.


    //Initialisation
    trouve = false;      
    statutPartie = true; 
    egalite = false;
    tourDeJeu = 0; 
    position = 0;
    choixDuPremierJoueur = static_cast<unsigned short int>(random(0,1));
    
    // TRAITEMENTS
    //-------------------------------------------------------
    //On mets une pause entre l'interface
    do
    {
        //Rinitialisation des variables a chaque tour
        position = 0;  //position du jeton quand il tombe
        tourDeJeu ++;  //Tour de jeu

        //Affiche de l'interface 
        afficherTitre();
        afficherJeu(tableauDeJeu,couleurDuJoueurUn,couleurDuJoueurDeux);

        //
        if (tourDeJeu % 2 == choixDuPremierJoueur)
        {
            nomDuGagnant = nomJoueurUn;      //Nom du joueur
            numeroDeLaCase = 1;             //Numero du joueur

            //Affichage du tour
            cout << "\n\nC'est a " << nomJoueurUn << " de jouer." << endl;  //Affiche le nom du joueur
            cout << "Vous avez les jetons de couleur ";
            afficherCouleurJoueur(couleurDuJoueurUn);  //Affiche la couleur du jetons du joueur    
        }
        else
        {
            nomDuGagnant = nomJoueurDeux;    //Nom du joueur
            numeroDeLaCase = 2;             //Numero du joueur

            //Affichage du tour
            cout << "\n\nC'est a " << nomJoueurDeux << " de jouer." << endl; //Affiche le nom du joueur
            cout << "Vous avez les jetons de couleur ";
            afficherCouleurJoueur(couleurDuJoueurDeux);  //Affiche la couleur du jetons du joueur
        }


        //verification si la colonne est pleine
        do
        {
            cout << "Saisissez une case : ";    //Annonce la saisie
            cin >> choixDuJoueur;
            if (choixDuJoueur == 999){statutPartie=false ; break;}

        }while (choixDuJoueur > 6 || tableauDeJeu[0][choixDuJoueur] > 0);

        if(choixDuJoueur !=999){

            while (trouve != true ) //Mettre le jeton a la bonne case (bonne position de hauteur et de colonne)
            {   
                //Si on tombe sur un jeton ou on en trouve pas
                if (position == 6 || tableauDeJeu[position][choixDuJoueur] > 0)
                {
                    position--; //On remonte d'un crant
                    tableauDeJeu[position][choixDuJoueur] = numeroDeLaCase; //On met le jeton avec le numero du joueur
                    break; //On sort de la boucle
                }
                position++; //On descend de case
            }
            
            //Verif
            statutPartie = verificationJeu(choixDuJoueur, position, numeroDeLaCase, tableauDeJeu);
            if (statutPartie==false){break;}
            if (tourDeJeu==42){statutPartie=false; egalite=true;} //Si il n'y a plus de case libre il y a egalite
            //Fin de la manche
            
        }
        
    }while (statutPartie != false);

    // Fin du jeu
    //-------------------------------------------------------
    if (choixDuJoueur!=999){
        afficherTitre();
        afficherJeu(tableauDeJeu,couleurDuJoueurUn,couleurDuJoueurDeux); //Affiche le jeu
    
        //Si il y un gagnant
        if (egalite==false){
            afficherTexteEnCouleur("\n\nNOUS AVONS UN GAGNANT ! ! !\n", rouge, true); //Gagnant 
            //Affichage de la position du jeton clef
            cout << nomDuGagnant << " gagne la partie grace au jeton depose a la ligne " << position + 1 << " de la " << choixDuJoueur << "eme colonne(s) !";
            
        }else
        {
            afficherTexteEnCouleur("\n\nEGALITE ! ! !\n", rouge, true);  //Egalité
            
        }
        
        cout << "\n\nAppuyer sur r pour recommencer, sinon tapper une autre touche.";
        choixDeRenouvellerLaPartie=static_cast<char>(_getwch());
        if (choixDeRenouvellerLaPartie == 'r'){
            jeu(couleurDuJoueurUn,couleurDuJoueurDeux,nomJoueurUn,nomJoueurDeux);
        }
        
    }
}