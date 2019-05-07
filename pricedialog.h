#ifndef PRICEDIALOG_H
#define PRICEDIALOG_H

#include <QDialog>

#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>

namespace Ui {
class PriceDialog;
}

class PriceDialog : public QDialog
{
    Q_OBJECT
public slots:
    void ShowPrice();
public:
    explicit PriceDialog(QWidget *parent = 0);
    ~PriceDialog();
    void paintEvent(QPaintEvent * p);
    void LoadDataFormDatabase();//add DB function
private:
    bool ReadDataFromFile(QString code);
    float StockPriceVolume[100][7];
    int ValidDayNum;

private:
    Ui::PriceDialog *ui;

};

#endif // PRICEDIALOG_H
