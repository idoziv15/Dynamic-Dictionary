#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct Word {
    char **translations;
    struct Word *next;
} Word;

typedef struct {
    char **languages;
    int numOfLanguages;
    Word *wordList;
} Dictionary;

/******************
* Function Name: strDivider
* Input: string and 2 dimensional array
* Output: int
* Function Operation: The function divides a given string by ','. And returns a pointer to Array of strings.
******************/
char **strDivider(char *str, int *num) {
    int size = 1;
    // Allocate memory to the languages array:
    char **stringsArr = (char **) malloc(size * sizeof(char *));
    // Return if malloc fail:
    if (stringsArr == NULL) {
        printf("The creation of the dictionary has failed!\n");
        return NULL;
    }

    const char delim[] = ",";
    char *token = strtok(str, delim);
    int i = 0;
    while (token != NULL) {
        char *tempToken = (char *) malloc(strlen(token) * sizeof(char));
        if (tempToken == NULL) {
            printf("The creation of the dictionary has failed!\n");
            return NULL;
        }
        strcpy(tempToken, token);
        stringsArr[i] = tempToken;
        token = strtok(NULL, delim);
        i++;
        if (token == NULL) {
            break;
        }
        // Reallocate memory for stringsArr:
        size++;
        char **tempStrArr = (char **) realloc(stringsArr, size * sizeof(char *));
        // Return if reallocation fail:
        if (tempStrArr == NULL) {
            printf("The creation of the dictionary has failed!\n");
            return NULL;
        }
        stringsArr = tempStrArr;
    }
    // Free str:
    free(str);
    // Assign number of strings in stringsArr:
    *num = i;
    return stringsArr;
}

/******************
* Function Name: getString
* Input: None
* Output: char*
* Function Operation: The function get a string from a user and returns a pointer to the string allocated for it
******************/
char *getString() {
    int len = 1;
    char *str = (char *) malloc(len * sizeof(char));
    if (str == NULL) {
        return NULL;
    }

    scanf(" %c", &str[len - 1]);
    // get the string:
    while (str[len - 1] != '\n') {
        len++;
        // Reallocate str size:
        char *tempStr = (char *) realloc(str, len * sizeof(char));
        if (tempStr == NULL) {
            free(str);
            return NULL;
        }
        str = tempStr;

        // Assign next character in the buffer to the last position in str:
        scanf("%c", &str[len - 1]);
    }
    str[len - 1] = '\0';
    return str;
}

/******************
* Function Name: newDictionary
* Input: pointer to dictionaries (Dictionary* dictionaries) and pointer to number of dictionaries (int* pNumOfDictionaries)
* Output: Dictionary*
* Function Operation: The function handle the process of creating a new dictionary and allocate memory for it.
******************/
Dictionary *newDictionary(Dictionary *dictionaries, int *pNumOfDictionaries) {
    // Increase number of dictionaries:
    (*pNumOfDictionaries)++;
    // Reallocation dictionaries array size:
    Dictionary *tempPointer = realloc(dictionaries, (*pNumOfDictionaries) * sizeof(Dictionary));
    // Return if reallocation failed:
    if (tempPointer == NULL) {
        printf("The creation of the dictionary has failed!\n");
        return 0;
    }
    dictionaries = tempPointer;

    // get the languages:
    printf("Define a new dictionary:\n");
    char *strLanguages = getString();
    // If the allocation to the string didn't work:
    if (strLanguages == NULL) {
        printf("The creation of the dictionary has failed!\n");
        return NULL;
    }
    int numOfLanguages = 0;
    // Divide the languages string into 2-D array:
    char **languages = strDivider(strLanguages, &numOfLanguages);

    // Create new dictionary:
    Dictionary *dict = &dictionaries[(*pNumOfDictionaries) - 1];
    // Assign pointer to languages string of the dictionary:
    dict->languages = languages;
    // Amount of languages in the dictionary:
    dict->numOfLanguages = numOfLanguages;
    // Initialize word-list to the dictionary:
    dict->wordList = NULL;
    // Print successful creation of the dictionary:
    printf("The dictionary has been created successfully!\n");

    return dictionaries;
}

