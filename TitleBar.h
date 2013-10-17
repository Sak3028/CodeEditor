#ifndef TITLEBAR_H
#define TITLEBAR_H
#include <QPoint>
#include <QMouseEvent>
#include <QToolButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QPropertyAnimation>
#include <QRect>
#include <QIcon>
#include <QString>
#include <QToolBar>
#include <QWidget>
#include <QPalette>
#include <QDebug>

#ifndef Q_OS_MACX
class TitleBarAutoFill : public QWidget
{
    Q_OBJECT
public:
    explicit TitleBarAutoFill(QWidget *parent = 0);

signals:
    void dblClickEmit();

protected:
    void mouseDoubleClickEvent(QMouseEvent *e);

private:
};
#endif

class TitleBar : public QWidget
{
    Q_OBJECT
public:
    explicit TitleBar(QWidget *parent = 0);
    void addToolButton(QToolButton *tblMainButton);
    void addToolSeparator();
    void setWindowMax();
    void setWindowNormal();
    void setWindowMin();
#ifndef Q_OS_MACX
    void setMenu(QMenu *menu);
    void setMainButtonIcon(const QString& mainIcon);
#endif

signals:

public slots:
    void showToolBar();
    void hideToolBar();

private slots:
    void _exchange_button_state();
#ifndef Q_OS_MACX
    void spacingDblClick();
#endif

protected:
#ifndef Q_OS_MACX
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
#endif

private:
    bool hasPressed;
    bool isShowingNormalButton;   //false when show minimizeButton, true when show normalButton
    bool toolbarShown;
    QPoint mousePosStart;
    QWidget *mainWindow;

    QToolButton *maximizeButton,*minimizeButton;
    QToolButton *closeButton;

    QVBoxLayout *vMinLayout, *vMaxLayout, *vCloseLayout;
    QHBoxLayout *hLayout;
    QString windowTitle;

#ifndef Q_OS_MACX
    TitleBarAutoFill *autoFill;
    QToolButton *mainButton;
#endif

    QIcon mainButtonIcon,normalButtonIcon,maximizeButtonIcon,minimizeButtonIcon,closeButtonIcon;
    QToolBar *mainToolBar;
    QPropertyAnimation *tlbHideAnime, *tlbShowAnime;

    QSpacerItem *NoUseSpacing;
};


#endif // TITLEBAR_H
