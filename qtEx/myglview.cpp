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
    glDisable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glPointSize(1);

    qglClearColor(QColor(0, 255, 0));

    glShadeModel(GL_SMOOTH/*GL_FLAT*/);
    glLineStipple(1, 0x3333);

    glEnableClientState(GL_VERTEX_ARRAY);
}

void MyGLView::resizeGL(int w, int h) {
    glViewport(0, 0, (GLint) w, (GLint) h);

    glMatrixMode(GL_PROJECTION);

    // Set axes to div-scale and apply correction for exact pixelization
    glLoadIdentity();
    GLdouble pixelizationWidthCorrection = (w > 0) ? (GLdouble) w / (w - 1) : 1;
    GLdouble pixelizationHeightCorrection = (h > 0) ? (GLdouble) h / (h - 1) : 1;
    //glOrtho(-(DIVS_TIME / 2) * pixelizationWidthCorrection, (DIVS_TIME / 2) * pixelizationWidthCorrection, -(DIVS_VOLTAGE / 2) * pixelizationHeightCorrection, (DIVS_VOLTAGE / 2) * pixelizationHeightCorrection, -1.0, 1.0);

    glMatrixMode(GL_MODELVIEW);

}

void MyGLView::paintGL() {
    int i = 0;
    mutex.lock();

    std::cout << "update() " << b_size << "\n";

    glClear(GL_COLOR_BUFFER_BIT);
    glLineWidth(1);

    float arr[] = { 12.0f, 13.0f, 24.0f, 25.0f };

    this->qglColor(QColor(0, 0, 255));
    glVertexPointer(2, GL_FLOAT, 0, arr);
    glDrawArrays(GL_LINE_STRIP, 0, 2);

    posted = 0;
    mutex.unlock();
}

