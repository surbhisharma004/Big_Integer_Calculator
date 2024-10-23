#include "BigInteger.h"
#include <stdio.h>

int main() {
   long long int a, b, choice;
    printf("Enter two integers:\n");
    scanf("%lld %lld", &a, &b);
    BigInteger* num1 = createFromInt(a);
    BigInteger* num2 = createFromInt(b);
    BigInteger* sum;
    BigInteger* difference;
    BigInteger* quotient;
    BigInteger* remainder;
     BigInteger* product;


    printf("Enter choice\n");
    printf("\t 1 for addition \n");
    printf("\t 2 for subtraction \n");
    printf("\t 3 for multiplication \n");
    printf("\t 4 for division \n");
    printf("\t 5 for modulus \n");
    scanf("%lld", &choice);

    switch(choice) {
        case 1: 
            sum = add(num1, num2);
            printf("Sum: ");
            display(sum);
            break;

        case 2: 
            difference = sub(num1, num2);
            printf("Difference: ");
            display(difference);
            break;
        case 3: product = mul(num1, num2);
               printf("Product: ");
               display(product);
               break;
        case 4:
            quotient = divi(num1, num2);
            printf("Quotient: ");
            display(quotient);
            break;
        case 5:
            remainder =mod(num1, num2);
            printf("Remainder: ");
            display(remainder);
            break;
        default:
            printf("Invalid choice");      
    }
    return 0;
}
