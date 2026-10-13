#ifndef POPUPWINDOW_H
#define POPUPWINDOW_H

#include <QDialog>

namespace Ui {
class popupwindow;
}

class popupwindow : public QDialog
{
    Q_OBJECT

public:
    explicit popupwindow(QWidget *parent = nullptr);
    ~popupwindow();

    static void generateWarningMessage(const QString& warning_msg);
    static void generateErrorMessage(const QString& error_msg);

private slots:
    void on_pushButton_clicked();

private:
    Ui::popupwindow *ui;

};

#endif // POPUPWINDOW_H
