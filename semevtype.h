#ifndef SEM_EVENT_TYPE_H
#define SEM_EVENT_TYPE_H

enum semEv_t {
  SE_NOTHING,
  SE_APP_FOCUSED,
  SE_APP_BLURED,
  SE_SCRIPT_RESTART,
  SE_SCRIPT_CANCEL,
  SE_SCRIPT_SPECIAL,
  SE_PROGRAM_CLOSE,
  SE_SCRIPT_WIGGLE,
  SE_SCRIPT_STRUGGLE,
  SE_SCRIPT_AUTOGEN,
  SE_SCRIPT_TOXIC,
};

enum stopSemEv_t {
  SSE_NOTHING,
  SSE_STOP,
  SSE_ACTION,
  SSE_RESET,
};

#endif