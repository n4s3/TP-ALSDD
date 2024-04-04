#include "Funcs.h"
#include "Read-Write-Functions.h"
#include "AbstractMachine.h"
#include <stdlib.h>
#include <stdio.h>
// mazalou 3fays ki nhdru ntfhmu 3lihm nta t3rf khir mni fihm mn3rflhmch mlih 
void  main() {
     printf("\t\t\t  .----------------.  .----------------.  .----------------.\n");
    printf("\t\t\t | .--------------. || .--------------. || .--------------. |\n");
    printf("\t\t\t | |  _________   | || |    _______   | || |     _____    | |\n");
    printf("\t\t\t | | |_   ___  |  | || |   /  ___  |  | || |    |_   _|   | |\n");
    printf("\t\t\t | |   | |_  \\_|  | || |  |  (__ \\_|  | || |    | |     | |\n");
    printf("\t\t\t | |   |  _|  _   | || |   \'.___`-.   | || |     | |     | |\n");
    printf("\t\t\t | |  _| |___/ |  | || |  |`\\____) |  | || |     | |_    | |\n");
    printf("\t\t\t | | |_________|  | || |  |_______.\'  | || |    |____|   | |\n");
    printf("\t\t\t | |              | || |              | || |              | |\n");
    printf("\t\t\t | \'--------------\' || \'--------------\' || \'--------------\' |\n");
    printf("\t\t\t  \'----------------\'  \'----------------\'  \'----------------\'\n");
    printf("\t\t\t\tCPI - Universitory Year 2023/2024 \n", 138, 130, 130);
  printf("\t\t\t ___________________________________________________________________\n");
  printf("\t\t\t|                                                                   |\n");
  printf("\t\t\t| REALISE PAR : Nekhoul Mohamed Acil                                |\n");
  printf("\t\t\t|                              &                                    |\n");
  printf("\t\t\t|                          Belarbi Anes Abdelmalek                  |\n");
  printf("\t\t\t|                                                                   |\n");
  printf("\t\t\t|                                                                   |\n");
  printf("\t\t\t|         \tSECTION : B           GROUPE: 08                        |\n");
  printf("\t\t\t|                                                                   |\n");
  printf("\t\t\t|         \tTP1 : Linked Lists                                      |\n", 130, 130);
  printf("\t\t\t|                                                                   |\n");
  printf("\t\t\t|           \t      < Manipuation of linked Lists  >                |\n");
  printf("\t\t\t|                                                                   |\n");
  printf("\t\t\t|                                                                   |\n");
  printf("\t\t\t| ENCADRED By  :Mme Bouziane                                        |\n");
  printf("\t\t\t|___________________________________________________________________|\n\n\n");
  
   printf("\t\t\t _______________________________________________________________________________________ \n");
   printf("\t\t\t| Note !! Click Enter To Access The menu  .                                             |\n");
   printf("\t\t\t| To choose your option, press the corresponding number on the keyboard.                |\n");
   printf("\t\t\t|_______________________________________________________________________________________|\n");
   

   char c ; 
   int x ; 
   char passwod[100];
  BankAccount *HeadAccount = NULL ;
  readAccountInfo("Account.txt", HeadAccount);
   scanf("%i", &c);
   switch (c){
    case 13 : 
      printf("\t\t\t _______________________________________________________________________________________\n");
      printf("\t\t\t| Note !! The Last Three Operations  only Admin Can Uses Adim.                          |\n");
      printf("\t\t\t| Transfering amount from account to another :  Click 1.                                |\n");
      printf("\t\t\t| Deposit Fund to an Account  : Click 2.                                                |\n");
      printf("\t\t\t| Make a withdrawal of funds : Clcik 3.                                                 |\n");
      printf("\t\t\t| Check The Total Amount of an Account : Click 4.                                       |\n");
      printf("\t\t\t| Check the history of bank transactions within a given date : Click 5.                 |\n");  
      printf("\t\t\t| Delete Account Or Edit Custumer  And | Or Code: Click 6.                              |\n");
      printf("\t\t\t| Add New Account  : Click 7 .                                                          |\n");
      printf("\t\t\t|_______________________________________________________________________________________|\n");

      printf ("please Enter your choise The number must be between 1 and 6 . \n ");
      while (x>7 && x<1){
      printf ("please Enter your choise The number must be between 1 and 6 . \n ");
      scanf("%i",&x);
      }
     switch (x){
        case 1 : 
         BankAccount *p = HeadAccount;
         for (int i = 0; i < 3; i++){
          printf("Enter The sender's Number.");
           int SenderNum;
           readNumberFromFile("Account.txt",3,i+1,&SenderNum);
           printf("Enter The receiver's Number.");
           int ReceiverNum;
           readNumberFromFile("Account.txt",3,i+2,&ReceiverNum);
           printf("Sender, How much money do you want to Transfer?");
           float Amount;
           readAmountFromFile("Amount.txt",i,&Amount);
           Date D;// now we need to read the date from the file
           readDateFromFile("Date.txt",i+1,&D);
           TransferAmount(p,SenderNum,ReceiverNum,Amount,D);// call the function 
           }
           
    case 2 : 
    BankAccount *p=HeadAccount;
    int AccNumber;
    for (int i = 1; i <4 ; i++){
      printf("Enter the Number of Your Account.");
      readNumberFromFile("Account.txt",3,i,&AccNumber);
      printf("how much money do you want to depose.  ?");
      float Amount ; 
      readAmountFromFile("Amount.txt",i,&Amount);
      Date D ; 
      readDateFromFile("Date.txt",i,&D);
      Deposit(p,AccNumber,Amount,D);
         }
    case 3 : 
       BankAccount *p =HeadAccount;
       int AccNumber; 
       for (int i = 7 ; i < 9 ; i++){
        printf("Enter The Numbe of Your Account.");
        readNumberFromFile("Account.txt",3,i,&AccNumber);
        printf("How much money do you Want ?");
        float Amount;
        readAmountFromFile("Amount.txt",i,&Amount);
        Date D ; 
        readDateFromFile(p,i,&D);
       }
    case 4 : 
    BankAccount * p = HeadAccount;
    int AccNumber ;
    for (int i = 8 ; i < 10; i++){
      printf("Enter The Number fo Your Account ");
      readNumberFromFile("Account.txt",3,i,&AccNumber);
      printf("Here is Your Amount : %.2f",CheckAmount(p,AccNumber));
    }
    case 5: 
    BankAccount *p =HeadAccount;
    int AccNumber; 
    for (int i = 2 ; i < 5; i++){
    printf("enter your Account Number .");
    readNumberFromFile("Account.txt",3,i,&AccNumber);
    Date D; 
    readDateFromFile("Date.txt",i,&D);
    printf("Here is Your History .\n");
    CheckHistory(p,AccNumber,D);
    }
    case 6 : 
    BankAccount *p =HeadAccount;
      int pincode;
      scanf("%i",&pincode);
      if (pincode = 200517){
        printf("Enter The Number Of The Account. \n");
        int AccNumber ; 
        scanf("%i",&AccNumber);
        EditCodeAndOrCustumer(p,AccNumber);
      }else {
        printf("Pin Incorrect.\n");
      }
      case 7 : 
       BankAccount *p =HeadAccount;
       int pincode;
       scanf("%i",&pincode);
       BankAccount *New;
       createAccount(&New);
       if (pincode = 200517){
        if (HeadAccount == NULL){
        New = HeadAccount;

      }else {
      while (next_Account(temp) != NULL) {
        temp = next_Account(temp);
      }
      AssignAccount(temp , New);// link it the last one
      AssignAccount(New, NULL); // JUST inserting the New node at the tail of the 
    // list 
     }
    // now DATA assigning
      printf("Enter the account number : %d", AccNum);
      scanf("%d",&AccNum);
      printf("Enter the account code : %d", CodeNum);
      scanf("%d",&CodeNum);
      New->Number = AccNum;
      New->Code = CodeNum;
      char FirstNameAcc[15];
      char LastNameAcc[15];
      printf("Enter the customer\'s Fisrt Name : %s", FirstNameAcc);
      scanf("%s",FirstNameAcc);
      printf("Enter the custoome\'s Last Name : %s", LastNameAcc);
      scanf("%s",LastNameAcc);
      CopyCharArray(New->Name.First, FirstNameAcc);
      CopyCharArray(New->Name.Last, LastNameAcc);
    // setting the balance to 0 (conventional, I think)
      New->Balance = 0;
      AssignTranList(New->transactionList, NULL);
      DeleteAccount(New);

       }else 
       {
        printf("Pin Incorrect.\n");
       }
      
  }
           
                  
     }
for (int j = 0 ; i<11 ; j++){
 DeleteAccount(HeadAccount);
 HeadAccount =next_Account(HeadAccount);
}
}
