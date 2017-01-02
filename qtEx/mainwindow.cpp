#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <qopenglcontext.h>
#include <qopenglfunctions.h>
#include "/home/wieker/source/fx2pipe-0.8/fx2pipe/fx2pipe.h"

#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_loadButton_clicked()
{
    ui->glBox->makeCurrent();
    ui->glBox->context()->functions()->glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    ui->glBox->context()->functions()->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    ui->glBox->doneCurrent();
}

void MainWindow::on_glBox_aboutToCompose()
{

}

void MainWindow::on_fwButton_clicked()
{
    FX2Pipe p;
    p.dir = -1;
    p.firmware_hex_path = "../qtEx/fw.ihx";
    p.search_vid = 0x04b4;
    p.search_pid = 0x602a;
    std::cout << p.ConnectAndInitUSB() << std::endl;
    p.dir = 1;
    p.no_stdio = 1;
    //std::cout << "One URB: " + p.SubmitOneURB((unsigned char *) "AaaaaBBbC", 9) << std::endl;
    std::cout << "One URB: " + p.SubmitOneURB((unsigned char *) "BAaaaaBBbC", 10) << std::endl;
    p.dir = -1;
    p.no_stdio = 0;
    std::cout << p.SubmitInitialURBs() << std::endl;
    for (int i = 0; i < 10; i ++) {
        std::cout << p.ProcessEvents(1000) << std::endl;
    }
    p.dir = 1;
    p.no_stdio = 1;
    std::cout << "One URB: " + p.SubmitOneURB((unsigned char *) "AaCCcCaaaBBbC", 12) << std::endl;
    p.dir = -1;
    p.no_stdio = 0;
    std::cout << p.SubmitInitialURBs() << std::endl;
    for (int i = 0; i < 10; i ++) {
        std::cout << p.ProcessEvents(1000) << std::endl;
    }
}
