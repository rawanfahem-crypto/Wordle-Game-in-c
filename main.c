#include <stdio.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_ATTEMPTS 6
#define WORD_LENGTH 5
#define MAX_WORDS 100

// Validate input
bool isValidInput(const char* input)
{
    if (strlen(input) != WORD_LENGTH)
        return false;

    for (int i = 0; i < WORD_LENGTH; i++)
    {
        if (!isalpha(input[i]))
            return false;
    }

    return true;
}

// Feedback system
void provideFeedback(const char* secretWord,
                     const char* guess)
{
    printf("Feedback: ");

    for (int i = 0; i < WORD_LENGTH; i++)
    {
        char g = toupper(guess[i]);

        // Correct letter and correct position
        if (g == toupper(secretWord[i]))
        {
            printf("[Green %c] ", g);
        }
        else
        {
            int found = 0;

            // Letter exists in another position
            for (int j = 0; j < WORD_LENGTH; j++)
            {
                if (g == toupper(secretWord[j]))
                {
                    found = 1;
                    break;
                }
            }

            if (found)
                printf("[Yellow %c] ", g);
            else
                printf("[Grey %c] ", g);
        }
    }

    printf("\n");
}

// Store time using pointer array
void storeGuessTime(double *timeArray[],
                    int attempt,
                    double duration)
{
    timeArray[attempt] =
        (double*)malloc(sizeof(double));

    if (timeArray[attempt] != NULL)
    {
        *(timeArray[attempt]) = duration;
    }
}

int main()
{
    // Array to store words from file
    char words[MAX_WORDS][WORD_LENGTH + 1];

    int wordCount = 0;

    // Open words file
    FILE *file = fopen("words.txt", "r");

    if (file == NULL)
    {
        printf("Could not open words.txt file.\n");
        return 1;
    }

    // Read words from file
    while (fscanf(file, "%5s", words[wordCount]) == 1)
    {
        // Convert word to uppercase
        for (int i = 0; i < WORD_LENGTH; i++)
        {
            words[wordCount][i] =
                toupper(words[wordCount][i]);
        }

        // Make sure word length is 5
        if (strlen(words[wordCount]) == WORD_LENGTH)
        {
            wordCount++;
        }

        if (wordCount >= MAX_WORDS)
            break;
    }

    fclose(file);

    // Check if file is empty
    if (wordCount == 0)
    {
        printf("No valid words found.\n");
        return 1;
    }

    // Random generator
    srand(time(NULL));

    // Select random word
    char secretWord[WORD_LENGTH + 1];

    strcpy(secretWord,
           words[rand() % wordCount]);

    // Arrays for guesses and times
    char guesses[MAX_ATTEMPTS]
                [WORD_LENGTH + 1];

    double *guessTimes[MAX_ATTEMPTS];

    // Initialize pointers
    for (int i = 0; i < MAX_ATTEMPTS; i++)
    {
        guessTimes[i] = NULL;
    }

    int currentAttempt = 0;

    bool hasWon = false;

    printf("===== WORDLE GAME =====\n");

    while (currentAttempt < MAX_ATTEMPTS
           && !hasWon)
    {
        char currentGuess[WORD_LENGTH + 1];

        printf("\nAttempt %d/%d\n",
               currentAttempt + 1,
               MAX_ATTEMPTS);

        printf("Enter a 5-letter word: ");

        // Start timer
        time_t start, end;

        time(&start);

        scanf("%5s", currentGuess);

        time(&end);

        // Calculate time
        double timeSpent =
            difftime(end, start);

        // Validate input
        if (!isValidInput(currentGuess))
        {
            printf("Invalid input! "
                   "Please enter exactly 5 letters.\n");

            continue;
        }

        // Store time
        storeGuessTime(
            guessTimes,
            currentAttempt,
            timeSpent
        );

        // Convert guess to uppercase
        for (int i = 0; i < WORD_LENGTH; i++)
        {
            guesses[currentAttempt][i] =
                toupper(currentGuess[i]);
        }

        guesses[currentAttempt]
               [WORD_LENGTH] = '\0';

        // Show feedback
        provideFeedback(
            secretWord,
            guesses[currentAttempt]
        );

        printf("Time: %.2f seconds\n",
               timeSpent);

        // Check win
        if (strcmp(
                guesses[currentAttempt],
                secretWord) == 0)
        {
            hasWon = true;
            break;
        }

        currentAttempt++;
    }

    // Final result
    if (hasWon)
    {
        printf("\nYou Win!\n");
        printf("Secret Word: %s\n",
               secretWord);
    }
    else
    {
        printf("\nYou Lost!\n");
        printf("Secret Word was: %s\n",
               secretWord);
    }

    // Summary
    printf("\n===== SUMMARY =====\n");

    double totalTime = 0;

    int attemptsShown =
        hasWon ?
        currentAttempt + 1 :
        MAX_ATTEMPTS;

    for (int i = 0; i < attemptsShown; i++)
    {
        if (guessTimes[i] != NULL)
        {
            printf("Attempt %d [%s] "
                   "= %.2f sec\n",
                   i + 1,
                   guesses[i],
                   *(guessTimes[i]));

            totalTime +=
                *(guessTimes[i]);

            // Free memory
            free(guessTimes[i]);
        }
    }

    printf("Total Time: %.2f sec\n",
           totalTime);

    return 0;
}