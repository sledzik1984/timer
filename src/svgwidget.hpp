////////////////////////////////////////////////////////////////////////////////
#ifndef SVGWIDGET_HPP
#define SVGWIDGET_HPP

////////////////////////////////////////////////////////////////////////////////
#include <QByteArray>
#include <QColor>
#include <QRect>
#include <QtSvg/QSvgWidget>
#include <QWidget>

////////////////////////////////////////////////////////////////////////////////
class SvgWidget : public QSvgWidget
{
    Q_OBJECT

public:
    ////////////////////
    explicit SvgWidget(QRect viewbox = QRect(), QColor color = QColor(), QByteArray contents = QByteArray(), QWidget* parent = nullptr);

signals:
    ////////////////////
    void  viewbox_changed(const QRect&);
    void    color_changed(const QColor&);
    void contents_changed(const QByteArray&);

protected:
    ////////////////////
    void set_viewbox(QRect viewbox);
    const QRect& viewbox() const noexcept { return _viewbox; }

    void set_color(QColor color);
    const QColor& color() const noexcept { return _color; }

    void set_contents(QByteArray contents);
    const QByteArray& contents() const noexcept { return _contents; }

    void reload();

    ////////////////////
    QRect _viewbox;
    QColor _color;
    QByteArray _contents;

    using QSvgWidget::load; // protect QSvgWidget::load
};

////////////////////////////////////////////////////////////////////////////////
#endif // SVGWIDGET_HPP
