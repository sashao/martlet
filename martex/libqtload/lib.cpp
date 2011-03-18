
#include <QCoreApplication>
#include <QThread>
#include <QEvent>
#include <QPushButton>

#include "filter.h"
#include "MartletServer.h"
#include "CSVEventFabric.h"
#include "RequestToRemote.h"
#include "qspywidget.h"

void startSpy(QObject * obj)
{
    QSpyWidget::instance()->setObject(obj);
    QSpyWidget::instance()->show();
}


static bool installed = false;

static MartletServer* myServer = 0;
void TransferOutput(QtMsgType type, const char *msg)
{
    myServer->client()->perform( APP_DEBUG_2, type, QString::fromAscii(msg) );
}


#ifdef Q_OS_WIN

#include <windows.h> 

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

//                QCoreApplication::instance()->installEventFilter( new filter());
                myServer = new MartletServer(startSpy);
                AbstractEventFabric::setInstance(new CSVEventFabric());
		installed = true;
                qInstallMsgHandler(TransferOutput);
	}
	return QObject::event(e);
}

#endif
