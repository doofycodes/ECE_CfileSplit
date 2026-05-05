#include <stdio.h>
#include <math.h>
#include "bank.h"

void menu(double *pBalance, FILE *pF, struct account bankUsers[], int totalUsers, int userIdx) {
    int choice = 0;
    while (choice != 6) {
        printf("1. Deposit money\n2. Withdraw money\n3. Check Balance\n4. Transfer Money\n5. Print Statement\n6. Exit\n\nEnter your choice:");
        scanf("%d", &choice);
        switch (choice) {
            case 1: depo(pBalance, pF); break;
            case 2: with(pBalance, pF); break;
            case 3: printBalance(pBalance); break;
            case 4: transfer(bankUsers, totalUsers, userIdx, pF); break;
            case 5: printStatement(pF); break;
            case 6: printf("thank you!\n"); break;
            default: printf("invalid choice, try again\n\n");
        }
    }
}

void depo(double *pBalance, FILE *pF) {
    double amount;
    printf("Enter deposit amount: $");
    scanf("%lf", &amount);
    if (amount < 0) amount = 0; // Simple check
    *pBalance += amount;
    fprintf(pF, "Deposited $%.2lf\n   Balance: $%.2lf\n", amount, *pBalance);
    printf("\nDeposit successful\nNew balance: $%.2lf\n\n", *pBalance);
}

void with(double *pBalance, FILE *pF) {
    double amount;
    printf("Please enter withdrawal amount: $");
    scanf("%lf", &amount);
    while (amount < 0 || amount > *pBalance || fmod(amount, 20.0) != 0) {
        printf("Invalid amount or insufficient funds. Must be multiple of $20: $");
        scanf("%lf", &amount);
    }
    *pBalance -= amount;
    fprintf(pF, "Withdrew $%.2lf\n   Balance: $%.2lf\n", amount, *pBalance);
    printf("\nWithdrawal successful\nNew balance $%.2lf \n\n", *pBalance);
}

void printBalance(double *pBalance) {
    printf("your balance is: $%.2lf \n", *pBalance);
}

int auth(struct account bankUsers[], int totalUsers) {
    int tempID, tempPIN, attempts = 0;
    printf("hello what is your account number\n");
    scanf("%d", &tempID);
    for (int i = 0; i < totalUsers; i++) {
        if (tempID == bankUsers[i].id) {
            printf("Account found!\nPlease enter PIN:");
            while (attempts < 3) {
                scanf("%d", &tempPIN);
                if (tempPIN == bankUsers[i].pin) return i;
                attempts++;
                if (attempts < 3) printf("Incorrect PIN, try again: ");
            }
            return -1;
        }
    }
    return -2;
}

void transfer(struct account bankUsers[], int totalUsers, int userIdx, FILE *pF) {
    int tempAccount;
    double tAmount = 0.0;
    printf("\nPlease enter the account number you want to transfer to: ");
    scanf("%d", &tempAccount);
    if (tempAccount == bankUsers[userIdx].id) {
        printf("\nCannot transfer to self.\n");
        return;
    }
    for (int i = 0; i < totalUsers; i++) {
        if (tempAccount == bankUsers[i].id) {
            printf("Enter amount: $");
            scanf("%lf", &tAmount);
            bankUsers[userIdx].balance -= tAmount;
            bankUsers[i].balance += tAmount;
            fprintf(pF, "Transfered $%.2lf to %d\n   Balance $%.2lf\n", tAmount, bankUsers[i].id, bankUsers[userIdx].balance);
            printf("Transfer complete!\n");
            return;
        }
    }
}

void printStatement(FILE *pF) {
    fflush(pF);
    rewind(pF);
    char line[100];
    printf("\n-----Your Statement-----\n");
    while (fgets(line, sizeof(line), pF)) printf("%s", line);
    fseek(pF, 0, SEEK_END);
}

int loadAccounts(struct account bankUsers[]) {
    FILE *pF = fopen("accounts.dat", "rb");
    if (!pF) return 0;
    int count = fread(bankUsers, sizeof(struct account), 3, pF);
    fclose(pF);
    return count;
}

void saveAccounts(struct account bankUsers[], int totalUsers) {
    FILE *pF = fopen("accounts.dat", "wb");
    if (pF) {
        fwrite(bankUsers, sizeof(struct account), totalUsers, pF);
        fclose(pF);
    }
}
