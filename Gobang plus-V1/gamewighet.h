#ifndef GAMEWIGHET_H
#define GAMEWIGHET_H

#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
#include <QMessageBox>
#include <QMap>
#include <QDebug>
#include <QRect>
#include <QIcon>
#include "chess.h"

using namespace std;

namespace Ui {
class gamewighet;
}

class gamewighet : public QWidget
{
    Q_OBJECT

public:
    explicit gamewighet(QWidget *parent = nullptr);
    ~gamewighet();
    void initGame();
    void clearScore();
    void setMode(gameMode md) {mode = md;}
    bool chessOneByPlayer();
    void chessMoveOne(int, int);
    bool isDeadGame();
    bool isLegalMove(int, int);


protected:
    void paintEvent(QPaintEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;//实际落子

signals:
    void returnSignal();
private slots:
    void returnButtonPushed();
    void chessOneByAI();
    void regretChess();

private:
    Ui::gamewighet *ui;
    gameMode mode; //游戏的模式
    gameTurn turn; //轮到黑/白下
    gameStatus status; //游戏的状态
    QPoint chessboard[15][15];  // 棋盘的坐标,第i列第j行
    chess playChess;  //真正的棋盘在chess类里面
    int nowRow, nowCol; //光标的位置
    int blackScore, whiteScore; //黑/白的得分

};

#endif // GAMEWIGHET_H
