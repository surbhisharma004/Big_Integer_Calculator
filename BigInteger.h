
#ifndef BIG_INTEGER_H
#define BIG_INTEGER_H

typedef struct Node {
    int digit;
    struct Node* next;
    struct Node* prev;
} Node;

typedef struct BigInteger {
    Node* head;
    Node* tail;
    int sign; // 1 for positive, -1 for negative
} BigInteger;

BigInteger* initialize();
void appendDigit(BigInteger* bigInt, int digit);
BigInteger* createFromInt(int num);
void display(BigInteger* bigInt);
BigInteger* add(BigInteger* a, BigInteger* b);
BigInteger* sub(BigInteger* a, BigInteger* b);

BigInteger* div1(BigInteger* dividend, BigInteger* divisor);

BigInteger* mod(BigInteger* dividend, BigInteger* divisor);
BigInteger* mul(BigInteger* a, BigInteger* b);


#endif
