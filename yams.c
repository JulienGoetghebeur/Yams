/**
* @brief jeu de Yams
* @author GOETGHEBEUR Julien
* @version 2.0
* @date 28 novembre 2021
*
* 
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

/**
 * @def NB_LIGNE
 * @brief Nombre de lignes dans la feuille de marque.
 */
const int NB_LIGNE = 18;
/**
 * @def NB_JOUEUR
 * @brief Nombre de colonne dans la feuille de marque.
 */
const int NB_JOUEUR = 2;
/**
 * @def NB_DE
 * @brief Nombre de dés dans la partie.
 */
const int NB_DE = 5;
/**
 * @def NB_MANCHE   
 * @brief Nombre de manche dans une partie.
 */
const int NB_MANCHE = 13;

/**
 * @typedef tFeuilleDeScore[NB_JOUEUR][NB_LIGNE]
 * @brief Type de tableau à deux dimensions de NB_JOUEUR sur NB_LIGNE entiers
 *  Tableau correspondant à la feuille de marque.
 */
typedef int tFeuilleDeScore[NB_JOUEUR][NB_LIGNE];

void demandeNom(char nom[20]);
void afficherFeuilleDeMarque(int joueur, tFeuilleDeScore feuilleDeMarque, char nomJoueur1[20], char nomJoueur2[20]);
void lancerDes(int tabDeValide[], int tabDeLance[]);
void validationLance(int tabDeValide[]);
void initFeuilleDeMarque(tFeuilleDeScore feuilleDeMarque);
void affectationScore(int joueur, int tabDeLance[], tFeuilleDeScore feuilleDeMarque);
void afficherLesScores(tFeuilleDeScore feuilleDeMarque, char nomJoueur1[20], char nomJoueur2[20]);
void afficher_ligne(int n);
int randInfBorne(int borne);
void triTabDe(int tab[]);
int comptageCombinaison(char combinaison[20], int tabDeLance[]);
bool estPlein(int tab[NB_DE]);
void actuFeuilleDeMarque(tFeuilleDeScore feuilleDeMarque, int joueur);
void initTabDe(int tabLance[], int tabValid[]);

int main()
{
    srand(time(NULL));
    char nomJoueur1[20];
    char nomJoueur2[20];
    int nbEssaie;
    int joueur;
    int manche;
    tFeuilleDeScore feuilleDeMarque;
    int tabDeLance[] = {0, 0, 0, 0, 0};
    int tabDeValide[] = {0, 0, 0, 0, 0};

    demandeNom(nomJoueur1);
    demandeNom(nomJoueur2);
    initFeuilleDeMarque(feuilleDeMarque);
    nbEssaie = 0;

    for (manche = 0; manche < NB_MANCHE; manche++)
    {
        for (joueur = 0; joueur < NB_JOUEUR; joueur++)
        {
            afficherFeuilleDeMarque(joueur + 1, feuilleDeMarque, nomJoueur1, nomJoueur2);
            nbEssaie = 3;
            initTabDe(tabDeLance, tabDeValide);

            lancerDes(tabDeValide, tabDeLance);
            nbEssaie -= 1;
            while (nbEssaie >= 1)
            {
                validationLance(tabDeValide);
                lancerDes(tabDeValide, tabDeLance);
                nbEssaie -= 1;
            }

            affectationScore(joueur, tabDeLance, feuilleDeMarque);
            actuFeuilleDeMarque(feuilleDeMarque, joueur);
        }
    }
    afficherLesScores(feuilleDeMarque, nomJoueur1, nomJoueur2);
    // test();

    return EXIT_SUCCESS;
}

/**
 * @fn void demandeNom(char nom[20])
 * 
 * @brief Permet au joueur de choisir un nom.
 * 
 * @param nom : Chaine de caractère de maximum 2à caractères.
 * 
 * Affecte à nom la chaine de caractère rentré par joueur.
 */
