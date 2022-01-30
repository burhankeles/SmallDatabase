#include <iostream>
#include<map>
#include <string>
#include<fstream>
#include <exception>
using namespace std;
class Person {
private:
	string buyerName;
	int buyerID;
public:
	Person(string _buyerName = " ", int _buyerID = 0) {
		buyerName = _buyerName;
		buyerID = _buyerID;
	}
	int getBuyerID() {
		return buyerID;
	}
	string getBuyerName() {
		return buyerName;
	}



};
class Items {
private:
	int itemID;
	string itemName;

public:
	Items(int _itemID = 0, string _itemName = " ") {
		itemID = _itemID;
		itemName = _itemName;
	}
	void print() {
		cout << itemID << itemName << endl;
	}
	int getItemID() {
		return itemID;
	}
	string getItemName() {
		return itemName;
	}

};
class Basket {
private:
	int itemID;
	string itemName;
	string buyerName;
	int buyerID;
public:
	Basket(string _buyerName = " ", int _buyerID = 0, int _itemID = 0, string _itemName = " ") {
		buyerName = _buyerName;
		buyerID = _buyerID;
		itemID = _itemID;
		itemName = _itemName;
	}
	bool operator<(const Basket& b) {
		if (buyerID == b.buyerID) {
			return buyerID < b.buyerID;
		}
		else if (buyerName == b.buyerName) {
			return buyerName < b.buyerName;
		}
	}
	string returnAll() {
		string all = to_string(buyerID) + "\t" + buyerName + "\t" + to_string(itemID) + "\t" + itemName;
		return all;
	}
};
int main() {
	map<int, Person> people;
	map<int, Items> items;
	map<int, Basket> basketPerson;
	ifstream inpItems("items.txt");
	ofstream allBasket("basket.txt");
	string tempItemName, tempID, tempbuyerName;
	int itemctr = 0, control = 1, customerctr = 0, selectionMenu, tempbuyerID, selectionSubMenu, basketctr = 0;
	map<int, Person>::iterator personIterator;
	map<int, Items>::iterator itemIterator;
	map<int, Basket>::iterator basketIterator;
	//Getting all items from a file
	while (inpItems.eof() != 1) {
		getline(inpItems, tempID, ':');
		getline(inpItems, tempItemName);
		items[itemctr] = Items(atoi(tempID.c_str()), tempItemName);
		itemctr++;
	}
	do {
		cout << "Welcome to BasketManager V0.1" << endl;
		cout << "What would you like to do?" << endl << "(For adding new customer, type 1)" << endl << "(For adding a item to customers' basket, type 2)" << endl << "(For quiting, type -1)";
		cin >> selectionMenu;
		if (selectionMenu == 1) {
			cout << "Please enter the name of customer: ";
			cin >> tempbuyerName;
			tempbuyerID = customerctr;
			people[customerctr] = Person(tempbuyerName, tempbuyerID);
			customerctr++;
		}
		else if (selectionMenu == 2) {
			cout << "For which customer's basket, you would like to add something:";
			cin >> tempbuyerID;
			cout << "Which item would you like to add:";
			cin >> tempID;
			personIterator = people.find(tempbuyerID);
			itemIterator = items.find(atoi(tempID.c_str()));
			basketPerson[basketctr] = Basket(personIterator->second.getBuyerName(), personIterator->second.getBuyerID(), itemIterator->second.getItemID(), itemIterator->second.getItemName());
			basketctr++;
		}

	} while (selectionMenu != -1);
	allBasket << "BasketID" << "\t" << "CustomerName" << "\t" << "Customer ID" << "\t" << "Item ID" << "\t" << "Item Name" << endl;
	for (basketIterator = basketPerson.begin(); basketIterator != basketPerson.end(); basketIterator++) {
		allBasket << basketIterator->first << "\t" << basketIterator->second.returnAll() << endl;
	}
}
/*
	for (map<int, Items>::iterator it = items.begin(); it != items.end(); it++) {
		it->second.print();
	}
*/