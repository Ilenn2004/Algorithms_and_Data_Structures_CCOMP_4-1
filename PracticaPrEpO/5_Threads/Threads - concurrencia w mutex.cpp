#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <random>

//Uso de mutex para proteger una suma compartida
std::mutex mtx;
//variable donde se acumulan los resultados parciales
long sumaAcumulada = 0;
//función para sumar los segmentos
void sumaSegmentos(std::vector<int>& data, size_t inicio, size_t fin) {
    long acumuladaTmp = 0;
    for (size_t i{inicio}; i < fin; i++) {
        acumuladaTmp = acumuladaTmp + data[i];
    }
    //Zona crítica
    std::lock_guard<std::mutex> lock(mtx);
    sumaAcumulada = sumaAcumulada + acumuladaTmp;
}

int main() {
    //poblar el vector
    size_t n = 1000000;
    std::vector<int> data(n);
    std::mt19937_64 eng{std::random_device{} ()};
    std::uniform_int_distribution<int> distrib(1,100);
    for (auto& d : data) d = distrib(eng);
    //lanzamos los hilos
    size_t n_hilos = 4;
    std::vector<std::thread> hilos;
    hilos.reserve(n_hilos);
    size_t part = (n + n_hilos - 1) / n_hilos;

    for (size_t t{0}; t < n_hilos; t++) {
        size_t inicio = t * part;
        size_t fin = std::min(inicio + part, n);
        hilos.emplace_back(sumaSegmentos, std::ref(data), inicio, fin);
    }
    //esperar a que terminen
    for (std::thread& h : hilos) if (h.joinable()) h.join(); //juntar las respuestas
    //mostrar resultado global
    std::cout << "Suma total: " << sumaAcumulada << std::endl;
    return 0;
}
