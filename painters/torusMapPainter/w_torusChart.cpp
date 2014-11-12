#include "w_torusChart.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QStringList>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    chartGraphics = new QGraphicsScene();
    chartPixels = new QPixmap();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::readChart(QFile &ifile, bool addData)
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

        std::vector<int> wNumbers;
        for (int i = 2; i < 5; i++)
        {
            QString & sNumber = valuesAsStrings[i];
            int val = sNumber.toInt(&isOk);
            if (isOk)
                wNumbers.push_back(val);
        }
        if (!addData)
            data[posX][posY].clear();
        data[posX][posY].push_back(wNumbers);
    }
    ifile.close();
}

void Saturate(QColor & r)
{
    qreal maxColorRatio = 0;
    int maxColorValue = 0;
    if (r.red() > maxColorValue && r.red()!=0)
    {
        maxColorValue = r.red();
        maxColorRatio = 1.0 / r.redF();
    }
    if (r.blue() > maxColorValue && r.blue()!=0)
    {
        maxColorValue = r.blue();
        maxColorRatio = 1.0 / r.blueF();
    }
    if (r.green() > maxColorValue && r.green()!=0)
    {
        maxColorValue = r.green();
        maxColorRatio = 1.0 /r.greenF();
    }
    try
    {
        if (maxColorValue != 255)
            r.setRgbF(maxColorRatio * r.redF(), maxColorRatio * r.greenF(), maxColorRatio*r.blueF());
        else
            r.setRgbF(maxColorRatio * r.redF(), maxColorRatio * r.greenF(), maxColorRatio*r.blueF());
    }
    catch (...) {
        r.setRgbF(1,1,1);
    }
}

QColor MainWindow::SelectColor(int mode, std::vector<int> wNumbers)
{
    QColor r;
    if (wNumbers.size() < 2)
    {
        r.setRgb(0,0,0);
        return r;
    }

    if (mode == 0)
    {
        r.setRgb(0xaa, 0xaa, 0xaa); // White
        return r;
    }
    else if (mode == 1)
    {
        if (wNumbers.size() == 2)
        {
            if (wNumbers[0] == 0 && wNumbers[1]==1)
                r.setRgb(0xff,0,0); //Red
            else if (wNumbers[0] == 1 && wNumbers[1]==1)
                r.setRgb(0, 0xff,0); //Green
            else if (wNumbers[0] == 1 && wNumbers[1]==0)
                r.setRgb(0,0, 0xff); //Blue
            else if (wNumbers[1] > wNumbers[0])
                r.setRgb(
                        0xff * (wNumbers[1]-wNumbers[0])/wNumbers[1],
                        0xff * wNumbers[0]/wNumbers[1],
                        0
                        ); // Farey Tree to select some yellow color
            else if (wNumbers[1] < wNumbers[0])
                r.setRgb(
                        0,
                        0xff * wNumbers[1]/wNumbers[0],
                        0xff * (wNumbers[0]-wNumbers[1])/wNumbers[0]
                        ); // Farey Tree to select some cyan color
        }
        else
        {
            int numbersSum = 0;
            for (int i = 0; i < wNumbers.size(); i++)
                numbersSum += abs(wNumbers[i]);

            std::vector<QColor> baseColors(wNumbers.size());
            for (int i = 0; i < baseColors.size(); i++)
            {
                QColor col;
                col.setHsvF(1.0/wNumbers.size()*i, 1.0, 1.0/numbersSum*abs(wNumbers[i]));
                baseColors[i] = col;
            }

            float redVal = 0, greenVal = 0, blueVal = 0, maxVal = 0;
            for (int i = 0; i < baseColors.size(); i++)
            {
                QColor & col = baseColors[i];
                redVal += col.redF()/numbersSum;
                greenVal += col.greenF()/numbersSum;
                blueVal += col.blueF()/numbersSum;
            }
            if (redVal < 0.0f || redVal > 1.0f)
                redVal = -redVal;
            if (greenVal < 0.0f || greenVal > 1.0f)
                greenVal = -greenVal;
            if (blueVal < 0.0f || blueVal > 1.0f)
                blueVal = -blueVal;

            r.setRgbF(redVal, greenVal, blueVal);
        }
    }
    else
    {
        r.setRgb(0x00,0x00,0x00); // Black
    }

    if (r.blue()==r.red() && r.red()==r.green() && r.green()==0)
        return r;

    Saturate(r);
    return r;
}

