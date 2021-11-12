/**
 * @file jeuEnDuo.cpp
 * @author Mathis Heriveau
 * @brief Corps du module sousProgramme.h
 * @date 27 octobre 2021
 */
#include "sousProgramme.h"
#include <iostream>
#include <conio.h> // pour la fonction _getwch
using namespace std;

void jeuDuo(unsigned short int couleurJoueur1, unsigned short int couleurJoueur2, string nomJoueurUn, string nomJoueurDeux){
    
    // TYPES UTILISES DANS LE PROGRAMME PRINCIPAL
    //-------------------------------------------------------
    const unsigned short int NB_DE_LIGNE = 6;
    const unsigned short int NB_DE_COLONNE = 7;
    unsigned short int tableauDeJeu[NB_DE_LIGNE][NB_DE_COLONNE] = {0}; //Tableau du jeu

    // VARIABLES UTILISEES DANS LE PROGRAMME PRINCIPA
    //-------------------------------------------------------
    char choixDeRenouvellerLaPartie;      //L'utilisateur choisi de continuer ou pas le jeux

    string nomDuJoueur;        //Nom du joueur au tour donné
    string nomDuGagnant;       //Nom du gagnant
    string nomDeLaVerifGagner; //Le nom de la verificarion qui fait gagner le joueur

    bool trouve = false;      //Permettant de savoir si il y a de la place dans la colonne
    bool statutPartie = true; //Le statut de la partie : true = en jeu ; false = fin du jeu
    bool egalite = false;     //En cas d'egalité on mets en true

    unsigned short int tourDeJeu = 0;  //Le nombre de tour de jeu
    unsigned short int numeroDeLaCase; //Le numero qui sera implementé dans le tableau de jeu
    unsigned short int choixDuJoueur;  //Le choix de la colonne du jeton
    unsigned short int position;       //Permettant de positionner la propriete a verifier
    unsigned short int couleurDuJoueur;//La couleur du joueur 


    // TRAITEMENTS
    //-------------------------------------------------------
    while (statutPartie != false)
    {
        //Initialisation des variables
        position = 0;  //position du jeton quand il tombe
        tourDeJeu ++;  //Tour de jeu
        choixDuJoueur=-1; //Initialise le choix du joueur

        //Affiche de l'interface 
        afficherJeu(tableauDeJeu,couleurJoueur1,couleurJoueur2);

        //Si le tour est paire le joueur 2 commence
        if (tourDeJeu % 2 == 1)
        {
            nomDuJoueur = nomJoueurUn;      //Nom du joueur
            numeroDeLaCase = 1;             //Numero du joueur
            couleurDuJoueur=couleurJoueur1;        //Initialise la couleur du joueur 
        }
        else
        {
            nomDuJoueur = nomJoueurDeux;    //Nom du joueur
            numeroDeLaCase = 2;             //Numero du joueur
            couleurDuJoueur=couleurJoueur2;        //Initialise la couleur du joueur 
        }

        
        //Affichage du tour
        cout << "\n\nC'est a " << nomDuJoueur << " de jouer. \nVous avez les jetons de couleur ";  //Affiche le nom du joueur
        //Affiche la couleur du jetons du joueur

        switch (couleurDuJoueur)
        {
        case 7: afficherTexteEnCouleur("gris", gris, false); break;
        case 9: afficherTexteEnCouleur("bleu", bleu, false); break;
        case 10: afficherTexteEnCouleur("vert", vert, false); break;
        case 11: afficherTexteEnCouleur("cyan", cyan, false); break;
        case 12: afficherTexteEnCouleur("rouge", rouge, false); break;
        case 13: afficherTexteEnCouleur("violet", violet, false); break;
        case 14: afficherTexteEnCouleur("jaune", jaune, false); break;
        case 15: afficherTexteEnCouleur("blanc", blanc, false); break;   
        }
        cout << ".\n";


        //verification si la colonne est pleine
        while ((choixDuJoueur > 6 || tableauDeJeu[0][choixDuJoueur] > 0 )&& (choixDuJoueur != 999))
        {
            if (choixDuJoueur == 999){statutPartie=false ; break;}
            cout << "Saisissez une case valide [0..6]: ";    //Annonce la saisie
            cin >> choixDuJoueur;
        }
        if (choixDuJoueur == 999){break;} //Le joueur abandonne la partie

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

        //Verification si le joueur a gagner
        verificationJeu(choixDuJoueur, position, numeroDeLaCase, tableauDeJeu, statutPartie, nomDeLaVerifGagner);
        if (tourDeJeu==42){statutPartie=false; egalite=true;} //Si il n'y a plus de case libre il y a egalite

        //Fin de la manche
    }
    // Fin du jeu
    //-------------------------------------------------------
    if (choixDuJoueur!=999){
        afficherJeu(tableauDeJeu,couleurJoueur1,couleurJoueur2); //Affiche le jeu

        //Si il y un gagnant
        if (egalite==false)
        {
            afficherTexteEnCouleur("\n\nNOUS AVONS UN GAGNANT ! ! !\n", rouge, true); //Gagnant 
            //Affichage de la position de la verification
            cout << nomDuJoueur << " gagne la partie en alignant 4 pions " << nomDeLaVerifGagner << ".";
        }
        else
        {
            afficherTexteEnCouleur("\n\nEGALITE ! ! !", rouge, true);  //Egalité
        }

        //Demande si le joueur veut refaire une partie ou retourner au lobby
        cout << "\n\nAppuyer sur r pour recommencer, sinon tapper une autre touche.";
        choixDeRenouvellerLaPartie=static_cast<char>(_getwch());
        //Si il veut recommencer
        if (choixDeRenouvellerLaPartie == 'r'){
            jeuDuo(couleurJoueur1,couleurJoueur2,nomJoueurUn,nomJoueurDeux);
        }
    }
    
}