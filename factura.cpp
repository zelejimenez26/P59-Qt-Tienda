#include "factura.h"
#include "ui_factura.h"
#include <QDebug>

Factura::Factura(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Factura)
{
    ui->setupUi(this);
    toString();
    ui->outDatosFactura->setPlainText(m_datos);
}

Factura::~Factura()
{
    delete ui;
}

void Factura::registroDatos(QString datos)
{
    ui->outFactura->setPlainText(datos);
}

void Factura::compra(QString productos)
{
    ui->outListaCompra->setPlainText(productos);
}

void Factura::Subtotal(QString subtotal)
{
    ui->outSubtotal->setText(subtotal);
}

void Factura::Iva(QString iva)
{
    ui->outiva->setText(iva);
}

void Factura::Total(QString total)
{
    ui->outTotal->setText(total);
}

void Factura::toString()
{
    m_datos+="**************************************\n";
    m_datos+="\tNacho Store\n";
    m_datos+="\t  El Eden\n";
    m_datos+="**************************************\n";
    m_datos+="\tFACTURA\n";
    fecha=QDate::currentDate().toString("dd.MM.yyyy");
    hora=QTime::currentTime().toString("hh:mm:ss");
    fechaCompleta=QDateTime::currentDateTime().toString("ddMMyyyy_hhmmss");
    m_datos+="Fecha: "+fecha+"\t";
    m_datos+="Hora: "+hora+"\n";
    m_datos+="**************************************\n";
    m_datos+="DATOS DEL CLIENTE\n";
}

void Factura::on_btnImprimir_clicked()
{
    //Creando un directorio a partir de un path
    QFile directorio("C:/Users/DELL/OneDrive/Escritorio/Zelena/2do semestre/POO/Proyectos Qt/Archivos Qt/Tienda/"+fechaCompleta);
    if(directorio.open(QFile::WriteOnly|QIODevice::Text)){
        //Crear un stream de texto
        QTextStream salida(&directorio);
        //Enviar los datos del resulatdo a la salida
        salida<<ui->outDatosFactura->toPlainText();
        salida<<"---------------------------------\n";
        salida<<ui->outFactura->toPlainText();
        salida<<ui->outListaCompra->toPlainText()<<"\n";
        salida<<"Subtotal: "<<ui->outSubtotal->text()<<"\n";
        salida<<"IVA: "<<ui->outiva->text()<<"\n";
        salida<<"Total: "<<ui->outTotal->text()<<"\n";

        //Mostrar por 5 segundos que todo esta bien
        //ui->statusbar->showMessage("Datos alamcenados en " + nombreArchivo, 5000);
    }else{
        QMessageBox::warning(this,tr("Guardar datos"), tr("No se puedo guardar el archivo"));
    }
    //Cuadro de dialogo que informa que la impresion se realizo
    QMessageBox::information(this,
                         tr("Datos"),
                         tr("Datos listos para imprimir"));
    //Cerrar archivo
    directorio.close();
}


void Factura::on_btnCancelar_clicked()
{
    close();
}

