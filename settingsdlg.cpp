#include "settingsdlg.h"
#include "ui_settingsdlg.h"
#include <QMessageBox>

SettingsDlg::SettingsDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsDlg)
{
    ui->setupUi(this);
    connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(DownloadStockFile()));
    connect(ui->pushButton_2,SIGNAL(clicked()),this,SLOT(SavetoDatabase()));
/*
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
    */

}

SettingsDlg::~SettingsDlg()
{
    delete ui;
}
void SettingsDlg::DownloadStockFile()
{
    if(QMessageBox::Yes == QMessageBox::information(NULL,"Mystock","download stock file",QMessageBox::Yes |QMessageBox::No))
     {
        ftp.FtpSetHostPort("192.168.3.100");
        ftp.FtpSetUserInfor("jiaoxue","123456");
        ftp.FtpGet("./ftp-data-center/600000.txt","/stockdata/600000.txt");

        QMessageBox::information(NULL,"Mystock","download succeed",QMessageBox::Yes , QMessageBox::Yes);
    }
}
void SettingsDlg::SavetoDatabase()
{
    if(QMessageBox::Yes==QMessageBox::information(NULL,"MyStock","Save to SQlite Data",QMessageBox::Yes|QMessageBox::No))
    {
        bool flag = true;
        QSqlQuery sql_query;
        QString insert_sql = "insert into stockInfo values (?,?)";
        sql_query.prepare(insert_sql);
        sql_query.addBindValue("600000");
        sql_query.addBindValue("600000");
        if(!sql_query.exec())
        {
            flag=false;
        }

        insert_sql = "insert into stockInfo values (?,?)";
        sql_query.prepare(insert_sql);
        sql_query.addBindValue("600004");
        sql_query.addBindValue("600004");
        if(!sql_query.exec())
        {
            flag=false;
        }

        insert_sql = "insert into stockInfo values (?,?)";
        sql_query.prepare(insert_sql);
        sql_query.addBindValue("600006");
        sql_query.addBindValue("600006");
        if(!sql_query.exec())
        {
            flag=false;
        }

        if(!flag)
        {
            QMessageBox::information(NULL,"MyStock","some item insert failed",QMessageBox::Yes,QMessageBox::Yes);
        }else
        {
             QMessageBox::information(NULL,"MyStock","all item insert finished",QMessageBox::Yes,QMessageBox::Yes);
        }

    }
}
