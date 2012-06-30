#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);  
  connect(ui->replWidget, SIGNAL(command(QString)), ui->replWidget, SLOT(result(QString)));
}

MainWindow::~MainWindow()
{
  delete ui;
}
