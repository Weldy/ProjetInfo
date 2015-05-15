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
    mainTab->addTab(createIntroGroupBox(),"Intro");
    mainTab->addTab(createLumiereGroupBox(),"Gestion des lumières");
    mainTab->addTab(createBasGroupBox(),"Occlusion ambiante");
    mainTab->addTab(createLogsGroupBox(),"Logs");
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

    this->resize(850,550);
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

QFrame *Mainwindow::createIntroGroupBox()
{
    //Création GroupBox
    QFrame *f_intro = new QFrame();
    QFrame *f_1 = new QFrame(f_intro);
    QFrame *f_2 = new QFrame(f_intro);
    QFrame *f_3 = new QFrame(f_intro);
    f_intro->setFrameShape(QFrame::StyledPanel);
    //Création Label
    QLabel *l_iTitle = new QLabel("EnLight'Int");
    l_iTitle->setFont(QFont("Arial",18));
    QLabel *l_iText = new QLabel("  Ce programme permet de changer en temps réel les parmamètres d'un moteur de rendu 3D. \n Il comporte plusieurs fenetres :  \n"
    "- La gestion des lumières permet d'ajouter jusqu'à 10 lumières dans la scène\n- L'occlusion ambiante peut être activée ou désactivée\n"
    "- Les logs permetent de suivre l'évolution du rendu\n- Le mode expert permet d'interagir directement avec le code en C++\n"
    "\n  Pour en apprendre plus n'hésitez pas à consulter la section à propos ;)");
    l_iText->setFont(QFont("Arial",11));
    //Organisation via GridLayout
    QGridLayout *itemGrid = new QGridLayout(f_intro);
    itemGrid->addWidget(l_iTitle, 0, 2);
    itemGrid->addWidget(f_1, 1, 0);
    itemGrid->addWidget(f_2, 1, 4,1,2);
    itemGrid->addWidget(f_3, 4, 0,1,2);
    itemGrid->addWidget(l_iText, 1, 1,2,2);

    return f_intro; //return intro créée
}

QGroupBox *Mainwindow::createLogsGroupBox()
{
    //Création GroupBox
    QGroupBox *g_item = new QGroupBox(tr("Engine logs"));
    QFrame *f_1 = new QFrame(g_item);
    //Création textarea
    t_logs = new QTextEdit("Console initialisée");
    t_logs->setReadOnly(true);
    //Organisation via GridLayout
    QGridLayout *itemGrid = new QGridLayout(g_item);
    itemGrid->addWidget(t_logs, 1, 1);
    itemGrid->addWidget(f_1, 0, 0,1,3);

    QObject::connect(this, SIGNAL(logsChanged(QString)), this, SLOT(changeText(QString)));

    QString logs = "logs initialisés";
    emit logsChanged(logs);

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
        QString logs = lightName + " : Nouvelle lumière crée !";
        emit logsChanged(logs);
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
    if (lightCurrent != NULL){
    this->listeLumiere->takeItem(this->listeLumiere->row(this->listeLumiere->currentItem()));
    QString logs = this->settings.light[lightCurrent->type()]->name + " : Suppresion en cours";
    emit logsChanged(logs);
    delete this->settings.light[lightCurrent->type()];
    logs = "... Suppresion effectuée !";
    emit logsChanged(logs);
    lightCurrent = NULL;
    lightNumber --;}
    else{QString logs = "Erreur selection : il faut cliquer correctement sur la lumière";
        emit logsChanged(logs);}


}

void Mainwindow::colorLightPick()
{
    QColor newColor = QColorDialog::getColor(this->settings.light[lightCurrent->type()]->couleur, this);
    this->settings.light[lightCurrent->type()]->couleur = newColor;
    QString iStyle ="background-color : rgb(%1,%2,%3);";
    this->l_color->setStyleSheet(iStyle.arg(this->settings.light[lightCurrent->type()]->couleur.red()).arg(this->settings.light[lightCurrent->type()]->couleur.green()).arg(this->settings.light[lightCurrent->type()]->couleur.blue()));
    QString logs = this->settings.light[lightCurrent->type()]->name + " : Nouvelle couleur --> " + this->settings.light[lightCurrent->type()]->couleur.name();
    emit logsChanged(logs);
}

