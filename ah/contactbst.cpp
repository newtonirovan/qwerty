 #include<iostream>
#include<sstream>
#include<fstream>
#include "contact.h"
#include "contactbst.h"
#include "myvector.h"
#include <string>
#include<algorithm>
using namespace std;


//----------------------------------------------------------------------------------
//constructor
ContactBST::ContactBST(){
    this->root = NULL;
}

//----------------------------------------------------------------------------------
//destructor
ContactBST::~ContactBST(){
    while(root){
        this->remove(root, root->key);
    }
}

//----------------------------------------------------------------------------------
//returns the root of the Tree
Node* ContactBST::getRoot(){
    return this->root;
}

//----------------------------------------------------------------------------------
//add key into tree/subtree with root ptr
//the key is of string data type and essentially is firstName + ‘ ‘ + lastName
void ContactBST::add(Node* ptr,string key, Contact *data){
    //if tree is empty
    if(ptr == NULL){
        root = new Node(key, data);
        cout<<"Contact "<<key<<" has successfully been added!"<<endl;
    }
    else{
        //compare strings/keys (ASCII)
        bool equal = false;
        bool key_left = false;
        if(key.size() == ptr->key.size()){
            key_left = false;
            equal = false;
            for(int i = 0; i < key.size(); i++){
                if(key[i] == ptr->key[i]){
                    continue;
                    equal = true;
                }
                else if(key[i] < ptr->key[i]){
                    key_left = true;
                    equal = false;
                }
                else if(key[i] > ptr->key[i]){
                    key_left = false;
                    equal = false;
                }
            }
        }
        else {
            key_left = false;
            equal = false;
            for(int i = 0; i < key.size(); i++){
                if(key[i] == ptr->key[i]){
                    continue;
                }
                else if(key[i] < ptr->key[i]){
                    key_left = true;
                }
                else if(key[i] > ptr->key[i]){
                    key_left = false;
                }
            }
        }

        //if keys are equal
        if (equal){
            ptr->contactVector.push_back(data);
            cout<<"Contact "<<ptr->key<<" has successfully been added!"<<endl;
        }
        //if the inserted key is less than key of the parent
        else if(key_left){
            if(ptr->left == NULL){
                ptr->left = new Node(key, data);
                ptr->left->parent = ptr;
                cout<<"Contact "<<ptr->left->key<<" has successfully been added!"<<endl;
            }
            else{
                add(ptr->left, key, data);
            }
        }
        //if the inserted key is more than key of the parent
        else if(!key_left && !equal){
            if(ptr->right == NULL){
                ptr->right = new Node(key, data);
                ptr->right->parent = ptr;
                cout<<"Contact "<<ptr->right->key<<" has successfully been added!"<<endl;
            }
            else{
                add(ptr->right, key, data);
            }
        }
    }
}


//----------------------------------------------------------------------------------
//edit the node with key
void ContactBST::update(Node *ptr, string key){
    if(searchFor(ptr, key) == NULL){
        cout<<"Contact is not found"<<endl;
        return;
    }
    int comparison;
    int i = 0;
    while(key[i] && key[i] == ptr->key[i])
    {
        i++;
    }
    comparison = key[i] - ptr->key[i];
    if(comparison < 0){
        ptr = ptr->left;
    } 
    else if(comparison > 0){
        ptr = ptr->right;
    }
    else if(comparison == 0){
        if(ptr->contactVector.size() == 1){
            cout<<"1 record found: "<<endl;
        }
        else if(ptr->contactVector.size() > 1){
            cout<<ptr->contactVector.size()<<" records found: "<<endl;
        }
        for (int i=0; i < ptr->contactVector.size(); i++){
            cout<<i+1<<". "<<ptr->contactVector.at(i)->fname<<",";
            cout<<ptr->contactVector.at(i)->lname<<",";
            cout<<ptr->contactVector.at(i)->email<<",";
            cout<<ptr->contactVector.at(i)->primaryPhone<<",";
            cout<<ptr->contactVector.at(i)->city<<",";
            cout<<ptr->contactVector.at(i)->country<<",";
            cout<<ptr->contactVector.at(i)->isFav<<","<<endl;;
        }
        int record_number;
        if(ptr->contactVector.size() > 1){
            cout<<"Please select the record you want to edit: ";
            cin>>record_number;
            record_number -= 1;
        }
        else if(ptr->contactVector.size() == 1){
            record_number = 0;
        }
        int user_input;
        cout<<"Which field do you want to edit? 1)First name, 2)Last name, 3)Email, 4)Phone#, 5)City, or 6)Country: ";
        cin>>user_input;
        string new_info;
        string updated_key;
        char y_n;
        if(user_input == 1){
            cout<<"Please enter the new First name: ";
            cin>>new_info;
            ptr->contactVector.at(record_number)->fname = new_info;
            updated_key = new_info + " " + ptr->contactVector.at(record_number)->lname;
            cout<<"Do you want to edit another field (y/n)?: ";
        }
        else if(user_input == 2){
            cout<<"Please enter the new Last name: ";
            cin>>new_info;
            ptr->contactVector.at(record_number)->lname = new_info;
            updated_key = ptr->contactVector.at(record_number)->fname + " " + new_info;
            cout<<"Do you want to edit another field (y/n)?: ";
        }
        else if(user_input == 3){
            cout<<"Please enter the new Email: ";
            cin>>new_info;
            ptr->contactVector.at(record_number)->email = new_info;
            cout<<"Do you want to edit another field (y/n)?: ";
        }
        else if(user_input == 4){
            cout<<"Please enter the new Phone#: ";
            cin>>new_info;
            ptr->contactVector.at(record_number)->primaryPhone = new_info;
            cout<<"Do you want to edit another field (y/n)?: ";
        }
        else if(user_input == 5){
            cout<<"Please enter the new City: ";
            cin>>new_info;
            ptr->contactVector.at(record_number)->city = new_info;
            cout<<"Do you want to edit another field (y/n)?: ";
        }
        else if(user_input == 6){
            cout<<"Please enter the new Country: ";
            cin>>new_info;
            ptr->contactVector.at(record_number)->country = new_info;
            cout<<"Do you want to edit another field (y/n)?: ";
        }
        else{
            cout<<"Invalid input"<<endl;
            return;
        }
        cin>>y_n;
        if(y_n == 'y'){
            update(root, updated_key);
            return;
        }
        else if(y_n == 'n'){
            cout<<"The contact record has successfully been updated!"<<endl;
            return;
        }
    }

}

