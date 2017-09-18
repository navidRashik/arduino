#ifndef LIST_H
#define LIST_H

typedef struct node{
            char data;
            int index;
            node* next;
        }* nodePtr;
class List
{
    private:

        nodePtr head;
        nodePtr curr;
        nodePtr temp;
    public:
        List();
        void AddNode(char addData);
        void AddNode(int index,char addData);
        void DeleteNode(int index);
        void PrintList();
        nodePtr returnNode(int index);
        virtual ~List();
    protected:

};

#endif // LIST_H
