#include "chess.h"

chess::chess()
{
    initType();
}

void chess::initType() {
    memset(type, 0, sizeof(type));
    type[2][2][2][2][2][2] = WIN;
    type[2][2][2][2][2][0] = WIN;
    type[0][2][2][2][2][2] = WIN;
    type[2][2][2][2][2][1] = WIN;
    type[1][2][2][2][2][2] = WIN;
    type[3][2][2][2][2][2] = WIN;//边界考虑
    type[2][2][2][2][2][3] = WIN;
    //黑连5，ai输
    type[1][1][1][1][1][1] = LOSE;
    type[1][1][1][1][1][0] = LOSE;
    type[0][1][1][1][1][1] = LOSE;
    type[1][1][1][1][1][2] = LOSE;
    type[2][1][1][1][1][1] = LOSE;
    type[3][1][1][1][1][1] = LOSE;
    type[1][1][1][1][1][3] = LOSE;
    //白活4
    type[0][2][2][2][2][0] = FLEX4;
    //黑活4
    type[0][1][1][1][1][0] = flex4;
    //白活3
    type[0][2][2][2][0][0] = FLEX3;
    type[0][0][2][2][2][0] = FLEX3;
    type[0][2][0][2][2][0] = FLEX3;
    type[0][2][2][0][2][0] = FLEX3;
    //黑活3
    type[0][1][1][1][0][0] = flex3;
    type[0][0][1][1][1][0] = flex3;
    type[0][1][0][1][1][0] = flex3;
    type[0][1][1][0][1][0] = flex3;
    //白活2
    type[0][2][2][0][0][0] = FLEX2;
    type[0][2][0][2][0][0] = FLEX2;
    type[0][2][0][0][2][0] = FLEX2;
    type[0][0][2][2][0][0] = FLEX2;
    type[0][0][2][0][2][0] = FLEX2;
    type[0][0][0][2][2][0] = FLEX2;
    //黑活2
    type[0][1][1][0][0][0] = flex2;
    type[0][1][0][1][0][0] = flex2;
    type[0][1][0][0][1][1] = flex2;
    type[0][0][1][1][0][0] = flex2;
    type[0][0][1][0][1][0] = flex2;
    type[0][0][0][1][1][0] = flex2;
    //白活1
    type[0][2][0][0][0][0] = FLEX1;
    type[0][0][2][0][0][0] = FLEX1;
    type[0][0][0][2][0][0] = FLEX1;
    type[0][0][0][0][2][0] = FLEX1;
    //黑活1
    type[0][1][0][0][0][0] = flex1;
    type[0][0][1][0][0][0] = flex1;
    type[0][0][0][1][0][0] = flex1;
    type[0][0][0][0][1][0] = flex1;

    int p1, p2, p3, p4, p5, p6, x, y, ix, iy;
    //x:左边5个格子中黑子个数，y:左边5个格子中白子个数,ix:右边5个中黑子个数,iy:右边5个格子中白字个数
    for (p1 = 0; p1 < 4; ++p1)
    {
        for (p2 = 0; p2 < 3; ++p2)
        {
             for (p3 = 0; p3 < 3; ++p3)
             {
                 for (p4 = 0; p4 < 3; ++p4)
                 {
                     for (p5 = 0; p5 < 3; ++p5)
                     {
                         for (p6 = 0; p6 < 4; ++p6)
                         {
                             x = y = ix = iy = 0;
                             if (p1 == 1) x++;
                             else if (p1 == 2) y++;

                             if (p2 == 1) { x++; ix++; }
                             else if (p2 == 2) { y++; iy++; }

                             if (p3 == 1) { x++; ix++; }
                             else if (p3 == 2) { y++; iy++; }

                             if (p4 == 1) { x++; ix++; }
                             else if (p4 == 2) { y++; iy++; }

                             if (p5 == 1) { x++; ix++; }
                             else if (p5 == 2) { y++; iy++; }

                             if (p6 == 1)ix++;
                             else if (p6 == 2)iy++;

                             if (p1 == 3 || p6 == 3)
                             {
                                    //有边界
                                    if (p1 == 3 && p6 != 3)
                                    {
                                        //左边界
                                        //白冲4
                                        if (ix == 0 && iy == 4)
                                        {
                                            //若右边有活4无妨，因为活4的权重远大于冲4
                                            if (type[p1][p2][p3][p4][p5][p6] == 0)
                                                type[p1][p2][p3][p4][p5][p6] = BLOCK4;

                                        }
                                        //黑冲4
                                        if (ix == 4 && iy == 0)
                                        {
                                            if (type[p1][p2][p3][p4][p5][p6] == 0)
                                                type[p1][p2][p3][p4][p5][p6] = block4;

                                        }
                                        //白眠3
                                        if (ix == 0 && iy == 3)
                                        {
                                            if (type[p1][p2][p3][p4][p5][p6] == 0)
                                                type[p1][p2][p3][p4][p5][p6] = BLOCK3;
                                        }
                                        //黑眠3
                                        if (ix == 3 && iy == 0)
                                        {
                                            if (type[p1][p2][p3][p4][p5][p6] == 0)
                                                type[p1][p2][p3][p4][p5][p6] = block3;
                                        }
                                        //白眠2
                                        if (ix == 0 && iy == 2)
                                        {
                                            if (type[p1][p2][p3][p4][p5][p6] == 0)
                                                type[p1][p2][p3][p4][p5][p6] = BLOCK2;
                                        }
                                    }
                                    else if (p6 == 3 && p1 != 3)
                                    {
                                        //右边界
                                        //白冲4
                                        if (x == 0 && y == 4)
                                        {
                                            if (type[p1][p2][p3][p4][p5][p6] == 0)
                                                type[p1][p2][p3][p4][p5][p6] = BLOCK4;
                                        }
                                        //黑冲4
                                        if (x == 4 && y == 0)
                                        {
                                            if (type[p1][p2][p3][p4][p5][p6] == 0)
                                                type[p1][p2][p3][p4][p5][p6] = block4;
                                        }
                                        //黑眠3
                                        if (x == 3 && y == 0)
                                        {
                                            if (type[p1][p2][p3][p4][p5][p6] == 0)
                                                type[p1][p2][p3][p4][p5][p6] = BLOCK3;
                                        }
                                        //白眠3
                                        if (x == 0 && y == 3)
                                        {
                                            if (type[p1][p2][p3][p4][p5][p6] == 0)
                                                type[p1][p2][p3][p4][p5][p6] = block3;
                                        }
                                        //黑眠2
                                        if (x == 2 && y == 0)
                                        {
                                            if (type[p1][p2][p3][p4][p5][p6] == 0)
                                                type[p1][p2][p3][p4][p5][p6] = BLOCK2;
                                        }
                                        //白眠2
                                        if (x == 0 && y == 2)
                                        {
                                            if (type[p1][p2][p3][p4][p5][p6] == 0)
                                                type[p1][p2][p3][p4][p5][p6] = block2;
                                        }
                                    }
                                }
                                else
                                {
                                    //无边界
                                    //白冲4
                                    if ((x == 0 && y == 4) || (ix == 0 && iy == 4))
                                    {
                                        if (type[p1][p2][p3][p4][p5][p6] == 0)
                                            type[p1][p2][p3][p4][p5][p6] = BLOCK4;
                                    }
                                    //黑冲4
                                    if ((x == 4 && y == 0) || (ix == 4 && iy == 0))
                                    {
                                        if (type[p1][p2][p3][p4][p5][p6] == 0)
                                            type[p1][p2][p3][p4][p5][p6] = block4;
                                    }
                                    //白眠3
                                    if ((x == 0 && y == 3) || (ix == 0 && iy == 3))
                                    {
                                        if (type[p1][p2][p3][p4][p5][p6] == 0)
                                            type[p1][p2][p3][p4][p5][p6] = BLOCK3;
                                    }
                                    //黑眠3
                                    if ((x == 3 && y == 0) || (ix == 3 && iy == 0))
                                    {
                                        if (type[p1][p2][p3][p4][p5][p6] == 0)
                                            type[p1][p2][p3][p4][p5][p6] = block3;
                                    }
                                    //白眠2
                                    if ((x == 0 && y == 2) || (ix == 0 && iy == 2))
                                    {
                                        if (type[p1][p2][p3][p4][p5][p6] == 0)
                                            type[p1][p2][p3][p4][p5][p6] = BLOCK2;
                                    }
                                    //黑眠2
                                    if ((x == 2 && y == 0) || (ix == 2 && iy == 0))
                                    {
                                        if (type[p1][p2][p3][p4][p5][p6] == 0)
                                            type[p1][p2][p3][p4][p5][p6] = block2;
                                    }
                                }
                         }
                     }
                 }
             }
        }
    }
}

