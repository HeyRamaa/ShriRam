
#include<stdio.h>
#include<stdlib.h>
struct polynomial
{
    int coeff,exp;
    struct polynomial *next;
};
struct polynomial *add(struct polynomial *poly1,struct polynomial *poly2)
{
    struct polynomial *p3,*head,*poly3;
    head = NULL;
    struct polynomial *p1 = poly1;
    struct polynomial *p2 = poly2;

    while(p1!=NULL && p2!=NULL)
    {
        if(p1->exp==p2->exp)
        {
            p3 = (struct polynomial*)malloc(sizeof(struct polynomial));
            p3->coeff = p1->coeff + p2->coeff;
            p3->exp=p1->exp;
            p3->next = NULL;
            p1 = p1->next;
            p2 = p2->next;
        }
        else if(p1->exp > p2->exp)
        {
            p3 = (struct polynomial*)malloc(sizeof(struct polynomial));
            p3->coeff = p1->coeff;
            p3->exp = p1->exp;
            p3->next=NULL;
            p1 = p1->next;
        }
        else
        {
            p3 = (struct polynomial*)malloc(sizeof(struct polynomial));
            p3->coeff = p2->coeff;
            p3->exp = p2->exp;
            p3->next=NULL;
            p2 = p2->next;
        }
        if(head==NULL)
        {
            head = p3;
            poly3 = head;
        }
        else
        {
            poly3->next = p3;
            poly3 = p3;
        }
    }

        while(p1!=NULL)
        {
            p3 = (struct polynomial*)malloc(sizeof(struct polynomial));
            p3->coeff = p1->coeff;
            p3->exp = p1->exp;
            p3->next=NULL;
            if(head==NULL)
            {
                head = p3;
                poly3 = head;
            }
            else
            {
                poly3->next = p3;
                poly3 = p3;
            }
            p1 = p1->next;
        }

        while(p2!=NULL)
        {
            p3 = (struct polynomial*)malloc(sizeof(struct polynomial));
            p3->exp = p2->exp;
            p3->coeff = p2->coeff;
            p3->next=NULL;

            if(head==NULL)
            {
                head = p3;
                poly3 = head;
            }
            else
            {
                poly3->next = p3;
                poly3 = p3;
            }
            p2 = p2->next;
        }

    return (head);
}

void sort(struct polynomial *head)
{
    struct polynomial *temp1 , *temp2;
    int a;
    temp1 = head;

    while(temp1!=NULL)
    {
         temp2=head;
         while(temp2!=NULL)
        {
            if(temp1->exp > temp2->exp)
            {
                a = temp1->coeff;
                temp1->coeff = temp2->coeff;
                temp2->coeff = a;

                a = temp1->exp;
                temp1->exp = temp2->exp;
                temp2->exp = a;
            }
            temp2 = temp2->next;
        }
        temp1 = temp1->next;
    }

}

struct  polynomial *create(int size)
{
    struct polynomial *head,*current,*ptr;
    head = NULL;

		int i;
        for(i=0;i<size;i++)
        {
            printf("Enter the coefficent %d and exponent %d: ",i+1,i+1);
            current = (struct polynomial*)malloc(sizeof(struct polynomial));
            scanf("%d%d",&current->coeff,&current->exp);
            current->next = NULL;
            if(head==NULL)
            {
                head = current;
                ptr = head;
            }
            else
            {
                ptr->next = current;
                ptr = current;
            }
        }
        sort(head);

        return (head);
}

void display(struct polynomial * poly)
{
    struct polynomial * p = poly;

    while(p!=NULL && p->coeff != 0)
    {
        printf("%dx^%d",p->coeff,p->exp);

        if(p->next != NULL && p->next->coeff !=0)
        {
            printf(" + ");
        }
        p = p->next;
    }
}

int main()
{
    int n,m;
    struct polynomial *poly1,*poly2,*poly3;
    printf("Enter the size of 1st polynomial and 2nd polynomial : ");
    scanf("%d%d",&n,&m);

    printf("\nEnter the first Polynomial...\n");
    poly1 = create(n);
    printf("\n");
    printf("\nEnter the second Polynomial...\n");
    poly2 = create(m);

    printf("\n1st Polynomial...\n");
    display(poly1);
    printf("\n");
    printf("\n2nd Polynomial...\n");
    display(poly2);
    printf("\n\n");
    printf("Addition of 2 Polynomial...\n");
    poly3 = add(poly1,poly2);
    display(poly3);
    printf("\n");
    return 0;

}
