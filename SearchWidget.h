#ifndef SEARCHWIDGET_H
#define SEARCHWIDGET_H
#include <QWidget>
#include <QLineEdit>
#include <QGridLayout>
#include <QPushButton>
#include <QToolButton>
#include <QResizeEvent>
#include <QMenu>

class kciSearchWidget : public QWidget
{
    Q_OBJECT
public:
    explicit kciSearchWidget(QWidget *parent);
    void setTextFocus();
    void setText(const QString& text);
    QString text() const;
    static const int searchTextPartWidth;

signals:
    void requireHide();
    void requireShowPreviousResult();
    void requireShowNextResult();
    void requireSearch(QString text,
                             bool regularExpression,
                             bool caseSensitively,
                             bool wholeWorld);

public slots:
    void onTextChanged(const QString &text);
    void onMenuClicked();

protected:
    void resizeEvent(QResizeEvent *event);
    void keyPressEvent(QKeyEvent *event);

private:
    enum menuItem
    {
        menuRegularExpress,
        menuMatchCase,
        menuWholeWord,
        menuItemCount
    };

    int currResultNum;

    QGridLayout *searchLayout;
    QToolButton *upButton, *downButton;

    //TextBox
    QWidget *searchText;
    QLineEdit *SearchTexts;
    QHBoxLayout *Layout;
    QPushButton *SearchIcon;

    QMenu *menu;
    QAction *menuAction[menuItemCount];
};

#endif // SEARCHWIDGET_H
