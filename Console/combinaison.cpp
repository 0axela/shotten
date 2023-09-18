#include "combinaison.h"

#include <iostream>

const NomCombinaison Combinaison::initializeNom() {

    if (c4 == nullptr) { //si 3 cartes
        auto suite = (toInt(c1->getNumero()) == toInt(c2->getNumero()) - 1 && toInt(c2->getNumero()) == toInt(c3->getNumero()) - 1) || (toInt(c1->getNumero()) == toInt(c3->getNumero()) - 1 && toInt(c3->getNumero()) == toInt(c2->getNumero()) - 1) ||
                     (toInt(c2->getNumero()) == toInt(c1->getNumero()) - 1 && toInt(c1->getNumero()) == toInt(c3->getNumero()) - 1) || (toInt(c2->getNumero()) == toInt(c3->getNumero()) - 1 && toInt(c3->getNumero()) == toInt(c1->getNumero()) - 1) ||
                     (toInt(c3->getNumero()) == toInt(c1->getNumero()) - 1 && toInt(c1->getNumero()) == toInt(c2->getNumero()) - 1) || (toInt(c3->getNumero()) == toInt(c2->getNumero()) - 1 && toInt(c2->getNumero()) == toInt(c1->getNumero()) - 1);

        auto couleur = (c1->getCouleur() == c2->getCouleur()) && (c2->getCouleur() == c3->getCouleur());

        if (suite && couleur) return NomCombinaison::suite_couleur;
        if (suite) return NomCombinaison::suite;
        if (couleur) return NomCombinaison::couleur;
        if ((c1->getNumero() == c2->getNumero()) && (c2->getNumero() == c3->getNumero())) return NomCombinaison::brelan;
        return NomCombinaison::somme;


    }
    else { //si 4 cartes
        auto suite =
                (toInt(c1->getNumero()) == toInt(c2->getNumero()) - 1 && toInt(c2->getNumero()) == toInt(c3->getNumero()) - 1 && toInt(c3->getNumero()) == toInt(c4->getNumero()) - 1)
                || (toInt(c1->getNumero()) == toInt(c3->getNumero()) - 1 && toInt(c3->getNumero()) == toInt(c2->getNumero()) - 1 && toInt(c2->getNumero()) == toInt(c4->getNumero()) - 1)
                || (toInt(c2->getNumero()) == toInt(c1->getNumero()) - 1 && toInt(c1->getNumero()) == toInt(c3->getNumero()) - 1 && toInt(c3->getNumero()) == toInt(c4->getNumero()) - 1)
                || (toInt(c2->getNumero()) == toInt(c3->getNumero()) - 1 && toInt(c3->getNumero()) == toInt(c1->getNumero()) - 1 && toInt(c1->getNumero()) == toInt(c4->getNumero()) - 1)
                || (toInt(c3->getNumero()) == toInt(c1->getNumero()) - 1 && toInt(c1->getNumero()) == toInt(c2->getNumero()) - 1 && toInt(c2->getNumero()) == toInt(c4->getNumero()) - 1)
                || (toInt(c3->getNumero()) == toInt(c2->getNumero()) - 1 && toInt(c2->getNumero()) == toInt(c1->getNumero()) - 1 && toInt(c1->getNumero()) == toInt(c4->getNumero()) - 1);

        auto couleur = (c1->getCouleur() == c2->getCouleur()) && (c2->getCouleur() == c3->getCouleur()) && (c3->getCouleur() == c4->getCouleur());

        if (suite && couleur) return NomCombinaison::suite_couleur;
        if (suite) return NomCombinaison::suite;
        if (couleur) return NomCombinaison::couleur;
        if ((c1->getNumero() == c2->getNumero()) && (c2->getNumero() == c3->getNumero()) && (c3->getNumero() == c4->getNumero())) return NomCombinaison::brelan;
        return NomCombinaison::somme;
    }

}

const int Combinaison::initializeValeur() {
    int coeff = 0;
    int res = 0;
    switch (nom) {
        case NomCombinaison::suite_couleur: coeff = 4; break;
        case NomCombinaison::brelan: coeff = 3; break;
        case NomCombinaison::couleur: coeff = 2; break;
        case NomCombinaison::suite: coeff = 1; break;
        default: coeff = 0; break;
    }
    res = sommeCartes + 36 * coeff;
    return res;   //36 represente la val max d'une somme si on est en combat de boue
}

const int Combinaison::initializeSomme() {
    if (c4 == nullptr) { //si 3 cartes
        return toInt(c1->getNumero()) + toInt(c2->getNumero()) + toInt(c3->getNumero());
    }
    else {
        return toInt(c1->getNumero()) + toInt(c2->getNumero()) + toInt(c3->getNumero()) + toInt(c4->getNumero());
    }

}

Combinaison::Combinaison(const Carte& c1, const Carte& c2, const Carte& c3) :
        c1(&c1), c2(&c2), c3(&c3), c4(nullptr), nom(initializeNom()), sommeCartes(initializeSomme()) {
    valeur = initializeValeur();
}

Combinaison::Combinaison(const Carte& c1, const Carte& c2, const Carte& c3, const Carte& c4) :
        c1(&c1), c2(&c2), c3(&c3), c4(&c4), nom(initializeNom()), sommeCartes(initializeSomme()), valeur(initializeValeur()) {}
