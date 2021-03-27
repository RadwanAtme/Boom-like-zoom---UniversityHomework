#ifndef HW1_WET_LINKEDLIST_H
#define HW1_WET_LINKEDLIST_H

#include "library.h"

template <class T, class N>
class listElement {
    T* AvlTree;
    int Time;
    listElement *next;
    listElement* prev;
public:
    ~listElement();
    explicit listElement(int Time,listElement *next, listElement *prev);
    listElement(const T *Tree, const int &Time, listElement *next,listElement *prev);
    bool operator==(listElement& element)const;
    bool operator<(listElement& element)const;
    void removeNode(N& node);
    int getListElementID()const ;
    listElement*& getNext();
    listElement*& getPrev();
    T* getAvltree();

};

template <class T, class N>
class LinkedList{
    listElement<T,N>* head;
public:
    LinkedList<T,N>();
    ~LinkedList();
    StatusType addNode(N &node,int time,listElement<T,N>*& Element);
    StatusType addWatchTime(listElement<T,N>*& Element,N& node,int time);
    StatusType GetMostViewedClasses(int numOfClasses, int *courses, int *classes, int& index);
     listElement<T,N>& getHead() const ;
};

template <class T, class N>
listElement<T,N>::listElement( int Time,listElement *next, listElement *prev): AvlTree(new T()) ,Time(Time), next(next),prev(prev) {}
template <class T, class N>
listElement<T,N>::listElement(const T *Tree, const int &Time, listElement *next, listElement *prev): AvlTree(Tree), Time(Time), next(next),prev(prev){}
template <class T, class N>
listElement<T,N>::~listElement() {
    delete this->AvlTree;
}
template <class T, class N>
listElement<T,N>*& listElement<T,N>::getNext(){
    return this->next;
}
template <class T, class N>
listElement<T,N>*& listElement<T,N>::getPrev(){
    return this->prev;
}
template <class T, class N>
int listElement<T,N>::getListElementID()const{
    return this->Time;
}
template <class T, class N>
T * listElement<T,N>::getAvltree()  {
    return this->AvlTree;
}
template <class T, class N>
bool listElement<T,N>::operator==(listElement &element) const {
    return this->Time == element.getListElementID();
}
template <class T, class N>
bool listElement<T,N>::operator<(listElement &element) const {
    return this->Time < element.getListElementID();
}
template <class T, class N>
void listElement<T,N>::removeNode(N &node){
    this->AvlTree->remove(node);
    if(this->AvlTree->treeIsEmpty()){
        listElement<T,N>* temp2= this->getNext();
        listElement<T,N>* temp1= this->getPrev();
        temp1->getNext()=temp2;
        temp2->getPrev()=temp1;
        delete this;
    }
}


//LinkedList functions..
template <class T, class N>
LinkedList<T,N>::LinkedList() : head(new listElement<T,N>(-1, nullptr, nullptr)){
    head->getNext() = head;
    head->getPrev() = head;
}

template <class T, class N>
LinkedList<T,N>::~LinkedList() {
    listElement<T,N>* temp= head;
    listElement<T,N>* temp2= head;
    temp=temp->getNext();
    while(temp!= head){
        temp2 = temp->getNext();
        delete temp;
        temp = temp2;
    }
    delete head;
}

template <class T, class N>
listElement<T,N>& LinkedList<T,N>::getHead() const {
    return this->head;
}

template <class T, class N>
StatusType LinkedList<T,N>::addNode(N &node, int time,listElement<T,N>*& Element) {
    listElement<T,N>* temp= head;
    temp=temp->getNext();
    while(temp!=head){
        if(temp->getListElementID()==time){
            temp->getAvltree()->addNode(node);//tree is not finish**
            Element = temp;
            return SUCCESS;
        }
        if(temp->getListElementID()>time){
            listElement<T,N>* NewElement=new listElement<T,N>(time,temp,temp->getPrev());//check malloc allocation error//
            NewElement->getAvltree()->addNode(node);//tree is not finished..
            listElement<T,N>* prev= temp->getPrev();
            prev->getNext()=NewElement;
            temp->getPrev()=NewElement;
            Element = NewElement;
            return SUCCESS;
        }
        temp=temp->getNext();
    }
    listElement<T,N>* NewElement=new listElement<T,N>(time,temp,temp->getPrev());//check malloc allocation error//
    NewElement->getAvltree()->addNode(node);//tree is not finished..
    listElement<T,N>* prev0= temp->getPrev();
    prev0->getNext()=NewElement;
    temp->getPrev()=NewElement;
    Element = NewElement;
    return SUCCESS;
}

template <class T, class N>
StatusType LinkedList<T,N>::addWatchTime(listElement<T, N>*& Element, N &node, int time) {
    int tempTime=0;
    listElement<T, N> *temp=Element;
    listElement<T, N> *temp1=Element;
    tempTime=temp->getListElementID();
    temp1=temp->getNext();
    temp->removeNode(node);
    tempTime=tempTime+time;
    while (temp1->getListElementID()<tempTime){
        if(temp1->getNext()==head){
            listElement<T,N>* NewElement=new listElement<T,N>(tempTime,temp1->getNext(),temp1);
            NewElement->getAvltree()->addNode(node);//tree is not finished..
            listElement<T,N>* prev0= temp1;
            prev0->getNext()=NewElement;
            head->getPrev()=NewElement;
            Element=NewElement;
            return SUCCESS;
        }
        temp1=temp1->getNext();
    }
    if(temp1->getListElementID()==tempTime){
        temp1->getAvltree()->addNode(node);//tree is not finish**
        Element=temp1;
        return SUCCESS;
    }
    listElement<T,N>* NewElement=new listElement<T,N>(tempTime,temp1,temp1->getPrev());
    NewElement->getAvltree()->addNode(node);//tree is not finished..
    listElement<T,N>* prev0= temp1->getPrev();
    prev0->getNext()=NewElement;
    temp1->getPrev()=NewElement;
    Element=NewElement;
    return SUCCESS;
}

template <class T, class N>
StatusType LinkedList<T,N>::GetMostViewedClasses(int numOfClasses, int *courses, int *classes, int& index) {
    listElement<T,N>* temp= head->getPrev();
    while(numOfClasses!=index){
        temp->getAvltree()->getMostViewedClasses(numOfClasses,courses,classes,index);//tree is not ***
        temp=temp->getPrev();
        if(temp==head){
            break;
        }
    }
    return SUCCESS;
}
 #endif //HW1_WET_LINKEDLIST_H



