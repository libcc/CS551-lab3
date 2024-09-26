// THIS CODE IS MY OWN WORK, IT WAS WRITTEN WITHOUT CONSULTING A
// TUTOR OR CODE WRITTEN BY OTHER STUDENTS - NAVID AZIMI

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>

int Maximum_char_per_word;

// This function takes a string as input and modifies it based on the specified sarg and larg arguments
int String_Mod(int sarg, int larg, char string[]) {

    int length = strlen(string);

    if (length <= sarg) {
        return -1;
    }

    int i;
    // Iterate through the characters of the string
    for (i = 0; i < length; i++) {
        // Check if the character is not a lowercase letter
        if (!islower(string[i])) {
            // If a non-lowercase character is found, replace it with a newline character
            string[i] = '\n';
            break;
        }
    }

    // Truncate the string: set the character at the position 'i' to a null terminator
    string[i] = '\0';

    // If the string is too long, truncate it to the larg size
    if (length > larg) {
        string[larg] = '\0';
    }

    // Return the position i: index of the first non-lowercase character
    return i;
}


// This function reads characters from the standard input until a non-alphabetic character is encountered
// then stores the characters in the Input array and returns the size of the resulting word
int WordS_stdin(char Input[]) {

    int counter = 0;       // Counter to keep track of the characters read
    int wordSize = -1;
    char Character;

    // A loop to read characters from stdin
    do {
        Character = getchar();
        // Check if the counter is within the bounds
        if (counter < Maximum_char_per_word) {
            Input[counter] = Character;       // Store the character in the Input array
        }
        counter++;  // Keep track of the number of characters read
      // Continue reading characters while Character is an uppercase or lowercase alphabetic character
    } while (((Character >= 'A' && Character <= 'Z') || (Character >= 'a' && Character <= 'z')));

    // Check if the counter is within the bounds
    if (counter <= Maximum_char_per_word) {
        Input[counter] = '\0';     // Add a null terminator to mark the end of the word
        wordSize = counter;        // Set wordSize to the number of characters read
    } 
    
    // If the word is too long, truncate it to the Maximum_char_per_word length
    else if (counter > Maximum_char_per_word) {
        Input[Maximum_char_per_word] = '\0';     // Add a null terminator to mark the end of the word
        wordSize = Maximum_char_per_word;        // Set wordSize to the Maximum_char_per_word length
    } 
    
    // Error or empty string
    else {
        wordSize = -1;
    }

    return wordSize;
}

// This function cleans the String_Array and the corresponding counters of each element
void StringsArray_Clean(char Strings_Array[][Maximum_char_per_word + 1], int counter[], int narg) {
    // Iterate through each element in the String_Array and clear it along with its counter
    for (int i = 0; i < narg; i++) {
        // Using strcpy to set the content of the Strings_Array element to an empty string
        strcpy(Strings_Array[i], "");
        // Set the counter for the current Strings_Array element to 0
        counter[i] = 0;
    }
}

// This function checks if the given Strings_Array is empty or not by iterating through its elements
int StringsArray_EmptyCheck(char Strings_Array[][Maximum_char_per_word + 1], int narg) {
    // Loop through each element in the Strings_Array to check if it contains any data
    for (int i = 0; i < narg; i++) {
        // Check if the first character of the Strings_Array element is not the null terminator
        // If it's not the null terminator, this element is considered non-empty
        if (Strings_Array[i][0] != '\0') {
            return i;       // Return the index of the first non-empty element found
        }
    }
    // -1: Strings_Array is empty
    return -1;
}

// Function to find the index of the smallest element in the Strings_Array
int StringsArray_SElement(char Strings_Array[][Maximum_char_per_word + 1], int narg) {
    // Check if the array is not empty
    int SElement = StringsArray_EmptyCheck(Strings_Array, narg);
    // Iterate through the array to find the smallest element
    if (SElement >= 0) {
        for (int i = 0; i < narg; i++) {
            // Check if the current element is not an empty string
            if (strcmp(Strings_Array[i], "") != 0) {
                // Check if the smallest element is empty or if the current element is smaller
                if (strcmp(Strings_Array[SElement], "") == 0 || strcmp(Strings_Array[i], Strings_Array[SElement]) < 0) {
                    // Update the index
                    SElement = i;
                }
            }
        }
    }
    // Return the index of the smallest element
    return SElement;
}

