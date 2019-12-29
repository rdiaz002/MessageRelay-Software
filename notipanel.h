#ifndef NOTIPANEL_H
#define NOTIPANEL_H

#include <QFrame>
#include "messageutils.h"
#include <unordered_set>
#include "messagewidget.h"

namespace Ui {
class NotiPanel;
}

class NotiPanel : public QFrame
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
private slots:
    void on_pushButton_2_clicked();

private:
    Ui::NotiPanel *ui;
    QRect setDialogSize();
    std::unordered_set<MessageWidget *> * notifications;


};

#endif // NOTIPANEL_H
