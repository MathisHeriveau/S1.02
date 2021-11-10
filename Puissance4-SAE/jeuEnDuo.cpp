/**
 * @file jeuEnDuo.cpp
 * @author Mathis Heriveau
 * @brief Corps du module sousProgramme.h
 * @date 27 octobre 2021
 */
#include "sousProgramme.h"
#include <iostream>
using namespace std;

void jeuDuo(unsigned short int joueur1, unsigned short int joueur2, string NomJoueurUn, string NomJoueurDeux){
    
    // TYPES UTILISES DANS LE PROGRAMME PRINCIPAL
    //-------------------------------------------------------
    const unsigned short int NB_DE_LIGNE = 6;
    const unsigned short int NB_DE_COLONNE = 7;
    unsigned short int tableauDeJeu[NB_DE_LIGNE][NB_DE_COLONNE] = {0}; //Tableau du jeu

    // VARIABLES UTILISEES DANS LE PROGRAMME PRINCIPA
    //-------------------------------------------------------
    char choixDeRenouvellerLaPartie;      //L'utilisateur choisi de continuer ou pas le jeux

    string nomDuJoueur;   //Nom du joueur au tour donné
    string nomDuGagnant;  //Nom du gagnant

    bool trouve = false;      //Permettant de savoir si il y a de la place dans la colonne
    bool statutPartie = true; //Le statut de la partie : true = en jeu ; false = fin du jeu
    bool egalite = false;     //En cas d'egalité on mets en true

    unsigned short int tourDeJeu = 2;  //Le nombre de tour de jeu
    unsigned short int numeroDeLaCase; //Le numero qui sera implementé dans le tableau de jeu
    unsigned short int choixDuJoueur;  //Le choix de la colonne du jeton
    unsigned short int position = -1;  //Permettant de positionner la propriete a verifier


    // TRAITEMENTS
    //-------------------------------------------------------
    //On mets une pause entre l'interface
    while (statutPartie != false)
    {
        //Initialisation des variables
        position = 0;  //position du jeton quand il tombe
        tourDeJeu ++;  //Tour de jeu

        /*cout << "\nChargement ...";     //Texte pour faire style
        pause(1);                       //Pause permettant de faire style que le chargelment dure 1s*/
        system("cls");                  //On clear le terminal

        //Affiche de l'interface 
        afficherTitre();
        afficherJeu(tableauDeJeu,joueur1,joueur2);
        cout << "\n                        revenir au menu(999)";
        //Si le tour est paire le joueur 2 commence
        if (tourDeJeu % 2 == 1)
        {
            nomDuJoueur = NomJoueurUn;      //Nom du joueur
            numeroDeLaCase = 1;             //Numero du joueur

            //Affichage du tour
            cout << "\n\nC'est a " << nomDuJoueur << " de jouer." << endl;  //Affiche le nom du joueur
            cout << "Vous avez les jetons de couleur ";
            afficherCouleurJoueur(joueur1);  //Affiche la couleur du jetons du joueur    
            cout << "." << endl;
        }
        else
        {
            nomDuJoueur = NomJoueurDeux;    //Nom du joueur
            numeroDeLaCase = 2;             //Numero du joueur

            //Affichage du tour
            cout << "\n\nC'est a " << nomDuJoueur << " de jouer." << endl; //Affiche le nom du joueur
            cout << "Vous avez les jetons de couleur ";
            afficherCouleurJoueur(joueur2);  //Affiche la couleur du jetons du joueur
            cout << "." << endl;
        }

        cout << "Saisissez une case : "; //Saisie de la colonne du jeton
        cin >> choixDuJoueur;
        if (choixDuJoueur == 999){break;}

        //verification si la colonne est pleine
        while (choixDuJoueur < 0 || choixDuJoueur > 6 || tableauDeJeu[0][choixDuJoueur] > 0)
        {
            if (choixDuJoueur == 999){statutPartie=false ; break;}
            cout << "Saisissez une case : ";    //Annonce la saisie
            cin >> choixDuJoueur;
        }

        while (trouve != true) //Mettre le jeton a la bonne case (bonne position de hauteur et de colonne)
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
        if(choixDuJoueur!=999){
            //Verif
        statutPartie = verificationJeu(choixDuJoueur, position, numeroDeLaCase, tableauDeJeu);
        if (statutPartie==false){break;}
        if (tourDeJeu==44){statutPartie=false; egalite=true;} //Si il n'y a plus de case libre il y a egalite
        //Fin de la manche
        }
        
    }

    // Fin du jeu
    //-------------------------------------------------------
    if (choixDuJoueur!=999){
        system("cls"); //Clear le terminal
        afficherTitre();
        afficherJeu(tableauDeJeu,joueur1,joueur2); //Affiche le jeu
    }
    
    //Si il y un gagnant
    if (egalite==false && choixDuJoueur != 999){
        afficherTexteEnCouleur("\n\nNOUS AVONS UN GAGNANT ! ! !\n", vert, true); //Gagnant 
        //Affichage de la position du jeton clef
        cout << nomDuJoueur << " gagne la partie grace au jeton depose a la ligne " << position + 1 << " de la " << choixDuJoueur << "eme colonne(s) !";
        
    }else if (egalite==true && choixDuJoueur != 999)
    {
        afficherTexteEnCouleur("\n\nEGALITE ! ! !\n", vert, true);  //Egalité
        cout << "\n\nAppuyer sur r pour recommencez";
        
    }
    if (choixDuJoueur!=999){
        cout << "\n\nAppuyer sur r pour recommencer, sinon tapper une autre touche.";
        choixDeRenouvellerLaPartie=_getwch();
        if (choixDeRenouvellerLaPartie == 'r'){
            jeuDuo(joueur1,joueur2,NomJoueurUn,NomJoueurDeux);
        }
    } 
}