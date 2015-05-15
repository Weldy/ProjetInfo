#include "mainwindow.h"

//Constructeur de Mainwindow à l'aide de GroupeBox et de GridLayout. Code directement inspiré de la documentation Qt
Mainwindow::Mainwindow()
    : QWidget()
{
    //init

    settings.occlusion=false;
    settings.fichier ="truc"; //inutile à l'état actuel

    LightSetting *lum1 = new LightSetting{0,"Lumière Principale",QColor(100,200,200),QVector3D(0,0,0),0,false,false,false};
    settings.light[0] = lum1;
    lightNumber =1;

    QWidget *tab1 = new QWidget(this) ;
    QTabWidget *mainTab = new QTabWidget(tab1);

    //QGridLayout *mainGrid = new QGridLayout;    //GridLayout principale de la fenetre principale. Permet d'organiser les GroupBox.

    mainTab->setFixedSize(800, 500);
    mainTab->addTab(createObjetGroupBox(),"Intro");
    mainTab->addTab(createLumiereGroupBox(),"Gestion des lumières");
    mainTab->addTab(createBasGroupBox(),"Occlusion ambiante");
    mainTab->addTab(createObjetGroupBox(),"Logs");
    mainTab->addTab(createObjetGroupBox(),"Mode Expert");
    mainTab->addTab(createObjetGroupBox(),"A propos");
    mainTab->setIconSize(QSize(30,50));
    mainTab->setTabIcon(0,QIcon("images/info.png"));
    mainTab->setTabIcon(1,QIcon("images/light.png"));
    mainTab->setTabIcon(2,QIcon("images/param.png"));
    mainTab->setTabIcon(3,QIcon("images/logs.png"));
    mainTab->setTabIcon(4,QIcon("images/expert.png"));
    mainTab->setTabIcon(5,QIcon("images/about.png"));

   // QPushButton *launch = new QPushButton("Lancer le moteur", this);
    //launch->show();
    //launch->setFont(QFont("Helvetica",18));
    //launch->resize(200,35);
    //launch->move(25,360);

    this->resize(800,550);
    setWindowTitle(tr("EnLight'INT"));  //Titre de la fenetre.

}

//Créer GroupBox du menu de base file/control/constantes
QGroupBox *Mainwindow::createMenuGroupBox()
{
    //Création GroupBox
    QGroupBox *g_main = new QGroupBox;
    g_main->setFont(QFont("Helvetica",18));
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
    QPushButton *p_delLight = new QPushButton(tr("delete"));

    listeLumiere = new QListWidget(this);
    new QListWidgetItem(settings.light[0]->name,listeLumiere,0);
    this->lightCurrent = this->listeLumiere->item(0);

    QPushButton *p_selectColor = new QPushButton("Selection couleur", this);
    l_color = new QLabel();
    l_color->setAutoFillBackground(true);
    QString iStyle ="background-color : rgb(%1,%2,%3);";
    l_color->setStyleSheet(iStyle.arg(this->settings.light[0]->couleur.red()).arg(this->settings.light[0]->couleur.green()).arg(this->settings.light[0]->couleur.blue()));

    b_posX = new QSpinBox(this);
    b_posX->setRange(-1000,1000);
    QLabel *l_posX = new QLabel("X : ");
    l_posX->setAlignment(Qt::AlignRight);
    b_posY = new QSpinBox(this);
    b_posY->setRange(-1000,1000);
    QLabel *l_posY = new QLabel("Y : ");
    l_posY->setAlignment(Qt::AlignRight);
    b_posZ = new QSpinBox(this);
    b_posZ->setRange(-1000,1000);
    QLabel *l_posZ = new QLabel("Z : ");
    l_posZ->setAlignment(Qt::AlignRight);
    b_ray = new QSpinBox(this);
    b_ray->setMaximum(2000);
    QLabel *l_ray = new QLabel("Rayon : ");
    l_ray->setAlignment(Qt::AlignRight);
    c_active = new QCheckBox(tr("Lumière Activée"));
    c_ombre = new QCheckBox(tr("Ombre Activée"));
    c_gi = new QCheckBox(tr("GI Activée"));

    //Organisation via GridLayout
    QGridLayout *lumiereGrid = new QGridLayout(g_lumiere);
    lumiereGrid->addWidget(p_addLight, 0, 0);
    lumiereGrid->addWidget(p_delLight, 0, 1);
    lumiereGrid->addWidget(listeLumiere, 1,0,7,3);
    lumiereGrid->addWidget(p_selectColor, 1,4,1,3);
    lumiereGrid->addWidget(l_color,1,3,1,1);
    lumiereGrid->addWidget(l_posX,2,3,1,1);
    lumiereGrid->addWidget(b_posX, 2,4,1,1);
    lumiereGrid->addWidget(l_posY,2,5,1,1);
    lumiereGrid->addWidget(b_posY, 2,6,1,1);
    lumiereGrid->addWidget(l_posZ,2,7,1,1);
    lumiereGrid->addWidget(b_posZ, 2,8,1,1);
    lumiereGrid->addWidget(l_ray,3,3,1,1);
    lumiereGrid->addWidget(b_ray,3,4,1,2);
    lumiereGrid->addWidget(c_active,4,3,1,1);
    lumiereGrid->addWidget(c_ombre,5,3,1,1);
    lumiereGrid->addWidget(c_gi,6,3,1,1);

    QObject::connect(p_addLight, SIGNAL(clicked()), this, SLOT(namePopUp()));
    QObject::connect(p_delLight, SIGNAL(clicked()), this, SLOT(deleteLight()));

    QObject::connect(p_selectColor, SIGNAL(clicked()), this, SLOT(colorLightPick()));

    QObject::connect(b_posX, SIGNAL(valueChanged(int)), this, SLOT(changePosX(int)));
    QObject::connect(b_posY, SIGNAL(valueChanged(int)), this, SLOT(changePosY(int)));
    QObject::connect(b_posZ, SIGNAL(valueChanged(int)), this, SLOT(changePosZ(int)));

    QObject::connect(b_ray, SIGNAL(valueChanged(int)), this, SLOT(changeRay(int)));

    QObject::connect(c_active, SIGNAL(stateChanged(int)), this, SLOT(enableLight(int)));
    QObject::connect(c_ombre, SIGNAL(stateChanged(int)), this, SLOT(enableShad(int)));
    QObject::connect(c_gi, SIGNAL(stateChanged(int)), this, SLOT(enableGI(int)));


    QObject::connect(listeLumiere,SIGNAL(itemClicked(QListWidgetItem *)),this,SLOT(refreshLight(QListWidgetItem *)));


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
    QCheckBox *c_occlusion = new QCheckBox(tr("Occlusion Ambiante"));
    c_occlusion->setToolTip("L'occlusion ambiante ajoute du rélisme à la scène en simulant le fait que certains endroits soit difficile d'accès pour la lumière et donc plus sombre");
    //Organisation via GridLayout
    QGridLayout *basGrid = new QGridLayout(g_bas);
    basGrid->addWidget(c_occlusion, 0, 0);

    QObject::connect(c_occlusion, SIGNAL(stateChanged(int)), this, SLOT(enableOccl(int)));

    return g_bas; //return GroupeBox créée
}

