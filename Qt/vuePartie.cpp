#include "vuePartie.h"

#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QProgressBar>
#include <QLCDNumber>
#include <QMessageBox>
#include <QPixmap>
#include <QDebug>
#include <QDir>
//#include <iostream>

using namespace std;

FirstWindow::FirstWindow(QWidget *parent) : QWidget(parent) {

    setWindowTitle("Paramètres de la partie de schotten totten");
    setFixedSize(340, 100);

    QVBoxLayout * layout = new QVBoxLayout(this);
    QLabel* titreParametre = new QLabel("Parametrer la partie : ");
    QPushButton* settingsBoutton = new QPushButton("Paramètres");

    layout->addWidget(titreParametre);
    layout->addWidget(settingsBoutton);

    connect(settingsBoutton, &QPushButton::released, this, &FirstWindow::cliqueSettings);
}

VueSettings::VueSettings(QWidget *parent) : QDialog(parent) {

    //Parametrage de la fenetre
    setWindowTitle("Paramètres de la partie de schotten totten");
    setFixedSize(340, 200);

    //Modes
    QComboBox *modeComboBox = new QComboBox(this);
    modeComboBox->addItem("Mode normal");
    modeComboBox->addItem("Mode tactique");
    modeComboBox->addItem("Mode expert");
    modeComboBox->move(10, 10);

    //Nb joueurs
    QComboBox *playersComboBox = new QComboBox(this);
    playersComboBox->addItem("1 joueur");
    playersComboBox->addItem("2 joueurs");
    playersComboBox->move(120, 10);

    //Nb manches
    QComboBox *manchesComboBox = new QComboBox(this);
    manchesComboBox->addItem("1 manche");
    for(auto i = 2; i < 10; i++){
        QString manche = QString::number(i) + " manches";
        manchesComboBox->addItem(manche);
    }
    manchesComboBox->move(230, 10);

    //Label des joueurs
    QLabel* nom1 = new QLabel("Joueur1 :", this);
    QLineEdit* lineEdit1 = new QLineEdit(this);
    QLabel* nom2 = new QLabel("Joueur2 :", this);
    QLineEdit* lineEdit2 = new QLineEdit(this);
    nom1 -> move(20, 60);
    nom2->move(20, 100);
    lineEdit1->move(80, 60);
    lineEdit2->move(80, 100);
    lineEdit1->setFixedWidth(200);
    lineEdit2->setFixedWidth(200);
    lineEdit1->setText("Joueur 1");
    lineEdit2->setText("Joueur 2");

    //Bouton Suivant
    QPushButton *Button = new QPushButton("Suivant", this);
    int buttonWidth = 300;
    int buttonHeight = 30;
    int buttonX = (340 - buttonWidth) / 2;
    int buttonY = 200 - buttonHeight - 10;
    Button->setGeometry(buttonX, buttonY, buttonWidth, buttonHeight);

    connect(Button, &QPushButton::clicked, this, [modeComboBox, manchesComboBox, playersComboBox, lineEdit1, lineEdit2, this]() {
        openPartie((modeComboBox->currentText()).toStdString(), (manchesComboBox->currentText()).toStdString(), (playersComboBox->currentText()).toStdString(), (lineEdit1->text()).toStdString(), (lineEdit2->text()).toStdString());
    });
}

void VueSettings::openPartie(string  mode, string manche, string nbJoueur, string nomJ1, string nomJ2){
    vueP = new VuePartie(nullptr, mode, manche, nbJoueur, nomJ1, nomJ2);
    vueP->show();
    close();
}


VuePartie::VuePartie(QWidget *parent, string  mode, string manche, string nbJoueur, string nomJ1, string nomJ2) :  QWidget(parent){

    //PARAMETRAGE DE LA FENETRE
    //setFixedSize(3500,5000);
    setWindowTitle("Schotten Totten !");

    //CREATION DES OBJETS
    //centralWidget = new QWidget;

    partie = &Partie::getInstance(mode, manche, nbJoueur, nomJ1, nomJ2);
    //Test pour verifier que la partie est bien crée
    //qDebug() << partie->getNb_manches();

    pioche = new VuePioche;
    labelPioche = new QLabel("Pioche : ");
    pioche->setFixedSize(437/3, 239/3);

    labelDefausse = new QLabel("Defausse : ");
    defausse = new VueDefausse;
    defausse->setFixedSize(437/3, 239/3);

    scoreLabel1 = new QLabel("Score du joueur 1 : ");
    score1Displayer = new QLCDNumber;
    score1Displayer->setFixedSize(90,90);
    score1Displayer->setSegmentStyle(QLCDNumber::Filled);

    scoreLabel2 = new QLabel("Score du joueur 2 : ");
    score2Displayer = new QLCDNumber;
    score2Displayer->setFixedSize(90,90);
    score2Displayer->display(0);

    bornes = new QHBoxLayout;
    for (int i = 0; i < 9; i++) {
        QPushButton *borne = new QPushButton;
        //borne->setFixedSize(150,100);

        borne->setFixedSize(437/3, 239/3);
        QString cheminAbsoluExecutable = QCoreApplication::applicationDirPath(); // Chemin absolu de l'exécutable
        QString cheminRelatif = cheminAbsoluExecutable + "/borne.jpeg"; // Chemin relatif à partir du répertoire de travail, il faut mettre l'image dans \build-ST2-Desktop_Qt_6_5_1_MinGW_64_bit-Debug\debug
        QPixmap image(cheminRelatif);
        borne->setIcon(image);
        borne->setIconSize(QSize(437/3, 239/3));
        bornes->addWidget(borne);
    }


    //GESTION DES LAYOUTS
    pioches = new QVBoxLayout;
    pioches->addWidget(labelPioche);
    pioches->addWidget(pioche);
    pioches->addWidget(labelDefausse);
    pioches->addWidget(defausse);
    bornes->addLayout(pioches);

    scores = new QHBoxLayout;
    scores->addWidget(scoreLabel1);
    scores->addWidget(score1Displayer);
    scores->addWidget(scoreLabel2);
    scores->addWidget(score2Displayer);

    QVBoxLayout * Test = new QVBoxLayout(this);
    Test->addLayout(scores);
    Test->addLayout(bornes);

    ElementsPartie = new QHBoxLayout;
    ElementsPartie->addLayout(Test);
    ElementsPartie->addLayout(pioches);
    //centralWidget->setLayout(ElementsPartie);
    //this->setCentralWidget(centralWidget);
}



