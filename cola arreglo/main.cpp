#include <iostream>
using namespace std;
//Cola con arreglo, se hace circular para reutilizar aquellas posiciones que hemos "eliminado" dentro del arreglo
//Cola FIFO(first-in, first-out): agrega al final (tail) y quita al inicio (head)

class Cola {
private:
    int arreglo[10];
    int *head, *tail;
    int cantidad;
public:
    Cola();
    void push(int valor);
    int pop();
    void print();
    bool vacía();
    bool llena();
};

Cola::Cola() {
    head = arreglo;
    tail = arreglo;
    cantidad = 0;
}

bool Cola::vacía() { return cantidad == 0; }

bool Cola::llena() { return cantidad == 10; }

void Cola::push(int valor) {
    if (llena()) { cout << "cola llena\n"; return; } //si está llena, fin
    //sino,
    *tail = valor;
    tail++; //tail avanza
    //cola "circular"
    if (tail == arreglo + 10) { tail = arreglo; }
    //para reutilizar aquellas posiciones "liberadas" que fueron poppeadas previamente
    // y reubicar tail

    //actualizamos cantidad
    cantidad++;
}

int Cola::pop() {
    if (vacía()) { cout << "cola vacía\n"; return -1; } //si está vacía, fin
    //sino,
    int valor = *head;
    head++; //head avanza
    //cola "circular"
    if (head == arreglo + 10) { head = arreglo; }
    //para indicar aquellas posiciones para ser "eliminadas", reubicando head
    //actualizamos cantidad
    cantidad--;
    return valor;
}

void Cola::print() {
    if (vacía()) { vacía(); return; }
    //if (llena()) { llena(); return; }

    cout << "Cola: ";
    int *tmp = head; //para no modificar nada
    for (int i{0}; i < cantidad; i++){
        cout << *tmp << " ; "; tmp++;
        if (tmp == arreglo + 10) { tmp = arreglo; } //cola "circular",
        // como con el pop, configura las posiciones ya impresas
        // y dado que, utiliza a head, al terminar, lo reubica en su posición original
    }
    cout << endl;
}

int main(){
    Cola c1;
    c1.pop();
    c1.push(4);
    c1.push(5);
    c1.push(2);
    c1.push(34);
    c1.print();
    c1.pop();
    c1.print();
    c1.push(1);
    c1.print();
}
