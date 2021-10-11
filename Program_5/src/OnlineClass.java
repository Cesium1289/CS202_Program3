//NAME:Carson Hansen
//FILE NAME:OnlineClass.java
//PURPOSE:Store and define data for an online class. Such as the class
//name, instructor name, course description, and the video playlists
import java.io.*;
import java.io.IOException;
import java.util.Scanner;

public class OnlineClass implements Serializable
{
    private  LLLArray mPlayList;
    private String mInstructor;
    private String mCourseName;
    private String mDescription;
    private int mPlaylists;
    private static Scanner input = new Scanner(System.in);

    //OnlineClass constructor
    public OnlineClass()
    {
        mPlayList = new LLLArray();
        mInstructor = null;
        mCourseName = null;
        mDescription = null;
        mPlaylists = 0;
    }

    //Allow user to create the online class
    public boolean Create()
    {
        mPlaylists = 0;

        System.out.println("Enter the name of the course");
        mCourseName = input.nextLine();

        System.out.println("Enter course description");
        mDescription = input.nextLine();

        System.out.println("Enter the instructors name");
        mInstructor = input.nextLine();

        return true;
    }

    //Lets user create a playlist
    private boolean CreatePlaylist()
    {
        Playlist newPlaylist = new Playlist();
        newPlaylist.Create();

        //check if playlist was added
        if(mPlayList.Add(newPlaylist))
        {
            ++mPlaylists;
            return true;
        }

        return false;
    }

    //Lets the user remove a playlist from the course. Returns true
    //if playlist was remove. False if it was not
    private boolean RemovePlaylist()
    {
        int toRemove = 0;

        //check if playlist is empty
        if(mPlayList.IsEmpty())
            return false;

        mPlayList.Display();
        System.out.println("Enter the number of the playlist you want to remove");
        toRemove = input.nextInt();

        if(mPlayList.Remove(toRemove-1))
        {
            //reduce number of playlists by 1
            --mPlaylists;
            return true;
        }
        return false;
    }

    //Allow the user to edit the online class. Returns true if user made an edit.
    //False if they did not
    public boolean Edit()
    {
        boolean madeEdit = false;
        int choice = 0;
        boolean isDone = false;

        do {
            System.out.println("Select an option");
            System.out.println("1.Add a playlist");
            System.out.println("2.Remove a playlist");
            System.out.println("3.Edit existing playlist");
            System.out.println("4.Edit class information");
            System.out.println("5.Exit");
            choice = input.nextInt();

            //compare user input
            if(choice == 1)
            {
                if(CreatePlaylist())
                {
                    System.out.println("Successfully created the new playlist");
                    madeEdit = true;
                }
                else
                    System.out.println("There was an issue creating that playlist.");
            }
            else if(choice == 2)
            {
                if(mPlayList.IsEmpty())
                    System.out.println("There are no playlists to remove.");
                else if(RemovePlaylist())
                {
                    System.out.println("Successfully removed the playlist.");
                    madeEdit = true;
                }
                else
                    System.out.println("There was an issue removing that playlist.");
            }
            else if (choice == 3)
            {
                if(mPlayList.IsEmpty())
                    System.out.println("There are no playlists to edit.");
                else if(EditPlaylist())
                {
                    System.out.println("Edits to the playlist were saved.");
                    madeEdit = true;
                }
                else
                    System.out.println("There was an issue saving the edits to the playlist.");
            }
            else if(choice == 4)
            {
                if(EditClassInfo())
                {
                    System.out.println("Successfully updated class information.");
                    madeEdit = true;
                }
                else
                    System.out.println("There was unable to save changes");
            }
            else
                isDone = true;

        }while(!isDone);

        return madeEdit;
    }

    //Displays the playlists the class has as well as class information. Returns
    //the number of playlists displayed
    public int Display()
    {
        if(!DisplayCourseInfo())
        {
            System.out.println("No course to display");
            return 0;
        }
        return mPlayList.Display();
    }

    //Displays the playlists the class has as well as class information. Returns
    //the number of playlists displayed
    public int DisplaySpecificPlaylist()
    {
        Playlist playlist = null;
        int index = 0;

        if(mPlayList.IsEmpty())
        {
            System.out.println("There are no playlists for this course");
            return 0;
        }
        mPlayList.Display();
        System.out.println("Enter the number of the playlist you want to display");
        index = input.nextInt();

        playlist = mPlayList.Get(index-1);
        playlist.Display();
        return 1;
    }

