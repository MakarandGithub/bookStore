/* database of books
assignment 3

module 1: details of books: entry, search, retrival,delete
*/


#include<stdlib.h>
#include<stdio.h>

#include<iostream>
#include<string.h>
#include "splay1.cpp"
using namespace std;

class book
{
     string author;//author of the book
     string title;//title of the book
     int price; //price of the book
     string publisher;//publisher of the book
     int stock; // stock/number of the books in store


int success; //successful transactions
int unsuccess; //unsuccessful transactions

     void price1(int p); //updates price of the book to Rs.p

   public:
     void updateStock(int s); //updates stock to s copies
     void updatePrice(int p); //calls private price function of the book to update price to Rs.p
     void setDetails(string au,string ti,int p,string pub,int s);//setter of the object
     void showDetails();
     void transact(int num);
     int check(string au,string ti);
     void addBook(int k);
     void copybook(book *b1);
};


int count=0;

void book::transact(int num)
{
    if(this->stock>=num)
    {
        int pri=this->price*num;//price of the transaction
        int confirm=5; //confirmation checker
        while(confirm!=1 || confirm!=0)
        {
        cout<<"Total Price of "<<num<<" books is : Rs."<<pri<<endl<<"press 1 to confirm and 0 to revert : ";
        cin>>confirm;
        switch(confirm)
        {
           case 1 : this->stock-=num;
                    this->success++;
                    cout<<endl<<"Congratulations! transaction successful! Pay Rs."<<pri<<endl;
                    return;
           case 0 : cout<<"Transaction Reverted!"<<endl;
                    return;
           default: cout<<"incorrect input! re-enter!"<<endl;
        }
        }
    }
    else
    {
        cout<<"Transaction unsuccessful! Not sufficient copies!"<<endl;
        this->unsuccess++;
        return;
    }

}

int book::check(string name,string namea)
{
    //string a1,a2;
    //strcpy(a1,name);
    //strcpy(a2,namea);
    //if(strcmp(a1,this->title)==0)
     if(name==this->title)
     {
           //if(strcmp(a2,this->author)==0)
           if(namea==this->author)
           {
              return 1;
           }
           else
           {
               return 0;
           }
     }
    else
     {
       return 0;
     }

}
void book::showDetails()
{
    cout<<"----------------------------------"<<endl
        <<"The Book has following details : "<<endl<<endl
        <<"Author : "<<this->author<<endl
        <<"Title : "<<this->title<<endl
        <<"Price : "<<this->price<<endl
        <<"Publisher : "<<this->publisher<<endl
        <<"stock available : "<<this->stock<<endl
        <<"Unsuccessful transaction : "<<this->unsuccess<<endl
        <<"Successful transaction : "<<this->success<<endl
        <<"---------------------------------"<<endl<<endl;


}

void book::setDetails(string au,string ti,int p,string pub,int s)//setter of the object
{
    this->author=au;
    this->title=ti;
    this->price=p;
    this->publisher=pub;
    this->stock=s;
}


void book::updateStock(int s)
{
     this->stock+=s;
}

void book::price1(int p)
{
     this->price=p;
}

void book::updatePrice(int p)
{
     this->price1(p);
}



void book::addBook(int k)
{
     string name,namea,pub;//temp title and author and publisher of the book
     int p,s;//temp price and stock of the book



        cout<<endl<<"Enter the title of the book "<<k+1<<" : ";
        cin>>name;
        cout<<"Enter the author of the book "<<k+1<<" : ";
        cin>>namea;
        cout<<"Enter the price of the book "<<name<<" : ";
        cin>>p;
        cout<<"Enter the publisher of the book "<<k+1<<" : ";
        cin>>pub;
        cout<<"Enter the stock of the book "<<k+1<<" : ";
        cin>>s;
        cout<<"------------------------------------------"<<endl;
        this->setDetails(namea,name,p,pub,s);
        this->unsuccess=0;
        this->success=0;
        count++;

}

void book::copybook(book *b1)
{
    this->author=b1->author;
    this->title=b1->title;
    this->price=b1->price;
    this->publisher=b1->publisher;
    this->stock=b1->stock;

}


