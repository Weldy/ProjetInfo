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
    void changePosX(int newPos);
    void changePosY(int newPos);
    void changePosZ(int newPos);
    void changeRay(int newRad);
    void enableLight(int state);
    void enableShad(int state);
    void enableGI(int state);
    void enableOccl(int state);

private:

//Methode private qui seront utilisées seulement par le constructeur pour déclarer les GroupBox utilisées.
//Ce découpage permet une meilleure lisibilité et modularité du code. (Inspiré du modèle de la Doc).
    QGroupBox *createMenuGroupBox();
    QGroupBox *createLumiereGroupBox();
    QGroupBox *createObjetGroupBox();
    QGroupBox *createBasGroupBox();
    //void createMainWindowConnection();

    Settings settings;

    //Gestion panneau lumière

    //QColor lightColor; //ammené à disparaitre
    QListWidget *listeLumiere;
    QLabel *l_color;
    int lightNumber;
    QListWidgetItem *lightCurrent;

    QSpinBox *b_posX;
    QSpinBox *b_posY;
    QSpinBox *b_posZ;
    QSpinBox *b_ray;
    QCheckBox *c_active;
    QCheckBox *c_ombre;
    QCheckBox *c_gi;




};


#endif // MAFENETRE_H
