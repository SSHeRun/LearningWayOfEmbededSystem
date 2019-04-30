#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->actionPrice,SIGNAL(triggered(bool)),this,SLOT(showPriceDlg()));
    connect(ui->actionSettings,SIGNAL(triggered(bool)),this,SLOT(showSettingDlg()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showPriceDlg()
{
    //QMessageBox::information(NULL,"hello","show a dialog here",QMessageBox::Yes | QMessageBox::No);
     /*
    PriceDialog priceDialog(this);
    priceDialog.exec();
    */
    PriceDlg.show();
}
void MainWindow::showSettingDlg()
{
    settingsDlg.show();
}

