#ifndef SEARCHLINETEXT_H
#define SEARCHLINETEXT_H

#include <QLineEdit>
#include <QLabel>
#include <QWidget>
#include <QPixmap>
#include <QHBoxLayout>


class kciSearchLineText : public QWidget
{
    Q_OBJECT
public:
    explicit kciSearchLineText(QWidget *parent = 0);

signals:

public slots:

private:
    QLineEdit *searchTextBox;
    QHBoxLayout *MainLayout;
    QLabel *lblImage;

};

#endif // SEARCHLINETEXT_H
