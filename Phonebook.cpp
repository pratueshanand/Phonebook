// PRATUESH ANAND(2k20/MC/102)

#include <iostream>
#include <string>
#include <fstream>

using namespace std;


//  phone book is saved in a file called "phone_book.txt". 
const char* phonebook_filename = "phone_book.txt";


//  Contact Group (one of: Family, Friends, Colleagues, VIP and Others). 
enum groups {Family, Friends, Colleagues, VIP, Others};


//  an entry in the phonebook has following information: 
//  a. Phone number. 
//  b. Contact name (CAPITAL letters).
//  c. Contact Group 
struct contact_info
{
	// string is preferred for phone numbers to allow +, - signs
	string phone_number;
	string contact_name;
	groups contact_group;
	contact_info* next_element=NULL;
};



contact_info* phonebook=NULL;


//  variable which shows number of entries in the phonebook called N_entries. 
unsigned int N_entries = 0;


contact_info* look_up[26] = {NULL};

void upcase (string&);			// This is the function prototype which would convert an string to uppercase
contact_info* create_entry();		// This is the function prototype which gets the input from user and stores in into a new contact object.
void contact_insert(contact_info*);	// This is the function prototype which inserts the new contact object into the phonebook
contact_info* contact_find(string);	// This is the function prototype to search and find a contact object based on Name
void contact_show(contact_info);	// This is the function prototype to show the information of a contact object
void contact_find_show_delete();	// This is the function prototype to find and delete contacts 
void contact_find_show();		// This is the function prototype to find and show a Name in phonebook 
void phonebook_save();			// This is the function prototype to store data into file 

int main()
{
	
	
	//  program menu: 
	char userchoice;
	do
	{
		cout << endl;
		cout << "a. Create a new entry." << endl;
		cout << "b. Delete an entry." << endl;
		cout << "c. Find an entry and show its information. " << endl;
		cout << "d. Save the whole phonebook in a file. " << endl;
		cout << "e. Exit. " << endl;
		cout << endl << "Please enter your choice: ";
		cin >> userchoice;
		switch (userchoice)
		{
	
	
		case 'a': case 'A':
			contact_insert(create_entry());
			break;
	
		//  If the user chooses (b), he must be asked for the name of the person whose entry is to be deleted
		// This is implemented in 3 functions (find, show & delete)
		case 'b': case 'B':
			contact_find_show_delete();
			break;
		
		//  If the user chooses (c), he must be asked for the name of the person.
		// This is implemented in 2 functions
		case 'c': case 'C':
			contact_find_show();
			break;
		
		//  the whole phone book must be saved   the phone book must be stored 
		case 'd': case 'D': case 'e': case 'E':
			phonebook_save();
			break;
		// Otherwise we have an invalid choice and should show an error message
		default:
			cout << endl << "!!! Invalid choice !!!" << endl;
		}

	//  If the user chooses (e), ... the program must be terminated 
	} while ((userchoice != 'e') && (userchoice != 'E'));
	cout << "Exiting program..." << endl;
	return 0;
}


//  Everything, even if entered in small letters, must be stored in CAPITAL letters.
void upcase(string &str)
{
	for (int i=0; i<str.length(); i++) str[i]=toupper(str[i]);
}


//  If the user chooses (a), he must be asked to enter the related information 
//  (phone number, contact name and group). 
contact_info* create_entry()
{
	// Creating a new blank contact
	contact_info* new_entry = new contact_info;
	cout << "Please enter name: ";
	cin.ignore();	// We are clearing input buffer to use getline function
	getline (cin,new_entry->contact_name);
	upcase(new_entry->contact_name);
	cout << "Please enter phone number: ";
	getline (cin,new_entry->phone_number);
	upcase(new_entry->phone_number);
	cout << "Please enter group" << endl;
	cout << "1) f for = Family" << endl;
	cout << "2) r for R = Friends" << endl;
	cout << "3) c or C = Colleagues" << endl;
	cout << "4) v or V = VIP" << endl;
	cout << "or enter any other character for (Others) group" << endl;
	cout << "Your choice: ";
	char groupchoice;
	cin >> groupchoice;
	switch (groupchoice)
	{
	case '1': case 'f': case 'F':
		new_entry->contact_group=Family;
		break;
	case '2': case 'r': case 'R':
		new_entry->contact_group=Friends;
		break;
	case '3': case 'c': case 'C':
		new_entry->contact_group=Colleagues;
		break;
	case '4': case 'v': case 'V':
		new_entry->contact_group=VIP;
		break;
	default:
		new_entry->contact_group=Others;
	}
	new_entry->next_element=NULL;
	cout << "New contact successfully created." << endl;
	return new_entry;
}


