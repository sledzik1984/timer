////////////////////////////////////////////////////////////////////////////////
#include "mainwindow.hpp"

#include <QApplication>
#include <QColor>
#include <QPalette>

////////////////////////////////////////////////////////////////////////////////
int main(int argc, char* argv[])
{
    QApplication a(argc, argv);

    for(const auto& arg : a.arguments())
    {
        if(arg == "--dark")
        {
            QPalette p;
            p.setColor(QPalette::Window, QColor(53,53,53));
            p.setColor(QPalette::WindowText, Qt::white);
            p.setColor(QPalette::Base, QColor(25,25,25));
            p.setColor(QPalette::AlternateBase, QColor(53,53,53));
            p.setColor(QPalette::ToolTipBase, Qt::white);
            p.setColor(QPalette::ToolTipText, Qt::white);
            p.setColor(QPalette::Text, Qt::white);
            p.setColor(QPalette::Button, QColor(53,53,53));
            p.setColor(QPalette::ButtonText, Qt::white);
            p.setColor(QPalette::BrightText, Qt::red);
            p.setColor(QPalette::Link, QColor(42, 130, 218));
            p.setColor(QPalette::Highlight, QColor(42, 130, 218));
            p.setColor(QPalette::HighlightedText, Qt::black);
            a.setPalette(p);
            a.setStyleSheet("QToolTip { color: #ffffff; background-color: #2a82da; border: 1px solid white; }");
        }
    }

    MainWindow w;
    w.show();

    return a.exec();
}