// Function to sort a Strings_Array along with their counted values in alphabetical order
void StringsArray_Sort(char Strings_Array[][Maximum_char_per_word + 1], int counter[], int narg) {
    for (int i = 0; i < narg; i++) {
        for (int j = i + 1; j < narg; j++) {
            // Check if the strings at positions i and j are not empty and if string i is alphabetically greater than string j
            if (Strings_Array[i][0] != '\0' && Strings_Array[j][0] != '\0' && strcmp(Strings_Array[i], Strings_Array[j]) < 0) {
                // Swap the strings in the Strings_Array
                char temp[Maximum_char_per_word + 1];
                strcpy(temp, Strings_Array[i]);
                strcpy(Strings_Array[i], Strings_Array[j]);
                strcpy(Strings_Array[j], temp);
                // Swap the corresponding counters
                int tempCounter = counter[i]; 
                counter[i] = counter[j];
                counter[j] = tempCounter;
            }
        }
    }
}

// Function to print the non-empty strings from String_Array along with their counted values
void StringsArray_stdout(char Strings_Array[][Maximum_char_per_word + 1], int num_string[], int narg) {
    for (int i = 0; i < narg; i++) {
        // Check if the string at position i is not empty
        if (Strings_Array[i][0] != '\0') {
            // Print the counter value and the string with 10 character field formatting
            printf("%-10i%s\n", num_string[i], Strings_Array[i]);
        }
    }
}

// Function to find the index of the first empty slot in String_Array, up to narg number of elements
int EmptySlot_Index(char Strings_Array[][Maximum_char_per_word + 1], int narg) {
    for (int i = 0; i < narg; i++) {
        // Check if the string at position i is empty
        if (Strings_Array[i][0] == '\0') {
            // Return the index of the first empty slot in the String_Array
            return i;
        }
    }
    return -1;
}

// Function to check if a given element exists in an array of strings up to a specified number of elements (narg)
int Search_Element(char Strings_Array[][Maximum_char_per_word + 1], char element[Maximum_char_per_word + 1], int narg) {

    int foundIndex = -1;

    // Check if the element is an empty string
    if (element[0] == '\0') {
        // Element has not been found in the Strings_Array
        return foundIndex;
    }

    // Iterate through the Strings_Array to find the element
    for (int i = 0; i < narg; i++) {
        if (strcmp(Strings_Array[i], element) == 0) {
            // Update foundIndex to i, if the element has been found at index i
            foundIndex = i;
            break;
        }
    }

    return foundIndex;
}   

// Function to read from a given FILE stream and store it in a character buffer
int File_Read(char **buffer, FILE *file) {
    
    size_t buffer_size = 0;
    // Read a line from the file into the buffer
    ssize_t line_size = getline(buffer, &buffer_size, file);        

    if (line_size == -1) {
        // Check if getline returned -1, which indicates the end of the file or an error
        return -1;
    }

    // Check if the last character is a newline character & remove the newline character if it exists
    if (line_size > 0 && (*buffer)[line_size - 1] == '\n') {
        // Replace the newline character with a null terminator
        (*buffer)[line_size - 1] = '\0';
        // Decrease the line size by 1 to exclude the removed newline character
        line_size--; 
    }

    return (int)line_size;
}

// Function to create a specified number of pipes and populating the pipeArray with the corresponding file descriptors
int Create_Pipes(int narg, int pipeArray[][2]) {

    int num_pipes = 0;
    // Loop through each pipe required for sorting and attempting to create one
    for (num_pipes = 0; num_pipes < narg; num_pipes++) {
        if (pipe(pipeArray[num_pipes]) == -1) {
            perror("ERROR: Failure in pipe creation");
            exit(1);
        }
    }
    // Return the total number of created pipes
    return num_pipes; 
}

