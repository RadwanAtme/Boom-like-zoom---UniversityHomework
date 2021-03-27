#ifndef HW1_WET_TREENODE_H
#define HW1_WET_TREENODE_H

/*Regular Node -no need to be generic-
 * Includes: course-number (int)
 *            class-number (int)
 *
 * make the node throw Aloocation error somehow  - maybe we can use std::exception allocation error
*/
class TreeNode{
    int courseID;
    int classID;
    TreeNode* parent;
    TreeNode* right_son;
    TreeNode* left_son;
    int height;
    int balance_factor;
public:
    TreeNode(int courseID,int classID);
    ~TreeNode()=default;
    TreeNode& operator=(TreeNode& node)= default;
    TreeNode(TreeNode& node);
    int getCourseID()const;
    int getClassID()const;
    bool operator==(TreeNode& Node)const;
    bool operator<(TreeNode& Node)const;
    TreeNode*& getRight();
    TreeNode*& getLeft();
    int& getHeight();
    int& getBF();
    TreeNode*& getParent();

};



#endif //HW1_WET_TREENODE_H
