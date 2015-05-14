#ifndef STRUCTURES
#define STRUCTURES

#endif // STRUCTURES

#include "include.h"

struct LightSetting {

    int number;
    QString name;
    QColor couleur;
    QVector3D pos;
    float radius;
    bool enabled;
    bool ombre;
    bool gi;

};

struct Settings {

    bool occlusion;
    QString fichier;
    LightSetting *light[10];

};
