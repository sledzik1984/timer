////////////////////////////////////////////////////////////////////////////////
#ifndef EDITWINDOW_HPP
#define EDITWINDOW_HPP

#include "eventmodel.hpp"
#include "timedelegate.hpp"

#include "ui_editwindow.h"

#include <QFileDialog>
#include <QModelIndex>
#include <QObject>
#include <QWidget>

////////////////////////////////////////////////////////////////////////////////
class EditWindow : public QWidget, private Ui::EditWindow
{
    Q_OBJECT

public:
    explicit EditWindow(QWidget* parent = nullptr);

private:
    EventModel* model = EventModel::get_model();

    void   clear_clicked();
    void    open_clicked();
    void    save_clicked();
    void save_as_clicked();

    QFileDialog* dialog = nullptr;

    void update_save();
    void update_current(const QModelIndex& current);

    TimeDelegate delegate;

    void     add_clicked();
    void  insert_clicked();
    void  remove_clicked();
};

////////////////////////////////////////////////////////////////////////////////
#endif // EDITWINDOW_HPP
