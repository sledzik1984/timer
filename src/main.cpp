////////////////////////////////////////////////////////////////////////////////
#include "error.hpp"
#include "mainwindow.hpp"

#include <QApplication>

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
        }
        else throw InvalidError("Invalid option " + option);
    }

    return application.exec();
}
catch(Error& e)
{
    std::cerr << e.message().toLatin1().data() << std::endl;
}
catch(std::exception& e)
{
    std::cerr << e.what() << std::endl;
}
catch(...)
{
    std::cerr << "Unknown error" << std::endl;
}
