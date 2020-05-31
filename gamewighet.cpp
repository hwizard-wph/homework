#include "gamewighet.h"
#include "ui_gamewighet.h"

gamewighet::gamewighet(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::gamewighet)
{
    ui->setupUi(this);

    for (int i = 0; i < 15; ++i)
    {
        for (int j = 0; j < 15; ++j)
        {
            chessboard[i][j].setX(20 + 30 * i);
            chessboard[i][j].setY(20 + 30 * j);
        }
    }
    connect(this->ui->returnButton, SIGNAL(click(bool)), this, SLOT(returnButtonPushed()));
    setMouseTracking(true);
    initGame();
}

gamewighet::~gamewighet()
{
    delete ui;
}

void gamewighet::returnButtonPushed()
{
    emit returnSignal();
    this->hide();
    initGame();
}

void gamewighet::initGame()
{
    for (int i = 0; i < 15; ++i)
    {
        for (int j = 0; j < 15; ++j)
        {
            playChess.chesses[i][j] = C_EMPTY;
        }
    }
    status = PLAYING;
    turn = T_BLACK;
    nowRow = nowCol = -1;
}

void gamewighet::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(Qt::black);
    for (int i = 0; i < 15; ++i)
    {
        painter.drawLine(chessboard[i][0], chessboard[i][14]);
        painter.drawLine(chessboard[0][i], chessboard[14][i]);
    }
    //画棋盘
    if (turn == T_BLACK) painter.setBrush(Qt::black);
    else painter.setBrush(Qt::white);
    if (nowCol != -1 && nowRow != -1)
    {
        QRect rec(chessboard[nowCol][nowRow].x() - 4, chessboard[nowCol][nowRow].y() - 4, 8, 8);
        painter.drawRect(rec);
    }
    //画光标
    for (int i = 0; i < 15; ++i)
    {
        for (int j = 0; j < 15; ++j)
        {
            if (playChess.chesses[i][j] != C_EMPTY)
            {
                if (playChess.chesses[i][j] == C_BLACK) painter.setBrush(Qt::black);
                else painter.setBrush(Qt::white);
                painter.drawEllipse(chessboard[i][j].x() - 10, chessboard[i][j].y() - 10, 20, 20);
            }
        }
    }

}

void gamewighet::mouseMoveEvent(QMouseEvent *event)
{
    if (event->x() >= 5 && event->x() <=455 && event->y() >= 5 && event->y() <= 5)
    {
        setCursor(Qt::BlankCursor);
        for (int i = 0; i < 15; ++i)
        {
            for (int j = 0; j < 15; ++j)
            {
                if (abs(chessboard[i][j].x() - event->x()) <= 15 &&
                    abs(chessboard[i][j].y() - event->x()) <= 15)
                {
                    nowCol = i;
                    nowRow = j;
                    if (playChess.chesses[i][j] != C_EMPTY)
                    {
                        setCursor(Qt::ForbiddenCursor);
                    }
                    break;
                }
            }
        }
    }
    else
    {
        setCursor(Qt::ArrowCursor);
    }
    update();
}

void gamewighet::mouseReleaseEvent(QMouseEvent *event)
{
    if(mode == PEOPLE)
    {
        if (chessOneByPlayer())
        {
            if (status == FINISH)
            {
                initGame();
            }
        }
    }
    else
    {
        if (chessOneByPlayer())
        {
            if (status == PLAYING)
            {
                chessOneByAI();
                if (status == FINISH)
                {
                    initGame();
                }
            }
            else
            {
                initGame();
            }
        }
    }
}

bool gamewighet::chessOneByPlayer()
{
    if (playChess.chesses[nowRow][nowCol] == C_EMPTY)
    {
        chessMoveOne(nowRow, nowCol);
        return true;
    }
    return false;
}

bool gamewighet::isDeadGame()
{
    int number = 0;
    for (int i = 0; i < 15; ++i)
    {
        for (int j = 0; j < 15; ++j)
        {
            number += (playChess.chesses[i][j] != C_EMPTY);
        }
    }
    return (number == 15 * 15);
}

bool gamewighet::isLegalMove(int row, int col)
{
    return (playChess.chesses[row][col] == C_EMPTY);
}

void gamewighet::chessMoveOne(int row, int col)
{
    if (turn == T_BLACK)
    {
        turn = T_WHITE;
        playChess.chesses[row][col] = C_BLACK;
    }
    else
    {
        turn = T_BLACK;
        playChess.chesses[row][col] = C_WHITE;
    }
    gameResult res = playChess.evaluate(playChess.chesses).result;
    QMessageBox msg;
    msg.setIcon(QMessageBox::Critical);
    msg.setStandardButtons(QMessageBox::Ok);
    if (res != R_BOTH)
    {
        status = FINISH;
        if (res == R_WHITE)
        {
            msg.setText("白棋获胜");
            ++whiteScore;
        }
        else
        {
            msg.setText("黑棋获胜");
            ++blackScore;
        }
        msg.exec();
        ui->lcd_white->display(whiteScore);
        ui->lcd_black->display(blackScore);
    }
    else if (isDeadGame())
    {
        status = FINISH;
        msg.setText("平局");
        msg.exec();
    }
    update();
}

void gamewighet::chessOneByAI()
{
    playChess.nodeNum = 0;
    if (!playChess.kill(playChess.chesses, 16))
    {
        playChess.analyze(playChess.chesses, 6, INT_MIN, INT_MAX);
    }
    QPoint p = playChess.decison.pos;
    if (isLegalMove(p.x(), p.y()))
    {
        chessMoveOne(p.x(), p.y());
    }
}





