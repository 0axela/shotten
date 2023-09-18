#include "pioche.h"
#include "carte.h"

//************************

//Pioche Commune

//************************

Pioche_Clan::Pioche_Clan(Clan** cartes_clan) {
    size_t i;
    for (i = 0; i < 54; i++) {
        Empiler(cartes_clan[i]);
    }
}

Pioche_Tactique::Pioche_Tactique(Tactique** cartes_tactiques) {
    size_t i;
    for (i = 0; i < 10; i++) {
        Empiler(cartes_tactiques[i]);
    }
}

ostream& operator<<(ostream& f, const Carte& c) {
    //redefinir operator<< pour les cartes
    c.print(f); //delegate printing to member function
    return f;
}

//****************
//Défausse
//****************

void Defausse::ajouterCarte(const Carte* c) {
    cartes.push_back(c);
}
void Defausse::AfficherDefausse() {
    cout << "Défausse: ";

    if (cartes.size() == 0) cout << "Vide \n";
    else {
        for (size_t i = 0; i < cartes.size(); i++) {
            cout << *cartes[i] << " ";
        }
        cout << endl;
    }

}
