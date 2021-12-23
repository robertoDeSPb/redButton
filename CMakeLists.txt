cmake_minimum_required(VERSION 3.14)

project(Sound_Button LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(SKIP_AUTOMOC)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Core REQUIRED)
find_package(Qt5 COMPONENTS Core Gui Widgets Multimedia MultimediaWidgets REQUIRED)

add_executable(Sound_Button
  main.cpp
)
target_link_libraries(Sound_Button Qt5::Core Qt5::Gui Qt5::Widgets Qt5::Multimedia Qt5::MultimediaWidgets)
