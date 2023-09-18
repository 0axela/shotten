#pragma once

using namespace std;
#include <string>
#include <vector>

class Carte;
class Borne;

class Joueur {

private:
    int numero;
    string nom;
    int nb_tactiques_jouees;
    int scoreManche; //inutile ?
    int scorePartie;
    vector<Borne*> bornes_revendiquees; //inutile ?
    Carte* cartes[7];
    int nb_cartes_en_main;
    bool joker_joue;

public:
    int getNumero() const { return numero; }

    void setNumero(int num);
    string getNom() const { return nom; }

    void setNom(string n);

    bool getJokerJoue() const { return joker_joue; }

    void setJokerJoue(bool b) { joker_joue = b; }

    int getNb_tactiques_jouee() const { return nb_tactiques_jouees; }

    void setNb_tactiques_jouee(int nb);

    void setPlusNb_tactiques_jouee() { //c'est mieux de faire une fonction qui incrémente le nombre de cartes jouées pour JouerCarte()
        nb_tactiques_jouees++;
    }

    int getScoreManche() const { return scoreManche; }

    void setScoreManche(int score);

    int getScorePartie() const { return scorePartie; }

    void setScorePartie(int score);

    void setCartes(Carte* c, int i);

    //méthode qui affiche les bornes_revendiquees
    void AfficherBornesRevendiquees();

    void Clear();
    Carte* getCartes(int i) const;

    Joueur(const Joueur& j) = delete;
    Joueur& operator=(const Joueur& j) = delete;

    string ChoisirNom();

    virtual void JouerCarte();

    virtual void DemanderRevendication();

    void afficherCartes();

    Carte* piocher();

    void ajouterBorneRevendiquee(Borne* b);

    void afficherAideCombi() const;

    int getNbCartesEnMain() const { return nb_cartes_en_main; }
    void setNbCartesEnMain(int nb) { nb_cartes_en_main = nb; }
    void DecNbCartesEnMain() { nb_cartes_en_main--; }
    void IncNbCartesEnMain() { nb_cartes_en_main++; }


    // Constructeurs et destructeur
    Joueur();
    Joueur(int num) : numero(num), nom(ChoisirNom()), nb_tactiques_jouees(0), scoreManche(0), scorePartie(0), joker_joue(false), nb_cartes_en_main(0) {
        for (int i = 0; i < 7; i++) {
            cartes[i] = nullptr;
        }
    }
    Joueur(int num, string n) : numero(num), nom(n), nb_tactiques_jouees(0), scoreManche(0), scorePartie(0), joker_joue(false), nb_cartes_en_main(0) {
        for (int i = 0; i < 7; i++) {
            cartes[i] = nullptr;
        }
    }

    virtual ~Joueur() = default;
};

ostream& operator<<(ostream& f, const Joueur& j);

class IA : public Joueur {
public:
    IA() : Joueur(2, "IA") {}
    void JouerCarte();
    void DemanderRevendication();

};

void DecalerCartesJoueur(Joueur* j);