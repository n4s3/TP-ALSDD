#include "Funcs.h"
#include "AbstractMachine.h"
#include <stdio.h>
#include <stdlib.h>

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
    printf(" Sorry , Opperation uncompleted because it  needs at least 2 "
           "accounts . ");
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

char *Printdate(Transaction *A) {
  Date Date;
  int i;
  char *Date_str = (char *)malloc(11 * sizeof(char));
  // initialized with null terminator
  int n = 0;
  // we will use a function called sprintf to "convert" our array of integers
  // into an array of characters // read more on
  // https://stackoverflow.com/questions/53069298/using-sprintf-to-convert-integer-to-string-seems-to-ignore-0
  for (i = 0; i <= 5; ++i) {
    n += sprintf(&Date_str[n], "%d", A->Date.Year[i]);
  }
  i = 0;
  for (i = 0; i <= 2; i++) {
    n += sprintf(&Date_str[n], ".%d", A->Date.Month[i]);
  }
  i = 0;
  for (i = 0; i <= 2; i++) {
    n += sprintf(&Date_str[n], ".%d", A->Date.Day[i]);
  }
  Date_str[n] = '\0';
  return Date_str; // here we can't for example return *Date_str because
  // we will return the first char of the array Date_str
  // we used malloc to allocate memory for the local variable Date_str
  // so we can return it properly
}
static void printData(Transaction *h) {
  printf("%c\n", h->opcode);
  char *Date;
  Date = Printdate(h);
  printf("The Date of Operation %s", Date);
  printf("The Balance is  : %f ", h->Balance);
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
        }
      }
    }
  }
}
void EditCodeAndOrCustumer(BankAccount *h, int Number) {
  printf("Admin !, what do you want to change ? \n");
  printf("Customer\'s Account Number: 1 \n");
  printf("Customer\'s Name: 2\n");
  printf("Delete Customer\'s Account: 3\n");
  printf("Add New Customer: 4\n");
  int x;
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
    } // to get the wanted acccount with the  number ;
    if (p == NULL) {
      printf("the account Does not exist  you must check the Number .");
    } else {
      printf(" enter you new First Name");
      char FirstName[15];
      scanf("%s", FirstName);
      printf(" enter you new Last Name");
      char LastName[15];
      scanf("%s", LastName);
      CopyCharArray(h->Name.First, FirstName);
      CopyCharArray(h->Name.Last, LastName);
    }

  case 3:
    printf("Enter the customer\'s number : ");
    scanf("%d", &c_num);
    Deletecustomeraccount(p, c_num);
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

Date readDate() {
  Date TDate;
  printf("Enter the day of the transaction: ");
  printf("Enter the month of the transaction: ");
  printf("Enter the year of the transaction: ");
  return TDate;
}

/// choof wech zedt wbdlt t3 delte dertha passage par variable
/// also bdlt stuct t3 date dertha sting afdal jet bdlt wsi file anu drk nhtlk
/// te3i

// Function to read BankAccount information from file
void readBankAccountInfo(const char *file_name, BankAccount **head) {
  FILE *file = fopen(file_name, "r");
  if (file == NULL) {
    printf("Error accessing file\n");
    return;
  }

  char line[100]; // Assuming each line in the file is not longer than 100
                  // characters
  // Read data for each BankAccount from the file
  while (fgets(line, sizeof(line), file) != NULL) {
    // Extract data from the line using sscanf
    char FirstName[15];
    char LastName[15];
    int Number;
    int Code;
    float Balance;

    if (sscanf(line, "%14s %14s %d %d %f", FirstName, LastName, &Number, &Code,
               &Balance) != 5) {
      printf("Error reading line: %s\n", line);
      continue; // Skip processing this line and move to the next one
    }

    // Create a new BankAccount node
    BankAccount *newAccount;
    createAccount(&newAccount);

    // Assign values to the new node
    newAccount->Number = Number;
    newAccount->Code = Code;
    strcpy(newAccount->Name.First, FirstName);
    strcpy(newAccount->Name.Last, LastName);
    newAccount->Balance = Balance;
    newAccount->nextBAcc = NULL;

    // Add the new node to the linked list
    if (*head == NULL) {
      *head = newAccount;
    } else {
      BankAccount *current = *head;
      while (current->nextBAcc != NULL) {
        current = current->nextBAcc;
      }
      current->nextBAcc = newAccount;
    }
  }

  fclose(file);
}

void readIntegerFromFile(const char *file_name, int fieldNumber, int lineNumber,
                         int *value) {
  FILE *file = fopen(file_name, "r");
  if (file == NULL) {
    printf("Error accessing file\n");
  }

  // Skip lines until reaching the desired line
  for (int i = 1; i < lineNumber; i++) {
    if (fscanf(file, "%*[^\n]%*c") == EOF) {
      printf("Error: Line number %d does not exist\n", lineNumber);
      fclose(file);
    }
  }

  // Skip fields until reaching the desired field
  for (int i = 1; i < fieldNumber; i++) {
    if (fscanf(file, "%*s") != 1) {
      printf("Error: Field number %d does not exist in line %d\n", fieldNumber,
             lineNumber);
      fclose(file);
    }
  }

  // Read the integer from the desired field
  if (fscanf(file, "%d", value) != 1) {
    printf("Error: Unable to read integer from field %d in line %d\n",
           fieldNumber, lineNumber);
    fclose(file);
  }

  fclose(file);
}

int readDateFromFile(const char *file_name, int lineNumber, Date *date) {
  FILE *file = fopen(file_name, "r");
  if (file == NULL) {
    printf("Error accessing file\n");
    return 0; // Return 0 to indicate failure
  }

  // Skip lines until reaching the desired line
  for (int i = 1; i < lineNumber; i++) {
    if (fscanf(file, "%*[^\n]%*c") == EOF) {
      printf("Error: Line number %d does not exist\n", lineNumber);
      fclose(file);
      return 0; // Return 0 to indicate failure
    }
  }

  // Read date fields
  if (fscanf(file, "%4s.%2s.%2s", date->Year, date->Month, date->Day) != 3) {
    printf("Error: Unable to read date from file\n");
    fclose(file);
    return 0; // Return 0 to indicate failure
  }

  fclose(file);
  return 1; // Return 1 to indicate success
}

void readAmountFromFile(const char *file_name, int lineNumber, float *amount) {
  FILE *file = fopen(file_name, "r");
  if (file == NULL) {
    printf("Error accessing file\n");
  }

  // Skip lines until reaching the desired line
  for (int i = 1; i < lineNumber; i++) {
    if (fscanf(file, "%*[^\n]%*c") == EOF) {
      printf("Error: Line number %d does not exist\n", lineNumber);
      fclose(file);
    }
  }

  // Read amount
  if (fscanf(file, "%f", amount) != 1) {
    printf("Error: Unable to read amount from file\n");
    fclose(file);
  }

  fclose(file);
}
