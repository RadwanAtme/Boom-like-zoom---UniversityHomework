
#ifndef HW1DS_SERVER_H
#define HW1DS_SERVER_H

#include <stdlib.h>


using namespace std;

template<typename T, class K>
class Tree {
public:
    class Node;

    int TSize;
    Node *head;

    Tree(int TSize=0):TSize(TSize),head(NULL){}

    ~Tree() = default;

    void updateHeightAux(Node *node);

    Node *find(const K &key) const;

    T *insert(const T &data, const K &key);

    void updateHeight(Node *node, Node *&head);

    void updateBF(Node *node);

    void rotateSwitch(Node *node, Node *&head);

    void rotateRL(Node *node, Node *&head);

    void rotateLL(Node *node, Node *&head);

    void rotateRR(Node *node, Node *&head);

    void rotateLR(Node *node, Node *&head);

    void removeAux(Node *node, Node *&head);

    void remove(Node *deleteNode, Node *&head);

    bool remove(const K &key);

    void clearTree();
};


template<typename T, class K>
typename Tree<T, K>::Node *Tree<T, K>::find(const K &key) const {
    if (!head) {
        return NULL;
    }
    Node *tmp = head;
    while (tmp) {
        if (key == tmp->key) {
            return tmp;
        }
        if (key > tmp->key) {
            tmp = tmp->right;
        } else
            tmp = tmp->left;
    }
    return NULL;
}

template<typename T, class K>
class Tree<T, K>::Node {
public:
    int BF;
    int height;
    K key;
    T data;
    Node *right;
    Node *left;
    Node *parent;

    ~Node() = default;
    Node() = default;

    Node(const K &key, const T &data, Node *right, Node *left, Node *parent, int BF, int height) :
            BF(BF), height(height),key(key), data(data), right(right), left(left),
            parent(parent) {}
};



template<typename T, class K>
void Tree<T, K>::clearTree() {
    //postOrderDelete(head);
    TSize = 0;
    head = NULL;
}

template<typename T, class K>
T *Tree<T, K>::insert(const T &data, const K &key) { /////////
    if (find(key)) {
        return NULL;
    }
    Node *tmp = head;
    Node *parent = NULL;
    int ToAdd = 0;
    while (tmp) {
        parent = tmp;
        if (key > tmp->key) {
            tmp = tmp->right;
            ToAdd = 1;
        } else if (key < tmp->key) {
            tmp = tmp->left;
            ToAdd = -1;
        }
    }
    Node *n = new Node(key, data, NULL, NULL, parent, 0, 1);
    switch (ToAdd) {
        case 1:
            parent->right = n;
            break;
        case 0:
            head = n;
            break;
        case -1:
            parent->left = n;
            break;
    }
    updateHeight(parent, this->head);
    TSize++;
    return &n->data;
}


template<typename T, class K>
void Tree<T, K>::updateHeightAux(Node *node) {
    if (!node)
        return;
    int rightH = node->right == NULL ? 0 : node->right->height;
    int leftH = node->left == NULL ? 0 : node->left->height;
    int height = (rightH > leftH) ? rightH : leftH;
    node->height = height + 1;
}


template<typename T, class K>
void Tree<T, K>::updateHeight(Node *node, Node *&head) {
    Node *tmp = node;
    while (tmp) {
        updateHeightAux(tmp);
        updateBF(tmp);
        if (tmp->BF > 1 || tmp->BF < -1) {
            rotateSwitch(tmp, head);
        }
        tmp = tmp->parent;
    }
}

template<typename T, class K>
void Tree<T, K>::updateBF(Node *node) {
    int rightH = node->right == NULL ? 0 : node->right->height;
    int leftH = node->left == NULL ? 0 : node->left->height;
    node->BF = leftH - rightH;
}


template<typename T, class K>
void Tree<T, K>::rotateSwitch(Node *node, Node *&head) {
    switch (node->BF) {
        case 2: {
            if (node->left->BF >= 0) {
                rotateLL(node, head);
            } else if (node->left->BF == -1) {
                rotateLR(node, head);
            }
        }
            break;
        case -2: {
            if (node->right->BF <= 0) {
                rotateRR(node, head);
            } else if (node->right->BF == 1) {
                rotateRL(node, head);
            }
        }
            break;
    }
}


