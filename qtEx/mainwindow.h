#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QThread>
#include "../fx2pipe-0.8/fx2pipe/fx2pipe.h"
#include <iostream>
#include "myglview.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    MyGLView* glWidget;

private slots:
    void on_loadButton_clicked();

    void on_glBox_aboutToCompose();

    void on_fwButton_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_5_clicked();

private:
    FX2Pipe* p;
    Ui::MainWindow *ui;

    void startWorkInAThread();
    void submitCommand(char* command);
};

class WorkerThread : public QThread
{
    Q_OBJECT
    void run() {
        QString result;
        pipe->dir = -1;
        pipe->no_stdio = 0;
        for (;;) {
            std::cout << pipe->ProcessEvents(1000) << std::endl;
        }
        emit resultReady(result);
    }
signals:
    void resultReady(const QString &s);
public:
    FX2Pipe* pipe;
};

#endif // MAINWINDOW_H
