// #include <iostream>
// #include <vector>
// #include <string>
// #include <algorithm> // Include this for std::find and std::find_if
// #include <limits>
// using namespace std;

// // Base class representing a generic User
// class User {
// protected:
//     int userID;
//     string name;
//     string email;
// public:
//     // Constructor to initialize user properties
//     User(int id, string n, string e) : userID(id), name(n), email(e) {}

//     // Virtual function to login the user
//     virtual void login() {
//         cout << name << " logged in." << endl;
//     }

//     // Virtual function to logout the user
//     virtual void logout() {
//         cout << name << " logged out." << endl;
//     }

//     // Virtual function to display user information
//     virtual void displayInfo() {
//         cout << "UserID: " << userID << ", Name: " << name << ", Email: " << email << endl;
//     }

//     // Getter for the user's name
//     string getName() const {
//         return name;
//     }

//     // Pure virtual function to show the menu
//     virtual void showMenu() = 0;
// };

// // Derived class representing an Admin user
// class Admin : public User {
// public:
//     // Constructor to initialize admin properties
//     Admin(int id, string n, string e) : User(id, n, e) {}

//     // Function to add a book to the library
//     void addBook(string title, string author, string genre) {
//         cout << "Book added by Admin: Title: " << title << ", Author: " << author << ", Genre: " << genre << endl;
//     }

//     // Function to remove a book from the library
//     void removeBook() {
//         cout << "Book removed by Admin." << endl;
//     }

//     // Override function to show admin-specific menu
//     void showMenu() override {
//         cout << "\nAdmin Menu:\n";
//         cout << "1. Add Book\n";
//         cout << "2. Remove Book\n";
//         cout << "3. Display All Books\n";
//         cout << "4. Display Available Books\n";
//         cout << "5. Logout\n";
//         cout << "Choose an option: ";
//     }
// };

// // Derived class representing a Member user
// class Member : public User {
// private:
//     vector<int> borrowedBooks; // List of borrowed book IDs
// public:
//     // Constructor to initialize member properties
//     Member(int id, string n, string e) : User(id, n, e) {}

//     // Function to borrow a book
//     void borrowBook(int bookID) {
//         borrowedBooks.push_back(bookID);
//         cout << "Book borrowed: " << bookID << endl;
//     }

//     // Function to return a borrowed book
//     void returnBook(int bookID) {
//         auto it = find(borrowedBooks.begin(), borrowedBooks.end(), bookID);
//         if (it != borrowedBooks.end()) {
//             borrowedBooks.erase(it);
//             cout << "Book returned: " << bookID << endl;
//         } else {
//             cout << "Book not found in borrowed list." << endl;
//         }
//     }

//     // Function to show the list of borrowed books
//     void showBorrowedBooks() {
//         cout << "Borrowed Books: ";
//         for (int id : borrowedBooks) {
//             cout << id << " ";
//         }
//         cout << endl;
//     }

//     // Override function to show member-specific menu
//     void showMenu() override {
//         cout << "\nMember Menu:\n";
//         cout << "1. Borrow Book\n";
//         cout << "2. Return Book\n";
//         cout << "3. Display All Books\n";
//         cout << "4. Display Available Books\n";
//         cout << "5. Display My Borrowed Books\n";
//         cout << "6. Logout\n";
//         cout << "Choose an option: ";
//     }
// };

// // Class representing a Book
// class Book {
// private:
//     int bookID;
//     string title;
//     string author;
//     string genre;
//     bool isBorrowed;
// public:
//     // Constructor to initialize book properties
//     Book(int id, string t, string a, string g) : bookID(id), title(t), author(a), genre(g), isBorrowed(false) {}

//     // Function to mark the book as borrowed
//     void borrowBook() {
//         isBorrowed = true;
//         cout << "Book borrowed: " << title << endl;
//     }

//     // Function to mark the book as returned
//     void returnBook() {
//         isBorrowed = false;
//         cout << "Book returned: " << title << endl;
//     }

//     // Function to display book information
//     void displayInfo() const {
//         cout << "BookID: " << bookID << ", Title: " << title << ", Author: " << author << ", Genre: " << genre << endl;
//     }

