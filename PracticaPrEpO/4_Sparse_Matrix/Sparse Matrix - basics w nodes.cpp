#include <iostream>

//técnicamente, la sparse matrix está llena de ceros, pero estos no cuentan,
// hasta que, un valor non-zero ocupe ese espacio

//nodos de la sparse matrix
struct SMNode {
    int valor; //valor distinto de nulo
    int x_data; //indice de fila (x)
    int y_data; //indice de columna (y)
    SMNode* next; //sgte en la fila
    SMNode* down; //sgte en la columna
    SMNode(int val, int x, int y) : valor(val), x_data(x), y_data(y) {
        next = nullptr;
        down = nullptr;
    }
};

/*
//proxy de paso para mapear los nodos LO GUARDAMOS
template<class M>
struct ProxyToMap {
    int valor; //valor actual en (x_tmp, y_tmp)
    int x_tmp;
    int y_tmp;
    M* matrix; //puntero a la matriz que gestiona

    ProxyToMap(int val, int x, int y, M* m) : valor(val), x_tmp(x), y_tmp(y), matrix(m) {}

    //para lectura implícita
    operator int() const { return valor; }
    //para escritura: , si no → inserta o actualiza
    ProxyToMap<M>& operator= (int val) {
        if (val == 0) {
            matrix->eliminar(x_tmp, y_tmp);
        }
        else {
            matrix->insertar(x_tmp, y_tmp, val);
        }
        return *this;
    }
};
*/

template<int filas, int columnas>
class SMatrix {
private:
    SMNode* filaHeads[filas];
    SMNode* colHeads[columnas];

    //verificar si las coordenadas están disponibles
    bool inRange(int x, int y) const {
        return (x >= 0 && x < filas) && (y >= 0 && y < columnas);
    }
    //función findInFila: recorre la lista hasta encontrar la posición
    SMNode** findInFila(int x, int y) {
        SMNode** pp = &filaHeads[x]; //enlaza las filas
        while (*pp && (*pp)->y_data < y) { //mientras exista "x" y "y" no sobrepase
            pp = &((*pp)->next); //recorre filas
        }
        return pp;
    }
    //función findInCol: recorre la lista hasta encontrar la posición
    SMNode** findInCol(int x, int y) {
        SMNode** pp = &colHeads[y]; //enlaza las columnas
        while (*pp && (*pp)->x_data < x) { //mientras exista "y" y "x" no sobrepase
            pp = &((*pp)->down); //recorre columnas
        }
        return pp;
    }
    //función findSMNode: indica la dirección del nodo mediante punteros
    SMNode* findSMNode (int x, int y) const {
        if (!inRange(x,y)) return nullptr; //caso base: las coordenadas no está en la matriz
        SMNode* p = filaHeads[x];
        while (p && p->y_data < y) { p = p->next; } //recorre
        return (p && p->y_data == y) ? p : nullptr; //si lo encuentra, lo muestra, sino, nullptr
    }
    //función removeSMNode: desconecta un nodo, ya buscado mediante find, en filas y columnas
    void removeSMNode(SMNode** ppFila, SMNode** ppCol) {
        SMNode* paraBorrar = *ppFila;
        *ppFila = paraBorrar->next; //desconecta en la fila
        *ppCol = paraBorrar->down; //desconecta en la columna
        delete paraBorrar;
    }

public:
    SMatrix() {
        for (int i{0}; i < filas; i++) filaHeads[i] = nullptr;
        for (int j{0}; j < columnas; j++) colHeads[j] = nullptr;
    }
    ~SMatrix() {
        for (int i{0}; i < filas; i++) {
            SMNode* p = filaHeads[i];
            while (p) {
                SMNode* nxt = p->next;
                delete p;
                p = nxt;
            }
        }
    }
    //función get
    int getSMNode(int x, int y) const {
        SMNode* n = findSMNode(x, y);
        return n ? n->valor : 0;
    }
    //función set
    bool setSMNode(int x, int y, int val) {
        if (!inRange(x, y)) return false; //caso base: coords fuera de la matriz
        //1ro: ubicar
        SMNode** ppFila = findInFila(x,y);
        SMNode** ppCol = findInCol(x,y);

        if (*ppFila && (*ppFila)->y_data == y) { //el nodo si existe
            if (val == 0) { removeSMNode(ppFila, ppCol); } //elimina
            else { (*ppFila)->valor = val; }
        }
        else if (val != 0) { //el nodo no existe, crear e insertar
            SMNode* n = new SMNode(val, x, y);
            n->next = *ppFila; *ppFila = n; //conectamos en fila
            n->down = *ppCol; *ppCol = n; //conectamos en columna
        }
        return true;
    }
    //Función printPorFilas
    void printPorFilas() const {
        for (int x{0}; x < filas; x++) {
            SMNode* p = filaHeads[x];
            for (int y{0}; y < columnas; y++) {
                if (p && p->y_data == y) {
                    std::cout << p->valor << " ";
                    p = p->next;
                }
                else {
                    std::cout << 0 << " ";
                }
            }
            std::cout << std::endl;
        }
    }
    //Función printPorColumnas
    void printPorColumnas() const {
        for (int y{0}; y < columnas; y++) {
            SMNode* p = colHeads[y];
            for (int x{0}; x < filas; x++) {
                if (p && p->x_data == x) {
                    std::cout << p->valor << " ";
                    p = p->down;
                }
                else {
                    std::cout << 0 << " ";
                }
            }
            std::cout << std::endl;
        }
    }
};

int main() {
    SMatrix<4,5> matrix;
    matrix.setSMNode(0,3,10);
    matrix.setSMNode(1,1,7);
    matrix.setSMNode(2,4,15);
    matrix.setSMNode(3,0,5);
    matrix.setSMNode(0,1,20);
    matrix.setSMNode(1,2,3);
    std::cout << "Matriz inicial (printPorFilas): " << std::endl;
    matrix.printPorFilas();
    std::cout << "Matriz inicial (printPorColumnas): " << std::endl;
    matrix.printPorColumnas();

    std::cout << "\nGet(2,4): " << matrix.getSMNode(2,4) << std::endl;
    std::cout << "\nGet(3,3): " << matrix.getSMNode(3,3) << std::endl;

    matrix.setSMNode(2, 4, 20);
    std::cout << "\nSet(2,4,20)... " << std::endl;
    matrix.printPorColumnas();

    matrix.setSMNode(1, 1, 0);
    std::cout << "\nSet(1,1,0)... " << std::endl;
    matrix.printPorColumnas();
    return 0;
}


