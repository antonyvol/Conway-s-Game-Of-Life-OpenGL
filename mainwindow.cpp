#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <GLWidget.h>

QTimer* mainTimer;
GLWidget * mainThread;

//>>>>>>>>>>>>>>>>>>>>>>>CONSTRUCTOR>>>>>>>>>>>>>>>>>>>
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    cnt = 0;

    mainTimer = new QTimer();
    mainTimer->setInterval(20);

    connect(mainTimer, SIGNAL(timeout()), SLOT(onTimerTick()));

    mainThread = new GLWidget(this);
    mainThread->setGeometry(ui->glWidget->x(), ui->glWidget->y(), ui->glWidget->geometry().width(), ui->glWidget->geometry().height());

    ui->glWidget = mainThread;



    this->setWindowState(Qt::WindowMaximized);
    mainTimer->start();
}

//>>>>>>>>>>>>>>>>>>>>>>>>DESTRUCTOR>>>>>>>>>>>>>>
MainWindow::~MainWindow()
{
    delete ui;
}

//>>>>>>>>>>>>>>>>>>>>>>>>RESIZE WINDOW EVENT>>>>>>>>>>>>>
void MainWindow::resizeEvent(QResizeEvent * s)
{
    s->accept();
    mainThread->setGeometry(mainThread->x(), mainThread->y(), s->size().width() - 15, s->size().height() - 50);

    mainThread->sizeX = (double)(this->geometry().width()) / 1000;
    mainThread->sizeY = (double)(this->geometry().height()) / 1000;
}



void MainWindow::on_startButton_clicked()
{
    if (mainTimer->isActive()) {
        mainTimer->stop();
        ui->startButton->setText("Not active");
    }
    else {
        mainTimer->start(100);
        ui->startButton->setText("Active");
    }
}


//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>CHANGE TIMER STEP>>>>>>>>>>>>>>>>>>>>
void MainWindow::on_timerStepSlider_valueChanged(int value)
{
    ui->label->setText("Time step: " + QString::number(value));
    mainTimer->stop();
    mainTimer->start(value);
}
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>RESET>>>>>>>>>>>>>>>>>>>>>>>>>>>
void MainWindow::on_resetButton_clicked()
{
    for(int i = 0; i < Rows; i++)
        for(int j = 0; j < Cols; j++)
        {
             mainThread->buffer[i][j] = false;
             mainThread->current[i][j] = false;
        }
}
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>RANDOM FILL OF SELECTED AREA>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void MainWindow::on_randomButton_clicked()
{
    int random = 0;

    for(int i = mainThread->getMin(mainThread->startSelection->x(), mainThread->endSelection->x()); i < mainThread->getMax(mainThread->startSelection->x(), mainThread->endSelection->x()); i++)
    {
        for(int j = mainThread->getMin(mainThread->startSelection->y(), mainThread->endSelection->y()); j < mainThread->getMax(mainThread->startSelection->y(), mainThread->endSelection->y()); j++)
        {
            random = rand() %2;
            mainThread->buffer[i][j] = random;
        }
    }

    mainThread->startSelection->setX(0);
    mainThread->startSelection->setY(0);
    mainThread->endSelection->setX(0);
    mainThread->endSelection->setY(0);
}
//>>>>>>>>>>>>>>>>>>>>>>>>>>FILL OF SELECTED AREA>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void MainWindow::on_fillButton_clicked()
{
    for(int i = mainThread->getMin(mainThread->startSelection->x(), mainThread->endSelection->x()); i < mainThread->getMax(mainThread->startSelection->x(), mainThread->endSelection->x()); i++)
    {
        for(int j = mainThread->getMin(mainThread->startSelection->y(), mainThread->endSelection->y()); j < mainThread->getMax(mainThread->startSelection->y(), mainThread->endSelection->y()); j++)
        {
            mainThread->buffer[i][j] = true;
        }
    }

    mainThread->startSelection->setX(0);
    mainThread->startSelection->setY(0);
    mainThread->endSelection->setX(0);
    mainThread->endSelection->setY(0);
}

void MainWindow::onTimerTick()
{
    mainThread->onTimerTick();
    cnt++;
    ui->counterLabel->setText("Time: " + QString::number(cnt));
}
