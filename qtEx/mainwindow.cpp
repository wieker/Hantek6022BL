#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <iostream>
#include "urbprocessor.h"

class WorkerThread;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    glWidget = new MyWidget(this);
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
    p = new URBProcessor(glWidget);
    p->dir = -1;
    p->firmware_hex_path = "../qtEx/fw.ihx";
    p->search_vid = 0x0547;
    p->search_pid = 0x1002;
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

void MainWindow::submitCommand(char *command) {
    p->dir = 1;
    p->no_stdio = 1;
    std::cout << "One URB: " + p->SubmitOneURB((unsigned char *) command, strlen(command)) << std::endl;
    p->dir = -1;
    p->no_stdio = 0;
}

void MainWindow::submitCommandWithLength(char *command, int length) {
    p->dir = 1;
    p->no_stdio = 1;
    std::cout << "One URB: " + p->SubmitOneURB((unsigned char *) command, length) << std::endl;
    p->dir = -1;
    p->no_stdio = 0;
}

void MainWindow::on_pushButton_clicked()
{
    submitCommand("11");
}

void MainWindow::on_pushButton_2_clicked()
{
    submitCommand("10");
}


void MainWindow::on_pushButton_4_clicked()
{
    submitCommand("21");
}

void MainWindow::on_pushButton_3_clicked()
{

    submitCommand("20");
}

void MainWindow::on_pushButton_6_clicked()
{

    submitCommand("31");
}

void MainWindow::on_pushButton_5_clicked()
{

    submitCommand("30");
}

void MainWindow::on_pushButton_7_clicked()
{
    submitCommand("P1");
}

unsigned char cvtToBin(char hex) {
    if (hex >= 'a') {
        return hex - 'a' + 0xa;
    } else if (hex >= 'A') {
        return hex - 'A' + 0xa;
    } {
        return hex - '0';
    }
}

void MainWindow::on_pushButton_9_clicked()
{
    submitCommandWithLength("R", 1);
}

void MainWindow::on_pushButton_10_clicked()
{
    submitCommandWithLength("G", 1);
}

void MainWindow::on_pushButton_11_clicked()
{
    glWidget->update();
}
