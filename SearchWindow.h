#ifndef SEARCHWINDOW_H
#define SEARCHWINDOW_H
#include <QGraphicsDropShadowEffect>
#include <QApplication>

#include "SearchWidget.h"

class kciSearchWindow : public kciSearchWidget
{
    Q_OBJECT

public:
    explicit kciSearchWindow(QWidget *parent);

private:
    QToolButton *closeButton;
};

#endif // SEARCHWINDOW_H
