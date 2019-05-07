#ifndef SETTINGSDLG_H
#define SETTINGSDLG_H

#include <QDialog>
#include <ftpclient.h>

#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>

namespace Ui {
class SettingsDlg;
}

class SettingsDlg : public QDialog
{
    Q_OBJECT

public slots:
    void DownloadStockFile();
    void SavetoDatabase();

public:
    explicit SettingsDlg(QWidget *parent = 0);
    ~SettingsDlg();

private:
    Ui::SettingsDlg *ui;

    FtpClient ftp;
};

#endif // SETTINGSDLG_H
