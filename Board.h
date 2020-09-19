#ifndef BOARD_H
#define BOARD_H

#include <QWidget>
#include"Stone.h"
#include<QMouseEvent>
#include<QtWidgets>
#include<QObject>

class Board : public QWidget
{
    Q_OBJECT
    public:
    explicit Board(QWidget *parent = 0);
    QLabel *Turn=new QLabel("红方执子",this);
    Stone _s[32];
    int _r;//棋子半径
    int frequence=0;    //判断和棋步数
    bool _turn=true;    //判断此时执子方,true：此时红方执子；false：此时黑方执子

    QPoint center(int row,int col);     //返回棋盘对应的窗口坐标
    QPoint center(int id);

    void drawStone(QPainter &painter,int id);   //给棋子上色
    void paintEvent(QPaintEvent *);             //画棋盘
    bool getRowCol(QPoint pt,int &row,int &col);    //判断鼠标是否点击棋盘内，并且改变row。col
    bool moveRule(int i,int j);   //检测棋子是否移动正确
    bool eatRule(int i,int j);//检查棋子是否吃子正确
    int judge1();
    bool judge2();
    void buttonExit();  //点击按钮确定退出
    void mousePressEvent(QMouseEvent *ev);      //实现棋子移动，吃子等操作
    void mouseReleaseEvent();


signals:

public slots:
};

#endif // BOARD_H
