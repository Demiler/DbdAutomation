#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>

HANDLE hStdin;
DWORD fdwSaveOldMode;

void closeProgram() {
  printf("Exiting...\n");
  //clear possible console input
  INPUT_RECORD irInBuf[4096];
  DWORD cNumRead;
  ReadConsoleInput(hStdin, irInBuf, 4096, &cNumRead);

  //resotre old console mod
  SetConsoleMode(hStdin, fdwSaveOldMode);
  //release hook
	UnhookWindowsHookEx(_hook);
  //terminate program
  exit(0);
}
 
// variable to store the HANDLE to the hook. Don't declare it anywhere else then globally
// or you will get problems since every function uses this variable.
HHOOK _hook;
 
// This struct contains the data received by the hook callback. As you see in the callback function
// it contains the thing you will need: vkCode = virtual key code.
KBDLLHOOKSTRUCT kbdStruct;
 
// This is the callback function. Consider it the event that is raised when, 
// in this case, a key is pressed.
LRESULT __stdcall
HookCallback(int nCode, WPARAM wParam, LPARAM lParam) {
	if (nCode >= 0) {
		// the action is valid: HC_ACTION.
		if (wParam == WM_KEYDOWN) {
			// lParam is the pointer to the struct containing the data needed, 
      // so cast and assign it to kdbStruct.

			kbdStruct = *((KBDLLHOOKSTRUCT*)lParam);
			/*// a key (non-system) is pressed.
			if (kbdStruct.vkCode == VK_F1) {
				// F1 is pressed!
				MessageBox(NULL, "F1 is pressed!", "key pressed", MB_ICONINFORMATION);
			}*/

      if (kbdStruct.vkCode == 0x51) { //q key
        closeProgram();
      }

      printf("%5d | %5d\n", kbdStruct.vkCode, nCode);
		}
	}
 
	// call the next hook in the hook chain.
  //This is nessecary or your hook chain will break and the hook stops
	return CallNextHookEx(_hook, nCode, wParam, lParam);
}

void
SetHook() {
	// Set the hook and set it to use the callback function above
	// WH_KEYBOARD_LL means it will set a low level keyboard hook. 
  // More information about it at MSDN.
	// The last 2 parameters are NULL, 0 because the callback function 
  // is in the same thread and window as the
	// function that sets and releases the hook. 
  // If you create a hack you will not need the callback function 
	// in another place then your own code file anyway. Read more about it at MSDN.
	if (!(_hook = SetWindowsHookEx(WH_KEYBOARD_LL, HookCallback, NULL, 0))) {
		MessageBox(NULL, "Failed to install hook!", "Error", MB_ICONERROR);
	}
}
 
int
main(void) {
  // Get the standard input handle.
  hStdin = GetStdHandle(STD_INPUT_HANDLE);
  if (hStdin == INVALID_HANDLE_VALUE)
    return 1;

  // Save the current input mode, to be restored on exit.
  if (!GetConsoleMode(hStdin, &fdwSaveOldMode))
    return 2;

  // Enable the window and mouse input events.
  DWORD fdwMode = ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT;
  if (!SetConsoleMode(hStdin, fdwMode))
    return 3;

  printf("Console output enabled successfully\n");

	// Set the hook
	SetHook();
 
	// Don't mind this, it is a meaningless loop to keep a console application running.
	// I used this to test the keyboard hook functionality. If you want to test it, keep it in ;)
	MSG msg;
	GetMessage(&msg, NULL, 0, 0);
  return 0;
}
