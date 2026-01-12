#include <stdio.h>
#include <string.h>


int main()
{
    char item[50] = "";
    float price = 0.0f;
    int quantity = 0;
    float total = 0.0f;

    printf("Enter the item name: ");
    fgets(item, sizeof(item), stdin);
    item[strlen(item) - 1] = '\0';

    printf("Enter the price: ");
    scanf("%f", &price);

    printf("Enter the quantity: ");
    scanf("%d", &quantity);

    printf("You bought %d %s(s)\n", quantity, item);

    total = quantity * price;
    printf("Total: $%.2f\n", total);

    return 0;
}
