//NAME:Carson Hansen
//FILE NAME:BST.java
//PURPOSE:Implement a BST to hold data about courses.
import javax.management.ObjectName;
import java.io.Serializable;

public class BST implements Serializable
{
    private BSTNode mRoot;

    //Default constructor
    public BST()
    {
        mRoot = null;
    }

    //Add a node to the bst. Returns true if it was added.
    public boolean Add(OnlineClass toAdd)
    {
        boolean[] added = new boolean[1];
        added[0] = false;

        if (mRoot == null)
        {
            mRoot = new BSTNode(toAdd);
            return true;
        }

        if (mRoot.GetData().CompareCourseName(toAdd) > 0)
            mRoot.SetLeft(Add(mRoot.GetLeft(), toAdd, added));
        else
            mRoot.SetRight(Add(mRoot.GetRight(), toAdd, added));
       return added[0];
    }

    //Recursive function to add an online class to the bst
    private BSTNode Add(BSTNode mRoot, OnlineClass toAdd, boolean[] added)
    {
        if (mRoot == null)
        {
            mRoot = new BSTNode(toAdd);
            added[0] = true;
            return mRoot;
        }

        if (mRoot.GetData().CompareCourseName(toAdd) > 0)
            mRoot.SetLeft(Add(mRoot.GetLeft(), toAdd, added));
        else
            mRoot.SetRight(Add(mRoot.GetRight(), toAdd, added));

        return mRoot;
    }

    //Wrapper function to display nodes in the bst
    int Display()
    {
        if (mRoot == null)
            return 0;
        return Display(mRoot);
    }

    //Display all the data in the bst. Returns number of data
    //displayed
    private int Display(BSTNode mRoot)
    {
        int displayed = 0;
        if (mRoot == null)
            return 0;

        displayed += Display(mRoot.GetLeft()) + 1;
        mRoot.GetData().DisplayCourseInfo();
        displayed += Display(mRoot.GetRight());
        return displayed;
    }

    //Wrapper function that returns an OnlineClass object to the client.
    // Returns an onlineClass object or null if it was not found
    public OnlineClass Get(String toGet)
    {
        if (mRoot == null)
            return null;
        else if(mRoot.GetData().CompareCourseName(toGet) == 0)
            return mRoot.GetData();
        else if(mRoot.GetData().CompareCourseName(toGet) > 0)
            return Get(mRoot.GetLeft(), toGet);
        else
            return Get(mRoot.GetRight(), toGet);
    }

    //Recursive function to return the data to the client. Returns
    //an online class object if it was found, null if it was not
    private OnlineClass Get(BSTNode mRoot, String toGet)
    {
        if (mRoot == null)
            return null;
        else if(mRoot.GetData().CompareCourseName(toGet) == 0)
            return mRoot.GetData();
        else if(mRoot.GetData().CompareCourseName(toGet) > 0)
            return Get(mRoot.GetLeft(), toGet);
        else
            return Get(mRoot.GetRight(), toGet);
    }

    //Remove all data in the bst by setting the root node to null
    public boolean RemoveAll()
    {
        mRoot = null;
        return true;
    }

    //Wrapper function to remove data in the bst.
    //Returns true if it was removed, false if it was not
    public boolean Remove(String toRemove)
    {
        boolean[] removed = new boolean[1];
        removed[0] = false;

        mRoot = Remove(mRoot, toRemove, removed);
        return removed[0];
    }

    //Recursive function to remove data in the bst.
    //Returns true if it was removed, false if it was not
    private BSTNode Remove(BSTNode mRoot, String toRemove, boolean[] removed)
    {
        if (mRoot == null)
            return null;
        else if (mRoot.GetData().CompareCourseName(toRemove) ==0)
        {
            if (mRoot.GetLeft() == null)
            {
                removed[0] = true;
                return mRoot.GetRight();
            }
            else if (mRoot.GetRight() == null)
            {
                removed[0] = true;
                return mRoot.GetLeft();
            }
            else
            {
                BSTNode[] temp = new BSTNode[1];
                mRoot = FindIOS(mRoot.GetRight(), temp, removed);
                mRoot.SetData(temp[0].GetData());
            }

        }
        else if (mRoot.GetData().CompareCourseName(toRemove) > 0)
            mRoot.SetLeft(Remove(mRoot.GetLeft(), toRemove, removed));
        else
            mRoot.SetRight(Remove(mRoot.GetRight(), toRemove, removed));

        return mRoot;
    }

    //Recursive function to find the IOS of a node that is being removed
    private BSTNode FindIOS(BSTNode mRoot, BSTNode[] temp, boolean[] removed)
    {
        //check if there is a left node to set as the IOS
        if (mRoot.GetLeft() == null)
        {
            removed[0] = true;
            temp[0].SetData(mRoot.GetData());
            return null;
        }
        return FindIOS(mRoot.GetLeft(), temp, removed);
    }
}