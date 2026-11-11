#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "popupwindow.h"
#include "effects.h"
#include "timemeter.h"

#include "libs/ImageEffects_api.h"

#include <thread>
#include <vector>

#include <QFileDialog>
#include <QPixmap>
#include <QImage>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->chosen_threads_num = this->ui->horizontalSlider_threads_number_choice->value();
    this->updateThreadsNumberChoiceSpinBox();

    this->initEffectsList();
    this->initLibSourcesTable();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateThreadsNumberChoiceSpinBox()
{
    int curr_threads_num = this->ui->horizontalSlider_threads_number_choice->value();

    this->ui->spinBox_threads_number_choice->setValue(curr_threads_num);
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

void MainWindow::initLibSourcesTable()
{
    this->lib_sources_table.addButton(this->ui->radioButton_assembler_library, static_cast<int>(effect::ALGORITHM_SOURCE::ASM));
    this->lib_sources_table.addButton(this->ui->radioButton_cpp_library, static_cast<int>(effect::ALGORITHM_SOURCE::CPP));
}

void MainWindow::modifyPicture()
{
    //preparing threads
    int thread_num = this->ui->spinBox_threads_number_choice->value();
    std::vector<std::thread> threads{};
    threads.reserve(thread_num);

    //preparing the image
    QImage base_image(this->ui->label_premodify_picture->pixmap().toImage());
    base_image = base_image.convertToFormat(QImage::Format_ARGB32);

    uchar* bit_ptr = base_image.bits();
    int bytes_per_line = base_image.bytesPerLine();
    int image_width = base_image.width();
    int image_height = base_image.height();

    int lines_per_thread = base_image.height() / thread_num;
    int start_row{};
    int end_row{};

    //preparing timer
    TimeMeter timer{};

    for(size_t i=0; i<this->ui->listWidget_effects_widget->count(); ++i)
    {
        QListWidgetItem* item = this->ui->listWidget_effects_widget->item(i);

        if(item->checkState() == Qt::Unchecked)
            continue;

        threads.clear();

        int operation_id = item->data(Qt::UserRole).toInt();

        effect::EFFECT_NAME curr_effect = static_cast<effect::EFFECT_NAME>(operation_id);
        effect::ALGORITHM_SOURCE curr_source = static_cast<effect::ALGORITHM_SOURCE>(this->lib_sources_table.checkedId());

        Func* curr_func = effect::getEffectFunction(curr_source, curr_effect);

        timer.startTimeSurvey();

        for(int i = 0;i<thread_num - 1;++i)
        {
            start_row = i*lines_per_thread;
            end_row = (i+1)*lines_per_thread;

            EffectParams params = {bit_ptr, start_row, end_row, image_width, image_height, bytes_per_line};
            threads.emplace_back([curr_func, params](){
                curr_func(&params);
            });
        }

        start_row = (thread_num - 1)*lines_per_thread;
        end_row = image_height;
        EffectParams last_params = {bit_ptr, start_row, end_row, image_width, image_height, bytes_per_line};
        threads.emplace_back([curr_func, last_params](){
            curr_func(&last_params);
        });

        std::for_each(threads.begin(), threads.end(), [](std::thread& curr_thread){curr_thread.join();});

        timer.endTimeSurvey();
    }



    QPixmap modified_pixmap{QPixmap::fromImage(base_image)};
    this->ui->label_modified_picture->setPixmap(modified_pixmap);
}

void MainWindow::on_horizontalSlider_threads_number_choice_valueChanged(int value)
{
    this->updateThreadsNumberChoiceSpinBox();
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

void MainWindow::on_pushButton_choose_picture_clicked()
{
    QString file_name = QFileDialog::getOpenFileName(this, "Choose picture", "", "Pictures (*.png *.jpg *.jpeg *.bmp)");

    if(file_name.isEmpty())
        return;

    QPixmap chosen_picture (file_name);

    if(chosen_picture.isNull())
        return;

    this->scalePixmap(chosen_picture, *this->ui->label_premodify_picture);
    this->ui->label_premodify_picture->setPixmap(chosen_picture);
}

void MainWindow::scalePixmap(QPixmap &pixmap, const QLabel &label)
{
    QSize base_size = label.contentsRect().size();
    pixmap = pixmap.scaled(base_size, Qt::KeepAspectRatio, Qt::SmoothTransformation);
}

void MainWindow::on_pushButton_reset_picture_clicked()
{
    this->ui->label_modified_picture->setPixmap(this->ui->label_premodify_picture->pixmap());
}

