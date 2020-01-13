#ifndef MAINHUB_H
#define MAINHUB_H

#include <QMainWindow>

namespace Ui {
class MainHub;
}

class MainHub : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainHub(QWidget *parent = nullptr);
    ~MainHub();

private:
    Ui::MainHub *ui;
};

#endif // MAINHUB_H
