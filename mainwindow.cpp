#include "mainwindow.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QProcess>
#include <qset.h>
#include <qstringlist.h>
#include <qstringlistmodel.h>
#include <ctype.h>
#include <qcompleter.h>
#include <QtGui>
#include "highlighter.h"
#include "textedit.h"
#include <qabstractitemmodel.h>

Highlighter *MyHighlighter;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{

    m_bChanged = false;

    textEdit = new TextEdit();
    completer = new QCompleter(this);
    completer->setModel(modelFromFile("completer.lcp"));
    completer->setModelSorting(QCompleter::CaseInsensitivelySortedModel);
    completer->setCaseSensitivity(Qt::CaseInsensitive);
    completer->setWrapAround(false);
    textEdit->setCompleter(completer);

    setCentralWidget(textEdit);
    MyHighlighter  = new Highlighter(textEdit->document());
    textEdit->setFont(QFont("Ubuntu Mono", 13));
    textEdit->setTabStopWidth(40);
    createActions();
    createMenus();

    m_search_window = new kciSearchWindow(this);
    m_search_window->hide();

}

MainWindow::~MainWindow()
{
}

QAbstractItemModel* MainWindow::modelFromFile(const QString& fileName)
 {
     QFile file(fileName);
     if (!file.open(QFile::ReadOnly))
         return new QStringListModel(completer);

 #ifndef QT_NO_CURSOR
     QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
 #endif
     QStringList words;

     while (!file.atEnd()) {
         QByteArray line = file.readLine();
         if (!line.isEmpty())
             words << line.trimmed();
     }

 #ifndef QT_NO_CURSOR
     QApplication::restoreOverrideCursor();
 #endif
     return new QStringListModel(words, completer);
 }

void MainWindow::on_action_New_triggered()
{
    if(m_bChanged)
    {
        if(QMessageBox::question(this, "New", "Save file?",
                                 QMessageBox::Yes | QMessageBox::No,
                                 QMessageBox::Yes) == QMessageBox::Yes)
        {
            SaveFileAs();
        }
    }
    textEdit->setPlainText("");

    //textEdit->setText("");
}

void MainWindow::on_action_Open_triggered()
{
    OpenFile();
}

void MainWindow::on_action_Save_triggered()
{
    SaveFile();
}

void MainWindow::on_action_Save_As_triggered()
{
    SaveFileAs();
}

void MainWindow::on_action_Exit_triggered()
{
    if(m_bChanged)
    {
        if(QMessageBox::question(this, "Exit", "Save file?",
                              QMessageBox::Yes | QMessageBox::No,
                              QMessageBox::Yes) == QMessageBox::Yes)
        {
            SaveFileAs();
        }
    }
    qApp->quit();
}

void MainWindow::OpenFile()
{
    QString strFileName = QFileDialog::getOpenFileName(this, tr("Open File"), ".", tr("C++ Files(*.cpp)"));
    if(!strFileName.isEmpty())
    {
        if(QFile::exists(strFileName))
        {
            QFile file(strFileName);
            if(file.open(QFile::ReadOnly))
            {
                SetFileInfo(strFileName);
                QByteArray data = file.readAll();
                textEdit->setPlainText(QObject::tr(data));
                //textEdit->setText(QObject::tr(data));
                setWindowTitle(m_strCurFileName+" - Light Cpp");
            }
            else
            {
                QMessageBox::warning(this, "Open", "Failed to open this file.");
            }
        }
        else
        {
            QMessageBox::warning(this, "Open", "File not exsits.");
        }
    }
    m_bChanged = false;
}
void MainWindow::undo()
{
    textEdit->undo();

}
void MainWindow::print()
{

}

void MainWindow::redo()
{
textEdit->redo();
}

void MainWindow::cut()
{
textEdit->cut();
}

void MainWindow::copy()
{
textEdit->copy();
}

void MainWindow::paste()
{
textEdit->paste();
}

void MainWindow::SaveFile()
{
    if(m_strCurFileDir.isEmpty())
    { SaveFileAs(); }
    else
    {
        QFile file(m_strCurFileDir);
        file.open(QFile::WriteOnly);
        QTextStream out(&file);
        out << textEdit->toPlainText();
        setWindowTitle(m_strCurFileName + " - Light Cpp");
    }
    m_bChanged = false;
}

void MainWindow::SaveFileAs()
{
    QString strFileName = QFileDialog::getSaveFileName(this, tr("Save As..."), ".", tr("Cpp Files(*.cpp)"));
    if(!strFileName.isEmpty())
    {
        if(!strFileName.endsWith(".cpp", Qt::CaseInsensitive))
        {strFileName += ".cpp"; }
        SetFileInfo(strFileName);
        SaveFile();
    }
}

void MainWindow::SetFileInfo(QString strFileName)
{
    int nPos = strFileName.lastIndexOf('/');
    m_strCurFileDir = strFileName;
    m_strCurFileName = strFileName.mid(nPos + 1, strFileName.size() - nPos - 1);
}

