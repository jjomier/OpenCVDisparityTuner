cmake_minimum_required(VERSION 2.8)
project(OpenCVDisparityTuner)

# Instruct CMake to run moc automatically when needed.
set( CMAKE_AUTOMOC ON )

# OPENCV LIBRARY
FIND_PACKAGE( OpenCV REQUIRED)
include_directories( ${OpenCV_INCLUDE_DIRS} )

# Find the QtWidgets library
set( QT5_COMPONENTS Core Widgets Xml Gui Sql)
find_package( Qt5 COMPONENTS ${QT5_COMPONENTS})

include_directories(${CMAKE_BINARY_DIR})

set( OpenCVDisparityTuner_SRCS 
     main.cxx
	 OpenCVDisparityTuner.cxx
	 cqtopencvviewergl.cxx
    )
	
QT5_WRAP_UI(OpenCVDisparityTuner_UI OpenCVDisparityTuner.ui)

add_executable( OpenCVDisparityTuner ${OpenCVDisparityTuner_SRCS} ${OpenCVDisparityTuner_UI} )
target_link_libraries(OpenCVDisparityTuner ${OpenCV_LIBS} Qt5::Widgets opengl32.lib)
