//NAME:Carson Hansen
//FILE NAME:playlist.java
//PURPOSE:Let the user implement a playlist filled with videos
import java.io.*;
import java.util.Scanner;

public class Playlist implements Serializable
{
    private LLL mList;
    private String mName;
    private int mNumberVideos;
    private String mDescription;
    private static Scanner input = new Scanner(System.in);

    //default playlist constructor
    public Playlist()
    {
        mList = new LLL();
        mName = null;
        mDescription = null;
        mNumberVideos = 0;
    }

    //Lets the user create a new playlist.
    //Returns 1 after playlist was created
    public int Create()
    {
        int choice = 0;
        System.out.println("Enter the name of the playlist");
        mName = input.nextLine();

        System.out.println("Enter the playlist description");
        mDescription = input.nextLine();

        return 1;
    }

    //Lets user add a video the playlist. Returns true if video
    //was added. Returns false if it was not
    public boolean AddVideo()
    {
        Video newVideo = null;
        int choice = 0;
        System.out.println("What kind of video do you want to add?");
        System.out.println("1.Video");
        System.out.println("2.Video with quiz");
        choice = input.nextInt();
        input.nextLine();

        if(choice == 1)
            newVideo = new Video();
        else
            newVideo = new QuizVideo();
        newVideo.Create();
        if(mList.Add(newVideo))
        {
            ++mNumberVideos;
            System.out.println("Added video to playlist");
            return true;
        }
        else
        {
            System.out.println("ERROR: unable to add video to playlist");
            return false;
        }
    }

    //Lets user remove a video from the playlist. Returns true if the video
    //was removed, false if it was not found
    public boolean RemoveVideo()
    {
        int toRemove;
        boolean removed = false;
        int displayed = 0;

        displayed = mList.DisplayNoQuiz();
        if(displayed == 0)
        {
            System.out.println("There are no videos in this playlist to remove");
            return false;
        }

        System.out.println("Enter the number of the video you want to remove");
        toRemove = input.nextInt();
        removed =  mList.Remove(toRemove-1);
        if(removed)
        {
            --mNumberVideos;
            System.out.println("The video was removed!");
        }
        else
            System.out.println("The video was not found.");
        return  removed;
    }

    //Lets user edit a video in the playlist.
    //Returns true if video was found, false if it was not
    public boolean EditVideo()
    {
        int toEdit;
        boolean found = false;
        int displayed = 0;
        Video video = null;

        displayed = mList.DisplayNoQuiz();
        if(displayed == 0)
        {
            System.out.println("There are no videos in this playlist to edit");
            return false;
        }
        System.out.println("Enter the number of the video you want to edit");
        toEdit = input.nextInt();

        //input.nextLine();
        video = mList.Get(toEdit-1);
        if(video == null)
        {
            System.out.println("Video was not found.");
            return false;
        }
        else
        {
            video.Edit();
            System.out.println("Edits were saved");
            return true;
        }
    }

    //Plays the video the user has selected
    public boolean PlayVideo()
    {
        Video toWatch = null;
        int toPlay;
        int useCC = 0;

        //check if there are videos to play
        if(mList.IsEmpty())
        {
            System.out.println("You have no videos in this playlist to play");
            return false;
        }

        //display the videos w/o the quiz information
        mList.DisplayNoQuiz();

        System.out.println("\n\n");
        System.out.println("Enter the number of the video you want to play");
        toPlay = input.nextInt();

        toWatch = mList.Get(toPlay-1);

        //check if video location was valid
        if(toWatch == null)
            System.out.println("There was no video at the location you entered");
        else
        {
            //check what kind of video the user wants to play
            System.out.println("Do you want to use closed captioning?");
            System.out.println("1.Yes");
            System.out.println("2.No");
            useCC = input.nextInt();
            if(useCC == 1)
                return toWatch.PlayClosedCaption();
            else
                return toWatch.Play();
        }
        return false;
    }

    //Lets user edit playlist data. Returns true if user updated
    //information. False if they did not;
    public boolean EditPlaylistData()
    {
        int choice = 0;
        boolean edited = false;

        do{
            System.out.println("What would you like to edit?");
            System.out.println("1.Playlist name");
            System.out.println("2.Playlist description");
            System.out.println("3.Exit");
            choice = input.nextInt();
            input.nextLine();

            if (choice == 1)
            {
                System.out.println("Enter the new playlist name");
                mName = input.nextLine();
                System.out.println("Edit was saved");
                edited = true;
            }
            else if(choice == 2)
            {
                System.out.println("Enter the playlist description");
                mDescription = input.nextLine();
                System.out.println("Edit was saved");
                edited = true;
            }
            else
                return edited;
        }while(choice < 3);

        return edited;
    }

    //Displays the playlist information to the user
    //Returns false if there is nothing to display
    //true if there is something to display
    public boolean DisplayPlaylistInfo()
    {
        if(mName == null)
            return false;

        System.out.println("Playlist Name: " + mName);
        System.out.println("Playlist Description: " + mDescription);
        System.out.println("Number of videos: " + mNumberVideos);
        System.out.println("-_-_-_-_-_-_-_-_-");
        return true;
    }

    //Displays all the videos in the playlist without the videos
    //Returns the number of videos displayed
    public int DisplayNoQuiz()
    {
        int displayed =0;
        if(mList == null || mList.IsEmpty())
            return 0;

        displayed = mList.Display();
        return displayed;

    }

    //Displays the videos in the playlist. Returns the number
    //of videos that were displayed
    public int Display()
    {
        int displayed =0;

        if(mName == null || mDescription == null || mList.IsEmpty())
        {
            System.out.println("playlist is empty");
            return 0;
        }

        displayed = mList.Display();

        if(displayed == 0)
            System.out.println("There are no videos to display");
        return displayed;
    }
}
