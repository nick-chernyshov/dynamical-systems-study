#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QFile>
#include <map>
#include <vector>

#include <QFileDialog>

static const double limit = 0.001;

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

    QPixmap * lyapunovPixels;
    QGraphicsScene * lyapunovGraphics;

    std::map <double, std::map <double, std::vector<double> > > data;
    std::pair<double, double> XYMin, XYMax;


    void readChart(QFile & ifile);
    int lyapCounter, lyapComputed;

    QColor SelectColor(std::vector<double>& lyaps, double limit,std::vector<QColor> chaoticColors,  std::vector<QColor> periodicColors, std::vector<QColor> quasiperiodicColors);
private slots:
    void on_action_3_triggered();

    void on_action_4_triggered();

    void on_action_2_triggered();

    void on_action_triggered();

    void on_action_5_triggered();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
