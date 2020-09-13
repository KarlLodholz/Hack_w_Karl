#pragma comment( lib, "winmm.lib" )

#include <iostream>
#include <windows.h>
#include <mmsystem.h>
#include <tchar.h>
#include <thread>

int main()
{
/*  int j = 500;
  for(int i = 500; i <= 3000; i += 15)
  {
    //hertz, milliseconds
    Beep(i, j);
    j -= 10;
    if(j <= 0)
    {
      break;
    }
  }*/

/*
  //List of cow sounds .wav
  std::vector <std::string> cowList;
  WIN32_FIND_DATA FindFileData;
  HANDLE hFind = FindFirstFile("C:\\Users\\tmorg\\OneDrive\\Documents\\Coding Projects\\Hackin_w_Karl\\sounds", &FindFileData);
  if (hFind == INVALID_HANDLE_VALUE) {
      printf ("FindFirstFile failed (%d)\n", GetLastError());
  }

  do {
      if (FindFileData.dwFileAttributes & !FILE_ATTRIBUTE_DIRECTORY)
          cowList.push_back(FindFileData.cFileName);
  } while (FindNextFile(hFind, &FindFileData) != 0);

  FindClose(hFind);
  for (int i = 0; i < cowList.size(); i++)
  {
    std::cout << cowList[i] << std::endl;
  }
  std::cout << "after loop" << std::endl;

  //Hit em with the moo
  srand(time(NULL));
  int randNum = rand() % cowList.size();
  std::string randomCow = cowList[randNum];
//  LPCSTR lprandomCow = randomCow.c_str();
//  std::cout << randomCow << std::endl;
//  std::cout << lprandomCow << std::endl;
//  PlaySound(lprandomCow, GetModuleHandle(NULL), SND_FILENAME);
//  PlaySound(L"regular.wav", GetModuleHandle(NULL), SND_FILENAME);
*/

  PlaySoundA((LPCSTR)"C:\\Users\\tmorg\\OneDrive\\Documents\\\"Coding Projects\"\\Hackin_w_Karl\\sounds\\cowhorn.wav", NULL, SND_FILENAME | SND_ASYNC);
  std::system("pause");
  return 0;
}
