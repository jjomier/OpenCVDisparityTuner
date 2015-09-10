cmake_minimum_required(VERSION 2.8)
project(OpenCVDisparityTuner)

set(OpenCVDisparityTuner_VERSION_MAJOR 1)
set(OpenCVDisparityTuner_VERSION_MINOR 0)
set(OpenCVDisparityTuner_VERSION_PATCH 0)

# Instruct CMake to run moc automatically when needed.
set( CMAKE_AUTOMOC ON )

# OpenCV library
find_package( OpenCV REQUIRED)
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
	
qt5_wrap_ui(OpenCVDisparityTuner_UI OpenCVDisparityTuner.ui)

add_executable( OpenCVDisparityTuner ${OpenCVDisparityTuner_SRCS} ${OpenCVDisparityTuner_UI} )
target_link_libraries(OpenCVDisparityTuner ${OpenCV_LIBS} Qt5::Widgets opengl32.lib)

# Installation
include( CMake/DeployQt5.cmake )
install_qt5_lib( bin ${QT5_COMPONENTS} )
install_qt5_icu( bin )
install_qt5_platform( bin )
install_qt5_dbdrivers( bin )
install (TARGETS OpenCVDisparityTuner DESTINATION bin)

# build a CPack driven installer package
include (InstallRequiredSystemLibraries)
set (CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE")
set (CPACK_PACKAGE_VERSION_MAJOR "${OpenCVDisparityTuner_VERSION_MAJOR}")
set (CPACK_PACKAGE_VERSION_MINOR "${OpenCVDisparityTuner_VERSION_MINOR}")
set (CPACK_PACKAGE_VERSION_PATCH "${OpenCVDisparityTuner_VERSION_PATCH}")
set (CPACK_PACKAGE_CONTACT       "julien.jomier at kitware.com")
set (CPACK_PACKAGE_VENDOR        "Julien Jomier")

if(WIN32 AND NOT UNIX)
  #set(CPACK_NSIS_MUI_ICON "${CMAKE_CURRENT_SOURCE_DIR}\\\\OpenCVDisparityTuner.ico")
  #set(CPACK_NSIS_MUI_UNIICON "${CMAKE_CURRENT_SOURCE_DIR}\\\\OpenCVDisparityTuner.ico")
  # set the package header icon for MUI
  #set(CPACK_PACKAGE_ICON "${CMAKE_CURRENT_SOURCE_DIR}\\\\OpenCVDisparityTuner.ico")
  #set(CPACK_NSIS_INSTALLED_ICON_NAME "bin\\\\OpenCVDisparityTuner.exe")
  set(CPACK_NSIS_DISPLAY_NAME "OpenCVDisparityTuner ${CPACK_PACKAGE_VERSION_MAJOR}.${CPACK_PACKAGE_VERSION_MINOR}.${CPACK_PACKAGE_VERSION_PATCH}")
  set(CPACK_NSIS_HELP_LINK "http:\\\\\\\\julien.jomier.com")
  set(CPACK_NSIS_URL_INFO_ABOUT "http:\\\\\\\\www.jomier.com")
  set(CPACK_NSIS_CONTACT "julien.jomier at kitware.com")
  # set(CPACK_NSIS_MODIFY_PATH ON)
  set (CPACK_NSIS_MENU_LINKS 	"bin\\\\OpenCVDisparityTuner.exe" "OpenCVDisparityTuner" )  
else()
  set(CPACK_STRIP_FILES "bin/OpenCVDisparityTuner")
  set(CPACK_SOURCE_STRIP_FILES "")
endif()

include (CPack)


