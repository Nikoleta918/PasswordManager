Password Manager (C Language)
This is a simple Command-Line Password Manager written in C. It allows users to save, retrieve, and delete passwords associated with various services. Access is controlled through a master login credential.

⚠️ Disclaimer: This is a basic educational project and does not use encryption or secure practices. Do not use it to store real passwords.

Features
Master Login System
Users can set a master username, which is used to authenticate before accessing passwords.

Add New Passwords
Store usernames for various services.

Retrieve Passwords
Look up a username for a service by entering the service name.

Delete All Saved Passwords
Clear the saved entries.

File Structure
masterCredentials.txt – Stores the master username (plaintext).

savedServices.txt – Stores service names and associated usernames.

How to Use
Compile the Program

bash
Copy
Edit
gcc password_manager.c -o password_manager
Run the Program

bash
Copy
Edit
./password_manager
Menu Options

Option	Description
1	Enter master login credentials (creates or overwrites masterCredentials.txt)
2	Login using your master username
3	Add a new password (service + username)
4	Delete all saved passwords
5	Retrieve a saved username by service name

File Paths
Update file paths before compiling on your own system!

This code uses absolute paths like:

c
Copy
Edit
"C:\\Users\\super\\Desktop\\C_Projects\\savedServices.txt"
Update them or make them relative paths for portability.

Security Warning
Data is stored in plain text.

No encryption is used.

Anyone with access to the files can read the credentials.

Use this code only for learning purposes.
