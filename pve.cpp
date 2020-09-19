#include "pve.h"
#include<QTimer>

pve::pve()
{}

int pve::calculateScore()
{
    int i;
    int blackScore=0;
    int redScore=0;
    int finalScore=0;
    for(i=15;i<32;i++)
    {
        if(_s[i]._side&&!_s[i]._dead)
            blackScore+=_s[i]._type;
    }

    for(i=0;i<16;i++)
    {
        if(_s[i]._red&&_s[i]._side&&!_s[i]._dead)
            redScore+=_s[i]._type;
    }

    finalScore=blackScore-redScore;
    return finalScore;
}

int pve::numUnshow()
{
    int num=0;
    for(int i=0;i<32;i++)
        if(_s[i]._side==0)  num++;
    return num;
}
bool pve::search(int row, int col)
{
    if(row<0||row>3||col<0||col>7)  return false;
    for(int i=0;i<32;i++)
        if(!_s[i]._dead&&_s[i]._row==row&&_s[i]._col==col)
            return false;
    return true;
}
void pve::mousePressEvent(QMouseEvent *ev)
{
    if(ev->button()!=Qt::LeftButton)    return;
   {
    QPoint pt=ev->pos();
    int row,col,i,j;
    if(getRowCol(pt,row,col))
    {
        for(i=0;i<32;i++)   //选中棋子
        {
            if(_s[i]._row==row&&_s[i]._col==col)
            {
                _s[i]._side++;
                if(_s[i]._side==1)
                    _turn=!_turn;   //翻面
                break;
            }
        }
        update();//刷新界面

     if(i<32)
      {
        for(j=0;j<32;j++)
            if(_s[j]._clicked)
                break;

        if(j==32&&(_s[i]._side>1))
        {
            _s[i]._clicked=true;
        }

        else if((_s[i]._side>1)&&eatRule(j,i)&&(_turn==_s[j]._red)) //实现吃子
        {
            _s[j]._row=_s[i]._row;
            _s[j]._col=_s[i]._col;
            _s[j]._clicked=false;
            _s[i]._dead=true;
            frequence=0;
            _turn=!_turn;
            update();
        }

        else
            {
             _s[j]._clicked=false;  //走棋错误，棋子点击数清零

             }

        for(int i=0;i<32;i++)   //安放死棋
        {
            if(_s[i]._dead)
            {
                _s[i]._row=i/8+5;
                _s[i]._col=i%8;
                update();
            }
        }
       }
      else
     {
         for(j=0;j<32;j++)
             if(_s[j]._clicked)
                {  _s[j]._clicked=false;
                    break;
                }

         if(j<32&&(_turn==_s[j]._red))   //实现棋子移动，判断和棋
         {
            if(((_s[j]._row-row)*(_s[j]._row-row)+(_s[j]._col-col)*(_s[j]._col-col))==1)
             {
              _s[j]._row=row;
              _s[j]._col=col;
              frequence++;
              _turn=!_turn;
             }
         }

     }


    }

    if(Board::_turn)    //判断执子方
         Turn->setText("红方执子");

   }
    switch (judge1())   //判断输赢
    {
    case 0:
        break;

    case 1:
    {
        QDialog* end1=new QDialog(this);
        end1->move(600,500);
        end1->resize(400,300);
        end1->move(600,500);
        QLabel* Text1=new QLabel(end1);
        Text1->move(150,90);
        Text1->setText("红方胜利！");
        QPushButton* Button1=new QPushButton(end1);
        Button1->setText("确定");
        Button1->move(140,150);
        end1->show();
        Text1->show();
        Button1->show();
        break;
    }

    case 2:
    {
        QDialog* end2=new QDialog(this);
        end2->move(600,500);
        end2->resize(400,300);
        end2->move(600,500);
        QLabel* Text2=new QLabel(end2);
        Text2->move(150,90);
        Text2->setText("黑方胜利！");
        QPushButton* Button2=new QPushButton(end2);
        Button2->setText("确定");
        Button2->move(140,150);
        end2->show();
        Text2->show();
        Button2->show();
        break;
     }

    }
    if(judge2())
    {
        QDialog* end1=new QDialog(this);
        end1->move(600,500);
        end1->resize(400,300);
        end1->move(600,500);
        QLabel* Text=new QLabel(end1);
        Text->move(150,90);
        Text->setText("和局！");
        QPushButton* Button1=new QPushButton(end1);
        Button1->setText("确定");
        Button1->move(140,150);
        end1->show();
        Text->show();
        Button1->show();
    }

   {
    int eat=0;
    int eaten=0;
    int best=0;
    if(ev->button()==Qt::LeftButton&&!_turn&&!(judge1()))
    {
        int i=16;
        int j=0;
        for(;i<32;i++)  //判断最优吃子
        {
            if(_s[i]._side&&!_s[i]._dead)
            {
                for(j=0;j<16;j++)
                    if(_s[j]._side&&!_s[j]._dead&&eatRule(i,j))
                    {
                        _s[j]._dead=true;
                        if(calculateScore()>best)
                        {
                            best=calculateScore();
                            eaten=j;
                            eat=i;
                        }
                        _s[j]._dead=false;
                        update();
                    }

            }
        }

        if(best)
        {
            _s[eat]._row=_s[eaten]._row;
            _s[eat]._col=_s[eaten]._col;
            _s[eaten]._dead=true;
            update();
        }

        if(best==0)
        {
          if(numUnshow())
           {
            while(1)
            {
                srand((int)time(0));
                int randNum=rand();
                if(_s[randNum%32]._side==0)
                {
                    _s[randNum%32]._side=1;
                    break;
                }
            }
           }
          else
          {
              int Rand1;
              int Rand2;
              int Row,Col;
              while(1)
              {
                  Rand2=rand()%4;
                  Rand1=16+rand()%16;
                  switch(Rand2)
                  {
                   case 0:
                      Row=1;  Col=0;
                      break;
                   case 1:
                      Row=0;  Col=1;
                      break;
                   case 2:
                      Row=-1; Col=0;
                      break;
                   case 3:
                      Row=0;  Col=-1;
                      break;
                  }
                  if(_s[Rand1]._dead)   continue;
                  if(search(_s[Rand1]._row+Row,_s[Rand1]._col+Col))
                  {
                      (_s[Rand1]._row)+=Row;
                      (_s[Rand1]._col)+=Col;
                      break;
                  }
              }
          }

        }

        update();
        _turn=!_turn;
    }
   }
    switch (judge1())   //判断输赢
    {
    case 0:
        break;

    case 1:
    {
        QDialog* end1=new QDialog(this);
        end1->move(600,500);
        end1->resize(400,300);
        end1->move(600,500);
        QLabel* Text1=new QLabel(end1);
        Text1->move(150,90);
        Text1->setText("红方胜利！");
        QPushButton* Button1=new QPushButton(end1);
        Button1->setText("确定");
        Button1->move(140,150);
        end1->show();
        Text1->show();
        Button1->show();
        break;
    }

    case 2:
    {
        QDialog* end2=new QDialog(this);
        end2->move(600,500);
        end2->resize(400,300);
        end2->move(600,500);
        QLabel* Text2=new QLabel(end2);
        Text2->move(150,90);
        Text2->setText("黑方胜利！");
        QPushButton* Button2=new QPushButton(end2);
        Button2->setText("确定");
        Button2->move(140,150);
        end2->show();
        Text2->show();
        Button2->show();
        break;
     }

    }
    if(judge2())
    {
        QDialog* end1=new QDialog(this);
        end1->move(600,500);
        end1->resize(400,300);
        end1->move(600,500);
        QLabel* Text=new QLabel(end1);
        Text->move(150,90);
        Text->setText("和局！");
        QPushButton* Button1=new QPushButton(end1);
        Button1->setText("确定");
        Button1->move(140,150);
        end1->show();
        Text->show();
        Button1->show();
    }
}
