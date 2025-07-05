//BinTree AVL.cpp
#include <iostream>

struct Menor { bool operator() (int x, int y){ return x < y; } };

//Nodo + altura para AVL
struct AVLNode {
    int valor, altura;
    AVLNode* nodos[2];

    AVLNode(int val) {
        valor = val;
        nodos[0] = nullptr; //hijo izq
        nodos[1] = nullptr; //hijo der
        altura = 1; //altura del nodo: hoja = 1
    }
};

//Arbol AVL (BST auto-balanceado)
template<class T>
class AVLTree {
private:
    AVLNode* root; //raiz del arbol
    T toCompare; //functor para detectar menor

    //FUNCIONES AUX
    //get la altura de un nodo
    int getAltura(AVLNode* nodo) {
        if (!nodo) return 0; //caso base
        return nodo->altura;
    }

    //get el factor de balance: altura(izq) - altura(der)
    //Si el resultado está fuera de [-1, 1], está desbalanceado
    int getBalance(AVLNode* nodo) {
        if (!nodo) return 0; //caso base
        return getAltura(nodo->nodos[0]) - getAltura(nodo->nodos[1]);
    }

    //actualizar la altura, comparando el valor mayor entre
    void actualizarAltura(AVLNode* nodo) {
        nodo->altura = 1 + std::max(getAltura(nodo->nodos[0]), getAltura(nodo->nodos[1]));
    }

    //ROTACIONES
    //CASO LL
    AVLNode* DERrotar(AVLNode* y) {
        AVLNode* x = y->nodos[0]; //hijo izq de y
        AVLNode* T2 = x->nodos[1]; //temporal arbol intermedio

        //1ro: x asciende, y desciende a la derecha
        x->nodos[1] = y;
        y->nodos[0] = T2;

        //2do: actualizar alturas
        actualizarAltura(y);
        actualizarAltura(x);

        //3ro: x es la nueva raiz
        return x;
    }

    //CASO RR
    AVLNode* IZQrotar(AVLNode* x) {
        AVLNode* y = x->nodos[1]; //hijo der de x
        AVLNode* T2 = y->nodos[0]; //temporal arbol intermedio

        //1ro: y asciende, x desciende a la izquierda
        y->nodos[0] = x;
        x->nodos[1] = T2;

        //2do: actualizar alturas
        actualizarAltura(x);
        actualizarAltura(y);

        //3ro: y es la nueva raiz
        return y;
    }

    //FUNCIÓN DE FIND RECURSIVO
    bool ParaFind(AVLNode* nodo, int val) {
        if (!nodo) return false; //caso base: no encontrado
        if (val == nodo->valor) return true; //encontrado
        //avanzar por el arbol
        if (toCompare(val, nodo->valor))
            return ParaFind(nodo->nodos[0], val); //a la izq
        else
            return ParaFind(nodo->nodos[1], val); //a la der
    }

    //FUNCIÓN DE INSERT RECURSIVA + BALANCEO
    AVLNode* ParaInsert(AVLNode* nodo, int val) {
        //1ro: Inserción BST normal
        if (!nodo) return new AVLNode(val); //caso base
        if(toCompare(val, nodo->valor))
            nodo->nodos[0] = ParaInsert(nodo->nodos[0], val);
        else if (toCompare(nodo->valor, val))
            nodo->nodos[1] = ParaInsert(nodo->nodos[1], val);
        else return nodo; //no duplicados

        //2do: actualizar altura
        actualizarAltura(nodo);

        //3ro: comprobar balance
        int balance = getBalance(nodo);

        //4to: cubrir los 4 casos de rotación
        //Caso IZQ-IZQ (LL)
        if (balance > 1 && toCompare(val, nodo->nodos[0]->valor))
            return DERrotar(nodo);

        //Caso DER-DER (RR)
        if (balance < -1 && toCompare(nodo->nodos[1]->valor, val))
            return IZQrotar(nodo);

        //Caso IZQ-DER (LR)
        if (balance > 1 && toCompare(nodo->nodos[0]->valor, val)) {
            nodo->nodos[0] = IZQrotar(nodo->nodos[0]);
            return DERrotar(nodo);
        }
        //CASO DER-IZQ (RL)
        if (balance < -1 && toCompare(val, nodo->nodos[1]->valor)) {
            nodo->nodos[1] = DERrotar(nodo->nodos[1]);
            return IZQrotar(nodo);
        }
        //extra: si ya está balanceado, se devuelve el mismo nodo
        return nodo;
    }

