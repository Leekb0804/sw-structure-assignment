#ifndef __CURSOR_H__
#define __CURSOR_H__

#include <Windows.h>

void SetCurrentCursorPos(int x, int y);
COORD GetCurrentCursorPos(void);
void RemoveCursor(void);


#endif // !__CURSOR_H__