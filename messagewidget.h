#ifndef MESSAGEWIDGET_H
#define MESSAGEWIDGET_H

#include <QFrame>
#include "messageutils.h"
#include<QMouseEvent>
namespace Ui {
class MessageWidget;
}

class MessageWidget : public QFrame
{
    Q_OBJECT

public:
    explicit MessageWidget(MessageItem & item,QWidget *parent = nullptr);
    ~MessageWidget();
    MessageItem data;
signals:
    void openMessageWindow(MessageWidget *);
private:
    Ui::MessageWidget *ui;
    static unsigned int id;
    void mousePressEvent(QMouseEvent *) override;
};

#endif // MESSAGEWIDGET_H
