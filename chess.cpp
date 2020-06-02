#include "chess.h"

chess::chess()
{
    nodeNum = 0;
    initType();
}

bool chess::checkBound(QPoint p)
{
    return (p.x() >= 0 && p.x() < 15 && p.y() >= 0 && p.y() < 15);
}

QPoint getPos(int row, int col, int dir, int len)
{
    QPoint retPos;
    if (dir == UP)
    {
        retPos.setX(row - len);
        retPos.setY(col);
    }
    else if (dir == RIGHT)
    {
        retPos.setX(row);
        retPos.setY(col + len);
    }
    else if (dir == UPRIGHT)
    {
        retPos.setX(row - len);
        retPos.setY(col + len);
    }
    else if (dir == UPLEFT)
    {
        retPos.setX(row - len);
        retPos.setY(col - len);
    }
    return retPos;
}

int chess::calcOnePos(int board[15][15], int row, int col, int C)
{
    int sum = 0;
    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 5; ++j)
        {
            QPoint st = getPos(row, col, UP + i, j - 4);
            QPoint ed = getPos(st.x(), st.y(), UP + i, 4);
            if (checkBound(st) && checkBound(ed))
            {
                int white = 0;
                int black = 0;
                for (int k = 0; k < 5; ++k) {
                    QPoint p = getPos(st.x(), st.y(), UP + i, k);
                    white += (board[p.x()][p.y()] == C_WHITE);
                    black += (board[p.x()][p.y()] == C_BLACK);
                }
                sum += listScore(white, black, C);
            }
        }
    }
    return sum;
}

int chess::listScore(int white, int black, int C)
{
    if (C == C_WHITE && white == 5) return 9999999;
    if (C == C_BLACK && black == 5) return 9999999;
    if (black == 0 && white == 0) return 5;
    else if (black >= 1 && white >= 1) return 0;
    else if (C == C_BLACK)
    {
        if (black == 1 && white == 0) return 20;
        else if (black == 2 && white == 0) return 800;
        else if (black == 3 && white == 0) return 15000;
        else if (black == 4 && white == 0) return 800000;
        else if (black == 0 && white == 1) return 10;
        else if (black == 0 && white == 2) return 400;
        else if (black == 0 && white == 3) return 7500;
        else return 200000;
    }
    else
    {
        if (white == 1 && black == 0) return 20;
        else if (white == 2 && black == 0) return 800;
        else if (white == 3 && black == 0) return 15000;
        else if (white == 4 && black == 0) return 800000;
        else if (white == 0 && black == 1) return 10;
        else if (white == 0 && black == 2) return 400;
        else if (white == 0 && black == 3) return 7500;
        else return 200000;
    }
}

QPoint chess::highestScorePos(int C)
{
    int highestScore = INT_MIN;
    int row, col;
    for (int i = 0; i < 15; ++i)
    {
        for (int j = 0; j < 15; ++j)
        {
            if (chesses[i][j] == C_EMPTY) {
                int score = calcOnePos(chesses, i, j, C);
                if (score > highestScore)
                {
                    highestScore = score;
                    row = i;
                    col = j;
                }
            }
        }
    }
    QPoint pos;
    pos.setX(row);
    pos.setY(col);
    return pos;
}

POINTS chess::seekPionts(int board[15][15])
{
    bool can[15][15];
    int score[15][15];
    for (int i = 0; i < 15; ++i)
    {
        for (int j = 0; j < 15; ++j)
        {
            can[i][j] = 0;
            score[i][j] = INT_MIN;
        }
    }
    for (int i = 0; i < 15; ++i)
    {
        for (int j = 0; j < 15; ++j)
        {
            if (chesses[i][j] == C_EMPTY)
            {
                for (int k = -3; k <= 3; ++k)
                {
                    int ii, jj;
                    ii = i; jj = j + k;
                    if (jj >= 0 && jj < 15 && chesses[ii][jj] == C_EMPTY)
                    {
                        can[ii][jj] = 1;
                    }
                    ii = i + k; jj = j;
                    if (ii >= 0 && ii < 15 && chesses[ii][jj] == C_EMPTY)
                    {
                        can[ii][jj] = 1;
                    }
                    ii = i + k; jj = j + k;
                    if (ii >= 0 && ii < 15 && jj >= 0 && jj < 15 && chesses[ii][jj] == C_EMPTY)
                    {
                        chesses[ii][jj] = 1;
                    }
                    ii = i - k; jj = j + k;
                    if (ii >= 0 && ii < 15 && jj >= 0 && jj < 15 && chesses[ii][jj] == C_EMPTY)
                    {
                        chesses[ii][jj] = 1;
                    }
                }
            }
        }
    }
    for (int i = 0; i < 15; ++i)
    {
        for (int j = 0; j < 15; ++j)
        {
            if (can[i][j] == 1)
            {
                score[i][j] = calcOnePos(chesses, i, j, C_WHITE);
            }
        }
    }
    POINTS pList;
    for (int k = 0; k < 20; ++k)
    {
        int tmpScore = INT_MIN;
        for (int i = 0; i < 15; ++i)
        {
            for (int j = 0; j < 15; ++j)
            {
                if (score[i][j] > tmpScore) {
                    tmpScore = score[i][j];
                    QPoint tmpPos;
                    tmpPos.setX(i);
                    tmpPos.setY(j);
                    pList.pos[k] = tmpPos;
                }
            }
        }
        int row = pList.pos[k].x();
        int col = pList.pos[k].y();
        board[row][col] = C_WHITE;
        pList.score[k] = evaluate(board).score;
        board[row][col] = C_EMPTY;
        score[row][col] = INT_MIN;
    }
    return pList;
}

void chess::copy(int b1[15][15], int b2[15][15])
{
    for (int i = 0; i < 15; ++i)
    {
        for (int j = 0; j < 15; ++j)
        {
            b2[i][j] = b1[i][j];
        }
    }
}

void chess::oppsite(int b1[15][15], int b2[15][15])
{
    for (int i = 0; i < 15; ++i)
    {
        for (int j = 0; j < 15; ++j)
        {
            if (b1[i][j] == C_EMPTY) b2[i][j] = C_EMPTY;
            else if (b1[i][j] == C_WHITE) b2[i][j] = C_BLACK;
            else b2[i][j] = C_WHITE;
        }
    }
}