//     // Getter for the book's title
//     string getTitle() const {
//         return title;
//     }

//     // Getter for the book's ID
//     int getID() const {
//         return bookID;
//     }

//     // Getter for the book's borrowed status
//     bool getStatus() const {
//         return isBorrowed;
//     }

//     // Setter for the book's borrowed status
//     void setStatus(bool status) {
//         isBorrowed = status;
//     }
// };

// // Class representing the Library
// class Library {
// private:
//     vector<Book> books; // List of books in the library
//     vector<User*> users; // List of users in the library
//     int nextUserID = 1;
//     int nextBookID = 1;

//     // Function to generate the next user ID
//     int getNextUserID() {
//         return nextUserID++;
//     }

//     // Function to generate the next book ID
//     int getNextBookID() {
//         return nextBookID++;
//     }

// public:
//     // Function to add a book to the library
//     void addBook(string title, string author, string genre) {
//         books.emplace_back(getNextBookID(), title, author, genre);
//     }

//     // Function to remove a book from the library
//     void removeBook(int bookID) {
//         auto it = find_if(books.begin(), books.end(), [bookID](Book& b) { return b.getID() == bookID; });
//         if (it != books.end()) {
//             books.erase(it);
//             cout << "Book removed from library." << endl;
//         } else {
//             cout << "Book not found." << endl;
//         }
//     }

//     // Function to register a new user in the library
//     void registerUser(User* u) {
//         users.push_back(u);
//     }

//     // Function to borrow a book for a member
//     void borrowBook(int bookID, Member* member) {
//         auto it = find_if(books.begin(), books.end(), [bookID](Book& b) { return b.getID() == bookID && !b.getStatus(); });
//         if (it != books.end()) {
//             it->setStatus(true);
//             member->borrowBook(bookID);
//         } else {
//             cout << "Book not available." << endl;
//         }
//     }

//     // Function to return a book for a member
//     void returnBook(int bookID, Member* member) {
//         auto it = find_if(books.begin(), books.end(), [bookID](Book& b) { return b.getID() == bookID && b.getStatus(); });
//         if (it != books.end()) {
//             it->setStatus(false);
//             member->returnBook(bookID);
//         } else {
//             cout << "Book not found or not borrowed." << endl;
//         }
//     }

//     // Function to display all books in the library
//     void displayBooks() const {
//         cout << "All Books:\n";
//         for (const Book& b : books) {
//             b.displayInfo();
//         }
//     }

//     // Function to display available (not borrowed) books in the library
//     void displayAvailableBooks() const {
//         cout << "Available Books:\n";
//         for (const Book& b : books) {
//             if (!b.getStatus()) {
//                 b.displayInfo();
//             }
//         }
//     }

//     // Function to login a user by name
//     User* login(string name) {
//         for (User* u : users) {
//             if (u->getName() == name) {
//                 u->login();
//                 return u;
//             }
//         }
//         return nullptr;
//     }

//     // Function to register a new user via console input
//     void registerNewUser() {
//         int userType;
//         string name, email;

//         cout << "Select user type (1 for Admin, 2 for Member): ";
//         cin >> userType;
//         cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore any remaining input

//         cout << "Enter name: ";
//         getline(cin, name);
//         cout << "Enter email: ";
//         getline(cin, email);

//         if (userType == 1) {
//             registerUser(new Admin(getNextUserID(), name, email));
//         } else if (userType == 2) {
//             registerUser(new Member(getNextUserID(), name, email));
//         } else {
//             cout << "Invalid user type selected." << endl;
//         }
//     }

//     // Destructor to clean up dynamically allocated memory
//     ~Library() {
//         for (User* u : users) {
//             delete u;
//         }
//     }
// };

// int main() {
//     Library lib;

