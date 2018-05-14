#include "mainwindow.h"
#include <QApplication>
#include <time.h>

int main(int argc, char *argv[])
{
    srand(time(NULL));
    QApplication a(argc, argv);
    MainWindow w;
    w.setFixedSize(424,485);
    w.show();
    return a.exec();
}
