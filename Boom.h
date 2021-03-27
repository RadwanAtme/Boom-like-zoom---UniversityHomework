#ifndef HW1_WET_BOOM_H
#define HW1_WET_BOOM_H

#include "AVLTree.h"
#include "LinkedList.h"
#include "TreeNode.h"
#include "PointerNode.h"
#include "library.h"
#include <iostream>
#include <cassert>
//using std::exception;

template<class Tree,class List,class DoubleTree,class Node,class PointerNode,class AVLTreeNode>
class Boom{
    Tree course_tree;
    List viewed_list;
    DoubleTree zero_viewed_tree;
public:
    Boom()= default;
    ~Boom()= default;
    StatusType AddCourse(int courseID, int numOfClasses);
    StatusType removeCourse(int courseID);

    StatusType WatchClass(int courseID, int classID, int time);

    StatusType TimeViewed(int courseID, int classID, int *timeViewed);

    StatusType GetMostViewedClasses(int numOfClasses, int *courses, int *classes);

};

template<class Tree, class List, class DoubleTree, class Node, class PointerNode,class AVLTreeNode>
StatusType Boom<Tree, List, DoubleTree, Node, PointerNode,AVLTreeNode>::AddCourse(int courseID, int numOfClasses) {
    assert(courseID > 0);
    assert(numOfClasses > 0);
    try {
        // fill courseTree
        PointerNode pointer_node(courseID, numOfClasses);
        StatusType checkFail1 = this->course_tree.addNode(pointer_node);
        if (checkFail1 != SUCCESS) {
            return checkFail1;
        }
        // fill ZeroViewedTree
        AVLTreeNode* tree_node = new AVLTreeNode(courseID, numOfClasses);
        StatusType checkFail2 = this->zero_viewed_tree.addNode(tree_node);
        if (checkFail2 != SUCCESS) {
            course_tree.remove(pointer_node);
            return checkFail2;
        }
        return SUCCESS;
    } catch (std::bad_alloc&) {
        return ALLOCATION_ERROR;
    }
}
template<class Tree, class List, class DoubleTree, class Node, class PointerNode,class AVLTreeNode>
StatusType Boom<Tree, List, DoubleTree, Node, PointerNode,AVLTreeNode>::removeCourse(int courseID) {
    assert(courseID > 0);
    try {
        PointerNode temp_node(courseID,0);
        PointerNode* pointer_node = this->course_tree.find(temp_node);
        AVLTreeNode tree_node(courseID,0);
        if(!pointer_node){
            return FAILURE;
        }else{
            for(int i=0;i<pointer_node->getArrayLength();i++){
                Node node(courseID,i);
                if(pointer_node->operator[](i) == nullptr){
                    continue;
                }else{
                    //delete the node that is in the tree_list
                    pointer_node->operator[](i)->getAvltree()->remove(node);
                }
            }
            zero_viewed_tree.remove(tree_node);
            course_tree.remove(temp_node);
            return SUCCESS;
        }
    } catch (std::bad_alloc&){
        return ALLOCATION_ERROR;
    }
}

template<class Tree, class List, class DoubleTree, class Node, class PointerNode,class AVLTreeNode>
StatusType Boom<Tree, List, DoubleTree, Node, PointerNode,AVLTreeNode>::WatchClass(int courseID, int classID, int time) {
    assert(courseID > 0);
    assert(classID > 0);
    assert(time > 0);
    try {
        PointerNode pointer_temp_node(courseID,0);
        PointerNode* pointer_node = this->course_tree.find(pointer_temp_node);
        if (pointer_node == nullptr) {
            return FAILURE;
        }
        if (classID + 1 > pointer_node->getArrayLength()) {
            return INVALID_INPUT;
        }
        Node new_node(courseID, classID);
        if (pointer_node->operator[](classID) == nullptr) {
            AVLTreeNode tree(courseID,0);
            tree.addNode(new_node);
            this->zero_viewed_tree.find(tree)->remove(new_node);
            this->viewed_list.addNode(new_node, time,pointer_node->operator[](classID));
        } else {
            this->viewed_list.addWatchTime(pointer_node->operator[](classID), new_node, time);
        }
        return SUCCESS;
    }catch (std::bad_alloc&) {
        return ALLOCATION_ERROR;
    }
}

template<class Tree, class List, class DoubleTree, class Node, class PointerNode,class AVLTreeNode>
StatusType Boom<Tree, List, DoubleTree, Node, PointerNode,AVLTreeNode>::TimeViewed(int courseID, int classID, int *timeViewed) {
    assert(courseID > 0);
    assert(classID >= 0);
    try {
        PointerNode pointer_temp_node(courseID,0);
        PointerNode* pointer_node = this->course_tree.find(pointer_temp_node);
        if (pointer_node == nullptr) {
            return FAILURE;
        }
        if(classID + 1 > pointer_node->getArrayLength()){
            return INVALID_INPUT;
        }
        if (pointer_node->operator[](classID) == nullptr) {
            *timeViewed = 0;
            return SUCCESS;
        }else {
            *timeViewed = pointer_node->operator[](classID)->getListElementID();
            return SUCCESS;
        }
    }catch (std::bad_alloc&) {
        return ALLOCATION_ERROR;
    }
}

template<class Tree, class List, class DoubleTree, class Node, class PointerNode,class AVLTreeNode>
StatusType Boom<Tree, List, DoubleTree, Node, PointerNode,AVLTreeNode>::GetMostViewedClasses(int numOfClasses, int *courses, int *classes) {
    assert(numOfClasses > 0);
    try {
        int index = 0;
        this->viewed_list.GetMostViewedClasses(numOfClasses, courses, classes, index);
        if (index != numOfClasses) {
            this->zero_viewed_tree.getMostViewedZeroClasses(zero_viewed_tree.getSmallestElement(), numOfClasses, courses,
                                                            classes, index,0,1);
        }
        if (index != numOfClasses) {
            return FAILURE;
        } else {
            return SUCCESS;
        }
    }catch (std::bad_alloc&) {
        return ALLOCATION_ERROR;
    }
}

#endif //HW1_WET_BOOM_H
