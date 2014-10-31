#include "GLWidget.h"


const bool cursorS[9][9] = {true, true, true, true, true, true, true, true, true,
                           true, true, true, true, true, true, true, true, true,
                           true, true, true, true, true, true, true, true, true,
                           true, false, true, true, true, true, true, true, true,
                           true, false, false, true, true, true, true, true, true,
                           false, false, false, false, true, true, true, true, true,
                           false, false, false, false, false, true, true, true, true,
                           false, false, false, false, false, false, true, true, true,
                           false, false, false, false, false, false, false, true, true

};

bool grabMode = false;
bool selectionMode = false;
bool translateMode = false;

float scale = 0.001;

GLWidget::GLWidget(QWidget *parent)
{
    translatePoint = new QPointF(-1, -1);

    cursorPosition = new QPoint(Rows/2, Cols/2);
    oldPoint = new QPoint(Rows / 2, Cols / 2);
    newPoint = new QPoint(Rows / 2, Cols / 2);
    startSelection = new QPoint();
    endSelection = new QPoint();

    this->setParent(parent);
    this->grabKeyboard();

    QDesktopWidget* desk = new QDesktopWidget();
    deskSize = new QPoint(desk->geometry().width(), desk->geometry().height());


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
    if (event->button() == Qt::RightButton)
    {
        if (grabMode)
        {
            grabMode = false;
            this->setMouseTracking(false);
                        this->releaseMouse();
            QApplication::setOverrideCursor(Qt::ArrowCursor);
        }
        else
        {
            QCursor::setPos(deskSize->x() / 2, deskSize->y() / 2);
            grabMode = true;
            this->grabMouse();
            this->setMouseTracking(true);
            QApplication::setOverrideCursor(Qt::BlankCursor);
            oldPoint->setX(QCursor::pos().x());
            oldPoint->setY(QCursor::pos().y());
        }
    }
    else if (event->button() == Qt::LeftButton)
    {
        if (grabMode)
        {
            selectionMode = true;
            startSelection->setX(cursorPosition->x());
            startSelection->setY(cursorPosition->y());
        }
    }
    else if (event->button() == Qt::MidButton && grabMode == true)
    {
        QCursor::setPos(deskSize->x() / 2, deskSize->y() / 2);
        translateMode = true;
        oldPoint->setX(QCursor::pos().x());
        oldPoint->setY(QCursor::pos().y());
    }

}

void GLWidget::mouseMoveEvent(QMouseEvent *event)
{
    if (grabMode && QCursor::pos().x() != deskSize->x() / 2 && QCursor::pos().y() != deskSize->y() / 2)
    {
    newPoint->setX(QCursor::pos().x());
    newPoint->setY(QCursor::pos().y());

    if ((cursorPosition->x() + newPoint->x() - oldPoint->x()) > 0)
    cursorPosition->setX((cursorPosition->x() + newPoint->x() - oldPoint->x()));

    if ((cursorPosition->y() + -(newPoint->y() - oldPoint->y())) > 0)
    cursorPosition->setY((cursorPosition->y() + -(newPoint->y() - oldPoint->y())));


    if (translateMode)
    {
        translatePoint->setX(translatePoint->x() + (newPoint->x() - oldPoint->x()) * 0.001);
        translatePoint->setY(translatePoint->y() + -(newPoint->y() - oldPoint->y()) * 0.001);
    }


    QCursor::setPos(deskSize->x() / 2, deskSize->y() / 2);

    oldPoint->setX(deskSize->x() / 2);
    oldPoint->setY(deskSize->y() / 2);

    if (selectionMode)
    {
        endSelection->setX(cursorPosition->x());
        endSelection->setY(cursorPosition->y());
     }
    }
}

void GLWidget::mouseReleaseEvent(QMouseEvent *event)
{
    if (grabMode)
    {
        if (event->button() == Qt::LeftButton)
        {
            selectionMode = false;
            endSelection->setX(cursorPosition->x());
            endSelection->setY(cursorPosition->y());
        }
        else if (event->button() == Qt::MidButton)
        {
            translateMode = false;
        }
    }
}

