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

enum gameMode{PEOPLE, AIE, AID};
enum gameStatus{PLAYING, FINISH};
enum gameTurn{T_BLACK, T_WHITE};
enum gameResult{R_BLACK, R_WHITE, R_BOTH};

#define OTHER 0//0,其他棋型不考虑
#define WIN 1//1000000,白赢
#define LOSE 2//-10000000
#define FLEX4 3//50000,白活4
#define flex4 4//-80000
#define BLOCK4 5//400
#define block4 6//-80000
#define FLEX3 7//400
#define flex3 8//-8000
#define BLOCK3 9//20
#define block3 10//-40
#define FLEX2 11//20
#define flex2 12//-40
#define BLOCK2 13//1
#define block2 14//-2
#define FLEX1 15//1
#define flex1 16//-2

struct DECISION {
    QPoint pos;
    int score;
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
    DECISION decision;
    int nodeNum;
private:
    int type[4][4][4][4][4][4];
public:
    void initType();
    bool checkBound(QPoint);//判断边界
    QPoint getPos(int, int, int, int);//得到五子组的开头结尾坐标
    int calcOnePos(int [15][15], int , int, int);//贪心算一个位置所在的五个五子组的得分总和
    int listScore(int, int, int);//根据一个五子组中的黑白棋个数和当前方的情况估计得分
    QPoint highestScorePos(int [15][15]);//寻找一步估计得分中最高的位置
    POINTS seekPoints(int [15][15]);
    EVALUATION evaluate(int [15][15]);
    void copy(int [15][15], int [15][15]);//复制棋盘
    void oppsite(int [15][15], int [15][15]);//取反棋盘
    int analyze(int [15][15], int, int, int);
    int step=0;
    int WhiteStep = 0;
    int BlackStep = 0;
    QPoint record[100];
    int recordRow=0;
    int recordCol=0;
};

#endif // CHESS_H
