////////////////////////////////////////////////////////////////////////////////
#include "editwindow.hpp"
#include "eventmodel.hpp"

#include <QMessageBox>

////////////////////////////////////////////////////////////////////////////////
EditWindow::EditWindow(QWidget* parent) : QWidget(parent),
    dialog(new QFileDialog(this))
{
    setupUi(this);

    connect(clear  , &QToolButton::clicked, this, &EditWindow::  clear_clicked);
    connect(open   , &QToolButton::clicked, this, &EditWindow::   open_clicked);
    connect(save   , &QToolButton::clicked, this, &EditWindow::   save_clicked);
    connect(save_as, &QToolButton::clicked, this, &EditWindow::save_as_clicked);

    dialog->setConfirmOverwrite(true);
    dialog->setDefaultSuffix("xml");
    dialog->setNameFilters(QStringList() << "Event files (*.xml)" << "All files (*)");

    sections->setModel(EventModel::get_model());
}

////////////////////////////////////////////////////////////////////////////////
void EditWindow::clear_clicked()
{
    EventModel::get_model()->clear();
}

////////////////////////////////////////////////////////////////////////////////
void EditWindow::open_clicked()
try
{
    dialog->setFileMode(QFileDialog::ExistingFile);
    dialog->setAcceptMode(QFileDialog::AcceptOpen);

    if(dialog->exec() == QDialog::Accepted)
        EventModel::get_model()->open(dialog->selectedFiles().at(0));
}
catch(const QString& e)
{
    QMessageBox::critical(this, "Error", e);
}

////////////////////////////////////////////////////////////////////////////////
void EditWindow::save_clicked()
try
{
    EventModel::get_model()->save();
}
catch(const QString& e)
{
    QMessageBox::critical(this, "Error", e);
}

////////////////////////////////////////////////////////////////////////////////
void EditWindow::save_as_clicked()
try
{
    dialog->setFileMode(QFileDialog::AnyFile);
    dialog->setAcceptMode(QFileDialog::AcceptSave);

    if(dialog->exec() == QDialog::Accepted)
        EventModel::get_model()->save_as(dialog->selectedFiles().at(0));
}
catch(const QString& e)
{
    QMessageBox::critical(this, "Error", e);
}
