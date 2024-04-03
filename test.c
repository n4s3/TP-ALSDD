#include "AbstractMachine.h"
#include "Funcs.h"
#include "Read-Write-Functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Scenario
const int AccNum = 659036305;
const char *file_name = "Accounts.txt";

int main() {
  // first we create head(BankAccount)
  BankAccount *h = NULL;
  createAccount(&h);
  // in case of deposit
  int Amount;
  Date DateDepo;
  printf("Enter your account number: \n"); // We only print this we get the
                                           // AccNum from the Accounts.txt
  // We defined An account number (refer to Scenario), we look for this Number
  // on the list (Defined Function In Funcs.h)
  BankAccount *OurAccount;
  OurAccount = searchAccountByNumber(file_name, AccNum);
  /* ***Clarification*** (IMPORTANT 👇): "Hypothetically" we ask the user the
   date we want to read the date associated with the "nth" bankaccount we can
   create a function that reads the Contents of (Opcode.txt, Date.txt,
   BalanceOfEachTransaction.txt) with respect to the bank account's position in
   the Accounts.txt file : Each Line of these text files is a representation of
   a BankAccount's Transaction Info  Of course that applies to the others as
   well*/
  printf("Enter the amount you want to deposit :%d \n", Amount);
  scanf("%d", &Amount);
  // deposit
  Deposit(h, AccNum, Amount, DateDepo);
  // we need to update the Accounts.txt inorder to do that we need
  // to find the AccNum in the list of Accounts in Accounts.txt
}
