#include "joueur.h"
#include <iostream>

#include "carte.h"
#include "borne.h"
#include "combinaison.h"
#include "partie.h"
#include "pioche.h"

using namespace std;


/*****************Joueur******************/

Carte* Joueur::piocher() {
	int choix_pioche = 0;
	// Si c'est une partie normale, le joueur ne peut piocher que dans la pioche clan
	if (Partie::getInstance().getMode() == Mode::normal) {
		if (Partie::getInstance().getInstance().getPiocheClan()->estVide()) {
			cout << "INFO: La pioche Clan est vide, vous ne pouvez plus rien piocher !" << endl;
			return nullptr; // à gérer
		}
		cout << "INFO: " << this->getNom() << " pioche dans la pioche Clan" << endl;
		IncNbCartesEnMain();
		return Partie::getInstance().getPiocheClan()->getCarteAPiocher();
	}

	if (this->getNom() != "IA") {
		while (choix_pioche != 1 && choix_pioche != 2) {
			std::cout << "> Dans quelle pioche souhaitez-vous piocher: 1 (Clan) 2 (Tactique)" << endl;
			cin >> choix_pioche;
		}
	}
	else {
		srand(std::time(0));
		choix_pioche = rand() % 2 + 1;
	}

	if (choix_pioche == 1) {
		if (Partie::getInstance().getPiocheClan()->estVide()) {
			cout << "INFO: La pioche Clan est vide " << this->getNom() << " doit absolument piocher une carte tactique (fait automatiquement) !" << endl;
			if (Partie::getInstance().getPiocheTactique()->estVide()) {
				cout << "INFO: La pioche Tactique est aussi vide, " << this->getNom() << " ne peut plus rien piocher !" << endl;
				return nullptr;
			}
			else {
				IncNbCartesEnMain();
				return Partie::getInstance().getPiocheTactique()->getCarteAPiocher();
			}
		}
		else {
			IncNbCartesEnMain();
			return Partie::getInstance().getPiocheClan()->getCarteAPiocher();
		}
	}

	if (choix_pioche == 2) {
		if (Partie::getInstance().getPiocheTactique()->estVide()) {
			cout << "INFO: La pioche Tactique est vide, " << this->getNom() << " doit absolument piocher une carte clan (fait automatiquement) ! " << endl;
			if (Partie::getInstance().getPiocheClan()->estVide()) {
				cout << "INFO: La pioche Clan est aussi vide, " << this->getNom() << " ne peut plus rien piocher !" << endl;
				return nullptr;
			}
			else {
				IncNbCartesEnMain();
				return Partie::getInstance().getPiocheClan()->getCarteAPiocher();
			}
		}
		else {
			IncNbCartesEnMain();
			return Partie::getInstance().getPiocheTactique()->getCarteAPiocher();
		}
	}
}

void Joueur::ajouterBorneRevendiquee(Borne* b) {
	if (b == nullptr) throw invalid_argument("La borne ne peut pas être nulle");
	bornes_revendiquees.push_back(b);
}
void Joueur::afficherCartes() {
	int i, nb_a_afficher;
	Mode mode = Partie::getInstance().getMode();
	if (mode == Mode::normal && nb_cartes_en_main < 6) DecalerCartesJoueur(this);
	else if ((mode == Mode::tactique || mode == Mode::expert) && nb_cartes_en_main < 7) DecalerCartesJoueur(this);

	cout << "\n----Cartes de: " << getNom() << "----\n" << endl;
	for (i = 0; i < nb_cartes_en_main; i++) {
		cout << *cartes[i] << "  ";
	}
	cout << endl;
}

void Joueur::setCartes(Carte* c, int i) {
	Mode mode = Partie::getInstance().getMode();
	if ((mode == Mode::normal) && (i < 0 || i > 5)) {
		throw invalid_argument("L'indice de la carte doit être compris entre 0 et 5 en mode normal");
	}
	else if ((mode == Mode::tactique || mode == Mode::expert) && (i < 0 || i > 6)) {
		throw invalid_argument("L'indice de la carte doit être compris entre 0 et 6 en mode tactique");
	}
	cartes[i] = c;
}

