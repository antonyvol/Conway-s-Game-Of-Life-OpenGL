#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "GLWidget.h"

#include <QGLWidget>

#include<GL/gl.h>

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


//>>>>>>>>>>>>>>>>>>>>>>>>>TABLE DOUBLE CLICKING>>>>>>>>>>>>>>>>>>>>>>>
/// :   Some function for add a new 'live' in cell
void MainWindow::on_tableWidget_doubleClicked(const QModelIndex &index)
{
//    if(ui->tableWidget->item(index.row(),index.column())->text() == "#")
//        ui->tableWidget->setItem(index.row(), index.column(), new QTableWidgetItem(" "));
//    else
//        ui->tableWidget->setItem(index.row(), index.column(), new QTableWidgetItem("#"));

}
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>CHANGE TIMER STEP>>>>>>>>>>>>>>>>>>>>
void MainWindow::on_timerStepSlider_valueChanged(int value)
{
//    mainTimer->stop();
//    timerStep = value;
//    mainTimer->start(value);
}
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>RESET>>>>>>>>>>>>>>>>>>>>>>>>>>>
void MainWindow::on_resetButton_clicked()
{
//    wcnt = 0;
//    for(int i = 0; i < Rows; i++) {
//        for(int j = 0; j < Cols; j++) {
//            buffer[i][j] = ' ';
//            ui->tableWidget->setItem(i, j, new QTableWidgetItem(" "));
//        }
//    }
}
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>RANDOM FILL OF SELECTED AREA>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void MainWindow::on_randomButton_clicked()
{
//    QList<QTableWidgetItem*> items = ui->tableWidget->selectedItems();
//    for(int i = 0; i < items.count(); ++i) {
//        int random = rand()%2;
//        if(mainTimer->isActive()) {
//            if(random)
//                buffer[items.at(i)->row()][items.at(i)->column()] = '#';
//        }
//        else {
//            if(random)
//                ui->tableWidget->setItem(items.at(i)->row(), items.at(i)->column(), new QTableWidgetItem("#"));
//        }
//    }
//    ui->tableWidget->clearSelection();
}
//>>>>>>>>>>>>>>>>>>>>>>>>>>FILL OF SELECTED AREA>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void MainWindow::on_fillButton_clicked()
{
//    QList<QTableWidgetItem*> items = ui->tableWidget->selectedItems();
//    for(int i = 0; i < items.count(); ++i)
//        if(mainTimer->isActive())
//            buffer[items.at(i)->row()][items.at(i)->column()] = '#';
//        else
//            ui->tableWidget->setItem(items.at(i)->row(), items.at(i)->column(), new QTableWidgetItem("#"));
//    ui->tableWidget->clearSelection();
}

    void MainWindow::onTimerTick()
    {
        mainThread->onTimerTick();
        cnt++;
        ui->label->setText(QString::number(cnt));

        ui->counterLabel->setText(QString("X: ") +QString::number( mainThread->mapFromGlobal(QCursor::pos()).x()) + QString(" Y: ") + QString::number( mainThread->mapFromGlobal(QCursor::pos()).y()));
    }
