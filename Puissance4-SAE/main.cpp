/**
 * @file JEU_PUISSANCE_4.cpp
 * @author Mathis Heriveau
 * @brief Alignez 4 jetons pour gagner
 * @date 27 octobre 2021
 */

#include <iostream>
#include "sousProgramme.h"
using namespace std;


//PROGRAMME PRINCIPAL
int main(void)
{
    //Variable utilise
    char modeDeJeu;
    bool exit = false;
    string nomJoueurUn;   //Nom du joueur1
    string nomJoueurDeux; //Nom du joueur2
    unsigned short int couleurJoueur1=14;
    unsigned short int couleurJoueur2=12;

    while (exit != true)
    {

        system("cls");
        // Regles du jeu
        afficherTitre();
        cout << "Ce programme est un jeu de puisssance 4." << endl;
        cout << "Il est concu avec le langage C++." << endl;
        cout << "Le but de ce jeu est de reussir a aligner quatre de ces jetons horizontalement, verticalement ou encore diagonalement." << endl;
        cout << "Le premier joueur a reussir cela gagne automatiquement." << endl;
        cout << "Si vous souhaitez jouer a 2 joueurs (d)" << endl;
        cout << "Une option permettant de changer de couleur est possible (o)" << endl;
        cout << "Vous pouvez quittez le jeu (x)\n";
        cout << "\n\nQue voulez vous faire ? ";
        modeDeJeu=static_cast<char>(_getwch());
        if (modeDeJeu == 'd')
        {
            //Affichage du nom du jeu
            afficherTitre();
            cout << "Vous avez selectionne le jeu a 2.\n\n" ;

            // Initialisation des noms
            cout << "Saisissez le nom du joueur 1 : ";  //Demande le nom du joueur 1
            cin >> nomJoueurUn;
            cout << "Saisissez le nom du joueur 2 : ";  //Demande le nom du joueur 2
            cin >> nomJoueurDeux;

            jeuDuo(couleurJoueur1,couleurJoueur2,nomJoueurUn,nomJoueurDeux);

        }
        else if (modeDeJeu == 'x')
        {
            exit = true;
        }
        else if(modeDeJeu == 'o')
        {
            option(couleurJoueur1,couleurJoueur2);
        }
    }

    return 0;
}