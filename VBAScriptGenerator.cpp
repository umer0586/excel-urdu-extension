
#include <iostream>
#include <windows.h>
#include <fstream>
#include "VBAScriptGenerator.h"


void generateVBAScript(const std::string& scriptfileName)
{


	const std::string DLL_64 = getCurrentDirectory() + "\\urdu64.dll";
	const std::string DLL_32 = getCurrentDirectory() + "\\urdu32.dll";


	std::ofstream ofs(scriptfileName + ".bas");

	ofs << "Attribute VB_Name = \"loader\" " << std::endl;
	ofs << "#If VBA7 Then " << std::endl;
	ofs << "   Private Declare PtrSafe Function toUrdu Lib "<< "\"" << DLL_64 << "\"" <<" (ByVal a As String) As String" << std::endl;
	ofs << "#Else" << std::endl;
	ofs << "   Private Declare Function toUrdu Lib " << "\"" << DLL_32 << "\"" << " (ByVal a As String) As String" << std::endl;
	ofs << "#End If" << std::endl << std::endl;

	ofs << "Function URDU(digits As String)" << std::endl;
	ofs << "   URDU = StrConv(toUrdu(digits), vbFromUnicode)" << std::endl;
	ofs << "End Function" << std::endl;

	ofs.close();





}

std::string getCurrentDirectory()
{

	TCHAR Buffer[MAX_PATH];
	DWORD dwRet;

	dwRet = GetCurrentDirectory(MAX_PATH, Buffer);

	   if( dwRet == 0 )
	      std::cout << "GetCurrentDirectory failed " << GetLastError();

	   if(dwRet > MAX_PATH)
	      std::cout << "Buffer too small; need %d characters\n" <<  dwRet;


	   return std::string(Buffer);

}