void MainWindow::on_action_About_triggered()
{
    QString strAbout = "About C++ Code Editor:\n";
    QMessageBox::information(this, "About", strAbout, QMessageBox::Yes);
}
void MainWindow::sellectAll()
{
    textEdit->selectAll();
}

void MainWindow::on_textEdit_textChanged()
{
    m_bChanged = true;
    const QTextCursor pCursor = textEdit->textCursor();
    m_nRowNumber = pCursor.blockNumber() + 1;
    m_nColNumber = pCursor.columnNumber() + 1;
    int nLen = textEdit->toPlainText().size();
    QString strInfo = "Total: " + QString::number(nLen, 8) + "  Row: " + QString::number(m_nRowNumber, 8) + "  Col: " + QString::number(m_nColNumber, 8);
    statusBar()->showMessage(strInfo);
}
void MainWindow::italic()
{

}
void MainWindow::bold()
{

}
void MainWindow::justify()
{

}
void MainWindow::setLineSpacing()
{

}

void MainWindow::setParagraphSpacing()
{

}
void MainWindow::leftAlign()
{

}
void MainWindow::rightAlign()
{

}
void MainWindow::center()
{

}

void MainWindow::on_action_search_triggered()
{
    m_search_window->show();
}

void MainWindow::createActions()
{
    m_search_action = new QAction(tr("&Search"), this);
    //newAct->setShortcuts(QKeySequence::New);
    m_search_action->setStatusTip(tr("Search"));
    connect(m_search_action, SIGNAL(triggered()), this, SLOT(on_action_search_triggered()));

    newAct = new QAction(tr("&New"), this);
    newAct->setShortcuts(QKeySequence::New);
    newAct->setStatusTip(tr("Create a new file"));
    connect(newAct, SIGNAL(triggered()), this, SLOT(on_action_New_triggered()));

    openAct = new QAction(tr("&Open..."), this);
    openAct->setShortcuts(QKeySequence::Open);
    openAct->setStatusTip(tr("Open an existing file"));
    connect(openAct, SIGNAL(triggered()), this, SLOT(on_action_Open_triggered()));

    saveAct = new QAction(tr("&Save"), this);
    saveAct->setShortcuts(QKeySequence::Save);
    saveAct->setStatusTip(tr("Save the document to disk"));
    connect(saveAct, SIGNAL(triggered()), this, SLOT(on_action_Save_triggered()));

    printAct = new QAction(tr("&Print..."), this);
    printAct->setShortcuts(QKeySequence::Print);
    printAct->setStatusTip(tr("Print the document"));
    connect(printAct, SIGNAL(triggered()), this, SLOT(print()));

    exitAct = new QAction(tr("E&xit"), this);
    exitAct->setShortcuts(QKeySequence::Quit);
    exitAct->setStatusTip(tr("Exit the application"));
    connect(exitAct, SIGNAL(triggered()), this, SLOT(on_action_Exit_triggered()));

    undoAct = new QAction(tr("&Undo"), this);
    undoAct->setShortcuts(QKeySequence::Undo);
    undoAct->setStatusTip(tr("Undo the last operation"));
    connect(undoAct, SIGNAL(triggered()), this, SLOT(undo()));

    redoAct = new QAction(tr("&Redo"), this);
    redoAct->setShortcuts(QKeySequence::Redo);
    redoAct->setStatusTip(tr("Redo the last operation"));
    connect(redoAct, SIGNAL(triggered()), this, SLOT(redo()));

    cutAct = new QAction(tr("Cu&t"), this);
    cutAct->setShortcuts(QKeySequence::Cut);
    cutAct->setStatusTip(tr("Cut the current selection's contents to the "
                            "clipboard"));
    connect(cutAct, SIGNAL(triggered()), this, SLOT(cut()));

    copyAct = new QAction(tr("&Copy"), this);
    copyAct->setShortcuts(QKeySequence::Copy);
    copyAct->setStatusTip(tr("Copy the current selection's contents to the "
                             "clipboard"));
    connect(copyAct, SIGNAL(triggered()), this, SLOT(copy()));

    pasteAct = new QAction(tr("&Paste"), this);
    pasteAct->setShortcuts(QKeySequence::Paste);
    pasteAct->setStatusTip(tr("Paste the clipboard's contents into the current "
                              "selection"));
    connect(pasteAct, SIGNAL(triggered()), this, SLOT(paste()));
    sellectAllAct = new QAction(tr("&Sellect All"),this);
    sellectAllAct->setShortcut(QKeySequence::SelectAll);
    sellectAllAct->setStatusTip(tr("Sellect All"));
    connect(sellectAllAct,SIGNAL(triggered()),this,SLOT(sellectAll()));

    boldAct = new QAction(tr("&Bold"), this);
    boldAct->setCheckable(true);
    boldAct->setShortcut(QKeySequence::Bold);
    boldAct->setStatusTip(tr("Make the text bold"));
    connect(boldAct, SIGNAL(triggered()), this, SLOT(bold()));

    QFont boldFont = boldAct->font();
    boldFont.setBold(true);
    boldAct->setFont(boldFont);


    italicAct = new QAction(tr("&Italic"), this);
    italicAct->setCheckable(true);
    italicAct->setShortcut(QKeySequence::Italic);
    italicAct->setStatusTip(tr("Make the text italic"));
    connect(italicAct, SIGNAL(triggered()), this, SLOT(italic()));

    QFont italicFont = italicAct->font();
    italicFont.setItalic(true);
    italicAct->setFont(italicFont);

    setLineSpacingAct = new QAction(tr("Set &Line Spacing..."), this);
    setLineSpacingAct->setStatusTip(tr("Change the gap between the lines of a "
                                       "paragraph"));
    connect(setLineSpacingAct, SIGNAL(triggered()), this, SLOT(setLineSpacing()));

    setParagraphSpacingAct = new QAction(tr("Set &Paragraph Spacing..."), this);
    setLineSpacingAct->setStatusTip(tr("Change the gap between paragraphs"));
    connect(setParagraphSpacingAct, SIGNAL(triggered()),
            this, SLOT(setParagraphSpacing()));

    aboutAct = new QAction(tr("&About"), this);
    aboutAct->setStatusTip(tr("Show the application's About box"));
    connect(aboutAct, SIGNAL(triggered()), this, SLOT(on_action_About_triggered()));

    aboutQtAct = new QAction(tr("About &Qt"), this);
    aboutQtAct->setStatusTip(tr("Show the Qt library's About box"));
    connect(aboutQtAct, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
    connect(aboutQtAct, SIGNAL(triggered()), this, SLOT(aboutQt()));

    leftAlignAct = new QAction(tr("&Left Align"), this);
    leftAlignAct->setCheckable(true);
    leftAlignAct->setShortcut(tr("Ctrl+L"));
    leftAlignAct->setStatusTip(tr("Left align the selected text"));
    connect(leftAlignAct, SIGNAL(triggered()), this, SLOT(leftAlign()));

    rightAlignAct = new QAction(tr("&Right Align"), this);
    rightAlignAct->setCheckable(true);
    rightAlignAct->setShortcut(tr("Ctrl+R"));
    rightAlignAct->setStatusTip(tr("Right align the selected text"));
    connect(rightAlignAct, SIGNAL(triggered()), this, SLOT(rightAlign()));

    justifyAct = new QAction(tr("&Justify"), this);
    justifyAct->setCheckable(true);
    justifyAct->setShortcut(tr("Ctrl+J"));
    justifyAct->setStatusTip(tr("Justify the selected text"));
    connect(justifyAct, SIGNAL(triggered()), this, SLOT(justify()));

    centerAct = new QAction(tr("&Center"), this);
    centerAct->setCheckable(true);
    centerAct->setShortcut(tr("Ctrl+E"));
    centerAct->setStatusTip(tr("Center the selected text"));
    connect(centerAct, SIGNAL(triggered()), this, SLOT(center()));

    alignmentGroup = new QActionGroup(this);
    alignmentGroup->addAction(leftAlignAct);
    alignmentGroup->addAction(rightAlignAct);
    alignmentGroup->addAction(justifyAct);
    alignmentGroup->addAction(centerAct);
    leftAlignAct->setChecked(true);
}

void MainWindow::createMenus()
{
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(newAct);
    fileMenu->addAction(openAct);
    fileMenu->addAction(saveAct);
    fileMenu->addAction(printAct);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAct);
    fileMenu->addAction(m_search_action);


    editMenu = menuBar()->addMenu(tr("&Edit"));
    editMenu->addAction(undoAct);
    editMenu->addAction(redoAct);
    editMenu->addSeparator();
    editMenu->addAction(cutAct);
    editMenu->addAction(copyAct);
    editMenu->addAction(pasteAct);
    editMenu->addSeparator();
    editMenu->addAction(sellectAllAct);
    editMenu->addSeparator();

    helpMenu = menuBar()->addMenu(tr("&Help"));
    helpMenu->addAction(aboutAct);
    helpMenu->addAction(aboutQtAct);

    formatMenu = editMenu->addMenu(tr("&Format"));
    formatMenu->addAction(boldAct);
    formatMenu->addAction(italicAct);
    formatMenu->addSeparator()->setText(tr("Alignment"));
    formatMenu->addAction(leftAlignAct);
    formatMenu->addAction(rightAlignAct);
    formatMenu->addAction(justifyAct);
    formatMenu->addAction(centerAct);
    formatMenu->addSeparator();
    formatMenu->addAction(setLineSpacingAct);
    formatMenu->addAction(setParagraphSpacingAct);
}



