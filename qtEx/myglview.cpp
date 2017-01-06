#include "myglview.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include <iostream>

MyGLView::MyGLView(QWidget* parent)
    : QGLWidget(parent)
{
    resize(400, 300);
}

void MyGLView::initializeGL() {

}

void MyGLView::resizeGL(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, w, h, 0);
    glMatrixMode(GL_MODELVIEW);

}

void MyGLView::paintGL() {
    int i = 0;
    mutex.lock();

    std::cout << "update() " << b_size << "\n";

    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glLineWidth(1.0);
    glPointSize(1.0f);
    glColor3f(1.0, 0.0, 0.0);

    glBegin(GL_LINE_STRIP);
    glVertex3f(10, 10, 0.0);
    glVertex3f(20, 20, 0.0);

    /*for (i = 0; i < b_size; i += 2) {
        glVertex3f(i, i % 2 ? 200: 100, 0);
    }*/

    glEnd();
    posted = 0;
    if (b != NULL) {
        free(b);
    }
    b = NULL;
    b_size = 0;
    mutex.unlock();
}

