#ifndef STONE_H
#define STONE_H
#include<QString>
#include<ctime>
#include<cstdlib>

class Stone
{
public:
    Stone(){}
    ~Stone(){}

    enum TYPE {BING=1,MA=2,CHE=4,XIANG=6,SHI=8,JIANG=12,PAO=10};

    int _row;
    int _col;
    int _id;
    bool _dead;//存活是false，死亡是true
    bool _red;//红色是true，黑色是false
    int _side;//side=0是背面朝上，side>0是正面朝上
    TYPE _type;//正面是false，背面是true
    bool _clicked=false;//是否被处于准备移动阶段

    int test[32];
    int i=0;

    void construct(int id)
    {
        for(int i0=0;i0<32;i0++)
        {test[i0]=100;}

        srand((int)time(0));
        for(;i<32;i++)
        {
           test[i]=(rand()%4*10+rand()%8);
            for(int i2=0;i2<i;i2++)
                if(test[i]==test[i2])
                {
                    i--;
                    break;
                }

        }

        struct {
            int row, col;
            Stone::TYPE type;
        } pos[32] = {
        {test[0]/10,test[0]%10, Stone::CHE},
        {test[1]/10,test[1]%10, Stone::MA},
        {test[2]/10,test[2]%10, Stone::XIANG},
        {test[3]/10,test[3]%10, Stone::SHI},
        {test[4]/10,test[4]%10, Stone::JIANG},
        {test[5]/10,test[5]%10, Stone::SHI},
        {test[6]/10,test[6]%10, Stone::XIANG},
        {test[7]/10,test[7]%10, Stone::MA},
        {test[8]/10,test[8]%10, Stone::CHE},
        {test[9]/10,test[9]%10, Stone::PAO},
        {test[10]/10,test[10]%10, Stone::PAO},
        {test[11]/10,test[11]%10, Stone::BING},
        {test[12]/10,test[12]%10, Stone::BING},
        {test[13]/10,test[13]%10, Stone::BING},
        {test[14]/10,test[14]%10, Stone::BING},
        {test[15]/10,test[15]%10, Stone::BING},
        {test[16]/10,test[16]%10, Stone::CHE},
        {test[17]/10,test[17]%10, Stone::MA},
        {test[18]/10,test[18]%10, Stone::XIANG},
        {test[19]/10,test[19]%10, Stone::SHI},
        {test[20]/10,test[20]%10, Stone::JIANG},
        {test[21]/10,test[21]%10, Stone::SHI},
        {test[22]/10,test[22]%10, Stone::XIANG},
        {test[23]/10,test[23]%10, Stone::MA},
        {test[24]/10,test[24]%10, Stone::CHE},
        {test[25]/10,test[25]%10, Stone::PAO},
        {test[26]/10,test[26]%10, Stone::PAO},
        {test[27]/10,test[27]%10, Stone::BING},
        {test[28]/10,test[28]%10, Stone::BING},
        {test[29]/10,test[29]%10, Stone::BING},
        {test[30]/10,test[30]%10, Stone::BING},
        {test[31]/10,test[31]%10, Stone::BING},
        };


        _id=id;
        _dead=false;
        _red=id<16;
        _side=0;

        if(_dead)
        {
            _row=id/8+5;
            _col=id%8;

        }
        else
        {
            _row=pos[id].row;
            _col=pos[id].col;
            _type=pos[id].type;
        }



    }

    QString getText()
    {
        if(this->_red)
        {
            switch(this->_type)
            {
            case CHE:
                return "俥";
            case MA:
                return "傌";
            case PAO:
                return "炮";
            case BING:
                return "兵";
            case JIANG:
                return "帥";
            case SHI:
                return "仕";
            case XIANG:
                return "相";
             }
        }
        else
        {
            switch(this->_type)
            {
            case CHE:
                return "車";
            case MA:
                return "馬";
            case PAO:
                return "砲";
            case BING:
                return "卒";
            case JIANG:
                return "將";
            case SHI:
                return "士";
            case XIANG:
                return "象";
             }
        }
        return "错误";
    }

};

#endif // STONE_H
