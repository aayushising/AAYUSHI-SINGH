#include"BigInteger.h"


void rev_sign(struct node *head)
{
    if(head==0)return;
    head->info *= -1;
    rev_sign(head->next);
}

struct BigInteger initialise(char *s)
{
    struct BigInteger d;
    d.l=0;
    d.length=0;
    struct node *head=0;
    int i=0 ,j=0, sign=1;;
    if(s[i]=='-')
    {
        sign = -1;
        i++;
    }
    d.sign=sign;

    while(s[i]!='\n' && s[i]!='\0')
    {
        if(s[i]!='0')
        break;
        i++;
    }
    while (s[i]!='\n' && s[i]!='\0')
    {
        struct node *temp=(struct node *)malloc (sizeof(struct node));
        if(!temp)
        {
            printf("Memory Allocation failed\n");
            return d;
        }
        temp->info=s[i]-'0';
        temp->next=0;
        if(!head)
        {
            head=temp;
        }
        else
        {
            temp->next=head;
            head=temp;
        }
        i++;
        j++;
    }
    d.l=head;
    d.length=j;

    return d;
}

struct BigInteger add(struct BigInteger a,struct BigInteger b)
{
    if(a.sign == 1 && b.sign == 1 )
    {
        if(a.length<b.length)
        return addition_pp(b,a,1);
        return addition_pp(a,b,1);
    }
    else if(a.sign == -1 && b.sign == 1)
    {
        if(a.length<b.length)
        return addition_mp(b,a,1);
        if(a.length==b.length && comparision(a.l,b.l,0)==-1)
        return addition_mp(b,a,1);
        return addition_mp(a,b,-1);
    }
    else if(a.sign == 1 && b.sign == -1)
    {
        if(a.length<b.length)
        return addition_mp(b,a,-1);
        if(a.length==b.length && comparision(a.l,b.l,0)==-1)
        return addition_mp(b,a,-1);
        return addition_mp(a,b,1);
    }
    else if(a.sign == -1 && b.sign == -1)
    {
        if(a.length<b.length)
        return addition_pp(b,a,-1);
        return addition_pp(a,b,-1);
    }
}

struct BigInteger addition_pp(struct BigInteger a,struct BigInteger b , int sign)
{
    struct BigInteger d;
    d.sign=sign;
    d.length=a.length;
    d.l=0;
    struct node *head=0 , *q1=a.l , *q2=b.l, *p , *temp;
    int x,carry=0;

    while(q2)
    {
        temp=(struct node *)malloc (sizeof(struct node));
        if(!temp)
        {
            printf("Memory alloction failed. \n");
            return d;
        }

        x=q1->info+q2->info+carry;

        temp->info=x%10;
        carry=x/10;

        temp->next=0;
        if(!head)
        {
            head=temp;
            p=head;
        }
        else
        {
            p->next=temp;
            p=temp;
        }
        q1=q1->next;
        q2=q2->next;
    }
    while(q1)
    {
        temp=(struct node *)malloc (sizeof(struct node));
        if(!temp)
        {
            printf("Memory alloction failed. \n");
            return d;
        }
        temp->info=q1->info+carry;
        if(temp->info>0)
        {
            carry=temp->info/10;
            temp->info=temp->info%10;
        }
        else
        {
            carry=0;
        }
        temp->next=0;
        if(!head)
        {
            head=temp;
            p=head;
        }

        p->next=temp;
        p=temp;
        q1=q1->next;
    }
    if(carry!=0)
    {
        temp=(struct node *)malloc (sizeof(struct node));
        if(!temp)
        {
            printf("Memory alloction failed. \n");
            return d;
        }
        d.length+=1;
        p->next=temp;
        temp->info=carry;
        temp->next=0;
    }
    d.l=head;
    free(d);
    return d;
}

struct BigInteger addition_mp(struct BigInteger a, struct BigInteger b,int sign)
{
    struct BigInteger d;
    d.sign=sign;
    d.l=0;
    d.length=a.length;
    struct node *head=0 , *q1=a.l , *q2=b.l ,*temp , *p;
    int x,carry=0;
    rev_sign(q2);

