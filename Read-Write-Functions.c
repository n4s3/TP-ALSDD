#include "Read-Write-Functions.h"
#include "AbstractMachine.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
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

// 👉 IMPORTANT : In order to work with this function we have to make sure that
// we already :
// have a linked list of bank accounts then we can associate those transactions
// with their given bank accounts.
void readTransactionList(BankAccount *head, const char *DateFile,
                         const char *OpCodeFile,
                         const char *BalanceOfEachTransactionFile) {
  FILE *date = fopen(date_file, "r");
  FILE *opcode = fopen(op_file, "r");
  FILE *bfile = fopen(bal_file, "r");
  if (date == NULL || opcode == NULL || bfile == NULL) {
    printf("Failed to open files\n");
    exit(EXIT_FAILURE);
  }
  char line[max_len];
  Transaction *head_t = NULL; // head of our Transaction list
  while (fgets(line, sizeof(line), date) != NULL) {
    // same approach as before
    int day, year, month;
    // strtok explanation 👇
    // Imagine you have a sentence, like "Hello, how are
    // you?" and you want to separate the words. strtok is like a magic tool
    // that you tell, "Hey, I want to split this sentence wherever there's a
    // space or a comma." Then, every time you use strtok, it gives you one
    // piece of the sentence, until there's nothing left. So, it's a way to take
    // a long sentence and get each word separately. using the delimiter of
    // choice
    char *seperated1 = strtok(line, " ");
    while (seperated1 != NULL) {
      int day1, year1, month1;
      if (sscanf("%d.%d.%d", seperated1, &year1, &month1, &day1) != 3) {
        printf("Reading .txt file failed successfully\n");
        exit(EXIT_FAILURE); // error handling
      }
      day = day1;
      month = month1;
      year = year1;
      char Op;
      while (fgets(line, sizeof(line), opcode) != NULL) {
        char *seperated2 = strtok(line, " ");
        while (seperated2 != NULL) {
          char Op1;
          if (sscanf("%c", seperated2, &Op1) != 1) {
            printf("Reading .txt file failed successfully\n");
            exit(EXIT_FAILURE); // error handling
          }
          Op = Op1;
          seperated2 = strtok(NULL, " ");
        }
      }
      float balance;
      while (fgets(line, sizeof(line), bfile) != NULL) {
        char *seperated3 = strtok(line, " ");
        while (seperated3 != NULL) {
          float balance1;
          if (sscanf("%f", seperated3, &balance1) != 1) {
            printf("Reading .txt file failed successfully\n");
            exit(EXIT_FAILURE); // error handling
          }
          balance = balance1;
          seperated3 = strtok(NULL, " ");
        }
      }
      // now that we made sure that the line was read successfully
      // we can use it
      Date date = {
          .Year =
              {year}, // Initializing the Year array with the value of 'year'
          .Month =
              {month}, // Initializing the Month array with the value of 'month'
          .Day = {day} // Initializing the Day array with the value of 'day'
      };
      // now we add the data to the transaction
      // assuming we start from the head
      addTransactionToList(&head_t, Op, date, balance);
      AssignListToBank(head, head_t);
      seperated1 = strtok(NULL, " ");
    }
  }
  fclose(date);
  fclose(opcode);
  fclose(bfile);
}
