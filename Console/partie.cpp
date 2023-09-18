#include "partie.h"
#include "joueur.h"
#include "borne.h"
#include "carte.h"
#include "pioche.h"
#include "enum.h"

using namespace std;

void DefinirNombreManche() {
    //affichage temporaire pour demander le nombre de parties à jouer
    cout << "\n";
    cout << "-------------------------------\n";
    cout << "Combien de parties voulez vous jouer ? \n";
    cout << "Le nombre de parties doit être compris en 1 et 10 \n";
    cout << "-------------------------------";
    cout << "\n";
    int a;
    cin >> a;
    //tant que le nombre de partie n'est pas raisonnable
    while (a < 1 || a > 10) {
        cout << "\n";
        cout << "-------------------------------\n";
        cout << "Ce nombre n'est pas compris entre 1 et 10 \n";
        cout << "Veuillez en entre un autre\n";
        cout << "-------------------------------";
        cout << "\n";
        cin >> a;
    }

}



Mode Partie::ModePartie() {
    Mode modePartie;
    int choix;
    cout << "\n";
    cout << "-------------------------------\n";
    cout << "Quel mode voulez vous jouer ? \n";
    cout << "Tapez 1 pour mode Normal \n";
    cout << "Tapez 2 pour mode Tactique \n";
    cout << "Tapez 3 pour mode Expert \n";
    cout << "-------------------------------";
    cout << "\n";
    cin >> choix;
    switch (choix) {
        case 1:
            modePartie = Mode::normal;
            break;
        case 2:
            modePartie = Mode::tactique;
            break;
        case 3:
            modePartie = Mode::expert;
            break;
        default:
            cout << "Choix non valide. Vous jouerez en mode normal. \n";
            modePartie = Mode::normal;
            break;
    }
    return modePartie;
}


int Partie::NombreManches() {
    int nb;
    cout << "Combien de manches voulez vous jouer ?" << "\n";
    cin >> nb;
    //on vérifie que le nb de manche est compris entre 1 et 10
    while (nb < 1) {
        cout << "Le nombre de manches doit être supérieur à 0" << "\n";
        cin >> nb;
    }
    return nb;
}

[[maybe_unused]] void Partie::AfficherTactique() {
    for (auto& carte : tactique) {
        cout << *carte;
    }
}

void Partie::AfficherClan() {
    for (auto& carte : clan) {
        cout << *carte;
    }
}

void Partie::VerifGagnantPartie() {

    if (isIA()) joueur2 = getIA();

    if (currentManche == nb_manches) {
        if (joueur1->getScorePartie() > joueur2->getScorePartie()) {
            cout << joueur1->getNom() << " gagne la partie avec " << joueur1->getScorePartie() << " points";
            cout << " contre " << joueur2->getNom() << " avec " << joueur2->getScorePartie() << " points\n";
            gagnant = joueur1;
        }
        else if (joueur1->getScorePartie() < joueur2->getScorePartie()) {
            cout << joueur2->getNom() << " gagne la partie avec " << joueur2->getScorePartie() << " points";
            cout << " contre " << joueur1->getNom() << " avec " << joueur1->getScorePartie() << " points\n";
            gagnant = joueur2;
        }
        else if (joueur1->getScorePartie() == joueur2->getScorePartie()) {
            cout << "Les deux joueurs sont à égalité avec " << joueur1->getScorePartie() << " points ! \n";
            gagnant = joueur1; //On met joueur 1 par défaut mais ça change rien ?
        }
    }

}


Joueur* Partie::DonnerMain() {
    //printPayss(cout);

    if (isIA()) {
        cout << "\nPartie avec IA, le joueur commence\n";
        return joueur1;
    }
    // On demande qui commence
    cout << "\nQui commence ?\n";
    cout << "1. " << joueur1->getNom() << "\n";
    cout << "2. " << joueur2->getNom() << "\n";
    int choix;
    cin >> choix;
    while (choix != 1 && choix != 2) {
        cout << "Choix non valide, veuillez recommencer\n";
        cin >> choix;
    }
    if (choix == 1) {
        return joueur1;
    }
    else {
        return joueur2;
    }

}

