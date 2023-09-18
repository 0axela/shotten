#pragma once


#include <iostream>
#include <random>
#include <string>
#include <vector>


enum class Numero;
enum class Couleur;
enum class NomTactique;
class Elite;
class Combat;
class Ruse;
using namespace std;

class Carte {
private:
protected:
    virtual void print(ostream& f) const { f << "print carte" << endl; }
public:
    friend ostream& operator<<(ostream& f, const Carte& c);

    //une tactique n'a pas forcément de couleur : or on est obligé de lui mettre une couleur par défaut (ici beige) ? à voir
    //Idem pour le numero
    //Idem pour le nom
    virtual Couleur getCouleur() const;
    virtual Numero getNumero() const;
    virtual NomTactique getNom() const;

    virtual void executerEffet() = 0;
};

class Clan : public Carte {
private:
    Numero numero;
    Couleur couleur;
protected:
    virtual void print(ostream& f) const;
public:
    Clan(Numero n, Couleur c) : numero(n), couleur(c) {}
    Numero getNumero() const { return numero; }
    Couleur getCouleur() const { return couleur; }

    void executerEffet() {}

    Clan(const Clan& c) = delete;
    Clan& operator=(const Clan& c) = delete;
};

class EffetTactique {
public:
    virtual void appliquerEffet() = 0;
    virtual ~EffetTactique() {}
};

class JokerEffet : public EffetTactique {
private:
    Elite* joker;
public:
    JokerEffet(Elite* jok) : joker(jok) {}
    void appliquerEffet() override;
};

class EspionEffet : public EffetTactique {
private:
    Elite* espion;
public:
    EspionEffet(Elite* esp) : espion(esp) {}
    void appliquerEffet() override;
};

class PorteBouclierEffet : public EffetTactique {
private:
    Elite* pb;
public:
    PorteBouclierEffet(Elite* p) : pb(p) {}
    void appliquerEffet() override;
};

class ColinMaillardEffet : public EffetTactique {
private:
    Combat* colmaill;
public:
    ColinMaillardEffet(Combat* c) : colmaill(c) {}
    void appliquerEffet() override;
};

class CombatBoueEffet : public EffetTactique {
private:
    Combat* cb;
public:
    CombatBoueEffet(Combat* c) : cb(c) {}
    void appliquerEffet() override;
};

class ChasseurTeteEffet : public EffetTactique {
private:
    Ruse* ct;
public:
    ChasseurTeteEffet(Ruse* r) : ct(r) {}
    void appliquerEffet() override;
};

class BansheeEffet : public EffetTactique {
private:
    Ruse* bansh;
public:
    BansheeEffet(Ruse* b) : bansh(b) {}
    void appliquerEffet() override;
};

class TraitreEffet : public EffetTactique {
private:
    Ruse* traitre;
public:
    TraitreEffet(Ruse* t) : traitre(t) {}
    void appliquerEffet() override;
};

class StrategeEffet : public EffetTactique {
private:
    Ruse* strat;
public:
    StrategeEffet(Ruse* str) : strat(str) {}
    void appliquerEffet() override;
};

class Tactique : public Carte {
private:
    NomTactique nom;
    EffetTactique* effet;
protected:
    virtual void print(ostream& f) const;
public:
    Tactique(NomTactique n);

    NomTactique getNom() const { return nom; }
    void executerEffet() {
        effet->appliquerEffet();
    }
};

class Elite : public Tactique {
private:
    Numero numero;
    Couleur couleur;
protected:
    virtual void print(ostream& f) const;
public:
    Elite(NomTactique n);
    Numero getNumero() const { return numero; }
    Couleur getCouleur() const { return couleur; }

    //Couleur et numéro à changer au moment de la poser
    void setNumero(Numero n) { numero = n; }
    void setCouleur(Couleur c) { couleur = c; }

    Elite(const Elite& e) = delete;
    Elite& operator=(const Elite& e) = delete;
};

class Combat : public Tactique {
protected:
    virtual void print(ostream& f) const;
public:
    Combat(NomTactique n) : Tactique(n) {}
};

class Ruse : public Tactique {
protected:
    virtual void print(ostream& f) const;
public:
    Ruse(NomTactique n) : Tactique(n) {}
};

