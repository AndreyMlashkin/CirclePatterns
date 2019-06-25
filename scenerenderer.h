#ifndef SCENERENDERER_H
#define SCENERENDERER_H

#include <QOpenGLWidget>

namespace Ui {
class SceneRenderer;
}

class SceneRenderer : public QOpenGLWidget
{
    Q_OBJECT

public:
    explicit SceneRenderer(QWidget *parent = 0);
    ~SceneRenderer();

    void setSceneParams(qreal internalRadius);

    void getDefaults (qreal& internalRadius);
    void getMaxValues(qreal& internalRadius);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    qreal m_internalRadius;
};

#endif // SCENERENDERER_H
