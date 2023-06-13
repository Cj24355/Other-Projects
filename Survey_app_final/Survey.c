#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
#include <conio.h>
#define CLEAR_SCREEN "cls"
#else
#include <stdio_ext.h>
#include <unistd.h>
#define CLEAR_SCREEN "clear"
#endif

#define MAX_QUESTION_LENGTH 100
#define MAX_ANSWER_LENGTH 100

void clearScreen();
void getUsername(char username[]);
void createQuestions(char ***questions);
void answerQuestions(char **questions, char ***answers);
void reviewAnswers(char **questions, char **answers);
void generateReviewFile(char **questions, char **answers, const char username[]);
int checkQuestionsCreated(char **questions);

int main()
{
    int choice;
    char **questions = NULL;
    char **answers = NULL;
    char username[50];
    int hasQuestions = 0;

    printf("Welcome! Please enter your username first:\n");
    getUsername(username);
    printf("Hello and welcome, %s!\n", username);

    while (1)
    {
        clearScreen();

        printf("Menu:\n");
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
                else
                {
                    // Free the memory allocated for existing questions and answers
                    for (int i = 0; questions[i] != NULL; i++)
                    {
                        free(questions[i]);
                        free(answers[i]);
                    }
                    free(questions);
                    free(answers);
                }
            }

            createQuestions(&questions);
            hasQuestions = 1;
            printf("\nQuestions created successfully!\n");
        }
        else if (choice == 2)
        {
            if (!checkQuestionsCreated(questions))
            {
                continue;
            }
            answerQuestions(questions, &answers);
        }
        else if (choice == 3)
        {
            if (!checkQuestionsCreated(questions))
            {
                continue;
            }
            reviewAnswers(questions, answers);
        }
        else if (choice == 4)
        {
            if (!checkQuestionsCreated(questions))
            {
                continue;
            }
            generateReviewFile(questions, answers, username);
            printf("\nReview file generated successfully!\n");
        }
        else if (choice == 5)
        {
            // Free the memory allocated for questions and answers
            for (int i = 0; questions[i] != NULL; i++)
            {
                free(questions[i]);
                free(answers[i]);
            }
            free(questions);
            free(answers);

            printf("Exiting the program. Goodbye, %s!\n", username);
            break;
        }
        else
        {
            printf("Invalid choice. Please try again.\n");
        }

        printf("Press any key to continue...");
#ifdef _WIN32
        _getch();
#else
        __fpurge(stdin);
        getchar();
#endif
    }

    return 0;
}

void clearScreen()
{
    system(CLEAR_SCREEN);
}

void getUsername(char username[])
{
    printf("Username: ");
    scanf("%s", username);
}

void createQuestions(char ***questions)
{
    int i = 0;

    printf("\n--- Question Creation ---\n");
    printf("Enter your questions (enter 'done' to finish):\n");

    *questions = (char **)malloc(sizeof(char *));

    while (1)
    {
        if (i > 0 && i % 5 == 0)
        {
            char addMoreChoice;
            printf("Do you want to add more questions? (y/n): ");
            scanf(" %c", &addMoreChoice);

            if (addMoreChoice == 'n' || addMoreChoice == 'N')
            {
                printf("Question creation completed.\n");
                break;
            }
            else
            {
                *questions = (char **)realloc(*questions, (i + 1) * sizeof(char *));
            }
        }

        (*questions)[i] = (char *)malloc(MAX_QUESTION_LENGTH * sizeof(char));

        printf("Question %d: ", i + 1);
        scanf(" %[^\n]s", (*questions)[i]);

        if (strcmp((*questions)[i], "done") == 0)
            break;

        i++;
        *questions = (char **)realloc(*questions, (i + 1) * sizeof(char *));
    }

    (*questions)[i] = NULL;
}

void answerQuestions(char **questions, char ***answers)
{
    int i = 0;

    printf("\n--- Question Answering ---\n");
    printf("Answer the following questions:\n");

    *answers = (char **)malloc(sizeof(char *));

    while (questions[i] != NULL)
    {
        *answers = (char **)realloc(*answers, (i + 1) * sizeof(char *));
        (*answers)[i] = (char *)malloc(MAX_ANSWER_LENGTH * sizeof(char));

        printf("Question %d: %s\n", i + 1, questions[i]);
        printf("Answer: ");
        scanf(" %[^\n]s", (*answers)[i]);

        i++;
        *answers = (char **)realloc(*answers, (i + 1) * sizeof(char *));
    }

    (*answers)[i] = NULL;

    printf("\nAnswers recorded successfully!\n");
}

void reviewAnswers(char **questions, char **answers)
{
    int i = 0;

    printf("\n--- Review Answers ---\n");
    printf("Here are the questions and answers:\n");

    while (questions[i] != NULL)
    {
        printf("Question %d: %s\n", i + 1, questions[i]);
        printf("Answer: %s\n", answers[i]);

        i++;
    }
}

void generateReviewFile(char **questions, char **answers, const char username[])
{
    int i = 0;
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

    while (questions[i] != NULL)
    {
        fprintf(file, "Question %d: %s\n", i + 1, questions[i]);
        fprintf(file, "Answer: %s\n", answers[i]);

        i++;
    }

    fclose(file);
}

int checkQuestionsCreated(char **questions)
{
    if (questions == NULL || questions[0] == NULL)
    {
        printf("No questions created. Please create questions first.\n");
        return 0;
    }
    return 1;
}