//----------------------------------------------------------------------------------
//delete a node with key from the tree/subtree with root
void ContactBST::remove(Node* ptr,string key){
    string t;
    t = key;
    if(ptr == NULL){
        cout<<"Empty: contact is not found"<<endl;
        return;
    }
    int comparison = 0;
    int i = 0;
    while(key[i] && key[i] == ptr->key[i])
    {
        i++;
    }
    comparison = key[i] - ptr->key[i];
    if(comparison == 0){
        if(ptr->contactVector.size() == 1){
            cout<<"1 record found: "<<endl;
            cout<<"1. "<<ptr->contactVector.at(0)->fname<<",";
            cout<<ptr->contactVector.at(0)->lname<<",";
            cout<<ptr->contactVector.at(0)->email<<",";
            cout<<ptr->contactVector.at(0)->primaryPhone<<",";
            cout<<ptr->contactVector.at(0)->city<<",";
            cout<<ptr->contactVector.at(0)->country<<",";
            cout<<ptr->contactVector.at(0)->isFav<<","<<endl;

            //no children
            if(ptr->left == NULL && ptr->right == NULL){
                    if(ptr->parent == NULL){
                        root = NULL;
                        return;
                    }
                    //compare strings ptr->key and ptr->parent->key
                    int c = 0;
                    int i = 0;
                    while(ptr->key[i] && ptr->key[i] == ptr->parent->key[i])
                    {
                        i++;
                    }
                    c = ptr->key[i] - ptr->parent->key[i];
                    //if ptr->key <= ptr->parent->key
                    if(c <= 0){
                        ptr->parent->left = NULL;
                        ptr = NULL;
                        return;
                    }
                    else if(c > 0){
                        ptr->parent->right = NULL;
                        ptr = NULL;
                        return;
                    }
            }
            //one right child
            else if(ptr->left == NULL && ptr->right != NULL){
                if(ptr->parent == NULL){
                    ptr->right->parent = NULL;
                    root = ptr->right;
                    //delete ptr;
                    return;
                }
                else{
                    int c = 0;
                    int i = 0;
                    while(ptr->key[i] && ptr->key[i] == ptr->parent->key[i])
                    {
                        i++;
                    }
                    c = ptr->key[i] - ptr->parent->key[i];
                    if(c <= 0){
                        ptr->parent->left = ptr->right;
                        ptr->right->parent = ptr->parent;
                        ptr = NULL;
                        return;
                    }
                    else if(c > 0){
                        ptr->parent->right = ptr->right;
                        ptr->right->parent = ptr->parent;
                        ptr = NULL;
                        return;
                    }
                }
            }
            //one left child
            else if(ptr->left != NULL && ptr->right == NULL){
                if(ptr->parent == NULL){
                    ptr->left->parent = NULL;
                    root = ptr->left;
                    delete ptr;
                    return;
                }
                else{
                    int c = 0;
                    int i = 0;
                    while(ptr->key[i] && ptr->key[i] == ptr->parent->key[i])
                    {
                        i++;
                    }
                    c = ptr->key[i] - ptr->parent->key[i];
                    if(c <= 0){
                        ptr->parent->left = ptr->left;
                        ptr->left->parent = ptr->parent;
                        ptr = NULL;
                    }
                    else if(c > 0){
                        ptr->parent->right = ptr->left;
                        ptr->left->parent = ptr->parent;
                        ptr = NULL;
                    }
                    return;
                }
            }
            //two children
            else if(ptr->left != NULL && ptr->right != NULL){
                Node* min_right = findMin(ptr->right);
                string min_key = min_right->key;
                remove(ptr->right, min_right->key);
                ptr->key = min_key;
            }
            cout<<"The contact record "<<t<<"has successfully been deleted!"<<endl;
        }
        //if multiple contacts with the same key
        else if(ptr->contactVector.size() > 1){
            cout<<ptr->contactVector.size()<<" records found: "<<endl;
            for (int i=0; i < ptr->contactVector.size(); i++){
                cout<<i+1<<". "<<ptr->contactVector.at(i)->fname<<",";
                cout<<ptr->contactVector.at(i)->lname<<",";
                cout<<ptr->contactVector.at(i)->email<<",";
                cout<<ptr->contactVector.at(i)->primaryPhone<<",";
                cout<<ptr->contactVector.at(i)->city<<",";
                cout<<ptr->contactVector.at(i)->country<<",";
                cout<<ptr->contactVector.at(i)->isFav<<","<<endl;
            }
            int record_number;
            cout<<"Please select the record you want to delete: ";
            cin>>record_number;
            ptr->contactVector.erase(record_number-1);
            cout<<"The contact record "<<t<<"has successfully been deleted!"<<endl;
        }

    }
    else if(comparison < 0){
        remove(ptr->left, key);
        return;
    }
    else if(comparison > 0){
        remove(ptr->right, key);
        return;
    }
}

