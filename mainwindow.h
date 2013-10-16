#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <qstringlist.h>
#include <qstringlistmodel.h>
#include <qtextcursor.h>
#include "textedit.h"

#include "SearchWindow.h"

class QAction;
class QActionGroup;
class QLabel;
class QMenu;


class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    void OpenFile();
    void SaveFile();
    void SaveFileAs();

private:
    QAbstractItemModel* modelFromFile(const QString& fileName);

private:
    void SetFileInfo(QString strFileName);
    void createActions();
    void createMenus();
    
private slots:
    void print();

    void undo();

    void redo();

    void cut();

    void copy();

    void paste();

    void bold();
    void italic();
    void leftAlign();
    void rightAlign();
    void justify();
    void center();
    void setLineSpacing();
    void setParagraphSpacing();

    void sellectAll();

    void on_action_New_triggered();

    void on_action_search_triggered();

    void on_action_Open_triggered();

    void on_action_Save_triggered();

    void on_action_Save_As_triggered();

    void on_action_Exit_triggered();

    void on_action_About_triggered();

    void on_textEdit_textChanged();

private:


    bool m_bChanged;
    QString m_strCurFileDir;
    QString m_strCurFileName;
    QMenu *fileMenu;
    QMenu *editMenu;
    QMenu *formatMenu;
    QMenu *helpMenu;
    QActionGroup *alignmentGroup;
    QAction *newAct;
    QAction *openAct;
    QAction *saveAct;
    QAction *printAct;
    QAction *exitAct;
    QAction *undoAct;
    QAction *redoAct;
    QAction *cutAct;
    QAction *copyAct;
    QAction *pasteAct;
    QAction *sellectAllAct;
    QAction *boldAct;
    QAction *italicAct;
    QAction *leftAlignAct;
    QAction *rightAlignAct;
    QAction *justifyAct;
    QAction *centerAct;
    QAction *setLineSpacingAct;
    QAction *setParagraphSpacingAct;
    QAction *aboutAct;
    QAction *aboutQtAct;
    QAction* m_search_action;

    TextEdit *textEdit;
    QCompleter *completer;

    int m_nRowNumber, m_nColNumber;
    kciSearchWindow* m_search_window;
};

#endif // MAINWINDOW_H
