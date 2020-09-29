#include "ledcontrolwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LedControlWindow w;
    w.show();
    return a.exec();
}
