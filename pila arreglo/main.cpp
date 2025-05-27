#include <iostream>
using namespace std;
//Pila con arreglo
//Pila LIFO(last-in, first out): insertamos por el tope y extraemos por el tope

class Pila {
private:
    int arreglo[10];
    int *top;
    int cantidad;
public:
    Pila();
    void push(int valor);
    int pop();
    void print();
    bool vacía();
    bool llena();
};

Pila::Pila() {
    top = arreglo - 1;
    //técnicamente, empieza a apuntar al inicio de arreglo, pero dado que arreglo - 1,
    // no existe entonces está antes del inicio real, realmente está vacío pero conectado
    cantidad = 0;
}

bool Pila::vacía() { return cantidad == 0; }

bool Pila::llena() { return cantidad == 10; }

void Pila::push(int valor) {
    if (llena()) { cout << "pila llena\n"; return; } //si está llena, fin
    //sino,
    top++; //avanza top
    *top = valor; //agrega el valor
    cantidad++; //actualizamos cantidad
    cout << "push " << valor << endl;
}

int Pila::pop() {
    if (vacía()) { cout << "pila vacia\n"; return -1; } //si está vacía, fin
    //sino,
    int valor = *top; //guardamos temporalmente el valor a eliminar
    top--; //retrocede top
    cantidad--; //actualizamos cantidad
    cout << "pop " << valor << endl;
    return valor; //retornamos el valor
}

void Pila::print() {
    if (vacía()) { cout << "pila vacia\n"; return; }
    cout << "Pila: \n";
    for (int *i = top; i >= arreglo; i--){ //vamos del top hasta la base(retrocedemos)
        if (i == top) { cout << *i << " (top) <- ";}
        else { cout << *i << " <- "; }
    }
    cout << endl;
}

int main() {
    Pila p1;
    p1.pop();
    p1.push(3);
    p1.push(6);
    p1.push(9);
    p1.push(10);
    p1.print();
    p1.pop();
    p1.print();
    p1.push(1);
    p1.print();
}