bool chess::checkBound(QPoint p)
{
    return (p.x() >= 0 && p.x() < 15 && p.y() >= 0 && p.y() < 15);
}

QPoint chess::getPos(int row, int col, int dir, int len)
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
            QPoint ed = getPos(st.x(), st.y(), UP + i, 4);//五元组的起点终点
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
        else if (black == 0 && white == 3) return 2000;
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
        else if (white == 0 && black == 3) return 2000;
        else return 200000;
    }
}

/*
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
*/

EVALUATION chess::evaluate(int board[15][15])
{
    const int weight[17] = {0, 1000000, -10000000, 50000, -100000, 400, -100000, 400, -8000, 20, -50, 20, -50, 1, -3, 1, -3};
    int i, j, ty;
    int sta[4][17];
    memset(sta, 0, sizeof (sta));

    int bigBoard[17][17]; // 包围了边界的大棋盘
    for (int i = 0; i < 17; i++)
    {
        bigBoard[i][0] = 3;
    }
    for (int i = 0; i < 17; i++)
    {
        bigBoard[i][16] = 3;
    }
    for (int j = 0; j < 17; j++)
    {
        bigBoard[0][j] = 3;
    }
    for (int j = 0; j < 17; j++)
    {
        bigBoard[16][j] = 3;
    }
    for (int i = 0; i < 15; i++)
    {
        for (int j = 0; j < 15; j++)
        {
            bigBoard[i + 1][j + 1] = board[i][j];
        }
    }
    //横向
    for (i = 1; i <= 15; i++)
    {
        for (j = 0; j < 12; j++)
        {
            ty = type[bigBoard[i][j]][bigBoard[i][j + 1]][bigBoard[i][j + 2]][bigBoard[i][j + 3]][bigBoard[i][j + 4]][bigBoard[i][j + 5]];
            ++sta[0][ty];
        }
    }
    //竖向
    for (j = 1; j <=15; j++)
    {
        for (i = 0; i < 12; i++)
        {
            ty = type[bigBoard[i][j]][bigBoard[i + 1][j]][bigBoard[i + 2][j]][bigBoard[i + 3][j]][bigBoard[i + 4][j]][bigBoard[i + 5][j]];
            ++sta[1][ty];
        }
    }
    //左上至右下
    for (i = 0; i < 12; i++)
    {
        for (j = 0; j < 12; j++)
        {
            ty = type[bigBoard[i][j]][bigBoard[i + 1][j + 1]][bigBoard[i + 2][j + 2]][bigBoard[i + 3][j + 3]][bigBoard[i + 4][j + 4]][bigBoard[i + 5][j + 5]];
            ++sta[2][ty];
        }
    }
    //右上至左下
    for (i = 0; i < 12; i++)
    {
        for (j = 5; j < 17; j++)
        {
            ty = type[bigBoard[i][j]][bigBoard[i + 1][j - 1]][bigBoard[i + 2][j - 2]][bigBoard[i + 3][j - 3]][bigBoard[i + 4][j - 4]][bigBoard[i + 5][j-5]];
            ++sta[3][ty];
        }
    }

    EVALUATION eval;
    memset (eval.STA, 0, sizeof (eval.STA));

    int score = 0;
    for (i = 1; i < 17; i++)
    {
        score += weight[i] * (sta[0][i] + sta[1][i] + sta[2][i] + sta[3][i]);

        int count = sta[0][i] + sta[1][i] + sta[2][i] + sta[3][i];
        if (i == WIN) eval.STA[WIN] = count;
        else if (i == LOSE) eval.STA[LOSE] = count;
        else if (i == FLEX4) eval.STA[FLEX4] = count;
        else if (i == BLOCK4) eval.STA[BLOCK4] = count;
        else if (i == FLEX3) eval.STA[FLEX3] = count;
    }
    eval.res = R_BOTH;

    if (eval.STA[WIN] > 0)eval.res = R_WHITE;
    else if (eval.STA[LOSE] > 0)eval.res = R_BLACK;

    eval.score = score;
    return eval;
}