void demandeNom(char nom[20])
{
    // Demande au joueur de saisir un nom puis renvoie la chaine de caractère saisi
    // par le joueur

    printf("Nom du Joueur ? \n");
    scanf("%s", nom);
}

/**
 * @fn afficherFeuilleDeMarque(int joueur, tFeuilleDeScore feuilleDeMarque, char nomJoueur1[20], char nomJoueur2[20])
 * 
 * @brief Affiche la feuille de marque d'un ou deux joueur.
 * 
 * @param joueur : Entier qui indique quelle feuille de marque afficher.
 *      Si joueur = 0 : La fonction affiche la feuille de marque des deux joueurs.
 *      Si joueur = 1 : La fonction affiche la feuille de marque du joueur 1.
 *      Si joueur = 2 : La fonction affiche la feuille de marque du joueur 2.
 * @param feuilleDeMarque : Tableau de type tFeuilleDeScore qui correspond à la feuille de marque des joueurs.
 * @param nomJoueur1 : Chaine de caractère qui correspond au nom du joueur 1.
 * @param nomJoueur2 : Chaine de caractère qui correspond au nom du joueur 2.
 * 
 * Affiche dans la console la feuille de marque correspondant au tableau feuilleDeMarque.
 */
void afficherFeuilleDeMarque(int joueur, tFeuilleDeScore feuilleDeMarque, char nomJoueur1[20], char nomJoueur2[20])
{
    // Affiche la feuille de marque correspondant au tableau feuilleDeMarque
    //   • Si joueur = 0 : la fonction affiche la feuille de marque des deux joueur
    //   • Si joueur = 1 : la fonction affiche la feuille de marque du joueur 1
    //   • Si joueur = 2 : la fonction affiche la feuille de marque du joueur 2
    int i;
    char nom[20];

    if (joueur == 0)
    {
        afficher_ligne(40);
        printf("Feuille de marque  |  %s  |  %s  |\n", nomJoueur1, nomJoueur2);
        afficher_ligne(40);
        printf("Total de 1 :\t\t  %3d \t   %3d\n", feuilleDeMarque[0][1], feuilleDeMarque[1][1]);
        printf("Total de 2 :\t\t  %3d \t   %3d\n", feuilleDeMarque[0][2], feuilleDeMarque[1][2]);
        printf("Total de 3 :\t\t  %3d \t   %3d\n", feuilleDeMarque[0][3], feuilleDeMarque[1][3]);
        printf("Total de 4 :\t\t  %3d \t   %3d\n", feuilleDeMarque[0][4], feuilleDeMarque[1][4]);
        printf("Total de 5 :\t\t  %3d \t   %3d\n", feuilleDeMarque[0][5], feuilleDeMarque[1][5]);
        printf("Total de 6 :\t\t  %3d \t   %3d\n", feuilleDeMarque[0][6], feuilleDeMarque[1][6]);
        printf("Bonus(si > 62(35)):\t  %3d  \t   %3d\n", feuilleDeMarque[0][7], feuilleDeMarque[1][7]);
        printf("> Total supérieur :\t  %3d  \t   %3d\n", feuilleDeMarque[0][8], feuilleDeMarque[1][8]);
        afficher_ligne(40);
        printf("Brelan :\t\t  %3d \t   %3d\n", feuilleDeMarque[0][9], feuilleDeMarque[1][9]);
        printf("Carré :\t\t\t  %3d \t   %3d\n", feuilleDeMarque[0][10], feuilleDeMarque[1][10]);
        printf("Full House :\t\t  %3d \t   %3d\n", feuilleDeMarque[0][11], feuilleDeMarque[1][11]);
        printf("Petite suite :\t\t  %3d \t   %3d\n", feuilleDeMarque[0][12], feuilleDeMarque[1][12]);
        printf("Grande suite :\t\t  %3d \t   %3d\n", feuilleDeMarque[0][13], feuilleDeMarque[1][13]);
        printf("Yams :\t\t\t  %3d \t   %3d\n", feuilleDeMarque[0][14], feuilleDeMarque[1][14]);
        printf("Chance :\t\t  %3d \t   %3d\n", feuilleDeMarque[0][15], feuilleDeMarque[1][15]);
        printf("> Total inférieur :\t  %3d \t   %3d\n", feuilleDeMarque[0][16], feuilleDeMarque[1][16]);
        afficher_ligne(40);
        printf(">> Total :\t\t  %3d \t   %3d\n", feuilleDeMarque[0][17], feuilleDeMarque[1][17]);
        afficher_ligne(40);
    }
    else
    {
        if (joueur == 1)
        {
            strcpy(nom, nomJoueur1);
        }
        else
        {
            strcpy(nom, nomJoueur2);
        }
        i = joueur - 1;
        afficher_ligne(40);
        printf("Feuille de marque  |  %s  |\n", nom);
        afficher_ligne(40);
        printf("Total de 1 :\t\t  %3d\n", feuilleDeMarque[i][1]);
        printf("Total de 2 :\t\t  %3d\n", feuilleDeMarque[i][2]);
        printf("Total de 3 :\t\t  %3d\n", feuilleDeMarque[i][3]);
        printf("Total de 4 :\t\t  %3d\n", feuilleDeMarque[i][4]);
        printf("Total de 5 :\t\t  %3d\n", feuilleDeMarque[i][5]);
        printf("Total de 6 :\t\t  %3d\n", feuilleDeMarque[i][6]);
        printf("Bonus(si > 62(35)):\t  %3d\n", feuilleDeMarque[i][7]);
        printf("> Total supérieur :\t  %3d\n", feuilleDeMarque[i][8]);
        afficher_ligne(40);
        printf("Brelan :\t\t  %3d\n", feuilleDeMarque[i][9]);
        printf("Carré :\t\t\t  %3d\n", feuilleDeMarque[i][10]);
        printf("Full House :\t\t  %3d\n", feuilleDeMarque[i][11]);
        printf("Petite suite :\t\t  %3d\n", feuilleDeMarque[i][12]);
        printf("Grande suite :\t\t  %3d\n", feuilleDeMarque[i][13]);
        printf("Yams :\t\t\t  %3d\n", feuilleDeMarque[i][14]);
        printf("Chance :\t\t  %3d\n", feuilleDeMarque[i][15]);
        printf("> Total inférieur :\t  %3d\n", feuilleDeMarque[i][16]);
        afficher_ligne(40);
        printf(">> Total :\t\t  %3d\n", feuilleDeMarque[i][17]);
        afficher_ligne(40);
    }
}

