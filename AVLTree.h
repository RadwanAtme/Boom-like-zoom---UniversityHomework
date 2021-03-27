#ifndef HW1_WET_AVLTREE_H
#define HW1_WET_AVLTREE_H

#include "library.h"

/* Generic AVLTree (the node is generic)
 * Includes: node
 *           pointer to the head
 *           pointer to the smallest element
 *
 * make the exceptions throw the AlloactionError somehow - maybe we can use std::exception allocation error
 *
 * Node has to have: operator==, operator<, constructor(int,int),getCourseID(),getClassID(),getBF,getHeight,
 *                      getLeft,getRight,getParent
 */

// Functions: dont forget to use the template before every function,
template<class Node>
class AVLTree{
protected:
    Node* head;
    Node* smallest_element;
public:
    AVLTree<Node>();
    AVLTree<Node>(int courseID,int numOfClasses);
    ~AVLTree<Node>();
    Node* sortedArrayToAVLTree(int courseID,int* array,int start,int end);
    Node* find(Node& node)const;
    bool NodeIsIn(Node& node)const;
    StatusType addNode(Node& node);
    StatusType addNode(Node* node);
    void remove(Node& node);
    void removeNode(Node *node);
    void getMostViewedClasses(int numOfClasses,int* courses,int* classes,int& index)const;
    void ReverseInOrder(Node* node,int numOfClasses, int *courses, int *classes, int& index,bool go_left,bool go_parent)const;

    void updateHeight(Node *node);
    void updateNodeHeight(Node *node);
    void updateHeights(Node* node,Node* son);
    void rotateTree(Node *node);
    void rotateLL(Node *node);
    void rotateRR(Node *node);
    void rotateLR(Node *node);
    void rotateRL(Node *node);

    void postOrderDelete(Node* node);
    bool treeIsEmpty()const;
    Node* getHead()const;
    Node* getSmallestElement();
    void updateNodeBF(Node* node);

    void getMostViewedZeroClasses(Node* tree_node,int numOfClasses, int *courses, int *classes, int& index,
                                    bool go_left,bool go_parent) const;



    };
template<class Node>
class AVLTreeNode: public AVLTree<Node>{
    int courseID;
    AVLTreeNode<Node>* parent;
    AVLTreeNode<Node>* left_son;
    AVLTreeNode<Node>* right_son;
    int height;
    int balance_factor;
public:
    AVLTreeNode<Node>(int courseID,int numOfClasses):AVLTree<Node>(courseID,numOfClasses),
    courseID(courseID),parent(nullptr),
    left_son(nullptr),right_son(nullptr),height(0),balance_factor(0){}
    AVLTreeNode<Node>(AVLTreeNode& tree_node);
    ~AVLTreeNode<Node>()= default;

    bool operator==(AVLTreeNode<Node>& node)const;
    bool operator<(AVLTreeNode<Node>& node)const;
    AVLTreeNode<Node>*& getRight();
    AVLTreeNode<Node>*& getLeft();
    AVLTreeNode<Node>*& getParent();
    int& getHeight();
    int& getBF();
    int getCourseID();



};


