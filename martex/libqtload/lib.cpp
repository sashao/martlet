
#include <QCoreApplication>
#include <QThread>
#include <QEvent>
#include <QPushButton>

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

//#pragma comment(linker, "/export:QCoreApplication::event=_RegistrationDll.QCoreApplication::event")

#include <windows.h> 

//LRESULT CALLBACK GetMsgProc(int nCode, WPARAM wParam, LPARAM lParam)


 __declspec(dllexport) LRESULT CALLBACK GetMsgProc(int nCode, WPARAM wParam, LPARAM lParam)
{

		printf("helo   GetMsgProc  !!!!!!!!!!!!!!!!!!!!!!!!!!!\n");

/*	if (!installed)
	{
		QCoreApplication::instance()->installEventFilter( new filter());
		installed = true;
	}
*/

    return CallNextHookEx (NULL, nCode, wParam, lParam);
}

#ifdef Q_OS_WIN

 class MyThread : public QThread
 {
 public:
	 void run();
 };


bool WINAPI DllMain(HMODULE hModule, DWORD dwReason, PVOID pvReserved)
{
	printf("helo!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
	if(dwReason == DLL_PROCESS_ATTACH)
   {
      printf("Attaching   helo!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");

   }
   else if(dwReason == DLL_PROCESS_DETACH)
   {
      printf("helo!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
   }
	 /*   if (!installed)
	{
		filter *f = new filter();
		f->moveToThread(QCoreApplication::instance()->thread());
		QCoreApplication::instance()->installEventFilter( f );
		f->moveToThread(QCoreApplication::instance()->thread());
		installed = true;
	}*/
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
#ifdef _MANAGED
#pragma managed(pop)
#endif



 void MyThread::run()
 {
	if (!installed)
	{
		filter *f = new filter();
//		f->moveToThread(QCoreApplication::instance()->thread());
		QCoreApplication::instance()->installEventFilter( f );
//		f->moveToThread(QCoreApplication::instance()->thread());
		installed = true;
	}
     exec();
 }

class Hello
{
public:
    Hello() {

	  	MyThread* t = new MyThread;
		t->start();
		//QPushButton w;
		//w.show();
		//QEventLoop el;
		//el.exec();
		//QCoreApplication::instance()->exec();
/*	  for (;;){
			QCoreApplication::instance()->processEvents();
	  }
*/

//		MessageBoxA(NULL, "Hello", "Hi", MB_OK);

    }
};

Hello h;



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
