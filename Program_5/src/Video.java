//NAME:Carson Hansen
//FILE NAME:Video.java
//PURPOSE:Define the video class as well as define its various functions
import java.io.Serializable;
import java.util.ArrayList;
import java.util.Scanner;

public class Video implements Serializable
{
    protected static Scanner input = new Scanner(System.in);
    protected String mName;
    protected String mDescription;
    protected String mDuration;
    protected int mViews;
    protected String mClosedCaption;
    protected ArrayList<String> mComments;

    //Default constructor
    public Video()
    {
        mClosedCaption = null;
        mComments = new ArrayList<String>();
        mName = null;
        mDescription = null;
        mDuration = null;
        mViews = 0;
    }

    //Allows user to put info that defines a video
    public int Create()
    {
        int choice = 0;
        System.out.println("Enter the name of the video");
        mName = input.nextLine();

        System.out.println("Enter the Description of the video");
        mDescription = input.nextLine();

        System.out.println("Enter the duration of the video");
        mDuration = input.nextLine();

        System.out.println("Will this video support closed captioning?");
        System.out.println("1.Yes");
        System.out.println("2.No");
        choice = input.nextInt();
        input.nextLine();
        if(choice == 1)
        {
            System.out.println("Enter the closed captioning for the video");
            mClosedCaption = input.nextLine();
        }

        return 1;
    }

    //Displays the name, description, and duration of the video
    public int Display()
    {
        if (mName == null || mDescription == null || mDuration == null) {
            System.out.println("There was an error displaying this video's content");
            return 0;
        }

        System.out.println("-_-_-_-_-_-_-_-_-_-");
        System.out.println("Video Name: " + mName);
        System.out.println("Video Description: " + mDescription);
        System.out.println("Video Duration: " + mDuration);
        System.out.println("Times video has been viewed: " + mViews);

        //check if there are comments to display
        if(mComments.size() > 0)
        {
            System.out.println("Video comments:");
            for(int i =0; i < mComments.size();++i)
            {
                System.out.print(i+1 + ". ");
                System.out.println(mComments.get(i));
            }
        }
        System.out.println();
        return  1;
    }

    //Displays the video without showing the quiz questions.
    //Returns 1 if it was able to display, 0 if it was not.
    public int DisplayNoQuiz()
    {
        if (mName == null || mDescription == null || mDuration == null) {
            System.out.println("There was an error displaying this video's content");
            return 0;
        }

        System.out.println("-_-_-_-_-_-_-_-_-_-");
        System.out.println("Video Name: " + mName);
        System.out.println("Video Description: " + mDescription);
        System.out.println("Video Duration: " + mDuration);
        System.out.println("Times video has been viewed: " + mViews);

        return  1;
    }

    //Allows the user to edit the videos data
    public int Edit()
    {
        boolean isDone = false;
        int choice = 0;

        while (!isDone)
        {
            System.out.println("1.Edit Video Name");
            System.out.println("2.Edit Video Description");
            System.out.println("3.Edit Video Duration");
            System.out.println("4.Add a comment");
            System.out.println("5.Remove a comment");
            System.out.println("6.Edit closed captioning");
            System.out.println("7.Exit");
            choice = input.nextInt();
            input.nextLine();

            if (choice == 1)
            {
                System.out.println("Enter the name of the video");
                mName = input.nextLine();
            }
            else if (choice == 2)
            {
                System.out.println("Enter the description of the video");
                mDescription = input.nextLine();
            }
            else if (choice == 3)
            {
                System.out.println("Enter the duration of the video");
                mDuration = input.nextLine();
            }
            else if(choice == 4)
            {
                PostMessage();
            }
            else if(choice == 5)
            {
                RemoveMessage();
            }
            else if(choice == 6)
            {
                System.out.println("Enter the closed captioning for the video");
                mClosedCaption = input.nextLine();
            }
            else
                isDone = true;
        }
        return 1;
    }

    //Allows the user to play the video
    public boolean Play()
    {
        ++mViews;
        System.out.println("The video is now playing!");
        System.out.println("The video is now over!");
        System.out.println("Wow! That video was neat!");
        System.out.println("\n\n");
        return true;
    }

    //While playing the video, this will have text that shows up
    public boolean PlayClosedCaption()
    {
        ++mViews;
        if(mClosedCaption != null) {
            System.out.println("The video is now playing with closed captioning!");
            System.out.println(mClosedCaption);
        }
        else
            System.out.println("This video does not have closed captioning. Playing without it.");
        System.out.println("The video is now over!");
        System.out.println("Wow! That video was neat!");
        System.out.println("\n\n");
        return true;
    }

    //Compare the names of two strings. Returns true if the names are the same
    //false if they are not the same.
    public boolean IsSameName(String name)
    {
        if(mName.equalsIgnoreCase(name))
            return true;
        return false;
    }

    //Lets user post a message. Returns 1
    //if it was posted. 0 if it was not.
    public int PostMessage()
    {
        String message;
        String sender;

        System.out.println("Enter the name of the person sending the message");
        sender = input.nextLine();
        System.out.println("Enter the message you want to add");
        message = input.nextLine();

        //edit the format of the message to look like - Sender: message
        sender += ": " + message;

        //check if message was added
        if(mComments.add(sender))
        {
            System.out.println("Message was added");
            return 1;
        }
        else
            System.out.println("There was an issue posting your message");
        return 0;
    }

    //Lets user remove a comment.
    //Returns true if it was removed, false if it was not.
    public int RemoveMessage()
    {
        int toRemove = 0;
        if(mComments.isEmpty())
            return 0;

        //display comments to user
        for(int i =0; i < mComments.size();++i)
        {
            System.out.print(i+1 + ". ");
            System.out.println(mComments.get(i));
        }

        System.out.println("Enter the comment number you want to remove");
        toRemove = input.nextInt();

        //validate data
        if(toRemove < 0 || toRemove > mComments.size())
            return 0;

        mComments.remove(toRemove-1);
        return 1;
    }

    //Displays the messages to the user.
    //Returns number of messages displayed.
    public int DisplayMessages()
    {
        if(mComments.isEmpty())
            return 0;

        for(int i =0; i < mComments.size();++i)
        {
            System.out.print(i+1 + ". ");
            System.out.println(mComments.get(i));
        }
        return mComments.size();
    }
}