//     // Create initial books
//     lib.addBook("1984", "George Orwell", "Dystopian");
//     lib.addBook("To Kill a Mockingbird", "Harper Lee", "Classic");
//     lib.addBook("The Great Gatsby", "F. Scott Fitzgerald", "Classic");
//     lib.addBook("One Hundred Years of Solitude", "Gabriel Garcia Marquez", "Magical Realism");
//     lib.addBook("Pride and Prejudice", "Jane Austen", "Romance");
//     lib.addBook("War and Peace", "Leo Tolstoy", "Historical Fiction");
//     lib.addBook("The Catcher in the Rye", "J.D. Salinger", "Fiction");
//     lib.addBook("The Hobbit", "J.R.R. Tolkien", "Fantasy");
//     lib.addBook("Moby Dick", "Herman Melville", "Adventure");
//     lib.addBook("Ulysses", "James Joyce", "Modernist");
//     lib.addBook("The Odyssey", "Homer", "Epic");
//     lib.addBook("Madame Bovary", "Gustave Flaubert", "Fiction");
//     lib.addBook("Crime and Punishment", "Fyodor Dostoevsky", "Psychological Fiction");
//     lib.addBook("The Divine Comedy", "Dante Alighieri", "Epic");
//     lib.addBook("The Brothers Karamazov", "Fyodor Dostoevsky", "Philosophical Fiction");
//     lib.addBook("Anna Karenina", "Leo Tolstoy", "Fiction");
//     lib.addBook("Brave New World", "Aldous Huxley", "Dystopian");
//     lib.addBook("The Iliad", "Homer", "Epic");
//     lib.addBook("Jane Eyre", "Charlotte Bronte", "Romance");
//     lib.addBook("Wuthering Heights", "Emily Bronte", "Gothic Fiction");
//     lib.addBook("Don Quixote", "Miguel de Cervantes", "Adventure");
//     lib.addBook("The Picture of Dorian Gray", "Oscar Wilde", "Philosophical Fiction");

//     // Create initial users
//     Admin* admin = new Admin(1, "Admin", "admin@example.com");
//     Member* member = new Member(2, "User", "user@example.com");

//     // Register initial users
//     lib.registerUser(admin);
//     lib.registerUser(member);

//     cout << "USE THE ABOVE 'Admin' OR 'User' FOR CHECKING DEMO OF THE CODE OR YOU CAN REGISTER NEWLY" << endl;

//     int choice;
//     do {
//         cout << "\nLibrary Management System\n";
//         cout << "1. Login\n";
//         cout << "2. Register New User\n";
//         cout << "3. Exit\n";
//         cout << "Choose an option: ";
//         cin >> choice;

//         if (choice == 1) {
//             string userName;
//             cout << "Enter your name to login: ";
//             cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore any remaining input
//             getline(cin, userName);

//             User* currentUser = lib.login(userName);
//             if (currentUser) {
//                 bool loggedIn = true;
//                 while (loggedIn) {
//                     currentUser->showMenu();
//                     int option;
//                     cin >> option;

//                     // Handle Admin actions
//                     if (Admin* admin = dynamic_cast<Admin*>(currentUser)) {
//                         switch (option) {
//                         case 1: {
//                             string title, author, genre;
//                             cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore any remaining input
//                             cout << "Enter book title: ";
//                             getline(cin, title);
//                             cout << "Enter book author: ";
//                             getline(cin, author);
//                             cout << "Enter book genre: ";
//                             getline(cin, genre);
//                             lib.addBook(title, author, genre);
//                             break;
//                         }
//                         case 2: {
//                             int bookID;
//                             cout << "Enter book ID to remove: ";
//                             cin >> bookID;
//                             lib.removeBook(bookID);
//                             break;
//                         }
//                         case 3:
//                             lib.displayBooks();
//                             break;
//                         case 4:
//                             lib.displayAvailableBooks();
//                             break;
//                         case 5:
//                             currentUser->logout();
//                             loggedIn = false;
//                             break;
//                         default:
//                             cout << "Invalid option. Try again." << endl;
//                         }
//                     // Handle Member actions
//                     } else if (Member* member = dynamic_cast<Member*>(currentUser)) {
//                         switch (option) {
//                         case 1: {
//                             int bookID;
//                             cout << "Enter book ID to borrow: ";
//                             cin >> bookID;
//                             lib.borrowBook(bookID, member);
//                             break;
//                         }
//                         case 2: {
//                             int bookID;
//                             cout << "Enter book ID to return: ";
//                             cin >> bookID;
//                             lib.returnBook(bookID, member);
//                             break;
//                         }
//                         case 3:
//                             lib.displayBooks();
//                             break;
//                         case 4:
//                             lib.displayAvailableBooks();
//                             break;
//                         case 5:
//                             member->showBorrowedBooks();
//                             break;
//                         case 6:
//                             currentUser->logout();
//                             loggedIn = false;
//                             break;
//                         default:
//                             cout << "Invalid option. Try again." << endl;
//                         }
//                     }
//                 }
//             } else {
//                 cout << "User not found." << endl;
//             }
//         } else if (choice == 2) {
//             lib.registerNewUser();
//         }
//     } while (choice != 3);

