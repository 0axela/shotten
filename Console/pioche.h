#pragma once

#include <iostream>
#include <vector>
#include <chrono>
#include <random>

class Clan;
class Tactique;
class Carte;

using namespace std;

template<typename Type> //Type: tactique ou clan
class Pioche {
protected:
    vector<Type*> pile;
public:
    void Empiler(Type* carte) { pile.push_back(carte); }
    Type* getCarteAPiocher();
    vector<Type*> getPile() { return pile; }
    bool estVide() { return pile.empty(); }
    void AjouterEnDessous(Type* carte) { pile.insert(pile.begin(), carte); }
    void Melanger();
    void Afficher();
    
    virtual ~Pioche() = default;
};

class Pioche_Clan : public Pioche<Clan> {
public:
    Pioche_Clan(Clan** cartes_clan);
};

class Pioche_Tactique : public Pioche<Tactique> {
public:
    Pioche_Tactique(Tactique** cartes_tactiques);
};

//nécéssaire d'implémenter ici (cf. https://stackoverflow.com/questions/10632251/undefined-reference-to-template-function)
template<typename Type>
Type* Pioche<Type>::getCarteAPiocher() {
    if (!estVide()) {
        //On ne peut pas renvoyer de référence car c'est une variable locale qu'on retourne
        Type* carte_retour = pile.back();
        pile.pop_back();
        return carte_retour;
    }
    else return nullptr;
}

template<typename Type>
void Pioche<Type>::Melanger() {
    //faire en sorte que le mélange soit réellement aléatoire
    unsigned seed = std::chrono::system_clock::now()
            .time_since_epoch()
            .count();
    shuffle(begin(pile), end(pile), default_random_engine(seed));
}

template<typename Type>
void Pioche<Type>::Afficher() {
    cout << "Affichage de la pioche" << endl;
    for (auto element : pile)
        cout << *element << endl;
    cout << "Fin de l'affichage de la pioche" << endl;
}

class Defausse {
private:
    vector<const Carte*>cartes;
public:
    Defausse() = default;
    void ajouterCarte(const Carte* c);
    void AfficherDefausse();
    vector<const Carte*> getCartes() { return cartes; }
};