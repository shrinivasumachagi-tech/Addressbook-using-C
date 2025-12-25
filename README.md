# Addressbook-using-C
Address Book Project is a console-based contact management system developed in C. It supports creating, searching, editing, deleting, and saving contacts with strict validation. The project uses structures, file handling, and modular programming on Linux.
# 📘 Address Book Project (C)
This project demonstrates real-world usage of **C programming**, commonly required in **Embedded Systems and Linux-based development**.

## 📌 Project Overview

The Address Book Project is designed to store and manage contact details such as **Name, Mobile Number, and Email ID**.  
It supports **creating, searching, editing, deleting, and saving contacts** while enforcing strict input validation rules to ensure data integrity.

## 🚀 Features

- Create new contacts with validation
- Search contacts by:
  - Name
  - Mobile Number
  - Email ID
- Edit contact details:
  - Name
  - Phone Number
  - Email ID
  - All fields
- Delete existing contacts
- Save contacts to a file
- Alphabetical sorting of contacts before saving
- Persistent storage using file handling

---

## 🗂️ File Structure
├── main.c # Main menu and program execution
├── contact.c # Core logic (create, search, edit, delete, save)
├── contact.h # Structure definitions and function declarations
├── data.txt # Contact storage file (generated at runtime)
└── README.md # Project documentation


---

## 🏗️ Data Structures Used

### Contacts Structure
```c
typedef struct
{
    char Name[30];
    char Mobile_number[11];
    char Mail_ID[30];
} Contacts;

typedef struct
{
    Contacts contact_details[100];
    int contact_count;
} AddressBook;