//     return 0;
// }

#include <bits/stdc++.h>
using namespace std;

// ========================= Book Class =========================
class Book {
private:
    int id;
    string title;
    string author;
    bool isBorrowed;

public:
    Book(int i, string t, string a) : id(i), title(t), author(a), isBorrowed(false) {}

    int getId() const { return id; }
    string getTitle() const { return title; }
    string getAuthor() const { return author; }
    bool getStatus() const { return isBorrowed; }

    void borrowBook() { isBorrowed = true; }
    void returnBook() { isBorrowed = false; }

    void displayBook() const {
        cout << "ID: " << id << " | Title: " << title << " | Author: " << author
             << " | Status: " << (isBorrowed ? "Borrowed" : "Available") << endl;
    }
};

// ========================= User Class =========================
class User {
protected:
    int userID;
    string name;
    string email;

public:
    User(int id, string n, string e) : userID(id), name(n), email(e) {}
    virtual ~User() {}
    int getUserID() const { return userID; }
    string getName() const { return name; }
    string getEmail() const { return email; }
    virtual void displayMenu() = 0;
};

// ========================= Admin Class =========================
class Admin : public User {
public:
    Admin(int id, string n, string e) : User(id, n, e) {}
    void displayMenu() override {
        cout << "\n--- Admin Menu ---\n";
        cout << "1. Add Book\n2. Remove Book\n3. View All Books\n4. Logout\n";
    }
};

// ========================= Member Class =========================
class Member : public User {
private:
    vector<int> borrowedBooks;

public:
    Member(int id, string n, string e) : User(id, n, e) {}

    void borrowBook(int bookId) { borrowedBooks.push_back(bookId); }
    void returnBook(int bookId) {
        borrowedBooks.erase(remove(borrowedBooks.begin(), borrowedBooks.end(), bookId), borrowedBooks.end());
    }
    vector<int> getBorrowedBooks() const { return borrowedBooks; }

    void displayMenu() override {
        cout << "\n--- Member Menu ---\n";
        cout << "1. Borrow Book\n2. Return Book\n3. View All Books\n4. Logout\n";
    }
};

// ========================= Library Class =========================
class Library {
private:
    vector<Book> books;
    vector<User*> users;
    int nextBookId = 1;
    int nextUserId = 1;

public:
    Library() { loadData(); }
    ~Library() { saveData(); for (auto u : users) delete u; }

    int getNextBookID() { return nextBookId++; }
    int getNextUserID() { return nextUserId++; }

    // ---------------- File Handling ----------------
    void saveData() {
        // Save books
        ofstream bookFile("books.txt");
        for (auto &b : books) {
            bookFile << b.getId() << "|" << b.getTitle() << "|" << b.getAuthor() << "|" << b.getStatus() << "\n";
        }
        bookFile.close();

        // Save users
        ofstream userFile("users.txt");
        for (auto u : users) {
            userFile << u->getUserID() << "|" << u->getName() << "|" << u->getEmail()
                     << "|" << (dynamic_cast<Admin*>(u) ? "Admin" : "Member") << "\n";
        }
        userFile.close();
    }

    void loadData() {
        // Load books
        ifstream bookFile("books.txt");
        if (bookFile) {
            string line;
            while (getline(bookFile, line)) {
                stringstream ss(line);
                string id, title, author, status;
                getline(ss, id, '|');
                getline(ss, title, '|');
                getline(ss, author, '|');
                getline(ss, status, '|');
                Book b(stoi(id), title, author);
                if (status == "1") b.borrowBook();
                books.push_back(b);
                nextBookId = max(nextBookId, stoi(id) + 1);
            }
        }

        // Load users
        ifstream userFile("users.txt");
        if (userFile) {
            string line;
            while (getline(userFile, line)) {
                stringstream ss(line);
                string id, name, email, type;
                getline(ss, id, '|');
                getline(ss, name, '|');
                getline(ss, email, '|');
                getline(ss, type, '|');
                if (type == "Admin")
                    users.push_back(new Admin(stoi(id), name, email));
                else
                    users.push_back(new Member(stoi(id), name, email));
                nextUserId = max(nextUserId, stoi(id) + 1);
            }
        }
    }