/**
 * @fn bool estPlein(int tab[NB_DE])
 * 
 * @brief Vérifie si un tableau est plein.
 * 
 * @param tab : Tableau de NB_DE entier 
 * @return true si tab est remplie de 1.
 * @return false si tab n'est pas remplie de 1.
 * 
 * Parcours le tableau tab pour vérifier si toutes les valeurs sont à 1.
 */
bool estPlein(int tab[NB_DE])
{
    bool res = true;
    int i;
    for (i = 0; i < NB_DE; i++)
    {
        if (tab[i] != 1)
        {
            res = false;
        }
    }
    return res;
}

/**
 * @fn void lancerDes(int tabDeValide[], int tabDeLance[])
 * 
 * @brief Remplace les valeurs de tabDeLance non validés par des nouvelles valeurs.
 * 
 * @param tabDeValide : tableau de NB_DE entier qui correspond aux dés validés par l'utilisateur. Est conposé de 0 ou de 1.
 * @param tabDeLance : tableau de NB_DE entier qui correspond aux dés lancés. Est composé d'entiers naturels compris entre 1 et 6.
 * 
 * Remplace chaque valeurs de tabDeLance par des nombres aléatoires si la valeur
 * de tabDeValide au même index est 0.
 * 
 */
void lancerDes(int tabDeValide[], int tabDeLance[])
{
    // • Remplace chaque valeurs de tabDeLance par un nombre pseudo-aléatoire
    // compris entre 1 et 6 si sont index n'est pas dans tabDeValide
    //    • Exemple : tabDeValide = [1,3,4] donc la fonction va modifier les
    //       valeurs de tabDeLance correspondant aux index 2 et 5
    // • Vérifie d’abord si tous les dés ont été validés, au quel cas la
    // procédure se termine directement.
    int i;
    if (estPlein(tabDeValide) == false)
    {
        printf("Lancé des dés...\n");
        printf("Dés : \n");
        for (i = 0; i < NB_DE; i++)
        {
            if (tabDeValide[i] == 0)
            {
                tabDeLance[i] = randInfBorne(6);
            }
        }
        printf("┌───┬───┬───┬───┬───┐\n");
        printf("│ %d │ %d │ %d │ %d │ %d │\n", tabDeLance[0], tabDeLance[1], tabDeLance[2], tabDeLance[3], tabDeLance[4]);
        printf("└───┴───┴───┴───┴───┘\n");
    }
}

