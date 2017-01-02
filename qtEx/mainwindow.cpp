#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <qopenglcontext.h>
#include <qopenglfunctions.h>

#include <iostream>
#include "urbprocessor.h"

class WorkerThread;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    glWidget = new MyGLView(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_loadButton_clicked()
{
    /*glWidget->makeCurrent();
    glWidget->context()->functions()->glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glWidget->context()->functions()->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glWidget->doneCurrent();*/
}

void MainWindow::on_glBox_aboutToCompose()
{

}

void MainWindow::on_fwButton_clicked()
{
    p = new URBProcessor();
    p->dir = -1;
    p->firmware_hex_path = "../qtEx/fw.ihx";
    p->search_vid = 0x04b4;
    p->search_pid = 0x602a;
    std::cout << "Connect: " + p->ConnectAndInitUSB() << std::endl;
    std::cout << p->SubmitInitialURBs() << std::endl;
    startWorkInAThread();
}

void MainWindow::startWorkInAThread()
{
    WorkerThread *workerThread = new WorkerThread();
    workerThread->pipe = p;
    //connect(workerThread, &WorkerThread::resultReady, this, &MyObject::handleResults);
    //connect(workerThread, &WorkerThread::finished, workerThread, &QObject::deleteLater);
    workerThread->start();
}

void MainWindow::on_pushButton_clicked()
{
    p->dir = 1;
    p->no_stdio = 1;
    std::cout << "One URB: " + p->SubmitOneURB((unsigned char *) "AAA", 3) << std::endl;
    p->dir = -1;
    p->no_stdio = 0;
}

void MainWindow::on_pushButton_2_clicked()
{
    p->dir = 1;
    p->no_stdio = 1;
    std::cout << "One URB: " + p->SubmitOneURB((unsigned char *) "BBB", 3) << std::endl;
    p->dir = -1;
    p->no_stdio = 0;
}

