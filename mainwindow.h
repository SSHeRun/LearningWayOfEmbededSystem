#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "pricedialog.h"
#include "settingsdlg.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT


public slots:

    void showPriceDlg();
    void showSettingDlg();

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    PriceDialog PriceDlg;
    SettingsDlg settingsDlg;
};

#endif // MAINWINDOW_H
