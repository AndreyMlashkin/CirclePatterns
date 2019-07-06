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
        setInternalRadius(newMappedValue);
    });

    connect(ui->externalRadiusBox,    SIGNAL(valueChanged(double)), SLOT(setInternalRadius(qreal)));
    connect(ui->externalRadiusSlider, &QSlider::valueChanged,
            [=](int newValue)
    {
        qreal maximum = ui->externalRadiusBox->maximum();
        qreal newMappedValue = maximum / 100 * newValue;
        setExternalRadius(newMappedValue);
        //ui->externalRadiusBox->setValue(newMappedValue);
    });

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setInternalRadius(qreal newValue)
{
    qDebug() << Q_FUNC_INFO << newValue;
    ui->m_scene->setInternalRadius(newValue);

    ui->m_scene->repaint();
}

void MainWindow::setExternalRadius(qreal newValue)
{
    qDebug() << Q_FUNC_INFO << newValue;
    ui->m_scene->setExternalRadius(newValue);

    ui->m_scene->repaint();
}
