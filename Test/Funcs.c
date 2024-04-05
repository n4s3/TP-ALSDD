#include "Funcs.h"
#include "AbstractMachine.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ADMIN_PASSWORD "admin123"
#define TRANSFER 'T'
#define DEPOSIT 'D'
#define WITHDRAWAL 'W'

bool isAdmin() {
  char password[20];
  printf("Enter the admin password: ");
  scanf("%s", password);
  // Compare the entered password with the admin password
  if (strcmp(password, ADMIN_PASSWORD) == 0) {
    return true; // User is admin
  } else {
    return false; // User is not admin
  }
}

void addTransaction(BankAccount *account, Date date, char opcode,
                    float amount) {
  Transaction *newTransaction;
  CreateNewTran(&newTransaction);
  AssignTranData(newTransaction, date, opcode, amount);
  newTransaction->nextTransaction = account->transactionList;
  account->transactionList = newTransaction;
}
void printBankAccounts(BankAccount *head) {
  BankAccount *current = head;

  while (current != NULL) {
    printf("Account Number: %d\n", current->Number);
    printf("First Name: %s\n", current->Name.First);
    printf("Last Name: %s\n", current->Name.Last);
    printf("Code: %d\n", current->Code);
    printf("Balance: %.2f\n", current->Balance);
    printf("Transaction List:\n");

    Transaction *transaction = current->transactionList;
    while (transaction != NULL) {
      Date Date;
      Date = PrintDate(transaction);
      printf("Date : %d.%d.%d", Date.Year, Date.Month, Date.Day);
      printf("Operation: %c\n", transaction->opcode);
      printf("Amount: %.2f\n", transaction->Balance);
      printf("\n");

      transaction = transaction->nextTransaction;
    }

    printf("\n");
    current = current->nextBAcc;
  }
}

void Deposit(BankAccount *h, int Number, float Amount, Date D) {
  BankAccount *p;
  p = h;
  while (Number != p->Number && p != NULL) {
    p = next_Account(p);
  }
  if (p == NULL) { // second if // in case the account does not exist it is not
                   // like the first one
    printf(" Sorry , This Account Does Not Exist . ");
  } else { // second
    p->Balance = p->Balance + Amount;
    Transaction *New_A;
    CreateNewTran(&New_A); // to put the new ooperation in this node
    AssignTranData(New_A, D, 'D', Amount); // assign data to the opperation
    Transaction *Temp_B;
    Temp_B = p->transactionList; // to get the head of the opeeration
    if (Temp_B == NULL) {        // third if
      AssignListToBank(p, New_A);
      AssignTranList(New_A, NULL);
      DeleteTran(New_A);
    } else { // third
      while (next_Transaction(Temp_B) != NULL) {
        Temp_B = next_Transaction(Temp_B);
      }
      AssignTranList(
          Temp_B,
          New_A); // assign to the anciet node the adress of the new node
      AssignTranList(New_A, NULL); //  assign null to the new node
      DeleteTran(New_A);
    } // third
  }   // second
} // end of the list

void Deletecustomeraccount(BankAccount *h, int Number) {

  BankAccount *p;
  BankAccount *previous;
  p = h;
  previous = h;
  while (Number != p->Number && p != NULL) {
    previous = p;
    p = next_Account(p);
  }
  if (p == NULL) {
    printf(" Sorry , no such account ");
  } else {        // first
    if (p != h) { // normal case
      AssignAccount(previous, next_Account(p));
      DeleteAccount(p);
    } else { // second
      // third  in case the node is the head
      h = next_Account(h);
      DeleteAccount(p);

    } // second
  }   // first

} // only the admin can do this and for more clarification BankAccount * h is
  // the head of the list of the acccounts
