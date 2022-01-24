#include "tienda.h"
#include "ui_tienda.h"

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
    //Configurara cabecera de la tabla
    QStringList cabecera ={"Cantidad", "Producto", "Subtotal"};
    ui->outDetalle->setColumnCount(3);
    ui->outDetalle->setHorizontalHeaderLabels(cabecera);

}

Tienda::~Tienda()
{
    delete ui;
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

