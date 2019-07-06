#include <QDebug>
#include <QPainter>
#include <QPaintEvent>
#include <QtMath>

#include "scenerenderer.h"

static const int POINTS_ON_CIRCLE    = 30;
//static const int OUTER_CIRCLE_RADIUS = 4;


SceneRenderer::SceneRenderer(QWidget *parent) :
    QOpenGLWidget(parent)
{   
    getDefaults(m_internalRadius, m_externalRadius);
}

SceneRenderer::~SceneRenderer()
{
}

void SceneRenderer::setSceneParams(qreal internalRadius, qreal externalRadius)
{
    m_internalRadius = internalRadius;
    m_externalRadius = externalRadius;
}

void SceneRenderer::setInternalRadius(qreal internalRadius)
{
    m_internalRadius = internalRadius;
}

void SceneRenderer::setExternalRadius(qreal externalRadius)
{
    m_externalRadius = externalRadius;
}

void SceneRenderer::getDefaults(qreal &internalRadius, qreal &externalRadius)
{
    QRect scene = geometry(); //event->rect();

    int minSide = qMin(scene.width(), scene.height());
    internalRadius = minSide / 2;

    externalRadius = internalRadius - 10;
}

void SceneRenderer::getMaxValues(qreal &internalRadius)
{
    QRect scene = geometry(); //event->rect();

    int minSide = qMin(scene.width(), scene.height());
    internalRadius = minSide;
}

void SceneRenderer::paintEvent(QPaintEvent *event)
{
    qDebug() << Q_FUNC_INFO;
    QPainter painter;
    painter.begin(this);
    painter.save();

    painter.fillRect(event->rect(), QColor(Qt::white));
    painter.setRenderHint(QPainter::Antialiasing);

    QRect scene = geometry(); //event->rect();

    int radius = m_internalRadius;
    int centerX = scene.width() / 2;
    int centerY = scene.height() / 2;

    QPen oldPen = painter.pen();
    oldPen.setColor(Qt::red);
    oldPen.setCapStyle(Qt::RoundCap);
    oldPen.setWidth(1);
    painter.setRenderHint(QPainter::Antialiasing,true);
    painter.setPen(oldPen);

//    QPoint btmRight = geometry().bottomRight();
//    painter.drawPoint(btmRight);

    painter.drawEllipse(QPointF(centerX, centerY), radius, radius);

    QPoint rightPoint(centerX, centerY);
    qreal sectorAngle = 360.0f / POINTS_ON_CIRCLE;
    for(int i = 0; i < POINTS_ON_CIRCLE; ++i)
    {
        qreal angle = sectorAngle * i;
        qreal radians = qDegreesToRadians(angle);
        qreal x = rightPoint.x() + radius * qCos(radians);
        qreal y = rightPoint.y() + radius * qSin(radians);

        qDebug() << QString("iteration=%1, Point(%2,%3)")
                    .arg(i)
                    .arg(x)
                    .arg(y);

        painter.drawEllipse(QPointF(x, y), m_externalRadius, m_externalRadius);
    }

//    painter.drawPoint(0, 0);

    painter.drawRect(geometry());

    QPen anotherPen = painter.pen();
    anotherPen.setColor(Qt::green);
    anotherPen.setCapStyle(Qt::RoundCap);
    anotherPen.setWidth(10);
    painter.setRenderHint(QPainter::Antialiasing,true);
    painter.setPen(anotherPen);

    painter.drawPoint(centerX, centerY);
    painter.drawRect(event->rect());
    //helper->paint(&painter, event, elapsed);
    painter.restore();
    painter.end();
}