int main()
{
     string name,namea;//temp title and author of the book
     int esc=0;//to exit the program (Checker)
     int option;//chooser
     int n,pri;
     int first=0;
     book *inventory,*temp;
     SplayTree st;
     //int vector[10] = {9,8,7,6,5,4,3,2,1,0};
     splay *root;
     root = NULL;
     //cout<<"\nInOrder: \n";
    // st.InOrder(root);
     while(esc==0)
     {

          cout<<endl<<"*********Welcome to Book Inventory Manager*******"<<endl<<endl;

          cout<<"What do you want to do? "<<endl;
          cout<<"1. Add books"<<endl;
          cout<<"2. Search for the book. "<<endl;
          cout<<"3. See the Splay tree for books"<<endl;
          cout<<"4. Exit"<<endl;
          cin>>option;
          switch(option)
          {
               case 1 : //cout<<"No books in the inventory yet! Please add them first"<<endl;
                        cout<<"Enter the number of books to be added : ";
                        cin>>n;
                        if(count==0)
                        {
                        temp=new book[n];
                        }
                        else
                        {temp=new book[n+count];}
                        for(int i=0;i<n;i++)
                           {
                              temp[i].addBook(i);
                              //root = st.Insert(i+1, root);

                           }
                        cout<<"----------------------------------"
                            <<endl<<"successfully added "<<n<<" books."<<endl
                            <<"----------------------------------"<<endl;

                        if(first==0)
                        {
                           inventory=new book[n];

                           for(int i=0;i<n;i++)
                           {
                              inventory[i].copybook(&temp[i]);
                               root = st.Insert(i+1, root);

                           }
                           first=1;
                        }
                        else
                        {
                            for(int i=n;i<count;i++)
                            {
                               temp[i].copybook(&inventory[i-n]);
                            }
                           // delete inventory;
                            inventory= new book[count];
                            for(int i=0;i<count;i++)
                            {
                               inventory[i].copybook(&temp[i]);
                                root = st.Insert(i+1, root);

                            }
                            //delete temp;
                        }
                        break;

               case 2 : if(count==0)
                        {
                           cout<<"No books in the inventory yet! Please add them first"<<endl;
                           cout<<"Enter the number of books to be added : ";
                           cin>>n;
                           inventory=new book[n];

                           for(int i=0;i<n;i++)
                           {
                              inventory[i].addBook(i);
                           }
                           cout<<"----------------------------------"
                               <<endl<<"successfully added "<<n<<" books."<<endl
                               <<"----------------------------------"<<endl;

                        }
                        else{
                        cout<<"Enter title of the book : "<<endl;
                       // getchar();
                        //getline(cin,name);
                        cin>>name;
                        cout<<"Enter author of the book : "<<endl;
                        //getchar();
                        //getline(cin,namea);
                        cin>>namea;
                        int b,c;
                        for(int i=0;i<n;i++)
                        {
                            b=inventory[i].check(name,namea);
                            if(b==1){c=i;break;}
                        }
                        if(b!=0)
                           {inventory[c].showDetails();
                            root = st.Search(c+1, root);
                            int cho,out=0;
                         while(out==0)
                          {
                            cout<<"What do you want to do? "<<endl;
                            cout<<"1. Buy this book "<<endl;
                            cout<<"2. Update price "<<endl;
                            cout<<"3. Update stock "<<endl;
                            cout<<"4. Show details"<<endl;
                            cout<<"5. Back to main Menu"<<endl;
                            cin>>cho;

                            switch(cho)
                            {
                                case 1:   cout<<"Enter Number of copies required : ";
                                          int num;//number of copies required
                                          cin>>num;
                                          inventory[c].transact(num);
                                          break;
                                case 2:   cout<<endl<<"Enter the new price : ";
                                          cin>>pri;
                                          inventory[c].updatePrice(pri);
                                          break;
                                case 3:   cout<<endl<<"Enter the new stock amount : ";
                                          cin>>pri;
                                          inventory[c].updateStock(pri);
                                          break;
                                case 4:   inventory[c].showDetails();
                                          break;
                                case 5:   out=1;break;
                                default:  cout<<"Incorect input! Re-enter"<<endl;
                            }

                           }
                           }
                          else
                           {cout<<"book not found!"<<endl;}
                        }
                        break;

               case 3 : //const int length = 10;
                        //int i;
                        st.InOrder(root);
                        break;
               case 4 : esc=1;
                        cout<<"---------------------------------"<<endl
                            <<"Thank you"<<endl<<"Software by OOAD Lab3 Pvt Ltd"<<endl
                            <<"---------------------------------"<<endl;
                        break;
               default: cout<<"Incorrect input, choose again!"<<endl;
          }

     }
     return 0;
}