    //FUNCIÓN PARA HALLAR EL NODO DE MENOR VALOR
    AVLNode* minValorNode(AVLNode* nodo) { //hallar el nodo de menor valor
        AVLNode* actual = nodo;
        while (actual->nodos[0]) { //va hasta el nodo izq del último nivel
            actual = actual->nodos[0];
        }
        return actual;
    }

    //FUNCIÓN DE DELETE RECURSIVA + BALANCEO
    AVLNode* ParaDelete(AVLNode* nodo, int val) {
        if (!nodo) return nodo; //caso base
        //Delete BST normal
        if (toCompare(val, nodo->valor)) {
            nodo->nodos[0] = ParaDelete(nodo->nodos[0], val);
        }
        else if (toCompare(nodo->valor, val)) {
            nodo->nodos[1] = ParaDelete(nodo->nodos[1], val);
        }
        else { //nodo encontrado
            if (!nodo->nodos[0] || !nodo->nodos[1]) {
                //si tiene 0 o 1 hijo
                AVLNode* tmp = nodo->nodos[0] ? nodo->nodos[0] : nodo->nodos[1];
                if (!tmp) { tmp = nodo; nodo = nullptr; } //case 0 hijos
                else { *nodo = *tmp; } //case 1 hijo
                delete tmp;
            }
            else { //case 2 hijos: copiar sucesor in-order
                AVLNode* tmp = minValorNode(nodo->nodos[1]);
                nodo->valor = tmp->valor;
                nodo->nodos[1] = ParaDelete(nodo->nodos[1], tmp->valor);
            }
        }
        if (!nodo) return nodo; //si quedó vacío
        //actualizar altura y balance
        actualizarAltura(nodo);
        int balance = getBalance(nodo);

        //cubrir los 4 casos de rotación
        //Caso IZQ-IZQ (LL)
        if (balance > 1 && getBalance(nodo->nodos[0]) >= 0)
            return DERrotar(nodo);

        //Caso DER-DER (RR)
        if (balance < -1 && getBalance(nodo->nodos[1]) <= 0)
            return IZQrotar(nodo);

        //Caso IZQ-DER (LR)
        if (balance > 1 && getBalance(nodo->nodos[0]) < 0) {
            nodo->nodos[0] = IZQrotar(nodo->nodos[0]);
            return DERrotar(nodo);
        }
        //CASO DER-IZQ (RL)
        if (balance < -1 && getBalance(nodo->nodos[1]) > 0) {
            nodo->nodos[1] = DERrotar(nodo->nodos[1]);
            return IZQrotar(nodo);
        }
        //extra: si ya está balanceado, se devuelve el mismo nodo
        return nodo;
    }

    //RECORRIDO IN-ORDER
    void InOrder(AVLNode* nodo) {
        if (!nodo) return; //caso base
        InOrder(nodo->nodos[0]);
        std::cout << nodo->valor << " - ";
        InOrder(nodo->nodos[1]);
    }

public:
    AVLTree() { root = nullptr; }

    //Uso al exterior
    //Insert + balancea
    void Insert(int val) {
        root = ParaInsert(root, val);
    }
    //Delete + balancea
    void Delete(int val) {
        root = ParaDelete(root, val);
    }
    //Find
    bool Find(int val) {
        return ParaFind(root, val);
    }
    //Mostrar
    void printInOrder() {
        InOrder(root); std::cout << std::endl;
    }
};

int main() {
    AVLTree<Menor> arbolEquilibrado;
    // Insert
    arbolEquilibrado.Insert(30);
    arbolEquilibrado.Insert(20);
    arbolEquilibrado.Insert(10);
    arbolEquilibrado.Insert(40);
    arbolEquilibrado.Insert(50);
    arbolEquilibrado.Insert(25);
    arbolEquilibrado.Insert(45);
    std::cout << "InOrder AVLTree: ";
    arbolEquilibrado.printInOrder();
    // Find
    std::cout << "Find 25? " << (arbolEquilibrado.Find(25) ? "si" : "no") << std::endl;
    std::cout << "Find 99? " << (arbolEquilibrado.Find(99) ? "si" : "no") << std::endl;
    // Borramos y reimprimimos
    arbolEquilibrado.Delete(20);
    std::cout << "InOrder tras borrar 20: ";
    arbolEquilibrado.printInOrder();      // 10 25 30 40 50

    return 0;
}
