#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "popupwindow.h"
#include "effects.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->chosen_threads_num = this->ui->horizontalSlider_threads_number_choice->value();
    this->updateThreadsNumberChoiceLabel();

    this->initEffectsList();
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

void MainWindow::initEffectsList()
{
    QList<QPair<effect::EFFECT_NAME, QString>> effects = {
        {effect::EFFECT_NAME::SEPIA_EFFECT, "Sepia effect"},
        {effect::EFFECT_NAME::VIGNETTE_EFFECT, "Vignette effect"}
    };

    for(const auto& effect : effects)
    {
        QListWidgetItem* item = new QListWidgetItem(effect.second, this->ui->listWidget_effects_widget);

        item->setFlags(item->flags() | Qt::ItemIsUserCheckable);
        item->setCheckState(Qt::Unchecked);
        item->setData(Qt::UserRole, static_cast<int>(effect.first));
    }
}

void MainWindow::modifyPicture()
{
    for(size_t i=0; i<this->ui->listWidget_effects_widget->count(); ++i)
    {
        QListWidgetItem* item = this->ui->listWidget_effects_widget->item(i);

        if(item->checkState() == Qt::Unchecked)
            continue;

        int operation_id = item->data(Qt::UserRole).toInt();

        effect::EFFECT_NAME curr_effect = static_cast<effect::EFFECT_NAME>(operation_id);

        //call a function to modify the picture
    }
}

void MainWindow::on_horizontalSlider_threads_number_choice_valueChanged(int value)
{
    this->updateThreadsNumberChoiceLabel();
}


void MainWindow::on_pushButton_modify_picture_clicked()
{
    if(not this->canModificationBeStarted())
        return;

    this->modifyPicture();
}

bool MainWindow::isLibraryChosen()
{
    return this->ui->radioButton_cpp_library->isChecked() || this->ui->radioButton_assembler_library->isChecked();
}

bool MainWindow::isPremodifyPictureSelected()
{
   return not this->ui->label_premodify_picture->pixmap().isNull();
}

bool MainWindow::canModificationBeStarted()
{
    if(not this->isLibraryChosen())
    {
        popupwindow::generateWarningMessage(QStringLiteral("No library chosen! Please choose one."));
        return false;
    }

    if(not this->isPremodifyPictureSelected())
    {
        popupwindow::generateWarningMessage(QStringLiteral("No picture selected! Please, select one."));
        return false;
    }

    return true;
}

