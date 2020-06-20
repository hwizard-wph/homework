#include "gamewighet.h"
#include "ui_gamewighet.h"
#include <QSound>
gamewighet::gamewighet(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::gamewighet)
{
    ui->setupUi(this);
    setFixedSize(1200, 900);
    setWindowTitle("Gobang");
    setWindowIcon(QIcon(":/mark.jpg"));

    for (int i = 0; i < 15; ++i)
    {
        for (int j = 0; j < 15; ++j)
        {
            chessboard[i][j].setX(180 + 50 * i);
            chessboard[i][j].setY(120 + 50 * j);
        }
    }
    //由于qt中坐标轴的原因，再绘制过程中为（i，j）表示第i列第j行的坐标
    //而在棋盘中（i，j）则表示第i行第j列的位置
    connect(this->ui->returnButton, SIGNAL(clicked(bool)), this, SLOT(returnButtonPushed()));
    setMouseTracking(true);
    initGame();
}

gamewighet::~gamewighet()
{
    delete ui;
}

void gamewighet::clearScore()
{
    whiteScore = blackScore = 0;
    ui->lcd_white->display(whiteScore);
    ui->lcd_black->display(blackScore);
}

void gamewighet::returnButtonPushed()
{
    emit returnSignal();
    this->hide();
    playChess.step=0;
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
    painter.drawPixmap(rect(), QPixmap(":/time1.jpg"), QRect());
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
        QRect rec(chessboard[nowCol][nowRow].x() - 6, chessboard[nowCol][nowRow].y() - 6, 12, 12);
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
                painter.drawEllipse(chessboard[j][i].x() - 15, chessboard[j][i].y() - 15, 30, 30);
            }
        }
    }
    //画棋子
}

void gamewighet::mouseMoveEvent(QMouseEvent *event)
{
    if (event->x() >= 180 && event->x() <=930 && event->y() >= 120 && event->y() <= 870)
    {
        setCursor(Qt::BlankCursor);
        for (int i = 0; i < 15; ++i)
        {
            for (int j = 0; j < 15; ++j)
            {
                float x = event->x();
                float y = event->y();
                if (abs(chessboard[i][j].x() - x) <= 15 &&
                    abs(chessboard[i][j].y() - y) <= 15)
                {
                    nowRow = j;
                    nowCol = i;
                    if (playChess.chesses[nowRow][nowCol] != C_EMPTY)
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
    { QSound::play(":/1.wav");
        QString str;
        str = "落子：";
        str += QString::number(nowRow);
        str += "行";
        str += QString::number(nowCol);
        str += "列";
        if (turn == T_BLACK) ui->blackpos->setText(str);
        else ui->whitepos->setText(str);
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
    gameResult res = playChess.evaluate(playChess.chesses).res;
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
    if (mode == AID)
    {
        if(playChess.step>5)
        {
        playChess.nodeNum = 0;
        playChess.analyze(playChess.chesses, 6, INT_MIN, INT_MAX);
        QPoint p = playChess.decision.pos;
        if (isLegalMove(p.x(), p.y()))
        {
            chessMoveOne(p.x(), p.y());
            QString str;
            str = "落子：";
            str += QString::number(p.x());
            str += "行";
            str += QString::number(p.y());
            str += "列";
            ui->whitepos->setText(str);
        }
        playChess.step++;
        }
        else
        {
            playChess.highestScorePos(playChess.chesses);
            QPoint p = playChess.decision.pos;
            if (isLegalMove(p.x(), p.y()))
            {
                chessMoveOne(p.x(), p.y());
                QString str;
                str = "落子：";
                str += QString::number(p.x());
                str += "行";
                str += QString::number(p.y());
                str += "列";
                ui->whitepos->setText(str);
            }
            playChess.step++;

        }
    }
    else
    {
        playChess.highestScorePos(playChess.chesses);
        QPoint p = playChess.decision.pos;

        if (isLegalMove(p.x(), p.y()))
        {
            chessMoveOne(p.x(), p.y());
            QString str;
            str = "落子：";
            str += QString::number(p.x());
            str += "行";
            str += QString::number(p.y());
            str += "列";
            ui->whitepos->setText(str);
        }
        playChess.step++;

    }
}





