//NAME:Carson Hansen
//FILE NAME:Question.java
//PURPOSE:Define the base class for what a question is
import java.io.Serializable;
import java.util.Scanner;

public abstract class Question implements Serializable
{
    protected static Scanner input = new Scanner(System.in);
    protected String mCorrectAnswer;
    protected String mUserAnswer;
    protected String mQuestion;

    //Default question constructor
    public Question()
    {
        mCorrectAnswer = null;
        mUserAnswer = null;
        mQuestion = null;
    }

    //Argument constructor
    public Question(String question)
    {
        input = new Scanner(System.in);
        mCorrectAnswer = null;
        mUserAnswer = null;
        mQuestion = question;
    }

    //Display the question
    public int Display()
    {
        if(mQuestion == null)
        {
            System.out.println("ERROR: unable to display question");
            return 0;
        }

        System.out.println("-_-_-_-Default Question display-_-_-_-");
        System.out.println(mQuestion);
        return  1;
    }

    //Checks if a question has the same name. Returns
    //true if they are the same. False if they are different
    public boolean IsSameName(String name)
    {
        if(mQuestion.equalsIgnoreCase(name))
            return true;
        return false;
    }

    //Allows the user to edit the videos data
    public boolean Edit()
    {
        boolean isDone = false;
        int choice = 0;

        while (!isDone)
        {
            System.out.println("1.Edit Question");
            System.out.println("2.Edit Correct Answer");
            System.out.println("3.Exit");
            choice = input.nextInt();
            input.nextLine();
            if (choice == 1)
            {
                System.out.println("Enter the question.");
                mQuestion = input.nextLine();
                System.out.println("Successfully updated.");
            } else if (choice == 2)
            {
                System.out.println("Enter the number of the correct answer.");
                mCorrectAnswer = input.nextLine();
                System.out.println("Successfully updated.");
            } else
                isDone = true;
        }
        return true;
    }

    //Stub function that is implemented in derived classes
    public int Create()
    {
        return 1;
    }

    //Check whether or not the user got the question correct
    public boolean IsCorrectAnswer()
    {
        if(mCorrectAnswer.equalsIgnoreCase(mUserAnswer))
            return true;
        return false;
    }

    //Displays the question to the user. Returns
    //0 if there is no question to display, 1 if there is.
    public int DisplayQuestion()
    {
        if(mQuestion == null)
            return 0;

        System.out.println(mQuestion);
        return  1;
    }
}
