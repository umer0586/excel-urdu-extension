
# $(CURDIR) is predefine variable which
OBJ_DIR = $(CURDIR)/OBJ
DLL_DIR = $(CURDIR)/DLL

CC = g++

# Invoke this target with mingw-w64 toolchain
DLL_64: $(DLL_DIR)/urdu64.dll

# Invokde this target with MingGW 32 bit toolchain
DLL_32: $(DLL_DIR)/urdu32.dll

# -static flag tells linker to statically link required libraries from toolchain (toolchain are packed with both static and dll version of libraries) into urdu(32/64).dll. 
# If we dont use -static flag then we have to distrubute libstdc++-6.dll and libgcc_s_dw2-1.dll along with urdu32.dll and also libwinpthread-1.dll when using mingw-w64 toolchain

$(DLL_DIR)/urdu64.dll: $(OBJ_DIR)/Excel_DLL.o $(OBJ_DIR)/Amount.o
	$(CC) $^ -o $@ -loleAut32 -m64 -static -shared  


$(DLL_DIR)/urdu32.dll: $(OBJ_DIR)/Excel_DLL.o $(OBJ_DIR)/Amount.o
	$(CC) $^ -o $@ -loleAut32 -static -shared 


$(OBJ_DIR)/Excel_DLL.o: Excel_DLL.cpp Excel_DLL.h
	$(CC) -c Excel_DLL.cpp -o $@ -Wl,--add-stdcall-alias 


$(OBJ_DIR)/Amount.o: Amount.cpp Amount.h
	$(CC) -c Amount.cpp -o $@ -std=c++11


clean:
	$(RM) $(OBJ_DIR)/*.o $(DLL_DIR)/*.dll


