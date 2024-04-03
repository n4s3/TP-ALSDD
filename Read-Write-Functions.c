#include "Read-Write-Functions.h"
#include "AbstractMachine.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define max_len 256
static const char *file_name = "Accounts.txt";
static const char *date_file = "Date.txt";
static const char *op_file = "Opcode.txt";
static const char *bal_file = "BalanceOfEachTransaction.txt";
// in this function we go through all the info that's in the file Account.txt
// and create a linked list of BankAccounts
BankAccount *readAccountInfo(const char *file_name, BankAccount *head) {
  // we used fopen from stdio.h with parameter r to open the .txt file
  // and return a pointer if successful
  FILE *file = fopen(file_name, "r");
  if (file == NULL) {
    printf("Error Accessing file\n");
    exit(EXIT_FAILURE);
  }
  int line_number = 0;
  char line[max_len];
  while (fgets(line, sizeof(line), file) != NULL) {
    char FirstName[15];
    char LastName[15];
    int Number;
    int Code;
    float Balance;
    if (sscanf(line, "%s %s %d %d %f", FirstName, LastName, &Number, &Code,
               &Balance) == 5) {
      // here in the condition we checked if all the data is in the line using
      // sscanf it returns an int of how many variable it had read(basically
      // like scanf)
      line_number++; // we start counting the line numbers (so we can easily use
                     // them later when associating the transaction with the
                     // bankaccount)
      addAccountToList(&head, FirstName, LastName, Number, Code, Balance);
    } else {
      printf("You Have Entered Wrong The wrong type\n");
    }
  }
  return head;
  fclose(file);
}

void writeAccountInfo(const char *file_name, BankAccount *AddedAcc) {
  FILE *file = fopen(file_name, "a"); // here we used append mode
  // Instead of write mode which doesn't overwirte the file
  if (file == NULL) {
    printf("Error Accessing file\n");
    return;
  }
  const BankAccount *temp;
  fprintf(file, "%s %s %d %d %f", AddedAcc->Name.First, AddedAcc->Name.Last,
          AddedAcc->Number, AddedAcc->Code, AddedAcc->Balance);
  fclose(file);
}
/*
BankAccount *searchAccountByNumber(const char *file_name, int ToLookForNumber) {
  FILE *file = fopen(file_name, "r");
  if (file == NULL) {
    printf("Error Accessing file\n");
    exit(EXIT_FAILURE);
  }

  char line[max_len];
  while (fgets(line, sizeof(line), file) != NULL) {
    char FirstName[15];
    char LastName[15];
    int Number;
    int Code;
    float Balance;
    if (sscanf(line, "%s %s %d %d %f", FirstName, LastName, &Number, &Code,
               &Balance) == 5) { // here same approach to readAccountInfo
      if (Number == ToLookForNumber) {
        BankAccount *found;
        createAccount(&found);
        strcpy(found->Name.First, FirstName);
        strcpy(found->Name.Last, LastName);
        found->Balance = Balance;
        found->Code = Code;
        found->Number = Number;
        fclose(file); // we immediately close the file to save resources
        return found;
      }
    } else {
      printf("Wrong Types In Accounts.txt\n");
      fclose(file); // same here
      exit(EXIT_FAILURE);
    }
  }

  printf("Didn't find account with number %d\n", ToLookForNumber);
  fclose(file);
  return NULL; // we return a null pointer to indicate that we didn't find the
  // account
}
*/

BankAccount *searchAccountByNumber(const char *file_name, int ToLookForNumber) {
  BankAccount *head = NULL;
  head = readAccountInfo(file_name, head);
  BankAccount *current = head;
  while (current != NULL && current->Number != ToLookForNumber) {
    current = next_Account(current);
    if (current == NULL) {
      printf("This account doesn\'t exist\n");
    }
  }
  return current;
}

// 👉 IMPORTANT : In order to work with this function we have to make sure that
// we already :
// have a linked list of bank accounts then we can associate those transactions
// with their given bank accounts.
void readOneTransactionInfo(BankAccount *head, const char *DateFile,
                            const char *OpCodeFile,
                            const char *BalanceOfEachTransactionFile) {
  // This is the same stuff we did in readAccountInfo
  FILE *date = fopen(DateFile, "r");
  FILE *opcode = fopen(OpCodeFile, "r");
  FILE *bfile = fopen(BalanceOfEachTransactionFile, "r");
  if (date == NULL || opcode == NULL || bfile == NULL) {
    printf("Failed to open files\n");
    exit(EXIT_FAILURE);
  }

  // Here's where we're going to put our temporarily transaction nodes data
  char line[max_len];
  while (fgets(line, sizeof(line), date) != NULL) {
    char *seperate_date = strtok(line, " "); // seperate date based on spaces
    Transaction *head_t = NULL;              // Head of the transaction list
    BankAccount *current = head;
    /* 👉 Strtok Explanation :
    https://www.tutorialspoint.com/c_standard_library/strtok.htm
    you have a sentence, like "Hello, how are you?" and you want to
    separate the words. strtok is like a magic tool that you tell, "Hey,
    I want to split this sentence wherever there's a space or a comma."
    Then, every time you use strtok, it gives you one piece of the
    sentence, until there's nothing left. So, it's a way to take a long
     sentence and get each word separately.*/

    while (seperate_date != NULL) {
      // Parse date from seperate_date
      int day, year, month;
      if (sscanf(seperate_date, "%d.%d.%d", &year, &month, &day) != 3) {
        printf("Error parsing date\n");
        exit(EXIT_FAILURE);
      }

      // Read opcode from OpCodeFile
      if (fgets(line, sizeof(line), opcode) != NULL) {
        // seperate opcode based on spaces
        char *seperate_opcode = strtok(line, " ");
        while (seperate_opcode != NULL) {
          // Read balance from BalanceOfEachTransactionFile
          if (fgets(line, sizeof(line), bfile) != NULL) {
            // seperateize balance based on spaces
            char *seperate_balance = strtok(line, " ");
            while (seperate_balance != NULL) {
              // Create and add transaction node
              Date date = {.Year = year,
                           .Month = month,
                           .Day = day}; // This is very important: to convert
                                        // those integers into a Date structure
              addTransactionToList(&head_t, seperate_opcode[0], date,
                                   atof(seperate_balance));

              // Move to the next balance seperate
              seperate_balance = strtok(NULL, " ");
            }
          } else {
            printf("Error reading balance\n");
            exit(EXIT_FAILURE);
          }
          // Move to the next opcode seperate
          seperate_opcode = strtok(NULL, " ");
        }
      } else {
        printf("Error reading opcode\n");
        exit(EXIT_FAILURE);
      }
      // Move to the next date seperate
      seperate_date = strtok(NULL, " ");
    }
    // Assign the transaction list to the bank account
    if (current != NULL) {
      AssignListToBank(head, head_t);
      head = next_Account(head);
    }
    // Reset head_t for next line
    head_t = NULL;
  }

  fclose(date);
  fclose(opcode);
  fclose(bfile);
}