/**
 * @fn void validationLance(int tabDeValide[])
 * 
 * @brief Le joueur choisie les dés qu'il veut valider.
 * 
 * @param tabDeValide : tableau de NB_DE entier qui correspond aux dés validés par l'utilisateur. Est conposé de 0 ou de 1.
 * 
 * Le joueur rentre un entier désignant le dé qu'il veut valider (de 1 à 6) et les valeurs correspondantes(de 0 à 5 (décalage de -1)) passe alors de 0 à 1.
 * 
 */
void validationLance(int tabDeValide[])
{
    // • Demande au joueur de saisir les numéro des dés qu'il veut conserver
    //  et les ajoute dans tabDeValide
    // • Si tous les dés sont déjà validés, la procédures se termine directement
    int i = 0;
    int input;
    if (estPlein(tabDeValide) == false)
    {
        printf("Entrez un dé à valider ou 0 pour mettre fin à la saisie.\n");
        scanf("%d", &input);
        while ((i < NB_DE) && (input != 0))
        {
            if ((input >= 0) && (input < 6) && (tabDeValide[input - 1] == 0))
            {
                tabDeValide[input - 1] = 1;
            }
            else if (tabDeValide[input - 1] == 1)
            {
                printf("Erreur. Vous avez déjà validé ce dé. Réessayer.\n");
            }
            else
            {
                printf("Erreur. Vous n'avez pas saisie un nombre entre 1 et 5. Réessayer.\n");
            }

            printf("Entrez un dé à valider ou 0 pour mettre fin à la saisie.\n");
            scanf("%d", &input);
        }
        printf("\nVous avez validé les dés : ");
        for (i = 0; i < NB_DE; i++)
        {
            if (tabDeValide[i] == 1)
            {
                printf(" %d ", i + 1);
            }
        }
        printf("\n");
    }
}

/**
 * @fn void initFeuilleDeMarque(tFeuilleDeScore feuilleDeMarque)
 * 
 * @brief Initialise le tableau feuilleDeMarque.
 * 
 * @param feuilleDeMarque : tableau du type tFeuilleDeScore qui correspond à la feuille de marque des joueurs.
 * 
 * Met chaque valeur de feuilleDeMarque à -1.
 * 
 */
void initFeuilleDeMarque(tFeuilleDeScore feuilleDeMarque)
{
    //met toutes les valeurs de feuilleDeMarque à -1
    int i, j;

    for (i = 0; i < NB_JOUEUR; i++)
    {
        for (j = 1; j < NB_LIGNE; j++)
        {
            feuilleDeMarque[i][j] = -1;
        }
    }
}

