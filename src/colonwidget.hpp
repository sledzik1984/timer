////////////////////////////////////////////////////////////////////////////////
#ifndef COLONWIDGET_HPP
#define COLONWIDGET_HPP

////////////////////////////////////////////////////////////////////////////////
#include "presswidget.hpp"
#include "svgwidget.hpp"

#include <QWidget>

////////////////////////////////////////////////////////////////////////////////
class ColonWidget : public SvgWidget, public PressWidget
{
    Q_OBJECT

public:
    ////////////////////
    explicit ColonWidget(QWidget* parent = nullptr) : ColonWidget(QColor(), parent) { }
    explicit ColonWidget(QColor color, QWidget* parent = nullptr);

    using SvgWidget::set_color; // make SvgWidget::set_color public

signals:
    ////////////////////
    void clicked() override;
    void pressed() override;
    void long_pressed() override;
    void released() override;

protected:
    ////////////////////
    void resizeEvent(QResizeEvent*) override;
};

////////////////////////////////////////////////////////////////////////////////
#endif // COLONWIDGET_HPP
