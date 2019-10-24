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
    explicit MessageWidget(QWidget *parent = nullptr,QString number="", QString message="");
    ~MessageWidget();
signals:
    void openMessageWindow(MessageItem);
private:
    Ui::MessageWidget *ui;
    MessageItem data;
    static int id;
    void mousePressEvent(QMouseEvent *) override;
};

#endif // MESSAGEWIDGET_H
