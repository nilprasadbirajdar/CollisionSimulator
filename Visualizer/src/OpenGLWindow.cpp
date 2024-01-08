#include "stdafx.h"
#include "OpenGLWindow.h"
#include "CollisionSimulator.h"                                                                       
#include <QOpenGLContext>
#include <QOpenGLPaintDevice>
#include <QOpenGLShaderProgram>
#include <QTimer>
#include <QPainter>
#include <tuple>

OpenGLWindow::OpenGLWindow(const QColor& background, QMainWindow* parent) :
    mBackground(background) 
{
    setParent(parent);
    setMinimumSize(300, 250);
    timer = new QTimer(this);
    collision = new CollisionSimulator();
}

OpenGLWindow::~OpenGLWindow() {
    reset();
}

void OpenGLWindow::reset() {
    makeCurrent();
    delete mProgram;
    mProgram = nullptr;
    delete mVshader;
    mVshader = nullptr;
    delete mFshader;
    mFshader = nullptr;
    mVbo.destroy();
    doneCurrent();

    QObject::disconnect(mContextWatchConnection);
}

void OpenGLWindow::startRendering(float& speed)
{
    connect(timer, &QTimer::timeout, this, &OpenGLWindow::updateSolarSystemData);
    timer->start(16);
}

void OpenGLWindow::stopRendering()
{
    timer->stop();
}

void OpenGLWindow::updateSolarSystemData()
{
    mVertices.clear();
    mColors.clear();
    collision->drawCollisionSystem(mVertices, mColors);
    update();
}

void OpenGLWindow::stopRevolving()
{
    timer->stop();
}

void OpenGLWindow::resetPositions()
{
    collision->resetPositions();
    updateSolarSystemData();
}

void OpenGLWindow::paintGL() {
    glClear(GL_COLOR_BUFFER_BIT);

    mProgram->bind();

    QMatrix4x4 matrix;
    matrix.rotate(rotationAngle);
    matrix.ortho(-30.0f, 30.0f, -30.0f, 30.0f, -0.1f, 100.0f);
    matrix.translate(0,0,-50);

    mProgram->setUniformValue(m_matrixUniform, matrix);

    GLfloat* verticesData = mVertices.data();
    GLfloat* colorsData = mColors.data();

    glVertexAttribPointer(m_posAttr,3, GL_FLOAT, GL_FALSE, 0, verticesData);
    glVertexAttribPointer(m_colAttr, 3, GL_FLOAT, GL_FALSE, 0, colorsData);

    glEnableVertexAttribArray(m_posAttr);
    glEnableVertexAttribArray(m_colAttr);
    
    glDrawArrays(GL_LINES, 0, mVertices.size()/3);

}

void OpenGLWindow::mouseMoveEvent(QMouseEvent* event) {
    int dx = event->x() - lastPos.x();
    int dy = event->y() - lastPos.y();

    if (event->buttons() & Qt::LeftButton) {
        QQuaternion rotX = QQuaternion::fromAxisAndAngle(0.0f, 1.0f, 0.0f, 0.5f * dx);
        QQuaternion rotY = QQuaternion::fromAxisAndAngle(1.0f, 0.0f, 0.0f, 0.5f * dy);

        rotationAngle = rotX * rotY * rotationAngle;
        update();
    }
    lastPos = event->pos();
}

void OpenGLWindow::updateData(std::vector<float>& vertices,std::vector<float>& colors)
{
    mVertices = vertices;
    mColors = colors;
    update();
}

void OpenGLWindow::initializeGL() {
    static const char* vertexShaderSource =
        "attribute highp vec4 posAttr;\n"
        "attribute lowp vec4 colAttr;\n"
        "varying lowp vec4 col;\n"
        "uniform highp mat4 matrix;\n"
        "void main() {\n"
        "   col = colAttr;\n"
        "   gl_Position = matrix * posAttr;\n"
        "}\n";

    static const char* fragmentShaderSource =
        "varying lowp vec4 col;\n"
        "void main() {\n"
        "   gl_FragColor = col;\n"
        "}\n";

    initializeOpenGLFunctions();
    setMouseTracking(true);

    mProgram = new QOpenGLShaderProgram(this);
    mProgram->addShaderFromSourceCode(QOpenGLShader::Vertex, vertexShaderSource);
    mProgram->addShaderFromSourceCode(QOpenGLShader::Fragment, fragmentShaderSource);
    mProgram->link();
    m_posAttr = mProgram->attributeLocation("posAttr");
    Q_ASSERT(m_posAttr != -1);
    m_colAttr = mProgram->attributeLocation("colAttr");
    Q_ASSERT(m_colAttr != -1);
    m_matrixUniform = mProgram->uniformLocation("matrix");
    Q_ASSERT(m_matrixUniform != -1);
}

//void OpenGLWindow::drawOrbit() {
//    glColor3f(1.0, 1.0, 1.0); // White color for the orbit
//    glBegin(GL_LINE_LOOP);
//    for (int i = 0; i < 360; ++i) {
//        double radians = qDegreesToRadians(static_cast<double>(i));
//        double x = orbitRadius * std::cos(radians);
//        double y = orbitRadius * std::sin(radians);
//        glVertex3f(x, y, 0.0);
//    }
//    glEnd();
//}