void Withdrawal(BankAccount *h, int Number, float Amount,
                Date D) { // begin of the function
  BankAccount *p;
  p = h; // intialize
  while (Number != p->Number && p != NULL) {
    p = next_Account(p);
  }
  if (p == NULL) {
    printf("Sorry, Operation cannot be done we need a valid account .");
  } else { // first
    if (p->Balance >=
        Amount) { // if the amount is less we can not do this opperation so this
                  // this condition is important
      p->Balance = p->Balance - Amount;
      Transaction *New_A;
      CreateNewTran(&New_A);
      AssignTranData(New_A, D, 'W', -Amount); // assign data to the opperation
      Transaction *Temp_B; // we need it to get hte head of the oppeations
      Temp_B = p->transactionList; // to get the head of the opeerations
      if (Temp_B == NULL) {
        AssignListToBank(p,
                         New_A); // to link list of opperation with the accounts
        AssignTranList(New_A, NULL);
        DeleteTran(New_A);
      } else { // third
        while (next_Transaction(Temp_B) != NULL) {
          Temp_B = next_Transaction(Temp_B); // go to the last node in case
        }
        AssignTranList(
            Temp_B,
            New_A); // assign to the anciet node the adress of the new node
        AssignTranList(New_A, NULL); //  assign null to the new node
        DeleteTran(New_A);
      } // third

    } else { // forth
      printf("Sorry , Your Balance is not enough");
    } // forth
  }   // second
} // the end of the function
void TransferAmount(BankAccount *h, int N1, int N2, float Amount,
                    Date D) { // begin of the function
  BankAccount *p;
  BankAccount *q;
  p = h; // intialize
  q = h; // same
  while (N1 != p->Number && p != NULL) {
    p = next_Account(p); // find the Account
  }
  if (p == NULL) {
    printf(" no such account , Operation uncompleted it needs at least 2 "
           "accounts  "); // in case the account does not exist we do not need
                          // to find the other account
  } else {
    while (N2 != q->Number && q != NULL) { // find the second  acc
      p = next_Account(p);
    }
    if (q == NULL) {
      printf(
          " error !!this operation needs at least 2 accounts "); // in case the
                                                                 // account does
                                                                 // exist
    } else {
      if (p->Balance >=
          Amount) { // the amount must be less or equal to the balance
        p->Balance = p->Balance - Amount;
        q->Balance = q->Balance + Amount;
        Transaction *New_A;
        Transaction *New_B;
        Transaction *Temp;
        Transaction *Temp_B;
        CreateNewTran(&New_A);
        CreateNewTran(&New_B);
        Temp = p->transactionList;   // get the head of the opperations lists of
                                     // the first account
        Temp_B = q->transactionList; // same second account
        AssignTranData(New_A, D, 'T', -Amount);
        AssignTranData(New_B, D, 'T', Amount);
        if (Temp == NULL) {
          AssignListToBank(p, New_A);
          AssignTranList(New_A, NULL);
          DeleteTran(New_A);
        } else { // first
          while (Temp != NULL) {
            Temp = next_Transaction(
                Temp); // find the node of opperations to add the new one
          }
          AssignTranList(Temp, New_A);
          AssignTranList(New_A, NULL);
          DeleteTran(New_A);
        } // first
        if (Temp_B == NULL) {
          AssignListToBank(q, New_B);
          AssignTranList(New_B, NULL);
          DeleteTran(Temp_B);
        } else { // second
          while (Temp_B != NULL) {
            Temp_B = next_Transaction(Temp_B);
          }
          AssignTranList(Temp_B, New_B);
          AssignTranList(New_B, NULL);
          DeleteTran(New_B);
        }      // second
      } else { // in case the amount greater then the Balance .
        printf("Sorry ,  your balance is not enough ");
      }
    }
  }
} // end of the function

float CheckAmount(BankAccount *h, int Number) { // begin of the function
  BankAccount *p;
  p = h;
  {
    while (Number != p->Number && p != NULL) {
      p = next_Account(p);
    }
    if (p == NULL) {
      printf("no such Account");
    } else {
      float Balance = p->Balance;
      return Balance;
    }
  }
  return -1;
} // end of the function
Date PrintDate(Transaction *Tran) {
  if (Tran == NULL) {
    printf("This Transaction Does not exsist\n");
    exit(EXIT_FAILURE);
  }
  Date date;
  date.Year = Tran->Date.Year;
  date.Month = Tran->Date.Month;
  date.Day = Tran->Date.Day;
  return date;
}
BankAccount *findAccountByNumber(BankAccount *head, int accountNumber) {
  BankAccount *current = head;
  while (current != NULL) {
    if (current->Number == accountNumber) {
      return current;
    }
    current = current->nextBAcc;
  }
  return NULL; // Account not found
}
static void printData(Transaction *h) {
  printf("%c\n", h->opcode);
  Date Date = PrintDate(h);
  printf("The Date of Operation %d.%d.%d \n", Date.Year, Date.Month, Date.Day);
  printf("The Balance is  : %f \n", h->Balance);
}

