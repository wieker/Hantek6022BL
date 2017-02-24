#include "mywidget.h"
#include <QPainter>
#include <iostream>

MyWidget::MyWidget(QWidget *parent) : QWidget(parent)
{
    resize(320, 240);
}

void MyWidget::_update(unsigned char *b, int q_size) {
    for (int i = 0; i < q_size; i ++) {
        if (cpos >= 1280 * 1024) {
            cpos = 0;
        }
        buf[cpos ++] = b[i];
    }
    updated ++;
    if (updated > 70) {
        std::cout << "70 updates done!" << std::endl;
        updated = 0;
    }
}

void MyWidget::paintEvent(QPaintEvent *) {
    QPainter painter(this);

    QRectF rectangle(10.0, 20.0, 80.0, 60.0);
    int startAngle = 30 * 16;
    int spanAngle = 120 * 16;
    painter.drawArc(rectangle, startAngle, spanAngle);

    QImage image = QImage(buf, 1280, 1024, QImage::Format_Grayscale8);
    painter.drawImage(rectangle, image);

    for (int i = 0; i < 1000; i ++) {
        (std::cout << std::hex) << (int) buf[i];
    }
    (std::cout << std::dec) << std::endl;
}