void Joueur::JouerCarte() {
	//MAJ du dernier joueur à avoir joué (le joueur en cours en l'ocurrence)
	Partie::getInstance().setDernierjoueur(this);

	//revendiquer la borne avant de joueur en mode expert

	if (Partie::getInstance().getMode() == Mode::expert) {
		DemanderRevendication();
	}

	Mode mode = Partie::getInstance().getMode();
	if (mode == Mode::normal && nb_cartes_en_main < 6) DecalerCartesJoueur(this);
	else if ((mode == Mode::tactique || mode == Mode::expert) && nb_cartes_en_main < 7) DecalerCartesJoueur(this);

	//Vérifier que le joueur peut jouer une carte. Sinon gérer le fait de passer son tour
	bool passer_tour = false;
	bool clan_dans_main = false;
	bool is_possible = false; // Pour gérer le fait que toutes les bornes sont pleines et que le joueur ne peut plus ajouter de carte
	int lim_to_check = 0;
	int nb_tactiques_jouees_adversaire;
	switch (numero) {
	case 1:
		//Vérification si le joueur a au moins une carte clan dans sa main
		for (int i = 0; i < nb_cartes_en_main; i++) {
			if (cartes[i]->getNom() == NomTactique::pasdenom) clan_dans_main = true;
		}

		//Vérification que toutes les bornes ne sont pas pleines du côté du joueur, auquel cas il ne peut pas jouer
		for (int i = 0; i < NB_BORNE; i++) {
			if (Partie::getInstance().getFrontiere(i)->getCombatBoue()) lim_to_check = 4;
			else lim_to_check = 3;
			if (Partie::getInstance().getFrontiere(i)->getnbCartes1() < lim_to_check) is_possible = true;
		}

		if (!is_possible) {
			cout << "\nToutes les bornes sont pleines de votre côté, vous ne pouvez plus jouer, revendiquez ! \n";
			passer_tour = true;
			break;
		}

		if (Partie::getInstance().getMode() == Mode::tactique || Partie::getInstance().getMode() == Mode::expert) {
			//Vérification si le joueur a joué plus de tactiques que son adversaire
			if (Partie::getInstance().isIA()) nb_tactiques_jouees_adversaire = Partie::getInstance().getIA()->getNb_tactiques_jouee();
			else nb_tactiques_jouees_adversaire = Partie::getInstance().getJoueur2()->getNb_tactiques_jouee();

			//S'il a joué plus de tactiques et n'a pas de carte clan dans sa main ou que toutes les bornes sont pleines, alors il ne peut pas jouer
			if (nb_tactiques_jouees > nb_tactiques_jouees_adversaire && clan_dans_main == false) {
				cout << "\nVous avez déjà joué plus d'une carte tactique de plus que votre adversaire et vous n'avez que des cartes tactiques dans votre jeu, vous ne pouvez donc pas jouer !\n";
				passer_tour = true;
			}
		}
		break;
	case 2:
		for (int i = 0; i < nb_cartes_en_main; i++) {
			if (cartes[i]->getNom() == NomTactique::pasdenom) clan_dans_main = true;
		}

		//Vérification que toutes les bornes ne sont pas pleines du côté du joueur, auquel cas il ne peut pas jouer
		for (int i = 0; i < NB_BORNE; i++) {
			if (Partie::getInstance().getFrontiere(i)->getCombatBoue()) lim_to_check = 4;
			else lim_to_check = 3;
			if (Partie::getInstance().getFrontiere(i)->getnbCartes2() < lim_to_check) is_possible = true;
		}

		if (!is_possible) {
			cout << "\nToutes les bornes sont pleines de votre côté, vous ne pouvez plus jouer, revendiquez ! \n";
			passer_tour = true;
			break;
		}

		if (Partie::getInstance().getMode() == Mode::tactique || Partie::getInstance().getMode() == Mode::expert) {
			//Vérification si le joueur a joué plus de tactiques que son adversaire
			nb_tactiques_jouees_adversaire = Partie::getInstance().getJoueur1()->getNb_tactiques_jouee();

			//S'il a joué plus de tactiques et n'a pas de carte clan dans sa main ou que toutes les bornes sont pleines, alors il ne peut pas jouer
			if ((nb_tactiques_jouees > nb_tactiques_jouees_adversaire) && (clan_dans_main == false)) {
				cout << "\nVous avez déjà joué plus d'une carte tactique de plus que votre adversaire et vous n'avez que des cartes tactiques dans votre jeu, vous ne pouvez donc pas jouer !\n";
				passer_tour = true;
			}
		}

		break;
	default:
		break;
	}

	//choisir la carte a jouer

	bool CarteValide = false;
	size_t indiceCarte;
	//choix de la carte à jouer

	if (!passer_tour) {
		do {
			//affichage des cartes du joueur
			afficherCartes();
			cout << "Choisissez l'indice de la carte que vous voulez jouer : \n";
			cin >> indiceCarte;
			while (indiceCarte < 0 || indiceCarte > nb_cartes_en_main - 1) { //si l'indice de la carte n'est pas correct
				cout << "L'indice de la carte doit être compris entre 0 et " << nb_cartes_en_main - 1 << endl;
				cout << "Retapez un indice \n";
				cin >> indiceCarte;
			}

			//si on est en mode tactique on vérifie que ce n'est pas une carte tactique de plus que l'adversaire
			if (Partie::getInstance().getMode() == Mode::tactique || Partie::getInstance().getMode() == Mode::expert) {
				if (cartes[indiceCarte]->getNom() != NomTactique::pasdenom) { //si c'est une carte tactique
					if (numero == 1) {
						if (Partie::getInstance().getIA() == nullptr) {
							if (Partie::getInstance().getJoueur1()->getNb_tactiques_jouee() <= Partie::getInstance().getJoueur2()->getNb_tactiques_jouee()) {
								CarteValide = true;
							}
							else {
								cout << "Vous ne pouvez pas jouer plus d'une carte tactique de plus que votre adversaire \n";
								cout << "Rechoisissez une carte\n";
								CarteValide = false;

							}
						}
						else {
							if (Partie::getInstance().getJoueur1()->getNb_tactiques_jouee() <= Partie::getInstance().getIA()->getNb_tactiques_jouee()) {
								CarteValide = true;
							}
							else {
								cout << "Vous ne pouvez pas jouer plus d'une carte tactique de plus que votre adversaire \n";
								cout << "Rechoisissez une carte\n";
								CarteValide = false;

							}
						}
					}
					else { //joueur 2
						if (Partie::getInstance().getJoueur2()->getNb_tactiques_jouee() <= Partie::getInstance().getJoueur1()->getNb_tactiques_jouee()) {
							CarteValide = true;
						}
						else {
							cout << "Vous ne pouvez pas jouer plus d'une carte tactique de plus que votre adversaire \n";
							cout << "Rechoisissez une carte\n";
							CarteValide = false;

						}
					}
					if (getJokerJoue() && cartes[indiceCarte]->getNom() == NomTactique::joker) {
						cout << "Vous avez déjà joué un joker!" << endl;
						cout << "Rechoisissez une carte\n";
						CarteValide = false;
					}
				}
				else { //si c'est une carte clan
					CarteValide = true;
				}

			}
			else { //mode normal
				CarteValide = true;
			}

		} while (!CarteValide);

		auto valid_card_name = cartes[indiceCarte]->getNom();
		Carte* ruse_to_defausse = nullptr;

		bool is_joker = false; //vrai si carte joker
		if (valid_card_name == NomTactique::joker) {
			is_joker = true;
		}

		bool trigger_inc_tactique = false; //vrai si la tactique a déjà impliqué l'incrémentation du nombre de tactiques jouées

		bool is_clan = false; //vrai si carte clan
		if (valid_card_name == NomTactique::pasdenom) {
			is_clan = true;
		}

		bool trigger_rtd = false; //trigger pour savoir si on doit défausser la carte ruse à la fin
		//Si c'est une carte Ruse (à part chasseurdetete qui est gérée directement dans l'effet pour des raisons spéciales, on la sauvegarde pour la défausser à la fin
		if (valid_card_name == NomTactique::stratege || valid_card_name == NomTactique::banshee || valid_card_name == NomTactique::traitre) {
			ruse_to_defausse = cartes[indiceCarte];
			trigger_rtd = true;
		}

		bool is_combat = false; //vrai si carte combat
		if (valid_card_name == NomTactique::colin_maillard || valid_card_name == NomTactique::combat_de_boue) {
			is_combat = true;
		}
		bool is_cdt = false; //vrai si carte chasseur de tete
		// si carte chasseur de tete, on applique juste l'effet, le reste est géré dans l'effet
		if (valid_card_name == NomTactique::chasseur_de_tete) {
			is_cdt = true;
			cartes[indiceCarte]->executerEffet();
		}

		if (!trigger_rtd && !is_combat) { //on se sert de trigger_rtd pour appliquer les effets des ruses sans demander une borne sur laquelle jouer, idem pour les cartes combat
			if (!is_cdt) {//cartes qui se jouent directement ou indirectement sur une borne, ne concerne pas chasseur de tete
				size_t indiceBorne; //choix de la borne sur laquelle jouer
				cout << "Choisissez l'indice de la borne sur laquelle vous voulez jouer la carte : \n";
				cin >> indiceBorne;

				int max_cartes_borne = 3;
				if (Partie::getInstance().getFrontiere(indiceBorne)->getCombatBoue()) max_cartes_borne = 4;

				while (indiceBorne < 0 || indiceBorne > 8 ||
					(numero == 1 && Partie::getInstance().getFrontiere(indiceBorne)->getnbCartes1() >= max_cartes_borne) ||
					(numero == 2 && Partie::getInstance().getFrontiere(indiceBorne)->getnbCartes2() >= max_cartes_borne)) {

					cout << "L'indice de la borne doit être compris entre 0 et 8 et la borne ne doit pas être pleine de votre côté \n";
					cout << "Retapez un indice \n";
					cin >> indiceBorne;
				}

				if (numero == 1) { //si c'est le joueur 1 qui joue

					//SI ON EST EN MODE NORMAL
					if (Partie::getInstance().getMode() == Mode::normal) {
						Partie::getInstance().getFrontiere(indiceBorne)->ajouter_cartes1(*cartes[indiceCarte]); //alors on ajoute la carte du bon côté de la borne
					}

					//SI ON EST EN MODE TACTIQUE ET QU'ON JOUE UNE TACTIQUE
					else if (Partie::getInstance().getMode() == Mode::tactique || Partie::getInstance().getMode() == Mode::expert) {

						//ON TRAITE LE CAS OU IL S'AGIT DE CARTES TACTIQUES QUI SE POSENT SUR LES BORNES
						//A SAVOIR JOKER, PORTE_BOUCLIER ET ESPION
						//L'EFFET DE CES 3 CARTES EST A APPELER AU MOMENT DE LA REVENDICATION
						//ON GERE AUSSI LE CAS DE SI ON POSE UNE CARTE CLAN QUI SE GERE PAREIL

						if (cartes[indiceCarte]->getNom() == NomTactique::joker ||
							cartes[indiceCarte]->getNom() == NomTactique::espion ||
							cartes[indiceCarte]->getNom() == NomTactique::porte_bouclier ||
							cartes[indiceCarte]->getNom() == NomTactique::pasdenom) {
							Partie::getInstance().getFrontiere(indiceBorne)->ajouter_cartes1(*cartes[indiceCarte]);
							if (cartes[indiceCarte]->getNom() != NomTactique::pasdenom) {
								this->setPlusNb_tactiques_jouee(); //on incrémente le nombre de cartes tactiques jouées du joueur
								trigger_inc_tactique = true;
							}
						}
					}
					Partie::getInstance().getJoueur1()->DecNbCartesEnMain();
				}
				else if (numero == 2) { //si c'est le joueur 2 qui joue

					//SI ON EST EN MODE NORMAL
					if (Partie::getInstance().getMode() == Mode::normal) {
						Partie::getInstance().getFrontiere(indiceBorne)->ajouter_cartes2(*cartes[indiceCarte]);
					}
					//SI ON EST EN MODE TACTIQUE ET QU'ON JOUE UNE TACTIQUE
					else if (Partie::getInstance().getMode() == Mode::tactique || Partie::getInstance().getMode() == Mode::expert) {

						//ON TRAITE LE CAS OU IL S'AGIT DE CARTES TACTIQUES QUI SE POSENT SUR LES BORNES
						//A SAVOIR JOKER, PORTE_BOUCLIER ET ESPION
						//L'EFFET DE CES 3 CARTES EST A APPELER AU MOMENT DE LA REVENDICATION
						//ON GERE AUSSI LE CAS DE SI ON POSE UNE CARTE CLAN QUI SE GERE PAREIL

						if (cartes[indiceCarte]->getNom() == NomTactique::joker ||
							cartes[indiceCarte]->getNom() == NomTactique::espion ||
							cartes[indiceCarte]->getNom() == NomTactique::porte_bouclier ||
							cartes[indiceCarte]->getNom() == NomTactique::pasdenom) {
							Partie::getInstance().getFrontiere(indiceBorne)->ajouter_cartes2(*cartes[indiceCarte]);
							if (cartes[indiceCarte]->getNom() != NomTactique::pasdenom) {
								this->setPlusNb_tactiques_jouee(); //on incrémente le nombre de cartes tactiques jouées du joueur
								trigger_inc_tactique = true;
							}
						}
					}
					Partie::getInstance().getJoueur2()->DecNbCartesEnMain();

				}
			}
		}
		else {//stratege ou banshee ou chasseur de tete ou colin maillard ou combat de boue
			cartes[indiceCarte]->executerEffet();
			if (!is_cdt) Partie::getInstance().getDernierjoueur()->DecNbCartesEnMain(); //car on veut faire 3 fois la décrémentation dans l'effet de cdt directement
		}

		//POUR NE PAS ENLEVER LA CARTE CHASSEUR DE TETE DEUX FOIS
		//Si c'est une carte Ruse (à part chasseurdetete qui est gérée directement dans l'effet pour des raisons spéciales, on la sauvegarde pour la défausser à la fin
		if (trigger_rtd) {
			Partie::getInstance().getDefausse()->ajouterCarte(ruse_to_defausse);
		}

		if (!is_cdt) {
			//Le joueur a joué sa carte et a géré le cas de la revendication, il ne faut pas oublier de piocher !
			this->setCartes(nullptr, indiceCarte);
			this->setCartes(this->piocher(), indiceCarte);
		}

		//gestion incrémentation des tactiques (uniquement) qui n'ont pas déjà été incrémentées autre que joker porte bouclier et espion
		if (!trigger_inc_tactique && !is_clan) {
			this->setPlusNb_tactiques_jouee();
		}

		//gestion joker joueur
		if (is_joker) {
			this->setJokerJoue(true);
		}
	}

	if (Partie::getInstance().getMode() != Mode::expert) DemanderRevendication();

}

