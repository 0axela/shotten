//
// Created by axela on 07/06/2023.
//

#include "borne.h"
#include "partie.h"
#include "combinaison.h"
#include "joueur.h"


using namespace std;

//fonction pour décaler la borne selon le numéro du joueur
void DecalerBorne(int borne, int joueur) {
    if (joueur == 1) {
        int taille = Partie::getInstance().getFrontiere(borne)->getnbCartes1();
        //On décale le tableau du côté du joueur 1 pour ne pas laisser un trou nullptr
        int indexDestination = 0;
        for (int indexSource = 0; indexSource < taille; ++indexSource) {
            if (Partie::getInstance().getFrontiere(borne)->getCarte1(indexSource) != nullptr) {
                Partie::getInstance().getFrontiere(borne)->setCarte1(indexDestination, Partie::getInstance().getFrontiere(borne)->getCarte1(indexSource));
                ++indexDestination;
            }
        }
        // Remplissage des éléments restants avec des zéros
        for (; indexDestination < taille; ++indexDestination) {
            Partie::getInstance().getFrontiere(borne)->setCarte1(indexDestination, nullptr);
        }
    }
    if (joueur == 2) {
        int taille = Partie::getInstance().getFrontiere(borne)->getnbCartes2();
        int indexDestination = 0;
        for (int indexSource = 0; indexSource < taille; ++indexSource) {
            if (Partie::getInstance().getFrontiere(borne)->getCarte2(indexSource) != nullptr) {
                Partie::getInstance().getFrontiere(borne)->setCarte2(indexDestination, Partie::getInstance().getFrontiere(borne)->getCarte2(indexSource));
                ++indexDestination;
            }
        }

        // Remplissage des éléments restants avec des zéros
        for (; indexDestination < taille; ++indexDestination) {
            Partie::getInstance().getFrontiere(borne)->setCarte2(indexDestination, nullptr);
        }
    }
}


