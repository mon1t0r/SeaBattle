#include "messages.h"
#include <commctrl.h>
#include "ship_ai.h"

#pragma comment(lib, "comctl32.lib")

#if defined _M_IX86
#pragma comment(linker, "/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_IA64
#pragma comment(linker, "/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='ia64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker, "/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker, "/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif

HWND messagesHWND;

AIType ShowAIMessageBox()
{
	int nButtonPressed = 0;
	TASKDIALOGCONFIG config = { 0 };
	const TASKDIALOG_BUTTON buttons[] = {
		{ 0, L"Easy" },
		{ 1, L"Medium" },
		{ 2, L"Hard" },
		{ 3, L"Exit" }
	};
	config.cbSize = sizeof(config);
	config.hwndParent = messagesHWND;
	config.pszMainIcon = TD_INFORMATION_ICON;
	config.pszWindowTitle = L"Welcome";
	config.pszContent = L"Welcome to Sea Battle. You can always restart the game by pressing F1. Please select difficulty.";
	config.pButtons = buttons;
	config.cButtons = ARRAYSIZE(buttons);

	TaskDialogIndirect(&config, &nButtonPressed, NULL, NULL);
	switch (nButtonPressed)
	{
	case 0:
	case 1:
	case 2:
		return nButtonPressed;
		break;
	default:
		exit(0);
		break;
	}

	return 0;
}

int ShowGameOverMessageBox(bool winner)
{
	int nButtonPressed = 0;
	TASKDIALOGCONFIG config = { 0 };
	const TASKDIALOG_BUTTON buttons[] = {
		{ IDYES, L"Yes" },
		{ IDNO, L"No" }
	};
	config.cbSize = sizeof(config);
	config.hwndParent = messagesHWND;
	config.pszMainIcon = TD_INFORMATION_ICON;
	config.nDefaultButton = IDYES;
	config.pszWindowTitle = L"Game Over";
	config.pszContent = winner ?
		L"You won! Congratulations!\nDo you want to play again?" :
		L"You lose. Better luck next time.\nDo you want to play again?";
	config.pButtons = buttons;
	config.cButtons = ARRAYSIZE(buttons);

	TaskDialogIndirect(&config, &nButtonPressed, NULL, NULL);

	return nButtonPressed;
}

int ShowRestartMessageBox()
{
	int nButtonPressed = 0;
	TASKDIALOGCONFIG config = { 0 };
	const TASKDIALOG_BUTTON buttons[] = {
		{ IDYES, L"Yes" },
		{ IDNO, L"No" }
	};
	config.cbSize = sizeof(config);
	config.hwndParent = messagesHWND;
	config.pszMainIcon = TD_INFORMATION_ICON;
	config.nDefaultButton = IDNO;
	config.pszWindowTitle = L"Confirmation";
	config.pszContent = L"Are you sure you want to restart the game?";
	config.pButtons = buttons;
	config.cButtons = ARRAYSIZE(buttons);

	TaskDialogIndirect(&config, &nButtonPressed, NULL, NULL);

	return nButtonPressed;
}