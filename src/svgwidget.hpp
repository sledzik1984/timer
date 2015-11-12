////////////////////////////////////////////////////////////////////////////////
#ifndef SVGWIDGET_HPP
#define SVGWIDGET_HPP

////////////////////////////////////////////////////////////////////////////////
#include <QMouseEvent>
#include <QString>
#include <QTimer>
#include <QtSvg/QSvgWidget>
#include <QWidget>

////////////////////////////////////////////////////////////////////////////////
class SvgWidget : public QSvgWidget
{
    Q_OBJECT

public:
    explicit SvgWidget(QWidget* parent = nullptr);

    virtual int heightForWidth(int width) const override;

signals:
    ////////////////////
    void clicked();
    void pressed();
    void long_pressed();
    void released();

protected:
    ////////////////////
    virtual void mousePressEvent(QMouseEvent*) override;
    virtual void mouseReleaseEvent(QMouseEvent*) override;

private:
    ////////////////////
    QTimer _long;
};

////////////////////////////////////////////////////////////////////////////////
#endif // SVGWIDGET_HPP
