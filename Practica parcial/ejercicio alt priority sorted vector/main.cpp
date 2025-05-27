#include <iostream>
#include <vector>
//priority sorted vector

class CSortedVector {
private:
    std::vector<int> v;
public:
    void pushx(int);
    void popx();
    int frontx();
    void remx(int);
    void printx();
};

void CSortedVector::pushx(int x) {
    if (v.empty()) {v.push_back(x); return; }

    //Opción 1: works, like a queue
    /*
    int tamaño = v.size();
    bool insertado{false};
    for (int t{0}; t < tamaño; t++) {
        if (!insertado && v.front() > x) {
            v.push_back(x);
            insertado = true;
        }
        //como una cola, después de evaluar el primer elemento
        v.push_back(v.front()); //se lleva atrás
        v.erase(v.begin()); //se elimina del inicio
    }
    if (!insertado) {
        v.push_back(x);
    }
    */
    //Opción 2: works better
    int counter{0};
    //ubicamos la posición donde debería ir el dato
    while ( counter < v.size() && v[counter] <= x) { counter++; }
    //insertamos el dato
    v.insert(v.begin() + counter, x);
}

void CSortedVector::popx() {
    if (v.empty()) { std::cout << "Vector vacío" << std::endl; return; }
    //se elimina al inicio, o sea el menor
    //Opción 1: works
    /*
    int tamaño = v.size();
    for (int t{0}; t < tamaño - 1; t++) { //desde v[0] hasta v[ultimo-1]
        // se corren los datos desde el 2do hasta el último, una posición adelante
        v[t] = v[t + 1];
        //dado que siempre se poppea el primer dato, sólo corremos todos los datos una posición adelante
    }
    v.pop_back(); //limpiamos el último dato
     */
    //Opción 2: works better
    v.erase(v.begin()); //front devuelve un valor, begin apunta al primer elemento
}

int CSortedVector::frontx() {
    if (v.empty()) { std::cout << "Vector vacío" << std::endl; return -1; }
    else { return v.front(); }
}

void CSortedVector::remx(int x) {
    if (v.empty()) { std::cout << "Vector vacío" << std::endl; return; }

    for (int t{0}; t < v.size(); ){ //controlamos el paso al siguiente elemento y el tamaño irá cambiando,
        //                ^^^^^asi que no puede ser un dato fijo
        if (v[t] == x) { v.erase(v.begin() + t); } //no avanzamos porque el tamaño ha cambiado
        //since begin da la & de v[0], podemos aplicar aritmetica de punteros
        else { t++; }
        //si el dato indicado no es el que estamos buscando, pasamos al siguiente
    }
}

void CSortedVector::printx() {
    if (v.empty()) { std::cout << "Vector vacío" << std::endl; return; }
    std::cout << "Vector: ";
    for (int t{0}; t < v.size(); t++){ std::cout << *(v.begin() + t) << " "; }
}

int main() {
    CSortedVector v1;
    v1.pushx(40); v1.printx(); std::cout << std::endl;

    v1.pushx(23); v1.printx(); std::cout << std::endl;
    v1.pushx(51); v1.printx(); std::cout << std::endl;
    v1.pushx(12); v1.printx(); std::cout << std::endl;
    v1.pushx(30); v1.printx(); std::cout << std::endl;
    v1.pushx(5);  v1.printx(); std::cout << std::endl;
    v1.pushx(40); v1.printx(); std::cout << std::endl;
    v1.pushx(18); v1.printx(); std::cout << std::endl;

    v1.remx(40);  v1.printx(); std::cout << std::endl;
    v1.remx(23);  v1.printx(); std::cout << std::endl;
    v1.remx(51);  v1.printx(); std::cout << std::endl;
    v1.remx(12);  v1.printx(); std::cout << std::endl;
    v1.remx(5);  v1.printx(); std::cout << std::endl;

    std::cout<<"\nfront => "<<v1.frontx(); v1.popx();
    std::cout<<"\nfront => "<<v1.frontx(); v1.popx(); std::cout << std::endl;
    v1.printx();


    return 0;
}