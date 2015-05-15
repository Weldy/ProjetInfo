#ifndef STRUCTURES
#define STRUCTURES

#endif // STRUCTURES

#include "include.h"

struct LightSetting {

    int number; // identifiant unique
    QString name; //nom choisi par l'user
    QColor couleur; // couleur de la lumière
    QVector3D pos; // position sous forme de vecteur
    float radius; //rayon dans lequel la lumière est présente
    bool enabled; // test l'activation ou non de la lumière
    bool ombre; //défini si l'ombrage est  activé pour cete lumière
    bool gi; // défini si l'illumination globale est activée pour cette lumière

};

struct Settings {

    bool occlusion; //defini si l'occlusion ambiante est activée
    QString fichier; //défini le chemin vers la scène rendue à l'écran (non implémenté)
    LightSetting *light[10]; // tableau de pointeur vers les differentes lumières parmètrés par l'user

};
