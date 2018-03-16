#include <stdarg.h>
#include "debugger.h"

void GxxGmOutputDebugString(const char *format, ...)
{
	va_list valist;
	va_start(valist, format);

	va_end(valist);
}