    while(q2)
    {
        temp=(struct node *)malloc (sizeof(struct node));
        if(!temp)
        {
            printf("Memory alloction failed. \n");
            return d;
        }

        x=q1->info+q2->info+carry;

        if(x<0)
        {
            temp->info=x+10;
            carry=-1;
        }
        else
        {
            temp->info=x;
            carry=0;
        }

        temp->next=0;
        if(!head)
        {
            head=temp;
            p=head;
        }
        else
        {
            p->next=temp;
            p=temp;
        }
        q1=q1->next;
        q2=q2->next;
    }
    while(q1)
    {
        temp=(struct node *)malloc (sizeof(struct node));
        if(!temp)
        {
            printf("Memory alloction failed. \n");
            return d;
        }
        temp->info=q1->info+carry;
        if(temp->info<0)
        {
            temp->info=temp->info+10;
            carry=-1;
        }
        else
        {
            carry=0;
        }

        temp->next=0;
        if(!head)
        {
            p=head=temp;
        }

        p->next=temp;
        p=temp;
        q1=q1->next;
    }
    d.l=head;
    rev_sign(b.l);
    free(d);
    return d;
}

void free(struct BigInteger d)
{
    struct node *tempfront=0,*p=d.l;
    if(!d.l)
        return;
    while(p->next)
    {
        if(p->next->info==0 && tempfront==0)
        {
            tempfront=p;
            p=p->next;
            continue;
        }
        if(p->info!=0 && tempfront)
        {
            tempfront=0;
        }
        p=p->next;
    }
    if(p->info!=0)
    {
        tempfront=0;
    }

    if(tempfront)
    {
        p=tempfront;
        tempfront=tempfront->next;
        p->next=0;
        while(tempfront)
        {
            p=tempfront;
            tempfront=tempfront->next;
            free(p);
            d.length -=1;
        }
    }

}

void print(struct BigInteger c)
{
    struct node *p=c.l,*temp;
    if(!p)
    {
        printf("0\n");
        return;
    }
    if(c.sign==-1 && p->info || p->next && c.sign==-1)
    {
        printf("-");
    }
    print_ll(c.l);
    printf("\n");
}

void print_ll(struct node *head)
{
    if(!head)
    {
        return;
    }
    print_ll(head->next);
    printf("%d",head->info);
}

struct BigInteger sub(struct BigInteger a,struct BigInteger b)
{
    if(a.sign == 1 && b.sign == 1)
    {
        if(a.length<b.length)
        return addition_mp(b,a,-1);
        if(a.length==b.length && comparision(a.l,b.l,0)==-1)
        return addition_mp(b,a,-1);
        return addition_mp(a,b,1);
    }
    else if(a.sign == -1 && b.sign == 1)
    {
        if(a.length<b.length)
        return addition_pp(b,a,-1);
        return addition_pp(a,b,-1);
    }
    else if(a.sign == 1 && b.sign == -1)
    {
        if(a.length<b.length)
        return addition_pp(b,a,1);
        return addition_pp(a,b,1);
    }
    else if(a.sign == -1 && b.sign == -1)
    {
        if(a.length<b.length)
        return addition_mp(b,a,1);
        if(a.length==b.length && comparision(a.l,b.l,0)==-1)
        return addition_mp(b,a,1);
        return addition_mp(a,b,-1);
    }
}

struct BigInteger mul(struct BigInteger a,struct BigInteger b)
{
    if(!a.l || !b.l)
    {
        struct BigInteger d = {0 ,0 ,0};
        return d;
    }
    if(a.sign == 1 && b.sign == 1 || a.sign == -1 && b.sign == -1)
    {
        return product(a,b,1);

    }
    else
    {
        return product(a,b,-1);
    }

}

struct BigInteger product(struct BigInteger a , struct BigInteger b ,int sign)
{
    struct BigInteger d;
    d.l=0;
    d.sign=sign;
    struct node *pFront , *pt2 , *p , *head=0 , *q1=a.l , *q2=b.l;
    int i,x,carry,n=a.length+b.length;
    d.length=n;
    for (i=1;i<=n;i++)
    {
        struct node *temp=(struct node *)malloc (sizeof(struct node));
        if(!temp)
        {
            printf("Memory Allocation failed\n");
            return d;
        }
        temp->info=0;
        temp->next=0;
        if(!head)
        {
            head=temp;
        }
        else
        {
            temp->next=head;
            head=temp;
        }
    }
    d.l=head;

    p=pFront=head;

