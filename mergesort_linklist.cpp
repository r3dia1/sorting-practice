#include <stdio.h>
#include <iostream>
using namespace std;

class node{
    public:
        int number;
        node* next;
        node(int a){number = a; next = NULL;};
};

void print_list(node* head){
    node* ptr = head;
    while(ptr != NULL)
    {
        cout << ptr->number << " ";
        ptr = ptr -> next;
    }
}

void spilt(node* list, node** a, node** b){
    int counter = 0;
    node* ptr = list;
    while(ptr != NULL)
    {
        counter++;
        ptr = ptr -> next;
    }

    counter = counter / 2;
    // cout << "counter = " << counter << endl;
    ptr = list;
    while(counter > 1)
    {
        counter--;
        // cout << ptr->number << " ";
        ptr = ptr -> next;
    }
    *a = list;
    *b = ptr -> next;
    ptr -> next = NULL;
}

void merge(node** list, node* a, node* b){
    node* ptr1 = a;
    node* ptr2 = b;
    node* tail;
    int flag = 0;

    while((ptr1 != NULL) || (ptr2 != NULL)){
        if((ptr1 != NULL) && (ptr2 != NULL))
        {
            // cout << "ptr1 : " << ptr1->number << endl;
            // cout << "ptr2 : " << ptr2->number << endl;
            if(ptr1->number <= ptr2->number)
            {
                if(flag == 0)
                {
                    flag = 1;
                    *list = ptr1;
                    tail = ptr1;
                    ptr1 = ptr1 -> next;
                }
                else
                {
                    tail -> next = ptr1;
                    tail = tail -> next;
                    ptr1 = ptr1 -> next;
                }
            }
            else
            {
                if(flag == 0)
                {
                    flag = 1;
                    *list = ptr2;
                    tail = ptr2;
                    ptr2 = ptr2 -> next;
                }
                else
                {
                    tail -> next = ptr2;
                    tail = tail -> next;
                    ptr2 = ptr2 -> next;
                }
            }
        }
        else if((ptr1 == NULL))
        {
            tail -> next = ptr2;
            tail = tail -> next;
            ptr2 = ptr2 -> next;
        }
        else if((ptr2 == NULL))
        {
            tail -> next = ptr1;
            tail = tail -> next;
            ptr1 = ptr1 -> next;
        }
    }
    return;
}

void mergesort(node** list){
    if((*list)->next == NULL)
        return;
    node* sub1;
    node* sub2;
    spilt(*list, &sub1, &sub2);

    // print_list(sub1);
    // cout << endl;
    // print_list(sub2);
    // cout << endl;

    mergesort(&sub1);
    mergesort(&sub2);
    merge(&*list, sub1, sub2);
    // print_list(*list);
}

int main(){
    node* list = NULL;
    cout << "Create number list: ";
    int num;
    node* ptr;
    while(cin >> num)
    {
        node* temp = new node(num);
        if(list == NULL)
        {
            list = temp;
            ptr = temp;
        }
        else
        {
            ptr->next = temp;
            ptr = temp;
        }
    }
    mergesort(&list);
    print_list(list);
}