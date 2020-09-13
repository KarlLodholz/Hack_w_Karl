#include <iostream>
#include <windows.h>
#include <thread>
#include <process.h>

void beepone(void *arg)
{
    Beep(1000,100);
   _endthread();
}
//
// int main(int argc, char* argv[])
// {
//       _beginthread(beepone, 0, NULL);
//       Beep(3000,100);
// }


void operation1();
void operation2();


int main()
{
    thread task1 = thread(operation1);
    thread task2 = thread(operation2);
    task2.join();
    task1.join();


  std::cout << "hello world" << std::endl;
  //std::cout << "\a" << std::endl;

  // int j = 500;
  // for(int i = 500; i <= 3000; i += 15)
  // {
  //   //hertz, milliseconds
  //   Beep(i, j);
  //   j -= 10;
  //   if(j <= 0)
  //   {
  //     break;
  //   }
  // }
  //
  // Sleep(200);
  // Beep(100, 5000);

////////////////////////////////////////////////////////////////////////////////

  // Beep(300, 250);
  // Sleep(200);
  // Beep(440, 250);
  // Beep(520, 300);
  // Sleep(200);
  // Beep(440, 300);
  // Sleep(200);
  // Beep(349, 300);
  // Beep(275, 250);
  // Beep(275, 250);
  // Beep(275, 250);
  // Sleep(350);
  // Beep(250, 300);
  // Beep(275, 220);
  // Beep(350, 220);
  // Beep(440, 220);
  // Beep(520, 300);
  // Sleep(200);
  // Beep(440, 400);
  // Sleep(200);
  // Beep(300, 250);
  // Beep(500, 450);
  // Sleep(200);
  // Beep(475, 250);
  // Beep(450, 250);
  // Sleep(400);
  //
  // Beep(325, 250);
  // Sleep(200);
  // Beep(520, 250);
  // Beep(300, 300);
  // Sleep(200);
  // Beep(520, 400);
  // Sleep(200);
  // Beep(325, 250);
  // Sleep(200);
  // Beep(520, 400);
  // Sleep(200);
  // Beep(312, 250);
  // Beep(300, 250);
  // Sleep(200);
  // Beep(275, 250);
  return 0;
}

void operation1()
{
    Beep(523, 1000);
}

void operation2()
{
    Beep(262, 1000);
}
