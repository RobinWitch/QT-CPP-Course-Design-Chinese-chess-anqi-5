#ifndef NETGAME_H
#define NETGAME_H

#include"Board.h"
#include<QTcpServer>
#include<QTcpSocket>


class Netgame:public Board
{
 public:
    Q_OBJECT
public:
    Netgame(bool server);
    void mousePressEvent(QMouseEvent *ev);

    QTcpServer* _server;
    QTcpSocket* _socket;

public slots:
    void slotNewConnection();
    void slotRecv();
};

#endif // NETGAME_H
