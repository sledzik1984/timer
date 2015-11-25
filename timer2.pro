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
    src/event.hpp           \
    src/eventnamewidget.hpp \
    src/eventreader.hpp     \
    src/eventtimewidget.hpp \
    src/eventwriter.hpp     \
    src/mainwindow.hpp      \
    src/numberwidget.hpp    \
    src/periodwidget.hpp    \
    src/section.hpp         \
    src/sectionreader.hpp   \
    src/sectionwidget.hpp   \
    src/sectionwriter.hpp   \
    src/svgwidget.hpp       \
    src/timelinewidget.hpp  \
    src/timewidget.hpp      \
    src/trucktimewidget.hpp \

################################################################################
SOURCES +=                  \
    src/clock.cpp           \
    src/clockwidget.cpp     \
    src/colonwidget.cpp     \
    src/digitwidget.cpp     \
    src/event.cpp           \
    src/eventnamewidget.cpp \
    src/eventreader.cpp     \
    src/eventtimewidget.cpp \
    src/eventwriter.cpp     \
    src/main.cpp            \
    src/mainwindow.cpp      \
    src/numberwidget.cpp    \
    src/periodwidget.cpp    \
    src/section.cpp         \
    src/sectionreader.cpp   \
    src/sectionwidget.cpp   \
    src/sectionwriter.cpp   \
    src/svgwidget.cpp       \
    src/timelinewidget.cpp  \
    src/timewidget.cpp      \
    src/trucktimewidget.cpp \

################################################################################
FORMS +=                    \
    src/eventnamewidget.ui  \
    src/eventtimewidget.ui  \
    src/mainwindow.ui       \
    src/trucktimewidget.ui  \

################################################################################
RESOURCES +=                \
    res/resource.qrc        \
