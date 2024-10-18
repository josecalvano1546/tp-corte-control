// Definición de la estructura Producto
#include <__config>
#include <iomanip>
#include <iostream>
#include <ostream>
#include <string>
template <typename T>
struct Producto
{
    T nombre;          // Cambiado a 'T' para permitir flexibilidad en el tipo (ej: string para el nombre)
    unsigned cantidad; // Acumulará la cantidad de ese producto ej: 300

    // Constructor para inicializar valores
    Producto() : nombre(""), cantidad(0) {}  // Constructor por defecto
    Producto(T _nombre, unsigned _cantidad) : nombre(_nombre), cantidad(_cantidad) {}
};

// Definición del nodo que contiene Productos
template <typename T>
struct NodoSub
{
    Producto<T> info; // Estructura de un Producto
    NodoSub<T> *sig;  // Puntero al siguiente subNodo [Producto:1]-->[Producto:2]-->null

    // Constructor para inicializar un NodoSub
    NodoSub(Producto<T> _info) : info(_info), sig(nullptr) {}
};


// Definicion de la estructura ciudad
template <typename T>
struct Provincia
{
    T nombre;          // Cambiado a 'T' para permitir flexibilidad en el tipo (ej: string para el nombre)
    unsigned cantidad; // Acumulará la cantidad de ese producto ej: 300

    // Constructor para inicializar valores
    Provincia() : nombre(""), cantidad(0) {}  // Constructor por defecto
    Provincia(T _nombre, unsigned _cantidad) : nombre(_nombre), cantidad(_cantidad) {}
};

// Definición del nodo que contiene Ciudades 
template <typename T>
struct NodoSubProvincia
{
    Provincia<T> info; // Estructura de una ciudad
    NodoSubProvincia<T> *sig;  // Puntero al siguiente subNodo [ciudad:corrientes]-->[Ciudad:BsAs]-->null

    // Constructor para inicializar un NodoSubCiudad
    NodoSubProvincia(Provincia<T> _info) : info(_info), sig(nullptr) {}
};

// Definición de la estructura Dock
template <typename T>
struct Dock
{
    unsigned nroDock;           // Número del dock ej: 1
    int cantDespacho;           // Acumulador para la cantidad de despachos
    NodoSub<T> *listaProductos; // Puntero a la lista de productos (nodos) [Producto:Taladro]-->[Producto:Martillo]-->null
    NodoSubProvincia<T> *listaProvincias; // Puntero a la lista de productos (nodos) [Producto:Taladro]-->[Producto:Martillo]-->null

    Dock() : nroDock(0), cantDespacho(0), listaProductos(nullptr), listaProvincias(nullptr) {}
    Dock(unsigned _nroDock) : nroDock(_nroDock), cantDespacho(0), listaProductos(nullptr), listaProvincias(nullptr) {}
};

// Definición del nodo que contiene Docks
template <typename T>
struct Nodo
{
    Dock<T> info; // Información del Dock
    Nodo<T> *sig; // Puntero al siguiente nodo [Dock:1]-->[Dock:2]-->null

    // Constructor para inicializar un Nodo
    Nodo(Dock<T> _info) : info(_info), sig(nullptr) {}
};

// Estructura del dock

// Lista de docks que leeremos del archivo
// Función para agregar un nodo a la lista
template <typename T>
struct DockArchivo
{
    unsigned nroDock;  // Número del dock (1-10)
    T provincia;       // Nombre de la provincia a la que se realizará el envío
    T producto;        // Nombre del producto
    unsigned cantidad; // Cantidad de productos

    // Constructor para inicializar DockArchivo
    DockArchivo(unsigned _nroDock, T _provincia, T _producto, unsigned _cantidad)
        : nroDock(_nroDock), provincia(_provincia), producto(_producto), cantidad(_cantidad) {}
};

// Nodo que contiene el DockArchivo
template <typename T>
struct NodoArchivo
{
    DockArchivo<T> info; // Información del Dock que obtenemos del archivo
    NodoArchivo<T> *sig; // Puntero al siguiente nodo

    // Constructor para inicializar NodoArchivo
    NodoArchivo(DockArchivo<T> _info) : info(_info), sig(nullptr) {}
};

