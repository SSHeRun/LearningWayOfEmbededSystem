#include "pricedialog.h"
#include "ui_pricedialog.h"
#include <QFile>
#include <QMessageBox>
#include <QTextStream>
#include <QPainter>
#include <QPen>

PriceDialog::PriceDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PriceDialog)
{
    ui->setupUi(this);
    ui->comboBox->addItem("600000");
    ui->comboBox->addItem("600004");
    ui->comboBox->addItem("600006");

    connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(ShowPrice()));

    ValidDayNum = -1;
}

PriceDialog::~PriceDialog()
{
    delete ui;
}

void PriceDialog::ShowPrice()
{
    this->showMaximized();
    QString code = ui->comboBox->currentText();
    ReadDataFromFile(code);
    this->repaint();
}
bool PriceDialog::ReadDataFromFile(QString code)
{
    QString filename;
    filename = "/stockdata/"+code+".txt";
    QFile f(filename);
    //QFile f("/stockdata/600000.txt");
    if(!f.open(QIODevice::ReadOnly | QIODevice::Text)){
        QMessageBox::information(NULL,"stock","fail",QMessageBox::Yes | QMessageBox::No);
        return false;
    }

    QTextStream txtInput(&f);
    QString lineStr;
    QString s;
    int maxline = 0;
    while(!txtInput.atEnd()&&maxline<100)
    {
        lineStr = txtInput.readLine();

        StockPriceVolume[maxline][0]=maxline;
        s = lineStr.section(',',1,1);
        StockPriceVolume[maxline][1]=s.toFloat();
        s = lineStr.section(',',2,2);
        StockPriceVolume[maxline][2]=s.toFloat();
        s = lineStr.section(',',3,3);
        StockPriceVolume[maxline][3]=s.toFloat();
        s = lineStr.section(',',4,4);
        StockPriceVolume[maxline][4]=s.toFloat();
        s = lineStr.section(',',5,5);
        StockPriceVolume[maxline][5]=s.toFloat();
        s = lineStr.section(',',6,6);
        StockPriceVolume[maxline][6]=s.toFloat();

        maxline++;
    }

    ValidDayNum = maxline;
    f.close();
    return true;
}
void PriceDialog::paintEvent(QPaintEvent * p)
{
    QPainter painter(this);
    QPen pen;
    int i,j;

    if(ValidDayNum>0)
    {
        float minvalue = 100000;
        float maxvalue = -100000;
        int height,width;
        float daystep;
        float pointstep;
        int margin = 5;

        float maxvolumevalue = -100000;
        float volumestep;

        for(i=0;i<ValidDayNum;i++)
        {
            for(j=1;j<5;j++)
            {
                if(minvalue>StockPriceVolume[i][j])
                {
                    minvalue=StockPriceVolume[i][j];
                }
                if(maxvalue<StockPriceVolume[i][j])
                {
                    maxvalue=StockPriceVolume[i][j];
                }
            }
            if(maxvolumevalue<StockPriceVolume[i][5])
            {
                maxvolumevalue=StockPriceVolume[i][5];
            }
        }

        height = this->height()*2/3-100;

        width = this->width();
        daystep=(width - 2 * margin)/ValidDayNum;
        pointstep=(height- 2*margin)/(maxvalue-minvalue);

        volumestep=this->height()/3/maxvolumevalue;

        //pen.setColor(Qt::darkCyan);
        pen.setWidth(1);
        //painter.setPen(pen);

        painter.setBrush(QBrush(Qt::black,Qt::SolidPattern));
        painter.drawRect(margin,
                         100,
                         this->width()-margin,
                         this->height()-margin);

        for(i=0;i<ValidDayNum;i++)
        {
           /* painter.drawLine((width-margin)-daystep*i,
                             (StockPriceVolume[i][4]-minvalue)*pointstep,
                            (width-margin)-daystep*(i+1),
                            (StockPriceVolume[i+1][4]-minvalue)*pointstep);
                            */
            float rect_top,rect_bottom;
            rect_top=StockPriceVolume[i][1]>StockPriceVolume[i][4]?StockPriceVolume[i][1]:StockPriceVolume[i][4];
            rect_bottom=StockPriceVolume[i][1]<StockPriceVolume[i][4]?StockPriceVolume[i][1]:StockPriceVolume[i][4];
            bool red;
            red = StockPriceVolume[i][1]<StockPriceVolume[i][4];

            if(red)
            {
                pen.setColor(Qt::darkRed);
            }else
            {
                pen.setColor(Qt::darkGreen);
            }

            painter.setPen(pen);

            painter.drawLine((width-margin)-daystep*i,
                            height-(rect_top-minvalue)*pointstep+100,
                            (width-margin)-daystep*i,
                            height-(StockPriceVolume[i][2]-minvalue)*pointstep+100);

            if(red)
            {
                painter.setBrush(Qt::NoBrush);
            }else
            {
                painter.setBrush(QBrush(Qt::green,Qt::SolidPattern));
            }

            painter.drawRect((width-margin)-daystep*i-2,
                            height-(rect_bottom-minvalue)*pointstep+100,
                            5,
                           (rect_bottom-rect_top)*pointstep);                                                      


            painter.drawLine((width-margin)-daystep*i,
                            height-(rect_bottom-minvalue)*pointstep+100,
                            (width-margin)-daystep*i,
                            height- (StockPriceVolume[i][3]-minvalue)*pointstep+100);

            painter.drawRect((width-margin)-daystep*i-2,
                             this->height()-margin-StockPriceVolume[i][5]*volumestep,
                             5,
                             StockPriceVolume[i][5]*volumestep);

        }
    }
}