QColor MainWindow::SelectColorLyap(int mode, std::vector<int> wNumbers)
{
    QColor r;
    if (wNumbers.size() < 2)
    {
        r.setRgb(0,0,0);
        return r;
    }

    if (mode == 0)
        r.setRgb(0xff, 0, 0); // Red
    else if (mode == 1)
    {
        r.setRgb(0xff,0xff,0); //Yellow
    }
    else
        r.setRgb(0,0,0xff); // Blue

    return r;
}

QColor MainWindow::SelectColor(std::vector<std::vector<int> > &dataSet)
{
    QColor r;
    r.setRgb(0,0,0);
    if (dataSet.empty() || dataSet[0].empty())
    {

        return r;
    }
    std::map<int, std::vector<int> > modes;
    for (auto wNumbersSet : dataSet)
    {
        std::vector<int> wNumbers(std::next(wNumbersSet.begin()), wNumbersSet.end());
        for (auto & wn : wNumbers )
            wn = std::abs(wn);
        modes[wNumbersSet[0]] = wNumbers;
    }

    std::vector<QColor> baseColors;
    for (auto mode : modes)
    {
        baseColors.push_back(SelectColor(mode.first, mode.second));
    }

    for (auto color : baseColors)
    {
        r.setRed(r.red() + color.red()/baseColors.size());
        r.setBlue(r.blue() + color.blue()/baseColors.size());
        r.setGreen(r.green()+color.green()/baseColors.size());
    }
    return r;
}

QColor MainWindow::SelectColorLyap(std::vector<std::vector<int> > &dataSet)
{
    QColor r;
    r.setRgb(0,0,0);
    if (dataSet.empty() || dataSet[0].empty())
    {

        return r;
    }

    std::map<int, std::vector<int> > modes;
    for (auto wNumbersSet : dataSet)
    {
        std::vector<int> wNumbers(std::next(wNumbersSet.begin()), wNumbersSet.end());
        modes[wNumbersSet[0]] = wNumbers;
    }

    std::vector<QColor> baseColors;
    for (auto mode : modes)
    {
        baseColors.push_back(SelectColorLyap(mode.first, mode.second));
    }

    for (auto color : baseColors)
    {
        r.setRed(r.red() + color.red()/baseColors.size());
        r.setBlue(r.blue() + color.blue()/baseColors.size());
        r.setGreen(r.green()+color.green()/baseColors.size());
    }
    return r;
}

void MainWindow::on_action_triggered()
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

void MainWindow::on_action_2_triggered()
{
    QString filename = QFileDialog::getOpenFileName(0, "Открыть файл", "*.*");
    QFile ifile(filename);
    if (ifile.exists())
    {
        readChart(ifile, true);
    }
}

void MainWindow::on_action_3_triggered()
{
    if (data.size())
    {
        int w = data.size();
        int h = data.begin()->second.size();
        QImage * canvas = new QImage(w, h, QImage::Format_RGB32);
        int px = 0;
        for (auto posX : data)
        {
            int py = 0;
            for (auto posY : posX.second)
            {
                QColor pixColor;
                if (!ui->checkBox->isChecked())
                    pixColor = SelectColor(posY.second);
                else
                    pixColor = SelectColorLyap(posY.second);
                QRgb rgbCode = pixColor.rgb();
                canvas->setPixel(px, h-1-py, rgbCode);
                py++;
            }
            px++;
        }
        *chartPixels = chartPixels->fromImage(*canvas);
        chartGraphics->clear();
        chartGraphics->addPixmap(*chartPixels);
        ui->graphicsView->setScene(chartGraphics);

        QRect graphicsViewPos = ui->graphicsView->geometry();
        ui->graphicsView->setGeometry(graphicsViewPos.x(), graphicsViewPos.y(),
                                      w+1,h+1);
        delete canvas;
    }

}

void MainWindow::on_action_4_triggered()
{
    QString filename = QFileDialog::getSaveFileName(0, "Сохранить файл", "*.png");
    if (filename == "")
        return;
    QImage * image = new QImage(ui->graphicsView->width(), ui->graphicsView->height(), QImage::Format_RGB32);
    QPainter * painter = new QPainter(image);
    ui->graphicsView->render(painter);
    image->save(filename);
    delete painter;
    delete image;
}
