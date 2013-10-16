#ifndef HIGHLIGHTER_H
#define HIGHLIGHTER_H

#include <qsyntaxhighlighter.h>

class Highlighter : public QSyntaxHighlighter
{

public:
    Highlighter(QTextDocument *parent = 0);

public slots:
    void setTextQueue();

protected:
    void highlightBlock(const QString &text);

private:
    struct HighlightingRule
    {
        QRegExp pattern;
        QTextCharFormat format;
    };
    QVector<HighlightingRule> highlightingRules;
    QTextCharFormat keyWordFormat;
};

#endif // HIGHLIGHTER_H
