#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "AbstractMachine.h"
#include "Read-Write-Functions.h"

// Very Important 👇
/*We need to break the given string (aka: Account.txt) into seperate substrings 
 inorder to modify/use them in our main.c
 We have the first field : First Name, second Last, third Number, fourth Code,
 and lastly Balance.
 So we use a function in the string.h called strtok() 
 strok(string, "delimiters(in our case "space")").  We will use that later
 it's just for clarification
 To read each line seperatly we need a function from stdio.h called fgets
 fgets requires us to have a limit to our line so 
 we allocate memory dynamically to store each line from the file using 
 the function getline() if getline() = -1 (EOF "End of file")
 getline(char **restrict lineptr, size_t *restrict n, FILE *restrict stream)
 */
char *file_name = "Accounts.txt";
void readAccountInfo(const char *file_name){
  // we used fopen from stdio.h with parameter r to open the .txt file
  // and return a pointer if successful
  FILE *file = fopen(file_name, "r");
  if (file == NULL){
    printf("Error Accessing file\n");
    return;
  }

  char *Line_Array = NULL; // array to store the info in chars
  size_t len = 0; // the size of the "buffer"
  ssize_t char_read; // how many chars were read
  while ((char_read = getline(&Line_Array, &len, file)) != -1) { // "-1" means EOF 
    // char_read = getline.. is just assigning
    //
    // We put the read data into a new Account
    char *Divided; // We use it to get the divided parts of the 
    // string in one line
    Divided = strtok(Line_Array, " "); // explained
    BankAccount *newAcc;
    createAccount(&newAcc);
    // we create data to put it in the new account
    char FirstName[15];
    char LastName[15];
    int Number;
    int Code;
    float Balance;
    while (Divided != NULL){
      strcpy(FirstName, Divided);// we put the elements of the array "Divided" into FirstName
      Divided = strtok(NULL, " "); // this ensures that we get the next field, strtok divides one set of strings 
      // before the delimter (space) one step at a time read more https://www.geeksforgeeks.org/strtok-strtok_r-functions-c-examples/
      strcpy(LastName, Divided); 
      Divided = strtok(NULL, " ");
      Number = atoi(Divided); // atoi (ASCII TO INTEGER) converts chars to ints
      Divided = strtok(NULL, " ");
      Code = atoi(Divided);
      Divided = strtok(NULL, " ");
      Balance = atof(Divided); // atof (ASCII TO FLOAT) /
      newAcc->Balance = Balance;
      newAcc->Code = Code;
      newAcc->Number = Number;
      strcpy(newAcc->Name.First, FirstName);
      strcpy(newAcc->Name.Last, LastName);
    }
  }
  free(Line_Array);
  fclose(file);
}
