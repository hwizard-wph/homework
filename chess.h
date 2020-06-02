#ifndef CHESS_H
#define CHESS_H

#include <QDebug>
#include <QPoint>

#define C_EMPTY 0
#define C_BLACK 1
#define C_WHITE 2

#define UP 0
#define RIGHT 1
#define UPRIGHT 2
#define UPLEFT 3

enum gameMode{PEOPLE, AI};
enum gameStatus{PLAYING, FINISH};
enum gameTurn{T_BLACK, T_WHITE};
enum gameResult{R_BLACK, R_WHITE, R_BOTH};

struct DECISION {
    QPoint pos;
    int eval;
};

struct EVALUATION {
    int score;
    gameResult res;
    int STA[8];
};

struct POINTS {
    QPoint pos[20];
    int score[20];
};

class chess
{
public:
    chess();
    int chesses[15][15];
    DECISION decison;
    int nodeNum;
private:
    int type[4][4][4][4][4][4];
    POINTS pts;
public:
    bool checkBound(QPoint);//判断边界
    QPoint getPos(int, int, int, int);//得到五子组的开头结尾坐标
    int calcOnePos(int [15][15], int , int, int);//贪心算一个位置所在的五个五子组的得分总和
    int listScore(int, int, int);//根据一个五子组中的黑白棋个数和当前方的情况估计得分
    QPoint highestScorePos(int);//贪心寻找一个估计得分中最高的位置
    POINTS seekPionts(int [15][15]);
    void copy(int [15][15], int [15][15]);//复制棋盘
    void oppsite(int [15][15], int [15][15]);//取反棋盘
};

#endif // CHESS_H
