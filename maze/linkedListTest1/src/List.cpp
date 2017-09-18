#include "List.h"
#include <cstdlib>
#include <iostream>
#include <stdio.h>
using namespace std;
List::List()
{
    head=NULL;
}

List::~List()
{

}
void List::AddNode(char addData)
{
    nodePtr n=new node;
    n->next=NULL;
    n->data=addData;
    if(head==NULL){head=n;curr=head;}
    else{
        curr->next=n;
        curr=n;
    }
}
void List::AddNode(int index,char addData)
{
    nodePtr assignNode=new node;
    assignNode->data=addData;
    if(index==0){assignNode->next=head;head=assignNode;}
    else
    {
        nodePtr tempStart=returnNode(index-1);
        nodePtr tempEnd=returnNode(index);
        tempStart->next=assignNode;
        assignNode->next=tempEnd;
    }
}
nodePtr List::returnNode(int index)
{
    nodePtr n=new node;
    int x=0;
    n=head;
    if(index==0){return n;}
    while(x!=index)
    {
        n=n->next;
        x++;
    }
    return n;
}
void List::DeleteNode(int index)
{
    nodePtr n=head;
    int x=1;
    if(index==0)
    {
        head=head->next;
    }
    else
    {
        while(x!=index)
        {
            n=n->next;
            x++;
        }
        n->next=n->next->next;
    }

 //   while(curr!=NULL)
}
void List:: PrintList()
{
    nodePtr n=head;
    while(n!=NULL)
    {
        cout<<n->data;
        n=n->next;
    }

}
