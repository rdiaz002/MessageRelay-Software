#ifndef MESSAGEWINDOW_H
#define MESSAGEWINDOW_H

#include <QDialog>

namespace Ui {
class MessageWindow;
}

class MessageWindow : public QDialog
{
    Q_OBJECT

public:
    explicit MessageWindow(QStringList * msgs,QWidget *parent = nullptr);
    ~MessageWindow();
    void paintEvent(QPaintEvent *) override;
private:
    Ui::MessageWindow *ui;
    QStringList * msgList;
};

#endif // MESSAGEWINDOW_H
