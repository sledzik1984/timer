////////////////////////////////////////////////////////////////////////////////
#ifndef EDITWINDOW_HPP
#define EDITWINDOW_HPP

#include "ui_editwindow.h"

#include <QFileDialog>
#include <QObject>
#include <QWidget>

////////////////////////////////////////////////////////////////////////////////
class EditWindow : public QWidget, private Ui::EditWindow
{
    Q_OBJECT

public:
    explicit EditWindow(QWidget* parent = nullptr);

private:
    void   clear_clicked();
    void    open_clicked();
    void    save_clicked();
    void save_as_clicked();

    QFileDialog* dialog = nullptr;
};

////////////////////////////////////////////////////////////////////////////////
#endif // EDITWINDOW_HPP