//----------------------------------------------------------------------------------
//needed for remove method
Node* ContactBST::findMin(Node* ptr){
    if(ptr->left == NULL){
        return ptr;
    }
    else if(ptr->left != NULL){
        ptr = findMin(ptr->left);
    }
    return ptr;
}

//----------------------------------------------------------------------------------
//helper function, check if key is in the tree
// bool ContactBST::findKey(Node *ptr,string key){
//     int comparison;
//     comparison = strcmp(key, ptr->key);
//     bool key_found;
//     key_found = false;
//     if(comparison == 0){
//         key_found = true;
//     }
//     else if(comparison < 0){
//         findKey(ptr->left, key);
//     }
//     else if(comparison > 0){
//         findKey(ptr->right, key);
//     }
// }

//----------------------------------------------------------------------------------
//find and returns the node with key
Node* ContactBST::searchFor(Node *ptr,string key){
    if(ptr == NULL){
        cout<<"Empty: no contacts"<<endl;
        return ptr;
    }
    int comparison = 0;
    int i = 0;
    while(key[i] && key[i] == ptr->key[i])
    {
        i++;
    }
    comparison = key[i] - ptr->key[i];
    if(comparison == 0){
        if(ptr->contactVector.size() == 1){
            cout<<"1 record found: "<<endl;
            cout<<"1. "<<ptr->contactVector.at(0)->fname<<",";
            cout<<ptr->contactVector.at(0)->lname<<",";
            cout<<ptr->contactVector.at(0)->email<<",";
            cout<<ptr->contactVector.at(0)->primaryPhone<<",";
            cout<<ptr->contactVector.at(0)->city<<",";
            cout<<ptr->contactVector.at(0)->country<<",";
            cout<<ptr->contactVector.at(0)->isFav<<","<<endl;
        }
        else if(ptr->contactVector.size() > 1){
            cout<<ptr->contactVector.size()<<" records found: "<<endl;
            for (int i=0; i < ptr->contactVector.size(); i++){
                cout<<i+1<<". "<<ptr->contactVector.at(i)->fname<<",";
                cout<<ptr->contactVector.at(i)->lname<<",";
                cout<<ptr->contactVector.at(i)->email<<",";
                cout<<ptr->contactVector.at(i)->primaryPhone<<",";
                cout<<ptr->contactVector.at(i)->city<<",";
                cout<<ptr->contactVector.at(i)->country<<",";
                cout<<ptr->contactVector.at(i)->isFav<<","<<endl;
            }
        }
    }
    else if(comparison < 0){
        ptr->left = searchFor(ptr->left, key);
    }
    else if(comparison > 0){
        ptr->right = searchFor(ptr->right, key);
    }
    return ptr;
}

//----------------------------------------------------------------------------------
//mark a contact as favorite 
bool ContactBST::markFav(string key){
    //to do
}

//----------------------------------------------------------------------------------
//unmark a contact as favorite 
bool ContactBST::unmarkFav(string key){
    //to do
}

//----------------------------------------------------------------------------------
//recursive method that prints the data at nodes in an ascending order
void ContactBST::printASC(Node *ptr){
    //to do
}

//----------------------------------------------------------------------------------
//recursive method that prints the data at nodes in a descending order
void ContactBST::printDES(Node *ptr){
    //to do
}

//----------------------------------------------------------------------------------
//print the favorite data at nodes in an ascending order
void ContactBST::printFav(Node *ptr){
    //to do
}

//----------------------------------------------------------------------------------
//load all the contacts from the CSV file to the BST
int ContactBST::importCSV(string path){
    //ifstream fin(path);
    //to do
}

//----------------------------------------------------------------------------------
//export all the contacts from the BST to a CSV file in an ascending order
int ContactBST::exportCSV(string path){
    if(root == NULL){
        cout<<"Empty: no contacts"<<endl;
        return -1;
    }
    else{
        ofstream fout(path);
        //to do
    }
}