void Mainwindow::changePosX(int newPos)
{
    this->settings.light[lightCurrent->type()]->pos = QVector3D(newPos,this->settings.light[lightCurrent->type()]->pos.y(),this->settings.light[lightCurrent->type()]->pos.z());
    QString logs = this->settings.light[lightCurrent->type()]->name + " : Nouvelle position en x --> [" + QString::number(this->settings.light[lightCurrent->type()]->pos.x()) + "," + QString::number(this->settings.light[lightCurrent->type()]->pos.y()) + "," + QString::number(this->settings.light[lightCurrent->type()]->pos.z()) + "]";
    emit logsChanged(logs);
}
void Mainwindow::changePosY(int newPos)
{
    this->settings.light[lightCurrent->type()]->pos = QVector3D(this->settings.light[lightCurrent->type()]->pos.x(),newPos,this->settings.light[lightCurrent->type()]->pos.z());
    QString logs = this->settings.light[lightCurrent->type()]->name + " : Nouvelle position en y --> [" + QString::number(this->settings.light[lightCurrent->type()]->pos.x()) + "," + QString::number(this->settings.light[lightCurrent->type()]->pos.y()) + "," + QString::number(this->settings.light[lightCurrent->type()]->pos.z()) + "]";
    emit logsChanged(logs);
}
void Mainwindow::changePosZ(int newPos)
{
    this->settings.light[lightCurrent->type()]->pos= QVector3D(this->settings.light[lightCurrent->type()]->pos.x(),this->settings.light[lightCurrent->type()]->pos.y(),newPos);
    QString logs = this->settings.light[lightCurrent->type()]->name + " : Nouvelle position en z --> [" + QString::number(this->settings.light[lightCurrent->type()]->pos.x()) + "," + QString::number(this->settings.light[lightCurrent->type()]->pos.y()) + "," + QString::number(this->settings.light[lightCurrent->type()]->pos.z()) + "]";
    emit logsChanged(logs);
}
void Mainwindow::changeRay(int newRad)
{
    this->settings.light[lightCurrent->type()]->radius = newRad;
    QString logs = this->settings.light[lightCurrent->type()]->name + " : Nouveau rayon --> " + QString::number(newRad) ;
    emit logsChanged(logs);
}

void Mainwindow::enableLight(int state)
{
    this->settings.light[lightCurrent->type()]->enabled = state;
    QString logs;
    if (state ==0){
     logs = this->settings.light[lightCurrent->type()]->name + " : Lumière désactivée" ;
    }else {logs = this->settings.light[lightCurrent->type()]->name + " : Lumière activée";}
    emit logsChanged(logs);
}
void Mainwindow::enableShad(int state)
{
    this->settings.light[lightCurrent->type()]->ombre = state;
    QString logs;
    if (state ==0){
     logs = this->settings.light[lightCurrent->type()]->name + " : Ombres désactivées" ;
    }else {logs = this->settings.light[lightCurrent->type()]->name + " : Ombres activées";}
    emit logsChanged(logs);
}
void Mainwindow::enableGI(int state)
{
    this->settings.light[lightCurrent->type()]->gi = state;
    QString logs;
    if (state ==0){
     logs = this->settings.light[lightCurrent->type()]->name + " : Illumination globale désactivée" ;
    }else {logs = this->settings.light[lightCurrent->type()]->name + " : Illumination globale activée";}
    emit logsChanged(logs);
}

void Mainwindow::enableOccl(int state)
{
    this->settings.occlusion = state;
    QString logs;
    if (state ==0){
     logs = "Occlusion ambiante désactivée";
    }else {logs = "Occlusion ambiante activée";}
    emit logsChanged(logs);
}

void Mainwindow::changeText(QString newLog)
{
    this->t_logs->append(newLog);
}

//Connection SIGNAL/SLOT de la fenetre principale.
/*void Mainwindow::createMainWindowConnection()
{
    QObject::connect(SIGNAL, p_file->push())
}*/