void CheckHistoryV2(BankAccount *Account, Date D) {
  Transaction *Temp;
  Temp = Account->transactionList; // you can not just do this you have to find
                                   // the account as i did
  if (Temp == NULL) {
    printf(" Sorry , there is no opperation in this account ");
  } else {
    while (Temp != NULL) {
      if (D.Day == Temp->Date.Day && D.Month == Temp->Date.Month &&
          D.Year == Temp->Date.Year) {
        // we print the data so we create a new function to do this
        printData(Temp);
        Temp = next_Transaction(Temp);
      } else {
        Temp = next_Transaction(Temp);
        if (Temp == NULL) {
          printf("There is no such date");
          return;
        }
      }
    }
  }
}
void CheckHistory(BankAccount *h, int Number, Date D) {
  BankAccount *p;
  Transaction *Temp;
  p = h;
  while (Number != p->Number && p != NULL) {
    p = next_Account(p);
  }
  if (p == NULL) {
    printf("the account does not exist .");
  } else {

    Temp = p->transactionList; // you can not just do this you have to find the
                               // account as i did
    if (Temp == NULL) {
      printf(" Sorry , there is no opperation in this account ");
    } else {
      while (Temp != NULL) {
        if (D.Day == Temp->Date.Day && D.Month == Temp->Date.Month &&
            D.Year == Temp->Date.Year) {
          // we print the data so we create a new function to do this
          printData(Temp);
          Temp = next_Transaction(Temp);
        } else {
          Temp = next_Transaction(Temp);
          if (Temp == NULL) {
            printf("There is no such date");
            return;
          }
        }
      }
    }
  }
}
void EditCodeAndOrCustomer(BankAccount *h, int Number, int x) {
  printf("Admin !, what do you want to change ? \n");
  printf("Customer\'s Account Number: 1 \n");
  printf("Customer\'s Name: 2\n");
  printf("Delete Customer\'s Account: 3\n");
  printf("Add New Customer: 4\n");
  int AccNum;
  int CodeNum;
  int c_num;
  BankAccount *p;
  BankAccount *New;
  createAccount(&New);
  BankAccount *temp;
  temp = h;
  p = h;
  while (x > 4 && x < 1) {
    printf("You must choose a number between one  and four.");
    scanf("enter your choice %i\n", &x);
  }
  switch (x) {
  case 1:
    while (Number != p->Number && p != NULL) {
      p = next_Account(p);
    } // to get the wanted acccount  with the  number ;
    if (p == NULL) {
      printf("the account Does not exist  you must check the Number .");
    } else {
      printf("enter the new Code ");
      int Code;
      scanf(" The code must contain only numbers you can not  use letters  %i ",
            &Code);
      p->Code = Code;
      printf("Your code has been changed successfully");
    }
  case 2:
    while (Number != p->Number && p != NULL) {
      p = next_Account(p);
    } // to get the wanted acccount with the  number
    if (p == NULL) {
      printf("The account Does not exist  you must check the Number .");
    } else {
      printf("Enter the new First Name");
      char FirstName[15];
      scanf("%s", FirstName);
      printf("Enter the new Last Name");
      char LastName[15];
      scanf("%s", LastName);
      CopyCharArray(h->Name.First, FirstName);
      CopyCharArray(h->Name.Last, LastName);
    }

  case 3:
    printf("Enter the customer\'s number : ");
    scanf("%d", &Number);
    Deletecustomeraccount(p, Number);
  case 4:
    if (h == NULL) {
      New = h;
    } else {
      while (next_Account(temp) != NULL) {
        temp = next_Account(temp);
      }
      AssignAccount(temp, New); // link it the last one
      AssignAccount(New,
                    NULL); // JUST inserting the New node at the tail of the
      // list
    }
    // now DATA assigning
    printf("Enter the account number : %d", AccNum);
    scanf("%d", &AccNum);
    printf("Enter the account code : %d", CodeNum);
    scanf("%d", &CodeNum);
    New->Number = AccNum;
    New->Code = CodeNum;
    char FirstNameAcc[15];
    char LastNameAcc[15];
    printf("Enter the customer\'s Fisrt Name : %s", FirstNameAcc);
    scanf("%s", FirstNameAcc);
    printf("Enter the custoome\'s Last Name : %s", LastNameAcc);
    scanf("%s", LastNameAcc);
    CopyCharArray(New->Name.First, FirstNameAcc);
    CopyCharArray(New->Name.Last, LastNameAcc);
    // setting the balance to 0 (conventional, I think)
    New->Balance = 0;
    AssignTranList(New->transactionList, NULL);
  }
  DeleteAccount(New);
}
