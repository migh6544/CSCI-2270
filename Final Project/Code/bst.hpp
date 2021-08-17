#include <iostream>

using namespace std;

struct Mail
{
    int key;
    Mail* left;
    Mail* right;

};

class MailTrackBST
{
private:
Mail* root;

public:

//what should my insert function do? insert a new piece of mail somewhere into the data structure? 
void insertMail(int key);

//search for a piece of mail based on its "tracking ID"?
Mail* searchMail(int key);

//print out every node in ll? (the entire thing)?
void printTracking();

};