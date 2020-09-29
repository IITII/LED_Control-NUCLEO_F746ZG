#ifndef LEDCONTROLWINDOW_H
#define LEDCONTROLWINDOW_H

#include <QMainWindow>
#include <QNetworkAccessManager>
#include <QNetworkReply>


QT_BEGIN_NAMESPACE
namespace Ui { class LedControlWindow; }
QT_END_NAMESPACE

class LedControlWindow : public QMainWindow
{
    Q_OBJECT

public:
    LedControlWindow(QWidget *parent = nullptr);
    ~LedControlWindow();

private slots:
    void on_onButton_clicked();

    void on_offButton_clicked();

    void on_toggleButton_clicked();

    void onNetworkRequestFinished(QNetworkReply *reply);

private:
    Ui::LedControlWindow *ui;

    QNetworkAccessManager manager;
};
#endif // LEDCONTROLWINDOW_H
