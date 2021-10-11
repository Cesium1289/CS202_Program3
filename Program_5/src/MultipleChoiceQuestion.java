//NAME:Carson Hansen
//FILE NAME:MultipleChoiceQuestion.java
//PURPOSE:Create and define multiple choice questions for the video quiz
import java.util.ArrayList;

public class MultipleChoiceQuestion extends  Question
{
    private ArrayList<String> mChoice;

    //Default constructor
    public  MultipleChoiceQuestion()
    {
        super();
        mChoice = new ArrayList<String>();
    }

    //Argument constructor
    public MultipleChoiceQuestion(String question)
    {
        super(question);
        mChoice = new ArrayList<String>();
    }

    //Allows user to create a question
    public int Create()
    {
        int choice =1;
        String mQuestionChoice = null;
        super.Create();

        //while user wants to keep adding potential correct answers to the question
        while(choice == 1)
        {
            System.out.println("Enter a possible answer");
            mQuestionChoice = input.nextLine();
            mChoice.add(mQuestionChoice);

            System.out.println("Would you like to enter another option?");
            System.out.println("1.Yes");
            System.out.println("2.No");
            choice = input.nextInt();
            input.nextLine();
        }

        //trim answer choices to correct size
        mChoice.trimToSize();

        //display the potential answers to the user
        for(int i =0; i < mChoice.size();++i)
        {
            System.out.println(i+1 +". " + mChoice.get(i));
        }

        //ask user what the correct answer is
        System.out.println("Enter the number that has the correct answer");
        mQuestionChoice = input.nextLine();
        mCorrectAnswer = mQuestionChoice;

        return 1;
    }

    //Display the question. It will return 0 if there was no question
    //to display. 1 if it displays the question
    public int Display()
    {
        //check if there is a question to show
        if(mQuestion == null)
            return 0;
        System.out.println("-_-_-_-Multiple Choice-_-_-_-_-");
        System.out.println(mQuestion);

        for(int i =0; i < mChoice.size();++i)
            System.out.println(i+1 +". " + mChoice.get(i));
        System.out.println("Correct answer: " + mCorrectAnswer);
        return 1;
    }

    //Allows the user to edit the videos data
    public boolean Edit()
    {
        boolean isDone = false;
        int choice = 0;
        int toRemove = 0;
        String question;

        //while user is still wanting to edit the questions
        while (!isDone)
        {
            System.out.println("1.Edit Question");
            System.out.println("2.Edit Correct Answer");
            System.out.println("3.Add an option");
            System.out.println("4.Remove an option");
            System.out.println("5.Exit");
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
                //display the potential answers to the user
                for(int i =0; i < mChoice.size();++i)
                    System.out.println(i+1 +". " + mChoice.get(i));

                System.out.println("Enter the number of the correct answer.");
                mCorrectAnswer = input.nextLine();
                System.out.println("Successfully updated.");
            }
            else if(choice == 3)
            {
                System.out.println("Enter another possible answer.");
                question = input.nextLine();
                if(mChoice.add(question))
                    System.out.println("Successfully updated.");
                else
                    System.out.println("There was an issue adding the question");
            }
            else if(choice == 4)
            {
                //display the potential answers to the user
                for(int i =0; i < mChoice.size();++i)
                    System.out.println(i+1 +". " + mChoice.get(i));

                System.out.println("Enter the number of the answer you want to remove.");
                toRemove = input.nextInt();
                mChoice.remove(toRemove-1);
                System.out.println("Successfully updated.");

            }
            isDone = true;
        }
        return true;
    }
}