///////////////////////// ESTAS FUNCIONES DEBEN SER ADAPTADOS A LA LECTURA DEL ARCHIVO /////////////////////////
// Función para mostrar la lista
template <typename T>
void mostrarLista(NodoArchivo<T> *lista)
{
    NodoArchivo<T> *temp = lista;
    while (temp)
    {
        std::cout << "Dock: " << temp->info.nroDock << ", Producto: " << temp->info.producto
                  << ", Provincia: " << temp->info.provincia << ", Cantidad: " << temp->info.cantidad << std::endl;
        temp = temp->sig;
    }
}

// Función para agregar un nodo a la lista
template <typename T>
void agregarNodo(NodoArchivo<T> *&lista, DockArchivo<T> dockInfo)
{
    NodoArchivo<T> *nuevoNodo = new NodoArchivo<T>(dockInfo);
    if (!lista)
    {
        lista = nuevoNodo; // Si la lista está vacía, el nuevo nodo es el primero
    }
    else
    {
        NodoArchivo<T> *temp = lista;
        while (temp->sig)
        { // Recorrer hasta el final de la lista
            temp = temp->sig;
        }
        temp->sig = nuevoNodo; // Agregar al final de la lista
    }
}

// funcion mostar lista con sus totales Lista principal
template <typename T>
void mostrarListaDocks(Nodo<T> *lista)
{
    Nodo<T> *p = lista;

    // Recorrer la lista de docks
    while (p != nullptr)
    {
        std::cout << "Dock Número: " << p->info.nroDock << " - Cantidad de despachos: " << p->info.cantDespacho << std::endl;

        std::cout << std::left << std::setw(20) << "Producto" << "Cantidad" << std::endl;

        // Mostrar la sublista de productos dentro de este dock
        mostrarListaProductos(p->info.listaProductos);
        std::cout << std::endl;
        // Avanzar al siguiente dock
        p = p->sig;
    }
}
// Mostrar lista anidada
template <typename T>
void mostrarListaProductos(NodoSub<T> *listaProductos)
{
    NodoSub<T> *p = listaProductos;

    // Recorrer la sublista de productos
    while (p != nullptr)
    {
        std::cout << std::left << std::setw(20) << p->info.nombre << p->info.cantidad << std::endl;

        // Avanzar al siguiente producto
        p = p->sig;
    }
}

// Mostrar lista anidada
template <typename T>
void mostrarListaProvincias(NodoSubProvincia<T> *listaProvincias)
{
    NodoSubProvincia<T> *p = listaProvincias;

    // Recorrer la sublista de productos
    while (p != nullptr)
    {
        std::cout << std::left << std::setw(20) << p->info.nombre << p->info.cantidad << std::endl;

        // Avanzar la siguiente provincia
        p = p->sig;
    }
}

