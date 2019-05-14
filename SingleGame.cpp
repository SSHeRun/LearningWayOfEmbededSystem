#include "SingleGame.h"


SingleGame::SingleGame(QWidget *)
{
    _level = 4;
}

void SingleGame::click(int id, int row, int col)
{
    if(_bRedTrue)
    {
        Borad::click(id,row,col);
        if(!_bRedTrue)
        {
            QTimer::singleShot(100, this, SLOT(computerMove()));
        }
    }
}

Step *SingleGame::getBestMove()
{
    Step* ret = NULL;
    QVector<Step*> steps;
    getAllPossibleMove(steps);
    int maxInAllMinScore = -300000;

    while(steps.count())
    {
        Step* step = steps.last();
        steps.removeLast();

        fakeMove(step);
        int minScore = getMinScore(this->_level-1, maxInAllMinScore);
        unfakeMove(step);

        if(minScore > maxInAllMinScore)
        {
            if(ret) delete ret;

            ret = step;
            maxInAllMinScore = minScore;
        }
        else
        {
            delete step;
        }
    }
    return ret;
}

void SingleGame::getAllPossibleMove(QVector<Step *> &steps)
{
    int min, max;
    if(!this->_bRedTrue)
    {
        min = 0, max = 16;
    }
    else
    {
        min = 16, max = 32;
    }

    for(int i=min;i<max; i++)
    {
        if(this->_s[i]._dead) continue;
        for(int row = 0; row<=9; ++row)
        {
            for(int col=0; col<=8; ++col)
            {
                int killid = this->getStoneId(row, col);
                if(sameColorStone(i, killid)) continue;

                if(canMove(i, killid, row, col))
                {
                    saveStep(i, killid, row, col, steps);
                }
            }
        }
    }
}

int SingleGame::getMinScore(int level, int curMin)
{
    if(level == 0)
        return score();

    QVector<Step*> steps;
    getAllPossibleMove(steps);
    int minInAllMaxScore = 300000;

    while(steps.count())
    {
        Step* step = steps.last();
        steps.removeLast();

        fakeMove(step);
        int maxScore = getMaxScore(level-1, minInAllMaxScore);
        unfakeMove(step);
        delete step;

        if(maxScore <= curMin)
        {
            while(steps.count())
            {
                Step* step = steps.last();
                steps.removeLast();
                delete step;
            }
            return maxScore;
        }

        if(maxScore < minInAllMaxScore)
        {
            minInAllMaxScore = maxScore;
        }


    }
    return minInAllMaxScore;
}

int SingleGame::getMaxScore(int level, int curMax)
{
    if(level == 0)
        return score();

    QVector<Step*> steps;
    getAllPossibleMove(steps);
    int maxInAllMinScore = -300000;

    while(steps.count())
    {
        Step* step = steps.last();
        steps.removeLast();

        fakeMove(step);
        int minScore = getMinScore(level-1, maxInAllMinScore);
        unfakeMove(step);
        delete step;

        if(minScore >= curMax)
        {
            while(steps.count())
            {
                Step* step = steps.last();
                steps.removeLast();
                delete step;
            }
            return minScore;
        }
        if(minScore > maxInAllMinScore)
        {
            maxInAllMinScore = minScore;
        }


    }
    return maxInAllMinScore;
}

int SingleGame::score()
{
    //enum TYPE{JIANG,SHI,XIANG,MA,CHE,PAO,BING};
    static int s[] = {15000, 100, 100, 500, 1000, 600, 200};
    int scoreBlack = 0;
    int scoreRed = 0;
    for(int i=0; i<=15; ++i)
    {
        if(_s[i]._dead) continue;
        scoreBlack += s[_s[i]._type];
    }
    for(int i=16; i<32; ++i)
    {
        if(_s[i]._dead) continue;
        scoreRed += s[_s[i]._type];
    }
    return scoreBlack - scoreRed;
}

void SingleGame::fakeMove(Step *step)
{
    killStone(step->_killid);
    moveStone(step->_moveid, step->_rowTo, step->_colTo);
}

void SingleGame::unfakeMove(Step *step)
{
    reliveStone(step->_killid);
    moveStone(step->_moveid, step->_rowFrom, step->_colFrom);
}

void SingleGame::computerMove()
{
    Step* step = getBestMove();
    moveStone(step->_moveid, step->_killid, step->_rowTo, step->_colTo);
    delete step;
    update();
}
