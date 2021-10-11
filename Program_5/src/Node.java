//NAME:Carson Hansen
//FILE NAME:Node.java
//PURPOSE:Package to hold a videos data to be stored into a LLL
import java.io.Serializable;
public class Node implements Serializable
{
    private Video mData;
    private Node mNext;

    //Default constructor
    public Node()
    {
        mData = null;
        mNext = null;
    }

    //Arg constructor that takes a video object
    public Node(Video video)
    {
        mData = video;
        mNext = null;
    }

    //Sets the next node to the node argument
    public void SetNext(Node next)
    {
        mNext = next;
    }

    //Sets the video data
    public void SetData(Video data)
    {
        mData = data;
    }

    //Returns the node data
    public Video GetData()
    {
        return  mData;
    }

    //Returns the next node
    public Node GetNext()
    {
        return mNext;
    }
}
