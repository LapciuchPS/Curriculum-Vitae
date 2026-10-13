#include "popupwindow.h"
#include "ui_popupwindow.h"

popupwindow::popupwindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::popupwindow)
{
    ui->setupUi(this);
}

popupwindow::~popupwindow()
{
    delete ui;
}

void popupwindow::generateWarningMessage(const QString &warning_msg)
{
    popupwindow warning_window{};

    QString warning_str = QStringLiteral("Warning: %1");
    warning_window.ui->label_message->setText(warning_str.arg(warning_msg));

    warning_window.exec();
}

void popupwindow::generateErrorMessage(const QString& error_msg)
{
    popupwindow error_window{};

    QString error_str = QStringLiteral("Error: %1");
    error_window.ui->label_message->setText(error_str.arg(error_msg));

    error_window.exec();
}

void popupwindow::on_pushButton_clicked()
{
    this->close();
}