void Joueur::DemanderRevendication() {

	int reponse;
	cout << "\nVoulez vous revendiquer une borne ? Tapez 1 pour oui et 2 pour non\n";
	cin >> reponse;
	while (reponse < 1 || reponse > 2) { //si la réponse n'est pas 1 ou 2
		cout << "Votre réponse doit être 1 (pour oui) ou (2 pour non).\n";
		cout << "Retapez une réponse.\n";
		cin >> reponse;
	}
	if (reponse == 1) {
		int indiceBorneRevendique;
		cout << "Sur quelle borne voulez vous revendiquer ?\n";
		cin >> indiceBorneRevendique;
		while (indiceBorneRevendique < 0 || indiceBorneRevendique > 8 || Partie::getInstance().getFrontiere(indiceBorneRevendique)->getProprietaire() != nullptr) { //si l'indice de la borne n'est pas compris entre 1 et 8 et que la borne est déjà revendiquée
			cout << "L'indice de la borne doit être compris entre 0 et 8 et la borne ne doit pas déjà être revendiquée. \n";
			cout << "Retapez un indice de borne.\n";
			cin >> indiceBorneRevendique;
		}

		//SI LE JOUEUR VEUT REVENDIQUER IL FAUT INITIALISER LES CARTES TACTIQUES DES DEUX COTES DE LA BORNE
		int i;
		int nb_cartes_j1 = Partie::getInstance().getFrontiere(indiceBorneRevendique)->getnbCartes1();
		int nb_cartes_j2 = Partie::getInstance().getFrontiere(indiceBorneRevendique)->getnbCartes2();
		switch (this->getNumero()) {
		case 1:
			for (i = 0; i < nb_cartes_j1; i++) {
				if (Partie::getInstance().getFrontiere(indiceBorneRevendique)->getCarte1(i)->getNom() == NomTactique::joker ||
					Partie::getInstance().getFrontiere(indiceBorneRevendique)->getCarte1(i)->getNom() == NomTactique::espion ||
					Partie::getInstance().getFrontiere(indiceBorneRevendique)->getCarte1(i)->getNom() == NomTactique::porte_bouclier) {

					Carte* c = const_cast<Carte*>(Partie::getInstance().getFrontiere(indiceBorneRevendique)->getCarte1(i));
					c->executerEffet();
				}
			}
			for (i = 0; i < nb_cartes_j2; i++) {
				if (Partie::getInstance().getFrontiere(indiceBorneRevendique)->getCarte2(i)->getNom() == NomTactique::joker ||
					Partie::getInstance().getFrontiere(indiceBorneRevendique)->getCarte2(i)->getNom() == NomTactique::espion ||
					Partie::getInstance().getFrontiere(indiceBorneRevendique)->getCarte2(i)->getNom() == NomTactique::porte_bouclier) {

					cout << "\n" << this->getNom() << " souhaite revendiquer la borne mais l'adversaire a sa carte "
						<< Partie::getInstance().getFrontiere(indiceBorneRevendique)->getCarte2(i)->getNom()
						<< " à initialiser ! \n";
					Carte* c = const_cast<Carte*>(Partie::getInstance().getFrontiere(indiceBorneRevendique)->getCarte2(i));
					if (Partie::getInstance().isIA() == true) {
						Partie::getInstance().setDernierjoueur(Partie::getInstance().getIA());
						c->executerEffet();
						Partie::getInstance().setDernierjoueur(this);
					}
					else c->executerEffet();
				}
			}
			break;
		case 2:
			for (i = 0; i < nb_cartes_j2; i++) {
				if (Partie::getInstance().getFrontiere(indiceBorneRevendique)->getCarte2(i)->getNom() == NomTactique::joker ||
					Partie::getInstance().getFrontiere(indiceBorneRevendique)->getCarte2(i)->getNom() == NomTactique::espion ||
					Partie::getInstance().getFrontiere(indiceBorneRevendique)->getCarte2(i)->getNom() == NomTactique::porte_bouclier) {

					Carte* c = const_cast<Carte*>(Partie::getInstance().getFrontiere(indiceBorneRevendique)->getCarte2(i));
					c->executerEffet();
				}
			}
			for (i = 0; i < nb_cartes_j1; i++) {
				if (Partie::getInstance().getFrontiere(indiceBorneRevendique)->getCarte1(i)->getNom() == NomTactique::joker ||
					Partie::getInstance().getFrontiere(indiceBorneRevendique)->getCarte1(i)->getNom() == NomTactique::espion ||
					Partie::getInstance().getFrontiere(indiceBorneRevendique)->getCarte1(i)->getNom() == NomTactique::porte_bouclier) {

					cout << "\n" << this->getNom() << " souhaite revendiquer la borne mais " << Partie::getInstance().getJoueur1()->getNom()
						<< " a sa carte " << Partie::getInstance().getFrontiere(indiceBorneRevendique)->getCarte1(i)->getNom()
						<< " à initialiser ! \n";
					Carte* c = const_cast<Carte*>(Partie::getInstance().getFrontiere(indiceBorneRevendique)->getCarte1(i));
					c->executerEffet();
				}
			}
			break;
		default:
			break;
		}

		//Si la revendication n'est pas valide, on réinitialise les cartes tactiques
		if (!Partie::getInstance().getFrontiere(indiceBorneRevendique)->verifRevendication(this)) {
			for (i = 0; i < nb_cartes_j1; i++) {
				Carte* c = const_cast<Carte*>(Partie::getInstance().getFrontiere(indiceBorneRevendique)->getCarte1(i));
				if (c->getNom() == NomTactique::joker || c->getNom() == NomTactique::porte_bouclier) {
					Elite* c_bis = (Elite*)c;
					c_bis->setCouleur(Couleur::pasdecouleur);
					c_bis->setNumero(Numero::pasdenumero);
				}
				if (c->getNom() == NomTactique::espion) {
					Elite* c_bis = (Elite*)c;
					c_bis->setCouleur(Couleur::pasdecouleur);
				}

			}
			for (i = 0; i < nb_cartes_j2; i++) {
				Carte* c = const_cast<Carte*>(Partie::getInstance().getFrontiere(indiceBorneRevendique)->getCarte2(i));
				if (c->getNom() == NomTactique::joker || c->getNom() == NomTactique::porte_bouclier) {
					Elite* c_bis = (Elite*)c;
					c_bis->setCouleur(Couleur::pasdecouleur);
					c_bis->setNumero(Numero::pasdenumero);
				}
				if (c->getNom() == NomTactique::espion) {
					Elite* c_bis = (Elite*)c;
					c_bis->setCouleur(Couleur::pasdecouleur);
				}

			}
		}
	}
	else {
		cout << "Pas de revendication \n";
	}

}

