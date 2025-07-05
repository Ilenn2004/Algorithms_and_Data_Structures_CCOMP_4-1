//BinTree - basics.cpp
#include <iostream>
#include <stack>
#include <queue>
//Binary Search Tree (BST) - Arbol Binario de B�squeda

struct Menor { bool operator() (int x, int y){ return x < y; } };

struct BinNode {
    int valor;
    BinNode* nodos[2];
    BinNode(int v) {
        valor = v;
        nodos[0] = nullptr; //hijo izq
        nodos[1] = nullptr; //hijo der
    }
};

template<class T>
class BinTree {
private:
    BinNode* root;
    T toCompare;
public:
    BinTree() { root = nullptr; }
    ~BinTree() {};
    //m�todos propios
    BinNode* getRoot(){ return root; }

	//M�TODOS BASE
    bool Find(int, BinNode**&);//ubica el nodo con el valor int indicado y si no lo encuentra, apunta donde deber�a estar
    BinNode** FindToRep(int, BinNode**); //ubica al nodo mayor de los menores
    bool Insert(int);
    bool Delete(int);

    //RECORRIDO w recursividad
    void PreOrder(BinNode*);
    void PostOrder(BinNode*);
    void InOrder(BinNode*);
    //RECORRIDO w STACK
    void PreOrderStack(BinNode*);
    void PostOrderStack(BinNode*);
    void InOrderStack(BinNode*);
    // RECORRIDO byLevels w QUEUE
    void byLevelsQueue(BinNode*);
};

//MÉTODOS BASE
template<class T>
bool BinTree<T>::Find(int val, BinNode**& ptr_busca) { //busca hasta llegar al fondo
    for (ptr_busca = &root; *ptr_busca && (*ptr_busca)->valor != val; ptr_busca = &((*ptr_busca)->nodos[toCompare((*ptr_busca)->valor, val)]));
    return (*ptr_busca != nullptr);
}

template<class T>
BinNode** BinTree<T>::FindToRep(int val, BinNode** ptr_busca) { //1� izq, luego der,der,der,...
    ptr_busca = &((*ptr_busca)->nodos[0]);
    while (*ptr_busca && (*ptr_busca)->nodos[1]){
        ptr_busca = &((*ptr_busca)->nodos[1]);
    }
    //for (ptr_busca = &((*ptr_busca)->nodos[0]); *ptr_busca && (*ptr_busca)->nodos[1]; ptr_busca = &((*ptr_busca)->nodos[toCompare((*ptr_busca)->valor, val)]));
    return ptr_busca; //ubica nodo izq
}

template<class T>
bool BinTree<T>::Insert(int val) {
    BinNode** p;
    if (Find(val, p)) return false; //si lo encuentra, ya no
    *p = new BinNode(val); //si no lo encuentra, si
    return true;
}

template<class T>
bool BinTree<T>::Delete(int val) {
    BinNode** p;
    if (!Find(val, p)) return false; //si no lo encuentra, fin

    if ((*p)->nodos[0] && (*p)->nodos[1]) { //caso tiene los 2 hijos
        BinNode** alt = FindToRep(val, p); //encuentra al mayor de los hijos, para REPLACE IT
        (*p)->valor = (*alt)->valor; //copia el valor del menor al de alt
        p = alt; //re-apunta al mayor de los menores, donde ahora se encuentra el duplicado, para ser borrado
    }
    //si sólo tiene un hijo
    //se elimina el nodo
    BinNode* tmp = *p; //guardamos la dirección para borrar
    *p = (*p)->nodos[(*p)->nodos[1] != nullptr]; //re-apuntamos al hijo no nulo, si 0 -> hijo izq, si 1-> hijo der
    delete tmp;
    return true;
}

//RECORRIDOS RECURSIVOS
template<class T>
void BinTree<T>::PreOrder(BinNode* nodo) { //PRE-ORDER: nodo > izquierda > derecha
    if (!nodo) return; //si llega al final, todo acaba
    std::cout << nodo->valor << " - ";
    PreOrder(nodo->nodos[0]);
    PreOrder(nodo->nodos[1]);
}

template<class T>
void BinTree<T>::PostOrder(BinNode* nodo) { //POST-ORDER: izquierda > derecha > nodo
    if (!nodo) return; //si llega al final, fin
    PostOrder(nodo->nodos[0]);
    PostOrder(nodo->nodos[1]);
    std::cout << nodo->valor << " - ";
}

template<class T>
void BinTree<T>::InOrder(BinNode* nodo) { //IN-ORDER: izquierda > nodo > derecha
    if (!nodo) return; //si llega al final, fin
    InOrder(nodo->nodos[0]);
    std::cout << nodo->valor << " - ";
    InOrder(nodo->nodos[1]);
}

