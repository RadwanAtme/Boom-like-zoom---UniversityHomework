#include <iostream>
#include "Boom.h"
#include "AVLTree.h"
#include "LinkedList.h"
#include "PointerNode.h"
#include "TreeNode.h"

typedef Boom< AVLTree<PointerNode< listElement< AVLTree<TreeNode>,TreeNode> >>,
            LinkedList<AVLTree<TreeNode>,TreeNode>,
            AVLTree<AVLTreeNode<TreeNode>>,
            TreeNode,
            PointerNode< listElement< AVLTree<TreeNode>,TreeNode > >,
            AVLTreeNode<TreeNode> > BoomStructure;

void *Init(){
    BoomStructure* DS = new BoomStructure();
    return DS;
}

StatusType AddCourse (void *DS, int courseID, int numOfClasses){
    if((DS==NULL)||(numOfClasses<=0)||(courseID<=0)){
        return INVALID_INPUT;
    }
    BoomStructure* Boom = static_cast<BoomStructure*>(DS);
    return Boom->AddCourse(courseID,numOfClasses);
}

StatusType RemoveCourse(void *DS, int courseID){
    if((DS==NULL)||(courseID<=0)){
       return INVALID_INPUT;
    }else{
        BoomStructure* Boom = static_cast<BoomStructure*>(DS);
        return Boom->removeCourse(courseID);
    }
}

StatusType WatchClass(void *DS, int courseID, int classID, int time){
    if((DS==NULL)||(classID<0)||(courseID<=0)||(time<=0)){
        return INVALID_INPUT;
    }
    BoomStructure* Boom = static_cast<BoomStructure*>(DS);
    return Boom->WatchClass(courseID,classID,time);
}

StatusType TimeViewed(void *DS, int courseID, int classID, int *timeViewed){
    if((DS==NULL)||(classID<0)||(courseID<=0)){
        return INVALID_INPUT;
    }
    BoomStructure* Boom = static_cast<BoomStructure*>(DS);
    return Boom->TimeViewed(courseID,classID,timeViewed);
}


StatusType GetMostViewedClasses(void *DS, int numOfClasses, int *courses, int *classes){
    if((DS==NULL)||(numOfClasses<=0)){
        return INVALID_INPUT;
    }
    BoomStructure* Boom = static_cast<BoomStructure*>(DS);
    return Boom->GetMostViewedClasses(numOfClasses,courses,classes);
}

void Quit(void **DS){
    if(DS== nullptr){
        return;
    }else{
        BoomStructure* Boom = static_cast<BoomStructure*>(*DS);
        delete Boom;
        *DS = nullptr;
    }
}
