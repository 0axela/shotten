#include <QApplication>
#include "st.h"
#include "vuePartie.h"
//#include "vuedebut.h"


int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    //VuePartie vueTest;
    //vueTest.show();
    FirstWindow partie;
    partie.show();


    return app.exec();
    //return 0;
}
