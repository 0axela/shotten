#pragma once
#include <iostream>
#include "enum.h"
#include "carte.h"

//Ne prend pas en compte le cas où il y a 4 cartes
class Combinaison {
public:
    //constructeur 3 cartes

    Combinaison(const Carte& c1, const Carte& c2, const Carte& c3);	//Composition entre borne et combinaison ?

    //Combinaison(const Carte** c); //défini pas inline en fonction de la taille du tableau
    Combinaison(const Carte& c1, const Carte& c2, const Carte& c3, const Carte& c4);	//A TESTER DU COUP

    const Carte& getCarte1() const { return *c1; }
    const Carte& getCarte2() const { return *c2; }
    const Carte& getCarte3() const { return *c3; }
    const Carte& getCarte4() const { return *c4; }

    const NomCombinaison getNom() const { return nom; }
    const int getSommeCartes() const { return sommeCartes; }
    const int getValeur() const { return valeur; }
    ~Combinaison() = default;
    Combinaison(const Combinaison&) = default;
    Combinaison& operator=(const Combinaison&) = default;

private:
    const Carte* c1;
    const Carte* c2;
    const Carte* c3;
    const Carte* c4;
    NomCombinaison nom;
    int sommeCartes;
    int valeur;
    const NomCombinaison initializeNom();
    const int initializeSomme();
    const int initializeValeur();
};
