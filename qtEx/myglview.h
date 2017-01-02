#ifndef MYGLVIEW_H
#define MYGLVIEW_H

#include <QWidget>
#include <QtOpenGL/QGLWidget>

class MyGLView : QGLWidget
{
public:
    MyGLView(QWidget* parent);
protected:

    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();
};

#endif // MYGLVIEW_H
