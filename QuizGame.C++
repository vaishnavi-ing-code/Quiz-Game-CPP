// QUIZ GAME
// A console-based quiz game developed using c++
// FEATURES:
// - Multiple quiz categories
// - Three difficulty levels
// - Random questions
// - Score and grade calculation
// - File handling
// AUTHOR: Vaishnavi Mishra

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <random>
#include <cctype>

using namespace std;

// CONSTANTS
// Number of questions asked in one quiz
const int QUESTIONS_PER_QUIZ = 10;

// QUESTION CLASS
// Stores all information related to one question.
class Question
{
    public:

    string category;
    string difficulty;
    string question;
    
    string optionA;
    string optionB;
    string optionC;
    string optionD;

    char correctAnswer;

    // Constructor to initialize a question
    Question( string cat, string diff, string ques,
             string a, string b, string c, string d, char answer )

  { 
    category = cat; difficulty = diff; question = ques;
    optionA = a; optionB = b; optionC = c; optionD = d;
    correctAnswer = answer;  
  }

  // Display the question and all four optioins
  void display() const
  {
    cout << "\n" << question << "\n";
    
    cout << "A." << optionA << "\n";
    cout << "B." << optionB << "\n";
    cout << "C." << optionC << "\n";
    cout << "D." << optionD << "\n";
  }

};

// STRING UTILITY FUNCTIONS
// Removes unnecessary spaces and newline characters form the beginning and end of a string.
string trim(string text)
{
    size_t start = text.find_first_not_of(" \t\r\n");
    size_t end = text.find_last_not_of(" \t\r\n");

    if(start == string::npos)
    {
        return "";
    }

    return text.substr(start, end - start + 1);
}

// Converts a string into lowercase. This is useful when comparing category and difficulty name.
string toLowerCase(string text)
{
    for(char &c : text)
    {
        c = static_cast<char>(tolower(static_cast<unsigned char>(c)));
    }
    return text;
}


// LOAD QUESTIONS FROM FILE
// Reads questions from questions.txt and creates question objects from the data stored in the file.
vector<Question> loadQuestions()
{
    vector<Question> questions;
    ifstream file("questions.txt");

    //Check whether the file was opened successfully.
    if(! file)
    {
        cout<< "\nError : questions.txt could nat be opened.\n";
        return questions;
    }

    string line;
    // Read the file line by line.
    while(getline(file, line))
    {
        // Ignore empty lines.
        if(line.empty())
        {
            continue;
        }

        stringstream ss(line);

      string category;
      string difficulty;
      string question;
    
      string optionA;
      string optionB;
      string optionC;
      string optionD;

      string answer;

      //Read each field separated by '|'.
      getline(ss, category, '|');
      getline(ss, difficulty, '|');
      getline(ss, question, '|');

      getline(ss, optionA, '|');
      getline(ss, optionB, '|');
      getline(ss, optionC, '|');
      getline(ss, optionD, '|');

      getline(ss, answer, '|');

      // Ignore incomplete question records.
      if(category.empty() || difficulty. empty() || question. empty() ||
         optionA. empty() || optionB. empty() || optionC. empty() ||
         optionD. empty() || answer. empty() )
         {
            continue;
         }
        answer = trim(answer);

         // Convert the correct answer to uppercase.
         char correctAnswer = static_cast<char>(toupper (static_cast<unsigned char>(answer[0])));

         // Create and store the Question object.
         questions.emplace_back(trim(category), trim(difficulty), trim(question), 
                                trim(optionA), trim(optionB), trim(optionC),
                                trim(optionD), correctAnswer);
    }
    file.close();
    return questions;
}

// CATEGORY SELECTION
// Allows the player to select a quiz category.
string chooseCategory()
{
    int choice;
    
    while (true)
    {
     cout<<"\n===========================================================================\n";
     cout<<"                     SELECT CATEGORY\n";
     cout<<"=============================================================================\n";

     cout<<"1. Mathematics\n";
     cout<<"2. Science\n";
     cout<<"3. Programming\n";
     cout<<"4. General Knowledge\n";

     cout<<"\nEnter your choice: ";
     cin >> choice;

     // Handle non-numeric input
     if(cin.fail())
     {
        cin.clear();
        cin.ignore(10000,'\n');

        cout<<"\nPlease enter a valid number.\n";
        continue;
     }

     cin.ignore(10000,'\n');
     
     if(choice == 1)
     {
        return "Mathematics";
     }

      if(choice == 2)
     {
        return "Science";
     }

      if(choice == 3)
     {
        return "Programming";
     }

      if(choice == 4)
     {
        return "General Knowledge";
     }

     cout<<"\nInvalid category. Please try again.\n";
   }
    
}

