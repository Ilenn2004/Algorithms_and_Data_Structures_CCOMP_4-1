#include <iostream>
#include <queue>
//Cuando push, el valor ingresa ya ordenado
//Cuando pop, se elimina el menor elemento de la cola (front)
//Se ordena de menor a mayor
//Si se repiten, igualmente se agrega
//Solución: se conserva el metodo circular de las colas, controlando el tamaño

class CSortedQueue
{
public:
    void pushx(int x); //RETO: insertar los valores acorde al orden
    void popx(); //trabaja con frontx para ubicar y eliminar el menor elemento de la cola
    int frontx(); //puntero al primer elemento de la cola
    void remx(int x); //buscar todas las existencias del mismo numero y eliminarlas
    void printx();
    std::queue<int> q;
};

void CSortedQueue::pushx(int x)
{
    if (q.empty()) { q.push(x); return; } //si es la primera vez insertando
    int tamaño = q.size();
    bool insertado{false};

    for (int t{0}; t < tamaño; t++) { //se repite la cantidad de veces == tamaño
        int actual = q.front(); //guarda el primero
        q.pop(); //elimina el primero de la cola
        if (!insertado && x < actual) { //ubica el lugar donde insertar según el orden
            q.push(x); //agrega a la cola al final
            insertado = true;
        }
        q.push(actual); //agrega el actual al final
    }
    //y si no se inserta nada porque x es el dato mayor, entonces se agrega al final de todo
    if (!insertado) { q.push(x); }
}

void CSortedQueue::popx()
{
    if (q.empty() == false){ q.pop(); }
    else { std::cout << "La cola está vacía" << std::endl; }
}

int CSortedQueue::frontx()
{
    if (q.empty() == false){ return q.front(); }
    else { std::cout << "La cola está vacía" << std::endl; }
}

void CSortedQueue::remx(int x)
{
    if (q.empty()) { std::cout << "La cola está vacía" << std::endl; return; } //si es la primera vez insertando

    int tamaño = q.size();
    for (int t{0}; t < tamaño; t++) { //se repite la cantidad de veces == tamaño
        int actual = q.front(); //guarda el primero
        q.pop(); //elimina el primero de la cola
        if (actual != x) { //valida si es diferente del valor
            q.push(actual); //agrega a la cola al final
        }
        //si se ubica el número que se quiere eliminar, entonces ya no se pushea,
        // dado que todos los elementos se poppean
    }
}

void CSortedQueue::printx()
{
    if (q.empty()) { std::cout << "La cola está vacía" << std::endl; return; }
    std::cout << "Cola: ";
    for (int t{0}; t < q.size(); t++) {
        int actual = q.front();
        q.pop();
        std::cout << actual << " ";
        q.push(actual);
    }
}

int main()
{
    CSortedQueue sq;
    sq.pushx(40); sq.printx(); std::cout << std::endl;
    sq.pushx(23); sq.printx(); std::cout << std::endl;
    sq.pushx(51); sq.printx(); std::cout << std::endl;
    sq.pushx(12); sq.printx(); std::cout << std::endl;
    sq.pushx(30); sq.printx(); std::cout << std::endl;
    sq.pushx(5);  sq.printx(); std::cout << std::endl;
    sq.pushx(40); sq.printx(); std::cout << std::endl;
    sq.pushx(18); sq.printx(); std::cout << std::endl;

    sq.remx(40);  sq.printx(); std::cout << std::endl;
    sq.remx(23);  sq.printx(); std::cout << std::endl;
    sq.remx(51);  sq.printx(); std::cout << std::endl;
    sq.remx(12);  sq.printx(); std::cout << std::endl;
    sq.remx(5);  sq.printx(); std::cout << std::endl;

    std::cout<<"\nfront => "<<sq.frontx(); sq.popx();
    std::cout<<"\nfront => "<<sq.frontx(); sq.popx(); std::cout << std::endl;
    sq.printx();
}

