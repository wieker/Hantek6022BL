#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QObject>
#include <QWidget>

class MyWidget : public QWidget
{
    int cx = 0, cy = 0;

    Q_OBJECT
public:
    explicit MyWidget(QWidget *parent = 0);
    void _update(unsigned char* b, int q_size);

signals:

public slots:
};

#endif // MYWIDGET_H
