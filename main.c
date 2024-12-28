#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <windows.h>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib") // Pour utiliser PlaySound

#define MAX_ERREURS 15
#define DICTIONNAIRE_TAILLE 10
#define TAILLE_MAX_MOT 20

#define MAX_MOTS_UTILISES 10

// Définition des couleurs
#define ROUGE "\033[1;31m"
#define VERT "\033[1;32m"
#define JAUNE "\033[1;33m"
#define BLEU_CIEL "\033[1;36m"
#define MAUVE "\033[1;35m"
#define GRIS "\033[1;30m"
#define RESET "\033[0m"

// Fonctions pour jouer les sons
void jouerSon(const char *fichier) {
    PlaySound(fichier, NULL, SND_FILENAME | SND_ASYNC);
}

void sonErreur() {
    jouerSon("./erreur.wav"); // Son d'erreur
}
void sonBonus() {
    jouerSon("./bonus.wav"); // Son de bonus
}
void sonVictoire() {
    jouerSon("./victoire.wav"); // Son de victoire
}

void sonDefaite() {
    jouerSon("./defaite.wav"); // Son de défaite
}

void sonBonneReponse() {
    jouerSon("./correct.wav"); // Son de bonne réponse
}

void sonIntro() {
    jouerSon("./intro.wav"); // Musique d'introduction
}

// Fonction pour afficher un texte centré
void centrerTexte(const char *texte) {
    int largeurEcran = 80; // Largeur standard
    int longueurTexte = strlen(texte);
    int marge = (largeurEcran - longueurTexte) / 2;

    for (int i = 0; i < marge; i++) {
        printf(" ");
    }
    printf("%s\n", texte);
}

// Fonction pour afficher un texte avec animation
void afficherTexteAnime(const char *texte) {
    for (int i = 0; texte[i] != '\0'; i++) {
        printf("%c", texte[i]);
        fflush(stdout);
        usleep(50000);
    }
    printf("\n");
}

// Fonction pour afficher une bannière encadrée
void afficherEncadre(const char *texte) {
    int longueurTexte = strlen(texte);
    printf("%s+", BLEU_CIEL);
    for (int i = 0; i < longueurTexte + 2; i++) printf("-");
    printf("+%s\n", RESET);

    printf("%s| %s%s |\n", BLEU_CIEL, texte, RESET);

    printf("%s+", BLEU_CIEL);
    for (int i = 0; i < longueurTexte + 2; i++) printf("-");
    printf("+%s\n", RESET);
}


// Fonction pour changer la couleur du texte et du fond
void color(int couleurDUTexte, int couleurDeFOND) {
    HANDLE H = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(H, couleurDeFOND * 16 + couleurDUTexte);
}

// Fonction pour afficher le message de bienvenue
     void bienvenue() {
    color(4, 0);

    // Affichage du texte ASCII
    printf("                   _______        ______    _________    _______                \n");
    printf("                 /  ______       |   _  |  |  _   _  |   | | ____|                \n");
    printf("                | /              | | | |   | | | |   |   | |____                  \n");
    printf("                | |     ___      | ____ |  | | |_| | |   |  _____|                 \n");
    printf("                | | _/ /         | |  | |  | |     | |   | |__                    \n");
    printf("                 \ _____ /        | |  | |  | |     | |   |  ____ |                   \n");
    printf("                   ______     _____       ______       _______    ________              \n");
    printf("                  | ____|   |   |   |   | |    | |    |  _____|      \n");
    printf("                  | |____      | |      | |    | |    |   ____|     | |              \n");
    printf("                  |____  |     | |      | |    | |    | |  | |      | |                  \n");
    printf("                    ___| |     | |      | |    | |    | |   | |     | |                 \n");
    printf("                  ||    ||     | |      | |    | |    | |    | |    |_|               \n");

    printf("\n");

}

    // Fonction de dessin de l'homme du pendu
      void dessin(char* joueur) {
    color(4, 0);
    printf("\t\t\t\t\t\t\t\t\t              _    \n");
    printf("\t\t\t\t\t\t\t\t\t             |_|    \n");
    printf("\t\t\t\t\t\t\t\t\t             /|\\        \n");
    printf("\t\t\t\t\t\t\t\t\t              |        \n");
    printf("\t\t\t\t\t\t\t\t\t             / \\      \n");

    color(3, 0); // Appliquer une couleur de texte cyan (3) et un fond noir (0)
    printf("\t\t L’HORLOGE TOURNE, CHAQUE SECONDE COMPTE ! VITE, TROUVE LES BONNES LETTRES.\n", joueur);
}