/**
 * @fn void affectationScore(int joueur, int tabDeLance[], tFeuilleDeScore feuilleDeMarque)
 * 
 * @brief Le joueur choisie à quelle combinaison il affecte son lancé.
 * 
 * @param joueur : Entier qui correspond au joueur qui joue. Peut prendre la valeur 0 ou 1.
 * @param tabDeLance : tableau de NB_DE entier qui correspond aux dés lancés. Est composé d'entiers naturels compris entre 1 et 6.
 * @param feuilleDeMarque : tableau du type tFeuilleDeScore qui correspond à la feuille de marque des joueurs.
 * 
 * Demande au joueur à quelle combinaison il veut affecter son lancé et ajoute le nombre de points correspondant dans la case de feuilleDeMarque si elle n'est pas déja prise.
 * 
 */
void affectationScore(int joueur, int tabDeLance[], tFeuilleDeScore feuilleDeMarque)
{
    // Demande au joueur à quelle combinaison il veut affecter son lancé et
    // l’ajoute dans feuilleDeMarque si la case n’est pas déjà remplie
    bool correct = false;
    char combinaison[20];
    while (correct == false)
    {
        printf("À quel combinaison voulez vous affecter votre lancer ? \nAttention si vous saisissez une combinaison qui ne correspond pas, elle sera sacrifié (0pts).\n");
        printf("Entrez le nom de la combinaison sans majuscule et avec un '_' pour les espaces.\n");
        scanf("%s", combinaison);

        if (strcmp(combinaison, "1") == 0)
        {
            if (feuilleDeMarque[joueur][1] == -1)
            {
                feuilleDeMarque[joueur][1] = comptageCombinaison(combinaison, tabDeLance);
                correct = true;
            }
            else
            {
                printf("Combinaison déja affectée.");
            }
        }
        else if (strcmp(combinaison, "2") == 0)
        {
            if (feuilleDeMarque[joueur][2] == -1)
            {
                feuilleDeMarque[joueur][2] = comptageCombinaison(combinaison, tabDeLance);
                correct = true;
            }
            else
            {
                printf("Combinaison déja affectée.");
            }
        }
        else if (strcmp(combinaison, "3") == 0)
        {
            if (feuilleDeMarque[joueur][3] == -1)
            {
                feuilleDeMarque[joueur][3] = comptageCombinaison(combinaison, tabDeLance);
                correct = true;
            }
            else
            {
                printf("Combinaison déja affectée.");
            }
        }
        else if (strcmp(combinaison, "4") == 0)
        {
            if (feuilleDeMarque[joueur][4] == -1)
            {
                feuilleDeMarque[joueur][4] = comptageCombinaison(combinaison, tabDeLance);
                correct = true;
            }
            else
            {
                printf("Combinaison déja affectée.");
            }
        }
        else if (strcmp(combinaison, "5") == 0)
        {
            if (feuilleDeMarque[joueur][5] == -1)
            {
                feuilleDeMarque[joueur][5] = comptageCombinaison(combinaison, tabDeLance);
                correct = true;
            }
            else
            {
                printf("Combinaison déja affectée.");
            }
        }
        else if (strcmp(combinaison, "6") == 0)
        {
            if (feuilleDeMarque[joueur][6] == -1)
            {
                feuilleDeMarque[joueur][6] = comptageCombinaison(combinaison, tabDeLance);
                correct = true;
            }
            else
            {
                printf("Combinaison déja affectée.");
            }
        }
        else if (strcmp(combinaison, "brelan") == 0)
        {
            if (feuilleDeMarque[joueur][9] == -1)
            {
                feuilleDeMarque[joueur][9] = comptageCombinaison(combinaison, tabDeLance);
                correct = true;
            }
            else
            {
                printf("Combinaison déja affectée.");
            }
        }
        else if (strcmp(combinaison, "carré") == 0)
        {
            if (feuilleDeMarque[joueur][10] == -1)
            {
                feuilleDeMarque[joueur][10] = comptageCombinaison(combinaison, tabDeLance);
                correct = true;
            }
            else
            {
                printf("Combinaison déja affectée.");
            }
        }
        else if (strcmp(combinaison, "full_house") == 0)
        {
            if (feuilleDeMarque[joueur][11] == -1)
            {
                feuilleDeMarque[joueur][11] = comptageCombinaison(combinaison, tabDeLance);
                correct = true;
            }
            else
            {
                printf("Combinaison déja affectée.");
            }
        }
        else if (strcmp(combinaison, "petite_suite") == 0)
        {
            if (feuilleDeMarque[joueur][12] == -1)
            {
                feuilleDeMarque[joueur][12] = comptageCombinaison(combinaison, tabDeLance);
                correct = true;
            }
            else
            {
                printf("Combinaison déja affectée.");
            }
        }
        else if (strcmp(combinaison, "grande_suite") == 0)
        {
            if (feuilleDeMarque[joueur][13] == -1)
            {
                feuilleDeMarque[joueur][13] = comptageCombinaison(combinaison, tabDeLance);
                correct = true;
            }
            else
            {
                printf("Combinaison déja affectée.");
            }
        }
        else if (strcmp(combinaison, "yams") == 0)
        {
            if (feuilleDeMarque[joueur][14] == -1)
            {
                feuilleDeMarque[joueur][14] = comptageCombinaison(combinaison, tabDeLance);
                correct = true;
            }
            else
            {
                printf("Combinaison déja affectée.");
            }
        }
        else if (strcmp(combinaison, "chance") == 0)
        {
            if (feuilleDeMarque[joueur][15] == -1)
            {
                feuilleDeMarque[joueur][15] = comptageCombinaison(combinaison, tabDeLance);
                correct = true;
            }
            else
            {
                printf("Combinaison déja affectée.");
            }
        }
        else
        {
            printf("Mauvaise saisie : '%s'. Réésayer.\n", combinaison);
        }
    }
}

