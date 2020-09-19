#ifndef EVE_H
#define EVE_H

#include"Board.h"

class eve:public Board
{
 public:
    eve();
    int RedCalculateScore();   //评价分值
    int BlackCalculateScore();
    bool search(int row,int col);  //检查当前点是否能走
    int numUnshow();    //统计棋盘上当前未翻面的棋子
    void mousePressEvent(QMouseEvent *ev);
};

#endif // EVE_H