POINTS chess::seekPoints(int board[15][15])
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
            if (board[i][j] != C_EMPTY)
            {
                for (int k = -3; k <= 3; ++k)
                {
                    int ii, jj;
                    ii = i; jj = j + k;
                    if (jj >= 0 && jj < 15 && board[ii][jj] == C_EMPTY)
                    {
                        can[ii][jj] = 1;
                    }
                    ii = i + k; jj = j;
                    if (ii >= 0 && ii < 15 && board[ii][jj] == C_EMPTY)
                    {
                        can[ii][jj] = 1;
                    }
                    ii = i + k; jj = j + k;
                    if (ii >= 0 && ii < 15 && jj >= 0 && jj < 15 && board[ii][jj] == C_EMPTY)
                    {
                        can[ii][jj] = 1;
                    }
                    ii = i + k; jj = j - k;
                    if (ii >= 0 && ii < 15 && jj >= 0 && jj < 15 && board[ii][jj] == C_EMPTY)
                    {
                        can[ii][jj] = 1;
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
                score[i][j] = calcOnePos(board, i, j, C_WHITE);
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

int chess::analyze(int board[15][15], int dep, int alpha, int beta)
{
    EVALUATION eval = evaluate(board);
    if (dep == 0 || eval.res != R_BOTH)
    {
        ++nodeNum;
        if (dep == 0)
        {
            POINTS p = seekPoints(board);
            return p.score[0];
        }
        else
        {
            return eval.score;
        }
    }
    else if (dep % 2 == 0) // 极大化层，白棋利益最大化
    {
        POINTS p = seekPoints(board);//贪心找出对白最有利的点
        for (int i = 0; i < 10; ++i)
        {
            int copyBoard[15][15];
            copy(board, copyBoard);
            copyBoard[p.pos[i].x()][p.pos[i].y()] = C_WHITE;
            int nxtA = analyze(copyBoard, dep - 1, alpha, beta);
            if (nxtA > alpha)
            {
                alpha = nxtA;
                if (dep == 6)
                {
                    decision.pos = p.pos[i];
                    decision.score = nxtA;
                }
            }
            if (alpha >= beta) break;
        }
        return alpha;
    }
    else// 极小化层，黑棋利益最大化
    {
        int oppBoard[15][15];
        oppsite(board, oppBoard);
        POINTS p = seekPoints(oppBoard);//将棋盘黑白子的颜色取反，贪心找出对黑最有利的点
        for (int i = 0; i < 10; ++i)
        {
            int copyBoard[15][15];
            copy(board, copyBoard);
            copyBoard[p.pos[i].x()][p.pos[i].y()] = C_BLACK;
            int nxtA = analyze(copyBoard, dep - 1, alpha, beta);
            if (nxtA < beta)
            {
                beta = nxtA;
            }
            if (alpha >= beta) break;
        }
        return beta;
    }
}