/**
 * @fn void afficherLesScores(tFeuilleDeScore feuilleDeMarque, char nomJoueur1[20], char nomJoueur2[20])
 * 
 *  @brief Affiche les scores de la partie.
 * 
 * @param feuilleDeMarque : tableau du type tFeuilleDeScore qui correspond à la feuille de marque des joueurs.
 * @param nomJoueur1 : Chaine de caractère qui correspond au nom du joueur 1.
 * @param nomJoueur2 : Chaine de caractère qui correspond au nom du joueur 2.
 * 
 * Affiche un message de fin de partie. Utilise afficherFeuilleDeMarque() puis affiche le vainqueur et son score final.
 * 
 */
void afficherLesScores(tFeuilleDeScore feuilleDeMarque, char nomJoueur1[20], char nomJoueur2[20])
{
    // Utilise afficherFeuilleDeMarque(0) et affiche le vainqueur
    // avec son score final
    printf("\nPARTIE TERMINÉ !!\n");
    printf("\nScore final :\n");
    afficherFeuilleDeMarque(0, feuilleDeMarque, nomJoueur1, nomJoueur2);
    if (feuilleDeMarque[0][17] < feuilleDeMarque[1][17])
    {
        printf("Le vainqueur est %s avec un score de : %d\n", nomJoueur2, feuilleDeMarque[1][17]);
    }
    else
    {
        printf("Le vainqueur est %s avec un score de : %d\n", nomJoueur1, feuilleDeMarque[0][17]);
    }
}

/**
 * @fn void afficher_ligne(int n)
 * 
 * @brief Affiche une ligne de n tiret
 * 
 * @param n : Entier correspondant au nombre de tiret.
 */
void afficher_ligne(int n)
{
    // affiche une ligne de tiret

    int i;
    i = 1;
    while (i <= n)
    {
        printf("—");
        i += 1;
    }
    printf("\n");
}

/**
 * @fn int randInfBorne(int borne)
 * 
 * @brief Renvoie un nombre pseudo-aléatoire inférieur à borne.
 * 
 * @param borne : Entier qui désigne la borne que les nombre aléatoire ne doit pas dépasser.
 * @return int : nombre pseudo-aléatoire inférieur à borne.
 */
int randInfBorne(int borne)
{
    return ((rand() % borne) + 1);
}

/**
 * @fn void triTabDe(int tab[])
 * 
 * @brief Trie tab dans l'ordre croissant.
 * 
 * @param tab : tableau de NB_DE entier qui doit être trié.
 */
