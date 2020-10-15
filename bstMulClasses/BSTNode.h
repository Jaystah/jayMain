class BSTNode
{
private:
    int value;
    BSTNode *left;
    BSTNode *right;
    int level;
    int col;

public:
    BSTNode(int value);
    bool exists()
    {
        if (value)
        {
            return true;
        }
        else
        {
            return false;
        }
    };
    int getLevel()
    {
        return level;
    }
    void setLevel(int value)
    {
        level = value;
    }
    int getCol()
    {
        return col;
    }
    void setCol(int value)
    {
        col = value;
    }
    void setLeft(int val);
    void setRight(int val);
    BSTNode *getRight()
    {
        return right;
    }
    BSTNode *getLeft()
    {
        return left;
    }
    bool hasLeft()
    {
        return left != nullptr;
    }
    bool hasRight()
    {
        return right != nullptr;
    }
    int getVal()
    {
        return value;
    }
};
