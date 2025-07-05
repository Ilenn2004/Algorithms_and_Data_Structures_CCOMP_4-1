#include <iostream>
#include <vector>
//Functor de comparación
struct Menor { bool operator() (int x, int y) { return x < y; } };

//HEAP IMPLEMENTADO CON STD::VECTOR
template<class T>
class HeapVector {
    std::vector<int> data;
    T compara_menor;

    //heapifyUp: flota el elemento en índice i
    void heapifyUp(size_t i) {
        //heapify up mientras que no sea la raíz y el padre sea "menor" que
        while (i > 0) {
            size_t tmp = (i-1) / 2;
            if (!compara_menor(data[tmp], data[i])) break;
            std::swap(data[tmp], data[i]);
            i = tmp;
        }
    }

    //heapifyDown: hunde el elemento en indice i
    void heapifyDown(size_t i) {
        size_t n = data.size();
        while (true) {
            size_t izq = 2*i + 1, der = 2*i + 2, mejor = i;
            //busca el hijo más grande
            if (izq < n && compara_menor(data[mejor], data[izq])) mejor = izq;
            if (der < n && compara_menor(data[mejor], data[der])) mejor = der;
            if (mejor == i) break;
            std::swap(data[i], data[mejor]);
            i = mejor;
        }
    }

public:
    //Inserto valor y lo heapifyUp hasta restaurar heap
    void Push(int val) {
        data.push_back(val);
        heapifyUp(data.size() - 1);
    }
    //Extrae el máximo y lo heapifyDown restaurando heap
    bool Extract (int& sale) {
        if (data.empty()) return false; //caso base: heap vacío
        sale = data[0]; //extrae
        data[0] = data.back(); //lo lleva al final
        data.pop_back(); //lo elimina
        if (!data.empty()) heapifyDown(0); //si no está vacío, restaura heap
        return true;
    }
    //Muestra el tope del heap
    int getPeek() const {
        if (data.empty()) std::cout << "Heap vacío"; return NULL; //caso base
        return data[0];
    }
    //Tamaño del heap
    size_t getSize() const { return data.size(); }
    //Verifica si está vacío
    bool ifEmpty() const { return data.empty(); }
    //Imprime el heap, formato array
    void printArr() const {
        for (int elem : data) std::cout << elem << " ";
        std::cout << std::endl;
    }
};

int main() {
    HeapVector<Menor> heapV;
    heapV.Push(30);
    heapV.Push(20);
    heapV.Push(40);
    heapV.Push(10);
    heapV.Push(25);
    heapV.Push(35);
    heapV.Push(50);
    std::cout << "heap Vector tras push consecutivos: " << std::endl;
    heapV.printArr();
    std::cout << "Peek (max): " << heapV.getPeek() << std::endl;
    std::cout << "Aplicando Extract en orden: " << std::endl;
    while (!heapV.ifEmpty()) {
        int val;
        heapV.Extract(val);
        std::cout << val << " ";
    }
    std::cout << std::endl << "Empty? " << (heapV.ifEmpty() ? "si" : "no") << std::endl;

    return 0;
}