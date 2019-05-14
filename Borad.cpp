#include "Borad.h"
#define GetRowCol(__row, __col, __id) \
    int __row = _s[__id]._row;\
    int __col = _s[__id]._col

Borad::Borad(QWidget *parent)
    : QMainWindow(parent)
{
    fullscreen=false;
    _r=23;
    init();

    backBut.setParent(this);
    backBut.setStyleSheet("QPushButton{ font-family:'Microsoft YaHei';font-size:30px;color:#666666;}");
    backBut.setText("悔棋");
    backBut.setGeometry(620,400,250,50);
    connect(&backBut,&QPushButton::released,this,&Borad::backs);

    reopen.setParent(this);
    reopen.setStyleSheet("QPushButton{ font-family:'Microsoft YaHei';font-size:30px;color:#666666;}");
    reopen.setText("重开");
    reopen.setGeometry(620,300,250,50);
    connect(&reopen,&QPushButton::released,this,&Borad::init);

    win.setParent(this);
    win.setStyleSheet("QLabel{ font-family:'华文行楷';font-size:100px;color:#ff0000;}");
    win.setText("对弈中");
    win.setGeometry(620,0,500,200);
}

void Borad::init()
{
    for(int i=0; i<32; ++i)
    {
        _s[i].init(i);
    }
    _selectid=-1;
    _bRedTrue=true;
    _bSide=true;
    update();
}

void Borad::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);//抗锯齿
    painter.setPen(Qt::NoPen);
    painter.setBrush(Qt::white);
    painter.drawRect(rect());

    drawBoard(painter);     //画棋盘
    drawStone(painter);
}

void Borad::drawBoard(QPainter &painter)
{
    painter.setPen(QPen(Qt::black,7));
    painter.drawRect(90,90,420,470);
    painter.setPen(QPen(Qt::black,4));
    int d=50;
    for(int i=0;i<10;++i)
    {
        painter.drawLine(QPoint(100,100+i*d),QPoint(100+8*d,100+i*d));
    }
    for(int i=0;i<9;i++)
    {
        if(i==0||i==8)
        {
            painter.drawLine(QPoint(100+i*d,100),QPoint(100+i*d,100+9*d));
        }
        else
        {
            painter.drawLine(QPoint(100+i*d,100),QPoint(100+i*d,100+4*d));
            painter.drawLine(QPoint(100+i*d,100+5*d),QPoint(100+i*d,100+9*d));
        }
    }

    // 九宫格
    painter.drawLine(QPoint(100+3*d, 100), QPoint(100+5*d, 100+2*d));
    painter.drawLine(QPoint(100+5*d, 100), QPoint(100+3*d, 100+2*d));

    painter.drawLine(QPoint(100+3*d, 100+7*d), QPoint(100+5*d, 100+9*d));
    painter.drawLine(QPoint(100+3*d, 100+9*d), QPoint(100+5*d, 100+7*d));
}

void Borad::drawStone(QPainter &painter)
{
    for(int i=0;i<32;i++)
    {
        drawStone(painter,i);
    }
}

void Borad::drawStone(QPainter &painter, int id)
{
    if(isDead(id)) return;
    if(red(id))
    {
        painter.setPen(QPen(Qt::red,4));
    }
    else
    {
        painter.setPen(QPen(Qt::black,4));
    }
    if(id==_selectid) painter.setPen(QPen(Qt::yellow,4));
    painter.drawEllipse(center(id),_r,_r);

    QPoint c=center(id);
    QRect rect=QRect(c.x()-_r,c.y()-_r,_r*2,_r*2);
    painter.setFont(QFont("楷体",25,500));
    painter.drawText(rect, _s[id].getText(), QTextOption(Qt::AlignCenter));
}

QPoint Borad::center(int id)
{
    return center(_s[id]._row,_s[id]._col);
}

QPoint Borad::center(int row, int col)
{
    QPoint pt(50*col+100,50*row+100);
    return pt;
}

bool Borad::getClickRowCol(QPoint &pt, int &row, int &col)
{
    for(row=0; row<=9; ++row)
    {
        for(col=0; col<=8; ++col)
        {
            QPoint distance = center(row, col) - pt;
            if(distance.x() * distance.x() + distance.y() * distance.y() < _r* _r)
                return true;
        }
    }
    return false;
}

