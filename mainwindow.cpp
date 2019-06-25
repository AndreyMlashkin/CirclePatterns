#include <QDebug>
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->internalRadiusBox,    SIGNAL(valueChanged(double)), SLOT(setInternalRadius(qreal)));
    connect(ui->internalRadiusSlider, &QSlider::valueChanged,
            [=](int newValue)
    {
        qreal maximum = ui->internalRadiusBox->maximum();
        qreal newMappedValue = maximum / 100 * newValue;
        ui->internalRadiusBox->setValue(newMappedValue);
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setInternalRadius(qreal newValue)
{
    qDebug() << Q_FUNC_INFO << newValue;
    ui->m_scene->setSceneParams(newValue);

    ui->m_scene->repaint();
}