    //Display the course information
    public boolean DisplayCourseInfo()
    {
        //check if data is valid
        if(mInstructor == null || mDescription == null || mCourseName == null)
        {
            System.out.println("Unable to display course info. Either instructor, description, or course name is invalid");
            return false;
        }

        //display data
        System.out.println("Course Name: " + mCourseName);
        System.out.println("Course Instructor: " + mInstructor);
        System.out.println("Course Description: " + mDescription);
        System.out.println("Number of playlists: " + mPlaylists);
        System.out.println("-_-_-_-_-_-_-_-_");
        return true;
    }

    //Displays the playlist data and playlists data as well
    //Returns number of playlists displayed
    public int DisplayPlaylist()
    {
        if(mPlayList.IsEmpty())
            return 0;

        return mPlayList.DisplayNoQuiz();
    }

    //Lets user edit the playlist. Returns true if edits were made
    //false if nothing was changed
    private boolean EditPlaylist()
    {
        int videoChoice = 0;
        boolean madeEdit = false;
        int editChoice = 0;
        int edit = 0;
        Playlist playlist = null;

        //display videos in playlist
        mPlayList.DisplayNoQuiz();
        System.out.println("Enter the number of the playlist you want to edit");
        videoChoice = input.nextInt();

        playlist = mPlayList.Get((videoChoice-1));

        //check if there is a valid playlist
        if(playlist != null)
        {
            System.out.println("Select an option");
            System.out.println("1.Add video");
            System.out.println("2.Remove video");
            System.out.println("3.Edit video information");
            System.out.println("4.Edit playlist information");
            System.out.println("5.Exit");
            editChoice = input.nextInt();

            if (editChoice == 1)
            {
                if (playlist.AddVideo())
                {
                    System.out.println("Video was added to playlist");
                    madeEdit = true;
                } else
                    System.out.println("There was an issue adding the video to the playlist");
            }
            else if (editChoice == 2)
            {
                if (playlist.RemoveVideo())
                {
                    System.out.println("Video was removed to playlist");
                    madeEdit = true;
                }
                else
                    System.out.println("There was an issue removing the video to the playlist");
            }
            else if (editChoice == 3)
            {
                if (playlist.EditVideo())
                {
                    System.out.println("Video was successfully updated");
                    madeEdit = true;
                } else
                    System.out.println("There was an issue updating the video to the playlist");
            }
            else if(editChoice == 4)
            {
                if(playlist.EditPlaylistData())
                    System.out.println("Successfully updated playlist data");
            }
            else
                editChoice = 4;
        }
        else
            System.out.println("You have no playlists to edit");
        return  madeEdit;
    }

    //Allows the user to edit the class information. Returns true
    //if user edited data. False if they did not
    private boolean EditClassInfo()
    {
        int toEdit = 0;
        boolean madeEdit = false;

        do {
            System.out.println("What would you like to edit?");
            System.out.println("1.Course name");
            System.out.println("2.Course description");
            System.out.println("3.Edit instructor name");
            System.out.println("4.Exit");
            toEdit = input.nextInt();

            input.nextLine();

            if(toEdit == 1)
            {
                System.out.println("Enter the course name");
                mCourseName = input.nextLine();

                System.out.println("Course name was updated.");
                madeEdit = true;
            }
            else if(toEdit == 2)
            {
                System.out.println("Enter the course description");
                mDescription = input.nextLine();

                System.out.println("Course description was updated.");
                madeEdit = true;
            }
            else if(toEdit == 3)
            {
                System.out.println("Enter the instructors name");
                mInstructor = input.nextLine();

                System.out.println("Course instructor was updated.");
                madeEdit = true;
            }
            else if(toEdit != 4)
                System.out.println("Enter a valid option");

        //while user is not done
        }while(toEdit < 4);

        return  madeEdit;
    }

    //Lets user play a video. Returns true if video was played.
    //False if the video was not played
    public boolean PlayVideo()
    {
        Playlist playlist = null;
        int choice = 0;


        //check if there are videos to play
        if (mPlayList.IsEmpty())
        {
            System.out.println("You don't have a playlist to display videos from");
            return false;
        }
        else
        {
            //prompt user to input video to watch
            mPlayList.DisplayNoQuiz();
            System.out.println("Enter the number of the playlist you want to play a video from");
            choice = input.nextInt();

            playlist = mPlayList.Get(choice - 1);

            if (playlist == null)
            {
                System.out.println("You selected an invalid playlist");
                return false;
            }
        }
        return playlist.PlayVideo();
    }

    //Compare the objects course name and the argument
    //passed in. Return true if they have the same name,
    //false if they do not
    public int CompareCourseName(String name)
    {
        return mCourseName.compareToIgnoreCase(name);
    }

    //Compare the objects course name and the argument
    //passed in. Return true if they have the same name,
    //false if they do not
    public int CompareCourseName(OnlineClass name)
    {
        return mCourseName.compareToIgnoreCase(name.mCourseName);
    }
}
