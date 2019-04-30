#ifndef SETTINGSDLG_H
#define SETTINGSDLG_H

#include <QDialog>
#include <ftpclient.h>

namespace Ui {
class SettingsDlg;
}

class SettingsDlg : public QDialog
{
    Q_OBJECT

public slots:
    void DownloadStockFile();

public:
    explicit SettingsDlg(QWidget *parent = 0);
    ~SettingsDlg();

private:
    Ui::SettingsDlg *ui;

    FtpClient ftp;
};

#endif // SETTINGSDLG_H
