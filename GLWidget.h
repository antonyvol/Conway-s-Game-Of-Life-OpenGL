#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>

class GLWidget: public QGLWidget
{
public:
    GLWidget(QWidget *parent);
    void paintGL();
    void resizeGL(int w, int h);
    void initializeGL();
    int getCountOfLife(int row, int col);
    void drawScene();
    void Draw();
    void onTimerTick();
    void keyPressEvent(QKeyEvent *event);

    void mousePressEvent(QMouseEvent*);
    void mouseReleaseEvent(QMouseEvent*);
    void mouseMoveEvent(QMouseEvent *event);

   double sizeX, sizeY;

private:

    char currentChar;

    int countRight;
    int wcnt;
    int timerStep;

};

#endif // GLWIDGETCLASS_H
