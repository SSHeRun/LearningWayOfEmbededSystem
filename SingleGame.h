#ifndef SINGLEGAME_H
#define SINGLEGAME_H

#include <QTimer>

#include "Borad.h"

class SingleGame:public Borad
{
    Q_OBJECT
public:
    explicit SingleGame(QWidget *parent = 0);
    int _level;

    void click(int id, int row, int col);

    Step *getBestMove();
    void getAllPossibleMove(QVector<Step*>& steps);
    int getMinScore(int level, int curMin);
    int getMaxScore(int level, int curMax);
    int score();

    void fakeMove(Step* step);
    void unfakeMove(Step* step);

public slots:
    void computerMove();
};

#endif // SINGLEGAME_H
