#include <iostream>
#include "List.h"
using namespace std;

List calculateVal(List dir)
{
    while(true)
    {
        bool flag=false;
        nodePtr node0,node1,node2;
        int x=0;
        if(dir.returnNode(x)!=NULL){node0=dir.returnNode(x);}else{break;}
        if(dir.returnNode(x+1)!=NULL){node1=dir.returnNode(x+1);}else{break;}
        if(dir.returnNode(x+2)!=NULL){node2=dir.returnNode(x+2);}else{break;}
        while(true)
        {
            if(node0->data=='l'&&node1->data=='b'&&node2->data=='r')
                {dir.DeleteNode(x);dir.DeleteNode(x);dir.DeleteNode(x);dir.AddNode(x,'b');flag=true;}
            else if(node0->data=='l'&&node1->data=='b'&&node2->data=='s')
                {dir.DeleteNode(x);dir.DeleteNode(x);dir.DeleteNode(x);dir.AddNode(x,'r');flag=true;}
            else if(node0->data=='r'&&node1->data=='b'&&node2->data=='l')
                {dir.DeleteNode(x);dir.DeleteNode(x);dir.DeleteNode(x);dir.AddNode(x,'b');flag=true;}
            else if(node0->data=='s'&&node1->data=='b'&&node2->data=='l')
                {dir.DeleteNode(x);dir.DeleteNode(x);dir.DeleteNode(x);dir.AddNode(x,'r');flag=true;}
            else if(node0->data=='s'&&node1->data=='b'&&node2->data=='s')
                {dir.DeleteNode(x);dir.DeleteNode(x);dir.DeleteNode(x);dir.AddNode(x,'b');flag=true;}
            else if(node0->data=='l'&&node1->data=='b'&&node2->data=='l')
                {dir.DeleteNode(x);dir.DeleteNode(x);dir.DeleteNode(x);dir.AddNode(x,'s');flag=true;}

            if(dir.returnNode(x)->next!=NULL){node0=dir.returnNode(x+1);}else{break;}
            if(dir.returnNode(x+1)->next!=NULL){node1=dir.returnNode(x+2);}else{break;}
            if(dir.returnNode(x+2)->next!=NULL){node2=dir.returnNode(x+3);}else{break;}
            x++;
        }

        cout<<"\n";
        if(flag==false){break;}
    }

    //for return maze// else return dir to start from beginning
    List next;
    while(true){
        if(dir.returnNode(0)->data=='l'){next.AddNode(0,'r');}
        else if(dir.returnNode(0)->data=='r'){next.AddNode(0,'l');}
        else{next.AddNode(0,dir.returnNode(0)->data);}

        if(dir.returnNode(0)->next==NULL){break;}
        dir.DeleteNode(0);
    }
    //dir.PrintList();
    return next;
}
int main()
{
    List dir;
    while(true){
        char c;
        cout<<"Enter : ";
        cin>>c;
        if(c=='o'){break;}
        dir.AddNode(c);
    }
    List aku=calculateVal(dir);
    aku.PrintList();


    //next.PrintList();
}

/*int main()
{
    List dir;
    while(true){
        char c;
        cout<<"Enter : ";
        cin>>c;
        if(c=='o'){break;}
        dir.AddNode(c);
    }
    while(true)
    {
        bool flag=false;
        nodePtr node0,node1,node2;
        int x=0;
        if(dir.returnNode(x)!=NULL){node0=dir.returnNode(x);}else{break;}
        if(dir.returnNode(x+1)!=NULL){node1=dir.returnNode(x+1);}else{break;}
        if(dir.returnNode(x+2)!=NULL){node2=dir.returnNode(x+2);}else{break;}
        while(true)
        {
            if(node0->data=='l'&&node1->data=='b'&&node2->data=='r')
                {dir.DeleteNode(x);dir.DeleteNode(x);dir.DeleteNode(x);dir.AddNode(x,'b');flag=true;}
            else if(node0->data=='l'&&node1->data=='b'&&node2->data=='s')
                {dir.DeleteNode(x);dir.DeleteNode(x);dir.DeleteNode(x);dir.AddNode(x,'r');flag=true;}
            else if(node0->data=='r'&&node1->data=='b'&&node2->data=='l')
                {dir.DeleteNode(x);dir.DeleteNode(x);dir.DeleteNode(x);dir.AddNode(x,'b');flag=true;}
            else if(node0->data=='s'&&node1->data=='b'&&node2->data=='l')
                {dir.DeleteNode(x);dir.DeleteNode(x);dir.DeleteNode(x);dir.AddNode(x,'r');flag=true;}
            else if(node0->data=='s'&&node1->data=='b'&&node2->data=='s')
                {dir.DeleteNode(x);dir.DeleteNode(x);dir.DeleteNode(x);dir.AddNode(x,'b');flag=true;}
            else if(node0->data=='l'&&node1->data=='b'&&node2->data=='l')
                {dir.DeleteNode(x);dir.DeleteNode(x);dir.DeleteNode(x);dir.AddNode(x,'s');flag=true;}

            if(dir.returnNode(x)->next!=NULL){node0=dir.returnNode(x+1);}else{break;}
            if(dir.returnNode(x+1)->next!=NULL){node1=dir.returnNode(x+2);}else{break;}
            if(dir.returnNode(x+2)->next!=NULL){node2=dir.returnNode(x+3);}else{break;}
            x++;
        }

        cout<<"\n";
        if(flag==false){break;}
    }
    dir.PrintList();
}*/
