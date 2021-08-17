#include "linkedlist.hpp"
#include <iostream>

using namespace std;
//note that ll is slow to insert because you have to traverse entire linked list each time, and slow to search because it's entirely unsorted to you have to traverse entire ll until correct node is found 

//Inserting one node at a time because I'm assuming the post office may need to insert any amount of mail at any time, not necessarily groups of 100

//should I keep track of last node inserted, or should I traverse linked list each time?
//wouldn't this affect time a lot? bc if I was inserting 100 items at a time I could just do one after another which would speed it up a bunch? 
//insert at end of ll
void MailTrackLL::insertMail(int key)
{
//create new node to insert
Mail* newMail= new Mail;
newMail->key = key;
newMail->next = NULL;

//if no nodes exist in ll insert at head
if(head==NULL)
{
    head = newMail;
    //cout to indicate node was added
    //cout << "adding: " << key << " (HEAD)" << endl;
}

else
{
//get last node 
Mail* curr = head;
while(curr->next!=NULL) 
{
    curr = curr->next;
}
    curr->next = newMail;
    //cout to indicate node was added
    //cout << "adding: " << key << " (prev: " << curr->key << ")" << endl;
    


//}
}
}
//should return mail node? 
Mail* MailTrackLL::searchMail(int key)
{
   //cout << "searching for " << key << endl;
    //create pointer to traverse ll 
    Mail* search = head;

    //traverse ll to search 
    while(search!=NULL && search->key != key)
    {
        search = search->next;
    }

    //either returns node of mail or NULL if mail is not found
  //  cout << "found " << search->key << endl;
    return search;
}


//does it matter how I print it out? (format)
void MailTrackLL::printTracking()
{
    //temporary node to traverse 
    Mail* print = head;

    cout << "== CURRENT PATH ==" << endl;
    
    //if no nodes in linked list
    if (head == NULL) 
    {
        cout << "nothing in path" << endl;
    } 

    //if there are nodes in linked list 
    else 
    {
        //traverse
         while(print->next != NULL)
         {
            //print out current node
            cout<< print->key <<" -> ";
            print = print->next;
         }
    //print last node and NULL at end of list 
    cout <<print->key<<" -> "<<"NULL"<< endl;
    }

   cout << "===" << endl;
}

