#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>
#include <QGLWidget>
#include <GL/gl.h>
#include <QTimer>
#include <QMouseEvent>
#include <QMessageBox>
#include <QDebug>
#include <QApplication>
#include <QDesktopWidget>
#include <QWheelEvent>
#include <QPointF>


#define Rows 1000
#define Cols 1000

class GLWidget: public QGLWidget
{
public:
    GLWidget(QWidget *parent);
    void paintGL();
    void resizeGL(int w, int h);
    void initializeGL();


    int getCountOfLife(int row, int col);
    int getMin(int x, int y);
    int getMax(int x, int y);
    void onTimerTick();
    void drawStep();
    void drawCursor();
    void drawSelection();
    void keyPressEvent(QKeyEvent *event);

    void mousePressEvent(QMouseEvent*);
    void mouseReleaseEvent(QMouseEvent*);
    void mouseMoveEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent*);

   double sizeX, sizeY;


   bool buffer[Rows][Cols];
   bool current[Rows][Cols];

   QPointF* translatePoint;
   QPoint* oldPoint;
   QPoint* newPoint;
   QPoint* deskSize;
   QPoint* cursorPosition;
   QPoint* startSelection;
   QPoint* endSelection;

   int maxX, maxY;

private:
    int countRight;
    int wcnt;
    int timerStep;

};

#endif // GLWIDGETCLASS_H
