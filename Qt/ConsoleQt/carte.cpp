//
// Created by axela on 07/06/2023.
//
#include <iostream>
#include <random>
#include "carte.h"
#include "enum.h"
#include "partie.h"
#include "joueur.h"
#include "pioche.h"
#include "borne.h"

Couleur Carte::getCouleur() const { return Couleur::pasdecouleur; }

Numero Carte::getNumero() const { return Numero::pasdenumero; }

NomTactique Carte::getNom() const { return NomTactique::pasdenom; }
//************************
//Carte Tactiques
//************************

Elite::Elite(NomTactique n) : Tactique(n) {
    couleur = Couleur::pasdecouleur; //Par défaut mais modifiable
    if (getNom() == NomTactique::espion) numero = Numero::sept;
    else numero = Numero::pasdenumero; //Numéro par défaut mais modifiable
}

void Elite::print(ostream &f) const { f << "(Elite)[" << getNom() << "," << numero << "," << couleur << "]"; }

void JokerEffet::appliquerEffet() {
    string reponseCouleur;
    int reponseNumero;

    //Choix pour le joueur
    if (Partie::getInstance().getDernierjoueur()->getNom() != "IA") {
        cout << "\n> JOKER: Numéro de la carte joker: ";
        cin >> reponseNumero;
        while (reponseNumero < 1 || reponseNumero > 9) {
            cout << "WARNING: Le numéro doit être entre 1 et 9: ";
            cin >> reponseNumero;
        }

        cout << "> JOKER: Couleur de la carte joker: (rouge, bleu, beige, jaune, vert, violet)\n";
        cin >> reponseCouleur;
        transform(reponseCouleur.begin(), reponseCouleur.end(), reponseCouleur.begin(), ::tolower);
        while (reponseCouleur != "rouge" && reponseCouleur != "bleu" && reponseCouleur != "beige" &&
               reponseCouleur != "jaune" && reponseCouleur != "vert" && reponseCouleur != "violet") {
            cout << "WARNING: Entrez une couleur valide !";
            cin >> reponseCouleur;
            transform(reponseCouleur.begin(), reponseCouleur.end(), reponseCouleur.begin(), ::tolower);
        }
    }
        //Choix random pour l'IA
    else {
        srand(std::time(0));
        reponseNumero = rand() % 9 + 1;
        string couleurs[] = { "rouge","bleu","beige","jaune","vert","violet" };
        reponseCouleur = couleurs[rand() % 6];
        cout << "L'IA initialise sa carte Joker avec la couleur " << reponseCouleur << " et le numéro " << reponseNumero << "\n";
    }

    joker->setNumero(toNum(reponseNumero));
    joker->setCouleur(toCouleur(reponseCouleur));

}

void EspionEffet::appliquerEffet() {
    string reponseCouleur;

    //Choix pour le joueur
    if (Partie::getInstance().getDernierjoueur()->getNom() != "IA") {
        cout << "\n> ESPION: Couleur de la carte espion: (rouge, bleu, beige, jaune, vert, violet)\n";
        cin >> reponseCouleur;
        transform(reponseCouleur.begin(), reponseCouleur.end(), reponseCouleur.begin(), ::tolower);
        while (reponseCouleur != "rouge" && reponseCouleur != "bleu" && reponseCouleur != "beige" &&
               reponseCouleur != "jaune" && reponseCouleur != "vert" && reponseCouleur != "violet") {
            cout << "WARNING: Entrez une couleur valide :" << endl;
            cin >> reponseCouleur;
            transform(reponseCouleur.begin(), reponseCouleur.end(), reponseCouleur.begin(), ::tolower);
        }
    }
        //Choix random pour l'IA
    else {
        srand(std::time(0));
        string couleurs[] = { "rouge","bleu","beige","jaune","vert","violet" };
        reponseCouleur = couleurs[rand() % 6];
        cout << "L'IA initialise sa carte Espion avec la couleur " << reponseCouleur << "\n";
    }
    Couleur couleur = toCouleur(reponseCouleur);
    espion->setCouleur(couleur);

}

void PorteBouclierEffet::appliquerEffet() {
    string reponseCouleur;
    int reponseNumero;

    //Choix pour le joueur
    if (Partie::getInstance().getDernierjoueur()->getNom() != "IA") {
        cout << "\n> PORTE-BOUCLIER: Numéro de la carte Porte-Bouclier: " << endl;
        cin >> reponseNumero;
        while (reponseNumero < 1 || reponseNumero > 3) {
            cout << "WARNING: Le numéro doit être entre 1 et 3: ";
            cin >> reponseNumero;
        }

        cout << "> PORTE-BOUCLIER: Couleur de la carte Porte-Bouclier: (rouge, bleu, beige, jaune, vert, violet)\n";
        cin >> reponseCouleur;
        while (reponseCouleur != "rouge" && reponseCouleur != "bleu" && reponseCouleur != "beige" &&
               reponseCouleur != "jaune" && reponseCouleur != "vert" && reponseCouleur != "violet") {
            cout << "> WARNING: Entrez une couleur valide !" << endl;
            cin >> reponseCouleur;
            transform(reponseCouleur.begin(), reponseCouleur.end(), reponseCouleur.begin(), ::tolower);
        }
    }
        //Choix random pour l'IA
    else {
        srand(std::time(0));
        string couleurs[] = { "rouge","bleu","beige","jaune","vert","violet" };
        reponseCouleur = couleurs[rand() % 6];
        reponseNumero = rand() % 3 + 1;
        cout << "L'IA initialise sa carte Porte bouclier avec la couleur " << reponseCouleur << " et le numéro " << reponseNumero << "\n";
    }
    pb->setNumero(toNum(reponseNumero));
    pb->setCouleur(toCouleur(reponseCouleur));
}

