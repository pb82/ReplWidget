#ifndef TERMINALWIDGET_H
#define TERMINALWIDGET_H

#include <QtGui/QPlainTextEdit>
#include <QKeyEvent>
#include <QTextBlock>
#include <QTextCursor>
#include <QTextDocumentFragment>
#include <QStack>

class ReplWidget : public QPlainTextEdit
{
  Q_OBJECT

public:
  ReplWidget(QWidget *parent = 0);

  QString prompt() const;
  void setPrompt(const QString &prompt);

protected:
  void keyPressEvent(QKeyEvent *e);

  // Do not handle other events
  void mousePressEvent(QMouseEvent *)       { /* Ignore */ }
  void mouseDoubleClickEvent(QMouseEvent *) { /* Ignore */ }
  void mouseMoveEvent(QMouseEvent *)        { /* Ignore */ }
  void mouseReleaseEvent(QMouseEvent *)     { /* Ignore */ }

private:
  void handleLeft(QKeyEvent *event);
  void handleEnter();
  void handleHistoryUp();
  void handleHistoryDown();
  void handleHome();

  void moveToEndOfLine();
  void clearLine();
  QString getCommand() const;

  int getIndex (const QTextCursor &crQTextCursor );

  QString userPrompt;
  QStack<QString> historyUp;
  QStack<QString> historyDown;
  bool locked, historySkip;

// The command signal is fired when a user input is entered
signals:
  void command(QString command);

// The result slot displays the result of a command in the terminal
public slots:
  void result(QString result);
  void append(QString text);
};

#endif