    while(q1)
    {
        pt2=q2;
        carry=0;
        while(pt2)
        {
            x=(q1->info)*(pt2->info)+carry;

            p->info += x;
            carry=(p->info)/10;
            p->info=(p->info)%10;

            pt2=pt2->next;
            p=p->next;
        }
        if(!pt2 && carry>0)
        {
            p->info += carry;
        }
        pFront=pFront->next;
        p=pFront;
        q1=q1->next;
    }
    free(d);
    return d;
}

void bin(struct BigInteger c)
{
    struct node *temp;
    while(c.l)
    {
        temp=c.l;
        c.l=c.l->next;
        free(temp);
    }
}


struct BigInteger div1(struct BigInteger a , struct BigInteger b )
{
    struct BigInteger d ={0 , 0 , 0};
    if(!b.l || !a.l)
    {
        printf("Invalid input\n");
        return d;
    }
    if(a.length<b.length)
    {
        return d;
    }
    else
    {
        if(a.sign == 1 && b.sign == 1 || a.sign == -1 && b.sign == -1)
        {

            return divide(a,b,1,1);

        }
        else
        {
            return divide(a,b,-1,1);
        }
    }
}

struct node *find_duplicate(struct node *head)
{
    struct node *k1=0,*p, *temp;
    while(head)
    {
        temp=(struct node *)malloc (sizeof(struct node));
        if(!temp)
        {
            printf("Memory alloction failed. \n");
            free(head);
            head=0;
            return head;
        }
        temp->info=head->info;
        temp->next=0;
        if(!k1)
        {
            k1=temp;
            p=temp;
        }
        else
        {
            p->next=temp;
            p=temp;
        }
        head=head->next;
    }
    return k1;
}


struct BigInteger divide(struct BigInteger a , struct BigInteger b , int sign , int ch)
{
    struct BigInteger d;
    d.l=0;
    d.length=0;
    d.sign=sign;
    int comp,length=b.length;
    struct node *head=0,*p,*temp ,*q2=b.l, *head_quotient=(struct node *) malloc(sizeof(struct node));
    if(!head_quotient)
    {
        printf("memory aloocation failed\n");
        return d;
    }
    if(a.length>b.length)
    {
        comp=1;
    }
    else
    {
        comp=comparision(a.l,q2,0);
    }
    printf("comp- %d\n",comp);

    if(comp<1)
    {
        if(comp==0)
        {
            if(ch==0)
            {
                return a;
            }
            head_quotient->info=1;
            head_quotient->next=0;
            d.l=head_quotient;
            d.length=1;
            return d;
        }
        if(ch ==0)
        {
            return a;
        }
        return d;
    }

    head=find_duplicate(q2);

    head_quotient->info=1;
    head_quotient->next=0;
    d.length=1;
    while(a.length>=length+1)
    {
        p=(struct node *) malloc(sizeof(struct node));
        temp=(struct node *) malloc(sizeof(struct node));
        if(!temp && !p)
        {
            printf("Memory allocation failed\n");
            return d;
        }
        temp->info=p->info=0;
        temp->next=head;
        head=temp;
        p->next=head_quotient;
        head_quotient=p;
        length+=1;

    }

    if((comp=comparision(a.l,head,0))==-1)
    {
        printf("%d\n",comp);
        temp=head;
        head=head->next;
        free(temp);
        temp=head_quotient;
        head_quotient=head_quotient->next;
        free(temp);
        length-=1;
    }
    while(a.length>length)
        divide_plus(head,b.l,head_quotient,&length);

    while((comp=comparision(a.l,head,0))!=-1)
        divide_plus(head,b.l,head_quotient,&length);


    if(comp==0)
    {
        if(ch==0)
        {
            d.l=head_quotient;
            bin(d);
            d.l=head;
            return d;
        }
        d.l=head;
        bin(d);
        d.l=head_quotient;
        return d;
    }
    if(comp==-1)
    {
        divide_minus(head,b.l,head_quotient);
    }
    if(ch == 0)
    {
        d.l=head_quotient;
        bin(d);
        d.l=head;
        free(d);
        return d;
    }
    d.l=head;
    bin(d);
    d.l=head_quotient;
    free(d);
    return d;
}

int comparision(struct node *k1 , struct node *h2, int d)
{
    static int x=0;
    x=d;

    if(!k1 && !h2)
    {
        return x;
    }
    comparision(k1->next,h2->next,d);

    if(x==-1)
        return x;
    else if(k1->info>h2->info)
    {
        x=1;
    }
    else if(k1->info<h2->info && x==0)
    {
        x=-1;
    }

    return x;
}

