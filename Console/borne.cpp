bool Borne::verifRevendication(Joueur* j) {
    if (isCombatBoue) { //si la carte combat de boue est jouée sur la borne
        if (nbCartes1 == 4 && nbCartes2 == 4) { //si on a bien 4 cartes de chaque côté

            auto c1 = Combinaison(*cartes1[0], *cartes1[1], *cartes1[2], *cartes1[3]); //on construit une combinaison avec les cartes de chaque côté de la borne
            auto c2 = Combinaison(*cartes2[0], *cartes2[1], *cartes2[2], *cartes2[3]);

            if (isColinMaillard) { //si la carte Colin Maillard est jouée sur la borne

                if (c1.getSommeCartes() > c2.getSommeCartes() && j->getNumero() == 1) { //si la somme des cartes du joueur 1 est supérieure
                    proprietaire = j;
                    cout << "\nRevendication valide, le joueur 1 (" << j->getNom() << ") gagne la borne ! \n";
                }

                else if (c1.getSommeCartes() < c2.getSommeCartes() && j->getNumero() == 2) { //si la somme des cartes du joueur 2 est supérieure
                    proprietaire = j;
                    cout << "\nRevendication valide, le joueur 2 (" << j->getNom() << ") gagne la borne ! \n";
                }

                else if (c1.getSommeCartes() == c2.getSommeCartes() && j->getNumero() == 1 && j == premierAposer) {
                    proprietaire = j;
                    cout << "\nRevendication valide, le joueur 1(" << j->getNom() << ") est le premier a avoir pose sa troisieme carte \n";
                }
                else if (c1.getSommeCartes() == c2.getSommeCartes() && j->getNumero() == 2 && j == premierAposer) {
                    proprietaire = j;
                    cout << "\nRevendication valide, le joueur 2 (" << j->getNom() << ") est le premier a avoir pose sa troisieme carte \n";
                }
                else {
                    cout << "\nRevendication non valide, la somme de 3 cartes n'est pas meilleure que celle de l'autre joueur \n";
                    return false;
                }

            }
            else { //si la carte Colin Maillard n'est pas jouée

                if (c1.getValeur() > c2.getValeur() && j->getNumero() == 1) { //si la valeur des cartes du joueur 1 est supérieure
                    proprietaire = j;
                    cout << "\nRevendication valide, le joueur 1(" << j->getNom() << ") gagne la borne ! \n";
                }

                else if (c1.getValeur() < c2.getValeur() && j->getNumero() == 2) { //si la valeur des cartes du joueur 2 est supérieure
                    proprietaire = j;
                    cout << "\nRevendication valide, le joueur 2 (" << j->getNom() << ") gagne la borne ! \n";
                }

                else if (c1.getValeur() == c2.getValeur() && j->getNumero() == 1 && j == premierAposer) {
                    proprietaire = j;
                    cout << "\nRevendication valide, le joueur 1 (" << j->getNom() << ") est le premier a avoir pose sa quatrieme carte \n";
                }
                else if (c1.getValeur() == c2.getValeur() && j->getNumero() == 2 && j == premierAposer) {
                    proprietaire = j;
                    cout << "\nRevendication valide, le joueur 2 (" << j->getNom() << ") est le premier a avoir pose sa quatrieme carte \n";
                }

                else {
                    cout << "\nRevendication non valide, la combinaison de 3 cartes n'est pas meilleure que celle de l'autre joueur \n";
                    return false;
                }

            }
            //Récap de la revendication
            cout << "\nRécap revendication: \n\n";
            if (j->getNumero() == 1) {
                cout << j->getNom() << " gagne avec la revendication suivante: " << c1.getNom() << " dont la somme des cartes valait " << c1.getSommeCartes() << "\n";
                cout << "L'adversaire avait la combinaison suivante: " << c2.getNom() << " dont la somme des vartes valait " << c2.getSommeCartes() << "\n\n";
            }
            else {
                cout << j->getNom() << " gagne avec la revendication suivante: " << c2.getNom() << " dont la somme des cartes valait " << c2.getSommeCartes() << "\n";
                cout << "L'adversaire avait la combinaison suivante: " << c1.getNom() << " dont la somme des vartes valait " << c1.getSommeCartes() << "\n\n";
            }
        }
        else { //revendication non valide car il n'y a pas 4 cartes de chaque côté
            cout << "Revendication invalide, il n'y a pas 4 cartes de chaque côté \n";
            return false;

        }
    }

    else { // si la carte combat de boue n'est pas posée
        if (nbCartes1 == 3 && nbCartes2 == 3) {

            auto c1 = Combinaison(*cartes1[0], *cartes1[1], *cartes1[2]); //on construit une combinaison avec les cartes de chaque côté de la borne
            auto c2 = Combinaison(*cartes2[0], *cartes2[1], *cartes2[2]);

            if (isColinMaillard) { //si la carte Colin Maillard est jouée sur la borne

                if (c1.getSommeCartes() > c2.getSommeCartes() && j->getNumero() == 1) { //si la somme des cartes du joueur 1 est supérieure
                    proprietaire = j;
                    cout << "Revendication valide, le joueur 1 (" << j->getNom() << ") gagne la borne !\n";
                }

                else if (c1.getSommeCartes() < c2.getSommeCartes() && j->getNumero() == 2) { //si la somme des cartes du joueur 2 est supérieure
                    proprietaire = j;
                    cout << "Revendication valide, le joueur 2 (" << j->getNom() << ") gagne la borne ! \n";
                }

                else if (c1.getSommeCartes() == c2.getSommeCartes() && j->getNumero() == 1 && j == premierAposer) {
                    proprietaire = j;
                    cout << "Revendication valide, le joueur 1 (" << j->getNom() << ") est le premier a avoir pose sa troisieme carte \n";
                }
                else if (c1.getSommeCartes() == c2.getSommeCartes() && j->getNumero() == 2 && j == premierAposer) {
                    proprietaire = j;
                    cout << "Revendication valide, le joueur 2 (" << j->getNom() << ") est le premier a avoir pose sa troisieme carte \n";
                }

                else {
                    cout << "Revendication non valide, la somme de 3 cartes n'est pas meilleure que celle de l'autre joueur \n";
                    return false;
                }

            }
            else { //si la carte Colin Maillard n'est pas jouée

                if (c1.getValeur() > c2.getValeur() && j->getNumero() == 1) { //si la valeur des cartes du joueur 1 est supérieure
                    proprietaire = j;
                    cout << "Revendication valide, le joueur 1 (" << j->getNom() << ") gagne la borne ! \n";
                }
                else if (c1.getValeur() < c2.getValeur() && j->getNumero() == 2) { //si la valeur des cartes du joueur 2 est supérieure
                    proprietaire = j;
                    cout << "Revendication valide, le joueur 2 (" << j->getNom() << ") gagne la borne ! \n";
                }
                else if (c1.getValeur() == c2.getValeur() && j->getNumero() == 1 && j == premierAposer) {
                    proprietaire = j;
                    cout << "Revendication valide, le joueur 1 (" << j->getNom() << ") est le premier a avoir pose sa troisieme carte \n";
                }
                else if (c1.getValeur() == c2.getValeur() && j->getNumero() == 2 && j == premierAposer) {
                    proprietaire = j;
                    cout << "Revendication valide, le joueur 2 (" << j->getNom() << ") est le premier a avoir pose sa troisieme carte \n";
                }
                else {
                    cout << "Revendication non valide, la combinaison de 3 cartes n'est pas meilleure que celle de l'autre joueur \n";
                    return false;
                }

            }
            //Récap de la revendication
            cout << "\nRécap revendication: \n\n";
            if (j->getNumero() == 1) {
                cout << j->getNom() << " gagne avec la revendication suivante: " << c1.getNom() << " dont la somme des cartes valait " << c1.getSommeCartes() << "\n";
                cout << "L'adversaire avait la combinaison suivante: " << c2.getNom() << " dont la somme des vartes valait " << c2.getSommeCartes() << "\n\n";
            }
            else {
                cout << j->getNom() << " gagne avec la revendication suivante: " << c2.getNom() << " dont la somme des cartes valait " << c2.getSommeCartes() << "\n";
                cout << "L'adversaire avait la combinaison suivante: " << c1.getNom() << " dont la somme des vartes valait " << c1.getSommeCartes() << "\n\n";
            }
        }

        else {
            cout << "Revendication invalide, il n'y a pas 3 cartes de chaque côté \n";
            return false;

        }

    }

    //si la revendication est valide, on ajoute la borne au vecteur de bornes du joueur
    if (proprietaire != nullptr) {
        proprietaire->ajouterBorneRevendiquee(this);
        proprietaire->setScoreManche(proprietaire->getScoreManche() + 1); //à voir l'utilité de cette ligne
        //Partie::getInstance().VerifGagnantManche(proprietaire); //Déplacé dans le script de jeu
        return true;
    }
}