void ColinMaillardEffet::appliquerEffet() {

    size_t indiceBorne;

    if (Partie::getInstance().getDernierjoueur()->getNom() != "IA") {
        cout << "\n> COLINMAILLARD: Sur quelle borne voulez vous jouer la carte ? \n";
        cin >> indiceBorne;
        while (indiceBorne < 0 || indiceBorne > 8) { //si l'indice de la borne n'est pas correct
            cout << "> WARNING: L'indice de la borne doit être compris entre 0 et 8 \n";
            cout << "> COLINMAILLARD: Retapez un indice \n";
            cin >> indiceBorne;
        }
    }
    else {
        srand(std::time(0));
        indiceBorne = rand() % 9;
        cout << "L'IA a appliqué une carte Colin maillard sur la borne n°" << indiceBorne << "\n";
    }
    Partie::getInstance().getFrontiere(indiceBorne)->ColinMaillardTrue();


}

void CombatBoueEffet::appliquerEffet() {

    size_t indiceBorne;
    if (Partie::getInstance().getDernierjoueur()->getNom() != "IA") {
        cout << "\n> COMBATBOUE: Sur quelle borne voulez vous jouer la carte ? \n";
        cin >> indiceBorne;
        while (indiceBorne < 0 || indiceBorne > 8) { //si l'indice de la borne n'est pas correct
            cout << "> WARNING: L'indice de la borne doit être compris entre 0 et 8 \n";
            cout << "> COMBATBOUE: Retapez un indice \n";
            cin >> indiceBorne;
        }
    }
    else {
        srand(std::time(0));
        indiceBorne = rand() % 9;
        cout << "L'IA a appliqué une carte Combat de boue sur la borne n°" << indiceBorne << "\n";
    }
    Partie::getInstance().getFrontiere(indiceBorne)->CombatBoueTrue();

}