template <typename T>
void mostrarDockMenorDespacho(Nodo<T> *lista, int nroDock){
    Nodo<T> *p = lista;

    // Recorrer la lista de docks
    while (p != nullptr){
        if(p->info.nroDock == nroDock){
            std::cout << "El dock con menos despachos es: " << p->info.nroDock << " con: " << p->info.cantDespacho << " despachos" <<  std::endl;
            
                 NodoSub<T> *pSubListProd = p->info.listaProductos;
                std::string prodMayorDespacho;
                int mayorCantidad = 0;
                while (pSubListProd != nullptr)
                {
                    if(pSubListProd -> info.cantidad > mayorCantidad){
                        mayorCantidad = pSubListProd->info.cantidad;
                        prodMayorDespacho = pSubListProd->info.nombre;
                    }
                    pSubListProd = pSubListProd->sig;
                }
            std::cout << "El producto con mayor cantidad de despachos en ese dock es: " <<  std::endl;
            std::cout << prodMayorDespacho << "  " << mayorCantidad << std::endl;
            std::cout << "Lista de despachos " <<  std::endl;
            std::cout << std::left << std::setw(20) << "Provincia" << "Cantidad" << std::endl;
            mostrarListaProvincias(p->info.listaProvincias);
        }
        p = p->sig;
    }
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Funcion buscarInsertarDock
template <typename T>
Nodo<T> *buscarInsertarDock(Nodo<T> *&lista, Dock<T> dockInfo)
{
    Nodo<T> *anterior = lista;
    Nodo<T> *p = lista;

    while (p != nullptr && p->info.nroDock < dockInfo.nroDock)
    {
        anterior = p;
        p = p->sig;
    }
    if (p != nullptr && dockInfo.nroDock == p->info.nroDock)
    {
        return p;
    }
    else
    {
        Nodo<T> *n = new Nodo<T>(dockInfo);
        n->info = dockInfo;
        n->sig = p;
        if (p != lista)
        {
            if (anterior != nullptr)
            {
                anterior->sig = n; // Conectar el nodo anterior con el nuevo nodo
            }
            else
            {
                lista = n; // Si `anterior` es null, significa que `n` es el nuevo primer nodo
            }
        }
        else
        {
            lista = n;
        }

        return n;
    }
}

// Funcion buscarInsertar en la sublista producto
template <typename T>
NodoSub<T> *buscarInsertarSubProd(NodoSub<T> *&lista, Producto<T> prodInfo)
{
    NodoSub<T> *anterior = lista;
    NodoSub<T> *p = lista;

    while (p != nullptr && p->info.nombre < prodInfo.nombre)
    {
        anterior = p;
        p = p->sig;
    }
    if (p != nullptr && prodInfo.nombre == p->info.nombre)
    {
        return p;
    }
    else
    {
        NodoSub<T> *n = new NodoSub<T>(prodInfo);
        n->info = prodInfo;
        n->sig = p;
        if (p != lista)
        {
            if (anterior != nullptr)
            {
                anterior->sig = n; // Conectar el nodo anterior con el nuevo nodo
            }
            else
            {
                lista = n; // Si `anterior` es null, significa que `n` es el nuevo primer nodo
            }
        }
        else
        {
            lista = n;
        }

        return n;
    }
}

// Funcion buscarInsertar en la sublista provincia
template <typename T>
NodoSubProvincia<T> *buscarInsertarSubProv(NodoSubProvincia<T> *&lista, Provincia<T> provInfo)
{
    NodoSubProvincia<T> *anterior = lista;
    NodoSubProvincia<T> *p = lista;

    while (p != nullptr && p->info.nombre < provInfo.nombre)
    {
        anterior = p;
        p = p->sig;
    }
    if (p != nullptr && provInfo.nombre == p->info.nombre)
    {
        return p;
    }
    else
    {
        NodoSubProvincia<T> *n = new NodoSubProvincia<T>(provInfo);
        n->info = provInfo;
        n->sig = p;
        if (p != lista)
        {
            if (anterior != nullptr)
            {
                anterior->sig = n; // Conectar el nodo anterior con el nuevo nodo
            }
            else
            {
                lista = n; // Si `anterior` es null, significa que `n` es el nuevo primer nodo
            }
        }
        else
        {
            lista = n;
        }

        return n;
    }
}



int main(int argc, char const *argv[])
{
    /* code */
    // Inicializamos la lista binaria y cargamos los valores ORDENADOS en la lista principal a recorrer
    /*
                ______________         ______________         ______________         ______________
                | Dock:1       |       | Dock:2       |       | Dock:3       |       | Dock:4       |
                | Prod:Taladro |       | Prod:Martillo|       | Prod:Sierra  |       | Prod:Destorn.|
    Lista -->   | Prov:Corr    | ----> | Prov:BsAs    | ----> | Prov:Mendoza | ----> | Prov:Rosario | --> Null
                | Cant:25      |       | Cant:50      |       | Cant:10      |       | Cant:75      |
                |______________|       |______________|       |______________|       |______________|

    */

    /////////////////////////////// Inicializamos la lista de archivos ///////////////////////////////
    NodoArchivo<std::string> *listaArchivos = nullptr;

    // Creamos algunos docks para insertar en la lista
    DockArchivo<std::string> dock1(1, "Corrientes", "Taladro", 25);
    DockArchivo<std::string> dock5(1, "Buenos Aires", "Taladro", 25);
    DockArchivo<std::string> dock6(1, "Chubut", "Martillo", 5);
    DockArchivo<std::string> dock7(1, "Buenos Aires", "Sierra", 5);

    DockArchivo<std::string> dock2(2, "Buenos Aires", "Martillo", 50);
    DockArchivo<std::string> dock13(2, "Buenos Aires", "Sierra", 50);
    DockArchivo<std::string> dock8(2, "Misiones", "Taladro", 13);

    DockArchivo<std::string> dock3(3, "Mendoza", "Sierra", 10);
    DockArchivo<std::string> dock9(3, "Corrientes", "Martillo", 10);
    DockArchivo<std::string> dock10(3, "Mendoza", "Sierra", 10);
    DockArchivo<std::string> dock14(3, "Mendoza", "Sierra", 10);

    DockArchivo<std::string> dock4(4, "Rosario", "Martillo", 20);
    DockArchivo<std::string> dock11(4, "Buenos Aires", "Taladro", 15);
    DockArchivo<std::string> dock12(4, "Chubut", "Destornillador", 17);
    DockArchivo<std::string> dock15(4, "Chubut", "Destornillador", 17);


    // Agregamos los docks a la lista
    agregarNodo(listaArchivos, dock1); agregarNodo(listaArchivos, dock8);
    agregarNodo(listaArchivos, dock2); agregarNodo(listaArchivos, dock9);
    agregarNodo(listaArchivos, dock3); agregarNodo(listaArchivos, dock10);
    agregarNodo(listaArchivos, dock4); agregarNodo(listaArchivos, dock11);
    agregarNodo(listaArchivos, dock5); agregarNodo(listaArchivos, dock12);
    agregarNodo(listaArchivos, dock6); agregarNodo(listaArchivos, dock13);
    agregarNodo(listaArchivos, dock7); agregarNodo(listaArchivos, dock14);
    agregarNodo(listaArchivos, dock15);
    
    //////////////////////////////////////////////////////////////////////////////////////////////////////////

    // Cargamos la nueva lista y sublista
    Nodo<std::string> *listaDocTotales = nullptr; // Lista de nodos que contiene Docks
    Dock<std::string> dc;                         // Un dock específico
    Producto<std::string> prod;                   // Un producto específico
    Provincia<std::string> prov;                   // Una Provincia específica

    // Punteros a nuestra lista inicial
    NodoArchivo<std::string> *p = listaArchivos;
    NodoArchivo<std::string> *nd = listaArchivos; // nd - Puntero que va a determinar el fin del archivo

    while (nd != nullptr)
    {
        dc.nroDock = nd->info.nroDock;                          // Carga la estructura del doc con el numero.
        dc.cantDespacho = 0;                                    // Carga la estructura del doc con la cantidad de despachos que se van a ir acumulando.

        // Buscar insertar en la lista de Docks
        Nodo<std::string> *pSub = buscarInsertarDock(listaDocTotales, dc);

        // a la lista creada acumulamos 1
        pSub->info.cantDespacho += 1;

        prod.nombre = nd->info.producto; // Cargamos la subestructura con el producto.

        // Buscar insertar en la sublista de Docks es decir en PRODUCTOS.
        NodoSub<std::string> *pSubProducto = buscarInsertarSubProd(pSub->info.listaProductos, prod);

        // Asigno la cantidad acumulando
        pSubProducto->info.cantidad += nd->info.cantidad;

        // -- Provincia --- //
        prov.nombre = nd->info.provincia; // Cargamos la subestructura con el provincia.

        // Buscar insertar en la sublista de Docks es decir en CIUDADES.
        NodoSubProvincia<std::string> *pSubProvincia = buscarInsertarSubProv(pSub->info.listaProvincias, prov);

        // Asigno la cantidad acumulando
        pSubProvincia->info.cantidad += nd->info.cantidad;

        // Hasta aca deberia estar cargada la sublista. y sus valores
        nd = nd->sig; // Avanza al siguiente nodo
    };

    mostrarListaDocks(listaDocTotales);

    int dockMenorDespachos = 10000;
    int menorCantidad = 1000;

    Nodo<std::string> *pSublist = listaDocTotales;

    while (pSublist != nullptr)
    {
        if (pSublist->info.cantDespacho < menorCantidad) // Va a guardar el primero si hay varios siempre muestro el primero.
        {
            menorCantidad = pSublist->info.cantDespacho;   // Actualizamos la menor cantidad
            dockMenorDespachos = pSublist->info.nroDock;  // Guardamos el nroDock con menor cantidad
        }
        pSublist = pSublist->sig;  // Avanzamos al siguiente nodo
    }

    mostrarDockMenorDespacho(listaDocTotales, dockMenorDespachos);

    return 0;
}
