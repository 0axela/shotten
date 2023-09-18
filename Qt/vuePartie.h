#ifndef VUEPARTIE_H
#define VUEPARTIE_H

#include "st.h"
#include "vueDefausse.h"
#include "vuePioche.h"

#include <string>
#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>
#include <QComboBox>
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QDebug>
#include <QLabel>
#include <QString>
#include <vector>
#include <QDialog>
#include <QFormLayout>
#include <QLCDNumber>
#include <QProgressBar>

class VueCarte;

using namespace std;

class VuePartie : public QWidget {
    Q_OBJECT
public:
    explicit VuePartie(QWidget *parent = nullptr, string mode = "Mode normal", string manche = "1 manche", string nbJoueur = "1 joueur", string nomJ1 = "Joueur 1", string nomJ2 = "Joueur 2");
    ~VuePartie() {Partie::libererInstance();}
private:

    Partie* partie;    //Partie* partie;
    VuePioche* pioche;
    VueDefausse* defausse;


    QHBoxLayout* ElementsPartie;
    QHBoxLayout * bornes;
    QVBoxLayout* Test;
    QVBoxLayout* pioches;
    QHBoxLayout* scores;

    QLabel* scoreLabel1; // texte "Score"
    QLabel* scoreLabel2; // texte "Score"
    QLCDNumber* score1Displayer;
    QLCDNumber* score2Displayer;// affichage du score

    QLabel* labelPioche; // texte "Pioche"
    QLabel* labelDefausse; // texte "Defausse"

    //PAS UTILISE
    QProgressBar* numberCardsDeckProgressBar; // progression de la pioche
    QHBoxLayout* informationsHeaderLayout;
    QGridLayout* cardsGridLayout; // grille des cartes
    QVBoxLayout* layer;
    vector<VueCarte*> vuecartes; // adresses des objets VueCarte
    //std::vector<Carte::Carte*> selectedCards; // ensemble des cartes sélectionnées
    //ERREUR
    int user1Score=0; // score courant (nb de sets trouvés)
    int user2Score=0;

private slots:
    //void cliqueSettings();
};


class VueSettings : public QDialog
{
    Q_OBJECT

public:
    explicit VueSettings(QWidget *parent = nullptr);
private:
    VuePartie* vueP;
private slots:
    void openPartie(string  mode, string manche, string nbJoueur, string nomJ1, string nomJ2);
};


class FirstWindow : public QWidget {
    Q_OBJECT
private:
    VueSettings* vueSettings;
public:
    explicit FirstWindow(QWidget *parent = nullptr);
private slots:
    void cliqueSettings(){
        VueSettings* vueSettings = new VueSettings();
        vueSettings->show();
        close();
    }
};

#endif // VUEPARTIE_H
