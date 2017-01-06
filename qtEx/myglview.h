#ifndef MYGLVIEW_H
#define MYGLVIEW_H

#include <QWidget>
#include <QtOpenGL/QGLWidget>
#include <QPaintEvent>
#include <QCoreApplication>
#include <QMutex>

#include <iostream>

class MyGLView : QGLWidget
{
public:
    MyGLView(QWidget* parent);
    unsigned char* b = NULL;
    size_t b_size = 0;
    QMutex mutex;
    int posted = 0;

    void _update(unsigned char* b, int q_size) {
        mutex.lock();
        std::cout << "Size: " << q_size << std::endl;
        if (this->b != NULL) {
            free(this->b);
        }
        this->b = (unsigned char *) malloc(q_size);
        memcpy(this->b, b, q_size);
        this->b_size = q_size;
        if (posted == 0) {
            QCoreApplication::postEvent(this, new QPaintEvent(this->rect()));
            posted = 1;
        }
        mutex.unlock();
    }

protected:

    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();
};

#endif // MYGLVIEW_H
