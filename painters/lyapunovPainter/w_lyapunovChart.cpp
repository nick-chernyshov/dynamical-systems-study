#include "w_lyapunovChart.h"
#include "ui_lyapunovChart.h"

#include <QImage>
#include <QPixmap>
#include <qfiledialog.h>

#include <fstream>
#include <string>



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    fileDialog(nullptr, "Открыть файл", "", "*.dat;*.txt")
{
    ui->setupUi(this);
    lyapunovGraphics = new QGraphicsScene();
    lyapunovPixels = new QPixmap();

}

MainWindow::~MainWindow()
{
    delete ui;
    delete lyapunovGraphics;
    delete lyapunovPixels;
}

void MainWindow::readChart(QFile &ifile)
{

    ifile.open(QFile::ReadOnly);

    while (!ifile.atEnd())
    {
        double posX, posY;


        QString dataLine = ifile.readLine();

        QStringList valuesAsStrings = dataLine.split(' ');
        bool isOk = false;

        posX = valuesAsStrings[0].toDouble(&isOk); if (!isOk)continue;

        posY = valuesAsStrings[1].toDouble(&isOk); if (!isOk)continue;


        std::vector<double> lyaps;
        for (int i = 2; i < valuesAsStrings.size(); i++)
        {
            QString & sNumber = valuesAsStrings[i];
            double val = sNumber.toDouble(&isOk);
            if (isOk)
                lyaps.push_back(val);
        }

        if (data.find(posX) != data.end())
            if (data.at(posX).find(posY) != data.at(posX).end())
            {
                for (int i = 0; i < lyaps.size(); i++)
                    if (data[posX][posY][i] < lyaps[i])
                    {
                        lyaps[i] = data[posX][posY][i];
                    }
            }
        data[posX][posY] = lyaps;

    }
    ifile.close();
}



void MainWindow::on_action_3_triggered()
{
    data.clear();
    QStringList filenames = fileDialog.getOpenFileNames(
                nullptr,"Открыть файлы",fileDialog.directory().path(),"text(*.txt *.dat); all files(*.*)");
    for (int i = 0; i < filenames.size(); i++)
    {
        QString filename = filenames[i];
        QFile ifile(filename);
        if (ifile.exists())
        {
            readChart(ifile);
        }
    }
}


QColor MainWindow::SelectColor(std::vector<double>& lyaps, double limit, std::vector<QColor> chaoticColors,  std::vector<QColor> periodicColors, std::vector<QColor> quasiperiodicColors)
{
    const int initRegime = 128;
    int regimeType = initRegime, colorIndex = 0;
    for (int i = 0; i < lyaps.size(); i++)
    {
        if (lyaps[i] == 0)
            continue;

        if (lyaps[i] > limit && i < chaoticColors.size())
        {
            regimeType = 0;
            colorIndex = i;
            continue;
        }

        if (regimeType > 0)
        {
            if (std::abs(lyaps[i]) < limit && i < quasiperiodicColors.size())
            {
                regimeType = 1;
                colorIndex = i;
                continue;
            }
        }
        if (regimeType > 1)
        {
            if (lyaps[i] < -limit && i < periodicColors.size())
            {
                regimeType = 2;
                colorIndex = i;
                continue;
            }
        }
    }

    switch (regimeType) {
        case 0:
            return chaoticColors[colorIndex];
        case 1:
            return quasiperiodicColors[colorIndex];
        case 2:
            return periodicColors[colorIndex];
        default:
            return QColor(255,255,255);
    }
    return QColor(255,255,255);
}

void MainWindow::on_action_4_triggered()
{
    QString limitStr = ui->plainTextEdit->toPlainText();
    double limit = limitStr.toDouble();
    if (data.size())
    {
        size_t w = data.size();
        size_t h = data.begin()->second.size();
        QImage * canvas = new QImage(w, h, QImage::Format_RGB32);
        int px = 0;
        for (auto posX : data)
        {
            int py = 0;
            for (auto posY : posX.second)
            {
                std::vector<double> & lyaps = posY.second;

                std::vector<QColor> chaoticColors;
                chaoticColors.push_back(QColor(0,0,0)); // black
                chaoticColors.push_back(QColor(0,128,0)); // darkGreen
                chaoticColors.push_back(QColor(255,255,255)); // white

                std::vector<QColor> quasiperiodicColors;
                quasiperiodicColors.push_back(QColor(255,255,0)); // yellow
                quasiperiodicColors.push_back(QColor(0,0,128)); // darkBlue
                quasiperiodicColors.push_back(QColor(0,255,0)); // brightGreen

                std::vector<QColor> periodicColors;
                periodicColors.push_back(QColor(255,0,0)); // brightRed


                QColor pixColor = SelectColor(lyaps, limit, chaoticColors,  periodicColors, quasiperiodicColors);
                QRgb rgbCode = pixColor.rgb();
                canvas->setPixel(px, h - py - 1, rgbCode);
                py++;
            }
            px++;
        }
        *lyapunovPixels = lyapunovPixels->fromImage(*canvas);
        lyapunovGraphics->clear();
        lyapunovGraphics->addPixmap(*lyapunovPixels);
        ui->graphicsView->setScene(lyapunovGraphics);

        QRect graphicsViewPos = ui->graphicsView->geometry();
        ui->graphicsView->setGeometry(graphicsViewPos.x(), graphicsViewPos.y(),
                                      w+1,h+1);

        delete canvas;
    }

}

void MainWindow::on_action_2_triggered()
{

    QStringList filenames = fileDialog.getOpenFileNames(
                nullptr,tr("Открыть файлы"),fileDialog.directory().path(),"text (*.txt *.dat);; all files (*.*)");
    for (int i = 0; i < filenames.size(); i++)
    {
        QString filename = filenames[i];
        QFile ifile(filename);
        if (ifile.exists())
        {
            readChart(ifile);
        }
    }
}

void MainWindow::on_action_triggered()
{
    data.clear();
    lyapunovGraphics->clear();
    ui->graphicsView->setScene(lyapunovGraphics);

    QRect graphicsViewPos = ui->graphicsView->geometry();
    ui->graphicsView->setGeometry(graphicsViewPos.x(), graphicsViewPos.y(),
                                  0,0);
    ui->graphicsView->update();

}

void MainWindow::on_action_5_triggered()
{

    QString filename = fileDialog.getSaveFileName(nullptr,tr("Сохранить файл"),fileDialog.directory().path(),"png (*.png)");
    lyapunovPixels->save(filename);
}
