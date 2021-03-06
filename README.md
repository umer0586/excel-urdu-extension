# Convert amount to Urdu in Excel 

This is an **extension/add-in** for **Microsoft Excel** to convert amount in figure to **Urdu** language.

Amount value ranging from `0 to 9999999999999` **(نناوے کھرب)**  can be converted to corresponding **Urdu words**

**Excel 2007** and above are supported **(32/64 bit)**

[Amount.cpp](https://github.com/umer0586/excel-urdu-extension/blob/master/Amount.cpp) is a major (C++) class which converts amount from **figure/digits** to **Urdu**


```c++
#include <iostream>
#include <string>
#include <fstream>
#include "Amount.h"

int main() {

  Amount amount("23445");

  /*
  * or you can also do the following
  * Amount amount;
  * amount.setDigits("23445");
  *
  */

  //To get Unicode Urdu string
  std::wstring amountInUrdu = amount.toUrduUnicode();

  //To get UTF-8 encoded Urdu string
  std::string amountInUrduUTF8 = amount.toUrduUTF8();

  // If console doesn't support UTF-8 you will not be able to see Urdu text
  std::cout << amountInUrduUTF8;

  // To check if code works you can write output to file
  std::ofstream ofs("output.txt");

  ofs << amount.getDigits()  << " = " << amountInUrduUTF8 ;

  ofs.close();

 return 0;

 }

```
If you compile and run this code you will get `output.txt` file containing the text `23445 = تئیس ہزار چار سو پینتالیس`


# How to convert amount in digits/figure to Urdu words in MS Excel

* Download [extension.rar](https://github.com/umer0586/excel-urdu-extension/releases/tag/v1.0)
* Extract folder to any location
* Click on `generate script.exe` it will produce `script.vba` file
* Open Excel then open **Visual Basic Editor** (Alt+F11) select `File > Import File` then choose `script.vba` file created by `generate script.exe`
* Now you can use `=URDU(10023420)` in any cell to convert amount

`Note :` You have to re-run `generate script.exe` whenever you **change the directory** of extracted folder or **rename** that extracted folder

if `generate script.exe` doesn't produce `script.vba` file then you have to do some setups manualy :(

Just create a new `Module` in **Visual Basic Editor** and paste following piece of VBA code in a newly created `Module`

``` VBA

Attribute VB_Name = "loader" 
#If VBA7 Then 
   Private Declare PtrSafe Function toUrdu Lib "<Path to urdu64.dll>" (ByVal a As String) As String
#Else
   Private Declare Function toUrdu Lib "<Path to urdu32.dll>" (ByVal a As String) As String
#End If

Function URDU(digits As String)
   URDU = StrConv(toUrdu(digits), vbFromUnicode)
End Function

```
Replace `<path to urdu64.dll>` with path of `urdu64.dll` file and replace `<Path to urdu32.dll>` with path of `urdu32.dll` file



# How to build DLLs from source

To build DLL `(urdu64.dll)` for 64 bit Excel use following `make` command with `mingw-w64` toolchain.

    make DLL_64

To build DLL `(urdu32.dll)` for 32 bit Excel, make sure you invoke following `make` command with 32 bit `MinGW` toolchain

    make DLL_32

Clean builds by

    make clean

*Build produces urdu64.dll, urdu32.dll under DLL folder and object files under OBJ folder*