    // ---------------- Book Management ----------------
    void addBook(string title, string author) {
        books.emplace_back(getNextBookID(), title, author);
        saveData();
    }

    void removeBook(int id) {
        books.erase(remove_if(books.begin(), books.end(), [id](Book &b) { return b.getId() == id; }), books.end());
        saveData();
    }

    void viewBooks() {
        cout << "\n--- Book List ---\n";
        for (auto &b : books) b.displayBook();
    }

    Book* findBook(int id) {
        for (auto &b : books)
            if (b.getId() == id) return &b;
        return nullptr;
    }

    // ---------------- User Management ----------------
    void registerUser(User* u) {
        users.push_back(u);
        saveData();
    }

    User* login(string name) {
        for (auto u : users)
            if (u->getName() == name) return u;
        return nullptr;
    }

    void registerNewUser() {
        int userType;
        string name, email;

        cout << "Select user type (1 for Admin, 2 for Member): ";
        cin >> userType;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "Enter name: ";
        getline(cin, name);
        cout << "Enter email: ";
        getline(cin, email);

        if (userType == 1) {
            registerUser(new Admin(getNextUserID(), name, email));
        } else if (userType == 2) {
            registerUser(new Member(getNextUserID(), name, email));
        } else {
            cout << "Invalid user type selected." << endl;
            return;
        }

        saveData(); // update users.txt immediately
        cout << "User registered successfully!\n";
    }
};

// ========================= Main =========================
int main() {
    Library lib;
    int choice;

    while (true) {
        cout << "\n--- Library System ---\n";
        cout << "1. Login\n2. Register New User\n3. Exit\nChoice: ";
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (choice == 1) {
            string name;
            cout << "Enter name: ";
            getline(cin, name);
            User* currentUser = lib.login(name);

            if (!currentUser) {
                cout << "User not found. Please register.\n";
                continue;
            }

            int opt;
            while (true) {
                currentUser->displayMenu();
                cout << "Choice: ";
                cin >> opt;

                if (dynamic_cast<Admin*>(currentUser)) {
                    if (opt == 1) {
                        string title, author;
                        cin.ignore();
                        cout << "Enter title: ";
                        getline(cin, title);
                        cout << "Enter author: ";
                        getline(cin, author);
                        lib.addBook(title, author);
                    } else if (opt == 2) {
                        int id;
                        cout << "Enter Book ID to remove: ";
                        cin >> id;
                        lib.removeBook(id);
                    } else if (opt == 3) {
                        lib.viewBooks();
                    } else break;
                } else if (dynamic_cast<Member*>(currentUser)) {
                    if (opt == 1) {
                        int id;
                        cout << "Enter Book ID to borrow: ";
                        cin >> id;
                        Book* b = lib.findBook(id);
                        if (b && !b->getStatus()) {
                            b->borrowBook();
                            dynamic_cast<Member*>(currentUser)->borrowBook(id);
                            cout << "Book borrowed successfully.\n";
                            lib.saveData();
                        } else cout << "Book unavailable.\n";
                    } else if (opt == 2) {
                        int id;
                        cout << "Enter Book ID to return: ";
                        cin >> id;
                        Book* b = lib.findBook(id);
                        if (b && b->getStatus()) {
                            b->returnBook();
                            dynamic_cast<Member*>(currentUser)->returnBook(id);
                            cout << "Book returned successfully.\n";
                            lib.saveData();
                        } else cout << "Invalid Book ID.\n";
                    } else if (opt == 3) {
                        lib.viewBooks();
                    } else break;
                }
            }
        } else if (choice == 2) {
            lib.registerNewUser();
        } else break;
    }

    return 0;
}
