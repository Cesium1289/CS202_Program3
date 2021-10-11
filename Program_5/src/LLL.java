//NAME:Carson Hansen
//FILE NAME:LLL.java
//PURPOSE:Define the LLL class which is a linked list that holds different videos
import java.io.Serializable;
public class LLL implements Serializable
{
    private Node mHead;
    private int mSize;

    //Default constructor
    public LLL()
    {
        mSize = 0;
        mHead = null;
    }

    //Wrapper function to add a video to the LLL
    //and returns true if it was added
    public boolean Add(Video toAdd)
    {
        boolean[] added = new boolean[1];
        if(mHead == null)
        {
            ++mSize;
            mHead = new Node(toAdd);
            added[0] = true;
        }
        else
            Add(mHead,toAdd,added);
        System.out.println("Added is " + added[0]);
        return  added[0];
    }

    //Recursive function to add a video the LLL
    private Node Add(Node mHead, Video toAdd, boolean[] added)
    {
        if(mHead == null)
        {
            ++mSize;
            added[0] = true;
            mHead = new Node(toAdd);
            return mHead;
        }
        mHead.SetNext(Add(mHead.GetNext(),toAdd,added));
        return mHead;
    }

    //Wrapper function to remove a video from the LLL.
    //Returns true if removed or false if it was not
    public boolean Remove(int toRemove)
    {
        //store if removed in boolean array
        Boolean[] removed = new Boolean[1];
        removed[0] = false;
        int currentIndex = 0;

        if(mHead == null)
            return false;
        if(currentIndex == toRemove)
        {
            --mSize;
            mHead = mHead.GetNext();
            return true;
        }

        Remove(mHead,toRemove,currentIndex, removed);
        return removed[0];
    }

    //Recursive remove function that removes a video from the list.
    // This will return true if it was removed, false if it was not
    private Node Remove(Node mHead, int toRemove, int currentIndex, Boolean[] removed)
    {
        if(mHead == null)
            return null;

        //compare the index to remove and the current index
        if(toRemove == currentIndex)
        {
            --mSize;
            Node temp = mHead.GetNext();
            removed[0] = true;
            return temp;
        }

        mHead.SetNext(Remove(mHead.GetNext(),toRemove,currentIndex, removed));
        return mHead;
    }

    //Wrapper function to edit a video based on the string passed in.
    //Returns true if the video was found. False if it was not
    public boolean Edit(int toEdit)
    {
        boolean[] found = new boolean[1];
        int currentIndex = 0;

        if(mHead == null)
            return false;

        Edit(mHead,currentIndex, toEdit,found);
        return found[0];
    }


    //Recursive function to edit a video in the LLL.
    //If the video was found, it will return true, else it will return false
    private  Node Edit(Node mHead, int currentIndex, int toEdit, boolean[] found)
    {
        if(mHead == null)
            return null;
        if(currentIndex == toEdit)
        {
            mHead.GetData().Edit();
            found[0] = true;
            return mHead;
        }

        mHead.SetNext(Edit(mHead.GetNext(),currentIndex, toEdit,found));
        return mHead;
    }

    //Wrapper function to display the LLL
    //returns the number displayed
    public int Display()
    {
        if(mHead == null)
            return 0;
        return Display(mHead);
    }

    //Recursive function to display all the data in the LLL.
    //Returns the number of times data was displayed
    private int Display(Node mHead)
    {
        if(mHead == null)
            return 0;

        mHead.GetData().Display();
        return  Display(mHead.GetNext())+1;
    }

    //Wrapper function to display the videos without the quiz if it has one.
    //returns the number of videos displayed
    public int DisplayNoQuiz()
    {
        int index = 0;
        if(mHead == null)
            return 0;
        return DisplayNoQuiz(mHead,index);
    }

    //Recursive function to display the videos without the quiz if it has one.
    //returns the number of videos displayed
    private int DisplayNoQuiz(Node mHead, int index)
    {
        if(mHead == null)
            return 0;

        System.out.print(index+1 +". ");
        mHead.GetData().DisplayNoQuiz();
        ++index;
        return DisplayNoQuiz(mHead.GetNext(),index)+1;
    }

    //Check if LLL is empty. Returns true if head is null
    //else returns false
    public boolean IsEmpty()
    {
        if(mHead == null)
            return true;
        return false;
    }

    //Wrapper function to return a video at a specific index.
    //Returns the video if it at that index. Returns null if it is not
    public Video Get(int index)
    {
        int currentIndex = 0;

        //check if the list is empty or index is greater than the number of elements
        if(index < 0 || mHead == null || index > mSize)
            return null;

        return Get(mHead,index,currentIndex);
    }

    //Recursive function to return an element at a specific spot
    //Returns the video at the element or null if it was out of bounds
    private Video Get(Node mHead, int index, int currentIndex)
    {
        if(currentIndex >= mSize)
            return null;
        if(index == currentIndex)
            return  mHead.GetData();

        ++currentIndex;
        return Get(mHead.GetNext(),index,currentIndex);
    }
}