bool Borne::verifRevendication(Joueur* j) {
    if (isCombatBoue) { //si la carte combat de boue est jouée sur la borne
        if (nbCartes1 == 4 && nbCartes2 == 4) { //si on a bien 4 cartes de chaque côté

            auto c1 = Combinaison(*cartes1[0], *cartes1[1], *cartes1[2], *cartes1[3]); //on construit une combinaison avec les cartes de chaque côté de la borne
            auto c2 = Combinaison(*cartes2[0], *cartes2[1], *cartes2[2], *cartes2[3]);

            if (isColinMaillard) { //si la carte Colin Maillard est jouée sur la borne

                if (c1.getSommeCartes() > c2.getSommeCartes() && j->getNumero() == 1) { //si la somme des cartes du joueur 1 est supérieure
                    proprietaire = Partie::getInstance().getJoueur1();
                    cout << "\nRevendication valide, le joueur 1 (" << j->getNom() << ") gagne la borne ! \n";
                }

                else if (c1.getSommeCartes() < c2.getSommeCartes() && j->getNumero() == 2) { //si la somme des cartes du joueur 2 est supérieure
                    proprietaire = Partie::getInstance().getJoueur2();
                    cout << "\nRevendication valide, le joueur 2 (" << j->getNom() << ") gagne la borne ! \n";
                }

                else if (c1.getSommeCartes() == c2.getSommeCartes() && j->getNumero() == 1 && j == premierAposer) {
                    proprietaire = Partie::getInstance().getJoueur1();
                    cout << "\nRevendication valide, le joueur 1(" << j->getNom() << ") est le premier a avoir pose sa troisieme carte \n";
                }
                else if (c1.getSommeCartes() == c2.getSommeCartes() && j->getNumero() == 2 && j == premierAposer) {
                    proprietaire = Partie::getInstance().getJoueur2();
                    cout << "\nRevendication valide, le joueur 2 (" << j->getNom() << ") est le premier a avoir pose sa troisieme carte \n";
                }

                else {
                    cout << "\nRevendication non valide, la somme de 3 cartes n'est pas meilleure que celle de l'autre joueur \n";
                    return false;
                }

            }
            else { //si la carte Colin Maillard n'est pas jouée

                if (c1.getValeur() > c2.getValeur() && j->getNumero() == 1) { //si la valeur des cartes du joueur 1 est supérieure
                    proprietaire = Partie::getInstance().getJoueur1();
                    cout << "\nRevendication valide, le joueur 1(" << j->getNom() << ") gagne la borne ! \n";
                }

                else if (c1.getValeur() < c2.getValeur() && j->getNumero() == 2) { //si la valeur des cartes du joueur 2 est supérieure
                    proprietaire = Partie::getInstance().getJoueur2();
                    cout << "\nRevendication valide, le joueur 2 (" << j->getNom() << ") gagne la borne ! \n";
                }

                else if (c1.getValeur() == c2.getValeur() && j->getNumero() == 1 && j == premierAposer) {
                    proprietaire = Partie::getInstance().getJoueur1();
                    cout << "\nRevendication valide, le joueur 1 (" << j->getNom() << ") est le premier a avoir pose sa quatrieme carte \n";
                }
                else if (c1.getValeur() == c2.getValeur() && j->getNumero() == 2 && j == premierAposer) {
                    proprietaire = Partie::getInstance().getJoueur2();
                    cout << "\nRevendication valide, le joueur 2 (" << j->getNom() << ") est le premier a avoir pose sa quatrieme carte \n";
                }

                else {
                    cout << "\nRevendication non valide, la combinaison de 3 cartes n'est pas meilleure que celle de l'autre joueur \n";
                    return false;
                }

            }
            //Récap de la revendication
            cout << "\nRécap revendication: \n\n";
            if (j->getNumero() == 1) {
                cout << j->getNom() << " gagne avec la revendication suivante: " << c1.getNom() << " dont la somme des cartes valaient " << c1.getSommeCartes() << "\n";
                cout << "L'adversaire avait la combinaison suivante: " << c2.getNom() << " dont la somme des vartes valaient " << c2.getSommeCartes() << "\n\n";
            }
            else {
                cout << j->getNom() << " gagne avec la revendication suivante: " << c2.getNom() << " dont la somme des cartes valaient " << c2.getSommeCartes() << "\n";
                cout << "L'adversaire avait la combinaison suivante: " << c1.getNom() << " dont la somme des vartes valaient " << c1.getSommeCartes() << "\n\n";
            }
        }
        else { //revendication non valide car il n'y a pas 4 cartes de chaque côté
            cout << "Revendication invalide, il n'y a pas 4 cartes de chaque côté \n";
            return false;

        }


    }

    else { // si la carte combat de boue n'est pas posée
        if (nbCartes1 == 3 && nbCartes2 == 3) {

            auto c1 = Combinaison(*cartes1[0], *cartes1[1], *cartes1[2]); //on construit une combinaison avec les cartes de chaque côté de la borne
            auto c2 = Combinaison(*cartes2[0], *cartes2[1], *cartes2[2]);

            if (isColinMaillard) { //si la carte Colin Maillard est jouée sur la borne

                if (c1.getSommeCartes() > c2.getSommeCartes() && j->getNumero() == 1) { //si la somme des cartes du joueur 1 est supérieure
                    proprietaire = Partie::getInstance().getJoueur1();
                    cout << "Revendication valide, le joueur 1 (" << j->getNom() << ") gagne la borne !\n";
                }

                else if (c1.getSommeCartes() < c2.getSommeCartes() && j->getNumero() == 2) { //si la somme des cartes du joueur 2 est supérieure
                    proprietaire = Partie::getInstance().getJoueur2();
                    cout << "Revendication valide, le joueur 2 (" << j->getNom() << ") gagne la borne ! \n";
                }

                else if (c1.getSommeCartes() == c2.getSommeCartes() && j->getNumero() == 1 && j == premierAposer) {
                    proprietaire = Partie::getInstance().getJoueur1();
                    cout << "Revendication valide, le joueur 1 (" << j->getNom() << ") est le premier a avoir pose sa troisieme carte \n";
                }
                else if (c1.getSommeCartes() == c2.getSommeCartes() && j->getNumero() == 2 && j == premierAposer) {
                    proprietaire = Partie::getInstance().getJoueur2();
                    cout << "Revendication valide, le joueur 2 (" << j->getNom() << ") est le premier a avoir pose sa troisieme carte \n";
                }

                else {
                    cout << "Revendication non valide, la somme de 3 cartes n'est pas meilleure que celle de l'autre joueur \n";
                    return false;
                }

            }
            else { //si la carte Colin Maillard n'est pas jouée

                if (c1.getValeur() > c2.getValeur() && j->getNumero() == 1) { //si la valeur des cartes du joueur 1 est supérieure
                    proprietaire = Partie::getInstance().getJoueur1();
                    cout << "Revendication valide, le joueur 1 (" << j->getNom() << ") gagne la borne ! \n";
                }
                else if (c1.getValeur() < c2.getValeur() && j->getNumero() == 2) { //si la valeur des cartes du joueur 2 est supérieure
                    proprietaire = Partie::getInstance().getJoueur2();
                    cout << "Revendication valide, le joueur 2 (" << j->getNom() << ") gagne la borne ! \n";
                }
                else if (c1.getValeur() == c2.getValeur() && j->getNumero() == 1 && j == premierAposer) {
                    proprietaire = Partie::getInstance().getJoueur1();
                    cout << "Revendication valide, le joueur 1 (" << j->getNom() << ") est le premier a avoir pose sa troisieme carte \n";
                }
                else if (c1.getValeur() == c2.getValeur() && j->getNumero() == 2 && j == premierAposer) {
                    proprietaire = Partie::getInstance().getJoueur2();
                    cout << "Revendication valide, le joueur 2 (" << j->getNom() << ") est le premier a avoir pose sa troisieme carte \n";
                }
                else {
                    cout << "Revendication non valide, la combinaison de 3 cartes n'est pas meilleure que celle de l'autre joueur \n";
                    return false;
                }

            }
            //Récap de la revendication
            cout << "\nRécap revendication: \n\n";
            if (j->getNumero() == 1) {
                cout << j->getNom() << " gagne avec la revendication suivante: " << c1.getNom() << " dont la somme des cartes valaient " << c1.getSommeCartes() << "\n";
                cout << "L'adversaire avait la combinaison suivante: " << c2.getNom() << " dont la somme des vartes valaient " << c2.getSommeCartes() << "\n\n";
            }
            else {
                cout << j->getNom() << " gagne avec la revendication suivante: " << c2.getNom() << " dont la somme des cartes valaient " << c2.getSommeCartes() << "\n";
                cout << "L'adversaire avait la combinaison suivante: " << c1.getNom() << " dont la somme des vartes valaient " << c1.getSommeCartes() << "\n\n";
            }
        }

        else {
            cout << "Revendication invalide, il n'y a pas 3 cartes de chaque côté \n";
            return false;

        }

    }

    //si la revendication est valide, on ajoute la borne au vecteur de bornes du joueur
    if (proprietaire != nullptr) {
        proprietaire->ajouterBorneRevendiquee(this);
        proprietaire->setScoreManche(proprietaire->getScoreManche() + 1); //à voir l'utilité de cette ligne
        //Partie::getInstance().VerifGagnantManche(proprietaire); //Déplacé dans le script de jeu
        return true;
    }
}


