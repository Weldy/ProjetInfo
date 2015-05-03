#include <QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc,  argv);

    Mainwindow fenetre;
    fenetre.show();

    return app.exec();
}
