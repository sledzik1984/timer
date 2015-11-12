################################################################################
QT += core gui svg widgets

QMAKE_CFLAGS += -std=c++14
QMAKE_CXXFLAGS += -std=c++14

################################################################################
TARGET = timer
TEMPLATE = app

################################################################################
HEADERS +=                  \
    src/error.hpp           \
    src/event.hpp           \
    src/eventreader.hpp     \
    src/eventwriter.hpp     \
    src/mainwindow.hpp      \
    src/section.hpp         \
    src/sectionreader.hpp   \
    src/sectionwriter.hpp   \
    src/svgwidget.hpp       \

################################################################################
SOURCES +=                  \
    src/event.cpp           \
    src/eventreader.cpp     \
    src/eventwriter.cpp     \
    src/main.cpp            \
    src/mainwindow.cpp      \
    src/section.cpp         \
    src/sectionreader.cpp   \
    src/sectionwriter.cpp   \
    src/svgwidget.cpp       \

################################################################################
FORMS +=                    \
    src/mainwindow.ui       \

################################################################################
RESOURCES +=                \
    res/resource.qrc        \