template<class Node>
AVLTree<Node>::AVLTree():head(nullptr),smallest_element(nullptr){}
template<class Node>
AVLTree<Node>::AVLTree(int courseID, int numOfClasses):head(nullptr),smallest_element(nullptr){
    if(numOfClasses==0){
        return ;
    }else{
        int* array = new int[numOfClasses];
        for(int i=0;i<numOfClasses;i++){
            array[i] = i;
        }
        head = this->sortedArrayToAVLTree(courseID,array,0,numOfClasses-1);
        Node node(courseID,0);
        smallest_element = find(node);
        delete[] array;
    }
}
template<class Node>
AVLTree<Node>::~AVLTree() {
    Node* node=head;
    postOrderDelete(node);
    head= nullptr;
    smallest_element= nullptr;
}
template<class Node>
void AVLTree<Node>::postOrderDelete(Node* node) {
    if(node== nullptr){
        return;
    }
    postOrderDelete(node->getLeft());
    postOrderDelete(node->getRight());
    delete node;
}
template<class Node>
Node* AVLTree<Node>::sortedArrayToAVLTree(int courseID,int* array,int start,int end){
    if(start>end){
        return nullptr;
    }else{
        int mid = (start+end)/2;
        Node* root = new Node(courseID,array[mid]);
        root->getLeft() = this->sortedArrayToAVLTree(courseID,array,start,mid-1);
        root->getRight() = this->sortedArrayToAVLTree(courseID,array,mid+1,end);
        if(root->getLeft()!= nullptr){
            root->getLeft()->getParent() = root;
        }
        if(root->getRight()!= nullptr){
            root->getRight()->getParent() = root;
        }
        return root;
    }
}
template<class Node>
Node* AVLTree<Node>::find(Node &node) const{
    if (!head) {
        return nullptr;
    }else{
        Node* temp = head;
        while (temp) {
            if (*temp==node) {
                return temp;
            }
            if (*temp<node) {
                temp = temp->getRight();
            } else
                temp = temp->getLeft();
        }
        return nullptr;
    }

}
template<class Node>
bool AVLTree<Node>::NodeIsIn(Node &node) const{
    return (this->find(node)!= nullptr);
}
template<class Node>
Node* AVLTree<Node>::getSmallestElement() {
    Node* node = smallest_element;
    while((node)&&(node->getLeft()!= nullptr)){node=node->getLeft();}
    return node;
}
template<class Node>
StatusType AVLTree<Node>::addNode(Node* node){
    if(NodeIsIn(*node)){
        return FAILURE;
    }else{
        Node* temp = head;
        Node* parent = nullptr;
        int ToAdd = 0;
        while (temp) {
            parent = temp;
            if (*temp<*node) {
                temp = temp->getRight();
                ToAdd = 1;
            } else{
                temp = temp->getLeft();
                ToAdd = -1;
            }
        }
        switch (ToAdd) {
            case 1:
                parent->getRight() = node;
                node->getParent() = parent;
                break;
            case 0:
                head = node;
                smallest_element = node;
                break;
            case -1:
                parent->getLeft() = node;
                if(parent == smallest_element){
                    smallest_element = node;
                }
                node->getParent() = parent;
                break;
        }
        this->updateHeight(parent);
        return SUCCESS;
    }
}

template<class Node>
StatusType AVLTree<Node>::addNode(Node& node) {
    if(NodeIsIn(node)){
        return FAILURE;
    }else{
        Node* temp = head;
        Node* parent = nullptr;
        int ToAdd = 0;
        while (temp) {
            parent = temp;
            if (*temp<node) {
                temp = temp->getRight();
                ToAdd = 1;
            } else{
                temp = temp->getLeft();
                ToAdd = -1;
            }
        }
        Node* new_node= new Node(node);
        switch (ToAdd) {
            case 1:
                parent->getRight() = new_node;
                new_node->getParent() = parent;
                break;
            case 0:
                head = new_node;
                smallest_element = new_node;
                break;
            case -1:
                parent->getLeft() = new_node;
                if(smallest_element == parent){
                    smallest_element = new_node;
                }
                new_node->getParent() = parent;
                break;
        }
        this->updateHeight(parent);
        return SUCCESS;
    }
}
template<class Node>
void AVLTree<Node>::remove(Node& node) {
    Node* deleteNode = find(node);
    if(deleteNode == smallest_element){
        if(smallest_element->getRight()!= nullptr){
            smallest_element = smallest_element->getRight();
        }else{
            smallest_element = smallest_element->getParent();
        }
    }
    if (!deleteNode->getLeft() || !deleteNode->getRight()) {
        removeNode(deleteNode);
        return;
    }else{
        Node *temp = deleteNode->getRight();
        while (temp->getLeft()) {
            temp = temp->getLeft();
        }
        if (deleteNode == head) {
            head = temp;
        } else {
            if (deleteNode->getParent()->getRight() == deleteNode) {
                deleteNode->getParent()->getRight() = temp;
            } else {
                deleteNode->getParent()->getLeft() = temp;
            }
        }
        if (temp->getRight()) {
            temp->getRight()->getParent() = deleteNode;
        }
        if (deleteNode->getLeft()) {
            deleteNode->getLeft()->getParent ()= temp;
        }
        if (deleteNode->getRight() != temp) {
            deleteNode->getRight()->getParent() = temp;
            if (temp->getParent()->getLeft() == temp) {
                temp->getParent()->getLeft() = deleteNode;
            } else {
                temp->getParent()->getRight() = deleteNode;
            }
            Node *temp2 = deleteNode->getParent();
            deleteNode->getParent() = temp->getParent();
            temp->getParent() = temp2;
            temp2 = deleteNode->getRight();
            deleteNode->getRight()= temp->getRight();
            temp->getRight() = temp2;
            temp2 = deleteNode->getLeft();
            deleteNode->getLeft() = temp->getLeft();
            temp->getLeft() = temp2;
        } else {
            deleteNode->getRight() = temp->getRight();
            temp->getRight() = deleteNode;
            temp->getParent() = deleteNode->getParent();
            deleteNode->getParent() = temp;
            temp->getLeft() = deleteNode->getLeft();
            deleteNode->getLeft() = nullptr;
        }
        removeNode(deleteNode);
    }
}
template<class Node>
void AVLTree<Node>::removeNode(Node *node) {
    if (!node) {
        return;
    }
    Node *parent = node->getParent();
    if (!node->getRight() && !node->getLeft()) {
        if (parent) {
            if (node == parent->getRight()) {
                node->getParent()->getRight() = nullptr;
            } else if (node == parent->getLeft()) {
                node->getParent()->getLeft() = nullptr;
            }
        } else {
            if (node == head) {
                head = nullptr;
            }
        }
        delete node;
        updateHeight(parent);
        return;
    }
    if (node->getRight()) {
        node->getRight()->getParent() = parent;
        if (node == head) {
            head = node->getRight();
        } else if (parent->getRight() == node) {
            parent->getRight() = node->getRight();
        } else if (parent->getLeft() == node) {
            parent->getLeft() = node->getRight();
        }
        delete node;
        if (parent) {
            updateHeight(parent->getRight());
        }
        return;
    }
    if (node->getLeft()) {
        node->getLeft()->getParent() = parent;
        if (node == head) {
            head = node->getLeft();
        } else if (parent->getRight() == node) {
            parent->getRight() = node->getLeft();
        } else if (parent->getLeft() == node) {
            parent->getLeft() = node->getLeft();
        }
        delete node;
        if (parent) {
            updateHeight(parent->getLeft());
        }
        return;
    }
}
template<class Node>
void AVLTree<Node>::updateHeight(Node *node) {
    Node *temp = node;
    while (temp) {
        updateNodeHeight(temp);
        updateNodeBF(temp);
        if (temp->getBF() > 1 || temp->getBF() < -1) {
            rotateTree(temp);
        }
        if((temp==smallest_element)&&(temp->getLeft()!= nullptr)){smallest_element = temp->getLeft();}
        temp = temp->getParent();
    }
}

