################################################################################
QT += core gui svg widgets

QMAKE_CFLAGS += -std=c++14
QMAKE_CXXFLAGS += -std=c++14

################################################################################
TARGET = timer
TEMPLATE = app

################################################################################
HEADERS +=                  \
    src/editwindow.hpp      \
    src/event.hpp           \
    src/eventmodel.hpp      \
    src/eventreader.hpp     \
    src/eventwriter.hpp     \
    src/mainwindow.hpp      \
    src/section.hpp         \
    src/sectionreader.hpp   \
    src/sectionwriter.hpp   \
    src/timedelegate.hpp    \
    src/xmlerror.hpp        \

################################################################################
SOURCES +=                  \
    src/editwindow.cpp      \
    src/event.cpp           \
    src/eventmodel.cpp      \
    src/eventreader.cpp     \
    src/eventwriter.cpp     \
    src/main.cpp            \
    src/mainwindow.cpp      \
    src/section.cpp         \
    src/sectionreader.cpp   \
    src/sectionwriter.cpp   \
    src/timedelegate.cpp    \

################################################################################
FORMS +=                    \
    src/editwindow.ui       \
    src/mainwindow.ui       \

################################################################################
RESOURCES +=                \
    res/resource.qrc        \
