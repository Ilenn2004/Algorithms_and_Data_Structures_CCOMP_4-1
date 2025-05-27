#include <iostream>
#include <array>     // library of array and its functions
#include <cstddef>   // library of size_t type
#include <chrono>
#include <random>
#include <iomanip>
using namespace std;
using namespace chrono;

//1ero: versión base
void bubble_sort_tranqui(int arr[], size_t size) {
    for(size_t i = 0; i < size - 1; i++) {
        for(size_t j = 0; j < size - 1 - i; j++) {
            if(arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

void bubble_sort_tranqui_ptr(int *arr, size_t tam){
    int* end = arr + tam;

    for(int* i = arr; i < end - 1; i++){
        for(int* j = arr; j < end - 1 - (i - arr); j++){
            if(*j > *(j + 1)){
                swap(*j, *(j + 1));
            }
        }
    }
}

//2do: versión con polimorfismo
struct Sort {
    virtual void sort(int arr[], size_t size) = 0;
};
struct bubbleSort : Sort {
    void sort(int arr[], size_t size) override{
        for(size_t i = 0; i < size - 1; i++) {
            for(size_t j = 0; j < size - 1 - i; j++) {
                if(arr[j] > arr[j + 1]) {
                    swap(arr[j], arr[j + 1]);
                }
            }
        }
    }
};

//3ro: versión con puntero a función
bool mayor(int a, int b){return a > b;}
bool menor(int a, int b){return a > b;}

void bubble_sort_ptr_func(int arr[], size_t size, bool (*func)(int, int)) {
    for(size_t i = 0; i < size - 1; i++) {
        for(size_t j = 0; j < size - 1 - i; j++) {
            if(func(arr[j], arr[j + 1])) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

//4to: versión con functores
struct mayorque{ bool operator()(int a, int b){return a > b;} };

template <class Compara>
struct bubble_sort_funct{
    void operator()(int arr[], size_t size, Compara opera){
        for(size_t i = 0; i < size - 1; i++) {
            for(size_t j = 0; j < size - 1 - i; j++) {
                if(opera(arr[j], arr[j + 1])) {
                    swap(arr[j], arr[j + 1]);
                }
            }
        }
    }
};

int main(){
    /* TEST DE PRUEBA
    constexpr size_t arrSize{5};
    array<int, arrSize> a1 {7, 12, 9, 11, 3};

    cout << "Array un-ordered: ";
    for (int item : a1){ cout << item << " "; }

     cout << "\nArray ordered: ";
    for (int item : a1){ cout << item << " "; }
     */

    //1era forma:
    //bubble_sort_tranqui(a1.data(), a1.size());
    //2da forma:
    //bubbleSort b2; b2.sort(a1.data(), a1.size());
    //3ra forma:
    //bubble_sort_ptr_func(a1.data(), a1.size(), mayor);
    //4ta forma:
    //mayorque compara1;
    //bubble_sort_funct<mayorque> ordena;
    //ordena(a1.data(), a1.size(), compara1);

    //TIEMPOS DE EJECUCIÓN
    constexpr size_t cant_datos{400};
    array<int, cant_datos> data;

    random_device rand;
    mt19937 gen(rand());
    uniform_int_distribution<> distrib(1, 10000);
    for (int i{0}; i < cant_datos; i++){
        data[i] = distrib(gen);
    }

    array<int, cant_datos> data2{data};

    //Inicia
    auto inicio{high_resolution_clock::now()};
    //1era forma:
    bubble_sort_tranqui(data2.data(), data2.size());
    //2da forma:
    //bubbleSort b2; b2.sort(data2.data(), data2.size());
    //3ra forma:
    //bubble_sort_ptr_func(data2.data(), data2.size(), mayor);
    //4ta forma:
    //mayorque compara1;
    //bubble_sort_funct<mayorque> ordena;
    //ordena(data2.data(), data2.size(), compara1);

    auto fin{high_resolution_clock::now()};
    auto duracion{duration_cast<milliseconds>(fin - inicio)};
    cout << "Tiempo de ejecucion con " << cant_datos << ": ";
    cout << duracion.count() << "ms\n";






    return 0;
}
