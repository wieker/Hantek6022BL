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

void MainWindow::on_textEdit_textChanged()
{
    QString text = ui->textEdit->toPlainText();
}

unsigned char cvtToBin(char hex) {
    if (hex >= 'a') {
        return hex - 'a';
    } else if (hex >= 'A') {
        return hex - 'A';
    } {
        return hex - '0';
    }
}

void MainWindow::on_pushButton_8_clicked()
{
    QString hexCode = ui->textEdit->toPlainText();
    hexCode.replace("\n", "");
    QString pinStr = ui->lineEdit->text();
    QString clkStr = ui->lineEdit_2->text();
    QString fromStr = ui->lineEdit_3->text();
    QString toStr = ui->lineEdit_4->text();

    char* command = new char[11];
    command[0] = 'W';
    command[1] = pinStr.at(0).toAscii();
    int i = 0;
    for (i = 2; i < 10; i ++) {
        if (hexCode.length() >= i * 2 - 2) {
            unsigned char most = 0x10 * cvtToBin(hexCode.at(2 * (i - 2)).toAscii());
            unsigned char least = cvtToBin(hexCode.at(2 * (i - 2) + 1).toAscii());
            command[i] = most + least;
        } else {
            command[i] = command[i - 1];
        }
    }
    command[10] = 0;
    submitCommand((char *) command);
}
