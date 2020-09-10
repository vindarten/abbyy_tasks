#include<iostream>
#include<fstream>

using namespace std;

struct ListItem
{
	int value;
	ListItem *next;
};

ListItem *ReadList(char *filename)
{
	ifstream data_file(filename, ios_base::in);
	int value;
	ListItem *list = NULL, *new_item = NULL;
	while (data_file >> value)
	{
		new_item = new ListItem();
		new_item->value = value;
		new_item->next = list;
		list = new_item;
	}
	return list;
}

void PrintList(ListItem *list)
{
	while(list != NULL)
	{
		cout << list->value << " ";
		list = list->next;
	}
	cout << endl;
}

void DeleteList(ListItem *list)
{
	ListItem *temp = NULL;
	while(list != NULL)
	{
		temp = list;
		list = list->next;
		delete temp;
	}
}

ListItem *ReverseList(ListItem *list)
{
	ListItem *new_list = NULL, *temp = NULL;
	while(list != NULL)
	{
		temp = list;
		list = list->next;
		temp->next = new_list;
		new_list = temp;
	}
	return new_list;
}

int main(int argc, char **argv)
{
	if(argc < 2)
	{
		cout << "Usage: " << argv[0] << " <data_file>" << endl;
		return 0;
	}

	ListItem *list = ReadList(argv[1]);

	cout << "Input data:" << endl;
	PrintList(list);
	list = ReverseList(list);
	cout << "Output data:" << endl;
	PrintList(list);

	DeleteList(list);

	return 0;
}
