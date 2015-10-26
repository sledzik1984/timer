################################################################################
QT += core gui svg widgets
CONFIG += c++11

################################################################################
TARGET = timer
TEMPLATE = app

################################################################################
HEADERS +=                  \
    src/editwindow.hpp      \
    src/event.hpp           \
    src/eventmodel.hpp      \
    src/mainwindow.hpp      \
    src/section.hpp         \
    src/timedelegate.hpp    \

################################################################################
SOURCES +=                  \
    src/editwindow.cpp      \
    src/event.cpp           \
    src/eventmodel.cpp      \
    src/main.cpp            \
    src/mainwindow.cpp      \
    src/section.cpp         \
    src/timedelegate.cpp    \

################################################################################
FORMS +=                    \
    src/editwindow.ui       \
    src/mainwindow.ui       \

################################################################################
RESOURCES +=                \
    res/resource.qrc        \
