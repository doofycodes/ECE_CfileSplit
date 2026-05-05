#include <stdio.h>
#include "bank.h"

int main() {
    struct account bankUsers[3];
    int totalUsers = 3;

    if (loadAccounts(bankUsers) == 0) {
        printf("No save file found. Initializing default accounts...\n");
        bankUsers[0] = (struct account){101, 1234, 100.0};
        bankUsers[1] = (struct account){102, 4321, 200.0};
        bankUsers[2] = (struct account){103, 1111, 300.0};
    } else {
        printf("Account data loaded successfully!\n");
    }

    int userIdx = auth(bankUsers, totalUsers);
    if (userIdx < 0) {
        printf("Authentication failed. Goodbye!\n");
        return 0;
    }

    FILE *pF = fopen("Statement.txt", "w+");
    fprintf(pF, "-----Welcome to your statement-----\n\n");

    printf("\nHello, welcome to Gbank\n");
    menu(&bankUsers[userIdx].balance, pF, bankUsers, totalUsers, userIdx);

    saveAccounts(bankUsers, totalUsers);
    fclose(pF);
    return 0;
}
