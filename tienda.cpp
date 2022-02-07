#include "tienda.h"
#include "ui_tienda.h"

#include <QDebug>

Tienda::Tienda(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Tienda)
{
    ui->setupUi(this);
    //Lista de productos en el constructor
    cargarProductos();
    //Mostrar los productos en el combo box
    foreach(Producto *p, m_productos){
        ui->inProducto->addItem(p->nombre());
    }
    //Configurar cabecera de la tabla
    QStringList cabecera ={"Cantidad", "Producto", "P. unitario", "Subtotal"};
    ui->outDetalle->setColumnCount(4);
    ui->outDetalle->setHorizontalHeaderLabels(cabecera);

    //Establecer subtotal a cero
    m_subtotal=0;
}

Tienda::~Tienda()
{
    delete ui;
}

void Tienda::borrar(char a[])
{
    for(int i=0; i<11;i++){
        if (a[i] == '\n')
            a[i] = '\0';
    }
}

/**
 * @brief Tienda::cargarProductos Carga la lista de productos de la tienda
 */
void Tienda::cargarProductos()
{
    //Crear productos quemados en el codigo
    m_productos.append(new Producto(1, "Leche", 0.80));
    m_productos.append(new Producto(2, "Pan", 0.15));
    m_productos.append(new Producto(3, "Queso", 2.50));
}

void Tienda::calcular(float stProducto)
{
    //Calcular valores
    m_subtotal+=stProducto;
    m_iva=m_subtotal*IVA/100;
    m_total = m_subtotal+m_iva;
    //Mostrar valores en GUI
    ui->outSubtotal->setText("$ " + QString::number(m_subtotal, 'f', 2));
    ui->outIva->setText("$ " + QString::number(m_iva, 'f', 2));
    ui->outTotal->setText("$ " + QString::number(m_total, 'f', 2));

}

QString Tienda::obtenerDatos()
{
    return  "Cédula: " + ui->inCedula->displayText() + "\n" +
            "\nNombre: " + ui->inNombre->displayText() + "\n" +
            "\nTeléfono: " + ui->inTelefono->displayText() + "\n" +
            "\nE-mail: " + ui->inEmail->displayText() + "\n" +
            "\nDirección: " + ui->inDireccion->toPlainText()+ "\n"+
            "\nDETALLES DE LA COMPRA\n" +
            "----------------------------------------------\n" +
            "\nCantidad\tProducto\tP. unitario\tSubtotal\n";

}

void Tienda::limpiar()
{
    ui->inCedula->setText("");
    ui->inNombre->setText("");
    ui->inTelefono->setText("");
    ui->inEmail->setText("");
    ui->inDireccion->setPlainText("");
    //Iniclizar cantidad
    ui->inCantidad->setValue(0);

    //Inicializar iva - subtotal - total
    m_subtotal=0;
    m_iva=0;
    m_total=0;

    ui->outSubtotal->setText("0.0");
    ui->outIva->setText("0.0");
    ui->outTotal->setText("0.0");

    //Eliminar filas de la tabla
    ui->outDetalle->removeRow(0);
    ui->outDetalle->removeRow(0);
    ui->outDetalle->removeRow(0);
    ui->outDetalle->removeRow(0);

    //Restablecer colores
    ui->inCedula->setStyleSheet("QLineEdit{ background-color: white}");
    ui->inNombre->setStyleSheet("QLineEdit{ background-color: white}");
    ui->inTelefono->setStyleSheet("QLineEdit{ background-color: white}");
    ui->inEmail->setStyleSheet("QLineEdit{ background-color: white}");
    ui->inDireccion->setStyleSheet("QPlainTextEdit {background-color: white}");

}

bool Tienda::valcedulaEcuatoriana(char cedula[])
{
    int v[10], num, limite;
    limite = strlen(cedula);

    if (limite != 10){
        ui->inCedula->setStyleSheet("QLineEdit { background-color :red}");
        return false;
    }

    if (limite == 10){

        for (int i=0;i<10;i++){

            num = cedula[i]-48;
            v[i] = num; }

        //Proceso de validacion de cedula
        int vec[10], suma, ultimo, ultimon;
        if (v[0] == 1 || v[0] == 2){
            if (v[2] > 0 && v[2] < 6 ){

                for (int i=0; i<9; i+=2){
                    vec[i] = v[i] *2;
                    if (vec[i] >= 10)
                        vec[i] -= 9;
                }
                for (int i=1; i<9; i+=2){
                    vec[i] = v[i];
                }
                suma= 0;
                for(int i=0; i<10; i++){
                    suma = suma + vec[i];
                }
                if (suma == 10)
                    ultimo = 0;
                else if(suma >10 && suma<20)
                    ultimo = 20;
                else if (suma >20 && suma<30)
                    ultimo = 30;
                else if (suma >30 && suma<40)
                    ultimo = 40;
                else {
                    ui->inCedula->setStyleSheet("QLineEdit { background-color :red}");
                    return false;
                }
                ultimon = ultimo - suma;

                if (ultimon == v[9]){
                    ui->inCedula->setStyleSheet("QLineEdit { background-color :green}");
                    return true;
                }
                else{
                    ui->inCedula->setStyleSheet("QLineEdit { background-color :red}");}
                bool var=true;
                for (int i=0;i<10;i++){
                    if( strcmp(cedula, "9999999999")){
                        var=false;
                    }
                }
                if(var != false){
                    ui->inCedula->setStyleSheet("QLineEdit { background-color :green}");
                    return true;
                }
                return false;
            }else{
                ui->inCedula->setStyleSheet("QLineEdit { background-color :red}");
                bool var=true;
                for (int i=0;i<10;i++){
                    if( strcmp (cedula, "9999999999")){
                        var=false;
                    }
                }

                if(var != false){
                    ui->inCedula->setStyleSheet("QLineEdit { background-color :green}");
                    return true;
                }
                return false;
            }
        }
    }
}