//A finir
void ChasseurTeteEffet::appliquerEffet() {
    //il y a forcément 7 cartes dans la main du joueur car on est forcément en mode tactique
    //piochez trois cartes d’une seule ou des deux pioches. Choisissez deux cartes parmi toutes celles de votre main et placez-les en dessous de la pioche correspondante.
    //on récupère le dernier joueur qui a joué


    Joueur* joueur = Partie::getInstance().getDernierjoueur();

    //Effet pour les joueurs
    if (joueur->getNom() != "IA") {
        //on récupère son numéro
        int numero = joueur->getNumero();
        //on localise la carte chasseur de tete dans la main du joueur
        int indice_cdt;
        for (int i = 0; i < 7; i++) {
            if (joueur->getCartes(i)->getNom() == NomTactique::chasseur_de_tete) {
                indice_cdt = i;
                break;
            }
        }
        //on récupère trois cartes de la pioche du joueur: ces trois cartes vont remplacer la carte chasseur de tete et deux cartes de sa main qu'il aura choisi
        //on demande au joueur de piocher 3 cartes
        int compteur = 0;
        Carte* ctarray[3];
        int ctarray2[2];
        for (int i = 0; i < 2; i++) {
            ctarray2[i] = -1;
        }
        cout << "\n> CHASSEURTETE: Piochez 3 cartes: \n";
        for (int i = 0; i < 3; i++) ctarray[i] = joueur->piocher();
        //on affiche les 3 cartes
        cout << "CHASSEURTETE: Voici les 3 cartes que vous avez pioché: \n\n";
        for (int i = 0; i < 3; i++) cout << *ctarray[i] << endl;
        //on demande de choisir deux cartes de sa main à enlever et à placer en dessous de la pioche
        //afficher la main du joueur
        cout << "CHASSEURTETE: Voici votre main: \n";

        joueur->DecNbCartesEnMain(); //pour compenser le fait de piocher
        joueur->DecNbCartesEnMain(); //pour compenser le fait de piocher
        joueur->DecNbCartesEnMain();

        joueur->afficherCartes();
        cout << "CHASSEURTETE: Choisissez deux cartes de votre main à placer en dessous de la pioche: \n";
        for (int i = 0; i < 2; i++) {
            cout << "Carte " << i << " : ";
            cin >> compteur;
            while (compteur < 0 || compteur > joueur->getNbCartesEnMain() || joueur->getCartes(compteur)->getNom() == NomTactique::chasseur_de_tete || compteur == ctarray2[0]) {
                cout << "WARNING: Entrez un numéro de carte valide (entre 0 et " << joueur->getNbCartesEnMain() << ") et ne choissisez pas ChasseurDeTete.Veillez également à ne pas choisir les 2 mêmes cartes. \n";
                cin >> compteur;
            }
            ctarray2[i] = compteur;
        }

        //Une fois les 2 cartes choisies, on commence par défausser chasseur de tete et on la remplace dans la main du joueur par le premier élément de ctarray
        Partie::getInstance().getDefausse()->ajouterCarte(joueur->getCartes(indice_cdt));
        joueur->setCartes(nullptr, indice_cdt); //par sécurité
        joueur->setCartes(ctarray[0], indice_cdt);
        //on récupère la carte du joueur, on la met en dessous de la pioche
        //on l'enlève de sa main
        for (int i = 1; i < 3; i++) {
            //ajouter la carte en dessous de la pioche selon le type de la carte
            if (joueur->getCartes(ctarray2[i - 1])->getNom() == NomTactique::pasdenom) Partie::getInstance().getPiocheClan()->AjouterEnDessous(
                        dynamic_cast<Clan*>(joueur->getCartes(ctarray2[i - 1])));
            else Partie::getInstance().getPiocheTactique()->AjouterEnDessous(
                        dynamic_cast<Tactique*>(joueur->getCartes(ctarray2[i - 1])));
            joueur->setCartes(nullptr, ctarray2[i - 1]); //par sécurité
            joueur->setCartes(ctarray[i], ctarray2[i - 1]);
        }
    }
        //Choix random pour l'IA
    else {
        int indice_cdt;
        for (int i = 0; i < 7; i++) {
            if (joueur->getCartes(i)->getNom() == NomTactique::chasseur_de_tete) {
                indice_cdt = i;
                break;
            }
        }

        //on récupère trois cartes de la pioche: ces trois cartes vont remplacer la carte chasseur de tete et deux cartes de sa main qu'il aura choisi
        //on fait piocher 3 cartes à l'IA
        Carte* ctarray[3];
        int ctarray2[2];
        for (int i = 0; i < 3; i++) ctarray[i] = joueur->piocher();

        joueur->DecNbCartesEnMain(); //pour compenser le fait de piocher
        joueur->DecNbCartesEnMain(); //pour compenser le fait de piocher
        joueur->DecNbCartesEnMain(); //pour compenser le fait de piocher


        //Choix des 2 cartes à enlever de la main de l'IA
        int indice = 0;
        for (int i = 0; i < 2; i++) {
            indice = rand() % joueur->getNbCartesEnMain();
            while (joueur->getCartes(indice)->getNom() == NomTactique::chasseur_de_tete) {
                indice = rand() % joueur->getNbCartesEnMain();
            }
            ctarray2[i] = indice;
        }
        //Une fois les 2 cartes choisies, on commence par défausser chasseur de tete et on la remplace dans la main du joueur par le premier élément de ctarray
        Partie::getInstance().getDefausse()->ajouterCarte(joueur->getCartes(indice_cdt));
        joueur->setCartes(nullptr, indice_cdt); //par sécurité
        joueur->setCartes(ctarray[0], indice_cdt);

        //on récupère la carte du joueur, on la met en dessous de la pioche
        //on l'enlève de sa main
        for (int i = 1; i < 3; i++) {
            //ajouter la carte en dessous de la pioche selon le type de la carte
            if (joueur->getCartes(ctarray2[i - 1])->getNom() == NomTactique::pasdenom) Partie::getInstance().getPiocheClan()->AjouterEnDessous(dynamic_cast<Clan*>(joueur->getCartes(ctarray2[i - 1])));
            else Partie::getInstance().getPiocheTactique()->AjouterEnDessous(dynamic_cast<Tactique*>(joueur->getCartes(ctarray2[i - 1])));
            joueur->setCartes(nullptr, ctarray2[i - 1]); //par sécurité
            joueur->setCartes(ctarray[i], ctarray2[i - 1]);
        }
        cout << "L'IA a joué Chasseur de Tete, elle a pioché 3 cartes au total dans une (ou les deux) pioche(s), qui ont remplacé la carte Chasseur de tête et 2 autres cartes dans son jeu"
             << " qui ont été mises en dessous de la/les pioche(s) concernée(s)\n";
    }
}

