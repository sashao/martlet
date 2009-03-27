
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

#ifdef Q_OS_WIN

#include <windows.h> 

bool WINAPI DllMain(HMODULE hModule, DWORD dwReason, PVOID pvReserved)
{
   if(dwReason == DLL_PROCESS_ATTACH)
   {
      printf("helo!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
   }
   else if(dwReason == DLL_PROCESS_DETACH)
   {
      printf("helo!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
   }
   return true;
}

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