void Borne::ajouter_cartes1(const Carte& c) {

    if (nbCartes1 == 2 && nbCartes2 < 3) { //si le joueur 1 est le premier a poser sa troisieme carte
        cartes1[nbCartes1] = &c;
        nbCartes1++;
        premierAposer = Partie::getInstance().getJoueur1();
    }

    else if (nbCartes1 == 3 && isCombatBoue) { //s'il est possible d'ajouter une quatrieme carte
        cartes1[nbCartes1] = &c;
        nbCartes1++;
    }
    else if (nbCartes1 < 3) {
        cartes1[nbCartes1] = &c;
        nbCartes1++;
    }
    else {
        cout << "Impossible d'ajouter une carte sur la borne \n";
    }

}

void Borne::ajouter_cartes2(const Carte& c) {

    if (nbCartes2 == 2 && nbCartes1 < 3) { //si le joueur 2 est le premier a poser sa troisieme carte
        cartes2[nbCartes2] = &c;
        nbCartes2++;
        premierAposer = Partie::getInstance().getJoueur2();
    }
    else if (nbCartes2 == 3 && isCombatBoue) { //s'il est possible d'ajouter une quatrieme carte
        cartes2[nbCartes2] = &c;
        nbCartes2++;
    }
    else if (nbCartes2 < 3) {
        cartes2[nbCartes2] = &c;
        nbCartes2++;
    }
    else {
        cout << "Impossible d'ajouter une carte sur la borne \n";
    }

}

Borne::Borne(size_t n) : numero(n), cartes1(new const Carte* [4]), cartes2(new const Carte* [4]) {
    for (int i = 0; i < 4; i++) {
        cartes1[i] = nullptr;
    }
    for (int i = 0; i < 4; i++) {
        cartes2[i] = nullptr;
    }
}

void Borne::Clear() {
    for (int i = 0; i < 4; i++) {
        cartes1[i] = nullptr;
    }
    for (int i = 0; i < 4; i++) {
        cartes2[i] = nullptr;
    }
    nbCartes1 = 0;
    nbCartes2 = 0;
    proprietaire = nullptr;
    premierAposer = nullptr;
    isCombatBoue = false;
}
/*
void Borne::ajouter_combinaison1() {
    *combinaisons1 = Combinaison(*cartes1[0], *cartes1[1], *cartes1[2]);
}

void Borne::ajouter_combinaison2() {
    auto c = Combinaison(*cartes1[0], *cartes1[1], *cartes1[2]);
    *combinaisons2 = c;
}
*/

ostream& operator<<(ostream& f, const Borne& b) {
    int i;
    f << "   " << b.getNumero() << "    |";

    if (b.getnbCartes1() == 0) cout << "Rien";
    else {
        for (i = 0; i < b.getnbCartes1(); i++) {
            f << *b.getCarte1(i) << " ";
        }
    }

    cout << "   |   ";

    if (b.getnbCartes2() == 0) cout << "Rien";
    else {
        for (i = 0; i < b.getnbCartes2(); i++) {
            f << *b.getCarte2(i) << " ";
        }
    }

    cout << "   |   ";

    if (b.getColinMaillard() && b.getCombatBoue()) cout << "Colin Maillard et Combat de Boue";
    else if (b.getCombatBoue()) cout << "Combat de Boue";
    else if (b.getColinMaillard()) cout << "Colin Maillard";
    else cout << "Non";

    cout << "   |   ";

    if (b.getProprietaire() != nullptr) {
        f << b.getProprietaire()->getNom();
    }
    else f << "Non";
    return f;
}