void Partie::afficherFrontiere() {
    int i;
    cout << "\n------------Affichage Plateau------------\n";

    cout << "\n-----Format d'affichage-----\n";
    if (!isIA()) {
        cout << "\nBorne n°|"
             << "Cartes " << Partie::getInstance().getJoueur1()->getNom()
             << "|Cartes " << Partie::getInstance().getJoueur2()->getNom()
             << "|Carte spéciale ? "
             << "|Revendiquee ?|" << endl;
        cout << "\n";
    }
    else {
        cout << "\nBorne n°|"
             << "Cartes " << Partie::getInstance().getJoueur1()->getNom()
             << "|Cartes " << Partie::getInstance().getIA()->getNom()
             << "|Carte spéciale ? "
             << "|Revendiquee ?|" << endl;
        cout << "\n";
    }
    for (i = 0; i < 9; i++) {
        cout << *getFrontiere(i) << "\n\n";
    }

    defausse->AfficherDefausse();

}

void Partie::distribuer_debut() {
    int i;
    int nb_a_distribuer;
    //Bien mélanger avant de distribuer comme ça on peut gérer avec les indices
    piocheClan->Melanger();
    if (mode == Mode::normal) {
        nb_a_distribuer = 6;
    }
    else if (mode == Mode::tactique || mode == Mode::expert) {
        nb_a_distribuer = 7;
        piocheTactique->Melanger();
    }

    //Distribution aux deux joueurs ou au joueur 1 et à l'IA dans le cas d'une partie avec IA
    for (i = 0; i < nb_a_distribuer; i++) {
        joueur1->setCartes(piocheClan->getCarteAPiocher(), i);
        if (!isIA()) joueur2->setCartes(piocheClan->getCarteAPiocher(), i);
        else ia->setCartes(piocheClan->getCarteAPiocher(), i);
    }

}

//singleton
Partie* Partie::instanceUnique = nullptr;
Partie& Partie::getInstance() {
    if (instanceUnique == nullptr) {
        instanceUnique = new Partie;
    }
    return *instanceUnique;
}
void Partie::libererInstance() {
    delete instanceUnique;
    instanceUnique = nullptr;
}

Partie::~Partie() {
    int i;
    for (i = 0; i < 54; i++) {
        delete clan[i];
    }
    for (i = 0; i < 10; i++) {
        delete tactique[i];
    }
    delete joueur1;
    delete joueur2;
    delete ia;

    for (i = 0; i < 9; i++) {
        delete frontiere[i];
    }

    delete piocheClan;
    delete piocheTactique;
    delete defausse;
}

Partie::Partie() : mode(ModePartie()), gagnant(nullptr), nb_manches(NombreManches()), dernierjoueur(nullptr), currentManche(0) {

    //Choix IA ou non
    char choix = 'Z';
    while ((choix != 'Y') && (choix != 'N')) {
        cout << "Cette partie se jouera-t-elle avec un joueur seulement, donc avec une IA ? (Y/N) ";
        cin >> choix;
        switch (choix) {
            case 'Y':
                joueur1 = new Joueur(1);
                ia = new IA();
                joueur2 = nullptr;
                break;
            case 'N':
                ia = nullptr;
                joueur1 = new Joueur(1);
                joueur2 = new Joueur(2);
                break;
            default:
                cout << "Merci de saisir une réponse correcte (Y ou N)\n\n";
                break;
        }
    }
    commence = DonnerMain();

    //Création des cartes clan
    int i = 0;
    for (auto c : Couleurs)
        if (c != Couleur::pasdecouleur) {
            for (auto n : Numeros)
                if (n != Numero::pasdenumero)
                    clan[i++] = new Clan(n, c);
        }

    //Création des cartes tactiques

    if (mode == Mode::tactique || mode == Mode::expert) {
        i = 0;
        for (auto n : NomTactiques) {
            if (n != NomTactique::pasdenom) {
                if (n == NomTactique::joker || n == NomTactique::espion || n == NomTactique::porte_bouclier) {
                    if (n == NomTactique::joker) tactique[i++] = new Elite(n); //si joker, on le fait 2 fois
                    tactique[i++] = new Elite(n);
                }
                if (n == NomTactique::colin_maillard || n == NomTactique::combat_de_boue) tactique[i++] = new Combat(n);
                if (n == NomTactique::chasseur_de_tete || n == NomTactique::stratege || n == NomTactique::banshee || n == NomTactique::traitre) tactique[i++] = new Ruse(n);
            }
        }
    }

    //Création de la frontière
    for (i = 0; i < 9; i++) {
        frontiere[i] = new Borne(i);
    }

    piocheClan = new Pioche_Clan(clan); //PIOCHE CLAN DANS PARTIE
    if (mode == Mode::tactique || mode == Mode::expert) {
        piocheTactique = new Pioche_Tactique(tactique);
    } //PIOCHE TACTIQUE DANS PARTIE

    defausse = new Defausse;
}