/******************
* Function Name: printDictionaries
* Input: pointer to dictionaries (Dictionary* dictionaries) and number of dictionaries (int length)
* Output: None
* Function Operation: The function prints all existing dictionaries.
******************/
void printDictionaries(Dictionary *dictionaries, int length) {
    for (int i = 0; i < length; i++) {
        printf("%d. ", i + 1);
        for (int j = 0; j < dictionaries[i].numOfLanguages; j++) {
            if (j != 0)
                printf(",");
            printf("%s", dictionaries[i].languages[j]);
        }
        printf("\n");
    }
}

/******************
* Function Name: addWordToLinkList
* Input: pointer to dictionaries (Dictionary* dict) and a pointer to some word (Word* newWord)
* Output: None
* Function Operation: The function adds a certain Word that just created to a link-list of a dictionary`s words.
******************/
void addWordToLinkList(Word *newWord, Dictionary *dict) {
    if (dict->wordList == NULL) {
        dict->wordList = newWord;
        return;
    }
    Word *currentWord = dict->wordList;
    while (currentWord->next != NULL) {
        currentWord = currentWord->next;
    }
    currentWord->next = newWord;
}

/******************
* Function Name: addWord
* Input: pointer to dictionaries (Dictionary* dictionaries) and a number of dictionaries (int lenOfDictionaries)
* Output: None
* Function Operation: The function handle the process of creating a new dictionary and allocate memory for it.
******************/
void addWord(Dictionary *dictionaries, int lenOfDictionaries) {
    int choice, numOfWords = 0;

    // Choose a dictionary:
    printf("Choose a dictionary:\n");
    printDictionaries(dictionaries, lenOfDictionaries);
    scanf("%d", &choice);

    // Choose dictionary to insert words:
    Dictionary *currDict = &dictionaries[choice - 1];
    printf("Enter a word in ");
    for (int i = 0; i < currDict->numOfLanguages; i++) {
        printf("%s", currDict->languages[i]);
        if (i != currDict->numOfLanguages - 1) {
            printf(",");
        }
    }
    printf(":\n");

    // Enter words to insert the dictionary:
    char *strWords = getString();
    // If the allocation to the string didn't work:
    if (strWords == NULL) {
        printf("The addition of the word has failed!\n");
        free(strWords);
        return;
    }

    // Get the translations from the string:
    char **translations = strDivider(strWords, &numOfWords);

    // Create new Word:
    Word *currentWord = (Word *) malloc(sizeof(struct Word));
    if (currentWord == NULL) {
        printf("The addition of the word has failed!\n");
        free(strWords);
        free(currentWord);
        return;
    }
    // Assign pointer to translations array of the word:
    currentWord->translations = translations;
    // Initialize word-next to NULL:
    currentWord->next = NULL;
    // Add "Word" to the linked-list:
    addWordToLinkList(currentWord, currDict);
    // Print success addition:
    printf("The word has been added successfully!\n");
}

/******************
* Function Name: searchWord
* Input: pointer to certain Word (Word* currWord) and a pointer of word string (char* word)
* Output: returns a word of type: Word*.
* Function Operation: The function search a given word in the link-list of a dictionary.
******************/
Word *searchWord(Word *currWord, char *word) {
    while (currWord != NULL) {
        int found = strcmp(currWord->translations[0], word);
        if (found == 0) {
            return currWord;
        }
        currWord = currWord->next;
    }
    return NULL;
}

/******************
* Function Name: release
* Input: pointer to array of strings (char** strings) and a number (int num)
* Output: None
* Function Operation: The function releases strings in a given array.
******************/
void release(char **strings, int num) {
    for (int i = num - 1; i > -1; i--) {
        free(strings[i]);
    }
}

