#include "AbstractMachine.h"
#include "Funcs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
  // first we create head(BankAccount)
  BankAccount *h = NULL;
  createAccount(&h);
  // in case of deposit
  // ask the user their acc num
  int AccNum;
  printf("Enter your account number :%d \n", AccNum);
  scanf("%d", &AccNum);
  // ask the user the date
  Date DateDepo;
  DateDepo = readDate();
  // ask the user the amount
  int Amount;
  printf("Enter the amount you want to deposit :%d \n", Amount);
  scanf("%d", &Amount);
  // deposit
  Deposit(h, AccNum, Amount, DateDepo);
}
