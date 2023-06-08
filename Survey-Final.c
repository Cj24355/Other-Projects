#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_QUESTIONS 5
#define MAX_QUESTION_LENGTH 100
#define MAX_ANSWER_LENGTH 100

void getUsername(char username[]);
void createQuestions(char questions[MAX_QUESTIONS][MAX_QUESTION_LENGTH]);
void answerQuestions(const char questions[MAX_QUESTIONS][MAX_QUESTION_LENGTH], char answers[MAX_QUESTIONS][MAX_ANSWER_LENGTH]);
void reviewAnswers(const char questions[MAX_QUESTIONS][MAX_QUESTION_LENGTH], const char answers[MAX_QUESTIONS][MAX_ANSWER_LENGTH]);
void generateReviewFile(const char questions[MAX_QUESTIONS][MAX_QUESTION_LENGTH], const char answers[MAX_QUESTIONS][MAX_ANSWER_LENGTH], const char username[]);
int checkQuestionsCreated(int hasQuestions);

int main()
{
    int choice;
    char questions[MAX_QUESTIONS][MAX_QUESTION_LENGTH];
    char answers[MAX_QUESTIONS][MAX_ANSWER_LENGTH];
    char username[50];
    int hasQuestions = 0;

    printf("Welcome! Please enter your username first:\n");
    getUsername(username);
    printf("Hello and welcome, %s!\n", username);

    while (1)
    {
        printf("\nMenu:\n");
        printf("1. Create questions\n");
        printf("2. Answer questions\n");
        printf("3. Review answers\n");
        printf("4. Generate review file\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        if (choice == 1)
        {
            if (hasQuestions)
            {
                char overwrite;
                printf("Existing questions found. Do you want to overwrite them? (y/n): ");
                scanf(" %c", &overwrite);

                if (overwrite == 'n' || overwrite == 'N')
                {
                    printf("Question creation canceled.\n");
                    continue;
                }
            }

            createQuestions(questions);
            hasQuestions = 1;
            printf("\nQuestions created successfully!\n");
        }
        else if (choice == 2)
        {
            if (!checkQuestionsCreated(hasQuestions))
            {
                continue;
            }
            answerQuestions(questions, answers);
        }
        else if (choice == 3)
        {
            if (!checkQuestionsCreated(hasQuestions))
            {
                continue;
            }
            reviewAnswers(questions, answers);
        }
        else if (choice == 4)
        {
            if (!checkQuestionsCreated(hasQuestions))
            {
                continue;
            }
            generateReviewFile(questions, answers, username);
            printf("\nReview file generated successfully!\n");
        }
        else if (choice == 5)
        {
            printf("Exiting the program. Goodbye, %s!\n", username);
            break;
        }
        else
        {
            printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}

void getUsername(char username[])
{
    printf("Username: ");
    scanf("%s", username);
}

void createQuestions(char questions[MAX_QUESTIONS][MAX_QUESTION_LENGTH])
{
    int i;

    printf("\n--- Question Creation ---\n");
    printf("Enter your questions:\n");

    for (i = 0; i < MAX_QUESTIONS; i++)
    {
        printf("Question %d: ", i + 1);
        scanf(" %[^\n]s", questions[i]);
    }
}

void answerQuestions(const char questions[MAX_QUESTIONS][MAX_QUESTION_LENGTH], char answers[MAX_QUESTIONS][MAX_ANSWER_LENGTH])
{
    int i;

    printf("\n--- Question Answering ---\n");
    printf("Answer the following questions:\n");

    for (i = 0; i < MAX_QUESTIONS; i++)
    {
        printf("Question %d: %s\n", i + 1, questions[i]);
        printf("Answer: ");
        scanf(" %[^\n]s", answers[i]);
    }

    printf("\nAnswers recorded successfully!\n");
}

void reviewAnswers(const char questions[MAX_QUESTIONS][MAX_QUESTION_LENGTH], const char answers[MAX_QUESTIONS][MAX_ANSWER_LENGTH])
{
    int i;

    printf("\n--- Review Answers ---\n");
    printf("Here are the questions and answers:\n");

    for (i = 0; i < MAX_QUESTIONS; i++)
    {
        printf("Question %d: %s\n", i + 1, questions[i]);
        printf("Answer: %s\n", answers[i]);
    }
}

void generateReviewFile(const char questions[MAX_QUESTIONS][MAX_QUESTION_LENGTH], const char answers[MAX_QUESTIONS][MAX_ANSWER_LENGTH], const char username[])
{
    int i;
    FILE *file;

    file = fopen("review.txt", "w");

    if (file == NULL)
    {
        printf("Error opening the file.\n");
        return;
    }

    fprintf(file, "--- Review Answers ---\n");
    fprintf(file, "Username: %s\n", username);
    fprintf(file, "Here are the questions and answers:\n");

    for (i = 0; i < MAX_QUESTIONS; i++)
    {
        fprintf(file, "Question %d: %s\n", i + 1, questions[i]);
        fprintf(file, "Answer: %s\n", answers[i]);
    }

    fclose(file);
}

int checkQuestionsCreated(int hasQuestions)
{
    if (!hasQuestions)
    {
        printf("No questions created. Please create questions first.\n");
        return 0;
    }
    return 1;
}