template<class Node>
void AVLTree<Node>::updateNodeBF(Node* node) {
    int rightH = node->getRight() == nullptr ? 0 : node->getRight()->getHeight();
    int leftH = node->getLeft() == nullptr ? 0 : node->getLeft()->getHeight();
    node->getBF() = leftH - rightH;
}

template<class Node>
void AVLTree<Node>::updateNodeHeight(Node *node) {
    if (!node){
        return;
    }else{
        int right_height = node->getRight() == nullptr ? 0 : node->getRight()->getHeight();
        int left_height = node->getLeft() == nullptr ? 0 : node->getLeft()->getHeight();
        int height = (right_height > left_height) ? right_height : left_height;
        node->getHeight() = height + 1;
    }
}
template<class Node>
void AVLTree<Node>::rotateTree(Node *node) {
    switch (node->getBF()) {
        case 2: {
            if (node->getLeft()->getBF() >= 0) {
                rotateLL(node);
            } else if (node->getLeft()->getBF() == -1) {
                rotateLR(node);
            }
        }
            break;
        case -2: {
            if (node->getRight()->getBF() <= 0) {
                rotateRR(node);
            } else if (node->getRight()->getBF() == 1) {
                rotateRL(node);
            }
        }
            break;
        default:return;
    }
}
template<class Node>
void AVLTree<Node>::rotateLL(Node *node) {
    Node *son = node->getLeft();
    Node *parent = node->getParent();
    Node *rightSon = son->getRight();
    node->getLeft() = rightSon;
    if (rightSon) {
        rightSon->getParent() = node;
    }
    son->getRight() = node;
    node->getParent() = son;
    node->getLeft() = rightSon;


    if (parent && parent->getRight() == node) {
        parent->getRight() = son;
        son->getParent() = parent;
    } else if (parent && parent->getLeft()== node) {
        parent->getLeft() = son;
        son->getParent() = parent;
    } else if (node == head) {
        head = son;
        son->getParent() = nullptr;
    }
    updateHeights(node,son);

}
template<class Node>
void AVLTree<Node>::rotateRR(Node *node) {
    Node *son = node->getRight();
    Node *parent = node->getParent();
    Node *leftSon = son->getLeft();
    node->getRight() = leftSon;
    if (leftSon) {
        leftSon->getParent() = node;
    }
    son->getLeft() = node;
    node->getParent() = son;
    node->getRight() = leftSon;

    if (parent && parent->getRight() == node) {
        parent->getRight() = son;
        son->getParent() = parent;
    } else if (parent && parent->getLeft() == node) {
        parent->getLeft() = son;
        son->getParent() = parent;
    } else if (node == head) {
        head = son;
        son->getParent() = nullptr;
    }
    updateHeights(node,son);
}
template<class Node>
void AVLTree<Node>::rotateLR(Node *node) {
    rotateRR(node->getLeft());
    rotateLL(node);
}
template<class Node>
void AVLTree<Node>::rotateRL(Node *node) {
    rotateLL(node->getRight());
    rotateRR(node);
}
template<class Node>
void AVLTree<Node>::updateHeights(Node *node, Node *son) {
    updateNodeHeight(son);
    updateNodeBF(son);
    updateNodeHeight(node);
    updateNodeBF(node);
}
template<class Node>
void AVLTree<Node>::getMostViewedClasses(int numOfClasses, int *courses, int *classes, int& index) const{
    Node* node = smallest_element;
    while((node)&&(node->getLeft()!= nullptr)){node=node->getLeft();}
    ReverseInOrder(node,numOfClasses,courses,classes,index,0,1);
}

