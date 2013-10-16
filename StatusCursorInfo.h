#ifndef STATUSCURSORINFO_H
#define STATUSCURSORINFO_H
#include <QWidget>
#include <QLabel>
#include <QHBoxLayout>
#include <QPropertyAnimation>
#include <QSpinBox>

class StatusCursorInfo : public QWidget
{
    Q_OBJECT
public:
    explicit StatusCursorInfo(QWidget *parent = 0);
    void ShowGotoBox(int currentValue, int MaxValue);
    void HideGotoBox();
    bool getGotoShowed();

signals:
    void ToLineNum(int LineNum);

protected:
    void resizeEvent(QResizeEvent *e);

public slots:
    void updateCursorPosition(int LineNum, int ColNum);
    void gotoLineNumber(int NewNum);
    void finishedHideGotoBox();

private slots:
    void setHideGotoBox();

private:
    QSpinBox *spbLineNum;
    QLabel *lblCursorPosition;
    bool gotoBarShowed;

    QPropertyAnimation *gotoHideAnime;

};


#endif // STATUSCURSORINFO_H
