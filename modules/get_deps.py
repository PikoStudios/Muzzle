import subprocess
import platform

def main():
    if (platform.system() == 'Windows'):
        print(f"OS: Windows {platform.release()} {platform.version()}")
        print("Compiling GLFW")
        subprocess.call('cd ../deps/glfw/; mkdir build; cd build; cmake .. -G "MinGW Makefiles"; mingw32-make.exe')
    else:
        print(f"OS: {platform.system()}")
        subprocess.call('cd ../deps/glfw/ && mkdir build && cd build && cmake .. && make')

if __name__ == "__main__":
    main()