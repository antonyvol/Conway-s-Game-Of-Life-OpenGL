#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QModelIndex>
#include <QResizeEvent>
#include <QTimer>
#include <QList>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void resizeEvent(QResizeEvent*);
    int getCountOfLife(int row, int col);
    void Draw();
    int cnt;



private:
    Ui::MainWindow *ui;

private slots:
    void on_startButton_clicked();
    void on_tableWidget_doubleClicked(const QModelIndex &index);
    void on_timerStepSlider_valueChanged(int value);
    void on_resetButton_clicked();
    void on_randomButton_clicked();
    void on_fillButton_clicked();
    void onTimerTick();
};

#endif // MAINWINDOW_H
