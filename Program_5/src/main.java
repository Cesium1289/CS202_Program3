//NAME:Carson Hansen
//FILE NAME:main.java
//PURPOSE:Starting point of the program to let user create videos for an online class
import java.io.*;
import java.sql.SQLOutput;
import java.util.Scanner;
public class main
{
    private static Scanner input = new Scanner(System.in);

    public static void main(String[] args) throws IOException
    {
       BST bst = new BST();
        int choice = 0;
        boolean isDone = false;

        //call chooseFile function
        bst = ChooseFile(bst);

        do{
            choice = Menu(input);
            switch (choice)
            {
                case 1:
                {
                    CreateNewCourse(bst);
                    break;
                }
                case 2:
                {
                    RemoveCourse(bst);
                    break;
                }
                case 3:
                {
                    RemoveAllCourses(bst);
                    break;
                }
                case 4:
                {
                    ViewCourse(bst);
                    break;
                }
                case 5:
                {
                    DisplayAllCourses(bst);
                    break;
                }
                case 6:
                {
                    isDone = true;
                    break;
                }
                default:
                {
                    System.out.println("ERROR: should not have got here....\nProgram is closing");
                    isDone = true;
                    break;
                }
            }

        //while user is not done with the program
        }while(!isDone);

        //write data to file
        WriteToFile(bst);

    }

    //Displays the main menu to the user
    public static int Menu(Scanner input)
    {
        int choice = 0;

        System.out.println("1.Create new online course");
        System.out.println("2.Remove online course");
        System.out.println("3.Remove all online courses");
        System.out.println("4.View online course"); //old menu
        System.out.println("5.Display all courses");
        System.out.println("6.Exit");

        //validate input from the user
        while(!input.hasNextInt())
        {
            System.out.println("Enter a valid option");
            input.next();
        }
        choice = input.nextInt();
        input.nextLine();
        return choice;
    }

    //Display all the courses in the BST to the user
    public static void DisplayAllCourses(BST bst)
    {
        int displayed;
        displayed = bst.Display();

        if(displayed >0)
            System.out.println("Displayed " + displayed + " courses");
        else
            System.out.println("There are no courses to display");
    }

    //Allow the user to remove all the courses that the BST has
    public static void RemoveAllCourses(BST bst)
    {
        int choice;
        System.out.println("Are you sure you want to remove all the courses?");
        System.out.println("1.Yes");
        System.out.println("2.No");
        choice = input.nextInt();

        if(choice == 1)
        {
            if(bst.RemoveAll())
                System.out.println("Removed all courses");
            else
                System.out.println("There was an issue removing the courses");
        }
        else
            return;

    }

    //Allow the user to remove a course from the BST
    public static void RemoveCourse(BST bst)
    {
        String toRemove;
        bst.Display();

        System.out.println("Enter the name of the course you want to remove");
        toRemove = input.nextLine();

        if(bst.Remove(toRemove))
            System.out.println("Course was removed.");
        else
            System.out.println("There is not a course with that name");

    }

    //Allow the user to create a new course
    public static void CreateNewCourse(BST bst)
    {
        OnlineClass newClass = new OnlineClass();
        newClass.Create();

        if(bst.Add(newClass))
            System.out.println("Class was created");
        else
            System.out.println("There was an issue creating that class");
    }

    //Allow the user to view the courses that are in the BST
    public static void ViewCourse(BST bst) {
        String toView;
        int choice = 0;
        OnlineClass onlineClass;

        //display the courses available
        bst.Display();

        System.out.println("Enter the name of the course you want to view");
        toView = input.nextLine();

        //find the course the user is trying to get
        onlineClass = bst.Get(toView);

        //check if there is a course
        if (onlineClass == null)
        {
            System.out.println("Unable to find a course with that name");
            return;
        }
        else
        {
            do
            {
                System.out.println("1.Edit course information");
                System.out.println("2.Display course information");
                System.out.println("3.Display playlist information");
                System.out.println("4.Display videos in a playlist");
                System.out.println("5.Play video");
                System.out.println("6.Exit");
                choice = input.nextInt();

                switch (choice)
                {
                    case 1: {

                        if (onlineClass.Edit())
                            System.out.println("Edits to the course were saved");
                        break;
                    }
                    case 2:
                    {
                        onlineClass.DisplayCourseInfo();
                        break;
                    }
                    case 3:
                    {
                        onlineClass.Display();
                        break;
                    }
                    case 4:
                    {
                        onlineClass.DisplaySpecificPlaylist();

                        break;
                    }
                    case 5:
                    {
                        onlineClass.PlayVideo();
                        break;
                    }
                    default:
                    {
                        return;
                    }
                }

            //while user is not done with the menu
            } while (choice < 6);
        }
    }

    //Lets the user decide if they want to import data or create a new course
    public static BST ChooseFile(BST bst) throws IOException
    {
        int fileChoice = 0;

        System.out.println("Select an option");
        System.out.println("1.Import course from file");
        System.out.println("2.Create new course (file data will be overwritten if a file exists)");
        fileChoice = input.nextInt();

        //check user option
        if(fileChoice == 1)
        {
            //check if there is a file to read from
            bst = ReadFromFile();
            if(bst == null)
            {
                bst = new BST();
                System.out.println("There was no file, or file was empty");
            }
            else
                System.out.println("playlist was imported from file");
        }
        return bst;
    }

    //Reads the online class in from a file
    public static BST ReadFromFile()throws IOException
    {
        BST bst = new BST();
        FileInputStream inputStream = null;
        ObjectInputStream objectStream = null;

        try
        {
            inputStream = new FileInputStream("data.ser");
            objectStream = new ObjectInputStream(inputStream);
            BST newBST = (BST) objectStream.readObject();

            bst = newBST;
            inputStream.close();
            objectStream.close();
        }
        catch (Exception e)
        {
            System.out.println("There was no file to read or file was empty");
            return null;
        }

        if(objectStream != null)
            objectStream.close();
        return bst;

    }

    //Writes the online course to a file
    public static void WriteToFile(BST bst) throws  IOException
    {
        ObjectOutputStream objectStream = null;
        FileOutputStream outputStream = null;

        try
        {
            outputStream = new FileOutputStream("data.ser", false);
            objectStream = new ObjectOutputStream(outputStream);
            objectStream.writeObject(bst);
        }
        catch (Exception ex)
        {
            System.out.println("There was an error saving the file");
        }
        if(outputStream != null)
            outputStream.close();
        if(objectStream != null)
            objectStream.close();
    }
}
