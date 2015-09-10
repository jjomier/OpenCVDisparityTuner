/*=========================================================================

  Program:   OpenCVDisparityTuner

  Copyright (c) Julien Jomier
  All rights reserved.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#include <QApplication>
#include <QException>
#include <QDebug>

#include "OpenCVDisparityTuner.h"

int main(int argc, char *argv[])
{
  int res=-1;

  try
    {
    QApplication a(argc, argv);
    OpenCVDisparityTuner w;
    w.show();
    res = a.exec();
    }
  catch(QException &e)
    {
    qCritical() << QString("Exception: %1").arg( e.what() );
    }
  catch(...)
    {
    qCritical() << QString("Unhandled Exception");
    }

  return res;
}