void triTabDe(int tab[])
{
    int i, j, min, indmin, tmp;
    for (i = 0; i < NB_DE; i++)
    {
        min = tab[i];
        indmin = i;
        for (j = i + 1; j < NB_DE; j++)
        {
            if (tab[j] < min)
            {
                min = tab[j];
                indmin = j;
            }
        }
        tmp = tab[i];
        tab[i] = tab[indmin];
        tab[indmin] = tmp;
    }
}

/**
 * @fn int comptageCombinaison(char combinaison[20], int tabDeLance[])
 * 
 * @brief compte le nombre de point qu'on obtient en fonction de la combinaison et des dés.
 * 
 * @param combinaison : chaine de caractères de 20 caractères maximum qui correspond à la combianison choisi par le joueur.
 * @param tabDeLance : tableau de NB_DE entier qui correspond aux dés lancés. Est composé d'entiers naturels compris entre 1 et 6.
 * @return int : le nombre de points obtenu.
 */
int comptageCombinaison(char combinaison[20], int tabDeLance[])
{
    int i, j, h, compteur, points, tmp;
    i = 0;
    j = 0;
    h = 0;
    compteur = 0;
    points = 0;
    tmp = 0;

    if ((strcmp(combinaison, "1") == 0))
    {
        for (i = 0; i < NB_DE; i++)
        {
            if (tabDeLance[i] == 1)
            {
                points += tabDeLance[i];
            }
        }
    }
    else if (strcmp(combinaison, "2") == 0)
    {
        for (i = 0; i < NB_DE; i++)
        {
            if (tabDeLance[i] == 2)
            {
                points += tabDeLance[i];
            }
        }
    }
    else if (strcmp(combinaison, "3") == 0)
    {
        for (i = 0; i < NB_DE; i++)
        {
            if (tabDeLance[i] == 3)
            {
                points += tabDeLance[i];
            }
        }
    }
    else if (strcmp(combinaison, "4") == 0)
    {
        for (i = 0; i < NB_DE; i++)
        {
            if (tabDeLance[i] == 4)
            {
                points += tabDeLance[i];
            }
        }
    }
    else if (strcmp(combinaison, "5") == 0)
    {
        for (i = 0; i < NB_DE; i++)
        {
            if (tabDeLance[i] == 5)
            {
                points += tabDeLance[i];
            }
        }
    }
    else if (strcmp(combinaison, "6") == 0)
    {
        for (i = 0; i < NB_DE; i++)
        {
            if (tabDeLance[i] == 6)
            {
                points += tabDeLance[i];
            }
        }
    }
    else if (strcmp(combinaison, "brelan") == 0)
    {
        for (i = 1; i <= 6; i++)
        {
            compteur = 0;
            for (j = 0; j < NB_DE; j++)
            {
                if (tabDeLance[j] == i)
                {
                    compteur += 1;
                    tmp += tabDeLance[j];
                }
            }
            if (compteur < 3)
            {
                tmp = 0;
            }
            else
            {
                points = tmp;
            }
        }
    }
    else if (strcmp(combinaison, "carré") == 0)
    {
        for (i = 1; i <= 6; i++)
        {
            compteur = 0;
            for (j = 0; j < NB_DE; j++)
            {
                if (tabDeLance[j] == i)
                {
                    compteur += 1;
                    tmp += tabDeLance[j];
                }
            }
            if (compteur < 4)
            {
                tmp = 0;
            }
            else
            {
                points = tmp;
            }
        }
    }
    else if (strcmp(combinaison, "full_house") == 0)
    {
        i = 0;
        while ((compteur < 3) && (i <= 6))
        {
            i++;
            compteur = 0;
            for (j = 0; j < NB_DE; j++)
            {
                if (tabDeLance[j] == i)
                {
                    compteur += 1;
                }
            }
        }
        if (compteur >= 3)
        {
            h = 1;
            compteur = 0;
            while ((compteur < 2) && (h <= 6))
            {
                compteur = 0;
                for (j = 0; j < NB_DE; j++)
                {
                    if ((tabDeLance[j] == h) && (h != i))
                    {
                        compteur += 1;
                    }
                }
                h++;
            }
            if (compteur == 2)
            {
                points = 25;
            }
        }
    }
    else if (strcmp(combinaison, "petite_suite") == 0)
    {
        triTabDe(tabDeLance);
        compteur = 0;
        i = -1;
        while ((i < 5) && (compteur < 3))
        {
            i++;
            if (tabDeLance[i] == (tabDeLance[i - 1] + 1))
            {
                compteur += 1;
            }
            else
            {
                compteur = 0;
            }
        }
        if (compteur >= 3)
        {
            points = 30;
        }
    }
    else if (strcmp(combinaison, "grande_suite") == 0)
    {
        triTabDe(tabDeLance);
        compteur = 0;
        for (i = 1; i < NB_DE; i++)
        {
            if (tabDeLance[i] == (tabDeLance[i - 1] + 1))
            {
                compteur += 1;
            }
            else
            {
                compteur = 0;
            }
        }
        if (compteur == 4)
        {
            points = 40;
        }
    }
    else if (strcmp(combinaison, "yams") == 0)
    {
        for (i = 1; i <= 6; i++)
        {
            compteur = 0;
            for (j = 0; j < NB_DE; j++)
            {
                if (tabDeLance[j] == i)
                {
                    compteur += 1;
                }
            }
            if (compteur == 5)
            {
                points = 50;
            }
        }
    }
    else if (strcmp(combinaison, "chance") == 0)
    {
        for (i = 0; i < NB_DE; i++)
        {
            points += tabDeLance[i];
        }
    }
    return points;
}

