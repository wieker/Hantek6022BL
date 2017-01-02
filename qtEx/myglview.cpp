#include "myglview.h"
#include <GL/gl.h>
#include <GL/glu.h>

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

    glClear(GL_COLOR_BUFFER_BIT);

    glLineWidth(1.0);
    glPointSize(1.0f);
    glColor3f(1.0, 0.0, 0.0);

    glBegin(GL_LINE_STRIP);
    glVertex3f(0.0, 540, 0.0);

    /*for (i = 0; i < 2 * SCREEN; i += 2) {
        glVertex3f(i / 2, (1000 - b[cpos + i * zoom] * 3), 0);
    }*/

    glEnd();
}

