#pragma once

#include <iostream>
#include <string>

class Carte;
class Joueur;

using namespace std;

void DecalerBorne(int borne, int joueur);
//Chaque Borne est unique est doit tre cre par la classe partie, qui assigne  chaque borne un numero unique (de 1  9) ?
class Borne {
public:
    Borne(size_t n);

    ~Borne() { delete[] cartes1; delete[] cartes2; }
    Borne(const Borne&) = delete;
    Borne& operator=(const Borne&) = delete;
    const size_t& getNumero() const { return numero; }

    void ajouter_cartes1(const Carte& c);
    void ajouter_cartes2(const Carte& c);

    bool verifRevendication(Joueur* j);	//si revendication valide on passe proprio au numero du joueur qui revendique

    const size_t& getnbCartes1() const { return nbCartes1; }
    const size_t& getnbCartes2() const { return nbCartes2; }
    void setnbCartes1(size_t nb) { nbCartes1 = nb; }
    void setnbCartes2(size_t nb) { nbCartes2 = nb; }

    bool getCombatBoue() const { return isCombatBoue; }
    bool getColinMaillard() const { return isColinMaillard; }

    Joueur* getProprietaire() const { return proprietaire; }
    void setProprietaire(Joueur* j) { proprietaire = j; }

    const Carte* getCarte1(int i) const { return cartes1[i]; }
    const Carte* getCarte2(int i) const { return cartes2[i]; }
    void setCarte1(int i, const Carte* c) { cartes1[i] = c; }
    void setCarte2(int i, const Carte* c) { cartes2[i] = c; }

    const Carte** getCartes_j1() const { return cartes1; }
    const Carte** getCartes_j2() const { return cartes2; }
    void setCartes_j1(const Carte** tab) { cartes1 = tab; }
    void setCartes_j2(const Carte** tab) { cartes2 = tab; }

    void CombatBoueTrue() {
        isCombatBoue = true;
    }
    void ColinMaillardTrue() {
        isColinMaillard = true;
    }

    void Clear();

private:
    const size_t numero;
    size_t nbCartes1 = 0;
    size_t nbCartes2 = 0;
    Joueur* proprietaire = nullptr;	//pointeur vers un joueur ?
    Joueur* premierAposer = nullptr;
    const Carte** cartes1;
    const Carte** cartes2;
    //Combinaison* combinaisons1 = nullptr;
    //Combinaison* combinaisons2 = nullptr;
    //void ajouter_combinaison1();	//Appeler dans ajouter_cartes2 si nbcartes2 = 3
    //void ajouter_combinaison2();	//Appeler dans ajouter_cartes2 si nbcartes2 = 3
    bool isCombatBoue = false;
    bool isColinMaillard = false;
};

ostream& operator<<(ostream& f, const Borne& b);


