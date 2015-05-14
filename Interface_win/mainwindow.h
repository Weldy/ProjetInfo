#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QCheckBox>
#include <QGroupBox>
#include <QLayout>
#include <QGridLayout>
#include <QMenu>
#include <QTabWidget>
#include <QListWidget>
#include <QSpinBox>
#include <QLabel>
#include <QString>
#include <QInputDialog>
#include <QColorDialog>
#include <QPalette>
#include <QColor>





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

private:

//Methode private qui seront utilisées seulement par le constructeur pour déclarer les GroupBox utilisées.
//Ce découpage permet une meilleure lisibilité et modularité du code. (Inspiré du modèle de la Doc).
    QGroupBox *createMenuGroupBox();
    QGroupBox *createLumiereGroupBox();
    QGroupBox *createObjetGroupBox();
    QGroupBox *createBasGroupBox();
    void createMainWindowConnection();

    QColor lightColor;
    QLabel *l_color;

};


#endif // MAFENETRE_H