bool Partie::VerifGagnantManche(Joueur* j) {
    //Le joueur gagne la manche si : il contrôle 3 bornes adjacentes ou 5 bornes dispersées au long de la frontière
    // Vérification des cas avec trois cases consécutives
    Joueur* opponent = nullptr;
    if (isIA()) {
        opponent = getIA();
    }
    else {
        opponent = (j == joueur1) ? joueur2 : joueur1;
    }
    bool win = false;
    int count = 0;
    int count_opponent = 0;
    int length = 9;
    for (int i = 0; i < length - 2; i++) {
        if (getFrontiere(i)->getProprietaire() == j && getFrontiere(i + 1)->getProprietaire() == j && getFrontiere(i + 2)->getProprietaire() == j) {
            win = true;
        }
    }

    // Vérification des cas avec cinq cases au total
    for (int i = 0; i < length; i++) {
        if (getFrontiere(i)->getProprietaire() == j) {
            count++;
        }
        else if (getFrontiere(i)->getProprietaire() == opponent) {
            count_opponent++;
        }
        if (count == 5) {
            win = true;
            break;
        }
    }
    //Si le joueur gagne la manche, on lui ajoute 5 points et on doit changer de manche, on met également à jour le tableau des manches. Il faut aussi ajouter le nombre de bornes gagnées par l'adversaire à son nombre de points
    if (win) {
        cout << "Le joueur " << j->getNom() << " a gagné la manche !" << endl;
        j->setScorePartie(j->getScorePartie() + 5);
        opponent->setScorePartie(opponent->getScorePartie() + count_opponent);
        cout << "Le joueur " << j->getNom() << " a maintenant " << j->getScorePartie() << " points." << endl;
        cout << "Le joueur " << opponent->getNom() << " a maintenant " << opponent->getScorePartie() << " points." << endl;

        return true;
    }
    else return false;

}

//Fonctions nécessaires pour la méthode jeu()

void afficher_message(const std::string& message) {
    std::cout << message << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));
}


void afficher_compte_a_rebours() {
    cout << endl;
    afficher_message("Changement de main dans 3 ..");
    afficher_message("Changement de main dans 2 ..");
    afficher_message("Changement de main dans 1 ..");
    afficher_message("Changement de main !");
}





