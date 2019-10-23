#ifndef NOTIPANEL_H
#define NOTIPANEL_H

#include <QDialog>

namespace Ui {
class NotiPanel;
}

class NotiPanel : public QDialog
{
    Q_OBJECT

public:
    explicit NotiPanel(QWidget *parent = nullptr);
    ~NotiPanel();

private:
    Ui::NotiPanel *ui;
    QRect setDialogSize();
};

#endif // NOTIPANEL_H
