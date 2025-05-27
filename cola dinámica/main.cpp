#include <iostream>
using namespace std;
//COLA DINÁMICA
//5 valores en cada nodo y connector el final con el inicio

template <class T>
class Cola {
private:
    struct cNode {
        int valores[5];
        cNode* next;
    };
    cNode* head;
    cNode* tail;
public:
    Cola(){
        head = nullptr;
        tail = nullptr;
    }
    ~Cola(){
        cNode* tmp = head;
        while(tmp){
            cNode* paraBorrar = tmp;
            tmp = tmp->next;
            delete paraBorrar;
        }
    }
    void insertar(T val);
    T eliminar();
    void print();
    bool vaciaOno();
};

template <class T>
void Cola<T>::insertar(T val){

}