#include "highlighter.h"
#include <fstream>

using namespace std;

Highlighter::Highlighter(QTextDocument *parent) : QSyntaxHighlighter(parent)
{
    HighlightingRule rule;

    keyWordFormat.setForeground(Qt::darkGreen);
    keyWordFormat.setFontWeight(QFont::Bold);

    setTextQueue();
}

void Highlighter::highlightBlock(const QString &text)
{
    foreach(const HighlightingRule &rule, highlightingRules)
    {
        QRegExp expression(rule.pattern);
        int nIndex = expression.indexIn(text);
        while(nIndex >= 0)
        {
            int nLength = expression.matchedLength();
            setFormat(nIndex, nLength, rule.format);
            nIndex = expression.indexIn(text, nIndex + nLength);
        }
    }
    setCurrentBlockState(0);
}


void Highlighter::setTextQueue()
{
    highlightingRules.clear();
    HighlightingRule rule;
    ifstream fin("highlighter.lcp");
    string strInput;
    while(fin >> strInput)
    {
        if(strInput.substr(0, 6) == "color-")
        {
            if(strInput == "color-darkGreen")
            {
                keyWordFormat.setForeground(Qt::darkGreen);
                keyWordFormat.setFontWeight(QFont::Bold);
            }
            if(strInput == "color-darkRed")
            {
                keyWordFormat.setForeground(Qt::darkRed);
                keyWordFormat.setFontWeight(QFont::Bold);
            }
            if(strInput == "color-darkMagenta")
            {
                keyWordFormat.setForeground(Qt::darkMagenta);
                keyWordFormat.setFontWeight(QFont::Bold);
            }
            if(strInput == "color-purple")
            {
                keyWordFormat.setForeground(QBrush(QColor::fromRgb(160, 32, 240)));
                keyWordFormat.setFontWeight(QFont::Bold);
            }
            if(strInput == "color-blue")
            {
                keyWordFormat.setForeground(Qt::blue);
                keyWordFormat.setFontWeight(QFont::Normal);
            }
        }
        else
        {
            QString pattern = QString(QString::fromLocal8Bit(strInput.c_str()));
            rule.pattern = QRegExp(pattern);
            rule.format = keyWordFormat;
            highlightingRules.append(rule);
        }
    }
}
