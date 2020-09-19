#ifndef PVE_H
#define PVE_H

#include"Board.h"

class pve:public Board
{
  public:
    pve();
    int calculateScore();   //评价分值
    bool search(int row,int col);  //检查当前点是否能走
    int numUnshow();    //统计棋盘上当前未翻面的棋子
    void mousePressEvent(QMouseEvent *ev);

};

#endif // PVE_H
