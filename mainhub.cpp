#include "mainhub.h"
#include "ui_mainhub.h"
#include "dialog.h"
#include <QVBoxLayout>
MainHub::MainHub(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainHub) {
  ui->setupUi(this);
}

MainHub::~MainHub() { delete ui; }
