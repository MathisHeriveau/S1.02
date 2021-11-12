/**
 * @file sousProgramme.cpp
 * @author Mathis Heriveau
 * @brief Corps du module sousProgramme.h
 * @date 27 octobre 2021
 */

#include "sousProgramme.h"
#include <iostream>


//Procedure d'affichage de texte
void afficherTexteEnCouleur(string chaine, Couleur couleur, bool retourALaLigne)
{
    HANDLE idTerminal = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(idTerminal, couleur); 
    cout << chaine << flush;
    SetConsoleTextAttribute(idTerminal, gris);
    if (retourALaLigne){cout << endl;} //Retour a la ligne
}

//Procedure d'affichage du jeu
void afficherJeu(unsigned short int tableau[6][7], unsigned short int joueur1, unsigned short int joueur2)
{

    //TRAITEMENTS DU SOUS-PROGRAMME

    afficherTitre();    //Affichage du titre

    cout <<"\n   0     1     2     3     4     5     6  "; //Affichage de la premiere ligne 

    for (int i = 0; i < 6; i++) //Pour toutes les lignes
    {
        cout << "\n+-----+-----+-----+-----+-----+-----+-----+\n|" ; //Affichage de l'interface

        for (int j = 0; j < 7; j++) //Pour toutes les colonnes
        {
            switch (tableau[i][j])
            {
            case 1: afficherOcouleur(joueur1); //Affichage de O en jaune
                    cout << "|";
                break;
            case 2 : afficherOcouleur(joueur2); //Affichage de O en rouge
                    cout << "|";
                break;
            default:
                cout << "     |";   //On saute de colonne
                break;
            }
        }
    }
    cout << "\n+-----+-----+-----+-----+-----+-----+-----+" ; //Affichage de la derniere ligne
    cout << "\n                        revenir au menu(999)"; //Affichage de la possibilité de quitter 
}

//Fonction de verification de la ligne horizontale
bool verificationHorizontale(unsigned short int ligne, unsigned short int nombreAverifier, unsigned short int tableau[6][7])
{

    //Variable
    unsigned short int suite = 0; //Calcul le nombre de couleur cote a cote
    //Traitement
    for (int i = 0; i < 6; i++) //Pour toute la ligne
    {
        //Si il y en a 2 a coté
        if (tableau[ligne][i] == nombreAverifier) 
        {
            suite++; //Augmentation de la suite
            if (suite == 4) //Si il en trouve 3 fois 2 a coté le joueur a gagner 
            {return false;}
        }
        //Sinon il remet le compteur a 0
        else {suite = 0;}
    }
    return true;//Si on a rien trouvé on sort
}

//Fonction de verification de la ligne verticale
bool verificationVertical(unsigned short int colonne, unsigned short int nombreAverifier, unsigned short int tableau[6][7])
{
    //Variable
    unsigned short int suite = 0; //Calcul le nombre de couleur cote a cote
    //Traitement
    for (int i = 5; i >= 0; i--) //Pour toute la colonne
    {
        //Si il en trouve 2 a coté
        if (tableau[i][colonne] == nombreAverifier)
        {
            suite++; //Augmentation de la suite
            if (suite == 4)  //Si il en trouve 3 fois 2 a coté le joueur a gagner 
            {return false;}
        }
        else{suite = 0;} //On remet le compteur a 0
    }
    return true; //Si on trouve rien. On sort
}

//Fonction de verification de la diagonale droite
bool verificationDiagonalDroite(unsigned short int colonne, unsigned short int ligne, unsigned short int nombreAverifier, unsigned short int tableau[6][7])
{
    //Variable
    unsigned short int suite = 0;                  //Calcul le nombre de couleur cote a cote
    unsigned short int placementColonne; //Longueur de la diagonal
    unsigned short int placementLigne;     //Placement de la verification

    placementColonne = colonne;
    placementLigne = ligne;

    //Initialisation des paramettres
    //Se mettre le plus en Haut a Gauche possible
    while (placementLigne != 0 && placementColonne != 0)
    {
        placementLigne--;   //On se redecale vers le haut
        placementColonne--; //On se redecale vers la gauche
    }

    //Traitement
    //Diagonal, on se deplace en bas a gauche a chaque fois, en verfifiant si il y a pas 4 jetons cote a cote
    while (placementLigne < 5 && placementColonne < 6)
    {
        //Si on trouve 2 jetons a coter
        if (tableau[placementLigne][placementColonne] == nombreAverifier)
        {
            suite++; //Augmentation de la suite
            if (suite == 4) //Si on en trouve 3. On sort
            {return false;}
        }
        else{suite = 0;} //On remet le compteur a 0

        placementColonne++; //On se deplace vers la droite
        placementLigne++;   //On se deplace verse le bas
    }
    return true; //Si on trouve rien? On sort
}