// Fonction du menu avec les noms encadrés par des fleurs
  void menu() {
    color(15, 0);

    printf("\n");
    printf("\t\t\t\t\t *********************************************\n");
    printf("\t\t\t\t\t *                                           *\n");
    printf("\t\t\t\t\t *     "); color(5, 0); printf("         Instructions"); color(15, 0); printf("                 *\n");
    printf("\t\t\t\t\t *                                           *\n");
    printf("\t\t\t\t\t *     "); color(13, 0); printf("Devinez le mot en proposant "); color(15, 0); printf("          *\n");
    printf("\t\t\t\t\t *  "); color(13, 0); printf("        une lettre a la fois."); color(15, 0); printf("            *\n");
    printf("\t\t\t\t\t *                                           *\n");
    printf("\t\t\t\t\t *     "); color(8, 0); printf("Vous avez 15 chances avant de perdre!"); color(15, 0); printf(" *\n");
    printf("\t\t\t\t\t *                                           *\n");
    printf("\t\t\t\t\t *                                           *\n");
    printf("\t\t\t\t\t *                                           *\n");
    printf("\t\t\t\t\t *     "); color(1, 0); printf("Bonne chance et amusez-vous bien !"); color(15, 0); printf("    *\n");
    printf("\t\t\t\t\t *                                           *\n");
    printf("\t\t\t\t\t *********************************************\n");
}



// Fonction pour afficher la potence
void afficherPotence(int erreurs) {
    switch (erreurs) {
        case 0: printf("\n\n\n\n\n\n\n"); break;
        case 1: printf("\n\n\n\n\n\n   _______\n"); break;
        case 2: printf("\n   |\n   |\n   |\n   |\n   |\n   |\n   _______\n"); break;
        case 3: printf("\n   _______\n   |\n   |\n   |\n   |\n   |\n   |\n   _______\n"); break;
        case 4: printf("\n   _______\n   |/\n   |\n   |\n   |\n   |\n   |\n   _______\n"); break;
        case 5: printf("\n   _______\n   |/    |\n   |\n   |\n   |\n   |\n   |\n   _______\n"); break;
        case 6: printf("\n   _______\n   |/    |\n   |     O\n   |\n   |\n   |\n   |\n   _______\n"); break;
        case 7: printf("\n   _______\n   |/    |\n   |     O\n   |     |\n   |\n   |\n   |\n   _______\n"); break;
        case 8: printf("\n   _______\n   |/    |\n   |     O\n   |    /|\n   |\n   |\n   |\n   _______\n"); break;
        case 9: printf("\n   _______\n   |/    |\n   |     O\n   |    /|\\\n   |\n   |\n   |\n   _______\n"); break;
        case 10: printf("\n   _______\n   |/    |\n   |     O\n   |    /|\\\n   |     |\n   |\n   |\n   _______\n"); break;
        case 11: printf("\n   _______\n   |/    |\n   |     O\n   |    /|\\\n   |     |\n   |    / \n   |\n   _______\n"); break;
        case 12: printf("\n   _______\n   |/    |\n   |     O\n   |    /|\\\n   |     |\n   |    / \\\n   |\n   _______\n"); break;
        case 13: printf("\n   _______\n   |/    |\n   |     O\n   |    /|\\\n   |     |\n   |    / \\\n   |   \n   _______\n"); break;
        case 14: printf("\n   _______\n   |/    |\n   |     O\n   |    /|\\\n   |     |\n   |    / \\\n   |  ____\n   _______\n"); break;
        case 15: printf("\n   ______\n   |/    |\n   |     O\n   |    /|\\\n   |     |\n   |    / \\\n   |/\n   _______\n"); break;
    }
}


