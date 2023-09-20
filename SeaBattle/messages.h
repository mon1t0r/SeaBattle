#pragma once
#include <stdlib.h>
#include <windows.h>
#include "ship_ai.h"

extern HWND messagesHWND;

AIType ShowAIMessageBox();
int ShowGameOverMessageBox(bool);
int ShowRestartMessageBox();