#include "Board.h"
#include<QPainter>
#include<QtWidgets>
#include<mainwindow.h>

Board::Board(QWidget *parent) : QWidget(parent)   //Board构造函数
{
    Turn->resize(100,50);
    Turn->move(1200,100);
    this->setFixedSize(1500,1200);
    this->setWindowTitle("象棋暗棋比大小");
    for(int i=0;i<32;i++)
    {
        _s[i].construct(i);//对每个棋子进行位置、颜色、死亡、是否翻面的初始化
    }

}
void Board::paintEvent(QPaintEvent*)      //画棋盘和棋子
{
    QPainter painter(this);

    int d=100;  //棋子直径
    _r=d/2;

    for(int i=1;i<=10;i++)  //画十条横线
    {
        painter.drawLine(QPoint(d,i*d),QPoint(9*d,i*d));
    }

    for(int i=1;i<=9;i++)   //画九条竖线
    {
        if(i==1||i==9)
            painter.drawLine(QPoint(d*i,d),QPoint(i*d,10*d));
        else
        {
            painter.drawLine(QPoint(d*i,d),QPoint(i*d,5*d));
            painter.drawLine(QPoint(d*i,6*d),QPoint(i*d,10*d));
        }
    }

    painter.drawLine(QPoint(d*4,d),QPoint(6*d,3*d));    //画九宫格
    painter.drawLine(QPoint(d*6,d),QPoint(4*d,3*d));
    painter.drawLine(QPoint(d*4,10*d),QPoint(6*d,8*d));
    painter.drawLine(QPoint(d*6,10*d),QPoint(4*d,8*d));


    for(int i=0;i<32;i++)   //画32个棋子
    {
        drawStone(painter,i);
    }
}

QPoint Board::center(int row,int col)   //根据行列求出对应方块（棋子）中心点坐标，以QPoint类型返回
{
    QPoint ret;
    ret.rx()=(col+1.5)*(_r)*2;
    ret.ry()=(row+1.5)*(_r)*2;
    return ret;
}
QPoint Board::center(int id)
{
    return center(_s[id]._row,_s[id]._col);
}

void Board::drawStone(QPainter &painter,int id)     //给每个棋子写字上色显字
{
    QPoint c=center(id);
    QRect rect=QRect(c.rx()-(_r),c.ry()-(_r),(_r)*2,(_r)*2);

    painter.setBrush(QBrush(QColor(255,255,0)));   //棋子背景颜色
    if(_s[id]._clicked)     painter.setBrush(QBrush(QColor(169,169,169)));

        painter.drawEllipse(center(id),_r,_r);      //画圆
        if(_s[id]._side)
        {
            if(_s[id]._side)
                    painter.setPen(Qt::black);  //画黑色矩形框以承载字体

            if(_s[id]._red)
                painter.setPen(Qt::red);  //将黑色矩形框换为红色矩形框


                painter.setFont(QFont("楷体", _r-20, 100));  //字体

                painter.drawText(rect,_s[id].getText(),QTextOption(Qt::AlignCenter));
        }
}

bool Board::getRowCol(QPoint pt, int &row, int &col)
{
    for(row=0;row<4;row++)
    {
        for(col=0;col<8;col++)
        {
            QPoint c=center(row,col);
            if(((pt.x()-c.x())*(pt.x()-c.x())+(pt.y()-c.y())*(pt.y()-c.y()))<(_r)*(_r))
                return true;
        }
    }
    return false;
}
void Board::mousePressEvent(QMouseEvent *ev)
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
                    _turn=!_turn;
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
    else
         Turn->setText("黑方执子");

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
bool Board::moveRule(int i,int j)   //镶嵌在eatRule函数中
{
    if(_s[i]._type!=Stone::PAO)
    {
        if(((_s[i]._row-_s[j]._row)*(_s[i]._row-_s[j]._row)+(_s[i]._col-_s[j]._col)*(_s[i]._col-_s[j]._col))==1)
            return true;
        return false;
    }

    else
    {
        int num=0;
        if(!(_s[i]._row==_s[j]._row||_s[i]._col==_s[j]._col))   return false;
        else if(_s[i]._row==_s[j]._row)
        {
            int colmax=_s[i]._col>_s[j]._col?_s[i]._col:_s[j]._col;
            int colmin=_s[i]._col<_s[j]._col?_s[i]._col:_s[j]._col;
            for(int tem=0;tem<32;tem++)
            {
                if(_s[tem]._row==_s[i]._row)
                    if(_s[tem]._col>colmin&&_s[tem]._col<colmax)    num++;
            }
            if(num==1) return true;
            else    return false;
        }
        else if(_s[i]._col==_s[j]._col)
        {
            int rowmax=_s[i]._row>_s[j]._row?_s[i]._row:_s[j]._row;
            int rowmin=_s[i]._row<_s[j]._row?_s[i]._row:_s[j]._row;
            for(int tem=0;tem<32;tem++)
            {
                if(_s[tem]._col==_s[i]._col)
                    if(_s[tem]._row>rowmin&&_s[tem]._row<rowmax)    num++;
            }
            if(num==1) return true;
            else    return false;
        }
    }
    return false;
}
bool Board::eatRule(int i, int j)       //_s[i]是移动子，_s[j]是被吃子
{

    if(_s[i]._red==_s[j]._red)  return false;
    if(moveRule(i,j))
    {

       switch (_s[i]._type)
      {

        case Stone::JIANG:
            if(_s[j]._type!=Stone::BING)   return true;
            else    return false;

        case Stone::SHI:
            if(_s[j]._type!=Stone::JIANG)  return true;
            else    return false;

        case Stone::XIANG:
            if(_s[j]._type!=Stone::JIANG&&_s[j]._type!=Stone::SHI)    return true;
            else    return false;

        case Stone::CHE:
            if(_s[j]._type!=Stone::JIANG&&_s[j]._type!=Stone::SHI&&_s[j]._type!=Stone::XIANG)    return true;
            else    return false;

        case Stone::MA:
            if(_s[j]._type==Stone::PAO||_s[j]._type==Stone::BING)     return true;
            else    return false;

        case Stone::PAO:
            if(_s[j]._type!=Stone::MA)     return true;
            else    return false;

        case Stone::BING:
            if(_s[j]._type==Stone::JIANG)  return true;
            else    return false;

        default:
            return false;
       }
    }
    return false;
}
int Board::judge1() //评判标准1.检查一方棋子是否被吃光，返回值为0，胜负暂时未分；返回值为1，红方胜利；返回值为2，黑方胜利
{
       for(int i=16;i<32;i++)
       {
           if(!_s[i]._dead) break;
           if(i==31)    return 1;
       }
       for(int i=0;i<16;i++)
       {
           if(!_s[i]._dead) break;
           if(i==15)    return 2;
       }

       return 0;

}
bool Board::judge2() //评判标准2，检查双方是否和棋，返回值为false，双方暂未和棋;返回值为true，双方和棋
{
    if(frequence>20)    return true;
    else return false;
}
void Board::mouseReleaseEvent()
{
    update();
}