void BansheeEffet::appliquerEffet() {
    //Choisir une carte sur une borne du côté adverse
    //La borne ne doit pas être revendiquée
    //Mettre dans la défausse

    int numero_borne;
    bool est_revendiquee;
    int carte_a_enlever = 3;

    Partie::getInstance().afficherFrontiere();
    if (Partie::getInstance().getDernierjoueur()->getNom() != "IA") {
        cout << "\n BANSHEE: Sur quelle borne souhaitez-vous voler une carte adverse ? (Attention, elle doit être non revendiquée): ";
        cin >> numero_borne;
        cout << "\n";

        //Regarder si la borne est déjà revendiquée ou pas
        if (Partie::getInstance().getFrontiere(numero_borne)->getProprietaire() == nullptr) {
            est_revendiquee = false;
        }
        else {
            est_revendiquee = true;
        }

        //Récupérer le joueur qui joue la Banshee pour pouvoir prendre dans les cartes du bon côté de la borne
        int numero_joueur_appelant = Partie::getInstance().getDernierjoueur()->getNumero();
        int numero_joueur_affecte = (numero_joueur_appelant == 1) ? 2 : 1;

        while ((numero_borne < 0 || numero_borne > 8) || (est_revendiquee == true)
               ||
               (numero_joueur_appelant == 1 && Partie::getInstance().getFrontiere(numero_borne)->getnbCartes2() == 0) ||
               (numero_joueur_appelant == 2 && Partie::getInstance().getFrontiere(numero_borne)->getnbCartes1() ==
                                               0)) { //si l'indice de la borne n'est pas correct) {
            cout << "\n";
            cout
                    << "WARNING: Saisissez un numéro de borne valide, non revendiquée et où il y a suffisamment de cartes du côté de votre adversaire ! \n";

            if (numero_borne >= 0 && numero_borne <= 8) {
                if (Partie::getInstance().getFrontiere(numero_borne)->getProprietaire() == nullptr)
                    est_revendiquee = false;
                else {
                    cout << "WARNING: Cette borne est déjà revendiquée ! \n\n";
                }
            }

            if (((numero_joueur_appelant == 1 &&
                  Partie::getInstance().getFrontiere(numero_borne)->getnbCartes2() == 0)) ||
                (numero_joueur_appelant == 2 &&
                 Partie::getInstance().getFrontiere(numero_borne)->getnbCartes1() == 0)) {
                cout << "WARNING: Il n'y a aucune carte du côté de votre adversaire, saisissez à nouveau !\n";
            }

            cin >> numero_borne;

        }

        carte_a_enlever = 3;

        //Cas joueur 1 affecté
        if (numero_joueur_affecte == 1) {
            size_t taille = Partie::getInstance().getFrontiere(numero_borne)->getnbCartes1();
            while ((carte_a_enlever < 0 || carte_a_enlever > 2) || (carte_a_enlever > taille - 1)) {
                cout << "BANSHEE: Quel est l'indice de la carte à enlever ? Il doit être compris entre 0 et "
                     << taille - 1 << " : ";
                cin >> carte_a_enlever;
                cout << "\n";

                if (carte_a_enlever > taille - 1) {
                    cout << "WARNING: Il n'y a pas autant de cartes pour que cet indice soit correct ! \n\n";
                }
            }
            Partie::getInstance().getDefausse()->ajouterCarte(
                    Partie::getInstance().getFrontiere(numero_borne)->getCarte1(carte_a_enlever));

            //On met à nullptr la carte qu'on enlève
            Partie::getInstance().getFrontiere(numero_borne)->setCarte1(carte_a_enlever, nullptr);

            //Décalage du tableau pour réarranger le fait qu'on a un nullptr qui traine
            DecalerBorne(numero_borne, numero_joueur_affecte);

            //Décrémente le nb de cartes associées au joueur 1 sur la borne
            Partie::getInstance().getFrontiere(numero_borne)->setnbCartes1(taille - 1);
        }

        carte_a_enlever = 3;

        //Cas joueur 2 affecté
        if (numero_joueur_affecte == 2) {
            size_t taille = Partie::getInstance().getFrontiere(numero_borne)->getnbCartes2();
            while ((carte_a_enlever < 0 || carte_a_enlever > 2) || (carte_a_enlever > taille - 1)) {
                cout << "BANSHEE: Quel est l'indice de la carte à enlever ? Il doit être compris entre 0 et "
                     << taille - 1 << " ";
                cin >> carte_a_enlever;
                cout << "\n";

                if (carte_a_enlever > taille - 1) {
                    cout << "WARNING: Il n'y a pas autant de cartes pour que cet indice soit correct ! \n\n";
                }
            }
            Partie::getInstance().getDefausse()->ajouterCarte(
                    Partie::getInstance().getFrontiere(numero_borne)->getCarte2(carte_a_enlever));

            //On met à nullptr la carte qu'on enlève
            Partie::getInstance().getFrontiere(numero_borne)->setCarte2(carte_a_enlever, nullptr);

            //Décalage du tableau pour réarranger le fait qu'on a un nullptr qui traine
            DecalerBorne(numero_borne, numero_joueur_affecte);

            //Décrémente le nb de cartes associées au joueur 1 sur la borne
            Partie::getInstance().getFrontiere(numero_borne)->setnbCartes2(taille - 1);
        }
    }
        //Cas où c'est l'IA qui joue la carte
    else {
        srand(std::time(0));
        //Choix n° borne
        numero_borne = rand() % 9;
        while (Partie::getInstance().getFrontiere(numero_borne)->getProprietaire() != nullptr || Partie::getInstance().getFrontiere(numero_borne)->getnbCartes1() == 0) {
            numero_borne = rand() % 9;
        }

        //Choix de la carte à enlever
        carte_a_enlever = rand() % 3;
        size_t taille = Partie::getInstance().getFrontiere(numero_borne)->getnbCartes1();
        while (carte_a_enlever > taille - 1) {
            carte_a_enlever = rand() % 3;
        }

        Partie::getInstance().getDefausse()->ajouterCarte(Partie::getInstance().getFrontiere(numero_borne)->getCarte1(carte_a_enlever));
        cout << "\n" << "L'IA a joué une carte Banshee sur la borne n°" << numero_borne << " et a fait retirer la carte " << *Partie::getInstance().getFrontiere(numero_borne)->getCarte1(carte_a_enlever) << "\n";

        //On met à nullptr la carte qu'on enlève
        Partie::getInstance().getFrontiere(numero_borne)->setCarte1(carte_a_enlever, nullptr);

        //Décalage du tableau pour réarranger le fait qu'on a un nullptr qui traine
        DecalerBorne(numero_borne, 1);

        //Décrémente le nb de cartes associées au joueur 1 sur la borne
        Partie::getInstance().getFrontiere(numero_borne)->setnbCartes1(taille - 1);

    }
}

