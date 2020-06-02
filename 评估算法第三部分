#include <iostream>
using namespace std;
#define C_NONE 0//棋子：黑子,白子,无子
#define C_BLACK 1
#define C_WHITE 2

//棋型代号 下标 权重
#define OTHER 0//0,其他棋型不考虑
#define WIN 1//100000,白赢
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

int tuple6type[4][4][4][4][4][4];

struct EVALUATION
{
    int score;
    gameResult result;
    int STAT[8];
};
EVALUATION chessAi::evaluate(int board[15][15])
{
    int weight[17] = { 0,1000000,-10000000,50000,-100000,400,-100000,400,-8000,20,-50,20,-50,1,-3,1,-3 };
    int i, j, type;
    int stat[4][17];
    memset(stat, 0, sizeof(stat));

    int A[17][17];
    for (int i = 0; i < 17; i++)
        A[i][0] = 3;
    for (int i = 0; i < 17; i++)
        A[i][16] = 3;
    for (int j = 0; j < 17; j++)
        A[0][j] = 3;
    for (int j = 0; j < 17; j++)
        A[16][j] = 3;
    for (int i = 0; i < 15; i++)
        for (int j = 0; j < 15; j++)
            A[i + 1][j + 1] = board[i][j];

    //横向
    for (i = 1; i <= 15; i++)
    {
        for (j = 0; j < 12; j++)
        {
            type = tuple6type[A[i][j]][A[i][j + 1]][A[i][j + 2]][A[i][j + 3]][A[i][j + 4]][A[i][j + 5]];
            stat[0][type]++;
        }
    }
    //竖向
    for (j = 1; j <=15; j++)
    {
        for (i = 0; i < 12; i++)
        {
            type = tuple6type[A[i][j]][A[i + 1][j]][A[i + 2][j]][A[i + 3][j]][A[i + 4][j]][A[i + 5][j]];
            stat[1][type]++;
        }
    }
    //左上至右下
    for (i = 0; i < 12; i++)
    {
        for (j = 0; j < 12; j++)
        {
            type = tuple6type[A[i][j]][A[i + 1][j + 1]][A[i + 2][j + 2]][A[i + 3][j + 3]][A[i + 4][j + 4]][A[i + 5][j + 5]];
            stat[2][type]++;
        }
    }
    //右上至左下
    for (i = 0; i < 12; i++)
    {
        for (j = 5; j < 17; j++)
        {
            type = tuple6type[A[i][j]][A[i + 1][j - 1]][A[i + 2][j - 2]][A[i + 3][j - 3]][A[i + 4][j - 4]][A[i+5][j-5]];
            stat[3][type]++;
        }
    }

    EVALUATION eval;
    memset(eval.STAT, 0, sizeof(eval.STAT));
    int score = 0;
    for (i = 1; i < 17; i++)
    {
        score += weight[i]*(stat[0][i] + stat[1][i] + stat[2][i] + stat[3][i]);

        int count = stat[0][i] + stat[1][i] + stat[2][i] + stat[3][i];
        if (i == WIN)eval.STAT[WIN] = count;
        else if (i == LOSE)eval.STAT[LOSE] = count;
        else if (i == FLEX4)eval.STAT[FLEX4] = count;
        else if (i == BLOCK4)eval.STAT[BLOCK4] = count;
        else if (i == FLEX3)eval.STAT[FLEX3] = count;
    }
    eval.result = R_DRAW;

    if (eval.STAT[WIN] > 0)eval.result = R_WHITE;
    else if (eval.STAT[LOSE] > 0)eval.result = R_BLACK;

    eval.score = score;
    return eval;
}
