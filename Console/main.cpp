#include "partie.h"
int main() {

    auto& partie = Partie::getInstance();
    partie.jeu();

    std::chrono::seconds duration(15);
    std::this_thread::sleep_for(duration);

    return 0;
}