#ifndef TEXTEDIT_H
#define TEXTEDIT_H
#include <QTextEdit>
#include <qplaintextedit.h>

 class QCompleter;

 class TextEdit : public QPlainTextEdit
 {
     Q_OBJECT

 public:
     TextEdit(QWidget *parent = 0);
     ~TextEdit();

     void setCompleter(QCompleter *c);
     QCompleter *completer() const;

     void lineNumberAreaPaintEvent(QPaintEvent *event);
     int lineNumberAreaWidth();

 protected:
     void keyPressEvent(QKeyEvent *e);
     void focusInEvent(QFocusEvent *e);

     void resizeEvent(QResizeEvent *event);

 private slots:
     void insertCompletion(const QString &completion);

     void updateLineNumberAreaWidth(int newBlockCount);
     void highlightCurrentLine();
     void updateLineNumberArea(const QRect &, int);

 private:
     QString textUnderCursor() const;

 private:
     QCompleter *c;

     QWidget *lineNumberArea;
 };

 class LineNumberArea : public QWidget
  {
  public:
      LineNumberArea(TextEdit *editor) : QWidget(editor) {
          textEdit = editor;
      }

      QSize sizeHint() const {
          return QSize(textEdit->lineNumberAreaWidth(), 0);
      }

  protected:
      void paintEvent(QPaintEvent *event) {
          textEdit->lineNumberAreaPaintEvent(event);
      }

  private:
      TextEdit *textEdit;
  };

#endif // TEXTEDIT_H
