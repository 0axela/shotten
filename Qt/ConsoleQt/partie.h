#pragma once
using namespace std;
#include <iostream>
#include <string>
#include <initializer_list>
#include <array>
#include <vector>
#include <cstdlib>
#include <stack>
#include <algorithm>
#include <random>
#include <chrono>
#include <iomanip>
#include <thread>

enum class Mode;
enum class Couleur;
class Joueur;
class IA;
class Borne;
class Clan;
class Tactique;
class Pioche_Clan;
class Pioche_Tactique;
class Defausse;


#define NB_BORNE 9
#define NB_CLAN 54
#define NB_TACTIQUE 10 //9 + 1 joker

class Partie {

private:
    static Partie* instanceUnique;

    ~Partie();
    Mode mode;
    Joueur* gagnant;
    IA* ia;
    int nb_manches;
    int currentManche;
    Joueur* joueur1;
    Joueur* joueur2;
    Borne* frontiere[NB_BORNE];
    Joueur* commence;
    Clan* clan[NB_CLAN];
    Tactique* tactique[NB_TACTIQUE]; //9 différentes dont 2 jokers
    Pioche_Clan* piocheClan;
    Pioche_Tactique* piocheTactique;
    Defausse* defausse;
    Joueur* dernierjoueur;

    Partie();
    Partie(string gamemode, string nbManches, string nbJoueur, string nomJ1, string nomJ2);

public:


    //------------singleton------------
    static Partie& getInstance();
    static Partie& getInstance(string gamemode, string nbManches, string nbJoueur, string nomJ1, string nomJ2);
    static void libererInstance();
    //------------getteur------------

    Mode getMode() const { return mode; }
    Joueur* getGagnant() const { return gagnant; }
    bool isIA() const { return (ia != nullptr); }
    int getNb_manches() const { return nb_manches; }
    Joueur* getJoueur1() { return joueur1; } //pas const
    Joueur* getJoueur2() { return joueur2; }
    IA* getIA() { return ia; }
    Borne* getFrontiere(int i) const { return frontiere[i]; }
    Joueur* getCommence() { return commence; }
    Clan* getClan(int i) { return clan[i]; }
    Tactique* getTactique(int i) { return tactique[i]; }
    Pioche_Clan* getPiocheClan() const { return piocheClan; }
    Pioche_Tactique* getPiocheTactique() const { return piocheTactique; }
    Joueur* getDernierjoueur() const { return dernierjoueur; }
    Defausse* getDefausse() { return defausse; }

    //------------méthodes de l'UML------------

    void setCommence(Joueur* j) {commence = j;}
    
    void setDernierjoueur(Joueur* j) { dernierjoueur = j; }

    void VerifGagnantPartie();

    bool VerifGagnantManche(Joueur* j); //ou alors utiliser les getJoueur

    Joueur* DonnerMain();

    int NombreManches(); //mettre cette méthode dans le constructeurs

    [[maybe_unused]] void scoreAzero(Joueur* j);

    [[maybe_unused]] void AfficherTactique();

    void AfficherClan();

    Mode ModePartie();

    void afficherFrontiere();

    void distribuer_debut();

    void jeu();

};

