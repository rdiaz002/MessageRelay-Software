#ifndef NOTIPANEL_H
#define NOTIPANEL_H

#include <QDialog>
#include "messageutils.h"
#include <unordered_set>
#include "messagewidget.h"

namespace Ui {
class NotiPanel;
}

class NotiPanel : public QDialog
{
    Q_OBJECT

public:
    explicit NotiPanel(QWidget *parent = nullptr);
    ~NotiPanel();
     void operator<< (MessageItem);
public slots:
    void notificationClicked(MessageWidget *);
signals:
    void openMessageWindow(MessageWidget*);
private:
    Ui::NotiPanel *ui;
    QRect setDialogSize();
    std::unordered_set<MessageWidget *> * notifications;


};

#endif // NOTIPANEL_H