void Partie::jeu() {
    auto joueur1 = getJoueur1();
    auto joueur2 = getJoueur2();
    if (isIA()) joueur2 = getIA();

    currentManche = 1;
    chrono::seconds waitTime(2);
    bool gagnant_manche;

    //Déroulé de la partie
    while (gagnant == nullptr) {

        //On initialise/réinitialise les mains
        distribuer_debut();

        if (mode == Mode::normal) {
            joueur1->setNbCartesEnMain(6);
            joueur2->setNbCartesEnMain(6);
        }
        else {
            joueur1->setNbCartesEnMain(7);
            joueur2->setNbCartesEnMain(7);
        }

        gagnant_manche = false;


        //Déroulé des manches selon qui commence
        if (commence == joueur1) {
            while (1) {
                cout << "\n";
                afficherFrontiere();
                cout << "\n---------------\nÀ " << joueur1->getNom() << " de jouer \n---------------\n";
                if (mode == Mode::tactique || mode == Mode::expert) {
                    cout << "Nombre de tactiques jouées par " << joueur1->getNom() << ": " << joueur1->getNb_tactiques_jouee() << endl;
                    cout << "Nombre de tactiques jouées par " << joueur2->getNom() << ": " << joueur2->getNb_tactiques_jouee() << endl;
                }
                joueur1->JouerCarte();
                if (Partie::getInstance().VerifGagnantManche(joueur1)) {
                    break;
                }
                afficher_compte_a_rebours();
                afficherFrontiere();
                cout << "\n---------------\nÀ " << joueur2->getNom() << " de jouer \n---------------\n";
                if (mode == Mode::tactique || mode == Mode::expert) {
                    cout << "Nombre de tactiques jouées par " << joueur2->getNom() << ": " << joueur2->getNb_tactiques_jouee() << endl;
                    cout << "Nombre de tactiques jouées par " << joueur1->getNom() << ": " << joueur1->getNb_tactiques_jouee() << endl;
                }
                joueur2->JouerCarte();
                if (Partie::getInstance().VerifGagnantManche(joueur2)) {
                    break;
                }

                afficher_compte_a_rebours();
            }
        }
        else {
            while (1) {
                cout << "\n";
                afficherFrontiere();
                cout << "\n---------------\nÀ " << joueur2->getNom() << " de jouer \n---------------\n";
                if (mode == Mode::tactique || mode == Mode::expert) {
                    cout << "Nombre de tactiques jouées par " << joueur2->getNom() << ": " << joueur2->getNb_tactiques_jouee() << endl;
                    cout << "Nombre de tactiques jouées par " << joueur1->getNom() << ": " << joueur1->getNb_tactiques_jouee() << endl;
                }
                joueur2->JouerCarte();
                if (Partie::getInstance().VerifGagnantManche(joueur2)) {
                    break;
                }
                afficher_compte_a_rebours();
                afficherFrontiere();
                cout << "\n---------------\nÀ " << joueur1->getNom() << " de jouer \n---------------\n";
                if (mode == Mode::tactique || mode == Mode::expert) {
                    cout << "Nombre de tactiques jouées par " << joueur1->getNom() << ": " << joueur1->getNb_tactiques_jouee() << endl;
                    cout << "Nombre de tactiques jouées par " << joueur2->getNom() << ": " << joueur2->getNb_tactiques_jouee() << endl;
                }
                joueur1->JouerCarte();
                if (Partie::getInstance().VerifGagnantManche(joueur1)) {
                    break;
                }
                afficher_compte_a_rebours();
            }
        }

        if (currentManche == nb_manches) {
            cout << "\n\n--------------------------- Fin de partie --------------------------- \n\n";
            VerifGagnantPartie();
            return;
        }
        currentManche++;
        //--On réinitialise tout pour la prochaine manche--
        int i;
        //On réinitialise la frontière
        for (i = 0; i < 9; i++) {
            frontiere[i]->Clear();
        }
        //Réinitialisation du dernier joueur
        setDernierjoueur(nullptr);
        //On réinitialise les pioches
        piocheClan->getPile().clear();
        for (i = 0; i < 54; i++) {
            piocheClan->Empiler(clan[i]);
        }
        if (mode == Mode::tactique || mode == Mode::expert) {
            piocheTactique->getPile().clear();
            for (i = 0; i < 10; i++) {
                piocheTactique->Empiler(tactique[i]);
            }
        }

        //On réinitialise la défausse
        defausse->getCartes().clear();

        //On réinitialise les attributs relatifs aux joueurs
        joueur1->Clear();
        joueur2->Clear();

        //Nouvelle manche
        cout << "\n\n --------------------------- Manche n°" << currentManche << "---------------------------\n\n";

        commence = DonnerMain();
    }


}

void Partie::scoreAzero(Joueur *j) { j->setScoreManche(0); }
