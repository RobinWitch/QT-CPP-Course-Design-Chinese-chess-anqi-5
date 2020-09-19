#include "eve.h"


eve::eve()
{

}

int eve::BlackCalculateScore()
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

int eve::RedCalculateScore()
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

    finalScore=redScore-blackScore;
    return finalScore;
}

int eve::numUnshow()
{
    int num=0;
    for(int i=0;i<32;i++)
        if(_s[i]._side==0)  num++;
    return num;
}

bool eve::search(int row, int col)
{
    if(row<0||row>3||col<0||col>7)  return false;
    for(int i=0;i<32;i++)
        if(!_s[i]._dead&&_s[i]._row==row&&_s[i]._col==col)
            return false;
    return true;
}

void eve::mousePressEvent(QMouseEvent *ev)
{
    {
     int eat=0;
     int eaten=0;
     int best=0;
     if(ev->button()==Qt::LeftButton&&_turn)
     {
         int i=0;
         int j=0;
         for(;i<16;i++)  //判断最优吃子
         {
             if(_s[i]._side&&!_s[i]._dead)
             {
                 for(j=16;j<32;j++)
                     if(_s[j]._side&&!_s[j]._dead&&eatRule(i,j))
                     {
                         _s[j]._dead=true;
                         if(RedCalculateScore()>best)
                         {
                             best=RedCalculateScore();
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
                   Rand1=rand()%16;
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
    {
     int eat=0;
     int eaten=0;
     int best=0;
     if(ev->button()==Qt::LeftButton&&!_turn)
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
                         if(BlackCalculateScore()>best)
                         {
                             best=BlackCalculateScore();
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
}
