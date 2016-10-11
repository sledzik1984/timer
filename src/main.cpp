////////////////////////////////////////////////////////////////////////////////
#include "mainwindow.hpp"

#include <QApplication>
#include <QDesktopWidget>

#include <exception>
#include <iostream>

////////////////////////////////////////////////////////////////////////////////
int main(int argc, char* argv[])
try
{
    QApplication application(argc, argv);

    MainWindow window;
    window.show();

    auto options = application.arguments();
    options.removeAt(0); // application name

    for(const QString& option : options)
    {
        if(option == "--full")
        {
            window.setWindowState(window.windowState() | Qt::WindowFullScreen);
            window.setGeometry(QApplication::desktop()->screenGeometry(&window));
        }
        else if(option == "--blink")
        {
            window.set_threshold(QTime(0, 0, 30));
        }
    }

    return application.exec();
}
catch(std::exception& e)
{
    std::cerr << e.what() << std::endl;
}
catch(...)
{
    std::cerr << "Unknown error" << std::endl;
}
