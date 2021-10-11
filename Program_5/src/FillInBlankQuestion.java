//NAME:Carson Hansen
//FILE NAME:FillInBlankQuestion.java
//PURPOSE:Create and define fill in the blank questions for the video quiz
public class FillInBlankQuestion extends Question
{
    //Default constructor
    public FillInBlankQuestion()
    {
        super();
    }

    //Argument constructor
    public FillInBlankQuestion(String question)
    {
        super(question);
    }

    //Allow user to create a fill in the blank question
    public int Create()
    {
        System.out.println("Enter the correct answer");
        mCorrectAnswer = input.nextLine();
        return 1;
    }

    //Displays the question. Returns 0 if there is no question to display
    //Returns 1 if the question displayed
    public int Display()
    {
        //check if there is a question to show
        if(mQuestion == null)
            return 0;
        System.out.println("-_-_-_-Fill in the Blank-_-_-_-_-");
        System.out.println("Question: " + mQuestion);
        System.out.println("Correct answer: " + mCorrectAnswer);
        return 1;
    }

    //Allows the user to edit the videos data. Returns true
    //user is done editing the question
    public boolean Edit()
    {
        boolean isDone = false;
        int choice = 0;

        //while user is wanting to edit
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
                System.out.println("Enter the correct answer.");
                mCorrectAnswer = input.nextLine();
                System.out.println("Successfully updated.");
            } else
                isDone = true;
        }
        return true;
    }
}