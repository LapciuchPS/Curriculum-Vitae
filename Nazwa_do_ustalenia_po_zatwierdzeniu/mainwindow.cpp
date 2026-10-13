#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "popupwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->chosen_threads_num = this->ui->horizontalSlider_threads_number_choice->value();
    this->updateThreadsNumberChoiceLabel();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateThreadsNumberChoiceLabel()
{
    QString label_preinfo = QStringLiteral("Threads number: %1");
    int curr_threads_num = this->ui->horizontalSlider_threads_number_choice->value();

    this->ui->label_threads_number_choice->setText(label_preinfo.arg(curr_threads_num));
}

void MainWindow::on_horizontalSlider_threads_number_choice_valueChanged(int value)
{
    this->updateThreadsNumberChoiceLabel();
}


void MainWindow::on_pushButton_modify_picture_clicked()
{
    if(not this->isLibraryChosen())
    {
        popupwindow::generateWarningMessage(QStringLiteral("No library chosen! Please choose one."));
        return;
    }

    if(not this->isPremodifyPictureSelected())
    {
        popupwindow::generateWarningMessage(QStringLiteral("No picture selected! Please, select one."));
        return;
    }

}

bool MainWindow::isLibraryChosen()
{
    return this->ui->radioButton_cpp_library->isChecked() || this->ui->radioButton_assembler_library->isChecked();
}

bool MainWindow::isPremodifyPictureSelected()
{
   return not this->ui->label_premodify_picture->pixmap().isNull();
}