//function to insert a new contact in the linked list
void contact_insert(contact_info* newcontact)
{
	// If the new item is the 1st item, we have special case
	if (N_entries==0 || phonebook->contact_name.compare(newcontact->contact_name)>0)
	{
		newcontact->next_element=phonebook;
		phonebook=newcontact;
	}
	else
	{
		contact_info* previous=phonebook;
		contact_info* next=phonebook->next_element;
		while(next!=NULL)
		{
			if (newcontact->contact_name.compare(next->contact_name)<0) break;
			previous=next;
			next=next->next_element;
		}
		previous->next_element=newcontact;
		newcontact->next_element=next;		
	}	
	N_entries++;
}


// It searchs & returns the pointer to contact based on contact name (or NULL if not found).
contact_info* contact_find(string Name)
{
	contact_info* contact = phonebook;
	while (contact != NULL)
	{
		if (Name.compare(contact->contact_name)==0)
			return contact;
		else
			contact=contact->next_element;
	}
	return NULL;
}


// This function prints a contact information.
void contact_show(contact_info* contact)
{
	cout << "Contact Name: " << contact->contact_name << endl;
	cout << "Contact Number: " << contact->phone_number << endl;
	cout << "Contact Group: ";
	switch (contact->contact_group)
	{
		case Family: cout << "FAMILY" << endl; break;
		case Friends: cout << "FRIENDS" << endl; break;
		case Colleagues: cout << "COLLEAGUES" << endl; break;
		case VIP: cout << "VIP" << endl; break;
		default: cout << "OTHERS" << endl;
	}
}

//  This function is for finding, Showing, confirming and deleting a contact
void contact_find_show_delete()
{
	cout << "Please enter contact name to be deleted: ";
	string Name;
	cin.ignore();
	getline (cin,Name);
	upcase(Name);
	cout << endl;
	contact_info* contact = contact_find(Name);
	if(contact != NULL)
	{
		cout << "We are going to delete following contact:" << endl;
		contact_show(contact);
		cout << "Enter Y/y to confirm delete:";
		char confirm;
		cin >> confirm;
		if (confirm == 'Y' || confirm == 'y')
		{
			// If the 1st Item is to be deleted, we have special case
			if (contact==phonebook)
			{
				phonebook=phonebook->next_element;
			}
			// Else, we should find previous contact for linking
			else
			{
				contact_info* previous=phonebook;
				while(previous->next_element != contact) previous=previous->next_element;
				previous->next_element=contact->next_element;				
			}
			// Free memory for deleted contact
			delete contact;
			N_entries--;
			cout << "Contact successfully deleted" << endl;
		}
		else cout << "Did not delete contact." << endl;
	}
	else cout << "Did not found " << Name << " in phonebook!!!" << endl;
}


void contact_find_show()
{
	cout << "Please enter contact name to be searched for: ";
	string Name;
	cin.ignore();
	getline (cin,Name);
	cout << endl;
	upcase(Name);
	contact_info* contact = contact_find(Name);
	if(contact != NULL)
		contact_show(contact);
	else
		cout << "Did not found " << Name << " in phonebook!!!" << endl;
}


//  whole phone book must be saved in a file
void phonebook_save()
{
	ofstream phonebook_file;
	//  called "phone_book.txt".
	phonebook_file.open(phonebook_filename);
	cout << "Writing " << N_entries << " records to " << phonebook_filename << " ..." << endl;
	//  On the first line the number of entries must be saved
	phonebook_file << N_entries << endl;
	contact_info* current_item=phonebook;
	while (current_item != NULL)
	{
		
		phonebook_file << "********************" << endl;
		//   For each entry, the name must be stored on the first line
		phonebook_file << current_item->contact_name << endl;
		phonebook_file << current_item->phone_number << endl;
		switch (current_item->contact_group)
		{
			case Family: phonebook_file << "FAMILY" << endl; break;
			case Friends: phonebook_file << "FRIENDS" << endl; break;
			case Colleagues: phonebook_file << "COLLEAGUES" << endl; break;
			case VIP: phonebook_file << "VIP" << endl; break;
			default: phonebook_file << "OTHERS" << endl;
		}
		current_item = current_item->next_element;
	}
	phonebook_file.close();
}