/******************
* Function Name: removeWord
* Input: pointer to dictionaries (Dictionary* dictionaries) and a number of dictionaries (int lenOfDictionaries)
* Output: None
* Function Operation: The function handle the process of deleting a Word and free memory accordingly.
******************/
void removeWord(Dictionary *dictionaries, int lenOfDictionaries) {
    int choice;

    // Choose a dictionary:
    printf("Choose a dictionary:\n");
    printDictionaries(dictionaries, lenOfDictionaries);
    scanf("%d", &choice);

    // Choose a dictionary:
    Dictionary *currDict = &dictionaries[choice - 1];
    printf("Enter a word in %s:\n", currDict->languages[0]);

    // Get the requested word:
    char *wordToRemove = getString();
    // If the allocation to the string didn't work:
    if (wordToRemove == NULL) {
        printf("The deletion of the word has failed!\n");
        return;
    }

    // Ask the user if he/she is sure:
    char isSure;
    printf("Are you sure? (y/n)\n");
    scanf("%c", &isSure);

    if (isSure == 'y') {
        // Check if the word is in the chosen dictionary:
        Word *word = searchWord(currDict->wordList, wordToRemove);
        free(wordToRemove);
        if (word == NULL) {
            printf("The deletion of the word has failed!\n");
            return;
        }
        // Delete translations:
        release(word->translations, currDict->numOfLanguages);
        // Free translations array:
        free(word->translations);

        // Remove the word from the dictionary link-list:
        // Find previous Word:
        Word *prevWord = currDict->wordList;
        while (prevWord != word && prevWord->next != word) {
            prevWord = prevWord->next;
        }
        if (prevWord == word) {
            currDict->wordList = prevWord->next;
            prevWord->next = NULL;
        } else {
            // Assign previous word in the link-list to current-word next "word" in the list:
            prevWord->next = word->next;
            // Current word will point NULL:
            word->next = NULL;
        }
        // Free current word:
        free(word);
        // Print successful delete:
        printf("The word has been deleted successfully!\n");
    } else {
        free(wordToRemove);
        printf("The deletion of the word has been canceled.\n");
        return;
    }
}

/******************
* Function Name: findWord
* Input: pointer to dictionaries (Dictionary* dictionaries) and a number of dictionaries (int lenOfDictionaries)
* Output: None
* Function Operation: The function finds a given Word in a given dictionary`s link-list.
******************/
void findWord(Dictionary *dictionaries, int lenOfDictionaries) {
    int choice;
    // Choose a dictionary:
    printf("Choose a dictionary:\n");
    printDictionaries(dictionaries, lenOfDictionaries);
    scanf("%d", &choice);

    // Return if there is no dictionary matching the choice:
    if (choice > lenOfDictionaries) {
        printf("Wrong option, try again:\n");
        return;
    }

    // Choose a dictionary:
    Dictionary *currDict = &dictionaries[choice - 1];
    printf("Enter a word in %s:\n", currDict->languages[0]);

    // Get the requested word:
    char *wordToFind = getString();
    // If the allocation to the string didn't work:
    if (wordToFind == NULL) {
        printf("The search has failed successfully!\n");
        return;
    }

    // Find the word:
    Word *foundWord = searchWord(currDict->wordList, wordToFind);
    if (!foundWord) {
        printf("There are no translations for \"%s\" in this dictionary.\n", wordToFind);
        free(wordToFind);
        return;
    }

    // Print the result:
    printf("The translations are:\n");
    for (int i = 1; i < currDict->numOfLanguages; i++) {
        printf("%s: %s", currDict->languages[i], foundWord->translations[i]);
        if (i != currDict->numOfLanguages - 1) {
            printf(", ");
        }
    }
    printf("\n");
    free(wordToFind);
}

/******************
* Function Name: freeWords
* Input: pointer to certain Word (Word* currWord) and number (int num)
* Output: None
* Function Operation: The function free the memory of a given Word.
******************/
void freeWords(Word *currWord, int num) {

    if (currWord->next == NULL) {
        // Free translations of currDict words:
        release(currWord->translations, num);
        free(currWord->translations);
        free(currWord);
        return;
    }

    // Remove recursively:
    freeWords(currWord->next, num);
    // Free translations of current word:
    release(currWord->translations, num);
    // Free translations array:
    free(currWord->translations);
    // Assign current word- next-pointer to null:
    currWord->next = NULL;
    // Free current word in the link-list:
    free(currWord);
}

