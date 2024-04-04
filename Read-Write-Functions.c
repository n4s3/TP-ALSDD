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
void readOneTransactionList(BankAccount *head, const char *DateFile,
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
}
/* 👉 Strtok Explanation :
https://www.tutorialspoint.com/c_standard_library/strtok.htm
you have a sentence, like "Hello, how are you?" and you want to
separate the words. strtok is like a magic tool that you tell, "Hey,
I want to split this sentence wherever there's a space or a comma."
Then, every time you use strtok, it gives you one piece of the
sentence, until there's nothing left. So, it's a way to take a long
 sentence and get each word separately.*/
void readOneTransactionInfo(BankAccount *head, const char *DateFile,
                            const char *OpCodeFile,
                            const char *BalanceOfEachTransactionFile) {

  FILE *date = fopen(DateFile, "r");
  FILE *opcode = fopen(OpCodeFile, "r");
  FILE *bfile = fopen(BalanceOfEachTransactionFile, "r");
  if (date == NULL || opcode == NULL || bfile == NULL) {
    printf("Failed to open files\n");
    exit(EXIT_FAILURE);
  }

  // Read each line from the Date file
  char line[max_len];
  while (fgets(line, sizeof(line), date) != NULL) {
    // Tokenize the line to extract date information
    char *separate_date = strtok(line, " ");
    // Initialize the head of the transaction list
    Transaction *head_t = NULL;
    // Traverse the bank account linked list
    BankAccount *current = head;
    while (separate_date != NULL) {
      int day, year, month;
      // Parse date information
      if (sscanf(separate_date, "%d.%d.%d", &year, &month, &day) != 3) {
        printf("Error parsing date\n");
        exit(EXIT_FAILURE);
      }

      // Read opcode from OpCodeFile
      if (fgets(line, sizeof(line), opcode) != NULL) {
        char *separate_opcode = strtok(line, " ");
        // Traverse the opcode list
        while (separate_opcode != NULL) {
          // Read balance from BalanceOfEachTransactionFile
          if (fgets(line, sizeof(line), bfile) != NULL) {
            char *separate_balance = strtok(line, " ");
            // Traverse the balance list
            while (separate_balance != NULL) {
              // Create and add transaction node
              Date date = {.Year = year, .Month = month, .Day = day};
              addTransactionToList(&head_t, separate_opcode[0], date,
                                   atof(separate_balance));
              separate_balance = strtok(NULL, " ");
            }
          } else {
            printf("Error reading balance\n");
            exit(EXIT_FAILURE);
          }
          separate_opcode = strtok(NULL, " ");
        }
      } else {
        printf("Error reading opcode\n");
        exit(EXIT_FAILURE);
      }
      separate_date = strtok(NULL, " ");
    }
    // Assign the transaction list to the current bank account
    if (current != NULL) {
      AssignListToBank(head, head_t);
      head = next_Account(head);
    }
    // Reset the head of the transaction list for the next bank account
    head_t = NULL;
  }
  // Close all file pointers
  fclose(date);
  fclose(opcode);
  fclose(bfile);
}

/* ❕ This Is What this function does, after we've read the bank accounts and
created them using readAccountInfo function
Bank Account 1:
  Transaction 1:
    Date: 2022.08.15
    Opcode: D W
    Balance: 4.281
  Transaction 2:
    Date: 2022.08.15
    Opcode: D W
    Balance: 6.739

Bank Account 2:
  Transaction 1:
    Date: 2022.09.22
    Opcode: W
    Balance: 5.082

Bank Account 3:
  Transaction 1:
    Date: 2022.11.01
    Opcode: T
    Balance: 7.591
*/
