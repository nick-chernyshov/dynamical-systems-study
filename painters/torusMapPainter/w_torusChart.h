#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <map>
#include <QFile>
#include <functional>
#include <QGraphicsScene>
#include <set>
#include <QFileDialog>

namespace Ui {
class MainWindow;
}



class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    QFileDialog fileDialog;

    QPixmap * chartPixels;
    QGraphicsScene * chartGraphics;


    void readChart(QFile & ifile, bool addData = false);
    int lyapCounter, lyapComputed;

    QColor SelectColor(int mode, std::vector<int> wNumbers);

    QColor SelectColor(std::vector<std::vector<int> >& dataSet);


protected:
    QColor SelectColorLyap(std::vector<std::vector<int> > &dataSet);
    QColor SelectColorLyap(int mode, std::vector<int> wNumbers);
private slots:
    void on_action_triggered();

    void on_action_2_triggered();

    void on_action_3_triggered();

    void on_action_4_triggered();

private:
    std::map <double, std::map<double, std::vector<std::vector<int> > > > data;
    std::pair<double, double> XYMin, XYMax;

    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
