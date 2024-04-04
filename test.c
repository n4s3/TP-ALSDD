#include "AbstractMachine.h"
#include "Funcs.h"
#include "Read-Write-Functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Scenario
const int AccNum = 659036305;
const char *file_name = "Accounts.txt";
const char *date_file = "Date.txt";
const char *op_file = "Opcode.txt";
const char *bal_file = "BalanceOfEachTransaction.txt";

int main() {
  // Deposit 👇
  BankAccount *head = NULL;
  int Amount;
  Date DateDepo;
  printf("Enter your account number: \n"); // We only print this we get the
                                           // AccNum from the Accounts.txt
  // We defined An account number (refer to Scenario), we look for this Number
  // on the list (Defined Function In Funcs.h)
  BankAccount *OurAccount;
  OurAccount =
      searchAccountByNumber(file_name, AccNum); // We used readAccountInfo
  /* ***Clarification*** (IMPORTANT 👇): "Hypothetically" we ask the user the
   date we want to read the date associated with the "nth" bankaccount we can
   create a function that reads the Contents of (Opcode.txt, Date.txt,
   BalanceOfEachTransaction.txt) with respect to the bank account's position in
   the Accounts.txt file : Each Line of these text files is a representation of
   a BankAccount's Transaction Info  Of course that applies to the others as
   well*/
  readOneTransactionList(OurAccount, date_file, op_file, bal_file);
  DateDepo = OurAccount->transactionList->Date; // this is the first transaction
  Amount = OurAccount->transactionList->Balance;
  Deposit(OurAccount, AccNum, Amount, DateDepo);
}
