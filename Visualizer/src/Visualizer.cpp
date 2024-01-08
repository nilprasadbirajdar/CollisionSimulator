#include "stdafx.h"
#include "Visualizer.h"
#include "OpenGLWindow.h"
#include "Orbit.h"
#include "QTimer"
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>

using namespace std;

Visualizer::Visualizer(QWindow* parent) : QMainWindow(nullptr)
{
    setupUi();
    connect(mpushButtonStart, &QPushButton::clicked, this, &Visualizer::startBtn);
    connect(mpushButtonStop, &QPushButton::clicked, this, &Visualizer::stopBtn);
    connect(mpushButtonReset, &QPushButton::clicked, this, &Visualizer::resetBtn);
}

Visualizer::~Visualizer()
{

}

void Visualizer::setupUi() {
    resize(1200, 900);

    mpushButtonStart = new QPushButton(this);
    mpushButtonStart->setText("Start");
    mpushButtonStart->setGeometry(QRect(750, 400, 100, 25));

    mpushButtonStop = new QPushButton(this);
    mpushButtonStop->setText("Stop");
    mpushButtonStop->setGeometry(QRect(750, 450, 100, 25));

    mpushButtonReset = new QPushButton(this);
    mpushButtonReset->setText("Reset");
    mpushButtonReset->setGeometry(QRect(750, 500, 100, 25));

    mRenderer = new OpenGLWindow(QColor(0, 0, 0), this);
    mRenderer->setGeometry(QRect(30,200, 700, 600));
    setWindowTitle(QCoreApplication::translate("Collision Viewer", "Collision Viewer", nullptr));
}

void Visualizer::readSTL()
{
    std::string filePath = "D:/sphere3.stl";

    std::ifstream dataFile;
    dataFile.open(filePath);
    if (!dataFile.is_open())
    {
        std::cout << "File not exist" << std::endl;
        return;
    }

    std::string line;
    //int c = 100;
    while (std::getline(dataFile, line))
    {
      
        if (line.find("vertex") != std::string::npos)
        {
            std::istringstream iss(line);
            std::string token;
            double x, y, z;
            iss >> token >> x >> y >> z;
            mVertices.push_back(x * 0.1);
            mVertices.push_back(y * 0.1);
            mVertices.push_back(z * 0.1);

            mColors.push_back(1.0f);
            mColors.push_back(0.0f);
            mColors.push_back(0.0f);
           
        }
    }
    
    mRenderer->updateData(mVertices, mColors);
    /*mVertices.clear();
    mColors.clear();
    dataFile.close();*/
    update();
}


void Visualizer::startBtn()

{
    mRenderer->startRendering(mVelocity);
}

void Visualizer::stopBtn()

{

    mRenderer->stopRevolving();

}

void Visualizer::resetBtn()

{

    mRenderer->resetPositions();

}