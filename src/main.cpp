////////////////////////////////////////////////////////////////////////////////
#include "error.hpp"
#include "mainwindow.hpp"

#include <QApplication>
#include <QColor>
#include <QPalette>

#include <exception>
#include <iostream>

////////////////////////////////////////////////////////////////////////////////
void set_dark_palette(QApplication& application)
{
    QPalette palette;

    palette.setColor(QPalette::Window, QColor(53,53,53));
    palette.setColor(QPalette::WindowText, Qt::white);
    palette.setColor(QPalette::Base, QColor(25,25,25));
    palette.setColor(QPalette::AlternateBase, QColor(53,53,53));
    palette.setColor(QPalette::ToolTipBase, Qt::white);
    palette.setColor(QPalette::ToolTipText, Qt::white);
    palette.setColor(QPalette::Text, Qt::white);
    palette.setColor(QPalette::Button, QColor(53,53,53));
    palette.setColor(QPalette::ButtonText, Qt::white);
    palette.setColor(QPalette::BrightText, Qt::red);
    palette.setColor(QPalette::Link, QColor(42, 130, 218));
    palette.setColor(QPalette::Highlight, QColor(42, 130, 218));
    palette.setColor(QPalette::HighlightedText, Qt::black);

    application.setPalette(palette);
    application.setStyleSheet("QToolTip { color: #ffffff; background-color: #2a82da; border: 1px solid white; }");
}

////////////////////////////////////////////////////////////////////////////////
int main(int argc, char* argv[])
try
{
    QApplication application(argc, argv);

    auto options = application.arguments();
    options.removeAt(0); // application name

    for(const QString& option : options)
    {
        if(option == "--dark")
        {
            set_dark_palette(application);
        }
        else throw InvalidError("Invalid option " + option);
    }

    MainWindow window;
    window.show();

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
