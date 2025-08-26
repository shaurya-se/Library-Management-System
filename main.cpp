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

