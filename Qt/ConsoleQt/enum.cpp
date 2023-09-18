#include <initializer_list>
#include "enum.h"
using namespace std;

std::initializer_list<Couleur> Couleurs = { Couleur::rouge, Couleur::beige, Couleur::bleu, Couleur::jaune, Couleur::vert, Couleur::violet, Couleur::pasdecouleur };
std::initializer_list<Numero> Numeros = { Numero::un, Numero::deux, Numero::trois, Numero::quatre, Numero::cinq,Numero::six,Numero::sept,Numero::huit,Numero::neuf, Numero::pasdenumero };
std::initializer_list<Mode> Modes = { Mode::normal, Mode::tactique, Mode::expert };
std::initializer_list<NomCombinaison> NomCombinaisons = { NomCombinaison::suite_couleur, NomCombinaison::suite, NomCombinaison::brelan, NomCombinaison::somme,NomCombinaison::couleur };
std::initializer_list<NomTactique> NomTactiques = { NomTactique::banshee,NomTactique::chasseur_de_tete,NomTactique::colin_maillard,NomTactique::combat_de_boue,NomTactique::espion,NomTactique::porte_bouclier,NomTactique::joker,NomTactique::stratege,NomTactique::traitre, NomTactique::pasdenom };

string toString(Couleur c) {
    switch (c) {
        case Couleur::rouge: return "Rouge";
        case Couleur::beige: return "Beige";
        case Couleur::vert: return "Vert";
        case Couleur::bleu: return "Bleu";
        case Couleur::jaune: return "Jaune";
        case Couleur::violet: return "Violet";
        case Couleur::pasdecouleur: return "PasDeCouleur";
        default: throw "Couleur inconnue";
    }
}

string toString(Numero n) {
    switch (n) {
        case Numero::un: return "1";
        case Numero::deux: return "2";
        case Numero::trois: return "3";
        case Numero::quatre: return "4";
        case Numero::cinq: return "5";
        case Numero::six: return "6";
        case Numero::sept: return "7";
        case Numero::huit: return "8";
        case Numero::neuf: return "9";
        case Numero::pasdenumero: return "PasDeNumero";
        default: throw "Numéro inconnu";
    }
}

string toString(Mode m) {
    switch (m) {
        case Mode::normal: return "Normal";
        case Mode::tactique: return "Tactique";
        case Mode::expert: return "Expert";
        default: throw "Mode inconnu";
    }
}

string toString(NomCombinaison n) {
    switch (n) {
        case NomCombinaison::suite_couleur: return "Suite Couleur";
        case NomCombinaison::brelan: return "Brelan";
        case NomCombinaison::couleur: return "Couleur";
        case NomCombinaison::somme: return "Somme";
        case NomCombinaison::suite: return "Suite";
        default: throw "Combinaison inconnue";
    }
}

string toString(NomTactique n) {
    switch (n) {
        case NomTactique::joker: return "Joker";
        case NomTactique::banshee: return "Banshee";
        case NomTactique::espion: return "Espion";
        case NomTactique::porte_bouclier: return "Porte Bouclier";
        case NomTactique::colin_maillard: return "Colin Maillard";
        case NomTactique::combat_de_boue: return "Combat de boue";
        case NomTactique::chasseur_de_tete: return "Chasseur de tete";
        case NomTactique::stratege: return "Stratege";
        case NomTactique::traitre: return "Traitre";
        case NomTactique::pasdenom: return "PasDeNom";
        default: throw "Tactique inconnue";
    }
}

int toInt(Numero n) {
    switch (n) {
        case Numero::un: return 1;
        case Numero::deux: return 2;
        case Numero::trois: return 3;
        case Numero::quatre: return 4;
        case Numero::cinq: return 5;
        case Numero::six: return 6;
        case Numero::sept: return 7;
        case Numero::huit: return 8;
        case Numero::neuf: return 9;
        case Numero::pasdenumero: return 0;
        default: throw "Numero Inconnu";
    }
}

Numero toNum(int n) {
    switch (n) {
        case 1: return Numero::un;
        case 2: return Numero::deux;
        case 3: return Numero::trois;
        case 4: return Numero::quatre;
        case 5: return Numero::cinq;
        case 6: return Numero::six;
        case 7: return Numero::sept;
        case 8: return Numero::huit;
        case 9: return Numero::neuf;
        default: return Numero::pasdenumero;
    }
}

Couleur toCouleur(string s) {
    if (s == "rouge") return Couleur::rouge;
    else if (s == "beige") return Couleur::beige;
    else if (s == "vert") return Couleur::vert;
    else if (s == "bleu") return Couleur::bleu;
    else if (s == "jaune") return Couleur::jaune;
    else if (s == "violet") return Couleur::violet;
    else return Couleur::pasdecouleur;
}

ostream& operator<<(ostream& f, Couleur c) { f << toString(c); return f; }
ostream& operator<<(ostream& f, Numero n) { f << toString(n); return f; }
ostream& operator<<(ostream& f, Mode m) { f << toString(m); return f; }
ostream& operator<<(ostream& f, NomCombinaison nc) { f << toString(nc); return f; }
ostream& operator<<(ostream& f, NomTactique nt) { f << toString(nt); return f; }