void TraitreEffet::appliquerEffet() {
    // choisissez une carte Clan du côté adverse de la frontière devant une Borne non revendiquée et placez-la devant une Borne non revendiquée de votre côté.
    int borne;
    int carte;
    int borne2;
    int numero;
    if (Partie::getInstance().getDernierjoueur()->getNom() != "IA") {
        //Affichage de la frontière
        Partie::getInstance().afficherFrontiere();
        cout << "\n TRAITRE: Vous devez choisir une carte Clan du côté adverse de la frontière devant une Borne non revendiquée" << endl;
        cout << "TRAITRE: Choissisez une borne non revendiquée" << endl;
        cin >> borne;
        Joueur* joueur = Partie::getInstance().getDernierjoueur();
        numero = joueur->getNumero();
        int opponent = (numero == 1) ? 2 : 1;
        Borne* borneclass = Partie::getInstance().getFrontiere(borne);
        bool clan_dans_borne = false;
        if (opponent == 1) {
            for (int i = 0; i < borneclass->getnbCartes1(); i++) {
                if (borneclass->getCarte1(i)->getNom() == NomTactique::pasdenom) {
                    clan_dans_borne = true;
                }
            }
        }
        else {
            for (int i = 0; i < borneclass->getnbCartes2(); i++) {
                if (borneclass->getCarte2(i)->getNom() == NomTactique::pasdenom) {
                    clan_dans_borne = true;
                }
            }
        }
        //si c'est le joueur 1 qui joue, il choisit parmi les cartes du joueur 2 et inversement
        while (!clan_dans_borne || borne < 0 || borne > 8 || Partie::getInstance().getFrontiere(borne)->getProprietaire() != nullptr
               || numero == 1 && Partie::getInstance().getFrontiere(borne)->getnbCartes2() == 0
               || numero == 2 && Partie::getInstance().getFrontiere(borne)->getnbCartes1() == 0) { //si l'indice de la borne n'est pas correct
            cout << "WARNING: L'indice de la borne doit être compris entre 0 et 8 et non revendiquée ou vide (cartes Clan) du côté de l'adversaire \n";
            cout << "TRAITRE: Retapez un indice \n";
            cin >> borne;
        }
        //choix de la carte
        const Carte* temp = nullptr;
        int adversaire = (numero == 1) ? 2 : 1;
        if (numero == 1) {
            cout << "\n TRAITRE: Choissisez une carte Clan de votre adversaire" << endl;
            cin >> carte;
            size_t taille = Partie::getInstance().getFrontiere(borne)->getnbCartes2();
            // on vérifie que l'indice de la carte est correct et que la carte est une carte clan
            while (carte < 0 || carte > taille - 1 ||
                   Partie::getInstance().getFrontiere(borne)->getCarte2(carte)->getNom() != NomTactique::pasdenom) {
                cout << "WARNING: L'indice de la carte clan doit être compris entre 0 et "
                     << taille - 1 << " (et ne doit pas être une carte Tactique)" << endl;
                cout << "TRAITRE: Retapez un indice \n";
                cin >> carte;
            }
            //on récupère la carte
            temp = Partie::getInstance().getFrontiere(borne)->getCarte2(carte);
            //on supprime la carte
            Partie::getInstance().getFrontiere(borne)->setCarte2(carte, nullptr);
            DecalerBorne(borne, adversaire);
            //on décrémente le nombre de cartes
            Partie::getInstance().getFrontiere(borne)->setnbCartes2(taille - 1);
        }
        else {
            cout << "TRAITRE: Choissisez une carte Clan de votre adversaire" << endl;
            cin >> carte;
            size_t taille = Partie::getInstance().getFrontiere(borne)->getnbCartes1();
            while (carte < 0 || carte > taille - 1 ||
                   Partie::getInstance().getFrontiere(borne)->getCarte1(carte)->getNom() != NomTactique::pasdenom) {
                cout << "WARNING: L'indice de la carte doit être compris entre 0 et "
                     << taille - 1 << "(et ne doit pas être une carte Tactique)" << endl;
                cout << "TRAITRE: Retapez un indice \n";
                cin >> carte;
            }
            //on récupère la carte
            temp = Partie::getInstance().getFrontiere(borne)->getCarte1(carte);
            //on supprime la carte
            Partie::getInstance().getFrontiere(borne)->setCarte1(carte, nullptr);
            DecalerBorne(borne, adversaire);

            //on décrémente le nombre de cartes
            Partie::getInstance().getFrontiere(borne)->setnbCartes1(taille - 1);
        }

        //on la place dans une borne de notre côté
        cout << "TRAITRE: Choissisez une borne non revendiquée et non pleine pour placer la carte" << endl;
        cin >> borne2;
        //On vérifie que la borne n'est pas pleine
        int max_cartes_borne = 3;
        if (Partie::getInstance().getFrontiere(borne2)->getCombatBoue()) max_cartes_borne = 4;

        while (borne2 < 0 || borne2 > 8 || Partie::getInstance().getFrontiere(borne2)->getProprietaire() != nullptr
               || numero == 1 && max_cartes_borne == Partie::getInstance().getFrontiere(borne2)->getnbCartes1()
               || numero == 2 && max_cartes_borne == Partie::getInstance().getFrontiere(borne2)->getnbCartes2()) { //si l'indice de la borne n'est pas correct
            cout << "WARNING! L'indice de la nouvelle borne doit être entre 0 et 8 et la borne ne doit pas être revendiquée ou pleine de votre côté \n";
            cout << "TRAITRE: Retapez un indice \n";
            cin >> borne2;
        }

        //On place la carte sur la borne au prochain indice disponible
        if (numero == 1) {
            Partie::getInstance().getFrontiere(borne2)->ajouter_cartes1(*temp);
            return;
        }
        else {
            Partie::getInstance().getFrontiere(borne2)->ajouter_cartes2(*temp);
            return;
        }
    }
        //Choix random pour l'IA
    else {
        srand(std::time(0));
        Borne* borneclass;
        bool clan_dans_borne = false;
        //On test si l'utilisation de traitre est possible...
        bool is_possible = false;

        for (int i = 0; i < NB_BORNE; i++) {

            borneclass = Partie::getInstance().getFrontiere(i);
            clan_dans_borne = false;
            for (int j = 0; j < borneclass->getnbCartes1(); j++) {

                if (borneclass->getCarte1(j)->getNom() == NomTactique::pasdenom) {
                    clan_dans_borne = true;
                }
            }

            if (Partie::getInstance().getFrontiere(i)->getnbCartes1() != 0 && Partie::getInstance().getFrontiere(i)->getProprietaire() == nullptr && clan_dans_borne) {
                is_possible = true;
            }
        }
        if (!is_possible) {
            cout << "L'IA a voulu jouer traitre mais aucune borne ne peut satisfaire les conditions de la carte traitre\n\n";
            return;
        }
        borne = rand() % 9;
        borneclass = Partie::getInstance().getFrontiere(borne);
        clan_dans_borne = false;

        while (Partie::getInstance().getFrontiere(borne)->getProprietaire() != nullptr || Partie::getInstance().getFrontiere(borne)->getnbCartes1() == 0 || !clan_dans_borne) {
            borne = rand() % 9;

            for (int i = 0; i < Partie::getInstance().getFrontiere(borne)->getnbCartes1(); i++) {
                if (Partie::getInstance().getFrontiere(borne)->getCarte1(i)->getNom() == NomTactique::pasdenom) {
                    clan_dans_borne = true;
                }
            }
        }

        //Choix de la carte à voler

        const Carte* temp = nullptr;
        size_t taille = Partie::getInstance().getFrontiere(borne)->getnbCartes1();
        carte = rand() % taille;
        while (Partie::getInstance().getFrontiere(borne)->getCarte1(carte)->getNom() != NomTactique::pasdenom) {
            carte = rand() % taille;
        }

        //on récupère la carte
        temp = Partie::getInstance().getFrontiere(borne)->getCarte1(carte);
        //on supprime la carte
        Partie::getInstance().getFrontiere(borne)->setCarte1(carte, nullptr);
        DecalerBorne(borne, 1);

        //on décrémente le nombre de cartes
        Partie::getInstance().getFrontiere(borne)->setnbCartes1(taille - 1);

        //Déplacement de la carte sur une borne du côté de l'IA
        borne2 = rand() % 9;
        int max_cartes_borne = 3;
        if (Partie::getInstance().getFrontiere(borne2)->getCombatBoue()) max_cartes_borne = 4;

        while (Partie::getInstance().getFrontiere(borne2)->getProprietaire() != nullptr || max_cartes_borne == Partie::getInstance().getFrontiere(borne2)->getnbCartes1()) {
            borne2 = rand() % 9;

        }
        Partie::getInstance().getFrontiere(borne2)->ajouter_cartes2(*temp);

        cout << "L'IA a joué une carte Traitre. Elle a volé la carte " << *temp << " sur la borne n°" << borne << " et l'a déplacé de son côté sur la borne n°" << borne2 << "\n";

    }
}

