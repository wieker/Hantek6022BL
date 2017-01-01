#include "mainwindow.h"
#include <QApplication>

volatile int caught_sigint=0;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
