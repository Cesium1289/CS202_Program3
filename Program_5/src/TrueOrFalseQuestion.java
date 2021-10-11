//NAME:Carson Hansen
//FILE NAME:TrueOrFalseQuestion.java
//PURPOSE:Create and define true or false questions for the video quiz
public class TrueOrFalseQuestion extends  Question
{

    //Default constructor
    public TrueOrFalseQuestion()
    {
        super();
    }

    //Argument constructor
    public TrueOrFalseQuestion(String question)
    {
        super(question);
    }

    //Allow input to create a true or false question
    public int Create()
    {
        //call super create
        super.Create();

        //get user input
        System.out.println("What is the correct answer?");
        System.out.println("1.True");
        System.out.println("2.False");
        mCorrectAnswer = input.nextLine();
        return 1;
    }

    //Displays the question with question with the options and correct answer.
    //Returns 0 if there is no question true if there is
    public int Display()
    {
        //check if there is a question to show
        if(mQuestion == null)
            return 0;
        System.out.println("-_-_-_-True or False-_-_-_-_-");
        System.out.println("Question: " + mQuestion);
        System.out.println("1.True");
        System.out.println("2.False");
        System.out.println("Correct answer: " + mCorrectAnswer);
        return 1;
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
            }
            else if (choice == 2)
            {
                System.out.println(mQuestion);
                System.out.println("1.True");
                System.out.println("2.False");
                System.out.println("Enter the number of the correct answer.");
                mCorrectAnswer = input.nextLine();
                System.out.println("Successfully updated.");
            }
            else
                isDone = true;
        }
        return true;
    }
}