//RECORRIDOS CON STACK
template<class T>
void BinTree<T>::PreOrderStack(BinNode* nodo_inicio) { //PRE-ORDER: nodo > izquierda > derecha
    if (!nodo_inicio) return; // Caso base: árbol vacío

    std::stack<BinNode*> pila;
    pila.push(nodo_inicio);

    while (!pila.empty()) {
        BinNode* actual = pila.top(); pila.pop();
        std::cout << actual->valor << " - ";

        // Empujar primero el hijo derecho y luego el izquierdo,
        // para que el izquierdo se procese antes (por la naturaleza LIFO de la pila).
        if (actual->nodos[1]) pila.push(actual->nodos[1]);
        if (actual->nodos[0]) pila.push(actual->nodos[0]);
    }
}

template<class T>
void BinTree<T>::PostOrderStack(BinNode* nodo_inicio) { //POST-ORDER: izquierda > derecha > nodo
    if (!nodo_inicio) return; // Caso base: árbol vacío

    std::stack<BinNode*> pila1, pila2;
    pila1.push(nodo_inicio);

    // Primera fase: llenar pila2 en orden postorden inverso
    while (!pila1.empty()) {
        BinNode* actual = pila1.top(); pila1.pop();
        pila2.push(actual);

        // Almacenar los hijos en el orden inverso al postorden
        if (actual->nodos[0]) pila1.push(actual->nodos[0]);
        if (actual->nodos[1]) pila1.push(actual->nodos[1]);
    }

    // Segunda fase: imprimir los nodos desde la pila2
    while (!pila2.empty()) {
        std::cout << pila2.top()->valor << " - ";
        pila2.pop();
    }
}

template<class T>
void BinTree<T>::InOrderStack(BinNode* nodo_inicio) { //IN-ORDER: izquierda > nodo > derecha
    if (!nodo_inicio) return; // Caso base: árbol vacío

    std::stack<BinNode*> pila;
    BinNode* actual = nodo_inicio;

    while (actual != nullptr || !pila.empty()) {
        // Paso 1: bajar al hijo izquierdo guardando el camino
        while (actual != nullptr) {
            pila.push(actual);
            actual = actual->nodos[0];
        }

        // Paso 2: procesar nodo actual (de la cima)
        actual = pila.top(); pila.pop();
        std::cout << actual->valor << " - ";

        // Paso 3: cambiar al hijo derecho
        actual = actual->nodos[1];
    }
}

//PRINT POR LEVELS CON QUEUE A MODO DE BFS (Breadth First Search)
template<class T>
void BinTree<T>::byLevelsQueue(BinNode* nodo_inicio){
    if (!nodo_inicio) return; // caso base: arbol vacío

    std::queue<BinNode*> cola;
    cola.push(nodo_inicio);

    while (!cola.empty()) {
        int cantidad_nodos = cola.size(); //cantidad de nodos en ese nivel
        //Procesar nodos del nivel
        while (cantidad_nodos > 0) {
            BinNode* actual = cola.front(); cola.pop();
            std::cout << actual->valor << " ";
            cantidad_nodos--;
            //"Encolamos" a los hijos, si existen
            if (actual->nodos[0]) cola.push(actual->nodos[0]); //hijo derecho
            if (actual->nodos[1]) cola.push(actual->nodos[1]); //hijo izquierdo
        }
        std::cout << std::endl; //fin del nivel actual
    }
}

int main(){

    BinTree<Menor> arbol1;
	arbol1.Insert(10);
	arbol1.Insert(5);
	arbol1.Insert(15);
    arbol1.Insert(7);
    arbol1.Insert(3);
    arbol1.Insert(12);
    arbol1.Insert(14);
    arbol1.Insert(11);
    arbol1.Insert(9);

    std::cout << "-------Recorrido PreOrder (nodo > izquierda > derecha) -------" << std::endl;
    std::cout << "Con Recursividad: ";
	arbol1.PreOrder(arbol1.getRoot());
    std::cout << std::endl << "Con Pila        : ";
    arbol1.PreOrderStack(arbol1.getRoot());
    std::cout << std::endl;

    std::cout << "-------Recorrido PostOrder (izquierda > derecha > nodo)-------" << std::endl;
    std::cout << "Con Recursividad: ";
    arbol1.PostOrder(arbol1.getRoot());
    std::cout << std::endl << "Con Pila        : ";
    arbol1.PostOrderStack(arbol1.getRoot());
    std::cout << std::endl;

    std::cout << "-------Recorrido InOrder (izquierda > nodo > derecha) --------" << std::endl;
    std::cout << "Con Recursividad: ";
    arbol1.InOrder(arbol1.getRoot());
    std::cout << std::endl << "Con Pila        : ";
    arbol1.InOrderStack(arbol1.getRoot());
    std::cout << std::endl;

    std::cout << "------Recorrido ByLevels Queue (top->bottom, izq->der)-------" << std::endl;
    arbol1.byLevelsQueue(arbol1.getRoot());



    return 0;
};