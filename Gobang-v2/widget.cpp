#include "widget.h"
#include "ui_widget.h"
#include "gamewighet.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    setFixedSize(700, 600);
    setWindowTitle("Gobang");
    setWindowIcon(QIcon(":/mark.jpg"));
    game = new gamewighet();
    game->hide();
    connect(this->ui->btn_player, SIGNAL(clicked(bool)), this, SLOT(playerButtonPushed()));
    connect(this->ui->btn_aid, SIGNAL(clicked(bool)), this, SLOT(aiDButtonPushed()));
    connect(this->ui->btn_aie, SIGNAL(clicked(bool)), this, SLOT(aiEButtonPushed()));
    connect(game, &gamewighet::returnSignal, this, &Widget::show);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.drawPixmap(rect(), QPixmap(":/timg.jpg"), QRect());
}

void Widget::playerButtonPushed()
{
    this->hide();
    game->show();
    game->clearScore();
    game->setMode(PEOPLE);
}

void Widget::aiEButtonPushed()
{
    this->hide();
    game->show();
    game->clearScore();
    game->setMode(AIE);
}

void Widget::aiDButtonPushed()
{
    this->hide();
    game->show();
    game->clearScore();
    game->setMode(AID);
}
