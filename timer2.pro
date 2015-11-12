################################################################################
QT += core gui svg widgets

QMAKE_CFLAGS += -std=c++14
QMAKE_CXXFLAGS += -std=c++14

################################################################################
TARGET = timer
TEMPLATE = app

################################################################################
HEADERS +=                  \
    src/block.hpp           \
    src/clockwidget.hpp     \
    src/digitwidget.hpp     \
    src/error.hpp           \
    src/event.hpp           \
    src/eventreader.hpp     \
    src/eventwriter.hpp     \
    src/mainwindow.hpp      \
    src/numberwidget.hpp    \
    src/section.hpp         \
    src/sectionreader.hpp   \
    src/sectionwriter.hpp   \
    src/svgwidget.hpp       \
    src/timewidget.hpp      \

################################################################################
SOURCES +=                  \
    src/clockwidget.cpp     \
    src/digitwidget.cpp     \
    src/event.cpp           \
    src/eventreader.cpp     \
    src/eventwriter.cpp     \
    src/main.cpp            \
    src/mainwindow.cpp      \
    src/numberwidget.cpp    \
    src/section.cpp         \
    src/sectionreader.cpp   \
    src/sectionwriter.cpp   \
    src/svgwidget.cpp       \
    src/timewidget.cpp      \

################################################################################
FORMS +=                    \
    src/mainwindow.ui       \

################################################################################
RESOURCES +=                \
    res/resource.qrc        \
