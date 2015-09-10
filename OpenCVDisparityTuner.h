/*=========================================================================

  Program:   OpenCVDisparityTuner

  Copyright (c) Julien Jomier
  All rights reserved.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#ifndef OpenCVDisparityTuner_H
#define OpenCVDisparityTuner_H

class vtkRenderer;
class vtkActor;
class vtkPolyDataMapper;

#include <QMainWindow>

#include <opencv2/highgui/highgui.hpp>

namespace Ui {
    class OpenCVDisparityTuner;
}

class OpenCVDisparityTuner : public QMainWindow
{
  Q_OBJECT

public:
  OpenCVDisparityTuner(QWidget *parent = 0);
  ~OpenCVDisparityTuner();

private slots: 
  void onLoadLeftImageButton();
  void onLoadRightImageButton();
  void onProcessButton();

private:
  Ui::OpenCVDisparityTuner *ui;

private:
  cv::Mat LeftImage;
  cv::Mat RightImage;
  cv::Mat Disparity;
};

#endif
