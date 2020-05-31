#ifndef CHESS_H
#define CHESS_H

#include <QDebug>
#include <QPoint>

#define C_EMPTY 0
#define C_BLACK 1
#define C_WHITE 2

enum gameMode{PEOPLE, AI};
enum gameStatus{PLAYING, FINISH};
enum gameTurn{T_BLACK, T_WHITE};
enum gameResult{R_BLACK, R_WHITE, R_BOTH};

struct DECISION {
    QPoint pos;
    int eval;
};

class chess
{
public:
    chess()
    {
        nodeNum = 0;
    };
    int chesses[15][15];
    DECISION decison;
    int nodeNum;
};

#endif // CHESS_H
