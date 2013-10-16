#ifndef STATUSREWRITE_H
#define STATUSREWRITE_H
#include <QLabel>

class StatusRewriteInfo : public QLabel
{
    Q_OBJECT
public:
    explicit StatusRewriteInfo(QWidget *parent = 0);

    bool getTextMode() const;
    void setTextMode(bool value);

signals:

public slots:

private:
    QString rewriteText, unrewriteText;
    bool textMode;
};


#endif // STATUSREWRITE_H