void divide_plus(struct node *q1 ,struct node *q2 ,struct node *q3 , int *l)
{
    struct node *temp=0 ,*ptr;
    int x,carry=0;
    while(q2)
    {

        q1->info=q1->info+q2->info+carry;
        carry=(q1->info)/10;
        q1->info=(q1->info)%10;
        q1=q1->next;
        q2=q2->next;
    }
    while(q1)
    {
        if(q1->next==0)
        {
            ptr=q1;
        }
        q1->info=q1->info+carry;
        carry=(q1->info)/10;
        q1->info=(q1->info)%10;
        if(carry==0)
        {
            break;
        }
        q1=q1->next;
    }
    if(carry!=0)
    {
        temp=(struct node *)malloc (sizeof(struct node));
        if(!temp)
        {
            printf("Memory alloction failed. \n");
            return;
        }
        ptr->next=temp;
        temp->info=carry;
        temp->next=0;
        *l+=1;
    }
    carry=1;
    while(q3)
    {
        q3->info=q3->info+carry;
        carry=(q3->info)/10;
        q3->info=(q3->info)%10;
        q3=q3->next;
        if(carry==0)
        {
            return;
        }
    }

}

void divide_minus(struct node *q1 ,struct node *q2 ,struct node *q3 )
{
    struct node *ptr=q2;
    int x,carry=0;
    rev_sign(q2);

    while(q2)
    {
        q1->info=q1->info+q2->info+carry;

        if(q1->info<0)
        {
            q1->info=q1->info+10;
            carry=-1;
        }
        else
        {
            carry=0;
        }

        q1=q1->next;
        q2=q2->next;
    }
    while(q1)
    {
        q1->info=q1->info+carry;
        if(q1->info<0)
        {
            q1->info=q1->info+10;
            carry=-1;
        }
        else
        {
            carry=0;
        }
        if(carry==0)
        {
            break;
        }
        q1=q1->next;

    }
    rev_sign(ptr);

    carry=-1;
    while(q3)
    {
        q3->info=q3->info+carry;
        if(q3->info<0)
        {
            q3->info+=10;
            carry=-1;
        }
        else
        {
            carry=0;
        }
        if(carry==0)
        {
            return;
        }
        q3=q3->next;
    }
}

struct BigInteger mod(struct BigInteger a , struct BigInteger b)
{
    struct BigInteger d ={0 , 0 , 0};
    if(!b.l || !a.l)
    {
        printf("Invalid input\n");
        return d;
    }
    if(a.length<b.length)
    {
        return a;
    }
    else
    {
        if(a.sign == 1 && b.sign == 1 || a.sign == -1 && b.sign == -1)
        {

            d = divide(a,b,1,0);

        }
        else
        {
            d = divide(a,b,-1,0);
        }
    }
    if(comparision(a.l,d.l,0)==0)
    return a;
    return modulus_sub(a,d);
}

struct BigInteger modulus_sub(struct BigInteger a , struct BigInteger b)
{
    struct BigInteger d;
    d.sign=1;
    d.l=0;
    d.length=a.length;
    struct node *head=0 , *q1=a.l , *q2=b.l ,*temp , *p;
    int x,carry=0;
    rev_sign(q2);

    while(q2)
    {
        temp=(struct node *)malloc (sizeof(struct node));
        if(!temp)
        {
            printf("Memory alloction failed. \n");
            return d;
        }

        x=q1->info+q2->info+carry;

        if(x<0)
        {
            temp->info=x+10;
            carry=-1;
        }
        else
        {
            temp->info=x;
            carry=0;
        }
        temp->next=0;
        if(!head)
        {
            head=temp;
            p=head;
        }
        else
        {
            p->next=temp;
            p=temp;
        }
        q1=q1->next;
        q2=q2->next;
    }
    while(q1)
    {
        temp=(struct node *)malloc (sizeof(struct node));
        if(!temp)
        {
            printf("Memory alloction failed. \n");
            return d;
        }
        temp->info=q1->info+carry;
        if(temp->info<0)
        {
            temp->info=temp->info+10;
            carry=-1;
        }
        else
        {
            carry=0;
        }

        temp->next=0;
        if(!head)
        {
            p=head=temp;
        }

        p->next=temp;
        p=temp;
        q1=q1->next;
    }
    d.l=head;
    rev_sign(b.l);
    free(d);
    return d;
}

