/**
 * @file sousProgramme.cpp
 * @author Mathis Heriveau, Tom Planche
 * @brief Corps du module sousProgramme.h
 * @date 27 octobre 2021
 */

#include "sousProgramme.h"
#include <conio.h> // pour la fonction _getch utilisée dans la procédure pause()
#include <chrono>  // pour la fonction now() utilisée dans la fonction random()
#include <random>  // pour la fonction random

//Fonction random
int random(int min, int max)
{
    std::default_random_engine generateur;
    std::uniform_int_distribution<int> distributionNombres;
    unsigned int tempsActuel = static_cast<unsigned int>(chrono::steady_clock::now().time_since_epoch().count());
    generateur.seed(tempsActuel);

    return ((distributionNombres(generateur) % (max + 1)) + min);
}


//Fonction pause avec touche
void pause(unsigned int dureeEnSecondes)
{
    if (dureeEnSecondes == 0) 
    {
        //Mise en pause jusqu'a la pression de la touche
        char touche;
        touche = char(_getch());    
        touche = ' ';
        cout << touche << endl;
    }
    else
    {
        //Pause de dureeEnSecondes * 10000
        const unsigned short int UNE_MILLISECONDE = 1000;
        Sleep(dureeEnSecondes * UNE_MILLISECONDE); 
    }
}

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
void afficherJeu(Case grille[6][7])
{

    //TRAITEMENTS DU SOUS-PROGRAMME

    cout <<"\n   0     1     2     3     4     5     6  "; //Affichage de la premiere ligne 

    for (int i = 0; i < 6; i++) //Pour toutes les lignes
    {
        cout << "\n+-----+-----+-----+-----+-----+-----+-----+\n|" ; //Affichage de l'interface
        for (int j = 0; j < 7; j++) //Pour toutes les colonnes
        {
            if ((grille[i][j]) == pionJaune)   //Si c'est le numero du joueur 1
            {
                afficherTexteEnCouleur("  O  ", jaune, false);
                cout << "|";
            }
            else if (grille[i][j] == pionRouge) //Si c'est le numero du joueur 2
            {
                afficherTexteEnCouleur("  O  ", rouge, false);
                cout << "|";
            }
            else    //Si c'est une case vide
            {
                cout << "     |";   //On saute de colonne
            }
        }
    }
    cout << "\n+-----+-----+-----+-----+-----+-----+-----+" ; //Affichage de la derniere ligne
    cout << "\n                        revenir au menu(999)";
    
}

//Fonction de verification de la ligne horizontale
bool verificationHorizontale(unsigned short int ligne, Case caseDuJeu, Case grille[6][7])
{

    //Variable
    unsigned short int suite; //Calcul le nombre de couleur cote a cote

    //Initialisation
    suite = 0;

    //Traitement
    for (int i = 1; i < 7; i++) //Pour toute la ligne
    {
        //Si il y en a 2 a coté
        if (grille[ligne][i] == caseDuJeu && caseDuJeu == grille[ligne][i - 1]) 
        {
            suite++; //Augmentation de la suite
            if (suite == 3) //Si il en trouve 3 fois 2 a coté le joueur a gagner 
            {return false;}
        }
        //Sinon il remet le compteur a 0
        else {suite = 0;}
    }
    return true;//Si on a rien trouvé on sort
}

//Fonction de verification de la ligne verticale
bool verificationVertical(unsigned short int colonne, Case caseDuJeu, Case grille[6][7])
{
    //Variable
    unsigned short int suite; //Calcul le nombre de couleur cote a cote

    //Initialisation
    suite = 0;

    //Traitement
    for (int i = 5; i > 0; i--) //Pour toute la colonne
    {
        //Si il en trouve 2 a coté
        if (grille[i][colonne] == caseDuJeu && caseDuJeu == grille[i - 1][colonne])
        {
            suite++; //Augmentation de la suite
            if (suite == 3)  //Si il en trouve 3 fois 2 a coté le joueur a gagner 
            {return false;}
        }
        else{suite = 0;} //On remet le compteur a 0
    }
    return true; //Si on trouve rien. On sort
}

//Fonction de verification de la diagonale droite
bool verificationDiagonalDroite(unsigned short int colonne, unsigned short int ligne, Case caseDuJeu, Case grille[6][7])
{
    //Variable
    unsigned short int placementColonne; //Longueur de la diagonal
    unsigned short int placementLigne;     //Placement de la verification
    unsigned short int suite; //Calcul le nombre de couleur cote a cote

    //Initialisation
    placementColonne = colonne;
    placementLigne = ligne;
    suite = 0;

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
        if (grille[placementLigne][placementColonne] == caseDuJeu && grille[placementLigne + 1][placementColonne + 1] == caseDuJeu)
        {
            suite++; //Augmentation de la suite
            if (suite == 3) //Si on en trouve 3. On sort
            {return false;}
        }
        else {suite = 0;} //On remet le compteur a 0

        placementColonne++; //On se deplace vers la droite
        placementLigne++;   //On se deplace verse le bas
    }
    return true; //Si on trouve rien? On sort
}

//Fonction de verification de la diagonal gauche
bool verificationDiagonalGauche(unsigned short int colonne, unsigned short int ligne, Case caseDuJeu, Case grille[6][7])
{
    //Variable
    unsigned short int placementColonne; //Longueur de la diagonal
    unsigned short int placementLigne;     //Placement de la verification
    unsigned short int suite; //Calcul le nombre de couleur cote a cote

    //Initialisation
    placementColonne = colonne;
    placementLigne = ligne;
    suite = 0;

    //Initialisation des paramettres
    //Se mettre le plus en haut a droite possible
    while (placementLigne != 0 && placementColonne != 6)
    {
        placementLigne--;   //On se decale vers le haut
        placementColonne++; //On se decale vers la droite
    }

    //Traitement
    //Diagonal, on se deplace en bas a gauche a chaque fois, en verfifiant si il y a pas 4 jetons cote a cote
    while (placementLigne < 5 && placementColonne > 0)
    {
        //Si on trouve 2 jetons cote a cote
        if (grille[placementLigne][placementColonne] == caseDuJeu && grille[placementLigne + 1][placementColonne - 1] == caseDuJeu)
        {
            suite++; //Augmentation de la suite
            if (suite == 3) //Si il en trouve 3 d'affiler. On sort
            {return false;}
        }
        else{suite = 0;} //On remet le compteur a 0

        placementColonne--; //On va vers la gauche
        placementLigne++;   //On descend
    }
    return true; //Si on trouve rien. On sort
}

//Fonction de verification complete 
bool verificationJeu(unsigned short int colonne, unsigned short int ligne, Case caseDuJeu, Case grille[6][7])
{
    //Variable
    //Traitement
    
    //Verif Horizontale
    if (!verificationHorizontale(ligne, caseDuJeu, grille)) //Si il trouve quelque chose on sort.
    {return false;}

    //Verif Vertical
    if (!verificationVertical(colonne, caseDuJeu, grille)) //Si il trouve quelque chose on sort.
    {return false;}

    //Verif de haut en bas de gauche a droite

    if (!verificationDiagonalDroite(colonne, ligne, caseDuJeu, grille)) //Si il trouve quelque chose on sort.
    {return false;}

    //Verif de haut en bas de droite a gauche
    if (!verificationDiagonalGauche(colonne, ligne, caseDuJeu, grille)) //Si il trouve quelque chose on sort.
    {return false;}

    return true; //Si on trouve rien. On sort
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
