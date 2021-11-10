/**
 * @file option.cpp
 * @author Mathis Heriveau
 * @brief Corps du module sousProgramme.h
 * @date 27 octobre 2021
 */
#include "sousProgramme.h"
#include <iostream>
using namespace std;

void option(unsigned short int& joueur1, unsigned short int& joueur2)
{

    //Variables
    char choixDeLoption;
    bool exit = false;
    //Affichage du nom du jeu
    while (exit != true)
    {
        system("cls");
        afficherTitre();
        cout << "Vous avez selectionne l'option.\n\n";

        //Choisir la couleur
        cout << "Voulez vous changer la couleur du titre, du joueur 1 ou du joueur 2 / console ?\n";
        cout << "                         joueur 1(j)                    joueur 2 / console (c)\n";
        cout << "Vous pouvez quittez le jeu (x)\n";
        cout << "\n\nQue voulez vous faire ? ";
        choixDeLoption=_getwch();
        
        if (choixDeLoption == 'x')
        {
            break;
        }
        system("cls");
        afficherTitre();
        cout << "Vous avez selectionne l'option.\n\n";
        cout << "Les couleurs disponibles sont : \n";
        cout << "Gris = 7,\nbleu = 9,\nvert = 10,\ncyan = 11,\nrouge = 12,\nviolet = 13,\njaune = 14,\nblanc = 15";
        
        if (choixDeLoption == 'j')
        {
            cout << "\n\nQuelle couleur voulez-vous avoir pour le joueur 1 ? ";
            cin >> joueur1;
        }
        else if (choixDeLoption == 'c')
        {
            cout << "\n\nQuelle couleur voulez-vous avoir pour le joueur 2 / console ? ";
            cin >> joueur2;
        }
        
    }
}
