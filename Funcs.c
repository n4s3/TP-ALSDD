#include <stdio.h>
#include "AbstractMachine.h"
#include "Funcs.h"
#include <stdlib.h>

void Deposit(BankAccount *h, int Number, float Amount , Date D  ){
  BankAccount *p; 
  createAccount(&p);
  p=h;
  while ( Number != p->Number ) {
    p = next_Account(p);
  } // to get the wanted acccount with the number
  p->Balance= p->Balance + Amount ; 
  Transaction *New_A;
  CreateNewTran(&New_A); // to put the new ooperation in this node
  AssignTranData(p , New_A,D,'D',Amount) ; //assign data to the opperation 
  Transaction *Temp_B; 
  CreateNewTran(&Temp_B);
  Temp_B = p -> transactionList ; // to get the head of the opeeration
  if ( Temp_B == NULL ){
    AssignListToBank(p , Temp_B);
    while ( Temp_B != NULL ){
      Temp_B = next_Transaction (Temp_B);
    }
    AssignTranList( Temp_B , New_A);// assign to the anciet node the adress of the new node
    AssignTranList( New_A , NULL); //  assign null to the new node
  }
}
void Deletecustomeraccount(BankAccount *h , int Number ){
  BankAccount *p; 
  p= h; 
  while ( Number != p->Number ) {
    p = next_Account(p);
  }
  DeleteAccount( p) ; 
}  // only the admin can do this and for more clarification BankAccount * h is the head of the list of the acccounts
void Withdrawal(BankAccount *h , int Number , float Amount , Date D ) {
  BankAccount *p;
  createAccount(&p);
  p = h;
  while ( Number != p->Number ) {
    p = next_Account(p);
  } // to get the  account we want  ; with the  number ;  
  p -> Balance= p -> Balance - Amount ; 
  Transaction *New_A ;
  CreateNewTran(&New_A); // to put the new ooperation in this node ;
  AssignTranData(p , New_A,D,'W',Amount) ; //assign data to the opperation 
  Transaction *Temp_B; 
  CreateNewTran(&Temp_B);
  Temp_B= p -> transactionList ; // to get the head of the opeerations ; 
  if ( Temp_B == NULL ){
    AssignListToBank(p , Temp_B);
  }
  while ( Temp_B != NULL ){
    Temp_B = next_Transaction (Temp_B);
  }
  AssignTranList( Temp_B , New_A);// assign to the ancient node the adress of the new node; 
  AssignTranList( New_A , NULL); //  assign null to the new node;
}
void TransferAmount(BankAccount *A, BankAccount *B, float Amount){
  // transfering 
  B->Balance = B->Balance + Amount;
  A->Balance = A->Balance - Amount;
  // creating the transaction nodes 
  // allocating a temptran
  Transaction *Temp_A;
  CreateNewTran(&Temp_A);
  Temp_A = A->transactionList;
  Transaction *Temp_B;
  CreateNewTran(&Temp_B);
  while (Temp_A != NULL) {
    Temp_A = next_Transaction(Temp_A);
  }
  Transaction *NewA;
  CreateNewTran(&NewA);
  Temp_A->nextTransaction = NewA;
  // This date is going to be changed of course 
  Date Date;
  AssignTranData(A,NewA, Date,'T', Amount);

  Temp_B = B->transactionList;
  while (Temp_B != NULL) {
    Temp_B = next_Transaction(Temp_B);
  }
  Transaction *NewB;
  CreateNewTran(&NewB);
  (Temp_B)->nextTransaction = NewB;
  AssignTranData(B,NewB, Date,'D',Amount);
  AssignTranList(NewB,NULL);
  AssignTranList(NewA,NULL);
}

int CheckAmount(BankAccount *A){
  return A->Balance;
}

