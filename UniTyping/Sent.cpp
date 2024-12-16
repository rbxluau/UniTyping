#include <Windows.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cwchar>
using namespace std;

int main(int argc, char* argv[]) {
    string arg1 = argc > 1 ? argv[1] : "";
    string arg2 = argc > 2 ? argv[2] : "3000";
    string arg3 = argc > 3 ? argv[3] : "0";
    ifstream file(arg1);
    stringstream stream;
    stream << file.rdbuf();
    string temp = stream.str();
    int buffer = MultiByteToWideChar(CP_ACP, 0, temp.c_str(), -1, NULL, 0);
    wchar_t* unicode = new wchar_t[buffer];
    MultiByteToWideChar(CP_ACP, 0, temp.c_str(), -1, unicode, buffer);
    INPUT inputs[2]{};
    size_t sent = 1;
    size_t len = wcslen(unicode);
    Sleep(stoi(arg2));
    for (size_t i = 0; i < len; i++)
    {
        inputs[0].type = INPUT_KEYBOARD;
        inputs[0].ki.wScan = unicode[i];
        inputs[0].ki.dwFlags = KEYEVENTF_UNICODE;
        inputs[1].type = INPUT_KEYBOARD;
        inputs[1].ki.wScan = unicode[i];
        inputs[1].ki.dwFlags = KEYEVENTF_KEYUP;
        SendInput(ARRAYSIZE(inputs), inputs, sizeof(INPUT));
        cout << "\r" << sent++ << "/" << len;
        Sleep(stoi(arg3));
    }
    return 0;
}