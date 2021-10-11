//NAME:Carson Hansen
//FILE NAME:BSTNode.java
//PURPOSE: Define the node of the BST
import java.io.Serializable;
public class BSTNode implements Serializable
{
    private OnlineClass mData;
    private BSTNode mLeft;
    private BSTNode mRight;

    //Default constructor
    public BSTNode()
    {
        mData = null;
        mLeft = null;
        mRight = null;
    }

    //Argument constructor
    public BSTNode(OnlineClass data)
    {
        mData = data;
        mLeft = null;
        mRight = null;
    }

    //Return the onlineClass data
    public OnlineClass GetData()
    {
        return mData;
    }

    //Return the left node
    public BSTNode GetLeft()
    {
        return  mLeft;
    }

    //Return the right node
    public BSTNode GetRight()
    {
        return  mRight;
    }

    //Sets the onlineClass data
    public void SetData(OnlineClass data)
    {
        mData = data;
    }

    //Sets the left node
    public void SetLeft(BSTNode left)
    {
        mLeft = left;
    }

    //Sets the right node
    public void SetRight(BSTNode right)
    {
        mRight = right;
    }

    //check to see if the current node is a leaf.
    //Returns true if it has no left or right child.
    //False if it has both or one child
    public boolean IsALeaf()
    {
        if(mRight == null && mLeft == null)
            return true;
        return false;
    }

}