string Joueur::ChoisirNom() {
	cout << "\n";
	cout << "-------------------------------\n";
	cout << "Entrez le nom du joueur : \n";
	cout << "-------------------------------\n";
	string choixNom;
	cin >> choixNom;
	while (choixNom == "IA") {
		cout << "Désolé, le nom IA ne peut pas être utilisé.\n";
		cout << "Saisissez un autre nom: ";
		cin >> choixNom;
	}
	return choixNom;
}

void Joueur::setNumero(int num) {
	if (numero != 1 && numero != 2) {
		throw invalid_argument("Le numéro du joueur doit être 1 ou 2");
	}
	else {
		numero = num;
	}
}

void Joueur::setNom(string n) {
	if (n == "") {
		throw invalid_argument("Le nom du joueur ne peut pas être vide");
	}
	else
		nom = n;
}

[[maybe_unused]] void Joueur::setNb_tactiques_jouee(int nb) { //utile pour remettre à 0 à la fin de la manche mais pas pour incrémenter
	if (nb < 0) {
		throw invalid_argument("Le nombre de tactiques jouées ne peut pas être négatif");
	}
	else
		nb_tactiques_jouees = nb;
}

void Joueur::setScoreManche(int score) {
	if (score < 0) {
		throw invalid_argument("Le score de la manche ne peut pas être négatif");
	}
	else
		scoreManche = score;
}

