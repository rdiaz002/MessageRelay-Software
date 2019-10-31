#ifndef MESSAGEWINDOW_H
#define MESSAGEWINDOW_H

#include <QDialog>
#include <QScrollBar>
namespace Ui {
class MessageWindow;
}

class MessageWindow : public QDialog
{
    Q_OBJECT

public:
    explicit MessageWindow(QStringList * msgs,QWidget *parent = nullptr);
    ~MessageWindow();
    void updateMessages();
private slots:
    void on_sendButton_clicked();
    void slideChange(int, int);
private:
    Ui::MessageWindow *ui;
    QStringList * msgList;
    QScrollBar* vert;
};

#endif // MESSAGEWINDOW_H
