#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    qApp->setStyleSheet("QWidget { background-color: lightblue; }");
    MainWindow mainWindow;
    mainWindow.show();
    return app.exec();
}
