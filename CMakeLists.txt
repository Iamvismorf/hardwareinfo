cmake_minimum_required(VERSION 3.31)
project(hardwareinfo) #${project_name}


set(CMAKE_EXPORT_COMPILE_COMMANDS on)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED on)
set(QT_QML_GENERATE_QMLLS_INI on)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 REQUIRED COMPONENTS Core Quick Qml Gui)
qt_standard_project_setup(REQUIRES 6.8)
qt_add_qml_module(hardwareinfo
   URI Vixhardware
   VERSION 1.0
   OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/Vixhardware"
   SOURCES
     ./include/Cpu.hpp
     ./src/Cpu.cpp

     ./include/Ram.hpp
     ./src/Ram.cpp
)
target_include_directories(hardwareinfo PRIVATE  ./include)

add_subdirectory(tests)
