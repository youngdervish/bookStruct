#include <iostream>
#include <limits>
using namespace std;

struct Book {
	char* title;
	char* author;
	int page;
	int bookID;
	float price;
};

void PrintMenu() {
	cout << "\n1. Show All Books"
		<< "\n2. Add a Book"
		<< "\n3. Search a Book"
		<< "\n4. Update a Book"
		<< "\n5. Delete a Book"
		<< "\n6. Exit\n";
}

void ShowLibrary(Book**& books, int& quantity) {
	for (int i = 0; i < quantity; i++)
	{
		cout << "\nThe title: " << books[i]->title
			<< "\nThe author: " << books[i]->author
			<< "\nPage count: " << books[i]->page
			<< "\nPrice: " << books[i]->price
			<< "\nBook ID: " << books[i]->bookID
			<< "\n---------------------------------------------\n";	
	}
}

void ShowBook(Book**& books, int& quantity, int& bookID) {
	bool found = false;
	for (int i = 0; i < quantity; i++)
	{
		if (books[i]->bookID == bookID) {
			cout << "\nThe title: " << books[i]->title
				<< "\nThe author: " << books[i]->author
				<< "\nPage count: " << books[i]->page
				<< "\nPrice: " << books[i]->price
				<< "\nBook ID: " << books[i]->bookID
				<< "\n---------------------------------------------\n";
			found = true;
		}
	}
	if (!found) { cout << "\nOur records do not have the book with that ID...\n"; }
}

bool FindBook(Book**& books, int& quantity, int& bookID) {
	for (int i = 0; i < quantity; i++)
	{
		if (bookID == books[i]->bookID) {
			cout << "\nA book of the same ID already exists\n";
			return false;
		}
	}
	return true;
}

void AddBook(Book**& books, int& quantity, char* title, char* author, int& pageCount, int& bookID, float& price) {
	cout << title << endl;
	Book* newBook = new Book{ title, author, pageCount, bookID, price };
	books[quantity] = newBook;
	quantity++;
	cout << "\nThe new entry was successfully added\n";
}

int SearchBook(Book**& books, int& quantity, int& bookID) {
	for (int i = 0; i < quantity; i++)
	{
		if (books[i]->bookID == bookID) {
			cout << "\nThe title: " << books[i]->title
				<< "\nThe author: " << books[i]->author
				<< "\nPage count: " << books[i]->page
				<< "\nPrice: " << books[i]->price
				<< "\nBook ID: " << books[i]->bookID
				<< "\n---------------------------------------------\n";
			return bookID;
		}
	}
	return -1;
}

void UpdateMenu() {
	cout << "\n1. Update Title: "
		<< "\n2. Update Author: "
		<< "\n3. Update Page Number: "
		<< "\n4. Update Book ID: "
		<< "\n5. Update Price: "
		<< "\n6. Exit\n";
}

void UpdateBookTitle(Book**& books, int& quantity, int& bookID, char*& title) {
	//strcpy_s(books[bookID - 1]->title, strlen(books[bookID - 1]->title), title);
	books[bookID - 1]->title = title;
}
void UpdateBookAuthor(Book**& books, int& quantity, int& bookID, char*& author) {
	//strcpy_s(books[bookID - 1]->author, strlen(books[bookID - 1]->author), author);
	books[bookID - 1]->author = author;
}
void UpdateBookPage(Book**& books, int& quantity, int& bookID, int& pageCount) {
	books[bookID - 1]->page = pageCount;
}
void UpdateBookID(Book**& books, int& quantity, int& oldBookID, int& newBookID) {
	books[oldBookID - 1]->bookID = newBookID;
}
void UpdateBookPrice(Book**& books, int& quantity, int& bookID, float& price) {
	books[bookID]->price = price;
}

void DeleteBook(Book** books, int& quantity, int& bookID) {
	for (int i = 0; i < quantity; i++)
	{
		if (books[i]->bookID == bookID) {
			delete[] books[i];
			quantity--;
		}
	}
}

