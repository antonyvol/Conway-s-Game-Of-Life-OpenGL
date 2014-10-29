#include "GLWidget.h"
#include <QGLWidget>
#include <GL/gl.h>
#include <QTimer>
#include <QMouseEvent>
#include <QMessageBox>
#include <QDebug>

#define Rows 1000
#define Cols 1000
//>>>>>>>>>>>>>>>>>>>>>>>GLOBAL VARIABLES>>>>>>>>>>>>>>>>>
bool buffer[Rows][Cols];
bool current[Rows][Cols];

float scale = 0.001;
float xCoor = - 1, yCoor = -1;

QPoint* oldPoint;
QPoint* newPoint;

QPoint* cursorPosition;

int currentMouseX, currentMouseY;

GLWidget::GLWidget(QWidget *parent)
{
    cursorPosition = new QPoint(25, 25);
    oldPoint = new QPoint(QCursor::pos().x(),  QCursor::pos().y());

    this->setParent(parent);
    this->grabKeyboard();


    for(int i =0 ; i < Rows; i++)
    {
        for(int j = 0; j < Cols; j++)
        {
            current[i][j] = false;
            buffer[i][j] = false;
        }
    }

    for(int i =250 ; i < 750; i++)
    {
        for(int j = 250; j < 750; j++)
        {
            current[i][j] = true;
             buffer[i][j] = true;
        }
    }
}


void GLWidget::mousePressEvent(QMouseEvent *event)
{
  //  oldPoint = new QPoint(event->x(), this->geometry().height() - event->y());


}

void GLWidget::mouseMoveEvent(QMouseEvent *event)
{
    cursorPosition->setX(oldPoint->x()- QCursor::pos().x());
    cursorPosition->setY(oldPoint->y()- QCursor::pos().y());


  //  if (cursorPosition->x() < 0)
     //   cursorPosition->setX(0);

   // if (cursorPosition->y() < 0)
     //   cursorPosition->setY(0);

   oldPoint->setX(cursorPosition->x());
   oldPoint->setY(cursorPosition->y());

 //   QCursor::setPos(1366 / 2, 768 / 2);
}

void GLWidget::mouseReleaseEvent(QMouseEvent *event)
{
   // newPoint = new QPoint(event->x(), this->geometry().height() - event->y());

//    for(int i = newPoint->x() ; i < oldPoint->x(); i++)
//    {
//        int k = i / .8 * 2;
//        buffer[k][50] = true;
//    }
}


void GLWidget::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Shift)
        scale += 0.0005;
    else if (event->key() == Qt::Key_Control)
        scale -= 0.0005;
    else if (event->key() == Qt::Key_Up)
        yCoor -= 0.1;
    else if(event->key() == Qt::Key_Down)
        yCoor += 0.1;
    else if(event->key() == Qt::Key_Right)
        xCoor -= 0.1;
    else if(event->key() == Qt::Key_Left)
        xCoor += 0.1;

    glLoadIdentity();
    glTranslatef(xCoor, yCoor, 0);
    glScalef(scale, scale, 0);
    glPushMatrix();
}



int GLWidget::getCountOfLife(int row, int col)
{
   int k = 0;
   int leftCol, rightCol, upRow, downRow;
   upRow = row - 1;
   downRow = row + 1;
   leftCol = col - 1;
   rightCol = col + 1;
   //***********CODE FOR CYCLING TABLE**************//
   if(upRow < 0)
       upRow = Rows - 1;
   if(downRow > Rows-1)
       downRow = 0;
   if(leftCol < 0)
       leftCol = Cols - 1;
   if(rightCol > Cols-1)
       rightCol = 0;

    if(current[upRow][leftCol] == true)
        k++;

    if(current[upRow][col] == true)
        k++;

    if(current[upRow][rightCol] == true)
        k++;
    if(current[row][leftCol] == true)
        k++;
    if(current[row][col]== true)
        k++;
    if(current[row][rightCol] == true)
        k++;
    if(current[downRow][leftCol] == true)
        k++;
    if(current[downRow][col] == true)
        k++;
    if(current[downRow][rightCol] == true)
        k++;

    return k;
}


void GLWidget::onTimerTick()
{
   // countRight = 0;

   // wcnt++;



    for(int i =Rows- 1 ; i >= 0; i--){
        for(int j = 0; j < Cols; j++) {


            int count = getCountOfLife(i, j);

            if (!current[i][j]) {
                if (count == 3)
                    buffer[i][j] = true;
            }
            else {
                if (count > 4 || count < 3)
                    buffer[i][j] = false;
            }




          //  if (currentChar == buffer[i][j])
           //     countRight++;

        }
    }
  //  this->Draw();
  //  if (countRight == Rows * Cols)
        //on_startButton_clicked();
    //ui->counterLabel->setText("Time: " + QString::number(wcnt));
    updateGL();
}

void GLWidget::Draw()
{
    for(int i = 0; i < Rows; i++) {
        for(int j = 0; j < Cols; j++) {
     //           currentChar = ui->tableWidget->item(i, j)->text().at(0).toLatin1();
                if (currentChar == buffer[i][j])
                    continue;

                 //ui->tableWidget->item(i, j)->setText(QString(buffer[i][j]));
        }
    }
}

void GLWidget::paintGL(){

    glClear(GL_COLOR_BUFFER_BIT);
    double red;
    double green;

    glColor3f(1,0,0);


    glBegin(GL_QUADS);


    for(int i = 0 ; i < Rows; i++)
    {
        for(int j = 0; j < Cols; j++)
        {
            if (buffer[i][j])
            {

                red = 1/(1+rand()%5);
                green = 1/(1+rand()%5);

                    glColor3f(red,green,0);

                    glVertex2f((i -1 ) / sizeX, (j - 1) / sizeY);
                    glVertex2f( i / sizeX, (j - 1) / sizeY);
                    glVertex2f(i / sizeX, j / sizeY);
                    glVertex2f((i -1 ) / sizeX, j / sizeY);
            }

            current[i][j] = buffer[i][j];
        }
    }

//>>>>>>>>>>>>>>>CURSOR>>>>>>>>>>>>>>>>>>>>.
    int i = cursorPosition->x();
    int j = cursorPosition->y();
    glColor3d(0, 1, 0);

    glVertex2f((i - 25) / sizeX, (j - 25) / sizeY);
    glVertex2f( i / sizeX, (j - 25) / sizeY);
    glVertex2f(i / sizeX, j / sizeY);
    glVertex2f((i - 25 ) / sizeX, j / sizeY);

//    glVertex2f(0, 0);
//    glVertex2f(0.5 / sizeX, 0);
//    glVertex2f(0.5 / sizeX, .5 / sizeY);
//    glVertex2f(0, .5 / sizeY);

    glEnd();
}

void GLWidget::resizeGL(int w, int h){
    glViewport(0, 0, w, h);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();


    glTranslatef(-1, -1, 0);
    glScalef(scale, scale, 0);
    glOrtho(0, 0, 1, 1, 0, 1);
    glPushMatrix();
}
void GLWidget::initializeGL(){
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_COLOR_MATERIAL);
    glEnable(GL_BLEND);
    glEnable(GL_POLYGON_SMOOTH);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glClearColor(1, 1, 1, 0);
}

void GLWidget::drawScene(){

}