// DIFFICULTY  SELECTION
// Allows the player to select the quiz difficulty.
string chooseDifficulty()
{
    int choice;

    while(true)
    {
        cout<<"\n==========================================================================\n";
        cout<<"              SELECT DIFFICULTY\n";
        cout<<"============================================================================\n";

        cout<<"1. Easy\n";
        cout<<"2. Medium\n";
        cout<<"3. Hard\n";

        cout<<"\nEnter your choice: ";
        cin >> choice;

       // Handle non-numeric input
     if(cin.fail())
     {
        cin.clear();
        cin.ignore(10000,'\n');

        cout<<"\nPlease enter a valid number.\n";
        continue;
     }

     cin.ignore(10000,'\n');

     if(choice == 1)
     {
        return "Easy";
     }

     if(choice == 2)
     {
        return "Medium";
     }

     if(choice == 3)
     {
        return "Hard";
     }

     cout<<"\nInvalid difficulty. Pleasa try again.\n";
    }
}

// GET ANSWER
// Accepts only A,B,C or D as a valid answer.
char getAnswer()
{
    char answer;

    while(true)
    {
        cout<<"\nEnter your answer (A/B/C/D): ";
        cin >> answer;

        // Handle invalid input
        if(cin.fail())
     {
        cin.clear();
        cin.ignore(10000,'\n');

        cout<<"\nInvalid input.\n";
        continue;
     }

     cin.ignore(10000,'\n');

     // Convert lowercase input to uppercase.
     answer = static_cast<char>(toupper(static_cast<unsigned char>(answer)));

     // Check wheather the answer is valid.
    if(answer == 'A' || answer == 'B' || answer == 'C' || answer == 'D' )
     {
        return answer;
     }
     cout<<"\nPlease enter only A,B,C or D.\n";
    }
}

// CALCULATE GRADE
// Determines the grade according to the percentage.
char calculateGrade(float percentage)
{
    if(percentage >= 90)
    {
        return 'A';
    }

    if(percentage >= 75)
    {
        return 'B';
    }

    if(percentage >= 50)
    {
        return 'C';
    }

    return 'F';

}

