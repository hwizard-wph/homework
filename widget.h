#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "gamewighet.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
private slots:
    void playerButtonPushed();
    void aiButtonPushed();
private:
    Ui::Widget *ui;
    gamewighet *game;
};
#endif // WIDGET_H
