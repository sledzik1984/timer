################################################################################
QT += core gui svg widgets

QMAKE_CFLAGS += -std=c++14
QMAKE_CXXFLAGS += -std=c++14

LIBS += -loscpack

################################################################################
TARGET = timer
TEMPLATE = app

################################################################################
HEADERS +=                  \
    src/clock.hpp           \
    src/clockwidget.hpp     \
    src/colonwidget.hpp     \
    src/countdownwidget.hpp \
    src/digitwidget.hpp     \
    src/mainwindow.hpp      \
    src/numberwidget.hpp    \
    src/osc_event.hpp       \
    src/osc_listener.hpp    \
    src/osc_video.hpp       \
    src/periodwidget.hpp    \
    src/presswidget.hpp     \
    src/svgwidget.hpp       \
    src/timerwidget.hpp     \
    src/timewidget.hpp      \

################################################################################
SOURCES +=                  \
    src/clock.cpp           \
    src/clockwidget.cpp     \
    src/colonwidget.cpp     \
    src/countdownwidget.cpp \
    src/digitwidget.cpp     \
    src/main.cpp            \
    src/mainwindow.cpp      \
    src/numberwidget.cpp    \
    src/osc_event.cpp       \
    src/osc_listener.cpp    \
    src/osc_video.cpp       \
    src/periodwidget.cpp    \
    src/presswidget.cpp     \
    src/svgwidget.cpp       \
    src/timerwidget.cpp     \
    src/timewidget.cpp      \

################################################################################
FORMS +=                    \
    src/mainwindow.ui       \

################################################################################
RESOURCES +=                \
    res/resource.qrc        \