// here we define a function to printout the date
char *Printdate(Transaction *A){
  Date Date;
  int i;
  char* Date_str = (char*)malloc(11 * sizeof(char));
  // initialized with null terminator
  int n = 0;
  // we will use a function called sprintf to "convert" our array of integers into an array 
  // of characters 
  for (i=0; i<=5; ++i){
    n += sprintf (&Date_str[n], "%d", A->Date.Year[i]);
  }
  i = 0;
  for (i=0; i<=2; i++) {
    n += sprintf (&Date_str[n], ".%d", A->Date.Month[i]);
  }
  i = 0;
  for (i=0; i<=2; i++) {
    n += sprintf (&Date_str[n], ".%d", A->Date.Day[i]);
  }
  Date_str[n] = '\0';
  return Date_str; // here we can't for example return *Date_str because
  // we will return the first char of the array Date_str
  // we used malloc to allocate memory for the local variable Date_str
  // so we can return it properly
}
static void printData(Transaction * h ) {
  printf ("%c\n",h->opcode);
  char *Date;
  Date = Printdate(h);
  printf (" The Date of Opperation %s", Date);
  printf("  the Balance is  : %f " , h->Balance );
}


void CheckHistory(BankAccount *A , Date D )
{
  Transaction *Temp;
  CreateNewTran(&Temp);
  Temp = A->transactionList ;
  if ( Temp == NULL ) {
    printf("there is no opperation in this account "); 
  }
  else {

    while(Temp != NULL){
      if (D.Day == Temp->Date.Day && D.Month == Temp->Date.Month && D.Year == Temp->Date.Year) {
        // we print the data so we create a new function to do this 
        printData(Temp);
        Temp =next_Transaction(Temp);
      } else {
        Temp = next_Transaction(Temp) ;
      }
    }
  }

}

void EditCodeAndOrCustumer( BankAccount * h , int Number ){
  printf("Admin !, what do you want to change ? \n");
  printf("Customer\'s Account Number: 1 \n");
  printf("Customer\'s Name: 2\n");
  printf("Delete Customer\'s Account: 3\n");
  printf("Add New Customer: 4\n");
  int x ;
  scanf ("enter your choice %i\n" , &x);
  switch (x){
    BankAccount *p; 
    BankAccount *New;
    createAccount(&New);
    createAccount(&p);
    int AccNum;
    int CodeNum;
    p=h;
      int c_num;
    case 1 :
      while ( Number != p->Number ) {
        p = next_Account(p);
      } // to get the wanted acccount ; with the  number ;
      printf( "enter the new Code ") ;
      int Code ; 
      scanf ("%i " , &Code ); 
      p->Code = Code ;
    case  2 : 
      while ( Number != p->Number ) {
        p = next_Account(p);
      } // to get the wanted acccount ; with the  number ;
      printf(" enter you new First Name");
      char FirstName[15];
      scanf ("%s",FirstName);
      printf(" enter you new Last Name");
      char LastName[15];
      scanf ("%s",LastName);
      CopyCharArray(h->Name.First, FirstName);
      CopyCharArray(h->Name.Last, LastName);
    case 3 :
      printf("Enter the customer\'s number : %d", c_num);
      scanf("%d", &c_num);
      Deletecustomeraccount(p, c_num);
    case 4 :
      if (h == NULL){
        New = h;
      }
      BankAccount *temp;
      createAccount(&temp);
      temp = h;
      while (temp != NULL) {
        temp = next_Account(temp);
      }
      AssignAccount(temp , New);// link it the last one
      AssignAccount(New, NULL); // JUST inserting the New node at the tail of the 
    // list
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
      scanf("%s",FirstNameAcc);
      printf("Enter the custoome\'s Last Name : %s", LastNameAcc);
      scanf("%s",l=LastNameAcc);
      CopyCharArray(New->Name.First, FirstNameAcc);
      CopyCharArray(New->Name.Last, LastNameAcc);
    // setting the balance to 0 (conventional, I think)
      New->Balance = 0;
      AssignTranList(New->transactionList, NULL);
  }
}
