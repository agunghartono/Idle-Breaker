#include <iostream>
#define _WIN32_WINNT 0x502
#include <windows.h>
using namespace std;

class IdleBreaker
{
private:
    LASTINPUTINFO info;
    DWORD idleSeconds;
protected:
    void press()
    {
        keybd_event(VK_NUMLOCK,0x45,KEYEVENTF_EXTENDEDKEY | 0,0);
        keybd_event(VK_NUMLOCK,0x45,KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP,0);
        keybd_event(VK_NUMLOCK,0x45,KEYEVENTF_EXTENDEDKEY | 0,0);
        keybd_event(VK_NUMLOCK,0x45,KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP,0);
    }
public:
    void getidle()
    {
        info.cbSize=sizeof(info);
        GetLastInputInfo(&info);
        idleSeconds=(GetTickCount()-info.dwTime)/1000;
        if(idleSeconds>9)press();
    }
};

int main()
{
    ShowWindow(GetConsoleWindow(),SW_HIDE);
    IdleBreaker appBreaker;
    while(true)
    {
        appBreaker.getidle();
        Sleep(1000);
    }
    return 0;
}
