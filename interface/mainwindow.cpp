#include "mainwindow.h"

//Constructeur de Mainwindow à l'aide de GroupeBox et de GridLayout. Code directement inspiré de la documentation Qt
Mainwindow::Mainwindow()
    : QWidget()
{
    QGridLayout *mainGrid = new QGridLayout;    //GridLayout principale de la fenetre principale. Permet d'organiser les GroupBox.
    mainGrid->addWidget(createMenuGroupBox(), 0, 0);
    mainGrid->addWidget(createLumiereGroupBox(), 1, 0);
    mainGrid->addWidget(createObjetGroupBox(), 2, 0);
    mainGrid->addWidget(createBasGroupBox(), 3, 0);
    setLayout(mainGrid);

    setWindowTitle(tr("EnLight'INT"));  //Titre de la fenetre.

}

//Créer GroupBox du menu de base file/control/constantes
QGroupBox *Mainwindow::createMenuGroupBox()
{
    //Création GroupBox
    QGroupBox *g_main = new QGroupBox;
    //Création PushButtons
    QPushButton *p_file = new QPushButton(tr("File"));
    QPushButton *p_control = new QPushButton(tr("Control"));
    QPushButton *p_const = new QPushButton(tr("Constant"));
    //Organisation via GridLayout
    QGridLayout *lumiereGrid = new QGridLayout(g_main);
    lumiereGrid->addWidget(p_file, 0, 0);
    lumiereGrid->addWidget(p_control, 0, 1);
    lumiereGrid->addWidget(p_const, 0, 2);

    return g_main; //return GroupBox créée
}

//Créer GroupBox du menu de gestion des lumieres add/set/del
QGroupBox *Mainwindow::createLumiereGroupBox()
{
    //Création GroupBox
    QGroupBox *g_lumiere = new QGroupBox(tr("Lights"));
    //Création PushButtons
    QPushButton *p_addLight = new QPushButton(tr("add"));
    QPushButton *p_setLight = new QPushButton(tr("set"));
    QPushButton *p_delLight = new QPushButton(tr("delete"));
    //Organisation via GridLayout
    QGridLayout *lumiereGrid = new QGridLayout(g_lumiere);
    lumiereGrid->addWidget(p_addLight, 0, 0);
    lumiereGrid->addWidget(p_setLight, 0, 1);
    lumiereGrid->addWidget(p_delLight, 0, 2);

    return g_lumiere; //return GroupeBox créée
}

//Créer GroupBox du menu de gestion des objets add/set/del
QGroupBox *Mainwindow::createObjetGroupBox()
{
    //Création GroupBox
    QGroupBox *g_item = new QGroupBox(tr("Items"));
    //Création PushButtons
    QPushButton *p_addItem = new QPushButton(tr("add"));
    QPushButton *p_setItem = new QPushButton(tr("set"));
    QPushButton *p_delItem = new QPushButton(tr("delete"));
    //Organisation via GridLayout
    QGridLayout *itemGrid = new QGridLayout(g_item);
    itemGrid->addWidget(p_addItem, 0, 0);
    itemGrid->addWidget(p_setItem, 0, 1);
    itemGrid->addWidget(p_delItem, 0, 2);

    return g_item; //return GroupBox créée
}

//Créer GroupBox des options annexes. CheckBox occlusion.
QGroupBox *Mainwindow::createBasGroupBox()
{
    //Création GroupBox
    QGroupBox *g_bas = new QGroupBox;
    //Création PushButtons
    QCheckBox *c_occlusion = new QCheckBox(tr("Occlusion"));
    //Organisation via GridLayout
    QGridLayout *basGrid = new QGridLayout(g_bas);
    basGrid->addWidget(c_occlusion, 0, 0);

    return g_bas; //return GroupeBox créée
}

//Connection SIGNAL/SLOT de la fenetre principale.
/*void Mainwindow::createMainWindowConnection()
{
    QObject::connect(SIGNAL, p_file->push())
}*/
