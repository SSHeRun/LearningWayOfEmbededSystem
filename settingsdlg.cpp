#include "settingsdlg.h"
#include "ui_settingsdlg.h"
#include <QMessageBox>

SettingsDlg::SettingsDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsDlg)
{
    ui->setupUi(this);
    connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(DownloadStockFile()));
}

SettingsDlg::~SettingsDlg()
{
    delete ui;
}
void SettingsDlg::DownloadStockFile()
{
    if(QMessageBox::Yes == QMessageBox::information(NULL,"Mystock","download stock file",QMessageBox::Yes , QMessageBox::Yes))
     {
        ftp.FtpSetHostPort("192.168.3.100");
        ftp.FtpSetUserInfor("jiaoxue","123456");
        ftp.FtpGet("./ftp-data-center/600000.txt","/stockdata/600000.txt");

        QMessageBox::information(NULL,"Mystock","download succeed",QMessageBox::Yes , QMessageBox::Yes);
    }
}
