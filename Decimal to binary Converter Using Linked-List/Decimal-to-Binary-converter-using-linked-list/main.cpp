#include <iostream>
#include <cmath>
using namespace std;

void binary_num (int num);
struct node
{
    int value;
    node *next;
};
node *head = NULL;

int main()
{
    int x=0,y=0,z=0;

    cout<<"Please enter a Decimal (Number_1)\n";
    cin>>x;
    cout<<"Decimal Number Which you entered is "<<endl<<x<<endl;
    cout<<"And the ''Binary Code of it'' is "<<endl;
    binary_num(x);

    cout<<"\n\nPlease enter a number (Number_2) Whaich you want to add to (number_1)\n";
    cin>>y;
    cout<<"Decimal Number Which you entered is "<<endl<<y<<endl;
    cout<<"And the ''Binary Code of it'' is "<<endl;
    binary_num(y);

    z=x+y;
    cout<<"\n\nThe Sum of (Number_1 + Number_2) in Binary Code : \n";
    binary_num(z);
    cout<<"\n\n";

    return 0;
}



void binary_num (int num)
{
    int k=0,n=0,i=0,p=0,a=0;

    if(num==0)
        cout<<"0000\n\n";
    else
    {

        //count number of nodes
        for(i=0;k<num;i++)
        {
            k+=pow(2,i);
            if(k<num)
            {
                n++;  //n:number of nodes
            }
        }
        //cout<<"K="<<k<<endl;
        k=0;
        n++;
        //cout<<"n="<<n<<endl;
        k=n%4;
        n+=((4-k)%4);
        k=0;
       // cout<<"n="<<n<<endl;


        //inserting (n) nodes
        for(i=1;i<=n;i++)
        {
            node *temp = new node;
            if(head==NULL)
            {
                head=temp;
                temp->value=0;
                head->next=NULL;
                temp=NULL;
                delete temp;
            }
            else
            {
                temp->next=head;
                temp->value=0;
                head=temp;
                temp=NULL;
                delete temp;
            }
        }
        
        //put number at binary
        for(i=0;num>0;i++)
        {
            k+=pow(2,i);
            p++; //p:aim_position
            if(k>=num)
            {
                node *current;
                current=head;
                for(a=1;a<p;a++)
                {
                    current=current->next;
                }
                current->value=1;
                current=NULL;
                delete current;
                num-=pow(2,i);
                k=0;
                i=-1;
                p=0;
            }
        }


        ////display
        node *current;
        while(n!=0)
        {
            current=head;
            for(a=1;a<n;a++)
            {
                current=current->next;
            }
            cout<<current->value;
            n--;
            delete current;
        }

    }
}
