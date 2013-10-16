#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    //Initalize Application Palette.
    QPalette pal=app.palette();
    pal.setColor(QPalette::Text,QColor(0,0,0));
    pal.setColor(QPalette::Highlight,QColor(0xf7,0xcf,0x3d));
    pal.setColor(QPalette::HighlightedText,QColor(0,0,0));
    app.setPalette(pal);
    MainWindow w;
    w.show();
    
    return app.exec();
}