// Function to close the read ends of a set of pipes specified in the pipeArray array
int Close_PipesRead(int pipeArray[][2], int num_pipes) {

    int error = 0;
    // Loop through each read end of the pipes
    for (int i = 0; i < num_pipes; i++) {
        if (close(pipeArray[i][0]) == -1) {
            fprintf(stderr, "ERROR: Failure in closing the read end of the pipe %i\n", pipeArray[i][0]);
            error = 1;
        }
    }
    return error; 
}

// Function to close the write ends of a set of pipes specified in the pipeArray array
int Close_PipesWrite(int pipeArray[][2], int num_pipes) {

    int error = 0;
    // Loop through each write end of the pipes
    for (int i = 0; i < num_pipes; i++) {
        if (close(pipeArray[i][1]) == -1) {
            fprintf(stderr, "ERROR: Failure in closing the write end of the pipe %i\n", pipeArray[i][1]);
            error = 1;
        }
    }
    return error;
}

// Function to check if a set of process IDs, stored in the SortingPIDs array, all correspond to child processes
int SortProcess_Parental_Check(int *SortingPIDs, int narg) {
    
    int parent = 1;
    // Loop through the array of process IDs
    for (int i = 0; i < narg; i++) {
        // Check if a process ID is non-positive, indicating it's not a child process
        if (SortingPIDs[i] <= 0) {
            parent = 0;     // A non-child process has been found
            break;
        }
    }

    return parent;
}

