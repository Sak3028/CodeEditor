#include "StatusBar.h"

StatusBar::StatusBar(QWidget *parent):
    QStatusBar(parent)
{
    //Set Margins
    setContentsMargins(0,0,0,0);

    //Add File Type Display Widget
    //kscFileTypeDisplay=new kciFileType(this);

    //Add Rewrite Mode Display Widget
    lblRewriteMode=new StatusRewriteInfo(this);
    lblRewriteMode->hide();

    //Add Cursor Position Widget
    kscCursorPosition=new StatusCursorInfo(this);
    connect(kscCursorPosition,SIGNAL(ToLineNum(int)),
            this, SIGNAL(ToNewPosition(int)));

    //addPermanentWidget(kscFileTypeDisplay);
    addPermanentWidget(lblRewriteMode);
    addPermanentWidget(kscCursorPosition);
}

void StatusBar::showGotoBar(int currentValue, int MaxValue)
{
    kscCursorPosition->ShowGotoBox(currentValue, MaxValue);
}

void StatusBar::updateCursorPosition(int LineNum, int ColNum)
{
    kscCursorPosition->updateCursorPosition(LineNum, ColNum);
}

void StatusBar::updateRewriteMode(bool NewValue)
{
    lblRewriteMode->show();
    lblRewriteMode->setTextMode(NewValue);
}

void StatusBar::hideRewriteDisplay()
{
    lblRewriteMode->hide();
}

