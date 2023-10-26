#include<stdio.h>
#include<stdlib.h>

struct node {
    int data;
    struct node *next;
};

struct BigInteger
{
    struct node *l;
    int sign;
    int length;
};

void rev_sign(struct node *head);
struct BigInteger initialise(char *s);


struct BigInteger add(struct BigInteger a,struct BigInteger b);
struct BigInteger addition_pp(struct BigInteger a,struct BigInteger b,int sign);
struct BigInteger addition_mp(struct BigInteger a,struct BigInteger b,int sign);



struct BigInteger sub(struct BigInteger a,struct BigInteger b);

struct BigInteger mul(struct BigInteger a,struct BigInteger b);
struct BigInteger product(struct BigInteger a , struct BigInteger b ,int sign);

struct BigInteger div1(struct BigInteger a , struct BigInteger b );
struct BigInteger divide(struct BigInteger a , struct BigInteger b , int sign , int ch);
void div_plus(struct node *q1 ,struct node *q2 ,struct node *q3 ,int *l );
void div_minus(struct node *q1 ,struct node *q2 ,struct node *q3 );
int comparision(struct node *h1 , struct node *h2, int d);

void print(struct BigInteger c);
void print_ll(struct node *head);

void free(struct BigInteger d);

void bin(struct BigInteger c);

struct BigInteger mod(struct BigInteger a , struct BigInteger b);
struct BigInteger modulus_sub(struct BigInteger a , struct BigInteger b);
