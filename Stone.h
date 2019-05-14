#ifndef STONE_H
#define STONE_H

#include <QString>

class Stone
{
public:
    Stone();
    enum TYPE{JIANG,SHI,XIANG,MA,CHE,PAO,BING};
    int _id;
    int _row;
    int _col;
    bool _isRed;
    bool _dead;
    TYPE _type;

    void init(int id);
    QString getText();
};

#endif // STONE_H
