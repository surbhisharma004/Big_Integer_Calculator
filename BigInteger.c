#include "BigInteger.h"
#include <stdio.h>
#include <stdlib.h>

// Function to initialize a BigInteger
BigInteger* initialize() 
{
    BigInteger* bigInt = (BigInteger*)malloc(sizeof(BigInteger));
    bigInt->head = NULL;
    bigInt->tail = NULL;
    bigInt->sign = 1;
    return bigInt;
}

void atend(BigInteger* bigInt, int digit)
{
    Node* new = (Node*)malloc(sizeof(Node));
    new->digit = digit;
    new->next = NULL;
    new->prev = bigInt->tail;

    if (bigInt->tail) 
    {
        bigInt->tail->next = new;
    } else 
    {
        bigInt->head = new;
    }
    bigInt->tail = new;
}

BigInteger* createFromInt(int n)
 {
    BigInteger* bigInt = initialize();
    if (n < 0) 
    {
        bigInt->sign = -1;
        n = -n;
    }
    while (n) 
    {
        atend(bigInt, n % 10);
        n /= 10;
    }
    return bigInt;
}

void display(BigInteger* bigInt)
 {
    if (bigInt->sign == -1) 
       printf("-");
    Node* temp = bigInt->tail; 
    while (temp) 
    {
        printf("%d", temp->digit);
        temp = temp->prev;
    }
    printf("\n");
}

BigInteger* add(BigInteger* a, BigInteger* b)
 {
    // This function assumes both a and b are non-negative for simplicity.
    BigInteger* result = initialize();
    Node* A = a->head;
    Node* B = b->head;
    int carry = 0;

    while (A || B || carry) 
    {
        int sum = carry + (A ? A->digit : 0) + (B ? B->digit : 0);
        atend(result, sum % 10);
        carry = sum / 10;
        
        if (A) A = A->next;
        if (B) B = B->next;
    }
    return result;
}

int compare(BigInteger* a, BigInteger* b) 
{
    if (a->sign == 1 && b->sign == -1)
     return 1;
    if (a->sign == -1 && b->sign == 1) 
    return -1;
    int multiplier = a->sign; // since both numbers have the same sign
    Node* A = a->tail;
    Node* B = b->tail;
    while (A && B) 
    {
        if (A->digit != B->digit) 
        {
            return (A->digit >B->digit) ? 1 * multiplier : -1 * multiplier;
        }
        A = A->prev;
        B = B->prev;
    }
    if (A)
     return 1 * multiplier; // a is longer
    if (B)
     return -1 * multiplier; // b is longer
    return 0; // equal
}
BigInteger* sub(BigInteger* a, BigInteger* b) 
{
    int cmp = compare(a, b);
    if (cmp == 0) 
    {
        BigInteger* result = initialize();
        atend(result, 0);
        return result;
    }
    BigInteger* big = cmp > 0 ? a : b;
    BigInteger* small = cmp > 0 ? b : a;
    BigInteger* result = initialize();
    Node* tempB = big->head;
    Node* tempS = small->head;
    int borrow = 0;
    while (tempB)
     {
        int differnce  = tempB->digit - borrow - (tempS? tempS->digit : 0);
        if (differnce  < 0) 
        {
            differnce += 10;
            borrow = 1;
        } 
        else
        {
            borrow = 0;
        }
        atend(result, differnce);
        tempB= tempB->next;
        if (tempS) tempS = tempS->next;
    }
    // Handle negative results
    if (cmp < 0) result->sign = -1;
    // Removing leading zeros (if any)
    while (result->tail && result->tail->digit == 0) 
    {
        Node* temp = result->tail;
        result->tail = result->tail->prev;
        if (result->tail) result->tail->next = NULL;
        else result->head = NULL;
        free(temp);
    }
    return result;
}
BigInteger* copy(BigInteger* bigInt) 
{
    BigInteger* newInt = initialize();
    Node* current = bigInt->head;
    while (current)
    {
        atend(newInt, current->digit);
        current = current->next;
    }
    newInt->sign = bigInt->sign;
    return newInt;
}
BigInteger* div1(BigInteger* divi, BigInteger* divisor) 
{
    if (divisor==0) 
    {
        printf("Division by zero!\n");
        return NULL; // Division by zero is undefined.
    }
    BigInteger* quotient = initialize();
    BigInteger* Dividend = copy(divi);
    while (compare(Dividend, divisor) >= 0) 
    {
        Dividend = sub(Dividend, divisor);
        BigInteger* oldQ = quotient;
        quotient = add(quotient, createFromInt(1));
        // Clean up old quotient from previous iteration
        // This can be optimized further by incrementing the least significant digit of quotient directly
    }
    return quotient;
}
BigInteger* mod(BigInteger* divi, BigInteger* divisor) 
{
    if (divisor==0) 
    {
        printf("Division by zero!\n");
        return NULL; // Division by zero is undefined
    }
    BigInteger* Dividend = copy(divi);
    while (compare(Dividend, divisor) >= 0) 
    {
        BigInteger* Temp = Dividend;
        Dividend = sub(Dividend, divisor);
        free(Temp); // Cleaning up the temporary variable.
    }
    return Dividend; // The remainder after all possible subtractions.
}
BigInteger* mul(BigInteger* a, BigInteger* b) 
{
    BigInteger* prod = initialize();
    atend(prod, 0);  // Initialize to zero
    if (a==0|| b==0) 
    return prod;
    int posA = 0;
    for (Node* nodeA = a->head; nodeA != NULL; nodeA = nodeA->next)
    {
        BigInteger* temp = initialize();
        for (int i = 0; i < posA; i++)
        {
            atend(temp, 0);
        }
        int carry = 0;
        int posB = 0;
        for (Node* nodeB = b->head; nodeB != NULL; nodeB = nodeB->next)
         {
            int mult = nodeA->digit * nodeB->digit + carry;
            atend(temp, mult % 10);
            carry = mult / 10;
            posB++;
        }
        while (carry) 
        {
            atend(temp, carry % 10);
            carry /= 10;
        }
        BigInteger* old = prod;
        prod = add(prod, temp);
        free(old);
        free(temp);
        posA++;
    }
        prod->sign = a->sign * b->sign;
    return prod;
}
