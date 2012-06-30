#include "ReplWidget.h"
#include <iostream>

ReplWidget::ReplWidget(QWidget *parent) : QPlainTextEdit(parent),
  userPrompt(QString("> ")),
  locked(false),
  historySkip(false)
{
  historyUp.clear();
  historyDown.clear();
  setLineWrapMode(NoWrap);
  insertPlainText(userPrompt);
}

/** Filter all key events. The keys are filtered and handled manually
  * in order to create a typical shell-like behaviour. For example
  * Up and Down arrows don't move the cursor, but allow the user to
  * browse the last commands that there launched.
  */

void ReplWidget::keyPressEvent(QKeyEvent *e) {
  // locked State: a command has been submitted but no result
  // has been received yet.
  if(locked) return;

  switch(e->key()) {
  case Qt::Key_Return:
    handleEnter();
    break;
  case Qt::Key_Backspace:
    handleLeft(e);
    break;
  case Qt::Key_Up:
    handleHistoryUp();
    break;
  case Qt::Key_Down:
    handleHistoryDown();
    break;
  case Qt::Key_Left:
    handleLeft(e);
    break;
  case Qt::Key_Home:
    handleHome();
    break;
  default:
    QPlainTextEdit::keyPressEvent(e);
    break;
  }
}

// Enter key pressed
void ReplWidget::handleEnter() {
  QString cmd = getCommand();

  if(0 < cmd.length()) {
    while(historyDown.count() > 0) {
      historyUp.push(historyDown.pop());
    }

    historyUp.push(cmd);
  }

  moveToEndOfLine();

  if(cmd.length() > 0) {
    locked = true;
    setFocus();
    insertPlainText("\n");
    emit command(cmd);
  } else {
    insertPlainText("\n");
    insertPlainText(userPrompt);
    ensureCursorVisible();
  }
}

// Result received
void ReplWidget::result(QString result) {
  insertPlainText(result);
  insertPlainText("\n");
  insertPlainText(userPrompt);
  ensureCursorVisible();
  locked = false;
}

// Append line but do not display prompt afterwards
void ReplWidget::append(QString text) {
  insertPlainText(text);
  insertPlainText("\n");
  ensureCursorVisible();
}

// Arrow up pressed
void ReplWidget::handleHistoryUp() {
  if(0 < historyUp.count()) {
    QString cmd = historyUp.pop();
    historyDown.push(cmd);

    clearLine();
    insertPlainText(cmd);
  }

  historySkip = true;
}

// Arrow down pressed
void ReplWidget::handleHistoryDown() {
  if(0 < historyDown.count() && historySkip) {
    historyUp.push(historyDown.pop());
    historySkip = false;
  }

  if(0 < historyDown.count()) {
    QString cmd = historyDown.pop();
    historyUp.push(cmd);

    clearLine();
    insertPlainText(cmd);
  } else {
    clearLine();
  }
}

void ReplWidget::clearLine() {
  QTextCursor c = this->textCursor();
  c.select(QTextCursor::LineUnderCursor);
  c.removeSelectedText();
  this->insertPlainText(userPrompt);
}

// Select and return the user-input (exclude the prompt)
QString ReplWidget::getCommand() const {
  QTextCursor c = this->textCursor();
  c.select(QTextCursor::LineUnderCursor);

  QString text = c.selectedText();
  text.remove(0, userPrompt.length());

  return text;
}

void ReplWidget::moveToEndOfLine() {
  QPlainTextEdit::moveCursor(QTextCursor::EndOfLine);
}

// The text cursor is not allowed to move beyond the
// prompt
void ReplWidget::handleLeft(QKeyEvent *event) {
  if(getIndex(textCursor()) > userPrompt.length()) {
    QPlainTextEdit::keyPressEvent(event);
  }
}

// Home (pos1) key pressed
void ReplWidget::handleHome() {
  QTextCursor c = textCursor();
  c.movePosition(QTextCursor::StartOfLine);
  c.movePosition(QTextCursor::Right, QTextCursor::MoveAnchor, userPrompt.length());
  setTextCursor(c);
}

// Solution for getting x and y position of the cursor. Found
// them in the Qt mailing list
int ReplWidget::getIndex (const QTextCursor &crQTextCursor ) {
  QTextBlock b;
  int column = 1;
  b = crQTextCursor.block();
  column = crQTextCursor.position() - b.position();
  return column;
}

void ReplWidget::setPrompt(const QString &prompt) {
  userPrompt = prompt;
  clearLine();
}

QString ReplWidget::prompt() const {
  return userPrompt;
}
