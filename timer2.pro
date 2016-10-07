################################################################################
QT += core gui svg widgets

QMAKE_CFLAGS += -std=c++14
QMAKE_CXXFLAGS += -std=c++14

################################################################################
TARGET = timer
TEMPLATE = app

################################################################################
HEADERS +=                  \
    src/clock.hpp           \
    src/clockwidget.hpp     \
    src/colonwidget.hpp     \
    src/digitwidget.hpp     \
    src/error.hpp           \
    src/eventtimewidget.hpp \
    src/mainwindow.hpp      \
    src/numberwidget.hpp    \
    src/periodwidget.hpp    \
    src/presswidget.hpp     \
    src/stylewidget.hpp     \
    src/svgwidget.hpp       \
    src/timewidget.hpp      \
    src/trucktimewidget.hpp \

################################################################################
SOURCES +=                  \
    src/clock.cpp           \
    src/clockwidget.cpp     \
    src/colonwidget.cpp     \
    src/digitwidget.cpp     \
    src/eventtimewidget.cpp \
    src/main.cpp            \
    src/mainwindow.cpp      \
    src/numberwidget.cpp    \
    src/periodwidget.cpp    \
    src/presswidget.cpp     \
    src/stylewidget.cpp     \
    src/svgwidget.cpp       \
    src/timewidget.cpp      \
    src/trucktimewidget.cpp \

################################################################################
FORMS +=                    \
    src/eventtimewidget.ui  \
    src/mainwindow.ui       \
    src/trucktimewidget.ui  \

################################################################################
RESOURCES +=                \
    res/resource.qrc        \
