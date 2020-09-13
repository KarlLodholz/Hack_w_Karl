#include <fstream>
#include <iostream>
#include <unistd.h>

int main() {

    const std::string queen_file_path;
    const std::string queen_file_name;
    const std::string worker_file_name;


    std::ifstream src;
    std::ofstream dst;
    const std::string startup_dest = "/home/karl/Desktop/code/c++/worker"; 
    for (;;) 
    { //cursed while loop
        dst.open(startup_dest);
        if(!src) {
            dst.close();
            src.open("worker");
            dst.open("/home/karl/Desktop/code/c++/worker");
            dst << src.rdbuf();
            std::cout<< "touched by GOD" <<std::endl;
        }
        else {
            std::cout<< "GOD has already given his gift"<<std::endl;
        }
        src.close();
        std::cout<<"in"<<std::endl;
        sleep(10);
    }
    std::cout<<" -> out"<<std::endl;
    return 0;
}