void GLWidget::wheelEvent(QWheelEvent *event)
{
    scale += event->delta() * 0.000001;

    glTranslatef(0.5, 0.5, 0);
}


void GLWidget::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_W)
        translatePoint->setY(translatePoint->y() - 0.1);
    else if(event->key() == Qt::Key_S)
        translatePoint->setY(translatePoint->y() + 0.1);
    else if(event->key() == Qt::Key_D)
        translatePoint->setX(translatePoint->x() - 0.1);
    else if(event->key() == Qt::Key_A)
        translatePoint->setX(translatePoint->x() + 0.1);
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
    for(int i = Rows- 1 ; i >= 0; i--){
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
        }
    }

    updateGL();
}

void GLWidget::drawStep()
{
    glColor3f(1,0,0);
    for(int i = 0 ; i < Rows; i++)
    {
        for(int j = 0; j < Cols; j++)
        {
            if (buffer[i][j])
            {
                    glVertex2f((i -1 ) / sizeX, (j - 1) / sizeY);
                    glVertex2f( i / sizeX, (j - 1) / sizeY);
                    glVertex2f(i / sizeX, j / sizeY);
                    glVertex2f((i -1 ) / sizeX, j / sizeY);
            }
            current[i][j] = buffer[i][j];
        }
    }
}

void GLWidget::drawCursor()
{
    if (cursorPosition->x() > Cols)
        cursorPosition->setX(Cols);
    else if (cursorPosition->x() < 1)
        cursorPosition = 0;


    if (cursorPosition->y() > Rows)
        cursorPosition->setY(Rows);
    else if (cursorPosition->y() < 1)
        cursorPosition = 0;


    glColor3f(0,1,0);

    for(int i = 0; i < 9; i++)
    {
        for(int j = 0; j < 9; j++)
        {
            if (cursorS[i][j])
            {
                glVertex2f(((i + cursorPosition->x()) -1 ) / sizeX, (j + cursorPosition->y() - 1) / sizeY);
                glVertex2f( (i + cursorPosition->x()) / sizeX, (j + cursorPosition->y()- 1) / sizeY);
                glVertex2f((i+ cursorPosition->x()) / sizeX, (j+ cursorPosition->y()) / sizeY);
                glVertex2f((i + cursorPosition->x() -1 ) / sizeX, (j+ cursorPosition->y()) / sizeY);
            }
        }
    }
}


void GLWidget::drawSelection()
{
   glColor3f(0, 0, 1);
   for(int i = getMin(startSelection->x(), endSelection->x()); i < getMax(startSelection->x(), endSelection->x()); i++)
   {
       for(int j = getMin(startSelection->y(), endSelection->y()); j < getMax(startSelection->y(), endSelection->y()); j++)
       {
           glVertex2f((i -1 ) / sizeX, (j - 1) / sizeY);
           glVertex2f( i / sizeX, (j - 1) / sizeY);
           glVertex2f(i / sizeX, j / sizeY);
           glVertex2f((i -1 ) / sizeX, j / sizeY);
       }
   }
}

void GLWidget::resizeGL(int w, int h){
    glViewport(0, 0, w, h);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();


    glTranslatef(-0.5, -0.5, 0);
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

void GLWidget::paintGL(){

    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(translatePoint->x(), translatePoint->y(), 0);
    glScalef(scale, scale, 0);
    glPushMatrix();

    glBegin(GL_QUADS);

        drawSelection();
        drawStep();
        drawCursor();

    glEnd();

    swapBuffers();
}


int GLWidget::getMin(int x, int y)
{
    if (x < y)
        return x;
    else
        return y;
}
int GLWidget::getMax(int x, int y)
{
    if (x > y)
        return x;
    else
        return y;
}
