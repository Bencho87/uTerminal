#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QSerialPortInfo>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
       buscaryconectar();
       if(arduino_disponible)
       {ui->pushButton->hide();}
}

MainWindow::~MainWindow()
{
    delete ui;
}



/*void MainWindow::on_pushButton_3_clicked()
{
    msg[0]=45;
    msg[1]=0;
    msg[2]=0;
    msg[3]=0;
    msg[4]=0;
    snd_msg(msg);

}

void MainWindow::on_pushButton_2_clicked()
{

    msg[0]=35;
    msg[1]=0;
    msg[2]=0;
    msg[3]=0;
    msg[4]=0;
    snd_msg(msg);

}*/

void MainWindow::on_pushButton_clicked()
{
    buscaryconectar();
}

void MainWindow::snd_msg(char *mensaje)
{


    if(arduino_disponible && Arduino->isWritable())
    {
       Arduino->write(mensaje,5);
    }

}


void MainWindow::buscaryconectar()
{
    arduino_disponible = false;
    das_disponible = false;
    arduino_puerto = "";
    Arduino = new QSerialPort;
    QString nombreDispositivoSerial = "";
    int nombreProductID = 0;

    //////////////////////////////////////////
    qDebug() << "Puertos disponibles: " << QSerialPortInfo::availablePorts().length();
    foreach (const QSerialPortInfo &serialPortInfo, QSerialPortInfo::availablePorts()) {
        qDebug() << "Identificador del fabricante (VENDOR ID): " << serialPortInfo.hasVendorIdentifier();
        if(serialPortInfo.hasVendorIdentifier()){
            qDebug() << "ID Vendedor " << serialPortInfo.vendorIdentifier();
            qDebug() << "ID Producto: " << serialPortInfo.productIdentifier();

            if(serialPortInfo.productIdentifier() == arduino_UNO || serialPortInfo.productIdentifier() == arduino_MEGA){
                arduino_disponible = true;
                nombreDispositivoSerial = serialPortInfo.portName();
                nombreProductID = serialPortInfo.productIdentifier();
            }
        }

    }

    //////////////////////////////////////////////////////////////
    //Pá detectar la dasp4550
    foreach (const QSerialPortInfo &serialPortInfo, QSerialPortInfo::availablePorts()) {
        qDebug() << "Identificador del fabricante (VENDOR ID): " << serialPortInfo.hasVendorIdentifier();
        if(serialPortInfo.hasVendorIdentifier()){
            qDebug() << "ID Vendedor " << serialPortInfo.vendorIdentifier();
            qDebug() << "ID Producto: " << serialPortInfo.productIdentifier();

            if(serialPortInfo.productIdentifier() == 11){
                das_disponible = true;
                nombreDispositivoSerial = serialPortInfo.portName();
                nombreProductID = serialPortInfo.productIdentifier();
            }
        }

    }


    ////////////////////////////////////////////////////////////////
    if(arduino_disponible){
        arduino_puerto = nombreDispositivoSerial;
        Arduino ->setPortName(arduino_puerto);
        Arduino->open(QIODevice::ReadWrite);
        Arduino->setDataBits(QSerialPort::Data8);
        //Arduino->setBaudRate(QSerialPort::Baud115200);
        Arduino->setBaudRate(2000000);
        Arduino->setParity(QSerialPort::NoParity);
        Arduino->setStopBits(QSerialPort::OneStop);
        Arduino->setFlowControl(QSerialPort::NoFlowControl);
        ui->label->clear();
        qDebug() << "Producto: " << nombreProductID;
        if(nombreProductID == 67) ui->label->setText("Arduino UNO R3 conectado");
        else if(nombreProductID == 66) ui->label->setText("Arduino Mega conectado");
        else ui->label->setText("Dispositivo no encontrado");
    }
    else{

    //////////////////////////////////////////////////////////
    if(das_disponible){
        qDebug()<<"Siquiera entro aqui";
        arduino_puerto = nombreDispositivoSerial;
        Arduino ->setPortName(arduino_puerto);
        Arduino->open(QIODevice::ReadWrite);
        Arduino->setDataBits(QSerialPort::Data8);
        //Arduino->setBaudRate(QSerialPort::Baud115200);
        Arduino->setBaudRate(9600);
        Arduino->setParity(QSerialPort::NoParity);
        Arduino->setStopBits(QSerialPort::OneStop);
        Arduino->setFlowControl(QSerialPort::NoFlowControl);
        ui->label->clear();
        qDebug() << "Producto: " << nombreProductID;
        if(nombreProductID == 11) ui->label->setText("DASP4550 Conectada");
        else ui->label->setText("Dispositivo no encontrado");
    }

    else{

        ui->label->clear();
        ui->label->setText("No hay arduino");
        }
    }

}
