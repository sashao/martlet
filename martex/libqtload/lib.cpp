
#include <QCoreApplication>
#include <QEvent>

#include "filter.h"

static bool installed = false;
/*
int QCoreApplication::exec()
{
    printf("helo!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");


}

void QCoreApplication::exit(int)
{
    printf("helo!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
}
*/



void Proc()
{
}


#include <windows.h> 

//LRESULT CALLBACK GetMsgProc(int nCode, WPARAM wParam, LPARAM lParam)


 __declspec(dllexport) LRESULT CALLBACK GetMsgProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	if (!installed)
	{
		QCoreApplication::instance()->installEventFilter( new filter());
		installed = true;
	}


    return CallNextHookEx (NULL, nCode, wParam, lParam);
}

#ifdef Q_OS_WIN

/*bool WINAPI DllMain(HMODULE hModule, DWORD dwReason, PVOID pvReserved)
{
	printf("helo!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");

	if(dwReason == DLL_PROCESS_ATTACH)
   {
      
   }
   else if(dwReason == DLL_PROCESS_DETACH)
   {
      printf("helo!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
   }
   return true;
}
*/
/*BOOL APIENTRY DllMain( HANDLE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved )
{
    if( ul_reason_for_call == DLL_PROCESS_ATTACH )
    {
        // Increase reference count via LoadLibrary

        char lib_name[MAX_PATH]; 
        ::GetModuleFileName( hModule, lib_name, MAX_PATH );
        ::LoadLibrary( lib_name );

        // Safely remove hook

        ::UnhookWindowsHookEx( g_hHook );
    }    
    return TRUE;
}
*/
#else

bool QCoreApplication::event(QEvent *e)
{
//	printf(":)  %d \n", e->type());
    if (e->type() == QEvent::Quit) {
        quit();
        return true;
    }

	if (e->type() == QEvent::ApplicationActivate && !installed)
	{

		QCoreApplication::instance()->installEventFilter( new filter());
		installed = true;
	}
	return QObject::event(e);
}

#endif
