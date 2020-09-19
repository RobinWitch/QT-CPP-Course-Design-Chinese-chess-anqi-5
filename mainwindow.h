#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <Board.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void on_PVP_clicked();
    void on_PVE_clicked();
    void on_EVE_clicked();
    void on_Internet_clicked();
    void on_quitGame_clicked();
private slots:

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
