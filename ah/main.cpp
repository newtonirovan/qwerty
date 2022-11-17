
//=================================================================================
// Name         : DS Assignment#2 
// Author       : 
// Version      : 1.0
// Date Created : 07-11-2022
// Date Modified: 
// Description  : Starter Code for Contact Management System using BST Tree in C++
//=================================================================================
#include<iostream>
#include<cstdlib>
#include<sstream>
#include "myvector.h"
#include "contact.h"
#include "contactbst.h"

//==========================================================
void listCommands()
{
	cout<<"----------------------------------"<<endl;
	cout<<"import <path>      :Import contacts from a CSV file"<<endl
		<<"export <path>      :Export contacts to a CSV file"<<endl
		<<"add                :Add a new contact"<<endl
		<<"edit <key>         :Update a contact's details"<<endl
		<<"remove <key>       :Delete a contact"<<endl
		<<"searchFor <key>    :Search for a contact"<<endl
		<<"markFav <key>      :Mark as favourite"<<endl
		<<"unmarkFav <key>    :Unmark as favourite"<<endl
		<<"printASC           :Print contacts in ascending order"<<endl
		<<"printDES           :Print contacts in descending order"<<endl
		<<"printFav           :Print all favourite contacts"<<endl
		<<"help               :Display the available commands"<<endl
		<<"exit               :Exit the program"<<endl;
}
//==========================================================

// to be completed with ALL the necessary method definitions

//==========================================================
int main(void)
{
    ContactBST MyContactBST;

    while(true)
    {
        Node* root = MyContactBST.getRoot();
        string command_input = "";
        string operation = "";
        string key = "";
        int i = 0;
        cout<<endl;
        listCommands();
        cout<<"> ";
        getline(cin, command_input);
        while(command_input[i] != ' ' && command_input[i])
        {
        	operation[i] += command_input[i];
        	i++;
        }
        while (command_input[i])
        {
        	key[i] = command_input[i];
        	i++;
        }

        if (operation == "import")
        {
            cout<<MyContactBST.importCSV(key);
        }
        else if (operation == "export")
        {
            cout<<MyContactBST.exportCSV(key);
        }
        else if(operation == "add")
        {
            int i = 0;
            string data_parameter[] = {"First Name", "Last Name", "Email", "Phone#", "City", "Country", "Do you want to add the contact in your favourite (y/n)"};
            string data_contact[7];
            while(i < 7)
            {
                string data_input = "";
                cout<<data_parameter[i]<<": ";
                getline(cin, data_input);
                if (data_input.length() == 0) {
                    cout<<"Invalid " + data_parameter[i]<<endl;
                    break;
                }
                if (i == 3)
                {
                    for (int a = 0; a < data_input.length(); ++a)
                    {
                        if(!isdigit(data_input[a]))
                        {
                            if (a != 0 && data_input[a] != '+')
                            {
                                cout<<"Invalid " + data_parameter[i]<<endl;
                                break;
                            }
                        }
                    }
                }
                // else if (i == 2)
                // {
                //     bool dot = false;
                //     bool ad = false;
                //     bool letter = false;
                //     for (int a = 0; a < ; ++a)
                //     {
                //         if (data_input[a] == ".")
                //         {
                //             dot = true;
                //         }
                //         else if (data_input[a] == "@")
                //         {
                //             ad = true;
                //         }
                //         else if ((data_input[a] >= 65 && data_input[a] <= 90) || (data_input[a] >= 97 && data_input[a] <= 122))
                //         {
                //             letter = true;
                //         }
                //     }
                // }
                else if (i == 6)
                {
                    if (data_input.length() != 1)
                    {
                        cout<<"Invalid favourite mark (y/n)!"<<endl;
                        break;
                    }
                    else if (data_input[0] != 'y' || data_input[0] != 'n')
                    {
                        cout<<"Invalid favourite mark (y/n)!"<<endl;
                        break;
                    }
                }
                data_contact[i] = data_input;
                i++;
            }
            bool isFav = false;
            if(data_contact[6][0] == 'y')
            {
                isFav = true;
            }
            Contact* data = new Contact(data_contact[0],data_contact[1],data_contact[2],data_contact[3],data_contact[4],data_contact[6],isFav);
            string key = data_contact[0] + " " + data_contact[1];
            MyContactBST.add(root, key, data);
        }
        else if(operation == "edit")
        {
            MyContactBST.update(root, key);
        }
        else if (operation == "remove")
        {
            ///asljcdhasiuchasu
            //MyContactBST.remove_helper(key);
        }
        else if(operation == "searchFor")
        {
            MyContactBST.searchFor(root, key);
        }
        else if(operation == "markFav")
        {
            MyContactBST.markFav(key);
        }
        else if(operation == "unmarkFav")
        {
            MyContactBST.unmarkFav(key);
        }
        else if(operation == "printASC")
        {
            MyContactBST.printASC(root);
        }
        else if (operation == "printDES")
        {
            MyContactBST.printDES(root);
        }
        else if(operation == "printFav")
        {
            MyContactBST.printFav(root);
        }
        else if(operation == "help")
        {
            listCommands();
        }
        else if(operation == "exit")
        {
            return (0);
        }
        else
        {
            cout<<"Invalid command"<<endl;
        }
    }

    return 0;
}