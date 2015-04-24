#ifndef _VH2015_LIST_H
#define _VH2015_LIST_H
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
template<class T>
class List;
template<class T>
class Node;
template<class T>
class ListIterator {
    unsigned long position = 0;
    List<T> *myList = 0;
    Node<T> *currentNode = 0;
    public:
        ListIterator(List<T> *);
        bool exists();
        T* next();

    unsigned long getPosition();
};
/** @brief Declaracion de la clase nodo
*
*/
template<class T>
class Node {
    friend class List<T>; //Clase amiga lista
private:

    T* data; //Valor almacenado en el nodo
    Node<T>* next; //Node next
    Node<T>* prev; //Node prev
public:
    Node(T *); //Constructor
    Node(T); //Constructor
    ~Node(); //Destructor
    T *getData(); //Devuelve el dato del objeto
    Node<T> *getNextNode(); //Accede al nodo next
    Node<T> *getPrevNode(); //Accede al nodo prev
    void insertAfter(Node<T> *); //Inserta un nodo next
    void insertBefore(Node<T> *); //Inserta un nodo prev
    void freeNext(); //Inserta un nodo next
    void freePrev(); //Inserta un nodo prev
};
/** @brief Declaracion de la clase nodo
*
*/
template<class T>
class List {
private:
    Node<T>* _head; //primer nodo
    Node<T>* _tail; //_tail nodo
    unsigned long l = 0; //longitud
public:
    virtual ListIterator<T> *getIterator();

    List(); //Constructor
    ~List(); //Destructor
    void add(T); //Inserta nodo al inicio
    void append(T); //Inserta nodo al final
    void append(T*); //Inserta nodo al final
    bool deleteNodeByData(T); //Busca nodo y lo borra
    bool deleteNode(unsigned int); //Busca nodo y lo borra
    void deleteAll(); //Borra all
    bool empty(); //True=vacia
    bool swap(unsigned int i, unsigned int j);

    Node<T> *search(T); //Busca dato T
    Node<T> *getNode(int); //Busca getNode
    T* get(int); //Busca getNode
    unsigned long len(); //Devuelve longtiud
    void print(); //Imprime en consola
};


/** @brief Constructor
*
*/
template<class T>
Node<T>::Node(T* v) {
    data = v;
    next = 0;
    prev = 0;
};
/** @brief Constructor
*
*/
template<class T>
Node<T>::Node(T v) {
    data = static_cast<T*>(malloc(sizeof(T)));
    *data = v;
    next = 0;
    prev = 0;
}
/** @brief Destructor
*
*/
template<class T>
Node<T>::~Node() {
    next = 0;
    prev = 0;
};
/** @brief Devuelve el next nodo
*
* @return Node<T>
*/
template<class T>
Node<T>* Node<T>::getNextNode() {
    return next;
};
/** @brief Devuelve el nodo prev
*
* @return Node<T>
*/
template<class T>
Node<T>* Node<T>::getPrevNode() {
    return prev;
};
/** @brief Devuelve el dato contenido
*
* @return T
*/
template<class T>
T* Node<T>::getData() {
    return data;
};
/** @brief Inserta un nodo despues
*
* @param Node<T>*
*/
template<class T>
void Node<T>::insertAfter(Node<T> *n) {
    if(next!=0){
        Node<T> *tmp = next;
        next = n;
        next->insertAfter(tmp);
    }else{
        next=n;
    };
    if(next->getPrevNode()!=this){
        next->insertBefore(this);
    };
};
/** @brief Inserta un nodo antes
*
* @param Node<T>*
*/
template<class T>
void Node<T>::insertBefore(Node<T> *n) {
    if(prev!=0){
        Node<T> *tmp = prev;
        prev = n;
        prev->insertBefore(tmp);
    }else{
        prev=n;
    };
    if(prev->getNextNode()!=this){
        prev->insertAfter(this);
    }
};
/** @brief Vacia nodo antes
*
*/
template<class T>
void Node<T>::freePrev() {
    prev = nullptr;
};
/** @brief Vacia nodo despues
*
*/
template<class T>
void Node<T>::freeNext() {
    next = nullptr;
};
/** @brief Construye la lista
*
*/
template<class T>
List<T>::List() {
    _head=0;
    _tail=0;
};
/** @brief Destruye la lista
*
*/
template<class T>
List<T>::~List() {
    deleteAll();
};
/** @brief Inserta un nodo al inicio
*
* @param Node<T>*
*/
template<class T>
void List<T>::add(T d) {
    Node<T> *n = new Node<T>(d);
    if(_head!=0){
        _head->insertBefore(n);
        _head=n;
    }else{
        _head = n;
        _tail = n;
    };
    l++;
};

/** @brief Inserta un nodo al final
*
* @param Node<T>*
*/
template<class T>
void List<T>::append(T* d) {
    Node<T>* n = static_cast<Node<T>*>(malloc(sizeof(Node<T>)));
    new(n) Node<T>(d);
    if(_tail!=0){
        _tail->insertAfter(n);
        _tail=n;
    }else{
        _head=n;
        _tail=n;
    };
    l++;
};

