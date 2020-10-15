#include <vector>
#include "BSTNode.h"

class BST
{
public:
    BST();
    ~BST();
    void insertKey(int newKey);
    bool hasKey(int searchKey);
    void deleteTree(BSTNode *node);
    std::vector<int> inOrder();
    int getHeight()
    {
        return height;
    }
    void prettyPrint();
private:
    BSTNode *head = nullptr;
    int height;
    int level;
    int totalNodes;
    std::vector<BSTNode *> allnodes;
    void printLine(int width);
    std::vector<int> sortedVec;
    void printLevel(int level);
    std::vector<BSTNode *> getVectorFromLevel(int level);
    void setTotalNodes(int num)
    {
        totalNodes = num;
    }
    int getTotalNodes()
    {
        return totalNodes;
    }
    void calcInOrder(BSTNode* node);
};