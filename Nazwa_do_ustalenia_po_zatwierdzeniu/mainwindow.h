#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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

private:
    Ui::MainWindow *ui;

    uint8_t chosen_threads_num{};

    void updateThreadsNumberChoiceLabel();
};
#endif // MAINWINDOW_H
