#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QObject>
#include <QWidget>

class MyWidget : public QWidget
{
    int cpos = 0;
    unsigned char* buf = new unsigned char[1280 * 1024];
    int updated = 0;

    Q_OBJECT
public:
    explicit MyWidget(QWidget *parent = 0);
    void _update(unsigned char* b, int q_size);
    void paintEvent(QPaintEvent *);

signals:

public slots:
};

#endif // MYWIDGET_H