void Joueur::setScorePartie(int score) {
	if (score < 0) {
		throw invalid_argument("Le score de la partie ne peut pas être négatif");
	}
	else
		scorePartie = score;
}

Carte* Joueur::getCartes(int i) const {
	if ((Partie::getInstance().getMode() == Mode::normal) && (i < 0 || i > 5)) {
		throw invalid_argument("L'indice de la carte doit être compris entre 0 et 5 en mode normal");
	}
	else if ((Partie::getInstance().getMode() == Mode::tactique || Partie::getInstance().getMode() == Mode::expert) && (i < 0 || i > 6)) {
		throw invalid_argument("L'indice de la carte doit être compris entre 0 et 6 en mode tactique");
	}
	else
		return cartes[i];
}

Joueur::Joueur() : numero(0), nom(ChoisirNom()), nb_tactiques_jouees(0), scoreManche(0), scorePartie(0), joker_joue(false), nb_cartes_en_main(0) {
	for (int i = 0; i < 7; i++) {
		cartes[i] = nullptr;
	}
}

void Joueur::AfficherBornesRevendiquees() {
	cout << "\n";
	cout << "Les bornes revendiquées par le joueur " << getNumero() << " sont :";
	for (int i = 0; i < bornes_revendiquees.size(); i++) {
		cout << bornes_revendiquees[i]->getNumero();
	}
	cout << "\n";
}

