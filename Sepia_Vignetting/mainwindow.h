#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QButtonGroup>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private slots:
    void on_horizontalSlider_threads_number_choice_valueChanged(int value);

    void on_pushButton_modify_picture_clicked();

    void on_pushButton_choose_picture_clicked();

private:
    Ui::MainWindow *ui;

    uint8_t chosen_threads_num{};
    QButtonGroup lib_sources_table;

    void scalePixmap(QPixmap& pixmap, const QLabel& label);
    bool isLibraryChosen();
    bool isPremodifyPictureSelected();
    bool canModificationBeStarted();
    void updateThreadsNumberChoiceLabel();
    void initEffectsList();
    void initLibSourcesTable();
    void modifyPicture();
};
#endif // MAINWINDOW_H