void StrategeEffet::appliquerEffet() {
    const Carte* carteStratege = nullptr;
    if (Partie::getInstance().getDernierjoueur()->getNom() != "IA") {
        cout << "\n STRATEGE: Choissisez une carte carte Clan ou Tactique de votre côté de la frontière sur une Borne non revendiquée." << endl;
        cout << "STRATEGE: Choissisez une borne non revendiquée" << endl;
        int borne;
        cin >> borne;
        Joueur* joueur = Partie::getInstance().getDernierjoueur();
        int numero = joueur->getNumero();
        while (borne < 0 || borne > 8 || Partie::getInstance().getFrontiere(borne)->getProprietaire() != nullptr
               || numero == 1 && Partie::getInstance().getFrontiere(borne)->getnbCartes1() == 0 || numero == 2 && Partie::getInstance().getFrontiere(borne)->getnbCartes2() == 0) { //si l'indice de la borne n'est pas correct
            cout << "WARNING: L'indice de la borne doit être compris entre 0 et 8 et la borne ne doit pas être revendiquée ou vide \n";
            cout << "STRATEGE: Retapez un indice \n";
            cin >> borne;
        }
        //On vérifie que la borne est pas vide du côté du joueur

        cout << "STRATEGE: Choissisez une carte Clan ou Tactique de votre côté de la frontière" << endl;
        int carte;
        cin >> carte;
        //Verification que la carte est bien dans la borne
        size_t max;
        if (numero == 1) {
            max = Partie::getInstance().getFrontiere(borne)->getnbCartes1();
        }
        else {
            max = Partie::getInstance().getFrontiere(borne)->getnbCartes2();
        }
        while (carte < 0 || carte > max - 1) {
            cout << "WARNING: La carte doit être comprise entre 0 et " << max - 1 << endl;
            cout << "STRATEGE: Retapez un indice \n";
            cin >> carte;
        }
        // On sauvegarde la carte et on la supprime de la borne
        carteStratege = nullptr;
        if (numero == 1) {
            int taille = Partie::getInstance().getFrontiere(borne)->getnbCartes1();
            carteStratege = Partie::getInstance().getFrontiere(borne)->getCarte1(carte);
            Partie::getInstance().getFrontiere(borne)->setCarte1(carte, nullptr);
            DecalerBorne(borne, numero);

            //on décrémente le nombre de cartes
            Partie::getInstance().getFrontiere(borne)->setnbCartes1(taille - 1);
        }
        else {
            int taille = Partie::getInstance().getFrontiere(borne)->getnbCartes2();
            carteStratege = Partie::getInstance().getFrontiere(borne)->getCarte2(carte);
            Partie::getInstance().getFrontiere(borne)->setCarte2(carte, nullptr);
            DecalerBorne(borne, numero);

            //on décrémente le nombre de cartes
            Partie::getInstance().getFrontiere(borne)->setnbCartes2(taille - 1);

        }

        //On demande au joueur si il veut la placer sur une autre Borne non revendiquée ou la défausser
        cout << "STRATEGE: Voulez vous placer la carte sur une autre borne non revendiquée ? (O/N)" << endl;
        char reponse;
        cin >> reponse;
        while (reponse != 'O' && reponse != 'N') {
            cout << "WARNING: La réponse doit être O ou N" << endl;
            cout << "STRATEGE: Retapez une réponse \n";
            cin >> reponse;
        }
        if (reponse == 'O') {
            cout << "STRATEGE: Choissisez une borne non revendiquée pour placer la carte" << endl;
            int borne2;
            cin >> borne2;
            while (borne2 < 0 || borne2 > 8 ||
                   Partie::getInstance().getFrontiere(borne2)->getProprietaire() != nullptr ||
                   borne2 == borne) { //si l'indice de la borne n'est pas correct
                cout
                        << "WARNING: L'indice de la nouvelle borne doit être compris entre 0 et 8 et la borne ne doit pas être revendiquée \n";
                cout << "STRATEGE: Retapez un indice \n";
                cin >> borne2;
            }
            //On vérifie que la borne n'est pas pleine
            int max_cartes_borne = 3;
            if (Partie::getInstance().getFrontiere(borne2)->getCombatBoue()) max_cartes_borne = 4;

            if (numero == 1 && max_cartes_borne == Partie::getInstance().getFrontiere(borne2)->getnbCartes1()) {
                cout << "STRATEGE: La borne est pleine, la carte est mise dans la défausse" << endl;
            }
            else if (numero == 2 && max_cartes_borne == Partie::getInstance().getFrontiere(borne2)->getnbCartes2()) {
                cout << "STRATEGE: La borne est pleine, la carte est mise dans la défausse" << endl;
            }
            else {
                //On place la carte sur la borne au prochain indice disponible
                if (numero == 1) {
                    //petit doute de si les parametres sont corrects
                    Partie::getInstance().getFrontiere(borne2)->ajouter_cartes1(*carteStratege);
                    return;
                }
                else {
                    Partie::getInstance().getFrontiere(borne2)->ajouter_cartes2(*carteStratege);
                    return;
                }
            }
        }
    }
        //Si c'est l'IA qui joue la carte
    else {
        srand(std::time(0));
        int borne = rand() % 9;

        while (Partie::getInstance().getFrontiere(borne)->getProprietaire() != nullptr || Partie::getInstance().getFrontiere(borne)->getnbCartes2() == 0) {
            borne = rand() % 9;
        }

        size_t max = Partie::getInstance().getFrontiere(borne)->getnbCartes2();
        int carte = rand() % max;
        while (carte > max - 1) {
            carte = rand() % max;
        }

        //On sauvegarde la carte à déplacer et on la supprime de la borne
        int taille = Partie::getInstance().getFrontiere(borne)->getnbCartes2();
        carteStratege = Partie::getInstance().getFrontiere(borne)->getCarte2(carte);
        Partie::getInstance().getFrontiere(borne)->setCarte2(carte, nullptr);
        DecalerBorne(borne, 2);

        //on décrémente le nombre de cartes
        Partie::getInstance().getFrontiere(borne)->setnbCartes2(taille - 1);

        //Choix de si on la déplace ou si on met dans la défausse
        int choix = rand() % 2; //0: déplace ; 1: dans la défausse
        if (choix == 0) {
            int borne2 = rand() % 9;
            while (Partie::getInstance().getFrontiere(borne2)->getProprietaire() != nullptr || borne2 == borne) {
                borne2 = rand() % 9;
            }
            //On vérifie que la borne n'est pas pleine
            int max_cartes_borne = 3;
            if (Partie::getInstance().getFrontiere(borne2)->getCombatBoue()) max_cartes_borne = 4;

            if (max_cartes_borne > Partie::getInstance().getFrontiere(borne2)->getnbCartes2()) {
                Partie::getInstance().getFrontiere(borne2)->ajouter_cartes2(*carteStratege);
                cout << "L'IA a joué une carte Stratege, elle a déplacé la carte " << *carteStratege << " initialement sur la borne n°" << borne << ", sur la borne n°" << borne2 << "\n";
                return;
            }
        }
        else {
            cout << "L'IA a joué une carte Stratege, elle a déplacé la carte " << *carteStratege << " initialement sur la borne n°" << borne << " dans la défausse" << "\n";
        }
    }

    //On met la carte dans la défausse
    Partie::getInstance().getDefausse()->ajouterCarte(const_cast<Carte*>(carteStratege));
    cout << "STRATEGE:La carte est mise dans la défausse" << endl;


}

