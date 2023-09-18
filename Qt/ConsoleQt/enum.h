#pragma once

#include <iostream>
#include <string>

using namespace std;
enum class Numero {
    pasdenumero = 0,
    un = 1,
    deux = 2,
    trois = 3,
    quatre = 4,
    cinq = 5,
    six = 6,
    sept = 7,
    huit = 8,
    neuf = 9
};

enum class NomTactique {
    pasdenom,
    joker,
    espion,
    porte_bouclier,
    colin_maillard,
    combat_de_boue,
    chasseur_de_tete,
    stratege,
    banshee,
    traitre
};

enum class Mode { normal, tactique, expert };
enum class Couleur { rouge, bleu, beige, jaune, vert, violet, pasdecouleur };
enum class NomCombinaison { suite_couleur, brelan, couleur, suite, somme };

//Ecriture d'une caractéristique énum sur un flux ostream
ostream& operator<<(ostream& f, Couleur c);
ostream& operator<<(ostream& f, Numero n);
ostream& operator<<(ostream& f, Mode m);
ostream& operator<<(ostream& f, NomCombinaison nc);
ostream& operator<<(ostream& f, NomTactique nt);

//Listes contenant les valeurs possibles pour nos caractéristiques
extern std::initializer_list<Couleur> Couleurs;
extern std::initializer_list<Numero> Numeros;
extern std::initializer_list<Mode> Modes;
extern std::initializer_list<NomCombinaison> NomCombinaisons;
extern std::initializer_list<NomTactique> NomTactiques;

string toString(Couleur c);
string toString(Numero n);
string toString(Mode m);
string toString(NomCombinaison n);
string toString(NomTactique n);
int toInt(Numero n);
Numero toNum(int n);
Couleur toCouleur(string s);