#ifndef GLOBAL_VARS_H
#define GLOBAL_VARS_H
#include <windows.h>
#include <stdbool.h>
#include "semevtype.h"

extern bool active;// = false;
extern bool showKeys;// = false;
extern HANDLE semaphore;
extern enum semEv_t semEv;

#endif