void Joueur::afficherAideCombi() const {

	//Création de l'aide comme elle est présentée dans le jeu

	cout << "\n-----AIDE DE JEU: (de la combinaison la plus forte à la plus faible)------\n" << endl;

	cout << "[Suite Couleur]: [3,Bleu] [4,Bleu] [5,Bleu]\n" << endl;
	cout << "[Brelan]: [6,Vert] [6,Bleu] [6,Rouge]\n" << endl;
	cout << "[Couleur]: [1,Violet] [3,Violet] [6,Violet]\n" << endl;
	cout << "[Suite]: [2,Beige] [3,Vert] [4,Violet]\n" << endl;
	cout << "[Somme]: [3,Beige] [7,Bleu] [9,Violet]\n" << endl;
}

void Joueur::Clear() {
	nb_tactiques_jouees = 0;
	joker_joue = false;
	for (int i = 0; i < 7; i++) {
		cartes[i] = nullptr;
	}
}

ostream& operator<<(ostream& f, const Joueur& j) {
	f << "\n\nJoueur n°" << j.getNumero() << "\nNom : " << j.getNom()
		<< "\nScore partie : " << j.getScoreManche() << "\nScore manche : " << j.getScoreManche()
		<< "\nNombre de tactiques jouées sur la manche : " << j.getNb_tactiques_jouee();

	f << "\nMain du joueur:\n";
	for (int i = 0; i < 7; i++) {
		f << "\n" << j.getCartes(i);
	}
	return f;
}