/** @brief Inserta un nodo al final
*
* @param Node<T>*
*/
template<class T>
void List<T>::append(T d) {
    Node<T>* n = static_cast<Node<T>*>(malloc(sizeof(Node<T>)));
    *n = Node<T>(d);
    if(_tail!=0){
        _tail->insertAfter(n);
        _tail=n;
    }else{
        _head=n;
        _tail=n;
    };
    l++;
};
/** @brief Borra el nodo que contiene el dato d
*
* @param T d
*/
template<class T>
bool List<T>::deleteNodeByData(T d) {
    Node<T> *tmp = _head;
    for(int i=0; i<l; i++){
        if(*tmp->getData()()==d){
            if(i<l-1){
                tmp->getPrevNode()->insertAfter(tmp->getNextNode());
            }
            free(tmp);
            l--;
            return true;
        };
        tmp=tmp->getNextNode();
    };
    return false;
};
/** @brief Borra el nodo de la getNode d
*
* @param int d
*/
template<class T>
bool List<T>::deleteNode(unsigned int d) {
    if(d==0){
        if (l == 1) {
            free(_head);
            _head = _tail = 0;
            l--;
            return true;
        }
        _head=_head->getNextNode();
        (_head->getPrevNode())->~Node();
        free(_head->getPrevNode());
        _head->freePrev();
        l--;
        return true;
    }else if(d==l-1){
        Node<T> *tmp = _tail;
        _tail=_tail->getPrevNode();
        _tail->getNextNode()->~Node();
        free(_tail->getNextNode());
        _tail->freeNext();
        l--;
        return true;
    }else if(d<l){
        Node<T> *tmp = _head;
        for(int i=0; i<d; i++){
            tmp=tmp->getNextNode();
        };
        Node<T> *ant = tmp->getPrevNode();
        Node<T> *sig = tmp->getNextNode();
        tmp->~Node();
        free(tmp);
        ant->freeNext();
        sig->freePrev();
        ant->insertAfter(sig);
        l--;
        return true;
    }else{
        return false;
    };
};
/** @brief Borra todos los nodos
*
*/
template<class T>
void List<T>::deleteAll() {
    for(int i=0; i<l; i++){
        Node<T> *tmp = _head;
        _head=_head->getNextNode();
        free(tmp);
    };
    l=0;
};
/** Revisa si la lista esta o no vacia
*
* @return bool
*/
template<class T>
bool List<T>::empty() {
    return (len()==0);
};
/** Busca un dato y devuelve el nodo que lo contiene
*
* @param T d, dato
* @return Node<T>*
*/
template<class T>
Node<T> *List<T>::search(T d) {
    Node<T> *tmp = _head;
    for(int i=0; i<l; i++){
        if(*tmp->getData()()==d){
            return tmp;
        };
        tmp=tmp->getNextNode();
    };
    return 0;
};
/** Devuelve el nodo en la getNode que se indique
*
* @param int n, getNode
* @return Node<T>*
*/
template<class T>
Node<T> *List<T>::getNode(int n) {
    if(n<l){
        if(n<l/2){
            Node<T> *tmp = _head;
            for(int i=0; i<n; i++){
                tmp=tmp->getNextNode();
            };
            return tmp;
        }else{
            Node<T> *tmp = _tail;
            for(int i=l-1; i>n; i--){
                tmp=tmp->getPrevNode();
            };
            return tmp;
        };
    }else{
        return 0;
    };
};
/** Devuelve el dato en la getNode que se indique
*
* @param int n, getNode
* @return T*
*/
template<class T>
T *List<T>::get(int n) {
    if(n<l){
        if(n<l/2){
            Node<T> *tmp = _head;
            for(int i=0; i<n; i++){
                tmp=tmp->getNextNode();
            };
            return (tmp->getData());
        }else{
            Node<T> *tmp = _tail;
            for(int i=l-1; i>n; i--){
                tmp=tmp->getPrevNode();
            };
            return (tmp->getData());
        };
    }else{
    };
    return nullptr;
};
/** Devuelve la longitud
*
* @return int;
*/
template<class T>
unsigned long List<T>::len() {
    return l;
};
/** @brief Imprime la lista
*
*/
template<class T>
void List<T>::print() {
    if(len()>0){
        Node<T> *tmp = _head;
        for(int i=0; i<len(); i++){
            std::cout << *(tmp->getData()()) << std::endl;
            tmp=tmp->getNextNode();
        };
    }else{
        std::cout<<"La lista esta vacia"<<std::endl;
    };
};
template <class T>
ListIterator<T> *List<T>::getIterator() {
    return new ListIterator<T>(this);
}
template <class T>
bool ListIterator<T>::exists() {
    return position<myList->len();
}
template <class T>
T *ListIterator<T>::next() {
    if (!currentNode)
        currentNode = myList->getNode(0);
    else
        currentNode = currentNode->getNextNode();
    position++;
    return currentNode->getData();
}
template <class T>
ListIterator<T>::ListIterator(List<T> *lista) {
    myList = lista;
}

template<class T>
unsigned long ListIterator<T>::getPosition() {
    return position;
}


template<class T>
bool List<T>::swap(unsigned int i, unsigned int j) {
    if (j > l - 1 || i > l - 1 || i == j)
        return false;

    Node<T> *iNode = getNode(i);
    Node<T> *jNode = getNode(j);

    T *dataI = iNode->data;
    iNode->data = jNode->data;
    jNode->data = dataI;
    return true;


}

#endif
