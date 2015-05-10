#include "interface.h"

Interface::Interface() : QMainWindow(), ambientOcclusion(false)
{
    show();

    setCentralWidget(mCentralWidget = new QWidget(this));

    mLayout = new QGridLayout(mCentralWidget);

    mLayout->addWidget(mCheckBoxAmbientOcclusion = new QCheckBox("Occlusion Ambiante", this));

    connect(mCheckBoxAmbientOcclusion, SIGNAL(stateChanged(int)), this, SLOT(ambientOcclusionChanged(int)));
}

void Interface::ambientOcclusionChanged(int state)
{
    if(state == Qt::Unchecked)
        ambientOcclusion = false;

    else
        ambientOcclusion = true;
}

Interface::~Interface()
{

}