void IA::JouerCarte() {
	//IA qui prend des décisions aléatoires pour tout
	srand(std::time(0));

	//MAJ du dernier joueur à avoir joué (le joueur en cours en l'ocurrence)
	Partie::getInstance().setDernierjoueur(this);

	//revendiquer la borne avant de joueur en mode expert

	if (Partie::getInstance().getMode() == Mode::expert) {
		DemanderRevendication();
	}

	Mode mode = Partie::getInstance().getMode();
	if (mode == Mode::normal && getNbCartesEnMain() < 6) DecalerCartesJoueur(this);
	else if ((mode == Mode::tactique || mode == Mode::expert) && getNbCartesEnMain() < 7) DecalerCartesJoueur(this);

	bool CarteValide = false;
	size_t indiceCarte;

	cout << "\n----L'IA joue----\n";

	//Vérification que toutes les bornes ne sont pas pleines du côté de l'IA, auquel cas elle ne peut pas jouer de carte
	int lim_to_check = 0;
	bool is_possible = false;
	bool passer_tour = false;
	for (int i = 0; i < NB_BORNE; i++) {
		if (Partie::getInstance().getFrontiere(i)->getCombatBoue()) lim_to_check = 4;
		else lim_to_check = 3;
		if (Partie::getInstance().getFrontiere(i)->getnbCartes2() < lim_to_check) is_possible = true;
	}

	bool clan_dans_main = false;
	for (int i = 0; i < getNbCartesEnMain(); i++) {
		if (getCartes(i)->getNom() == NomTactique::pasdenom) clan_dans_main = true;
	}

	int nb_tactiques_jouees_adversaire = 0;
	if (Partie::getInstance().getMode() == Mode::tactique || Partie::getInstance().getMode() == Mode::expert) {
		//Vérification si le joueur a joué plus de tactiques que son adversaire
		nb_tactiques_jouees_adversaire = Partie::getInstance().getJoueur1()->getNb_tactiques_jouee();

		//S'il a joué plus de tactiques et n'a pas de carte clan dans sa main ou que toutes les bornes sont pleines, alors il ne peut pas jouer
		if ((getNb_tactiques_jouee() > nb_tactiques_jouees_adversaire) && (clan_dans_main == false)) {
			is_possible = false;
		}
	}


	if (is_possible) {
		//choix de la carte à jouer
		do {

			indiceCarte = rand() % this->getNbCartesEnMain();

			//si on est en mode tactique on vérifie que ce n'est pas une carte tactique de plus que l'adversaire
			if (Partie::getInstance().getMode() == Mode::tactique || Partie::getInstance().getMode() == Mode::expert) {
				if (getCartes(indiceCarte)->getNom() != NomTactique::pasdenom) { //si c'est une carte tactique

					if (Partie::getInstance().getIA()->getNb_tactiques_jouee() <= Partie::getInstance().getJoueur1()->getNb_tactiques_jouee()) {
						CarteValide = true;
					}
					else {
						CarteValide = false;
					}
				}
				else { //si c'est une carte clan
					CarteValide = true;
				}

			}
			else { //mode normal
				CarteValide = true;
			}

		} while (!CarteValide);

		bool is_cdt = false; //vrai si carte chasseur de tete

		// si carte chasseur de tete, on applique juste l'effet, le reste est géré dans l'effet
		if (getCartes(indiceCarte)->getNom() == NomTactique::chasseur_de_tete) {
			is_cdt = true;
			getCartes(indiceCarte)->executerEffet();
			this->setPlusNb_tactiques_jouee();
		}

		//cartes qui se jouent directement ou indirectement sur une borne, ne concerne pas chasseur de tete
		if (!is_cdt) {
			size_t indiceBorne = rand() % 9; //choix de la borne sur laquelle jouer
			int max_cartes_borne = 3;
			if (Partie::getInstance().getFrontiere(indiceBorne)->getCombatBoue()) max_cartes_borne = 4;

			while (Partie::getInstance().getFrontiere(indiceBorne)->getnbCartes2() >= max_cartes_borne) {
				indiceBorne = rand() % 9;
			}

			//SI ON EST EN MODE NORMAL
			if (Partie::getInstance().getMode() == Mode::normal) {
				Partie::getInstance().getFrontiere(indiceBorne)->ajouter_cartes2(*getCartes(indiceCarte));
				cout << "L'IA a joué la carte " << *getCartes(indiceCarte) << " sur la borne n°" << indiceBorne << "\n\n";
			}
			//SI ON EST EN MODE TACTIQUE ET QU'ON JOUE UNE TACTIQUE
			else if (Partie::getInstance().getMode() == Mode::tactique || Partie::getInstance().getMode() == Mode::expert) {

				//ON TRAITE LE CAS OU IL S'AGIT DE CARTES TACTIQUES QUI SE POSENT SUR LES BORNES
				//A SAVOIR JOKER, PORTE_BOUCLIER ET ESPION
				//L'EFFET DE CES 3 CARTES EST A APPELER AU MOMENT DE LA REVENDICATION
				//ON GERE AUSSI LE CAS DE SI ON POSE UNE CARTE CLAN QUI SE GERE PAREIL

				if (getCartes(indiceCarte)->getNom() == NomTactique::joker ||
					getCartes(indiceCarte)->getNom() == NomTactique::espion ||
					getCartes(indiceCarte)->getNom() == NomTactique::porte_bouclier ||
					getCartes(indiceCarte)->getNom() == NomTactique::pasdenom) {
					Partie::getInstance().getFrontiere(indiceBorne)->ajouter_cartes2(*getCartes(indiceCarte));
					if (getCartes(indiceCarte)->getNom() != NomTactique::pasdenom) {
						this->setPlusNb_tactiques_jouee(); //on incrémente le nombre de cartes tactiques jouées du joueur
					}
					cout << "L'IA a joué la carte " << *getCartes(indiceCarte) << " sur la borne n°" << indiceBorne << "\n\n";
				}
				//SI CE N'EST NI UN JOKER NI UN ESPION NI UN PORTE BOUCLIER ET PAS UNE CARTE CLAN
				else {
					getCartes(indiceCarte)->executerEffet();
					this->setPlusNb_tactiques_jouee();
				}
			}

			Partie::getInstance().getIA()->DecNbCartesEnMain();

			//POUR NE PAS ENLEVER LA CARTE CHASSEUR DE TETE DEUX FOIS

			//Le joueur a joué sa carte et a géré le cas de la revendication, il ne faut pas oublier de piocher !
			this->setCartes(nullptr, indiceCarte);
			this->setCartes(this->piocher(), indiceCarte);
		}
	}

	if (Partie::getInstance().getMode() != Mode::expert) DemanderRevendication();


}

