import platform
import os
import shutil

exe_path = "build/I_wanna_riding_the_bike/"
exe_name = "play"
dll_path = "dependence/dll/"
exe_full_path = ""
if platform.system() == "Windows":
    exe_full_path = exe_path + exe_name +".exe"
else:
    exe_full_path = exe_path + exe_name

if not os.path.exists(exe_full_path):
    print("no such file {}, please `cmake ..` and `make` in build directory".format(exe_full_path))
else:
    if platform.system() == "Windows":
        if not os.path.exists(dll_path):
            print("{} is not exists, please input necessary DLLs in it".format(dll_path))
        else:
            srcfiles = os.listdir(dll_path)
            dstfile = os.listdir(exe_path)
            for f in srcfiles:
                if not f in dstfile:
                    shutil.copy(dll_path+f, exe_path)
            os.system("./"+exe_full_path)
    else:
        os.system("./"+exe_full_path)
    os.system(r"echo result of play: $?")