template<typename T, class K>
void Tree<T, K>::rotateLL(Node *node, Node *&head) {
    Node *son = node->left;
    Node *parent = node->parent;
    Node *rightSon = son->right;
    node->left = rightSon;
    if (rightSon) {
        rightSon->parent = node;
    }
    son->right = node;
    node->parent = son;

    if (parent && parent->right == node) {
        parent->right = son;
        son->parent = parent;
    } else if (parent && parent->left == node) {
        parent->left = son;
        son->parent = parent;
    } else if (node == head) {
        head = son;
        son->parent = NULL;
    }

    updateHeightAux(son);
    updateBF(son);
    updateHeightAux(node);
    updateBF(node);
}

template<typename T, class K>
void Tree<T, K>::rotateRR(Node *node, Node *&head) {
    Node *son = node->right;
    Node *parent = node->parent;
    Node *leftSon = son->left;
    node->right = leftSon;
    if (leftSon) {
        leftSon->parent = node;
    }
    son->left = node;
    node->parent = son;

    if (parent && parent->right == node) {
        parent->right = son;
        son->parent = parent;
    } else if (parent && parent->left == node) {
        parent->left = son;
        son->parent = parent;
    } else if (node == head) {
        head = son;
        son->parent = NULL;
    }

    updateHeightAux(son);
    updateBF(son);
    updateHeightAux(node);
    updateBF(node);
}

template<typename T, class K>
void Tree<T, K>::rotateLR(Node *node, Node *&head) {
    rotateRR(node->left, head);
    rotateLL(node, head);
}


template<typename T, class K>
void Tree<T, K>::rotateRL(Node *node, Node *&head) {
    rotateLL(node->right, head);
    rotateRR(node, head);
}


template<typename T, class K>
void Tree<T, K>::remove(Node *deleteNode, Node *&head) {
    if (!deleteNode->left || !deleteNode->right) {
        removeAux(deleteNode, head);
        return;
    }
    Node *tmp = deleteNode->right;
    while (tmp->left) {
        tmp = tmp->left;
    }
    if (deleteNode == head) {
        head = tmp;
    } else {
        if (deleteNode->parent->right == deleteNode) {
            deleteNode->parent->right = tmp;
        } else {
            deleteNode->parent->left = tmp;
        }
    }
    if (tmp->right) {
        tmp->right->parent = deleteNode;
    }
    if (deleteNode->left) {
        deleteNode->left->parent = tmp;
    }
    if (deleteNode->right != tmp) {
        deleteNode->right->parent = tmp;
        if (tmp->parent->left == tmp) {
            tmp->parent->left = deleteNode;
        } else {
            tmp->parent->right = deleteNode;
        }
        Node *tmp1 = deleteNode->parent;
        deleteNode->parent = tmp->parent;
        tmp->parent = tmp1;
        tmp1 = deleteNode->right;
        deleteNode->right = tmp->right;
        tmp->right = tmp1;
        tmp1 = deleteNode->left;
        deleteNode->left = tmp->left;
        tmp->left = tmp1;
    } else {
        deleteNode->right = tmp->right;
        tmp->right = deleteNode;
        tmp->parent = deleteNode->parent;
        deleteNode->parent = tmp;
        tmp->left = deleteNode->left;
        deleteNode->left = NULL;
    }
    removeAux(deleteNode, head);
}

template<typename T, class K>
void Tree<T, K>::removeAux(Node *node, Node *&head) {
    if (!node) {
        return;
    }
    Node *parent = node->parent;
    if (!node->right && !node->left) {
        if (parent) {
            if (node == parent->right) {
                node->parent->right = NULL;
            } else if (node == parent->left) {
                node->parent->left = NULL;
            }
        } else {
            if (node == head) {
                head = NULL;
            }
        }
        delete node;
        updateHeight(parent, head);
        return;
    }
    if (node->right) {
        node->right->parent = parent;
        if (node == head) {
            head = node->right;
        } else if (parent->right == node) {
            parent->right = node->right;
        } else if (parent->left == node) {
            parent->left = node->right;
        }
        delete node;
        if (parent) {
            updateHeight(parent->right, head);
        }
        return;
    }
    if (node->left) {
        node->left->parent = parent;
        if (node == head) {
            head = node->left;
        } else if (parent->right == node) {
            parent->right = node->left;
        } else if (parent->left == node) {
            parent->left = node->left;
        }
        delete node;
        if (parent) {
            updateHeight(parent->left, head);
        }
        return;
    }
}


template<typename T, class K>
bool Tree<T, K>::remove(const K &key) {
    Node *node = find(key);
    if (!node) {
        return false;
    }
    remove(node, head);
    TSize--;
    return true;
}


#endif //HW1DS_SERVER_H
