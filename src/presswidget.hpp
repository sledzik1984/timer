////////////////////////////////////////////////////////////////////////////////
#ifndef PRESSWIDGET_HPP
#define PRESSWIDGET_HPP

#include <QEvent>
#include <QObject>
#include <QTimer>

////////////////////////////////////////////////////////////////////////////////
// NB: PressWidget does not derive from QObject to avoid
// multiple inheritance from it. Instead it takes a reference
// to self as QObject, which is provided by the derived classes
class PressWidget
{
public:
    ////////////////////
    explicit PressWidget(QObject* self);
    virtual ~PressWidget() { }

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

    bool eventFilter(QObject*, QEvent*) override;

private:
    ////////////////////
    QTimer _long;
    PressWidget* _widget;
};

////////////////////////////////////////////////////////////////////////////////
#endif // PRESSWIDGET_HPP
