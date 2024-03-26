#include <locale.h>
#include <stdio.h>
#include "AbstractMachine.h"
// for sprintf I suppose
#include <locale.h>
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
  AssignTranData(A,NewA, 'T', Date, Amount);

  Temp_B = B->transactionList;
  while (Temp_B != NULL) {
    Temp_B = next_Transaction(Temp_B);
  }

  Transaction *NewB;
  CreateNewTran(&NewB);
  (Temp_B)->nextTransaction = NewB;
  AssignTranData(B,NewB, 'D', Date, Amount);
}

int CheckAmount(BankAccount *A){
  return A->Balance;
}


// here we define a function to printout the date
static char Printdate(BankAccount *A){
  Date Date;
  int i;
  char Date_str[9] = {0};// to store the characters of the date arrays 
  // initialized with null terminator
  int n = 0;
  // we will use a function called sprintf to "convert" our array of integers into an array 
  // of characters 
  for (i=0; i<=4; ++i){
    n += sprintf (&Date_str[n], "%d.", A->transactionList->Date.Year[i]);
  }
  i = 0;
  for (i=0; i<=2; i++) {
    n += sprintf (&Date_str[n], "%d.", A->transactionList->Date.Month[i]);
  }
  i = 0;
  for (i=0; i<=2; i++) {
    n += sprintf (&Date_str[n], "%d", A->transactionList->Date.Day[i]);
  }
  return *Date_str;
}
void printData(Transaction * h ) {
  printf ("%c\n",opcode);
  Printf (" The Date of Opperation " );
  printf("  %c \ ", h->Date.Year);
  printf(" %c \ ",h-> Date.Month );
  printf(" %c ", h->Date.Day);
  printf("  the Balance is  : %f " , h->Balance );
}
  



void CheckHistory(BankAccount *A , Date D )
{
  Transaction *Temp;
  CreateNewTran(&Temp);
  Temp = A->transactionList ;
  if ( Temp = NULL ) {
    printf("there is no opperation in this account "); }else {

  while(Temp != NULL){
   if ( D = Temp -> Date ) {
     // we print the date so we create a new function to do this 
     printData(Temp );
     Temp =nextTransaction ( Temp );
     
  }else {
     Temp = nextTransaction (Temp) ;
        }
                    }
                                                             }
}


void Deposit(BankAccount *h, int Number, float De , Date D  ){
BankAccount p ; 
p =h;
while ( Number <> p->Number ) {
p = nextAcc(p);
} // to get the wanted acccount ; with the  number ;  
p -> Balalnce = p -> Balance + De ; 
Transaction *New_A ;
CreateNewTran(&New_A); // to put the new ooperation in this node ;
AssignTranData(h , New_A,'D', D , De) ; //assign data to the opperation 

Transaction *Temp_B; 
CreateNewTran(&Temp_B);
Temp_B= p -> TransactionList ; // to get the head of the opeeration ; 
 if ( Temp_B= NULL ){
 AssignList(h , Temp_ b);
while ( Temp_B != NULL ){
 Temp_B = next_Transaction (Temp_B);
}
AssignTranList( Temp_B , New_A);// assign to the anciet node the adress of the new node; 
AssignTranList( New_A , NULL); //  assign null to the new node;
 }
void Withdrawal(BankAccount *h , int Number , float De , Date D ) {
  BankAccount p ; 
p = h;
while ( Number <> p->Number ) {
p = nextAcc(p);
} // to get the  account we want  ; with the  number ;  
p -> Balalnce = p -> Balance - De ; 
Transaction *New_A ;
CreateNewTran(&New_A); // to put the new ooperation in this node ;
AssignTranData(h , New_A,'W', D , De) ; //assign data to the opperation 

Transaction *Temp_B; 
CreateNewTran(&Temp_B);
Temp_B= p -> TransactionList ; // to get the head of the opeerations ; 
 if ( Temp_B= NULL ){
 AssignList(h , Temp_ B);
while ( Temp_B != NULL ){
 Temp_B = next_Transaction (Temp_B);
}
AssignTranList( Temp_B , New_A);// assign to the ancient node the adress of the new node; 
AssignTranList( New_A , NULL); //  assign null to the new node;
}
void Deletecustomeraccount(BankAccount *h , int Number ){
  BankAccount p; 
  p= h; 
  while ( Number <> p->Number ) {
    p = nextAcc(p);
  }
  DeleteAccount( p) ; 
 }  // only the admin can do this and for more clarification BankAccount * h is the head of the list of the acccounts
void EditCodeAndOrCustumer( BankAccount * h , int Number ){
  pritnf (" what do you want to change Code or Custumer ? ")
  printf("\n");
  printf ( " the code ? Click 1 );
  printf("\n");
  printf ( " the customer ? Click 2 );
  printf("\n");
  printf ( " Both ? Click 3 );
  int x ;
  scanf ("enter your choice %i" , &x);
  switch (x){
      case 1 :
        BankAccount p ; 
        p =h;
        while ( Number <> p->Number ) {
           p = nextAcc(p);
               } // to get the wanted acccount ; with the  number ;
        pritnf ( "enter the new Code ") ;
        int Code ; 
        scanf ("%i " , &Code ); 
        p->Code = Code ;
      case  2 : 
                BankAccount p ; 
        p =h;
        while ( Number <> p->Number ) {
           p = nextAcc(p);
               } // to get the wanted acccount ; with the  number ;
        printf(" enter you new FirstName ");
        char FirstName[15];
        scanf ("%c",FirstName);
         
         
        
         
            
  

            
  


  

  







  
  
  
  