void Mainwindow::namePopUp()
{
    if(lightNumber<10){
        QString lightName = QInputDialog::getText(this, "Nom", "Quel nom pour cette lumière ?");
        LightSetting *newLum = new LightSetting{lightNumber,lightName,QColor("white"),QVector3D(0,0,0),0,false,false,false};
        int test =0;
        while(settings.light[test] != NULL){
            test++;
        }
        settings.light[test]= newLum;
        new QListWidgetItem(settings.light[test]->name,listeLumiere,test);
        lightNumber ++;
    }
}

void Mainwindow::refreshLight(QListWidgetItem *index)
{
    this->lightCurrent= index;
    QString iStyle ="background-color : rgb(%1,%2,%3);";
    this->l_color->setStyleSheet(iStyle.arg(this->settings.light[lightCurrent->type()]->couleur.red()).arg(this->settings.light[lightCurrent->type()]->couleur.green()).arg(this->settings.light[lightCurrent->type()]->couleur.blue()));
    this->b_posX->setValue(this->settings.light[lightCurrent->type()]->pos.x());
    this->b_posY->setValue(this->settings.light[lightCurrent->type()]->pos.y());
    this->b_posZ->setValue(this->settings.light[lightCurrent->type()]->pos.z());
    this->b_ray->setValue(this->settings.light[lightCurrent->type()]->radius);
    this->c_active->setChecked(this->settings.light[lightCurrent->type()]->enabled);
    this->c_ombre->setChecked(this->settings.light[lightCurrent->type()]->ombre);
    this->c_gi->setChecked(this->settings.light[lightCurrent->type()]->gi);
}

void Mainwindow::deleteLight()
{
    this->listeLumiere->takeItem(this->listeLumiere->row(this->listeLumiere->currentItem()));
    this->settings.light[lightCurrent->type()];
    lightNumber --;
}

void Mainwindow::colorLightPick()
{
    QColor newColor = QColorDialog::getColor(this->settings.light[lightCurrent->type()]->couleur, this);
    this->settings.light[lightCurrent->type()]->couleur = newColor;
    QString iStyle ="background-color : rgb(%1,%2,%3);";
    this->l_color->setStyleSheet(iStyle.arg(this->settings.light[lightCurrent->type()]->couleur.red()).arg(this->settings.light[lightCurrent->type()]->couleur.green()).arg(this->settings.light[lightCurrent->type()]->couleur.blue()));
}

void Mainwindow::changePosX(int newPos)
{
    this->settings.light[lightCurrent->type()]->pos = QVector3D(newPos,this->settings.light[lightCurrent->type()]->pos.y(),this->settings.light[lightCurrent->type()]->pos.z());
}
void Mainwindow::changePosY(int newPos)
{
    this->settings.light[lightCurrent->type()]->pos = QVector3D(this->settings.light[lightCurrent->type()]->pos.x(),newPos,this->settings.light[lightCurrent->type()]->pos.z());
}
void Mainwindow::changePosZ(int newPos)
{
    this->settings.light[lightCurrent->type()]->pos= QVector3D(this->settings.light[lightCurrent->type()]->pos.x(),this->settings.light[lightCurrent->type()]->pos.y(),newPos);
}
void Mainwindow::changeRay(int newRad)
{
    this->settings.light[lightCurrent->type()]->radius = newRad;
}

void Mainwindow::enableLight(int state)
{
    this->settings.light[lightCurrent->type()]->enabled = state;
}
void Mainwindow::enableShad(int state)
{
    this->settings.light[lightCurrent->type()]->ombre = state;
}
void Mainwindow::enableGI(int state)
{
    this->settings.light[lightCurrent->type()]->gi = state;
}

void Mainwindow::enableOccl(int state)
{
    this->settings.occlusion = state;
}

//Connection SIGNAL/SLOT de la fenetre principale.
/*void Mainwindow::createMainWindowConnection()
{
    QObject::connect(SIGNAL, p_file->push())
}*/
