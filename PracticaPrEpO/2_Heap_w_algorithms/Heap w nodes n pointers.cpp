#include <iostream>
#include <queue>
//para insert y delete
#include <vector>
#include <deque>

//Functor para comparación
struct Menor { bool operator() (int x, int y) { return x < y; } };

//Nodos para Heap
struct HeapNode {
    int valor;
    HeapNode* parent;
    HeapNode* hijos[2];
    HeapNode(int val, HeapNode* p = nullptr) {
        valor = val;
        parent = p;
        hijos[0] = nullptr;
        hijos[1] = nullptr;
    }
};

//Clase para heap
template<class T>
class HeapNodes {
private:
    HeapNode* root = nullptr;
    T compara_menor;
    //para insert y delete
    std::vector<HeapNode*> lista_nodos; //esta lista conserva el orden de inserción
    std::deque<HeapNode*> cola_insert; //candidatos con <2 hijos (0 o 1 hijo)


    //Función para heapifyUp: sift-up "flota" para MAX-HEAP
    void heapifyUp(HeapNode* n) {
        while (n->parent && compara_menor(n->parent->valor, n->valor)) {
            std::swap(n->parent->valor, n->valor);
            n = n->parent;
        }
    }
    //Función para heapifyDown: sift-down "se hunde" para MIN-HEAP
    void heapifyDown(HeapNode* n) {
        while (n) {
            HeapNode* mejor = n;
            for (int i{0}; i < 2; i++) {
                if (n->hijos[i] && compara_menor(mejor->valor, n->hijos[i]->valor)) {
                    mejor = n->hijos[i];
                }
            }
            if (mejor == n) break;
            std::swap(n->valor, mejor->valor);
            n = mejor;
        }
    }
    //Print con BFS (Breadth First Search ~ Primera búsqueda en amplitud)
    void BFSprint(HeapNode* n) const {
        if (!n) return; //caso base: está vacío
        std::queue<HeapNode*> q;
        q.push(n);
        while (!q.empty()) {
            HeapNode* actual = q.front(); q.pop();
            std::cout << actual->valor << " - ";
            if (actual->hijos[0]) q.push(actual->hijos[0]);
            if (actual->hijos[1]) q.push(actual->hijos[1]);
        }
        std::cout << std::endl;
    }

public:
    ~HeapNodes() { //liberando HeapNodes
        for (HeapNode* n : lista_nodos) delete n;
    }
    //Función para Insertar desde el public
    void Push(int val) {
        HeapNode* n = new HeapNode(val); //caso base: primer nodo
        if (!root) {
            root = n; //y se ubica en la raiz
        }
        else { //ubica la posición donde insertar con bits
            //1ro: insert parent que será el primer nodo con <2 hijos
            HeapNode* p = cola_insert.front();
            //2do: asociar a izq o der
            if (!p->hijos[0]) p->hijos[0] = n; //si no tiene hijo izq, ahi se asocia
            else { p->hijos[1] = n; } //y sino el otro hijo, der
            n->parent = p; //reconectamos
            //3ro: si se completaron los hijos, lo retira de la lista
            if (p->hijos[0] && p->hijos[1]) cola_insert.pop_front();
        }
        //4to: el nuevo nodo puede ser futuro parent
        cola_insert.push_back(n);
        //5to: lo registra en la lista que lleva los nodos en orden
        lista_nodos.push_back(n);
        //6to: restaurar la propiedad de heap
        heapifyUp(n);
    }
    //Función para Extraer la última posición del heap, a modo de POP
    bool Extract(int& sale) {
        if (lista_nodos.empty()) return false; //caso base: heap vacío
        //1ro: guardar el valor de la raíz
        sale = root->valor;
        //2do: guardar el último nodo
        HeapNode* ultimo = lista_nodos.back();
        lista_nodos.pop_back();

        //si el último nodo es la raíz
        if (ultimo == root) { //el heap quedaría vacío
            delete root; root = nullptr;
            cola_insert.clear();
            return true;
        }

        //3ro: llevar el valor al root
        root->valor = ultimo->valor;
        //4to: desconectar el último de su parent
        HeapNode* p = ultimo->parent;
        if (p->hijos[0] == ultimo) p->hijos[0] = nullptr;
        else { p->hijos[1] = nullptr; }
        //5to: pero si p ya tiene a los 2 hijos, regresa a la lista para evaluar
        if (!p->hijos[0] || !p->hijos[1]) {
            cola_insert.push_front(p);
        }
        delete ultimo;
        //6to: establecer la nueva raíz
        heapifyDown(root);
        return true;
    }
    int getPeek() const { //retorna el valor de la raíz, o sea el máximo
        if (!root) { std::cout << "Heap vacio"; return NULL; } //caso base
        return root->valor;
    }
    //Función para obtener el tamaño del heap
    size_t getSize() const { return lista_nodos.size(); }
    //Función para verificar si el heap está vacío
    bool ifEmpty() const { return lista_nodos.empty(); }
    //Función para imprimir el heap
    void printHeap() const { BFSprint(root); }
};

int main() {
    HeapNodes<Menor> heap1;
    heap1.Push(30);
    heap1.Push(20);
    heap1.Push(40);
    heap1.Push(10);
    heap1.Push(25);
    heap1.Push(35);
    heap1.Push(50);
    heap1.Push(15);
    std::cout << "Visualizar heap por niveles: ";
    heap1.printHeap();
    std::cout << "Ver el root (peek o max): " << heap1.getPeek() << std::endl;
    std::cout << "Empty? " << (heap1.ifEmpty() ? "si" : "no") << std::endl;
    std::cout << "Ver el size: " << heap1.getSize() << std::endl;
    std::cout << std::endl << "Aplicar Extract (extrae en orden), a todo el heap: " << std::endl;
    while (!heap1.ifEmpty()) {
        int salida;
        heap1.Extract(salida);
        std::cout << salida << " - ";
    }
    std::cout << std::endl;
    std::cout << "Verificar: Empty? " << (heap1.ifEmpty() ? "si" : "no") << std::endl;
    std::cout << "Ver el size: " << heap1.getSize() << std::endl;

    return 0;
}