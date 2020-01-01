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
    explicit MessageWindow(QString num,QStringList * msgs,QWidget *parent = nullptr);
    ~MessageWindow();
    void updateMessages();
signals:
    void sendMessage(QByteArray data);
    void closeWindow(QString number);
private slots:
    void on_sendButton_clicked();
    void slideChange(int, int);
    void on_MessageWindow_finished(int result);

private:
    struct EnterListener: public QObject{
        protected:
        bool eventFilter(QObject *, QEvent *);
        public:
        MessageWindow * parent;
    };

    EnterListener * listener;
    Ui::MessageWindow *ui;
    QStringList * msgList;
    QScrollBar* vert;
    QString number;
};

#endif // MESSAGEWINDOW_H