// SAVE SCORE
// save the player's result in scores.txt
void saveScore(string playerName, string category, string difficulty, 
                int score)
    {
        // Open the file in append mode so previous scores are not deleted.
        ofstream file("scores.txt", ios::app);

        if(!file)
        {
            cout<<"\nUnable to save score.\n";
            return;
        }

        // Store the score using | as a separator.
        file<<playerName<<"|" <<category<<"|" <<difficulty<<"|" <<score <<"\n";
        file.close();
    }            

    // DISPLAY HIGH SCORES
    // Reads save scores and displays the top 10 scores.
    void displayHighScores()
    {
        ifstream file("scores.txt");

        // If the file does not exist, there are no scores yet.
        if(!file)
        {
            cout<<"\nNo high scores available yet.\n";
            return;
        }

        // Temporary structure for storing score information.
        struct Score
        {
            string name;
            string category;
            string difficulty;
            int score;
        };

        vector<Score> scores;
        string line;

        // Read each saved score.
        while(getline(file, line))
        {
            if(line.empty())
            {
                continue;
            }

            stringstream ss(line);

            string name;
            string category;
            string difficulty;
            string scoreText;

            getline(ss, name, '|');
            getline(ss, category, '|');
            getline(ss, difficulty, '|');
            getline(ss, scoreText, '|');

            // Ignore incomplete records.
            if(name.empty() || category.empty() || difficulty.empty() || scoreText.empty())
            {
                continue;
            }

            try
            {
                int score = stoi(scoreText);

                scores.push_back({
                    name, category, difficulty, score
                });
            }

            catch(...)
            {
                // Ignore invalid score records.
                continue;
            }

        }

        file.close();

        if(scores.empty())
        {
            cout<<"\nNo high scores available yet.\n";
            return;
        }

        // Sort scores from highest to lowest.
        sort(scores.begin(), scores.end(), 
             [](const Score &a, const Score &b)
            {
                return a.score > b.score ;
            });

            cout<<"\n=====================================================================\n";
            cout<<"            HIGH SCORES\n";
            cout<<"========================================================================\n";

            // Display a maximum of 10 high scores.
            int limit = min(10, static_cast<int>(scores.size()));

            for(int i = 0; i < limit; i++)
            {
                cout << i + 1 << "."
                     << scores[i].name << "-"
                     << scores[i].score << "/"
                     << QUESTIONS_PER_QUIZ << "("
                     << scores[i].category << ","
                     << scores[i].difficulty << ")\n";
            }
    }

    // START QUIZ
    // Runs one complete quiz session.
    void startQuiz(const vector<Question> &allQuestions, string playerName)
    {
        // Ask the player to select category and difiiculty.
        string category = chooseCategory();
        string difficulty = chooseDifficulty();

        // Store questions matching the player's selection.
        vector<Question> selectedQuestions;

        // Search through all available questions.
        for(const Question &q : allQuestions)
        {
            if(toLowerCase(q.category) == toLowerCase(category)
                && toLowerCase(q.difficulty) == toLowerCase(difficulty) )
                {
                    selectedQuestions.push_back(q);
                }
        }

        // At least 10 questions are required for one completed quiz.
        if(selectedQuestions.size() < QUESTIONS_PER_QUIZ)
        {
            cout << "\nNot enough questions available!\n";
            cout<<"This category and difficulty need at least"
                << QUESTIONS_PER_QUIZ
                << " questions.\n";
           return;
        }

        // Create a random number generator.
        random_device rd;
        mt19937 generator(rd());

        // Shuffle the selected questions. This makes the order different for each quiz.
        shuffle(selectedQuestions.begin(),
                 selectedQuestions.end(),
                generator );
                
        int score = 0;

        cout << "\n===================================================================\n";
        cout << "             QUIZ STARTED\n";
        cout << "=====================================================================\n";

        cout << "Player     :" << playerName << "\n";
        cout << "Category   :" << category << "\n";
        cout << "Difficulty :" << difficulty << "\n";

        // Ask exactly 10 questions.
        // Because the vector was shuffles first, the questions are selected ramdomly without reprtition.
        for(int i = 0; i < QUESTIONS_PER_QUIZ; i++)
        {
            cout << "\n------------------------------------------------------\n";
            cout << "Question" << i + 1 << "/"
                 << QUESTIONS_PER_QUIZ << "\n";
            
            cout <<"----------------------------------------------------------\n";
            
            // Display current question.
            selectedQuestions[i].display();
            // Get the player's answer.
            char answer = getAnswer();

            // Check the answer.
            if(answer == selectedQuestions[i].correctAnswer)
            {
                cout << "\nCorrect!\n";
                score++;
            }
            else
            {
                cout << "Incorrect!\n";
                cout << "Correct answer: " << selectedQuestions[i].correctAnswer << "\n";

            }
        }

        // RESULT CALCULATION
        float percentage = ( static_cast<float>(score)/ QUESTIONS_PER_QUIZ ) *100;
        char grade = calculateGrade(percentage);

        // DISPLAY FINAL RESULT
        cout << "\n=============================================================\n";
        cout << "                     QUIZ RESULT\n";
        cout << "===============================================================\n";

        cout << "Player      :" << playerName << "\n";
        cout << "Category    :" << category << "\n";
        cout << "Difficulty  :" << difficulty << "\n";
        cout << "\nCorrect    :" << score << "\n";
        cout << "Incorrect   :" << QUESTIONS_PER_QUIZ - score << "\n";
        cout << "Score       :" << score << "/" << QUESTIONS_PER_QUIZ << "\n";
        cout << "Percentage  :" << percentage << "%" << "\n";
        cout << "Grade       :" << grade << "\n";

        cout << "==========================================================\n";

        // Save the result to high-score file.
        saveScore(playerName, category, difficulty, score);
        cout << "\nYour score has been saved!\n";

    }

    // MAIN FUNCTION
    //Controls the main menu and overall program flow.
    int main()
    {
        // Load all questions from questions.txt.
        vector<Question> questions = loadQuestions();

        // Stop the program if no questions were loaded.
        if(questions.empty())
        {
            cout << "\nNo questions founf.\n";
            cout << "Please check your questions.txt file.\n";
            return 0;
        }

        // PLAYER INFORMATION
        string playerName;
        cout << "=============================================================\n";
        cout << "            QUIZ MASTER\n";
        cout << "=============================================================\n";

        cout << "\nEnter your name: ";
        getline(cin, playerName);

        // Use "Player" if the name is left empty.
        if(playerName.empty())
        {
            playerName = "Player";
        }
        int choice = 0;

        // MAIN MENU
        do
        {
         cout << "\n===========================================================\n";
         cout << "                       MAIN MENU\n";
         cout << "==============================================================\n";
         
         cout << "1. Start Quiz\n";
         cout << "2. View High Scores\n";
         cout << "3. Exit\n";

         cout << "\nEnter your choice: ";
         cin >> choice;

         // Handle non-numeric menu input.
         if(cin.fail())
         {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "\nInvalid input. Please enter a number.\n";
            continue;
         }

         cin.ignore(10000, '\n');
         // Start a new quiz.
         if(choice == 1)
         {
            startQuiz(questions, playerName);
         }

         // Display saved high scores.
         else if(choice == 2)
         {
            displayHighScores();
         }

         // Exit the program.
         else if(choice == 3)
         {
            cout << "\nThank you for playing Master!\n";
            cout << "Goodbye!\n";
         }

         // Handle invalid menu choices.
         else
         {
            cout << "\nIvalid choice. Please try again. \n";
         }
        }
         while (choice != 3);
         return 0;
        
    }