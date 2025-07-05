#include <iostream>
#include <queue>
#include <vector>

int main() {
    //Max-heap de int
    std::priority_queue<int> colaMax;
    colaMax.push(10);
    colaMax.push(5);
    colaMax.push(20);
    std::cout << "Max-heap top: " << colaMax.top() << std::endl;
    //eliminar
    colaMax.pop();
    std::cout << "Tras pop, top: " << colaMax.top() << std::endl;
    //Min-heap con greater
    std::priority_queue<int, std::vector<int>, std::greater<>> colaMin;
    colaMin.push(10);
    colaMin.push(5);
    colaMin.push(20);
    std::cout << "Min-heap top: " << colaMin.top() << std::endl;

    return 0;
}