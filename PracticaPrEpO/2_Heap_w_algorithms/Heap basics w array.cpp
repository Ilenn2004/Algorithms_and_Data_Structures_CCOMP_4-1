//heap_manual_in_array.cpp
#include <iostream>

//FUNCIÓN PARA SIFT-DOWN (MIN-HEAP: PADRE <= HIJOS)
void heapify(int arr[], int n, int i) {
    int menor = i;
    int izq = 2*i + 1; //indice hijo izquierdo
    int der = 2*i + 2; //índice hijo derecho

    //buscar el menor, comparando padre con hijos
    if (izq < n && arr[izq] < arr[menor]) { menor = izq; }
    if (der < n && arr[der] < arr[menor]) { menor = der; }

    //swap si es necesario, intercambiando y seguir bajando
    if (menor != i) {
        std::swap(arr[i], arr[menor]);
        heapify(arr, n, menor); //una vez intercambiado, volver a bajar evaluando
    }
}

//FUNCIÓN PARA CONSTRUIR HEAP
void buildHeap(int arr[], int n) {
    //heapify desde el final del array
    for (int i = n/2 - 1; i >= 0; i--) {
        heapify(arr, n, i);
    }
}

//FUNCIÓN ORDENAMIENTO CON HEAP
void heapSort(int arr[], int n) {
    //1ro: convertir array a min-heap
    buildHeap(arr, n);
    //2do: evaluar cada valor desde el final, llevando el menor hasta el final
    for (int i = n/2 - 1; i >= 0; i--) {
        std::swap(arr[0], arr[i]); //lleva el mínimo al final
        heapify(arr, i, 0); //re-heapify los últimos
    }
}

//FUNCIÓN DE INSERT PARA HEAP
void pushHeap(int arr[], int& n, int nuevo) {
    //inserta al final y "flota" (sift-up)
    arr[n++] = nuevo;
    int i = n - 1;
    while (i && arr[(i-1)/2] > arr[i]) { //recorre el arreglo,
        std::swap(arr[i], arr[(i-1)/2]); //comparando e intercambiando
        i = (i-1)/2;
    }
}
//FUNCIÓN DE DELETE PARA HEAP
bool popHeap(int arr[], int& n, int& out) {
    if (n == 0) return false; //caso base: está vacío
    out = arr[0];
    arr[0] = arr[--n];
    heapify(arr, n, 0);
    return true;
}
//FUNCIÓN PARA OBTENER EL VALOR DEL ROOT, o sea el máximo
int getPeekHeap(int arr[], int n) {
    if (n > 0) return arr[0];
    else { std::cout << "Heap vacío"; return NULL;}
}

int main() {
    int arr[100], n = 0;
    //llenamos
    pushHeap(arr, n, 30);
    pushHeap(arr, n, 35);
    pushHeap(arr, n, 10);
    pushHeap(arr, n, 50);
    //sacamos y mostramos
    int x;
    std::cout << "Heap ordenado: ";
    while (popHeap(arr,n, x)) {
        std::cout << x << " ";
    }
    std::cout << std::endl << "Mostrar el valor del root: ";
    getPeekHeap(arr, n);

    return 0;
}