//    Martlet - application automated Qt GUI application testing and more.
//    Copyright (C) 2010  Oleksandr Omelchuk sashao@e-mail.ua

//    This program is free software: you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    (at your option) any later version.

//    This program is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.

//    You should have received a copy of the GNU General Public License
//    along with this program.  If not, see <http://www.gnu.org/licenses/>.

#include <QApplication>
#include <QThread>
#include <QEvent>
#include <QPushButton>
#include <QMessageBox>

#include "filter.h"
#include "MartletServer.h"
#include "CSVEventFabric.h"
#include "RequestToRemote.h"
#include "qspywidget.h"

#ifndef Q_OS_WIN
#define __declspec(...)
#endif


__declspec(dllexport) void startSpy(QObject * obj)
{
    QSpyWidget::instance()->moveToThread(obj->thread());
    QSpyWidget::instance()->setObject(obj);
    QSpyWidget::instance()->show();
}


static bool installed = false;

static MartletServer* myServer = 0;
__declspec(dllexport) void TransferOutput(QtMsgType type, const char *msg)
{
    if (myServer) {
       myServer->client()->perform( APP_DEBUG_2, type, QString::fromAscii(msg) );
    }
}

#include <windows.h>
__declspec(dllexport) void installMartlet()
{
    if (!installed )
    {
        myServer = new MartletServer(startSpy);
        myServer->moveToThread(QCoreApplication::instance()->thread());

        AbstractEventFabric* ef = new CSVEventFabric();
        ef->moveToThread(QCoreApplication::instance()->thread());

        AbstractEventFabric::setInstance( ef );
        qInstallMsgHandler(TransferOutput);
        installed = true;
//        MessageBoxA(NULL, "Installed !!! ", "Hi   ", MB_OK);
//        if (QApplication::topLevelWidgets().count()>0) {
//            startSpy(QApplication::topLevelWidgets().at(0));
//        }
    }
}

#ifdef Q_OS_WIN

#include <windows.h> 

const long iterations = 35;

 class __declspec(dllexport) MyThread : public QThread
 {

 public:
	 void run();
 };

 __declspec(dllexport) DWORD ThreadProc (LPVOID lpdwThreadParam )
 {
//          QMessageBox::information(0, "Hello ", "\n\n\n\n\n GGG \n\n\n");
//             QPushButton w;
//                             w.show();
//                             QEventLoop el;
//                             el.exec();
//                             QCoreApplication::instance()->exec();
//            	  for (;;){
//                                    QCoreApplication::instance()->processEvents();
//                      }
     float fff = 9985;
 for (long i = 1 ; i< iterations; ++i ) {
     for (long j = 1 ; j< iterations; ++j ) {
         for (long k = 1 ; k< iterations; ++k ) {
             for (long m = 1 ; m< iterations; ++m ) {
 fff /= i+j/k*m;
}}}}

installMartlet();
 //ENd of thread
 return 0;
 }


// BOOL WINAPI DllMain(
//   __in  HINSTANCE hinstDLL,
//   __in  DWORD fdwReason,
//   __in  LPVOID lpvReserved
// );

//bool WINAPI DllMain(HMODULE hModule, DWORD dwReason, PVOID pvReserved)
BOOL WINAPI DllMain(HINSTANCE hModule, DWORD dwReason, LPVOID pvReserved)
{
    MessageBoxA(NULL, "Hello", "Hi DllMain !!! ", MB_OK);
     //QMessageBox::information(0, "Hello ", "\n\n\n\n\n GGG \n\n\n");
        //printf("helo!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
        if(dwReason == DLL_PROCESS_ATTACH)
   {

                float fff = 9985;
            for (long i = 1 ; i< iterations; ++i ) {
                for (long j = 1 ; j< iterations; ++j ) {
                    for (long k = 1 ; k< iterations; ++k ) {
                        for (long m = 1 ; m< iterations; ++m ) {
            fff /= i+j/k*m;
        }}}}
//            FILE* f = fopen("bwapi-error.txt", "a+");
//            fprintf(f, "Could not Create remote thread.\n");
//            //MessageBoxA(NULL, "Could not Create remote thread.\n", "Error", MB_OK);
//            fclose(f);

//            DisableThreadLibraryCalls(hModule);
//            CreateThread(NULL, //Choose default security
//            0, //Default stack size
//            (LPTHREAD_START_ROUTINE)&ThreadProc,
//            //Routine to execute
//            (LPVOID) NULL, //Thread parameter
//            0, //Immediately run the thread
//            NULL //Thread Id
//            );


            //		MessageBoxA(NULL, "Hello", "Hi", MB_OK);

//            printf("Attaching   helo!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
//      MyThread* h = new MyThread();
//      h->start();

   }
   else if(dwReason == DLL_PROCESS_DETACH)
   {
      printf("helo!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
   }

//   installMartlet();
   return TRUE;
}


/*
BOOL APIENTRY DllMain( HANDLE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved )
{
    if( ul_reason_for_call == DLL_PROCESS_ATTACH )
    {
        // Increase reference count via LoadLibrary


//        char lib_name[MAX_PATH];
//        ::GetModuleFileName( hModule, lib_name, MAX_PATH );
//        ::LoadLibrary( lib_name );

        // Safely remove hook

//        ::UnhookWindowsHookEx( g_hHook );
    }    
    return TRUE;
}
*/

//#ifdef _MANAGED
//#pragma managed(pop)
//#endif



 __declspec(dllexport) void MyThread::run()
 {
    float fff = 9985;
    for (long i = 1 ; i< iterations; ++i ) {
     for (long j = 1 ; j< iterations; ++j ) {
         for (long k = 1 ; k< iterations; ++k ) {
             for (long m = 1 ; m< iterations; ++m ) {
    fff /= i+j/k*m;
    }}}}
    // QCoreApplication::instance()->exit(0);

//    QApplication::aboutQt();
    installMartlet();

    exec();
 }

class __declspec(dllexport) Hello
{
public:
    __declspec(dllexport) Hello()
    {
        qDebug("void MyThread::run()");
                MyThread* t = new MyThread;

//                MessageBoxA(NULL, "Hello from constructor", "Hi", MB_OK);

                float fff = 9985;
            for (long i = 1 ; i< iterations; ++i ) {
                for (long j = 1 ; j< iterations; ++j ) {
                    for (long k = 1 ; k< iterations; ++k ) {
                        for (long m = 1 ; m< iterations; ++m ) {
            fff *= i+j*k*m;
            }}}}
            t->start();

            qDebug("hello %f", fff);
           // QCoreApplication::instance()->exit(0);


//             installMartlet();
            }
};

static Hello h;



#else

bool QCoreApplication::event(QEvent *e)
{
//	printf(":)  %d \n", e->type());
    if (e->type() == QEvent::Quit) {
        quit();
        return true;
    }

    if (e->type() == QEvent::ApplicationActivate)
	{
        installMartlet();
	}
	return QObject::event(e);
}

#endif
