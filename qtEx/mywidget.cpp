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

    QRectF rectangle(0.0, 0.0, 320.0, 240.0);
    QImage image = QImage(1280, 1024, QImage::Format_RGB32);
    int pos = 0;
    for (int i = 0; i < 1024; i ++) {
        for (int j = 0; j < 1280; j ++) {
            image.setPixel(j, i, qRgba(buf[pos] * 10, (int) buf[pos] * 10, (int) buf[pos] * 10, 0));
            if (pos < 100) (std::cout << std::hex) << (int) buf[pos];
            if (pos < 100) std::cout << " ";
            pos ++;
        }
    }

    (std::cout << std::dec) << std::endl;
    painter.drawImage(rectangle, image);
    int startAngle = 30 * 16;
    int spanAngle = 120 * 16;
    painter.drawArc(rectangle, startAngle, spanAngle);

    color += 100;
}