void Clan::print(ostream &f) const { f << "(Clan)[" << numero << "," << couleur << "]"; }

Tactique::Tactique(NomTactique n) : nom(n), effet(nullptr) {

    switch (n) {
        case NomTactique::joker:
            effet = new JokerEffet((Elite*)this);
            break;
        case NomTactique::espion:
            effet = new EspionEffet((Elite*)this);
            break;
        case NomTactique::porte_bouclier:
            effet = new PorteBouclierEffet((Elite*)this);
            break;
        case NomTactique::colin_maillard:
            effet = new ColinMaillardEffet((Combat*)this);
            break;
        case NomTactique::combat_de_boue:
            effet = new CombatBoueEffet((Combat*)this);
            break;
        case NomTactique::chasseur_de_tete:
            effet = new ChasseurTeteEffet((Ruse*)this);
            break;
        case NomTactique::banshee:
            effet = new BansheeEffet((Ruse*)this);
            break;
        case NomTactique::traitre:
            effet = new TraitreEffet((Ruse*)this);
            break;
        case NomTactique::stratege:
            effet = new StrategeEffet((Ruse*)this);
            break;
        default:
            break;
    }
}

void Tactique::print(ostream &f) const { f << "(Tactique): " << nom; }

void Combat::print(ostream &f) const { f << "(Combat)[" << getNom() << "]"; }

void Ruse::print(ostream &f) const { f << "(Ruse)[" << getNom() << "]"; }
