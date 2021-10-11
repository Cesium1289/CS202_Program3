//NAME:Carson Hansen
//FILE NAME:Quiz.java
//PURPOSE:Define what a quiz is. It has questions the user can add and remove
import java.io.Serializable;
import java.util.ArrayList;
import java.util.Scanner;

public class Quiz implements Serializable
{
    private ArrayList<Question> mQuestions;
    private static Scanner input = new Scanner(System.in);

    //Default constructor
    public Quiz()
    {
        mQuestions = new ArrayList<Question>();
    }

    //Lets user add a question to the quiz. Returns true
    //if quiz was added. False if it was not
    public boolean AddQuestion()
    {
        Question newQuestion;
        int choice = 0;
        String question;

        System.out.println("Which kind of question will this be?");
        System.out.println("1.True of False");
        System.out.println("2.Multiple Choice");
        System.out.println("3.Fill in the Blank");
        choice = input.nextInt();

        input.nextLine();
        System.out.println("Enter in the question");
        question = input.nextLine();

        if(choice == 1)
            newQuestion = new TrueOrFalseQuestion(question);
        else if(choice ==2)
            newQuestion = new MultipleChoiceQuestion(question);
        else
            newQuestion = new FillInBlankQuestion(question);

        newQuestion.Create();

        //check if question was successfully added
        if(mQuestions.add(newQuestion))
        {
            mQuestions.trimToSize();
            return true;
        }
        else
            return false;
    }

    //Lets user remove a question from the quiz. Returns
    //true if quiz was removed, false if it was not
    public boolean Remove()
    {
        int toRemove = 0;
        int index =1;
        int size = mQuestions.size();

        //display the questions to the user
        for(Question mQuestions: mQuestions)
        {
            System.out.print(index +". ");
            mQuestions.Display();
            ++index;

        }

        System.out.println("Enter the question number of the question you want to remove");
        toRemove = input.nextInt();

        if(toRemove > size || toRemove < 1)
            return  false;
        else
        {
            //remove the index
            mQuestions.remove(toRemove-1);

            //trim array to correct size
            mQuestions.trimToSize();
            return true;
        }
    }

    //Displays the questions in the quiz.
    //Returns the number of quizzes displayed
    public int Display()
    {
        int displayed =0;

        if(mQuestions.isEmpty())
            return 0;

        //loop though questions to display
        for(Question mQuestions: mQuestions)
        {
            System.out.print(displayed+1 +". ");
            mQuestions.Display();
            System.out.println();
            ++displayed;
        }

        //display(mQuestions,index,displayed);
        return  displayed;
    }

    //Lets user edit the question. Returns true
    //if data was edited, false if it was not
    public boolean Edit()
    {
        Question toEdit;
        int choice =0;
        int displayed =0;

        //loop though the questions and display them
        for(Question mQuestions: mQuestions)
        {
            System.out.print(displayed+1 +". ");
            mQuestions.DisplayQuestion();
            System.out.println();
            ++displayed;
        }

        System.out.println("Enter question number you want to edit");
        choice = input.nextInt();

        //get its current index. remove it. put it back in teh right index
        if(choice > mQuestions.size() || choice < 1)
            return false;
        toEdit = mQuestions.get(choice-1);
        return toEdit.Edit();

    }
}
