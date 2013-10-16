#ifndef STATUSBAR_H
#define STATUSBAR_H
#include <QLabel>
#include <QDebug>
#include <QStatusBar>

#include "StatusCursorInfo.h"
#include "StatusReWrite.h"

class StatusBar : public QStatusBar
{
    Q_OBJECT
public:
    StatusBar(QWidget *parent);
    void showGotoBar(int currentValue, int MaxValue);

signals:
    void ToNewPosition(int NewLineNum);

public slots:
    void updateCursorPosition(int LineNum, int ColNum);
    void updateRewriteMode(bool NewValue);
    void hideRewriteDisplay();

private:
    //kciFileType *kscFileTypeDisplay;
    StatusCursorInfo *kscCursorPosition;
    StatusRewriteInfo *lblRewriteMode;

};


#endif // STATUSBAR_H
