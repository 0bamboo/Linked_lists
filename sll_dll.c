#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include <unistd.h>
#include <unistd.h>

// Example of singly linked list :
typedef struct s_llist
{
    int a;
    struct s_llist *next;
}               p_llist;


// Example of doubly linked list :
typedef struct d_list
{
    int a;
    struct d_list *next;
    struct d_list *prev;
}               dd_list;


// Push front of a singly linked list :
void _push_front_(p_llist **head, int c)
{
    p_llist *new;

    new = (p_llist *)malloc(sizeof(p_llist));
    new->a = c;
    new->next = *head;
    *head = new;
}


// Push back and return the head of a singly linked list :
p_llist *_push_back_return(p_llist *head, int c)
{
    p_llist *new;

    new = (p_llist *)malloc(sizeof(p_llist));
    if (head == NULL)
    {
        head = new;
        head->a = c;
        head->next = NULL;
    }
    else
    {
        while (head->next)
            head = head->next;
        head->next = new;
        new->a = c;
        new->next = NULL;
    }
    return head;
    // you need to assign this return of struct to the same variable of list that you send in args of this function
}


// Push back using reference of the working singly linked list :
void _push_back_(p_llist **head, int c)
{
    p_llist *new;

    new = (p_llist *)malloc(sizeof(p_llist));
    new->a = c;
    new->next = NULL;
    if ((*head) == NULL)
        (*head) = new;
    else
    {
        while((*head)->next)
            (*head) = (*head)->next;
        (*head)->next = new;
    }
}


int     _pop_the_first_node(p_llist **head)
{
    int retval;
    p_llist *new_node;

    retval = -1;
    if (head == NULL)
        return retval;
    new_node = NULL;
    new_node = (*head)->next;
    retval = (*head)->a;
    free(*head);
    (*head) = new_node;
    return retval;
}



int     _pop_the_last_node(p_llist **head)
{
    int retval;
    p_llist *current;

    // this one is for a list contains one node : 
    if ((*head)->next == NULL)
    {
        retval = (*head)->a;
        free((*head));
        (*head) = NULL;
        return retval;
    }
    current = *head;
    // Traverse untill you reach the second last node :
    while (current->next->next != NULL)
        current = current->next;
    // Get the value of the last node :
    retval = current->next->a;
    free(current->next);
    current->next = NULL;
    return retval;
}


int _pop_a_specific_node(p_llist **head, int val)
{
    p_llist *current;
    p_llist *tmp;
    int retval;

    tmp = NULL;
    current = *head;
    if (val == current->a)
        return (_pop_the_first_node(head));
    while(current->next->a != val)
    {
        if (current->next == NULL)
            return -1;
        current = current->next;
    }
    tmp = current->next;
    retval = tmp->a;
    current->next = tmp->next;
    free(tmp);
    return retval;
}


void    _push_front_dll(dd_list **head, int val)
{
    dd_list *insert;

    //In case of OVERFLOW
    if (!(insert = (dd_list *)malloc(sizeof(dd_list))))
        exit (0);
    if (!(*head))
    {
        insert->prev = NULL;
        insert->a = val;
        insert->next = NULL;
        *head = insert;
    }
    else
    {
        insert->prev = NULL;
        insert->a = val;
        insert->next = *head;
        (*head)->prev = insert;
        *head = insert;
    }
}


void        _push_back_dll(dd_list **head, int val)
{
    dd_list *insert;

    // In case of overflow
    if (!(insert = (dd_list *)malloc(sizeof(dd_list))))
        exit (0);
    insert->a = val;
    insert->prev = NULL;
    insert->next = NULL;
    if (!(*head))
        (*head) = insert;
    else
    {
        while ((*head)->next)
            (*head) = (*head)->next;
        (*head)->next = insert;
    }
}

// Try to use the tmp for every head you use ....

void        _push_after_specific_node_dll(dd_list **head, int spec, int val)
{
    dd_list *insert;
    dd_list *tmp;

    if (!(*head))
        exit (0);
    if (!(insert = (dd_list *)malloc(sizeof(dd_list))))
        exit (0);
    while ((*head)->next && (*head)->next->a != spec)
        (*head) = (*head)->next;
    tmp = (*head)->next;
    if (tmp && tmp->a == spec)
    {
        insert->a = val;
        insert->prev = tmp;
        insert->next = tmp->next;
        tmp->next->prev = insert;
        tmp->next = insert;
    }
}


void        _push_before_specific_node_dll(dd_list **head, int spec, int val)
{
    dd_list *insert;
    dd_list *tmp;

    if (!(*head))
        exit (0);
    if (!(insert = (dd_list *)malloc(sizeof(dd_list))))
        exit (0);
    while ((*head)->next != NULL && ((*head)->next->a != spec))
        (*head) = (*head)->next;
    if ((*head)->next && (*head)->next->a == spec)
    {
        tmp = (*head)->next;
        insert->a = val;
        insert->next = tmp;
        insert->prev = (*head);
        tmp->prev = insert;
        (*head)->next = insert;
    }
}


int main(void)
{
    p_llist *head;
    p_llist *traverse;
    p_llist *test1;
    p_llist *test2;
    dd_list *head_dd;
    dd_list *trav_dd;
    dd_list *t2_dd;
    dd_list *t1_dd;
    int i;


    // // SINGLY LINKED LIST :

    // head = (p_llist *)malloc(sizeof(p_llist));
    head = NULL;
    // if you allocated the head you should assign head to trav ... but if you do not allocated the head you should assign it inside the loop ....> traverse = head;
    i = -1;
    while (++i < 10)
    {
        // traverse = _push_back_return(traverse, i);
        _push_back_(&head, i);
        // Hold the address of first node if head is NULL
        if (i == 0)
            traverse = head;
    }
    i = -1;
    // Push front the numbers from 0 to 9
    while (++i < 10)
        _push_front_(&traverse, i);

    printf("The original: \n");
    test1 = traverse; 
    // Print the all the shit inside of list : 
    while (test1)
    {
        printf("%d-", test1->a);
        test1 = test1->next;
    }
    printf("\npop : %d\n", _pop_the_last_node(&traverse));
    printf("pop : %d\n", _pop_a_specific_node(&traverse, 0));
    // Print the all the shit inside of list :
    test2 = traverse;
    while (test2)
    {
        printf("%d-", test2->a);
        test2 = test2->next;
    }
    puts("");


    // DOUBLY LINKED LIST :

    head_dd = NULL;
    i = -1;
    // Push front for doubly linked list :
    while (++i < 14)
        _push_front_dll(&head_dd, i);
    t1_dd = head_dd;
    t2_dd = head_dd;
    dd_list *test;
    test = head_dd;
    printf("Forward :\n");
    while (t1_dd->next)
    {
        printf(" %d^", t1_dd->a);
        t1_dd = t1_dd->next;
    }
    _push_after_specific_node_dll(&head_dd, 0, 99);
    // _push_before_specific_node_dll(&test, 5, 88);
    printf("%d\n", t1_dd->a);
    printf("Backward : \n");
    while (t1_dd->prev)
    {
        printf("%d^", t1_dd->a);
        t1_dd = t1_dd->prev;
    }
    printf("%d\n", t1_dd->a);
    puts("push back and then print everything : ");
    i = 13;
    while (++i < 20)
        _push_back_dll(&test, i);
    while (t2_dd)
    {
        printf(" | %d", t2_dd->a);
        t2_dd = t2_dd->next;
    }
    puts("");
    return 0;
}