#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Board.h"
#include "pve.h"
#include "eve.h"
#include "Netgame.h"
#include<QtWidgets>
#include<QMessageBox>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("登录界面");
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_PVP_clicked()
{
    Board * board=new Board();
    QPushButton *renshu=new QPushButton(board);
    QPushButton *qiuhe=new QPushButton(board);
    renshu->setText(tr("认输"));
    qiuhe->setText("求和");
    renshu->resize(300,100);
    qiuhe->resize(300,100);
    qiuhe->move(1100,200);
    renshu->move(1100,800);
    board->show();

}

void MainWindow::on_PVE_clicked()
{
    pve *board=new pve();
    QPushButton *renshu=new QPushButton(board);
    renshu->setText(tr("认输"));
    renshu->resize(300,100);
    renshu->move(1100,800);
    board->show();
}

void MainWindow::on_EVE_clicked()
{
    eve *board=new eve();
    board->show();
}

void MainWindow::on_Internet_clicked()
{
    QMessageBox::StandardButton ret;
    ret= QMessageBox::question(NULL,"server or client","是否作为服务器启动");
    if(ret==QMessageBox::Yes)
    {
        Netgame* board= new Netgame(true);
                board->show();
    }
    else
    {
        Netgame* board= new Netgame(false);
                board->show();
    }
}

void MainWindow::on_quitGame_clicked()
{
    QApplication::quit();
}