int Borad::getStoneId(int row, int col)
{
    for(int i=0; i<32; ++i)
    {
        if(_s[i]._row == row && _s[i]._col == col && !isDead(i))
            return i;
    }
    return -1;
}

bool Borad::isDead(int id)
{
    if(id == -1)return true;
    return _s[id]._dead;
}

bool Borad::sameColorStone(int id1, int id2)
{
    if(id1 == -1 || id2 == -1) return false;

    return red(id1) == red(id2);
}

bool Borad::red(int id)
{
    return _s[id]._isRed;
}

void Borad::killStone(int id)
{
    if(id==-1) return;
    _s[id]._dead = true;
}

void Borad::reliveStone(int id)
{
    if(id==-1) return;
    _s[id]._dead = false;
}

void Borad::moveStone(int moveid, int row, int col)
{
    _s[moveid]._row = row;
    _s[moveid]._col = col;

    _bRedTrue = !_bRedTrue;
}

void Borad::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button() != Qt::LeftButton)
    {
        return;
    }

    click(event->pos());
}

void Borad::click(QPoint pt)
{
    int row, col;
    bool bClicked = getClickRowCol(pt, row, col);

    if(!bClicked) return;

    int id = getStoneId(row, col);
    click(id, row, col);
}

void Borad::click(int id, int row, int col)
{
    if(_selectid==-1)
    {
        trySelectStone(id);
    }
    else
    {
        tryMoveStone(id,row,col);
    }
}

void Borad::trySelectStone(int id)
{
    if(id == -1)
        return;

    if(!canSelect(id)) return;

    _selectid = id;
    update();
}

void Borad::tryMoveStone(int killid, int row, int col)
{
    if(killid != -1 && sameColorStone(killid, _selectid))
    {
        trySelectStone(killid);
        return;
    }

    bool ret = canMove(_selectid, killid, row, col);
    if(ret)
    {
        moveStone(_selectid, killid, row, col);
        _selectid = -1;
        update();
    }
}

void Borad::moveStone(int moveid, int killid, int row, int col)
{
    saveStep(moveid, killid, row, col, _steps);

    killStone(killid);
    if(killid==20 && _s[killid]._dead == true)
    {
        win.setText("您输了");
    }
    moveStone(moveid, row, col);
}

void Borad::saveStep(int moveid, int killid, int row, int col, QVector<Step *> &steps)
{
    GetRowCol(row1, col1, moveid);
    Step* step = new Step;
    step->_colFrom = col1;
    step->_colTo = col;
    step->_rowFrom = row1;
    step->_rowTo = row;
    step->_moveid = moveid;
    step->_killid = killid;

    steps.append(step);
}

void Borad::backs()
{
    if(_bRedTrue)
    {
        backOne();
        backOne();
    }
}

void Borad::backOne()
{
    if(this->_steps.size() == 0) return;

    Step* step = this->_steps.last();
    _steps.removeLast();
    back(step);

    update();
    delete step;
}

void Borad::back(Step *step)
{
    reliveStone(step->_killid);
    moveStone(step->_moveid, step->_rowFrom, step->_colFrom);
}

bool Borad::canSelect(int id)
{
    return _bRedTrue==_s[id]._isRed;
}

bool Borad::canMove(int moveid, int killid, int row, int col)
{
    if(sameColorStone(moveid,killid))return false;

    switch (_s[moveid]._type) {
    case Stone::JIANG:
        return canMoveJiang(moveid, killid, row, col);
    case Stone::SHI:
        return canMoveShi(moveid, killid, row, col);
    case Stone::XIANG:
        return canMoveXiang(moveid, killid, row, col);
    case Stone::MA:
        return canMoveMa(moveid, killid, row, col);
    case Stone::CHE:
        return canMoveChe(moveid, killid, row, col);
    case Stone::PAO:
        return canMovePao(moveid, killid, row, col);
    case Stone::BING:
        return canMoveBing(moveid, killid, row, col);
    }
    return false;
}

