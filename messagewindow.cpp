#include "messagewindow.h"
#include "ui_messagewindow.h"
#include <QDebug>
#include <QLabel>
#include <QKeyEvent>
// TODO: Update Message Window Styling.

MessageWindow::MessageWindow(QString num, QStringList *msgList, QWidget *parent)
    : QDialog(parent), ui(new Ui::MessageWindow), number(num),
      msgList(msgList) {
  ui->setupUi(this);
  this->setWindowTitle(number);
  listener = new EnterListener();
  listener->parent = this;
  ui->textBox->installEventFilter(listener);
  ui->chatBox->setAlignment(Qt::AlignTop);
  ui->chatBox->setSizeConstraint(QLayout::SetDefaultConstraint);
  ui->chatBox->setColumnStretch(0, 1);
  ui->chatBox->setColumnStretch(2, 1);
  ui->chatBox->setColumnStretch(1, 1);
  vert = ui->scrollArea->verticalScrollBar();

  connect(vert, &QAbstractSlider::rangeChanged, this,
          &MessageWindow::slideChange);
  updateMessages();
}

MessageWindow::~MessageWindow() { delete ui; }

void MessageWindow::updateMessages() {

  QLayoutItem *child;
  while ((child = ui->chatBox->takeAt(0)) != nullptr) {
    ui->chatBox->removeWidget(child->widget());
    delete child->widget();
    delete child;
  }

  for (auto i : *msgList) {
    QLabel *msg = new QLabel(i.mid(1));
    msg->setAlignment(Qt::AlignLeft);
    msg->setWordWrap(true);
    msg->setContentsMargins(10, 2, 10, 2);
    msg->setMaximumWidth(static_cast<int>(this->width() * 0.30));
    msg->setMinimumHeight(20);
    msg->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    msg->adjustSize();
    if (i[0] == 0x04) {
      msg->setProperty("sender", true);
      ui->chatBox->addWidget(msg, ui->chatBox->rowCount(), 0);

    } else {
      msg->setProperty("reciever", true);
      ui->chatBox->addWidget(msg, ui->chatBox->rowCount(), 2);
    }
  }
}

void MessageWindow::on_sendButton_clicked() {
  // TODO: Fix weird sending bug when long messages are typed.
  QString msg = ui->textBox->toPlainText();
  msgList->push_back(0x05 + msg);
  QByteArray data;
  data += this->number;
  data += 0x02;
  data += msg;
  data += '\n';
  emit sendMessage(data);
  ui->textBox->clear();
  updateMessages();
}

void MessageWindow::slideChange(int, int) { vert->setValue(vert->maximum()); }

void MessageWindow::on_MessageWindow_finished(int result) {
  emit closeWindow(number);
}

bool MessageWindow::EnterListener::eventFilter(QObject *obj, QEvent *event) {
  if (event->type() == QEvent::KeyPress) {
    QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
    if (parent != nullptr && keyEvent->key() == Qt::Key_Return &&
        (keyEvent->modifiers() ^ Qt::ShiftModifier)) { // make sure parent is
                                                       // not null and shift is
                                                       // not held.
      parent->on_sendButton_clicked();
      return true;
    }
  }
  return QObject::eventFilter(obj, event);
}
