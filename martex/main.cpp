#include <QtGui/QApplication>

#include <stdio.h>
#include <stdlib.h>

#ifdef Q_OS_WIN

#include <windows.h>

#else

#include <dlfcn.h>

#endif

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
	if (argc < 1) return -1;
	QString str(QObject::tr("translate me"));
	    qWarning("TODO check for lib existance: %s:%d", __FILE__, __LINE__);
	    qWarning("TODO check for executable existance: %s:%d", __FILE__, __LINE__);
	    qWarning("TODO: %s:%d", __FILE__, __LINE__);

#ifdef Q_OS_WIN

HANDLE hProcess;

HANDLE hThread;
char    szLibPath[_MAX_PATH];  // The name of our "LibSpy.dll" module

                               // (including full path!);

void*   pLibRemote;   // The address (in the remote process) where 

                      // szLibPath will be copied to;

DWORD   hLibModule;   // Base address of loaded module (==HMODULE);

HMODULE hKernel32 = ::GetModuleHandle(L"Kernel32");

// initialize szLibPath

//...


// 1. Allocate memory in the remote process for szLibPath

// 2. Write szLibPath to the allocated memory

pLibRemote = ::VirtualAllocEx( hProcess, NULL, sizeof(szLibPath),
                               MEM_COMMIT, PAGE_READWRITE );
::WriteProcessMemory( hProcess, pLibRemote, (void*)szLibPath,
                      sizeof(szLibPath), NULL );


// Load "LibSpy.dll" into the remote process

// (via CreateRemoteThread & LoadLibrary)

hThread = ::CreateRemoteThread( hProcess, NULL, 0,
            (LPTHREAD_START_ROUTINE) ::GetProcAddress( hKernel32,
                                       "LoadLibraryA" ),
             pLibRemote, 0, NULL );
::WaitForSingleObject( hThread, INFINITE );

// Get handle of the loaded module

::GetExitCodeThread( hThread, &hLibModule );

// Clean up

::CloseHandle( hThread );
::VirtualFreeEx( hProcess, pLibRemote, sizeof(szLibPath), MEM_RELEASE );

#else
		    int ret;
            char *nargv[] = { (char *)0 };
            char *env[] = { "HOME=/home/oomel", "LOGNAME=oomel", "DISPLAY=:0.0", "LD_PRELOAD=./libQtLoad.so", (char *)0 };
            ret = execve (argv[1], nargv, env);

#endif

}
