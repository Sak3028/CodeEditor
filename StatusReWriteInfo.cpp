#include "StatusReWrite.h"

StatusRewriteInfo::StatusRewriteInfo(QWidget *parent) :
    QLabel(parent)
{
    rewriteText=tr("Overwrite");
    unrewriteText=tr("Insert");

    //Text Mode is always the same as insert mode status.
    textMode=false;

    //Set Default Text.
    setText(unrewriteText);
}

bool StatusRewriteInfo::getTextMode() const
{
    return textMode;
}

void StatusRewriteInfo::setTextMode(bool value)
{
    textMode = value;
    //When text mode is changed, refresh the text.
    if(textMode)
    {
        setText(rewriteText);
    }
    else
    {
        setText(unrewriteText);
    }
}



