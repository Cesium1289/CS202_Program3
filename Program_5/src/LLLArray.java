//NAME:Carson Hansen
//FILE NAME:LLLArray.java
//PURPOSE:Define the LLLArray class to hold an array of playlists
import java.io.Serializable;
public class LLLArray implements Serializable
{
    final int SIZE = 10;
    private Playlist[] mHead;
    private int mSize;

    //default LLLArray constructor
    public LLLArray()
    {
        mSize = 0;
        mHead = new Playlist[10];
    }

    //Wrapper function to add a playlist to the LLLArray. Returns true if added
    //False if there was not enough room to add it
    public boolean Add(Playlist playList)
    {
        boolean[] added = new boolean[1];
        added[0] = false;
        int index = 1;

        if(mHead[0] == null)
        {
            mHead[0] = playList;
            ++mSize;
            return true;
        }
        else
            return Add(mHead, playList, index, added);
    }

    //Recursive function to add a playlist to the playlist. Returns true if
    //it was added to the list. False if it was not
    private boolean Add(Playlist[] mHead, Playlist playList, int index, boolean[] added)
    {
        if(index == SIZE)
            return added[0];

        if(mHead[index] == null)
        {
            added[0] = true;
            mHead[index] = playList;
            ++mSize;
            return added[0];
        }
        ++ index;
        return Add(mHead,playList,index,added);
    }

    //Wrapper function to display the playlist.
    //Returns number of items displayed
    public int Display()
    {
        int index = 0;
        int[] displayed = new int[1];
        displayed[0] = 0;
        if(mHead[0] == null)
            return 0;

        Display(mHead,index,displayed);
        return displayed[0];
    }

    //Recursive function to display the playlist data.
    //Returns number of items displayed
    private int Display(Playlist[] mHead, int index, int[] displayed)
    {
        if(index == SIZE)
            return displayed[0];
        if(mHead[index] == null)
            return displayed[0];

        System.out.print(index+1 +". ");
        mHead[index].DisplayPlaylistInfo();
        ++index;
        ++displayed[0];
        return Display(mHead,index,displayed);
    }

    //Remove a playlist based on the index past in.
    //Returns true if removed or false if it was not
    public boolean Remove(int index)
    {
        //check if list is empty or index is out of bounds
        if(mHead == null || mHead[0] == null || index > mSize || index < 0)
            return false;

        //place last playlist in spot that is being deleted
        mHead[index] = mHead[mSize-1];
        mHead[mSize-1] = null;

        --mSize;
        return true;
    }

    //Wrapper function to display all the playlist names
    //Returns the number of playlists displayed
    public int DisplayNoQuiz()
    {
        int index = 0;
        int[] displayed = new int[1];
        displayed[0] = 0;
        if(mHead[0] == null)
            return 0;
        return DisplayNoQuiz(mHead,index,displayed);
    }

    //Recursive function to display the playlist names with a corresponding number to indicate the order they are in
    private int DisplayNoQuiz(Playlist[] mHead, int index, int[] displayed)
    {
        if(index == SIZE)
            return displayed[0];
        if(mHead[index] == null)
            return displayed[0];

        System.out.print(index+1 +". ");
        mHead[index].DisplayPlaylistInfo();
        ++index;
        ++displayed[0];
        return DisplayNoQuiz(mHead,index,displayed);
    }

    //Checks if the array is empty. Returns true if
    //mHead[0] is empty. False if mHead[0] is not empty
    public boolean IsEmpty()
    {
        if(mHead == null || mHead[0] == null)
            return true;
        return false;
    }

    //Returns the playlist at the given index. Will return null
    //if there is no index at the requested spot
    public Playlist Get(int index)
    {
        //check if the list is empty and if the index that was requested is out of bounds
        if(mHead == null || mHead[0] == null || index < 0 || index > mSize)
            return null;
        return mHead[index];
    }
}