// Fonction pour choisir un mot secret
void choisirMotSecret(char *motSecret, char *categorie, int niveau) {
    const char *dictionnaire[DICTIONNAIRE_TAILLE][2] = {
        {"melon", "Fruit"},
        {"ordinateur", "Technologie"},
        {"programmation", "Informatique"},
        {"montagne", "Géographie"},
        {"poire", "Fruit"},
        {"metro", "Transport"},
        {"chocolat", "Aliment"},
        {"python", "Programmation"},
        {"musique", "Art"},
        {"licorne", "Fantaisie"}
    };

    int index;
    srand(time(NULL));
    if (niveau == 1) {
        // Choisir un mot aléatoire, mais avec max 6 caractères
        do {
            index = rand() % DICTIONNAIRE_TAILLE;
        } while (strlen(dictionnaire[index][0]) > 6 );
    } else if (niveau == 2) {
        // Choisir un mot aléatoire sans limite de longueur
        do {
            index = rand() % DICTIONNAIRE_TAILLE;
        } while (0); // Ignorer l'historique
    } else { char ch;
        int i = 0;
        printf("Entrez un mot secret (max 20 caractères) : ");
 while (1) {
            ch = getch();
            if (ch == 13)
                break;
            else if (ch == 8) {
                if (i > 0) {
                    printf("\b \b"); // Efface un caractère à l'écran
                    i--;
                }
            }
            else if (i < TAILLE_MAX_MOT && isalpha(ch)) {
                motSecret[i++] = ch; // Ajouter la lettre au mot
                printf("*");
            }
        }
        motSecret[i] = '\0'; // Ajouter le caractère de fin de chaîne après la boucle
        strcpy(categorie, "Personnalisé");
        return;
    }
    // Copier le mot et la catégorie dans les variables fournies en paramètre
    strcpy(motSecret, dictionnaire[index][0]);
    strcpy(categorie, dictionnaire[index][1]);

}

