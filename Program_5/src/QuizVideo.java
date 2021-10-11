//NAME:Carson Hansen
//FILE NAME:QuizVideo.java
//PURPOSE:Define a video that has a quiz component
import java.io.Serializable;
public class QuizVideo extends Video implements Serializable
{
    private Quiz mQuiz;

    //Default constructor
    public QuizVideo()
    {
        super();
        mQuiz = new Quiz();
    }

    //Allow user to create video questions
    public int Create()
    {
        int choice = 1;
        super.Create();

        while (choice ==1)
        {
            mQuiz.AddQuestion();
            System.out.println("Would you like to add another question?");
            System.out.println("1.Yes");
            System.out.println("2.No");
            choice = input.nextInt();
        }
        return 1;
    }

    //Display the content of the question
    public int Display()
    {
        super.Display();
        mQuiz.Display();
        return 1;
    }

    //Lets user add a quiz question
    public int AddQuizQuestion()
    {
        mQuiz.AddQuestion();
        return 1;
    }

    //Lets user remove a quiz question
    public int RemoveQuizQuestion()
    {
        mQuiz.Remove();
        return 1;
    }

    //Allows the user to edit the videos data
    public int Edit()
    {
        int choice = 0;
        boolean isDone = false;
        boolean readyToExit = false;
        do {
            System.out.println("Select an option");
            System.out.println("1.Edit video information");
            System.out.println("2.Edit quiz information");
            System.out.println("3.Exit");
            choice = input.nextInt();

            if (choice == 1)
                super.Edit();
            else if (choice == 2)
            {
                while (!isDone)
                {
                    System.out.println("1.Add quiz question");
                    System.out.println("2.Remove quiz question");
                    System.out.println("3.Edit quiz question");
                    System.out.println("4.Exit");
                    choice = input.nextInt();
                    input.nextLine();
                    if (choice == 1)
                    {
                        if(mQuiz.AddQuestion())
                            System.out.println("Successfully added quiz question");
                        else
                            System.out.println("ERROR: there was an issue trying to add that question");
                    }
                    else if (choice == 2)
                    {
                        if(mQuiz.Remove())
                            System.out.println("Successfully removed quiz question");
                        else
                            System.out.println("ERROR: there was an issue trying to remove that question");
                    }
                    else if (choice == 3)
                    {
                        if(mQuiz.Edit())
                            System.out.println("Successfully edited quiz question");
                        else
                            System.out.println("ERROR: there was an issue trying to edit that question");
                    }
                    else
                        isDone = true;
                }
            }
            else
                readyToExit = true;

        //while user is still editing
        }while(!readyToExit);
        return 1;
    }
}
