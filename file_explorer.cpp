
#include <iostream>
#include <fstream>
#include <dirent.h>
#include <unistd.h>
#include <cstdio>
#include <sys/stat.h>

using namespace std;

// show files in current folder
void listFiles() {
    DIR *d = opendir(".");
    struct dirent *entry;
    if (!d) {
        cout << "Cannot open folder\n";
        return;
    }
    cout << "Files here:\n";
    while ((entry = readdir(d)) != NULL) {
        cout << entry->d_name << "\n";
    }
    closedir(d);
}

// change directory
void changeDir() {
    string folder;
    cout << "Enter folder name (.. to go back): ";
    cin >> folder;
    if (chdir(folder.c_str()) == 0)
        cout << "Folder changed\n";
    else
        cout << "Cannot change folder\n";
}

// create a new file
void createFile() {
    string name;
    cout << "Enter new file name: ";
    cin >> name;
    ofstream f(name.c_str());
    if (f) {
        cout << "File created\n";
        f.close();
    } else {
        cout << "Could not create file\n";
    }
}

// delete a file
void deleteFile() {
    string name;
    cout << "Enter file name to delete: ";
    cin >> name;
    if (remove(name.c_str()) == 0)
        cout << "File deleted\n";
    else
        cout << "Could not delete file\n";
}

// copy file
void copyFile() {
    string s, d;
    cout << "Enter source file name: ";
    cin >> s;
    cout << "Enter destination file name: ";
    cin >> d;

    ifstream in(s.c_str(), ios::binary);
    if (!in) {
        cout << "Source not found\n";
        return;
    }
    ofstream out(d.c_str(), ios::binary);
    if (!out) {
        cout << "Cannot create destination\n";
        return;
    }
    out << in.rdbuf();
    in.close();
    out.close();
    cout << "File copied\n";
}

// move or rename file
void moveFile() {
    string oldn, newn;
    cout << "Enter old file name: ";
    cin >> oldn;
    cout << "Enter new file name or path: ";
    cin >> newn;
    if (rename(oldn.c_str(), newn.c_str()) == 0)
        cout << "Moved / Renamed\n";
    else
        cout << "Could not move/rename\n";
}

// make directory
void makeDir() {
    string name;
    cout << "Enter folder name to create: ";
    cin >> name;
    if (mkdir(name.c_str(), 0755) == 0)
        cout << "Folder created\n";
    else
        cout << "Could not create folder\n";
}

// remove directory (must be empty)
void removeDir() {
    string name;
    cout << "Enter folder name to remove: ";
    cin >> name;
    if (rmdir(name.c_str()) == 0)
        cout << "Folder removed\n";
    else
        cout << "Could not remove folder (maybe not empty)\n";
}

// show current working directory
void showCurDir() {
    char buf[1024];
    if (getcwd(buf, sizeof(buf)) != NULL)
        cout << "Current dir: " << buf << "\n";
    else
        cout << "Cannot get current dir\n";
}

// search file by part of name
void searchFile() {
    string key;
    cout << "Enter name or part to search: ";
    cin >> key;
    DIR *d = opendir(".");
    struct dirent *entry;
    if (!d) {
        cout << "Cannot open folder\n";
        return;
    }
    bool found = false;
    while ((entry = readdir(d)) != NULL) {
        string n = entry->d_name;
        if (n.find(key) != string::npos) {
            cout << "Found: " << n << "\n";
            found = true;
        }
    }
    closedir(d);
    if (!found) cout << "No matching file found\n";
}

// show permissions in octal
void showPerm() {
    string f;
    cout << "Enter file name: ";
    cin >> f;
    struct stat st;
    if (stat(f.c_str(), &st) == 0) {
        cout << "Permissions (octal): " << oct << (st.st_mode & 0777) << dec << "\n";
    } else {
        cout << "Cannot access file\n";
    }
}

// change permissions (enter like 644)
void changePerm() {
    string f;
    int mode;
    cout << "Enter file name: ";
    cin >> f;
    cout << "Enter new permission (e.g. 644): ";
    cin >> mode;
    if (chmod(f.c_str(), mode) == 0)
        cout << "Permissions changed\n";
    else
        cout << "Could not change permissions\n";
}

int main() {
    int choice;
    while (true) {
        cout << "\n=== FILE EXPLORER APP ===\n";
        cout << "1. List files\n";
        cout << "2. Change directory\n";
        cout << "3. Create file\n";
        cout << "4. Delete file\n";
        cout << "5. Copy file\n";
        cout << "6. Move / Rename file\n";
        cout << "7. Make directory\n";
        cout << "8. Remove directory\n";
        cout << "9. Show current directory\n";
        cout << "10. Search file\n";
        cout << "11. Show permissions\n";
        cout << "12. Change permissions\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 0) {
            cout << "Goodbye!\n";
            break;
        }
        switch (choice) {
            case 1: listFiles(); break;
            case 2: changeDir(); break;
            case 3: createFile(); break;
            case 4: deleteFile(); break;
            case 5: copyFile(); break;
            case 6: moveFile(); break;
            case 7: makeDir(); break;
            case 8: removeDir(); break;
            case 9: showCurDir(); break;
            case 10: searchFile(); break;
            case 11: showPerm(); break;
            case 12: changePerm(); break;
            default: cout << "Invalid choice\n"; break;
        }
    }
    return 0;
}
