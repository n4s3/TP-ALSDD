#ifndef ABSTRACTMACHINE_H_INCLUDED
#define ABSTRACTMACHINE_H_INCLUDED
typedef struct Name {
  char First[15];
  char Last[15];
} Name;

// The record of the account Node Has a pointer to a next_account and the head of 
// the transactions list
// Date Record
struct Date {
  int Year[5];
  int Month[2];
  int Day[2];
};
typedef struct Date Date;
// The record of the transaction Node points to the next_transaction
struct Transaction {
  char opcode; // T:Transfer D:Deposit W:Withdrawal
  Date Date;
  float Balance;
 struct Transaction *nextTransaction;
};
typedef struct Transaction Transaction;

struct BankAccount {
  int Number;
  int Code;
  Name Name;
  float Balance;
  struct BankAccount *nextBAcc;
  Transaction *transactionList;
};
typedef struct BankAccount BankAccount;
// The AbstarctMachineFunctions
void createAccount(BankAccount **p); // malloc 
void DeleteAccount (BankAccount *p); // free
void AssignAccount(BankAccount *p ,BankAccount *q); // like assign adr 
void AssignListToBank(BankAccount *p , Transaction *q);// 
void AssignTranList(Transaction *p , Transaction *q); // like assign_adr(p,q);between nodes hab=ve the type transaction like AssignAccount 
BankAccount *next_Account(BankAccount *p);
Transaction *next_Transaction(Transaction *p);
// void AssignData(BankAccount *p , Transaction *q , int N , int c , Name Na , int b);
void CreateNewTran(Transaction **p);
void Ass_Date(Transaction *p ,Date D);
void AssignTranData(Transaction *p, Date D,char o, float B); // modified 
void AssignAccData(BankAccount *p, int N, int C, Name Na, float B); // modified
char *CopyCharArray(char *A, char *B);
void DeleteTran(Transaction *p);
void addAccountToList(BankAccount **head, char FirstName[15], char LastName[15],
                      int Number, int Code, float Balance);
void addTransactionToList(Transaction **head, char opcode, Date date,
                          float balance);
#endif
