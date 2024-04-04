/* ***Clarification*** (VERY IMPORTANT 👇): "Hypothetically" we ask the user
  the date, account number..., so idealy we want to read the date
  associated with the "nth" bankaccount we can create a function that
  reads the Contents of (Opcode.txt, Date.txt,
  BalanceOfEachTransaction.txt) with respect to the bank account's
  position in the Accounts.txt file : Each Line of these text files is a
  representation of a BankAccount's Transaction Info  Of course that
  applies to the others as well*/
#include "AbstractMachine.h"
#include "Funcs.h"
#include "Read-Write-Functions.h"
#include <stdio.h>
#include <stdlib.h>
// .txt STRINGS
#define ACCOUNTS_FILE "Accounts.txt"
#define DATE_FILE "Date.txt"
#define OPCODE_FILE "Opcode.txt"
#define BALANCE_FILE "BalanceOfEachTransaction.txt"
int main() {
  BankAccount *head = NULL;
  head = readAccountInfo(ACCOUNTS_FILE, head);
  readOneTransactionList(head, DATE_FILE, OPCODE_FILE, BALANCE_FILE);
  Transaction *head_t = NULL;
  head_t = head->transactionList;
  int choice;
  int accountNumber;
  int targetAccountNumber;
  float amount;
  Date transactionDate;
  while (1) {
    printf("\nMain Menu:\n");
    printf("1. Transfer funds from one account to another.\n");
    printf("2. Deposit funds into an account.\n");
    printf("3. Withdraw funds from an account.\n");
    printf("4. Check total balance.\n");
    printf(
        "5. Check transaction history for an account within a given date.\n");
    printf("6. Add a new customer account.\n");
    printf("7. Delete a customer account.\n");
    printf("8. Edit customer details.\n");
    printf("9. Exit.\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch (choice) {
    case 1:
      // Transfer Case
      printf("Enter the account number you want to transfer funds from: %d \n",
             accountNumber);
      scanf("%d", &accountNumber);
      printf("Enter the account number you want to transfer funds to: %d \n",
             targetAccountNumber);
      scanf("%d", &targetAccountNumber);
      BankAccount *sourceAccount =
          searchAccountByNumber(ACCOUNTS_FILE, accountNumber);
      BankAccount *destinationAccount =
          searchAccountByNumber(ACCOUNTS_FILE, targetAccountNumber);
      transactionDate =
          sourceAccount->transactionList
              ->Date; // We get the first date we can chose what we want
      amount = sourceAccount->transactionList->Balance;
      TransferAmount(head, accountNumber, targetAccountNumber, amount,
                     transactionDate);
      printf("Transfer Successful\n");
      break;
    case 2:
      // Deposit Case
      printf("Enter you account number: %d \n", accountNumber);
      scanf("%d", &accountNumber);
      printf("Enter the amount you want to deposit: \n"); // We read that from
                                                          // .txt file
      BankAccount *depositAccount =
          searchAccountByNumber(ACCOUNTS_FILE, accountNumber);
      transactionDate = depositAccount->transactionList->Date;
      float amountDeposit =
          depositAccount->transactionList->Balance; // As Explained earlier
      Deposit(head, accountNumber, amountDeposit, transactionDate);
      printf("Deposit Successful\n");
      // we can add here the updated balance if we want to. Not implemented yet
      break;
    case 3:
      // Withdrawal Case
      printf("Enter you account number: %d\n", accountNumber);

      scanf("%d", &accountNumber);
      printf("Enter the ammount you want to depoist\n"); // We read that from
                                                         // .txt file as usual
      BankAccount *withdrawalAccount =
          searchAccountByNumber(ACCOUNTS_FILE, accountNumber);
      transactionDate = withdrawalAccount->transactionList->Date;
      float amountToWithdraw = withdrawalAccount->transactionList->Balance;
      Withdrawal(head, accountNumber, amountToWithdraw, transactionDate);
      printf("Withdrawal Successful\n");
      // we can add here the updated balance if we want to. Not implemented yet
      break;
    case 4:
      // Check total balance
      printf("Enter the number of your account %d\n", accountNumber);
      scanf("%d", &accountNumber);
      BankAccount *balanceAccount =
          searchAccountByNumber(ACCOUNTS_FILE, accountNumber);
      float Balance =
          balanceAccount->Balance; // Unfortunately we didn't need CheckAmount
                                   // Function In Funcs.c
      printf("Your current balance is : %f\n", Balance);
      break;
    case 5:
      // Check transaction history
      printf("Enter the number of the account %d\n", accountNumber);
      scanf("%d", &accountNumber);
      BankAccount *historyAccount =
          searchAccountByNumber(ACCOUNTS_FILE, accountNumber);
      Transaction *transaction = historyAccount->transactionList;
      transactionDate =
          transaction->Date; // This is as "clarified" Before "Scenario"
      CheckHistoryV2(historyAccount, transactionDate);
      break;
    case 6:
      // Add a new customer account
      // Only Admins are allowed to add new accounts
      // we used the function from Funcs.c isAdmin
      if (isAdmin()) {
        // Refer to Funcs.c EditCodeAndOrCusomer Function
        // switch case 4 : add a new customer
        EditCodeAndOrCustomer(head, accountNumber,
                              4); // Here there's no need for the account number
                                  // we parse it to the function to pass errors
        // So when we added a new account we need to write it to the file
        // The LinkedList tail is this account so we need to get to it
        BankAccount *newAddedAcc = NULL;
        while (next_Account(head) != NULL) {
          head = next_Account(head);
        }
        newAddedAcc = head->nextBAcc;
        writeAccountInfo(ACCOUNTS_FILE, newAddedAcc);
      }
      break;
    case 7:
      // Delete a customer account
      if (isAdmin()) {
        // case 3 : Delete a customer's account
        printf("Enter the number of the account %d\n", accountNumber);
        scanf("%d", &accountNumber);
        EditCodeAndOrCustomer(head, accountNumber, 3);
      }
      break;
    case 8: //
      // Edit customer details
      if (isAdmin()) {
        int z;
        switch (z) {
        case 1:
          printf("Enter the number of the account %d \n", accountNumber);
          scanf("%d", &accountNumber);
          EditCodeAndOrCustomer(head, accountNumber, 1);
          break;
        case 2:
          printf("Enter the number of the account %d\n", accountNumber);
          scanf("%d", &accountNumber);
          EditCodeAndOrCustomer(head, accountNumber, 2);
          break;
        }
      }
      break;
    case 9:
      // Exit
      printf("Exiting program.\n");
      exit(EXIT_SUCCESS);
    default:
      printf("Invalid choice. Please enter a number between 1 and 9.\n");
    }
  }
  printBankAccounts(head);
  return 0;
}
