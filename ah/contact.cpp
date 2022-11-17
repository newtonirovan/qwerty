#include <iostream>
#include "contact.h"
using namespace std;

Contact::Contact(string fname_, string lname_, string email_, string primaryPhone_, string city_, string country_, bool isFav_)
{
    fname = fname_;
    lname = lname_;
    email = email_;
    primaryPhone = primaryPhone_;
    city = city_;
    country = country_;
    isFav = isFav_;
}

