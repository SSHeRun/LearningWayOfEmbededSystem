#ifndef BORAD_H
#define BORAD_H

#include <QMainWindow>
#include <QPainter>
#include <QMouseEvent>
#include <QVector>
#include <QDebug>
#include <QPushButton>
#include <QLabel>

#include "Stone.h"
#include "Step.h"

class Borad : public QMainWindow
{
    Q_OBJECT

public:
    Borad(QWidget *parent = 0);

    QPushButton reopen;     //重开按钮
    QPushButton backBut;    //悔棋按钮

    QLabel win;

    bool fullscreen;        //是否全屏
    Stone _s[32];           //32颗棋子
    int _r;                 //棋子半径
    int _selectid;          //是否被选中
    bool _bRedTrue;         //是否为红棋
    bool _bSide;            //红方
    QVector<Step*> _steps;  //记录走棋
    void init();

    /*draw function*/
    virtual void paintEvent(QPaintEvent *)override;
    void drawBoard(QPainter &painter);                  //绘制棋盘
    void drawStone(QPainter &painter);                  //绘制全部棋子
    void drawStone(QPainter &painter,int id);           //绘制棋子

    /*function coordinate*/
    QPoint center(int id);                              //根据棋子id返回棋子坐标
    QPoint center(int row,int col);                     //根据棋盘位置返回窗体像素坐标
    bool getClickRowCol(QPoint &pt,int &row,int &col);  //判断是否点中棋子

    int getStoneId(int row, int col);                   //获取棋子id
    bool isDead(int id);                                //是否被吃
    bool sameColorStone(int id1, int id2);              //判断是否是同色棋子
    bool red(int id);                                   //获取棋子颜色
    void killStone(int id);                             //棋子被吃掉
    void reliveStone(int id);                           //恢复被吃棋子
    void moveStone(int moveid, int row, int col);       //移动棋子并换方

    /*move stone*/
    virtual void mouseReleaseEvent(QMouseEvent *);      //鼠标点击松开事件
    void click(QPoint pt);                              //点击落子点
    virtual void click(int id, int row, int col);       //判断是否选中棋子
    void trySelectStone(int id);                        //判断棋子颜色
    void tryMoveStone(int killid,int row,int col);      //试着移动棋子
    void moveStone(int moveid, int killid, int row, int col);   //移动棋子
    void saveStep(int moveid, int killid, int row, int col, QVector<Step*>& steps);//保存走棋
    void backs();                                        //悔棋
    void backOne();                                     //悔一步棋
    void back(Step *step);

    /*rule*/
    bool canSelect(int id);
    bool canMove(int moveid, int killid, int row, int col);//棋子走法选择器
    bool canMoveJiang(int moveid, int killid, int row, int col);
    bool canMoveShi(int moveid, int killid, int row, int col);
    bool canMoveXiang(int moveid, int killid, int row, int col);
    bool canMoveMa(int moveid, int killid, int row, int col);
    bool canMoveChe(int moveid, int killid, int row, int col);
    bool canMovePao(int moveid, int killid, int row, int col);
    bool canMoveBing(int moveid, int killid, int row, int col);

    int relation(int row1, int col1, int row, int col); //计算棋谱坐标差值
    bool isBottomSide(int id);                          //判断上下方
    int getStoneCountAtLine(int row1, int col1, int row2, int col2);

    virtual void keyPressEvent(QKeyEvent *)override;    //键盘事件
    ~Borad();

};

#endif // BORAD_H
