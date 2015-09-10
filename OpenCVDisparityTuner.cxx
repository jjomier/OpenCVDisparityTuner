/*=========================================================================

  Program:   OpenCVDisparityTuner

  Copyright (c) Julien Jomier
  All rights reserved.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
// Application includes
#include "OpenCVDisparityTuner.h"
#include "ui_OpenCVDisparityTuner.h"

// Qt includes
#include <QFileDialog>
#include <QProgressBar>

// Windows include
#include <iostream>
#include <ctime>

#include "opencv2/core/core.hpp"
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/calib3d/calib3d.hpp"
#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

using namespace cv;

OpenCVDisparityTuner::OpenCVDisparityTuner(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::OpenCVDisparityTuner)
{
  ui->setupUi(this);
   
  QObject::connect(this->ui->loadLeftImageButton, SIGNAL(clicked()), this, SLOT(onLoadLeftImageButton()));
  QObject::connect(this->ui->loadRightImageButton, SIGNAL(clicked()), this, SLOT(onLoadRightImageButton()));
  QObject::connect(this->ui->numberOfDisparities, SIGNAL(valueChanged(int)), this, SLOT(onProcessButton()));
  QObject::connect(this->ui->SADWindowSize, SIGNAL(valueChanged(int)), this, SLOT(onProcessButton()));
  QObject::connect(this->ui->preFilterCap, SIGNAL(valueChanged(int)), this, SLOT(onProcessButton()));
  QObject::connect(this->ui->minDisparity, SIGNAL(valueChanged(int)), this, SLOT(onProcessButton()));
  QObject::connect(this->ui->uniquenessRatio, SIGNAL(valueChanged(int)), this, SLOT(onProcessButton()));
  QObject::connect(this->ui->disp12MaxDiff, SIGNAL(valueChanged(int)), this, SLOT(onProcessButton()));
  QObject::connect(this->ui->fullDP, SIGNAL(stateChanged(int)), this, SLOT(onProcessButton()));
  QObject::connect(this->ui->speckleWindowSize, SIGNAL(valueChanged(int)), this, SLOT(onProcessButton()));
  QObject::connect(this->ui->speckleRange, SIGNAL(valueChanged(int)), this, SLOT(onProcessButton()));
  QObject::connect(this->ui->p1, SIGNAL(valueChanged(int)), this, SLOT(onProcessButton()));
  QObject::connect(this->ui->p2, SIGNAL(valueChanged(int)), this, SLOT(onProcessButton()));

  QObject::connect(this->ui->processButton, SIGNAL(clicked()), this, SLOT(onProcessButton()));
}

OpenCVDisparityTuner::~OpenCVDisparityTuner()
{
  delete ui;
}

/** On LoadLeftImageButton */
void OpenCVDisparityTuner::onLoadLeftImageButton()
{
  QString filter = "Images (*.jpg *.JPG *.jpeg *.png *.PNG)";

  QString filename = QFileDialog::getOpenFileName(this, "Select an image...", QDir::currentPath(), filter);
  this->LeftImage = cv::imread(filename.toStdString().c_str(), 1);
  cv::Mat imageFlipped;
  cv::flip( this->LeftImage,imageFlipped, 0);
  ui->imageViewerLeft->showImage( imageFlipped );
  ui->imageViewerDisparity->showImage(cv::Mat::zeros(0,0,0));
}

/** On LoadRightImageButton */
void OpenCVDisparityTuner::onLoadRightImageButton()
{
  QString filter = "Images (*.jpg *.JPG *.jpeg *.png *.PNG)";

  QString filename = QFileDialog::getOpenFileName(this, "Select an image...", QDir::currentPath(), filter);
  this->RightImage = cv::imread(filename.toStdString().c_str(), 1);
  cv::Mat imageFlipped;
  cv::flip( this->RightImage,imageFlipped, 0);
  ui->imageViewerRight->showImage( imageFlipped );
  ui->imageViewerDisparity->showImage(cv::Mat::zeros(0,0,0));
}

/** On ProcessButton */
void OpenCVDisparityTuner::onProcessButton()
{
  cv::StereoSGBM sgbm;
  cv::Size img_size = this->LeftImage.size();

  sgbm.SADWindowSize = this->ui->SADWindowSize->value();
  sgbm.numberOfDisparities = this->ui->numberOfDisparities->value()*16;
  sgbm.preFilterCap = this->ui->preFilterCap->value();;
  sgbm.minDisparity = this->ui->minDisparity->value()*16;
  sgbm.uniquenessRatio = this->ui->uniquenessRatio->value();
  sgbm.speckleWindowSize = this->ui->speckleWindowSize->value();
  sgbm.speckleRange = this->ui->speckleRange->value();
  sgbm.disp12MaxDiff = this->ui->disp12MaxDiff->value();
  sgbm.fullDP = this->ui->fullDP->isChecked();
  sgbm.P1 = this->ui->p1->value();
  sgbm.P2 = this->ui->p2->value();

  cv::Mat disp, disp8;
  sgbm(this->LeftImage, this->RightImage, disp);

  // Check its extreme values
  double minVal; double maxVal;
  minMaxLoc( disp, &minVal, &maxVal );
  printf("Min disp: %f Max value: %f \n", minVal, maxVal);
 
  // Convert to 8
  disp.convertTo( disp8, CV_8UC1, 255/(maxVal - minVal));
  
  cv::Mat imageFlipped;
  cv::flip( disp8,imageFlipped, 0);
  ui->imageViewerDisparity->showImage( imageFlipped );

  // Construct the 3D points
  cv::Mat imgDisparity32F;
  disp.convertTo( imgDisparity32F, CV_32F, 1./16);

  std::cout << "Done!" << std::endl;

}