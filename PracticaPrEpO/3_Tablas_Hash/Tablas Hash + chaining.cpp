#include <iostream>
#include <vector>
#include <list>

//Hash table a modo de vector, compuesto de listas -> un vector de listas
class HashTable {
private:
    size_t bucketConteo; //cantidad total de buckets
    std::vector<std::list<int>> buckets; //vector de buckets

    //función para hash: convierte las claves en un índice de buckets
    size_t hashFunction(int clave) const {
        return static_cast<size_t>(clave) % bucketConteo;
    }

public:
    explicit HashTable(size_t numBuckets) :
    bucketConteo (numBuckets), buckets(numBuckets)
    {}
    //función insert: añade al final
    void insert(int val) {
        size_t idx = hashFunction(val);
        buckets[idx].push_back(val);
    }
    //función find: hasheamos el valor y luego lo buscamos en su bucket
    bool find(int val) const {
        size_t idx = hashFunction(val);
        for (int v : buckets[idx]) {
            if (v == val) { return true; } //sí se encontró
        }
        return false; //no se encontró
    }
    //función erase: elimina la primera ocurrencia del valor
    bool erase(int val) {
        size_t idx = hashFunction(val);
        auto &chain = buckets[idx]; //iterator para recorrer cada bucket
        for (auto it = chain.begin(); it != chain.end(); it++) {
            if (*it == val) {
                chain.erase(it);
                return true;
            }
        }
        return false;
    }
    //función print: visualizar valores
    void display() const {
        std::cout << "Hash Table: " << std::endl;
        for (size_t i = 0; i < bucketConteo; i++) {
            std::cout << "Bucket [" << i << "]: ";
            for (int val : buckets[i]) {
                std::cout << val << " -> ";
            }
            std::cout << "null" << std::endl;
        }
    }
};

int main() {
    int elements[] = {5,10,7,20,40,10};
    size_t n = sizeof(elements) / sizeof(int);

    HashTable ht(7);
    for (size_t i{0}; i < n; i++){
        ht.insert(elements[i]);
    }
    std::cout << "Estado inicial: " << std::endl;
    ht.display();
    std::cout << "Find 17? " << (ht.find(17) ? "si" : "no") << std::endl;
    std::cout << "Find 20? " << (ht.find(20) ? "si" : "no") << std::endl;
    std::cout << "Eliminando 10... " << (ht.erase(10) ? "eliminado" : "no eliminado") << std::endl;
    std::cout << "Estado final: " << std::endl;
    ht.display();
    std::cout << "Find 10? " << (ht.find(10) ? "si" : "no") << std::endl;
    std::cout << "Eliminando 10... " << (ht.erase(10) ? "eliminado" : "no eliminado") << std::endl;
    std::cout << "Find 10? " << (ht.find(10) ? "si" : "no") << std::endl;

    return 0;
}