bool Borad::canMoveJiang(int moveid, int killid, int row, int col)
{
    if(killid != -1 && _s[killid]._type == Stone::JIANG)
        return canMoveChe(moveid, killid, row, col);

    GetRowCol(row1, col1, moveid);
    int r = relation(row1, col1, row, col);
    if(r != 1 && r != 10) return false;

    if(col < 3 || col > 5) return false;
    if(isBottomSide(moveid))
    {
        if(row < 7) return false;
    }
    else
    {
        if(row > 2) return false;
    }
    return true;
}

bool Borad::canMoveShi(int moveid, int , int row, int col)
{
    GetRowCol(row1, col1, moveid);
    int r = relation(row1, col1, row, col);
    if(r != 11) return false;

    if(col < 3 || col > 5) return false;
    if(isBottomSide(moveid))
    {
        if(row < 7) return false;
    }
    else
    {
        if(row > 2) return false;
    }
    return true;
}

bool Borad::canMoveXiang(int moveid, int , int row, int col)
{
    GetRowCol(row1, col1, moveid);
    int r = relation(row1, col1, row, col);
    if(r != 22) return false;

    int rEye = (row+row1)/2;
    int cEye = (col+col1)/2;
    if(getStoneId(rEye, cEye) != -1)
        return false;

    if(isBottomSide(moveid))
    {
        if(row < 4) return false;
    }
    else
    {
        if(row > 5) return false;
    }
    return true;
}

bool Borad::canMoveMa(int moveid, int , int row, int col)
{
    GetRowCol(row1, col1, moveid);
    int r = relation(row1, col1, row, col);
    if(r != 12 && r != 21)
        return false;

    if(r == 12)
    {
        if(getStoneId(row1, (col+col1)/2) != -1)
            return false;
    }
    else
    {
        if(getStoneId((row+row1)/2, col1) != -1)
            return false;
    }

    return true;
}

bool Borad::canMoveChe(int moveid, int , int row, int col)
{
    GetRowCol(row1, col1, moveid);
    int ret = getStoneCountAtLine(row1, col1, row, col);
    if(ret == 0)
        return true;
    return false;
}

bool Borad::canMovePao(int moveid, int killid, int row, int col)
{
    GetRowCol(row1, col1, moveid);
    int ret = getStoneCountAtLine(row, col, row1, col1);
    if(killid != -1)
    {
        if(ret == 1) return true;
    }
    else
    {
        if(ret == 0) return true;
    }
    return false;
}

bool Borad::canMoveBing(int moveid, int , int row, int col)
{
    GetRowCol(row1, col1, moveid);
    int r = relation(row1, col1, row, col);
    if(r != 1 && r != 10) return false;

    if(isBottomSide(moveid))
    {
        if(row > row1) return false;
        if(row1 >= 5 && row == row1) return false;
    }
    else
    {
        if(row < row1) return false;
        if(row1 <= 4 && row == row1) return false;
    }

    return true;
}

int Borad::relation(int row1, int col1, int row, int col)
{
    return qAbs(row1-row)*10+qAbs(col1-col);
}

bool Borad::isBottomSide(int id)
{
    return _bSide == _s[id]._isRed;
}

int Borad::getStoneCountAtLine(int row1, int col1, int row2, int col2)
{
    int ret = 0;
    if(row1 != row2 && col1 != col2)
        return -1;
    if(row1 == row2 && col1 == col2)
        return -1;

    if(row1 == row2)
    {
        int min = col1 < col2 ? col1 : col2;
        int max = col1 < col2 ? col2 : col1;
        for(int col = min+1; col<max; ++col)
        {
            if(getStoneId(row1, col) != -1) ++ret;
        }
    }
    else
    {
        int min = row1 < row2 ? row1 : row2;
        int max = row1 < row2 ? row2 : row1;
        for(int row = min+1; row<max; ++row)
        {
            if(getStoneId(row, col1) != -1) ++ret;
        }
    }

    return ret;
}



void Borad::keyPressEvent(QKeyEvent *event)
{
    switch (event->key())
            {
            //F1为全屏和普通屏的切换键
            case Qt::Key_F1:
                fullscreen = !fullscreen;
                if (fullscreen)
                {
                    showFullScreen();
                }
                else
                {
                    showNormal();
                }
                break;
            //ESC为退出键
            case Qt::Key_Escape:
                close();
                break;
        }
}

Borad::~Borad()
{

}
