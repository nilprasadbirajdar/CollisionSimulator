#pragma once

#include <QtWidgets/QMainWindow>
#include "CollisionSimulator.h"
#include "OpenGLWindow.h"
#include <Qvector>
#include<vector>
#include"Orbit.h"

class OpenGLWindow;

class Visualizer : public QMainWindow {
    Q_OBJECT

public:
    Visualizer(QWindow* parent = nullptr);
    ~Visualizer();

private:
    void setupUi();

public:
    void readSTL();
    //void drawBoundingBox();
    void startBtn();
    void stopBtn();
    void resetBtn();

private:
    QWidget* mCentralWidget;
    OpenGLWindow* mRenderer;

    QPushButton* mpushButton;

    QPushButton* mpushButtonRead;
    QPushButton* mpushButtonBBox;
    QPushButton* mpushButtonStart;
    QPushButton* mpushButtonStop;
    QPushButton* mpushButtonReset;
    QPushButton* mspeedButton;
    QPushButton* maltitudeButton;
    QPushButton* msizeButton;

    QDoubleSpinBox* mspeedInput;
    QDoubleSpinBox* maltitudeInput;
    QDoubleSpinBox* msizeInput;

    std::vector<float> mVertices;
    std::vector<float> mColors;

    std::vector<float>mTempVertices;
    std::vector<float>mTempColors;

    float mVelocity;
    float mAltitude;
    float mSize;

    Orbit orbit;
};
