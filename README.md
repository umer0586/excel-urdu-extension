# Convert amount to Urdu in Excel 

![excel capture](https://user-images.githubusercontent.com/35717992/144745325-3d962dbc-6868-4c36-8279-82dd218b8002.JPG)


## Complete Video Tutorial
[![IMAGE ALT TEXT](http://img.youtube.com/vi/WvcUi0CQaB0/0.jpg)](http://www.youtube.com/watch?v=WvcUi0CQaB0 "Convert amount to Urdu in Excel ")

This is an **extension/add-in** for **Microsoft Excel** to convert amount in figure to **Urdu** language.

Amount value ranging from `0 to 9999999999999` **(نناوے کھرب)**  can be converted to corresponding **Urdu words**

**Excel 2007** and above are supported **(32/64 bit)**



# How to convert amount in digits/figure to Urdu words in MS Excel

* Download [extension.rar](https://github.com/umer0586/excel-urdu-extension/releases)
* Extract folder to any location
* Click on `generate script.exe` it will produce `script.vba` file
* Open Excel then open **Visual Basic Editor** (Alt+F11) select `File > Import File` then choose `script.vba` file created by `generate script.exe`
* Now you can use `=URDU(10023420)` in any cell to convert amount

`Note :` You have to re-run `generate script.exe` whenever you **change the directory** of extracted folder or **rename** that extracted folder



# How to build DLLs from source

To build DLL `(urdu64.dll)` for 64 bit Excel use following `make` command with `mingw-w64` toolchain.

    make DLL_64

To build DLL `(urdu32.dll)` for 32 bit Excel, make sure you invoke following `make` command with 32 bit `MinGW` toolchain

    make DLL_32

Clean builds by

    make clean

*Build produces urdu64.dll, urdu32.dll under DLL folder and object files under OBJ folder*

##
*You can send feedback at umerfarooq2383@gmail.com*

