#include <iostream>
#include <vector>
#include <thread>
#include <random>
#include <algorithm>

//función SortPart: ordenar y partir
void SortPart(std::vector<int>& v, size_t inicio, size_t fin) {
    std::sort(v.begin() + inicio, v.begin() + fin);
}

int main() {
    //poblamos un vector con los datos
    size_t N = 1048576; // ≈1 048 576
    std::vector<int> v(N);
    std::mt19937_64 eng{std::random_device{}()};
    std::uniform_int_distribution<int> dist(0, 1'000'000);
    for (auto& x : v) x = dist(eng);
    //decidimos la cant de hilos
    unsigned int n_hilos = std::thread::hardware_concurrency();
    if (n_hilos == 0) n_hilos = 4; //en caso no encuentre, lo forzamos
    std::vector<std::thread> hilos;
    hilos.reserve(n_hilos); //se reservan la cant de hilos
    //dividimos el vector en num_threads y ordenamos en paralelo
    size_t parte = (N + n_hilos - 1) / n_hilos;
    for (int h{0}; h < n_hilos; h++) {
        size_t inicio = h * parte;
        size_t fin = std::min(inicio + parte, N);
        hilos.emplace_back(SortPart, std::ref(v), inicio, fin);
    }
    for (auto& h : hilos) if(h.joinable()) h.join();
    //fusionamos los resultados con merges sucesivos, combinando de dos en dos
    size_t n_intervalos = n_hilos;
    size_t intervalo_size = parte;
    while (n_intervalos > 1) {
        size_t merged = 0;
        for (size_t i{0}; i + 1 < n_intervalos; i = i + 2) {
            size_t izq_inicio = i * intervalo_size;
            size_t medio = std::min(izq_inicio + intervalo_size, N);
            size_t der_fin = std::min(medio + intervalo_size, N);
            std::inplace_merge(v.begin() + izq_inicio, v.begin() + medio, v.begin() + der_fin);
            merged++;
        }
        //si hay in intervalo sin pareja, se opera al final
        if (n_intervalos % 2 == 1) { merged++; }
        n_intervalos = merged;
        intervalo_size = intervalo_size * 2;
    }
    //mostramos los primeros 10 elementos ordenados
    std::cout << "10 elem. ordenados: ";
    for (size_t i{0}; i < 10 && i < v.size(); i++) std::cout << v[i] << " ";
    std::cout << std::endl;
    return 0;
}