//Fonction de verification de la diagonal gauche
bool verificationDiagonalGauche(unsigned short int colonne, unsigned short int ligne, unsigned short int nombreAverifier, unsigned short int tableau[6][7])
{
    //Variable
    unsigned short int suite = 0;                  //Calcul le nombre de couleur cote a cote
    unsigned short int placementColonne; //Longueur de la diagonal
    unsigned short int placementLigne;     //Placement de la verification

    placementColonne = colonne;
    placementLigne = ligne;


    //Initialisation des paramettres
    //Se mettre le plus en haut a droite possible
    while (placementLigne != 0 && placementColonne != 6)
    {
        placementLigne--;   //On se decale vers le haut
        placementColonne++; //On se decale vers la droite
    }
    //Traitement
    //Diagonal, on se deplace en bas a gauche a chaque fois, en verfifiant si il y a pas 4 jetons cote a cote
    while (placementLigne <= 5 && placementColonne > 0)
    {
        //Si on trouve 2 jetons cote a cote
        if (tableau[placementLigne][placementColonne] == nombreAverifier)
        {
            suite++; //Augmentation de la suite
            if (suite == 4) //Si il en trouve 3 d'affiler. On sort
            {return false;}
        }
        else{suite = 0;} //On remet le compteur a 0

        placementColonne--; //On va vers la gauche
        placementLigne++;   //On descend
    }
    return true; //Si on trouve rien. On sort
}

//Fonction de verification complete 
void verificationJeu(unsigned short int colonne, unsigned short int ligne, unsigned short int nombreAverifier, unsigned short int tableau[6][7], bool& etatVerification, string& nomDeLaVerif)
{
    //Verif Horizontale
    if (!verificationHorizontale(ligne, nombreAverifier, tableau)){etatVerification = false; nomDeLaVerif = "horizontalement"; }
    if (!verificationVertical(colonne,nombreAverifier,tableau)){etatVerification = false; nomDeLaVerif = "verticalement"; }
    if (!verificationDiagonalGauche(colonne,ligne,nombreAverifier,tableau)){etatVerification = false; nomDeLaVerif = "diagonalement (g)"; }
    if (!verificationDiagonalDroite(colonne,ligne,nombreAverifier,tableau)){etatVerification = false; nomDeLaVerif = "diagonalement (d)"; }
}

void afficherTitre(){
    system("cls");
    afficherTexteEnCouleur(" P ", bleu, false);
    afficherTexteEnCouleur("U ", jaune, false);
    afficherTexteEnCouleur("I ", rouge, false);
    afficherTexteEnCouleur("S ", bleu, false);
    afficherTexteEnCouleur("S ", jaune, false);
    afficherTexteEnCouleur("A ", rouge, false);
    afficherTexteEnCouleur("N ", bleu, false);
    afficherTexteEnCouleur("C ", jaune, false);
    afficherTexteEnCouleur("E ", rouge, false);
    afficherTexteEnCouleur(" 4\n", bleu, true);

}

void afficherOcouleur(unsigned short int couleur){
    switch (couleur)
    {
    case 7: afficherTexteEnCouleur("  O  ", gris, false); break;
    case 9: afficherTexteEnCouleur("  O  ", bleu, false); break;
    case 10: afficherTexteEnCouleur("  O  ", vert, false); break;
    case 11: afficherTexteEnCouleur("  O  ", cyan, false); break;
    case 12: afficherTexteEnCouleur("  O  ", rouge,false); break;
    case 13: afficherTexteEnCouleur("  O  ", violet,false); break;
    case 14: afficherTexteEnCouleur("  O  ", jaune,false); break;
    case 15: afficherTexteEnCouleur("  O  ", blanc,false); break;   
    }
}
