#include "widget.h"
#include "ui_widget.h"
#include "gamewighet.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    game = new gamewighet();
    connect(this->ui->btn_player,SIGNAL(clicked(bool)),this,SLOT(playerButtonPushed()));
    connect(this->ui->btn_ai,SIGNAL(clicked(bool)),this,SLOT(aiButtonPushed()));
    connect(game, &gamewighet::returnSignal, this, &Widget::show);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::playerButtonPushed() {
    this->hide();
}

void Widget::aiButtonPushed() {
    this->hide();
}
