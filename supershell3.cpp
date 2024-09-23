#include <iostream>
#include <string>
#include <fstream>
#include <unistd.h>  // For chdir()

using namespace std;

class supershell {
private:
    string command;  // Single string to hold the command
    string breaked_command[10];  // Array to hold the split commands
    string path = "C:\\Users";  // Default path

public:
    // Constructor
    supershell() {
        if (chdir(path.c_str()) == 0) {
            cout << "Directory changed to: " << path << endl;
        } else {
            perror("chdir() error");
        }
    }

    // Method to get input continuously
    void get() {
        while (true) {
            cout << "User@UNKNOWM ";  // Shell-like prompt
            getline(cin, command);  // Get the full command input
            if (command.empty()) continue;  // Ignore empty inputs

            command_break();  // Break the command into words
            int action = checker();  // Check and perform actions based on command

            if (action == 0) break;  // Exit command
            if (action == 11) {  // Change directory
                // Check if the second part (directory) is provided
                if (breaked_command[1].empty()) {
                    cout << "Please provide a directory.\n";
                    continue;
                }
                path = breaked_command[1];
                if (chdir(path.c_str()) == 0) {  // Convert string to C-string using .c_str()
                    cout << "Directory changed to: " << path << endl;
                } else {
                    perror("chdir() error");  // Print error if chdir() fails
                }
            } else if (action == 2) {
                file_op(1);  // Create a file
            } else if (action == 3) {
                file_op(0);  // Read a file
            }
        }
    }

    // Method to split the command into words
    void command_break() {
        string word;
        int j = 0;
        for (int i = 0; i <= command.length(); i++) {
            if (command[i] == ' ' || i == command.length()) {  // Check for space or end of string
                breaked_command[j] = word;  // Store the word in the array
                j++;
                word = "";  // Reset word
            } else {
                word += command[i];  // Build the word
            }
        }
        // Ensure the array is properly terminated
        for (int k = j; k < 10; ++k) {
            breaked_command[k] = "";  // Reset remaining array elements
        }
    }

    // Method to check and execute the command
    int checker() {
        if (breaked_command[0] == "cd") {
            cout << "Changing directory\n";
            return 11;  // Trigger directory change
        } else if (breaked_command[0] == "ls") {
            // Listing files in the current directory
            system("dir");  // Use "ls" for Linux/macOS
        } else if (breaked_command[0] == "exit") {
            return 0;  // Exit the loop
        } else if (breaked_command[0] == "cwd") {
            // Show current working directory
            cout << "Current directory: " << path << endl;
        } else if (breaked_command[0] == "touch") {
            return 2;  // Create file
        } else if (breaked_command[0] == "cat") {
            return 3;  // Read file
        }else if (breaked_command[0] == "pwd"){
            cout<<path;
        }

        else {
            cout << "Unknown command\n";
        }
        return 1;  // Continue the loop
    }

    void read_file() {
        ifstream infile(breaked_command[1]);  // Open file for reading

        if (!infile) {  // Check if the file opened successfully
            cerr << "Error opening file for reading." << endl;
            return;
        }

        string line;
        while (getline(infile, line)) {  // Read file line by line
            cout << line << endl;
        }

        infile.close();
    }

    void make_file() {
        ofstream outfile(breaked_command[1]);  // Open file for writing

        if (!outfile) {  // Check if the file opened successfully
            cerr << "Error opening file for writing." << endl;
            return;
        }

        outfile << "Hello, world!" << endl;  // Write to file

        outfile.close();
    }

    void file_op(int mode) {
        if (mode) {
            make_file();
        } else {
            read_file();
        }
    }

    // Destructor
    ~supershell() {}
};

int main() {
    supershell shell;  // Create an object of supershell
    shell.get();  // Start the shell interface
    return 0;
}
