#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_loadButton_clicked();

    void on_glBox_aboutToCompose();

    void on_fwButton_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