template<class Node>
void AVLTree<Node>::ReverseInOrder(Node* node,int numOfClasses, int *courses, int *classes, int& index,
                                             bool go_left,bool go_parent) const {
    if (!node || index == numOfClasses) {
        return;
    } else {
        if (go_left) {
            ReverseInOrder(node->getLeft(), numOfClasses, courses, classes, index, 1, 0);
            if (index == numOfClasses) { return; }
        }
        courses[index] = node->getCourseID();
        classes[index] = node->getClassID();
        index++;
        ReverseInOrder(node->getRight(), numOfClasses, courses, classes, index, 1, 0);
        if (index == numOfClasses) { return; }
        if (go_parent) {
            ReverseInOrder(node->getParent(), numOfClasses, courses, classes, index, 0, 1);
            if (index == numOfClasses) { return; }
        }
    }
}

template<class Node>
bool AVLTree<Node>::treeIsEmpty() const {
    return !head;
}
template<class Node>
Node* AVLTree<Node>::getHead() const{
    return head;
}
template<class Node>
bool AVLTreeNode<Node>::operator==(AVLTreeNode<Node>& node) const{
    return courseID==node.getCourseID();
}
template<class Node>
bool AVLTreeNode<Node>::operator<(AVLTreeNode<Node>& node) const{
    return courseID<node.getCourseID();
}
template<class Node>
AVLTreeNode<Node> * & AVLTreeNode<Node>::getLeft() {
    return left_son;
}
template<class Node>
AVLTreeNode<Node> * & AVLTreeNode<Node>::getRight() {
    return right_son;
}
template<class Node>
int& AVLTreeNode<Node>::getHeight() {
    return height;
}
template<class Node>
int& AVLTreeNode<Node>::getBF() {
    return balance_factor;
}
template<class Node>
AVLTreeNode<Node>*& AVLTreeNode<Node>::getParent() {
    return parent;
}
template<class Node>
int AVLTreeNode<Node>::getCourseID() {
    return courseID;
}

template<class Node>//here we have AVLTree<AVLTreeNode>
void AVLTree<Node>::getMostViewedZeroClasses(Node* tree_node,int numOfClasses, int *courses, int *classes, int& index,
                                                     bool go_left,bool go_parent) const {
    if (!tree_node || index == numOfClasses) {
        return;
    } else {
        if(go_left){
            getMostViewedZeroClasses(tree_node->getLeft(), numOfClasses, courses, classes, index,1,0);
            if (index == numOfClasses) { return; }
        }
        if (tree_node->getSmallestElement() != nullptr) {
            tree_node->getMostViewedClasses(numOfClasses, courses, classes, index);
            if (index == numOfClasses) { return; }
        }
        getMostViewedZeroClasses(tree_node->getRight(), numOfClasses, courses, classes, index,1,0);
        if (index == numOfClasses) { return; }
        if(go_parent){
            getMostViewedZeroClasses(tree_node->getParent(), numOfClasses, courses, classes, index,0,1);
            if (index == numOfClasses) { return; }
        }
    }
}
#endif //HW1_WET_AVLTREE_H
