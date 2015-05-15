#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "include.h"


//Déclaration de la classe Mainwindow qui servira à gérer la fenetre principale.
//Cette classe est fille de la classe QWidget
class Mainwindow : public QWidget
{

    Q_OBJECT    //C'est un QObject.

public:

    Mainwindow(); //Déclaration du constructeur.

public slots:
    void namePopUp();
    void colorLightPick();
    void refreshLight(QListWidgetItem *index);
    void deleteLight();

private:

//Methode private qui seront utilisées seulement par le constructeur pour déclarer les GroupBox utilisées.
//Ce découpage permet une meilleure lisibilité et modularité du code. (Inspiré du modèle de la Doc).
    QGroupBox *createMenuGroupBox();
    QGroupBox *createLumiereGroupBox();
    QGroupBox *createObjetGroupBox();
    QGroupBox *createBasGroupBox();
    //void createMainWindowConnection();


    QColor lightColor; //amené à disparaitre
    QLabel *l_color;
    int lightNumber;
    Settings settings;
    QListWidgetItem *lightCurrent;

    QListWidget *listeLumiere;

};


#endif // MAFENETRE_H
