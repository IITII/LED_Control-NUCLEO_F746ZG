#include "ledcontrolwindow.h"
#include "ui_ledcontrolwindow.h"

#include <QDebug>
#include <QNetworkRequest>
#include <QUrl>

LedControlWindow::LedControlWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::LedControlWindow)
{
    ui->setupUi(this);

    int led_numbers = 3;
    for (int i = 0; i < led_numbers; i++) {
        ui->ledBox->addItem("LED" + QString::number(i + 1));
    }

    connect(&manager, &QNetworkAccessManager::finished, this, &LedControlWindow::onNetworkRequestFinished);
}

LedControlWindow::~LedControlWindow()
{
    delete ui;
}


void LedControlWindow::on_onButton_clicked()
{
    QNetworkRequest request(QUrl("http://" + ui->addressEdit->text() + "/" + QString::number(ui->ledBox->currentIndex() + 1) + "/on"));
    manager.get(request);
}

void LedControlWindow::on_offButton_clicked()
{
    QNetworkRequest request(QUrl("http://" + ui->addressEdit->text() + "/" + QString::number(ui->ledBox->currentIndex() + 1) + "/off"));
    manager.get(request);
}

void LedControlWindow::on_toggleButton_clicked()
{
    QNetworkRequest request(QUrl("http://" + ui->addressEdit->text() + "/" + QString::number(ui->ledBox->currentIndex() + 1) + "/toggle"));
    manager.get(request);
}

void LedControlWindow::onNetworkRequestFinished(QNetworkReply *reply)
{
    if (reply->error() != QNetworkReply::NoError) {
        ui->statusbar->showMessage(reply->errorString());
    }
}
