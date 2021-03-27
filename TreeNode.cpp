#include "TreeNode.h"

TreeNode::TreeNode(int courseID, int classID):courseID(courseID),classID(classID),parent(nullptr),right_son(nullptr),left_son(nullptr),
                                                height(0),balance_factor(0){}

int TreeNode::getCourseID()const{
    return courseID;
}

int TreeNode::getClassID()const{
    return classID;
}

bool TreeNode::operator==(TreeNode &Node)const{
    return ((courseID==Node.getCourseID())&&(classID==Node.getClassID()));
}

bool TreeNode::operator<(TreeNode &Node)const{
    int nodeCourseID = Node.getCourseID();
    if(courseID>nodeCourseID){
        return false;
    }else if(courseID<nodeCourseID){
        return true;
    }else{
        return (classID<Node.getClassID());
    }
}

TreeNode*& TreeNode::getRight() {
    return right_son;
}

TreeNode*& TreeNode::getLeft() {
    return left_son;
}

int& TreeNode::getHeight() {
    return height;
}

int& TreeNode::getBF() {
    return balance_factor;
}

TreeNode*& TreeNode::getParent() {
    return parent;
}

TreeNode::TreeNode(TreeNode &node){
    courseID = node.getCourseID();
    classID = node.getClassID();
    height = node.getHeight();
    balance_factor=node.getBF();
    parent = nullptr;
    left_son = nullptr;
    right_son = nullptr;
}
