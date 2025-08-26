# 📚 Library Management System (C++)

## 📖 Overview
This is a **console-based Library Management System** built in **C++** using Object-Oriented Programming (OOP) concepts.  
It allows **Admins** and **Members** to manage and interact with books in a digital library.  

The project also includes **file handling** to persist data about books and users across program executions.

---

## ✨ Features
### 👨‍💼 Admin
- Add new books  
- Remove existing books  
- View all books  

### 👤 Member
- Borrow available books  
- Return borrowed books  
- View all books  

### ⚙️ General
- Register new Admins or Members  
- Login with your name  
- Persistent data storage (`books.txt` and `users.txt`)  

---

## 🏗️ Classes Used
- **Book** → Represents a book with ID, title, author, and status.  
- **User** (abstract class) → Base class for Admin and Member.  
- **Admin** → Inherits from User; can add/remove books.  
- **Member** → Inherits from User; can borrow/return books.  
- **Library** → Manages books, users, and file handling.  

---

## 📂 File Handling
- **books.txt** → Stores all books with details (ID, title, author, status).  
- **users.txt** → Stores all registered users (ID, name, email, type).  

Example:
