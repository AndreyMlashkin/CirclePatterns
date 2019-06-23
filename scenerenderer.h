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
};

#endif // SCENERENDERER_H
