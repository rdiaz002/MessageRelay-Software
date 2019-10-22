#ifndef POPUP_H
#define POPUP_H

#include <QDialog>

namespace Ui {
class Popup;
}

class Popup : public QDialog
{
    Q_OBJECT

public:
    explicit Popup(QWidget *parent = nullptr);
    void closeEvent(QCloseEvent *) override;
    int exec() override;
    ~Popup();

private:
    Ui::Popup *ui;
    void autoPos();
};

#endif // POPUP_H
