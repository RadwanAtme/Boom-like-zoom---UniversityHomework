#ifndef HW1_WET_POINTERNODE_H
#define HW1_WET_POINTERNODE_H

template<class ListElement>
class PointerNode{
    int courseID{};
    ListElement** pointerArray;
    int arrayLength;
    PointerNode* parent;
    PointerNode* right_son;
    PointerNode* left_son;
    int height;
    int balance_factor;
public:
    PointerNode(int courseID,int numOfClasses);
    PointerNode(PointerNode& node);
    ~PointerNode();
    int getArrayLength()const;
    ListElement*& operator[](int index);
    void changePointer(void* listElement,int index);
    int getCourseID()const;
    bool operator==(PointerNode<ListElement>& node)const;
    bool operator<(PointerNode<ListElement>& node)const;
    int& getHeight();
    int& getBF();
    PointerNode<ListElement>*& getParent();
    PointerNode<ListElement>*& getRight();
    PointerNode<ListElement>*& getLeft();

};


template<class ListElement>
PointerNode<ListElement>::PointerNode(int courseID, int numOfClasses){
    this->courseID = courseID;
    arrayLength = numOfClasses;
    pointerArray = new ListElement*[arrayLength];
    for(int i=0;i<arrayLength;++i){
        pointerArray[i]= nullptr;
    }
    right_son = nullptr;
    left_son = nullptr;
    height = 0;
    balance_factor = 0;
    parent = nullptr;
}

template<class ListElement>
PointerNode<ListElement>::~PointerNode(){
    delete[] pointerArray;
}

template<class ListElement>
int PointerNode<ListElement>::getArrayLength() const{
    return arrayLength;
}

template<class ListElement>
ListElement*& PointerNode<ListElement>::operator[](int index) {
    return pointerArray[index];
}

template<class ListElement>
int PointerNode<ListElement>::getCourseID() const{
    return courseID;
}

template<class ListElement>
bool PointerNode<ListElement>::operator==(PointerNode<ListElement> &node) const{
    return courseID==node.getCourseID();
}

template<class ListElement>
bool PointerNode<ListElement>::operator<(PointerNode<ListElement> &node) const{
    return courseID<node.getCourseID();
}
template<class ListElement>
int& PointerNode<ListElement>::getHeight() {
    return height;
}

template<class ListElement>
int& PointerNode<ListElement>::getBF() {
    return balance_factor;
}
template<class ListElement>
PointerNode<ListElement>*& PointerNode<ListElement>::getLeft() {
    return left_son;
}
template<class ListElement>
PointerNode<ListElement>*& PointerNode<ListElement>::getRight() {
    return right_son;
}
template<class ListElement>
PointerNode<ListElement>*& PointerNode<ListElement>::getParent() {
    return parent;
}
template<class ListElement>
void PointerNode<ListElement>::changePointer(void* listElement,int index){
    ListElement* listElement1 = static_cast<ListElement*>(listElement);
    pointerArray[index]=listElement1;
}
template<class ListElement>
PointerNode<ListElement>::PointerNode(PointerNode<ListElement> &node) {
    courseID = node.getCourseID();
    height = node.getHeight();
    arrayLength = node.getArrayLength();
    balance_factor=node.getBF();
    parent = nullptr;
    left_son = nullptr;
    right_son = nullptr;
    pointerArray = new ListElement*[arrayLength];
    for(int i=0;i<arrayLength;i++){
        pointerArray[i] = node[i];
    }
}

#endif //HW1_WET_POINTERNODE_H
