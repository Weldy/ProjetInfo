#ifndef INTERFACE_H
#define INTERFACE_H

#include <QMainWindow>
#include <QCheckBox>
#include <QGridLayout>

class Interface : public QMainWindow
{
    Q_OBJECT
public:
    Interface();
    ~Interface();

    /** No encapsulation here **/
public:
    bool ambientOcclusion;

private slots:
    void ambientOcclusionChanged(int state);

private:
    QWidget *mCentralWidget;
    QGridLayout *mLayout;
    QCheckBox *mCheckBoxAmbientOcclusion;
};

#endif // INTERFACE_H