/******************
* Function Name: removeAndFree
* Input: pointer to dictionaries (Dictionary* dictionaries), a number of dictionaries (int lenOfDictionaries)
*        and an index of a given dictionary (int index)
* Output: Dictionary*
* Function Operation: The function free memory of a given dictionary and reallocate and reorder the dictionaries array.
******************/
Dictionary *removeAndFree(Dictionary *dictionaries, int *lenOfDictionaries, int index, int flag) {
    Dictionary *chosenDict = &dictionaries[index];
    // Free currDict words:
    if (chosenDict->wordList != NULL) {
        freeWords(chosenDict->wordList, chosenDict->numOfLanguages);
        chosenDict->wordList = NULL;
    }
    // Free each language:
    release(chosenDict->languages, chosenDict->numOfLanguages);
    // Free languages:
    free(chosenDict->languages);
    chosenDict->languages = NULL;

    if ((*lenOfDictionaries) == 1) {
        free(dictionaries);
        dictionaries = NULL;
    } else {
        // Reorder the dictionaries in the array:
        for (int i = index; i < (*lenOfDictionaries) - 1; i++) {
            dictionaries[i] = dictionaries[i + 1];
        }
        // Decrease dictionaries array:
        Dictionary *tempDictionaries = realloc(dictionaries, ((*lenOfDictionaries) - 1) * sizeof(Dictionary));
        if (tempDictionaries == NULL) {
            printf("The deletion of the dictionary has failed!\n");
            return dictionaries;
        }
        dictionaries = tempDictionaries;
    }
    // Decrease number of dictionaries:
    (*lenOfDictionaries)--;
    // Print successful deletion of the dictionary:
    if (!flag) {
        printf("The dictionary has been deleted successfully!\n");
    }
    return dictionaries;
}

/******************
* Function Name: removeAndFree
* Input: pointer to dictionaries (Dictionary* dictionaries), and number of dictionaries (int lenOfDictionaries)
* Output: Dictionary*
* Function Operation: The function handle the process of deleting a Dictionary and free memory accordingly.
******************/
Dictionary *deleteDictionary(Dictionary *dictionaries, int *lenOfDictionaries) {
    int flag = 0;
    // Choose a dictionary:
    int choice;
    printf("Choose a dictionary:\n");
    printDictionaries(dictionaries, *lenOfDictionaries);
    scanf("%d", &choice);

    // Return if choice is not valid:
    if (choice > *lenOfDictionaries) {
        printf("The deletion of the dictionary has been canceled.\n");
        return dictionaries;
    }

    // Ask if the user sure to delete:
    char isSure;
    printf("Are you sure? (y/n)\n");
    scanf(" %c", &isSure);
    if (isSure != 'y') {
        printf("The deletion of the dictionary has been canceled.\n");
        return dictionaries;
    }
    // Remove and free the chosen dictionary:
    return removeAndFree(dictionaries, lenOfDictionaries, choice - 1, flag);
}

/******************
* Function Name: exitProgram
* Input: pointer to dictionaries (Dictionary* dictionaries), and number of dictionaries (int lenOfDictionaries)
* Output: None
* Function Operation: The function handle the process of deleting everything int the program and free memory accordingly.
******************/
void exitProgram(Dictionary *dictionaries, int *numOfDictionaries) {
    int flag = 1;
    for (int i = (*numOfDictionaries) - 1; i > -1; i--) {
        dictionaries = removeAndFree(dictionaries, numOfDictionaries, i, flag);
    }
    printf("Bye!\n");
}

/******************
* Function Name: main
* Input: None
* Output: Int
* Function Operation: The function initialize and runs the core of the program.
******************/
int main() {
    int choice, numOfDictionaries = 0;
    // initialize array of dictionaries:
    Dictionary *dictionaries;

    do {
        printf("Welcome to the dictionaries manager!\n"
               "Choose an option:\n"
               "1. Create a new dictionary.\n"
               "2. Add a word to a dictionary.\n"
               "3. Delete a word from a dictionary.\n"
               "4. Find a word in a dictionary.\n"
               "5. Delete a dictionary.\n"
               "6. Exit.\n");

        scanf("%d", &choice);

        while (choice != 6 && choice != 1 && numOfDictionaries < 1) {
            printf("This option is not available right now, try again:\n");
            scanf("%d", &choice);
        }

        switch (choice) {
            case 1:
                dictionaries = newDictionary(dictionaries, &numOfDictionaries);
                break;
            case 2:
                addWord(dictionaries, numOfDictionaries);
                break;
            case 3:
                removeWord(dictionaries, numOfDictionaries);
                break;
            case 4:
                findWord(dictionaries, numOfDictionaries);
                break;
            case 5:
                dictionaries = deleteDictionary(dictionaries, &numOfDictionaries);
                break;
            case 6:
                exitProgram(dictionaries, &numOfDictionaries);
                return 0;
            default:
                printf("Wrong option, try again:\n");
        }
    } while (choice != 6);

    return 0;
}
