/**\
  * @file sousProgramme.cpp
  * @author Tom Planche, Mathis Hériveau
  * @brief Coprs du module sousProgramme
  * @remarks Ce corps permet un fonctionnement sous architecture Windows ainsi que macOs. Tous les commentaires liés aux sous programmes sont détaillés dans sousProgramme.h
  * @date 24-11-2021
  * 
\**/

#include "sousProgramme.h"

// Si l'appareil utilisé est sous Windows 
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
    #include <conio.h>
// Sinon
#else 
    #include <unistd.h>
#endif

// Si L'appareil utilisé est sous macOs
# ifdef __APPLE__

    #define RESET "\033[0m"
    #define ROUGE "\033[0;31m"
    #define VERT "\033[0;32m"
    #define JAUNE "\033[0;33m"
    #define BLEU "\033[0;34m"
    #define VIOLET "\033[0;35m"
    #define CYAN "\033[0;36m"
    #define BLANC "\033[0;37m"

    /**\
      * @brief Retourne le code couleur de la couleur passée en paramètre
      * 
      * @param couleur Couleur désirée
      * @return string Couleur sous forme de string
    \**/
    string getCodeCouleur(Couleur couleur)
    {
        string codeCouleur;
        switch (couleur)
        {
        case bleu:
            codeCouleur = BLEU;
            break;

        case vert:
            codeCouleur = VERT;
            break;

        case cyan:
            codeCouleur = CYAN;
            break;

        case rouge:
            codeCouleur = ROUGE;
            break;

        case violet:
            codeCouleur = VIOLET;
            break;

        case jaune:
            codeCouleur = JAUNE;
            break;

        case blanc:
            codeCouleur = BLANC;
            break;

        default:
            codeCouleur = RESET;
            break;
        }

        return codeCouleur;
    }
# endif


int random(int min, int max)
{
    std::default_random_engine generateur;
    std::uniform_int_distribution<int> distributionNombres;
    unsigned int tempsActuel = static_cast<unsigned int>(steady_clock::now().time_since_epoch().count());
    generateur.seed(tempsActuel);

    return ((distributionNombres(generateur) % (max + 1)) + min);
}


void afficherTexteEnCouleur(string chaine, Couleur couleur, bool retourALaLigne) {
    # ifdef _WIN32
        HANDLE idTerminal = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(idTerminal, couleur);
        cout << chaine << flush;
        SetConsoleTextAttribute(idTerminal, gris);
    # else
        string codeCouleur = getCodeCouleur(couleur);
        cout << codeCouleur << chaine << RESET << flush;
    # endif

    if (retourALaLigne) {
        cout << endl;
    }
}


// Procédure d'affichage du jeu
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
            {return true;}
        }
        //Sinon il remet le compteur a 0
        else {suite = 0;}
    }
    return false;//Si on a rien trouvé on sort
}

//Fonction de verification de la ligne verticale
bool verificationVerticale(unsigned short int colonne, Case caseDuJeu, Case grille[6][7])
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
            {return true;}
        }
        else{suite = 0;} //On remet le compteur a 0
    }
    return false; //Si on trouve rien. On sort
}

//Fonction de verification de la diagonale droite
bool verificationDiagonaleDroite(unsigned short int colonne, unsigned short int ligne, Case caseDuJeu, Case grille[6][7])
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
            {return true;}
        }
        else {suite = 0;} //On remet le compteur a 0

        placementColonne++; //On se deplace vers la droite
        placementLigne++;   //On se deplace verse le bas
    }
    return false; //Si on trouve rien? On sort
}

//Fonction de verification de la diagonal gauche
bool verificationDiagonaleGauche(unsigned short int colonne, unsigned short int ligne, Case caseDuJeu, Case grille[6][7])
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
            {return true;}
        }
        else{suite = 0;} //On remet le compteur a 0

        placementColonne--; //On va vers la gauche
        placementLigne++;   //On descend
    }
    return false; //Si on trouve rien. On sort
}

void effacer() {
    # ifdef _WIN32
        HANDLE idTerminal;
        CONSOLE_SCREEN_BUFFER_INFO caracteristiquesTerminal;
        DWORD count;
        DWORD nbreCellulesDansTerminal;
        COORD coordonneesOrigine = {0, 0};

        idTerminal = GetStdHandle(STD_OUTPUT_HANDLE);
        if (idTerminal == INVALID_HANDLE_VALUE)
        {
            return;
        }

        /* Calculer le nombre de cellules du terminal */
        if (!GetConsoleScreenBufferInfo(idTerminal, &caracteristiquesTerminal))
        {
            return;
        }
        nbreCellulesDansTerminal = caracteristiquesTerminal.dwSize.X * caracteristiquesTerminal.dwSize.Y;

        /* Remplir le terminal avec des espaces */
        if (!FillConsoleOutputCharacter(idTerminal, (TCHAR)' ', nbreCellulesDansTerminal, coordonneesOrigine, &count))
        {
            return;
        }

        /*Remplir le terminal avec les couleurs courantes */
        if (!FillConsoleOutputAttribute(
                idTerminal,
                caracteristiquesTerminal.wAttributes,
                nbreCellulesDansTerminal,
                coordonneesOrigine,
                &count))
        {
            return;
        }

        /* Déplacer le curseur au début du terminal */
        SetConsoleCursorPosition(idTerminal, coordonneesOrigine);
    #else
        cout << "\033[2J\033[1;1H";
    #endif
}


void afficherTitre(){
    effacer();
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


unsigned short int saisieVerifCase() {
    string str;
    regex regex_pattern("[0-6]|999");
    do {
        cout << "Saisissez une case : ";
        cin >> str;
    } while(!regex_match(str, regex_pattern));

    return stoi(str);
}
