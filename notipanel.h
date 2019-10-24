#ifndef NOTIPANEL_H
#define NOTIPANEL_H

#include <QDialog>
#include "messageutils.h"
#include <queue>
namespace Ui {
class NotiPanel;
}

class NotiPanel : public QDialog
{
    Q_OBJECT

public:
    explicit NotiPanel(QWidget *parent = nullptr);
    ~NotiPanel();
signals:
    void notificationClicked(MessageItem);

private:
    Ui::NotiPanel *ui;
    QRect setDialogSize();
    void operator<< (MessageItem);
    std::queue<MessageItem> notifications;


};

#endif // NOTIPANEL_H
