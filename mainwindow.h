#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSerialPort>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();
    void snd_msg(char *mensaje);
private:
    //

    Ui::MainWindow *ui;
    QSerialPort *Arduino;
        static const quint16 arduino_uno_vendor_id = 9025;
        static const quint16 arduino_UNO = 67;
        static const quint16 arduino_MEGA = 66;
        static const quint16 das_vendor_vid = 9221;
        static const quint16 das_pid = 11;

        bool arduino_disponible;
        bool das_disponible;
        QString arduino_puerto;
        void buscaryconectar();

        char mensaje[5];
        char msg[5];
};
#endif // MAINWINDOW_H