void Tienda::on_inProducto_currentIndexChanged(int index)
{
    //Obtener el precio del producto actual seleccionado en base al indice de los productos en el vector
    float precio = m_productos.at(index)->precio();
    //Mostra el precio en la etiqueta
    ui->outPrecio->setText("$ " + QString::number(precio, 'f', 2));
    //Resetear el spinbox de cantidad
    ui->inCantidad->setValue(0);
}


void Tienda::on_btnAgregar_released()
{
    //Obtener datos de la GUI
    QString cedula = ui->inCedula->text();
    std::string utf8_text = cedula.toUtf8().constData();
    char buffer[100];
    strcpy(buffer,utf8_text.c_str());

    //validar que no se agregen productos con 0 cantidad
    int cantidad=ui->inCantidad->value();
    if(cantidad==0){
        return;
    }
    borrar(buffer);
    bool auxiliar=valcedulaEcuatoriana(buffer);
    if(auxiliar){
        //Obtener los datos de la GUI
        //Obtener producto
        int i = ui->inProducto->currentIndex();
        Producto *p = m_productos.at(i);

        //Calcular subtotal del producto
        float subtotal = p->precio()*cantidad;

        //Buscar y 'eliminar' repetidos
        if(!eliminarRepetidos(p, cantidad)){
            //Agregar datos a la tabla
            int fila = ui->outDetalle->rowCount(); //rowCout da el numero de filas
            ui->outDetalle->insertRow(fila);
            ui->outDetalle->setItem(fila, 0, new QTableWidgetItem(QString::number(cantidad)));
            ui->outDetalle->setItem(fila, 1, new QTableWidgetItem(p->nombre()));
            ui->outDetalle->setItem(fila, 2, new QTableWidgetItem(QString::number(p->precio(), 'f', 2)));
            ui->outDetalle->setItem(fila, 3, new QTableWidgetItem(QString::number(subtotal, 'f',2)));

        }

        //Limpiar datos
        ui->inCantidad->setValue(0);
        ui->inProducto->setFocus();

        //Actualizar subtotales
        calcular(subtotal);
    }
}
void Tienda::producto()
{
    int index = ui->inProducto->currentIndex();
    Producto *p = m_productos.at(index);
    int fila = ui->outDetalle->rowCount();
    ui->outDetalle->setItem(fila,1,new QTableWidgetItem(p->nombre()));
}

bool Tienda::eliminarRepetidos(Producto *producto, int cantidad)
{
    //Obtener NumFilas
    int numFilas = ui->outDetalle->rowCount();
    //Recorrer la tabla de productos
    for(int i=0;i<numFilas;i++){

        //Obtener el item en la fila y columna posicion 1
        QTableWidgetItem *item = ui->outDetalle->item(i,1);

        //Obtener el nombre del producto
        QString dato = item->data(Qt::DisplayRole).toString();

        //Comparar el producto
        if(dato==producto->nombre()){
            QTableWidgetItem *item = ui->outDetalle->item(i,0);
            int actualCantidad = item->data(Qt::DisplayRole).toInt();

            //Sumar las cantidades de un mismo producto
            int nuevaCantidad = actualCantidad + cantidad;

            //Calcular el nuevo subtotal generado
            float subtotal = nuevaCantidad*producto->precio();

            //Actualizar en la tabla
            ui->outDetalle->setItem(i,0,new QTableWidgetItem(QString::number(nuevaCantidad)));
            ui->outDetalle->setItem(i,3,new QTableWidgetItem(QString::number(subtotal)));
            return true;
        }
    }
    return false;
}


void Tienda::on_btnFinalizar_released()
{
    Factura *fac = new Factura();
    QString cedula= ui->inCedula->text();

    QStringList lista;
    QString productos;
    if(cedula.length() != 10){
        QMessageBox::warning(this, "ADVERTENCIA", "Datos importantes incompletos");
        return;
    }

    for( int fila = 0; fila < ui->outDetalle->rowCount(); ++fila)    {
        for( int columna = 0; columna < ui->outDetalle->columnCount(); ++columna){
            lista << ui->outDetalle->item(fila, columna)->text();
            QTableWidgetItem* item = ui->outDetalle->item(fila,columna);
            if (!item || item->text().isEmpty()){
                ui->outDetalle->setItem(fila,columna,new QTableWidgetItem("0"));
            }
            productos = lista.join("      ");
            lista<<"";
        }
        lista<<"\n";
        fac->compra(productos);
    }

    fac->registroDatos(obtenerDatos());
    fac->Subtotal(ui->outSubtotal->text());
    fac->Iva(ui->outIva->text());
    fac->Total(ui->outTotal->text());
    fac->exec();
    limpiar();
}


void Tienda::on_pushButton_released()
{
    limpiar();
}

