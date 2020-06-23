#include "gamewighet.h"
#include "ui_gamewighet.h"
#include <QDateTime>
#include <QSound>
#include<QDir>
#include <QFileDialog>
using namespace std;
gamewighet::gamewighet(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::gamewighet)
{   QFile file("test.txt");
    file.remove();
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
    connect(this->ui->pushButton, SIGNAL(clicked(bool)), this, SLOT(regretChess()));
    connect(this->ui->saveButton,SIGNAL(clicked(bool)),this,SLOT(saveButtonPushed()));
    connect(this->ui->loadButton,SIGNAL(clicked(bool)),this,SLOT(loadButtonPushed()));
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
    QFile file("test.txt");
    file.remove();
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
    for(int i=1;i<=playChess.step;i++)
    {
        playChess.record[i].setX(0);
        playChess.record[i].setY(0);
    }
    playChess.step=0;
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
                if(i==m && j==n && turn==T_BLACK)
                {
                    painter.drawRect(chessboard[j][i].x() - 5, chessboard[j][i].y() - 5, 10, 10);
                }
                else if(i==m && j==n &&turn==T_WHITE)
                {
                    painter.setBrush(Qt::white);
                    painter.drawRect(chessboard[j][i].x() - 5, chessboard[j][i].y() - 5, 10, 10);
                }
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
    {
        QSound::play(":/1.wav");
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
        playChess.step++;
        turn = T_WHITE;
        playChess.chesses[row][col] = C_BLACK;
        playChess.recordRow=row;
        playChess.recordCol=col;
        playChess.record[playChess.step].setX(playChess.recordRow);
        playChess.record[playChess.step].setY(playChess.recordCol);
        m=row;
        n=col;

    }
    else
    {
        playChess.step++;
        turn = T_BLACK;
        playChess.chesses[row][col] = C_WHITE;
        playChess.recordRow=row;
        playChess.recordCol=col;
        playChess.record[playChess.step].setX(playChess.recordRow);
        playChess.record[playChess.step].setY(playChess.recordCol);
        m=row;
        n=col;

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
            playChess.step=0;
        }
        else
        {
            msg.setText("黑棋获胜");
            ++blackScore;
            playChess.step=0;
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
        if (playChess.step > 5)
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

            }

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


    }

}

void gamewighet::regretChess()
{
    QMessageBox msg;
    msg.setIcon(QMessageBox::Critical);
    msg.setStandardButtons(QMessageBox::Ok);
    if (playChess.step == 0) {
        msg.setText("无棋可悔");
        msg.exec();
        return;
    }
    if (mode == PEOPLE)
    {
        playChess.chesses[playChess.recordRow][playChess.recordCol] = C_EMPTY;
        playChess.step--;
        playChess.recordRow = playChess.record[playChess.step].x();
        playChess.recordCol = playChess.record[playChess.step].y();
        if(playChess.step%2==1)
        {
            turn=T_WHITE;
        }
        else turn=T_BLACK;
    }
    else
    {
        for(int i=0;i<2;i++)
        {
            playChess.chesses[playChess.recordRow][playChess.recordCol] = C_EMPTY;
            playChess.step--;
            playChess.recordRow = playChess.record[playChess.step].x();
            playChess.recordCol = playChess.record[playChess.step].y();
        }
        turn=T_BLACK;
    }

    update();
}
void gamewighet::saveButtonPushed()
{
    QFile filex("test.txt");
    filex.remove();
    QFile file("test.txt");
    file.open(QIODevice::ReadWrite);
    file.close();
    if (file.open(QIODevice::ReadWrite | QIODevice::Text))
    {
        QTextStream stream(&file);
        stream.seek(file.size());
        for (int i = 1; i <= playChess.step; ++i)
        {


                    if (i%2==1)
                        stream <<playChess.record[i].x()<<endl<<playChess.record[i].y()<<endl<<"1"<<endl;
                    else if(i%2==0)
                        stream <<playChess.record[i].x()<<endl<<playChess.record[i].y()<<endl<<"2"<<endl;
                    //stream <<i<<endl<<j<<endl<<"2"<<endl;


        }
        file.close();
    }
    QString curPath = QDir::currentPath();
        QString fileName;
        fileName =QFileDialog::getExistingDirectory(this, "请选择保存棋谱文件的路径...", "./");
        QString filePath1 = curPath,filePath2 = fileName;
        filePath1.append("/test.txt");
        QString str_time;
        QDateTime time = QDateTime::currentDateTime();
        str_time = time.toString("yyyy-MM-dd_hh-mm-ss");
        filePath2+=("/"+str_time+".txt");
        QFile file1(filePath1);
        file1.copy(filePath2);
}

void gamewighet::loadButtonPushed()
{
    QString fileName =QFileDialog::getOpenFileName(this,tr("选择棋局文件"),"",tr("TXT(*.txt)"));
    QFile file(fileName);
        //qDebug()<<fileName;
        i=0;
        if (file.open(QIODevice::ReadWrite | QIODevice::Text))
        {
            initGame();
            while (!file.atEnd())
            {
                int r,c,d=0;
                if(i%3==0)
                {
                    i++;
                    QByteArray line = file.readLine();
                    const char* txt(line);
                    //qDebug()<<i;

                    r = atoi(txt);
                    //qDebug()<<"录入R坐标"<<r;


                }
                else if(i%3==1)
                {
                    i++;
                    QByteArray line = file.readLine();
                    const char* txt(line);
                    c= atoi(txt);
                    //qDebug()<<i;
                    //qDebug()<<"录入C坐标"<<c;
                }
                else if(i%3==2)
                {
                    QPainter painter;
                    QByteArray line = file.readLine();
                    const char* txt(line);
                    d=atoi(txt);
                    if (d == 1)
                    {
                        i++;
                        // playChess.chesses[r][c]=C_BLACK;
                        //qDebug()<<r;
                        //qDebug()<<c;
                        chessMoveOne(r,c);
                        //qDebug()<<i;
                        //qDebug()<<"黑色落子";

                    }
                    else if (d == 2)
                    {
                        i++;
                        //playChess.chesses[r][c]=C_WHITE;
                        //qDebug()<<r;
                        //qDebug()<<c;
                        chessMoveOne(r,c);
                        //qDebug()<<i;
                        //qDebug()<<"白色落子";

                    }
                    else
                    {
                        QMessageBox msg;
                        msg.setIcon(QMessageBox::Critical);
                        msg.setStandardButtons(QMessageBox::Ok);
                        msg.setText("选择文件有误");
                        msg.exec();
                        initGame();
                        break;
                    }

                }
            }
        }

    update();
}
