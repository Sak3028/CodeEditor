#include "SearchWindow.h"

static const int nFixedWidth=290;

kciSearchWindow::kciSearchWindow(QWidget *parent) :
    kciSearchWidget(parent)
{
    //Set Search Details.
    setFixedSize(nFixedWidth,38);

    QPalette kswPal=palette();
    kswPal.setColor(QPalette::Window,QColor(0,0,0));
    setPalette(kswPal);

    QGraphicsDropShadowEffect *wndShadow = new QGraphicsDropShadowEffect(this);
    wndShadow->setBlurRadius(15.0);
    wndShadow->setColor(QColor(0, 0, 0, 200));
    wndShadow->setOffset(0);
    setGraphicsEffect(wndShadow);

    QGridLayout* searchLayout=(QGridLayout*)layout();

    //Set Close Button
    closeButton=new QToolButton(this);
    closeButton->setIcon(QIcon(":/toolbutton/image/Close.png"));
    closeButton->setAutoRaise(true);
    closeButton->setFixedSize(16,26);
    searchLayout->addWidget(closeButton,0,searchLayout->columnCount());

    //Set Button Palette
    QPalette pal=closeButton->palette();
    pal.setColor(QPalette::Button, QColor(190,0,0));
    closeButton->setPalette(pal);
    //Set Button Action
    connect(closeButton, SIGNAL(clicked()),
            this, SIGNAL(requireHide()));

    qApp->installEventFilter(this);
}