// Fonction principale
int main() {
    char motSecret[TAILLE_MAX_MOT + 1], motAffiche[TAILLE_MAX_MOT + 1], lettresProposees[26] = {0};
    char categorie[30];
    char lettre;
    int erreurs = 0, trouve = 0, lettresCount = 0, niveau;
    int longueurMot;
    int indiceVoulu = 0;  // 0 = non, 1 = oui
    char reponse[4];
    char saisie[10];
    char joueur[50];
    char choix;
    sonIntro();
    bienvenue();
    dessin(joueur);
    Sleep(4000);
    system("cls");
    menu();
    Sleep(6000);
    system("cls");
    centrerTexte(GRIS"Voulez-vous voir les regles du jeu ? (O/N) : ");
    sonBonus();
    scanf(" %c", &choix);
    system("cls");

// Vérifier la réponse
if (choix == 'O' || choix == 'o') {
    printf("\n");
    centrerTexte(ROUGE"=======================================");
    centrerTexte(ROUGE"         Regles du jeu du Pendu        ");
    centrerTexte(ROUGE"=======================================");
    sonBonus;
    printf("\n");
    afficherTexteAnime(GRIS"1. Devinez le mot secret en proposant une lettre a la fois.");
    afficherTexteAnime(GRIS"2. Vous avez un nombre limite de tentatives (15).");
    afficherTexteAnime(GRIS"3. Chaque mauvaise reponse rapproche la potence de la pendaison.");
    afficherTexteAnime(GRIS"4. Si vous devinez toutes les lettres avant de manquer vos tentatives, vous gagnez !");
    afficherTexteAnime(GRIS"5. Si vous n'y parvenez pas, vous perdez et le mot secret est revele.");
    afficherTexteAnime(GRIS"6. Vous pouvez demander un indice, mais cela coute une tentative.");
    printf("\n");
    centrerTexte("=======================================");
    afficherTexteAnime(GRIS"Appuyez sur Entree pour continuer...");
    printf("\n");
    while (getchar() != '\n'); // Vider le tampon
    getchar();
}
     system("cls");
     printf("\n");
     centrerTexte(MAUVE "Choisissez votre niveau :" RESET);
     centrerTexte(MAUVE "1 - Debutant " RESET);
     centrerTexte(MAUVE "2 - Intermediaire " RESET);
     centrerTexte(MAUVE "3 - Expert " RESET);
     centrerTexte(MAUVE "Votre choix : " RESET);


   while (1) {
    if (scanf("%d", &niveau) != 1) {
            sonErreur ();
        // Vider le tampon et afficher une erreur
        printf(ROUGE"Erreur : veuillez entrer un nombre entier.\n");
        sonErreur();
        while (getchar() != '\n');
        printf("Votre choix : ");
    } else if (niveau < 1 || niveau > 3) {
        sonErreur ();
        printf(ROUGE"Choix invalide. Veuillez entrer un niveau entre 1 et 3 : ");
    } else {
        break;
    }
}
   system("cls");

    // Demander l'indice au début du jeu
     if (niveau != 3) {
    printf("Voulez-vous un indice (oui/non) ? ");
    scanf("%s", reponse);
    if (strcmp(reponse, "oui") == 0 || strcmp(reponse, "OUI") == 0) {
        indiceVoulu = 1;
    } else {
        indiceVoulu = 0;
    }
}
    choisirMotSecret(motSecret, categorie, niveau);
    longueurMot = strlen(motSecret);
    for (int i = 0; i < longueurMot; i++) motAffiche[i] = '*';
    motAffiche[longueurMot] = '\0';


    // Boucle principale du jeu
    while (erreurs < MAX_ERREURS && !trouve) {
        printf("\n=======================================\n");
        printf("%sMot a deviner : %s\n", BLEU_CIEL, motAffiche);
        afficherPotence(erreurs);
        printf("=======================================\n");
        printf("Lettres incorrectes proposees : ");
        for (int i = 0; i < lettresCount; i++) {
            if (!strchr(motSecret, lettresProposees[i])) {
                printf("%c ", lettresProposees[i]);
            }
        }
        printf("\n=======================================\n");

        if (indiceVoulu) {
    printf("Indice : Le mot appartient a la categorie : %s\n", categorie);
     printf(ROUGE "Vous avez perdus une tentative !\n" RESET);
     sonBonus();
     indiceVoulu = 0;  // Empêche de redemander l'indice
    erreurs++;
}
        printf("Proposez une lettre : ");
        scanf("%9s", saisie);

         // Vérification de la validité de la lettre
              if (strlen(saisie) != 1 || !isalpha(saisie[0])) {
       printf("%sVeuillez entrer une seule lettre valide !%s\n", ROUGE, RESET);
       erreurs++;
       sonErreur();
       while (getchar() != '\n');
       Sleep(1000);
       system("cls");
      continue;
}
           lettre = saisie[0]; // Pas de conversion en minuscule
           if ((niveau == 1 || niveau == 2) && isupper(lettre)) {
    printf("%sErreur ! Les majuscules ne sont pas autorisees a ce niveau.%s\n", ROUGE, RESET);
    erreurs++;
    Sleep(1000);
    system("cls");
    continue;
}
        if (strchr(lettresProposees, lettre)) {
            sonErreur();
            printf("%sCette lettre a deja ete proposee.\n%s", MAUVE, RESET);
            erreurs++;
            Sleep(1000);
            system("cls");
            continue;
        }
   lettresProposees[lettresCount++] = lettre;

        int lettreTrouvee = 0;
        for (int i = 0; i < longueurMot; i++) {
            if (motSecret[i] == lettre) {
                motAffiche[i] = lettre;
                lettreTrouvee = 1;
}}
        if (lettreTrouvee) {
            printf("%sBonne reponse !\n%s", VERT, RESET);
            sonBonneReponse();
            Sleep(1000);
            system("cls");
        } else {
            printf("%sMauvaise reponse !\n%s", ROUGE, RESET);
            erreurs++;
            Sleep(1000);
            system("cls");
            sonErreur();
        }
         trouve = (strchr(motAffiche, '*') == NULL);
    }

if (trouve) { system("cls");
        printf("%s", ROUGE);
        centrerTexte("                    *    .''.    *                     ");
        printf("%s", JAUNE);
        centrerTexte("          .''.      *   :\\/:   *    .''.             ");
        printf("%s", MAUVE);
        centrerTexte("      *   :\\/:     *   : /\\ :   *   *              ");
        printf("%s", VERT);
        centrerTexte("   *    .:.* /\\ *       *  '..'.  *  o__o *          ");
        printf("%s", RESET);
        printf("%s", VERT);
        centrerTexte("                  'YEAH!'                        ");
        centrerTexte("     FELICITATIONS   \\O/    FELICITATIONS ! ");
        centrerTexte("                      |                     ");
        centrerTexte("                     / \\                    ");
        centrerTexte("            Tu m'as sauve, merci !                    ");
        printf("%s\n", RESET);
        // Message de félicitations
        centrerTexte("");
        printf(" Felicitations, vous avez trouve le mot : %s\n %s", VERT, motSecret, RESET);
        centrerTexte("");
        sonVictoire();
        Sleep(4000);}
else {
  Sleep(2700);
    color(15, 0);
    printf("\t\t\t\t\t   ______________________________\n");
    printf("\t\t\t\t\t / \\         ");
    color(5, 0);
    printf("GAME OVER");
    color(15, 0);
    printf("          \. \n");
    printf("\t\t\t\t\t|   |                            |.\n");
    printf("\t\t\t\t\t \\_  |                           |.\n");
    printf("\t\t\t\t\t    |                            |.\n");
    printf("\t\t\t\t\t    |      ");
    color(12, 0);
    printf("        ___           |. \n");
    color(15, 0);
    printf("\t\t\t\t\t    |      ");
    color(7, 0);
    printf("        # #           |. \n");
    printf("                                            |             |_*_|          | \n");
    color(15, 0);
    printf("\t\t\t\t\t    |                            |.\n");
    printf("\t\t\t\t\t    |      ");
    color(8, 0);
    printf("        /|\\        \n");
    color(15, 0);
    printf("\t\t\t\t\t    |                            |.\n");
    printf("\t\t\t\t\t    |      ");
    color(3, 0);
    printf("         |        \n");
    color(15, 0);
    printf("\t\t\t\t\t    |                            |.\n");
    printf("\t\t\t\t\t    |      ");
    color(1, 0);
    printf("        / \\      \n");
    color(15, 0);
    printf("\t\t\t\t\t    |                            |.\n");
    printf("\t\t\t\t\t    |____________________________|.\n");
    printf("\t\t\t\t\t    |                            |.\n");
    printf("\t\t\t\t\t    |      ");
    color(12, 0);
    printf("SUSPECT IS DEAD");
    color(15, 0);
    printf("       |.\n");
    printf("\t\t\t\t\t    |                            |.\n");
    printf("\t\t\t\t\t    |      ");
    color(15, 0);
    printf("  YOU LOSE");
    color(15, 0);
    printf("            |.\n");
    printf("\t\t\t\t\t    |____________________________|.\n");
    printf("\t\t\t\t\t    |   _________________________|___\n");
    printf("\t\t\t\t\t    |  /%s Le mot etait :%s          \n", ROUGE, motSecret);
    printf("\t\t\t\t\t    \\_/____________________________/.\n");
    sonDefaite();
    Sleep(4000);
}


    return 0;
}