int main(int argc, char *argv[]) {

    int opt;
    int opt_narg;
    int opt_sarg;
    int opt_larg;
    int narg = 1;
    int sarg= 4;
    int larg = 10;

    while ((opt = getopt(argc, argv, "n:s:l:")) != -1) {

        switch (opt) {

            case 'n':
                opt_narg = 1;
                if (optarg && strtol(optarg, NULL, 10)) {
                    narg = strtol(optarg, NULL, 10);
                }
                if (narg <= 0) {
                    fprintf(stderr, "ERROR: n: argument can't be negative \n");
                    exit (1);
                }
                break;
            case 's':
                opt_sarg = 1;
                if (optarg && strtol(optarg, NULL, 10)) {
                    sarg = strtol(optarg, NULL, 10);
                }
                if (sarg <= 0) {
                    fprintf(stderr, "ERROR: s: argument can't be negative \n");
                    exit (1);
                }
                break;
            case 'l':
                opt_larg = 1;
                if (optarg && strtol(optarg, NULL, 10)) {
                    larg = strtol(optarg, NULL, 10);
                }
                if (larg <= 0) {
                    fprintf(stderr, "ERROR: l: argument can't be negative \n");
                    exit (1);
                }
                break;
            case '?':
                fprintf(stderr, "ERROR: SYNOPSIS: ./pipesort [n:s:l:] < input \n");
                return 1;
                break;
            default:
                fprintf(stdout, "ERROR: SYNOPSIS: ./pipesort [n:s:l:] < input \n");
                return 1;
                break;
        }
    }


    Maximum_char_per_word = larg;

    int parsingPID = 1;                 // Process ID for parsing

    // Array to store file descriptors for parse/sort data pipes
    int ParsingPipeFD[narg][2];          
    int SortingPipeFD[narg][2]; 

    // Create pipes for parsed/sorted data
    Create_Pipes(narg, ParsingPipeFD);
    Create_Pipes(narg, SortingPipeFD);

    int mergingPID = 1;                 // Process ID for merging
    char buffer[32];                    // Buffer for reading data from pipes
    int SortingActivePrcs = 0;          // Variable to track active sorting processes
    int SortingPIDs[narg];              // Array to store process IDs for sorting

    // Initialize the SortingPIDs array
    for (int i = 0; i < narg; i++) {
        SortingPIDs[i] = 1;
    }

    // Check conditions and fork processes based on the parent process
    if ((parsingPID > 0) && (mergingPID > 0) && SortProcess_Parental_Check(SortingPIDs, narg)) {
        // Fork new processes for parsing & merging
        parsingPID = fork();
        mergingPID = fork();

        // Fork processes for sorting based on the SortingPIDs array
        for (int i = 0; i < narg; i++) {
            if (SortProcess_Parental_Check(SortingPIDs, narg) > 0) {
                SortingPIDs[i] = fork();
            }
        }
    }

    // Close unnecessary pipe ends for the parent process
    if ((parsingPID > 0) && (mergingPID > 0) && SortProcess_Parental_Check(SortingPIDs, narg)) {
        Close_PipesRead(ParsingPipeFD, narg); 
        Close_PipesWrite(ParsingPipeFD, narg); 
        Close_PipesRead(SortingPipeFD, narg); 
        Close_PipesWrite(SortingPipeFD, narg);
    }

    // Check if the current process is a parsing process, the parent process for merging exists, and there are sorting processes
    if (parsingPID == 0 && ((mergingPID > 0) ? 1 : 0) && SortProcess_Parental_Check(SortingPIDs, narg)) {

        long InputSize = 1;
        char Input[larg + 1];        // Character array for input data
        Input[0] = 1;                // Initialize the first element of Input to 1
        int ActivePipesIndex = 0;

        // Close unnecessary pipe ends
        Close_PipesRead(ParsingPipeFD, narg); 
        Close_PipesRead(SortingPipeFD, narg); 
        Close_PipesWrite(SortingPipeFD, narg); 

        do {
            // Read data from standard input into Input array
            InputSize = WordS_stdin(Input);

            int i = 0;

            // Convert all characters in Input to lowercase
            while (Input[i] != '\0') {
                Input[i] = tolower(Input[i]);
                i++;
            }

            // Modify the input string based on the specified limits
            int stringSize = String_Mod(sarg, larg, Input);

            // Check the validity of modified string
            if (stringSize > 0 && Input[0] > 0) {
                // Write the modified input to the appropriate parsing pipe
                write(ParsingPipeFD[ActivePipesIndex][1], Input, strlen(Input) + 1);
                write(ParsingPipeFD[ActivePipesIndex][1], "\n", strlen("\n"));
                // Update the index for active pipes in a circular manner
                ActivePipesIndex = (ActivePipesIndex + 1) % narg;
            }
            // Continue processing input data until an invalid value is encountered
        } while (InputSize > 0 && Input[0] != -1);

        // Close write ends of parsing pipes and exit the process
        Close_PipesWrite(ParsingPipeFD, narg);
        exit(0);
    }

    // Check if the current process is a merging process, the parent process for parsing exists, and there are sorting processes
    if (((mergingPID > 0) ? 1 : 0) && ((parsingPID > 0) ? 1 : 0) && !SortProcess_Parental_Check(SortingPIDs, narg)) {

        // Close unnecessary pipe ends
        Close_PipesRead(SortingPipeFD, narg); 
        Close_PipesWrite(ParsingPipeFD, narg); 

        // Loop through each active sorting process
        for (int SortingActivePrcs = 0; SortingActivePrcs < narg; SortingActivePrcs++)
        {
            // Check if the current process is a sorting child process
            if (SortingPIDs[SortingActivePrcs] == 0)
            {
                // Redirect standard input to the read end of the corresponding parsing pipe
                dup2(ParsingPipeFD[SortingActivePrcs][0], 0);
                // Close the read end of the parsing pipe
                close(ParsingPipeFD[SortingActivePrcs][0]);

                // Redirect standard output to the write end of the corresponding sorting pipe
                dup2(SortingPipeFD[SortingActivePrcs][1], 1);
                // Close the write end of the sorting pipe
                close(SortingPipeFD[SortingActivePrcs][1]);

                // Execute the 'sort' command using exec, replacing the current process
                execl("/usr/bin/sort", "sort", NULL);
                // Exit the current process if exec fails
                exit(0);
            }
        }

        // Close pipe ends for parsing and sorting and exit the process
        Close_PipesRead(ParsingPipeFD, narg); 
        Close_PipesWrite(SortingPipeFD, narg); 
        exit(0);
    }

    // Check if the current process is a merging child process, parsing process is the parent, and there are sorting processes
    if (mergingPID == 0 && ((parsingPID > 0) ? 1 : 0) && SortProcess_Parental_Check(SortingPIDs, narg)) {

        char *buf;
        FILE *PipeFS[narg];
        char Strings_Array[narg][larg + 1];
        int num_string[narg];
        char PipeBuf[narg][larg + 1];
        
        // Close unnecessary pipe ends
        Close_PipesWrite(ParsingPipeFD, narg);
        Close_PipesRead(ParsingPipeFD, narg); 
        Close_PipesWrite(SortingPipeFD, narg); 

        // Read and store data from the sorting pipes' heads
        for (int i = 0; i < narg; i++)
        {
            PipeFS[i] = fdopen(SortingPipeFD[i][0], "r");
            File_Read(&buf, PipeFS[i]);
            strcpy(PipeBuf[i], buf);
        }

        int EmptySlotIndex = EmptySlot_Index(Strings_Array, narg);
        int StringArraySElement = StringsArray_SElement(PipeBuf, narg);
        StringsArray_Clean(Strings_Array, num_string, narg);

        do
        {
            // First loop: Process the merging of data
            do
            {
                // Check if there is an empty slot in Strings_Array
                if (EmptySlotIndex >= 0) {
                    num_string[EmptySlotIndex] = num_string[EmptySlotIndex] + 1;
                    strcpy(Strings_Array[EmptySlotIndex], PipeBuf[StringArraySElement]);
                    File_Read(&buf, PipeFS[StringArraySElement]);
                    strcpy(PipeBuf[StringArraySElement], buf);
                }

                // Second loop: Check for duplicate elements
                for (int i = 0; i < narg; i++) {
                    int exist = Search_Element(Strings_Array, PipeBuf[i], narg);

                    if (exist >= 0) {
                        num_string[exist] = num_string[exist] + 1;
                        File_Read(&buf, PipeFS[i]);
                        strcpy(PipeBuf[i], buf);
                        if (strcmp(buf, "") != 0) {
                            i--;
                        }
                    }
                }

                // Update variables for the next iteration
                EmptySlotIndex = EmptySlot_Index(Strings_Array, narg);
                StringArraySElement = StringsArray_SElement(PipeBuf, narg);

            } while (EmptySlotIndex >= 0 && StringArraySElement >= 0);

            // Check if Strings_Array is full, then sort, print and clean the data
            if (EmptySlot_Index(Strings_Array, narg) == -1) {
                StringsArray_Sort(Strings_Array, num_string, narg);
                StringsArray_stdout(Strings_Array, num_string, narg);
                StringsArray_Clean(Strings_Array, num_string, narg);
            }

        } while (StringsArray_EmptyCheck(PipeBuf, narg) >= 0);

        // Close pipe end and exit the merging process
        Close_PipesRead(SortingPipeFD, narg);
        exit(0);
    }

    int PID = 0;             // Process ID variable
    int PrcsStatus = 0;      // Process status variable
    int ChildCount = 2;      // Number of child processes

    while (ChildCount > 0) {
        // Wait for and collect the exit status of a child process
        if ((PID = wait(&PrcsStatus)) == -1) {
            // Exit if waiting for the process fails
            exit(1);
        }
    }

    // Iterate over the remaining child processes (narg) and wait for each one
    for (int i = 0; i < narg; i++) {
        if ((PID = wait(&PrcsStatus)) == -1) {
            // Exit if waiting for the process fails
            exit(1);
        }
    }

    // Successful execution
    return 0; 

}