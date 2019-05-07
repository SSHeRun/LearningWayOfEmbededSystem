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

    QSqlDatabase database = QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName("MyStock.db");

    QString create_sql="create table stockInfo (id int primary key,name varchar(30))";
    QString msg;
    if(!database.open())
     {
        msg="can not open database";
    }else
    {
        QSqlQuery sql_query;
        sql_query.prepare(create_sql);

        if(!sql_query.exec())
        {
            msg="table has been existed";
        }else
        {
            msg="create new table:";
        }
    }
    QMessageBox::information(NULL,"MyStock",msg,QMessageBox::Yes,QMessageBox::Yes);
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
    PriceDlg.LoadDataFormDatabase();
}
void MainWindow::showSettingDlg()
{
    settingsDlg.show();
}