void DeleteEverything(Book**& books, int& quantity) {
	for (int i = 0; i < quantity; i++)
	{
		delete[] books[i];
	}
	delete[] books;
	quantity = 0;
}

void main() {
	int quantity = 0;

	cout << "Welcome to our humble library.\nWe do not have many books, but the ones we got are of highest interest to readers all over the world.\nPlease make your choice below:\n";
	Book* book1 = new Book{ new char[30] {"Satanic Verses"}, new char[30] {"Salman Rushdie"}, 561, 001, 14.47 };
	quantity++;
	Book* book2 = new Book{ new char[30] {"The Name of the Rose"}, new char[30] {"Umberto Eco"}, 592, 002, 22.52 };
	quantity++;
	Book* book3 = new Book{ new char[30] {"Synchronicity"}, new char[30] {"Carl Gustav Jung"}, 160, 003, 7.99 };
	quantity++;
	
	Book** library = new Book * [quantity] {book1, book2, book3};

	char* title = new char[30] {};
	char* author = new char[30] {};
	int pages, bookID, newBookID, choice, updateChoice;
	float price;
	
	//Choices
	PrintMenu();
	while (true) {
		cin >> choice;
		switch (choice) {
		case 1:
			ShowLibrary(library, quantity);
			PrintMenu();
			break;
		case 2:
			cout << "\nPlease enter the book ID:\n";
			cin >> bookID;
			while (!FindBook(library, quantity, bookID)) {
				cin >> bookID;
			}

			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "\nPlease enter the book title:\n";
			cin.getline(title, 30);

			cout << "\nPlease enter the author:\n";
			cin.getline(author, 30);

			cout << "\nPlease enter the number of pages:\n";
			cin >> pages;

			cout << "\nPlease enter the price:\n";
			cin >> price;

			AddBook(library, quantity, title, author, pages, bookID, price);
			ShowLibrary(library, quantity);
			PrintMenu();
			break;
		case 3:
			cout << "\nPlease enter the ID of the book you'd like to find:\n";
			cin >> bookID;
			cout << SearchBook(library, quantity, bookID);
			PrintMenu();
			break;
		case 4:
			cout << "\nPlease enter the ID of the book you'd like to modify:\n";
			cin >> bookID;
			UpdateMenu();
			cin >> updateChoice;
			
			switch (updateChoice) {
			case 1:
				cout << "\nPlease enter the new title: \n";
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cin.getline(title, 30);
				UpdateBookTitle(library, quantity, bookID, title);
				ShowBook(library, quantity, bookID);
				break;
			case 2:
				cout << "\nPlease enter the new author: \n";
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cin.getline(author, 30);
				UpdateBookAuthor(library, quantity, bookID, author);
				ShowBook(library, quantity, bookID);
				break;
			case 3:
				cout << "\nPlease enter the new page number: \n";
				cin >> pages;
				UpdateBookPage(library, quantity, bookID, pages);
				ShowBook(library, quantity, bookID);
				break;
			case 4:
				cout << "\nPlease enter the new bookID:\n";
				cin >> newBookID;
				UpdateBookID(library, quantity, bookID, newBookID);
				ShowBook(library, quantity, newBookID);
				break;
			case 5:
				cout << "\nPlease enter the new price:\n";
				cin >> price;
				UpdateBookPrice(library, quantity, bookID, price);
				ShowBook(library, quantity, bookID);
				break;
			case 6:
				cout << "\nWrong selection. Going back to menu.\n";
				break;
			}
			PrintMenu();
			break;
		case 5:
			cout << "\nPlease enter the book Id to delete:\n";
			cin >> bookID;
			ShowBook(library, quantity, bookID);
			DeleteBook(library, quantity, bookID);
			ShowBook(library, quantity, bookID);
			PrintMenu();
			break;
		case 6:
			DeleteEverything(library, quantity);
			return;
		default:
			break;
		}
	}
}
