#ifndef CUSTOMICON_H
#define CUSTOMICON_H

#include <QDialog>

namespace Ui {
class CustomIcon;
}

class CustomIcon : public QDialog
{
    Q_OBJECT

public:
    explicit CustomIcon(QWidget *parent = nullptr);
    ~CustomIcon();

private:
    Ui::CustomIcon *ui;
    QRect setDialogLocation();
};

#endif // CUSTOMICON_H
