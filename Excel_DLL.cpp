#include "Excel_DLL.h"
#include <windows.h>

#include "../excel-urdu-extension/Amount.h"
//wrapping @class Amount under "C" interface
extern "C" __declspec(dllexport) BSTR __stdcall toUrdu(const char* digits)
{

	Amount amount(digits);

    BSTR urduText = SysAllocString(amount.toUrduUnicode().c_str());

	return urduText;

	/*
	 * String allocated with SysAllocString(BSTR) must explicitly be deallocated by Caller using SysFreeString(BSTR)
	 * BSTR is VBA's native String (i-e VBA stores strings as BSTR),
	 * VBA's garbage collector automatically deallocates string (BSTR) so no need to call SysFreeString(BSTR) at VBA side (Its not a memory leak)
	 *
	 * @link https://stackoverflow.com/questions/14280569/in-vb6-do-i-need-to-call-sysfreestring-on-strings-allocated-with-sysallocstring
	 * @link https://github.com/ReneNyffenegger/VBA-calls-DLL/issues/1
	 * */

}

/*
 * I tried all string returning methods @ https://renenyffenegger.ch/notes/development/languages/VBA/Calling-DLLs/return-char-array
 * The only return method which worked perfectly for Urdu was the Last one i-e returning BSTR from DLL to VBA
 *
 * */