/**
 * @fn void actuFeuilleDeMarque(tFeuilleDeScore feuilleDeMarque, int joueur)
 * 
 * @brief Actualise la feuille de marque du joueur.
 * 
 * @param feuilleDeMarque : tableau du type tFeuilleDeScore qui correspond à la feuille de marque des joueurs.
 * @param joueur : Entier qui correspond au joueur qui joue. Peut prendre la valeur 0 ou 1.
 * 
 * Calcul les totaux inférieur, supérieur et final ansi que le bonus.
 * 
 */
void actuFeuilleDeMarque(tFeuilleDeScore feuilleDeMarque, int joueur)
{
    int i;
    int total = 0;
    // calcul du total supérieur
    for (i = 1; i <= 6; i++)
    {
        if (feuilleDeMarque[joueur][i] != -1)
        {
            total += feuilleDeMarque[joueur][i];
        }
        else
        {
            total += 0;
        }
    }
    // ajout du bonus
    if (total > 62)
    {
        feuilleDeMarque[joueur][7] = 35;
        total += feuilleDeMarque[joueur][7];
    }
    feuilleDeMarque[joueur][8] = total;
    // calcul du total inférieur
    total = 0;
    for (i = 9; i <= 15; i++)
    {
        if (feuilleDeMarque[joueur][i] != -1)
        {
            total += feuilleDeMarque[joueur][i];
        }
        else
        {
            total += 0;
        }
    }
    feuilleDeMarque[joueur][16] = total;
    // calcul du total
    feuilleDeMarque[joueur][17] = feuilleDeMarque[joueur][8] + feuilleDeMarque[joueur][16];
}

/**
 * @fn void initTabDe(int tabLance[], int tabValid[])
 * 
 * @brief Initialise les tableau tabLance et tabValid.
 * 
 * @param tabLance : tableau de NB_DE entier
 * @param tabValid : tableau de NB_DE entier
 * 
 * Met toutes les valeurs des tableau à 0.
 * 
 */
void initTabDe(int tabLance[], int tabValid[])
{
    int i;
    for (i = 0; i < NB_DE; i++)
    {
        tabLance[i] = 0;
        tabValid[i] = 0;
    }
}