void IA::DemanderRevendication() {
	int reponse = rand() % 2 + 1;

	if (reponse == 1) {
		int indiceBorneRevendique = rand() % 9;
		while (indiceBorneRevendique < 0 || indiceBorneRevendique > 8 || Partie::getInstance().getFrontiere(indiceBorneRevendique)->getProprietaire() != nullptr) { //si l'indice de la borne n'est pas compris entre 1 et 8 et que la borne est déjà revendiquée
			indiceBorneRevendique = rand() % 9;
		}
		cout << "L'IA tente de revendiquer la borne " << indiceBorneRevendique << "\n\n";

		//SI L'IA VEUT REVENDIQUER IL FAUT INITIALISER LES CARTES TACTIQUES DES DEUX COTES DE LA BORNE

		int i;
		int nb_cartes_j1 = Partie::getInstance().getFrontiere(indiceBorneRevendique)->getnbCartes1();
		int nb_cartes_j2 = Partie::getInstance().getFrontiere(indiceBorneRevendique)->getnbCartes2();

		for (i = 0; i < nb_cartes_j2; i++) {
			if (Partie::getInstance().getFrontiere(indiceBorneRevendique)->getCarte2(i)->getNom() == NomTactique::joker ||
				Partie::getInstance().getFrontiere(indiceBorneRevendique)->getCarte2(i)->getNom() == NomTactique::espion ||
				Partie::getInstance().getFrontiere(indiceBorneRevendique)->getCarte2(i)->getNom() == NomTactique::porte_bouclier) {

				Carte* c = const_cast<Carte*>(Partie::getInstance().getFrontiere(indiceBorneRevendique)->getCarte2(i));
				c->executerEffet();
			}
		}
		for (i = 0; i < nb_cartes_j1; i++) {
			if (Partie::getInstance().getFrontiere(indiceBorneRevendique)->getCarte1(i)->getNom() == NomTactique::joker ||
				Partie::getInstance().getFrontiere(indiceBorneRevendique)->getCarte1(i)->getNom() == NomTactique::espion ||
				Partie::getInstance().getFrontiere(indiceBorneRevendique)->getCarte1(i)->getNom() == NomTactique::porte_bouclier) {

				cout << "\n" << this->getNom() << " souhaite revendiquer la borne mais l'adversaire"
					<< " a sa carte " << Partie::getInstance().getFrontiere(indiceBorneRevendique)->getCarte1(i)->getNom()
					<< " à initialiser ! \n";
				Carte* c = const_cast<Carte*>(Partie::getInstance().getFrontiere(indiceBorneRevendique)->getCarte1(i));
				Partie::getInstance().setDernierjoueur(Partie::getInstance().getJoueur1());
				c->executerEffet();
				Partie::getInstance().setDernierjoueur(this);
			}
		}



		//Si la revendication n'est pas valide, on réinitialise les cartes tactiques
		if (!Partie::getInstance().getFrontiere(indiceBorneRevendique)->verifRevendication(this)) {
			for (i = 0; i < nb_cartes_j1; i++) {
				Carte* c = const_cast<Carte*>(Partie::getInstance().getFrontiere(indiceBorneRevendique)->getCarte1(i));
				if (c->getNom() == NomTactique::joker || c->getNom() == NomTactique::porte_bouclier) {
					Elite* c_bis = (Elite*)c;
					c_bis->setCouleur(Couleur::pasdecouleur);
					c_bis->setNumero(Numero::pasdenumero);
				}
				if (c->getNom() == NomTactique::espion) {
					Elite* c_bis = (Elite*)c;
					c_bis->setCouleur(Couleur::pasdecouleur);
				}

			}
			for (i = 0; i < nb_cartes_j2; i++) {
				Carte* c = const_cast<Carte*>(Partie::getInstance().getFrontiere(indiceBorneRevendique)->getCarte2(i));
				if (c->getNom() == NomTactique::joker || c->getNom() == NomTactique::porte_bouclier) {
					Elite* c_bis = (Elite*)c;
					c_bis->setCouleur(Couleur::pasdecouleur);
					c_bis->setNumero(Numero::pasdenumero);
				}
				if (c->getNom() == NomTactique::espion) {
					Elite* c_bis = (Elite*)c;
					c_bis->setCouleur(Couleur::pasdecouleur);
				}

			}
		}
	}
	else {
		cout << "L'IA ne souhaite pas revendiquer\n\n";
	}
}



void DecalerCartesJoueur(Joueur* j) {
	int taille = j->getNbCartesEnMain() + 1;
	int indexDestination = 0;
	for (int indexSource = 0; indexSource < taille; ++indexSource) {
		if (j->getCartes(indexSource) != nullptr) {
			j->setCartes(j->getCartes(indexSource), indexDestination);
			++indexDestination;
		}
	}
	// Remplissage des éléments restants avec des nullptr
	for (; indexDestination < taille; ++indexDestination) {
		j->setCartes(nullptr, indexDestination);
	}

}