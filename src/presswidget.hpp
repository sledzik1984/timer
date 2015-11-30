////////////////////////////////////////////////////////////////////////////////
#ifndef PRESSWIDGET_HPP
#define PRESSWIDGET_HPP

#include <QEvent>
#include <QObject>
#include <QTimer>

////////////////////////////////////////////////////////////////////////////////
class PressWidget
{
public:
    ////////////////////
    PressWidget(QObject* self);

    ////////////////////
    virtual void clicked()      = 0;
    virtual void pressed()      = 0;
    virtual void long_pressed() = 0;
    virtual void released()     = 0;
};

////////////////////////////////////////////////////////////////////////////////
class Monitor : public QObject
{
    Q_OBJECT

public:
    ////////////////////
    Monitor(QObject* parent, PressWidget* widget);
    virtual bool eventFilter(QObject*, QEvent*) override;

private:
    ////////////////////
    QTimer _long;
    PressWidget* _widget;
};

////////////////////////////////////////////////////////////////////////////////
#endif // PRESSWIDGET_HPP