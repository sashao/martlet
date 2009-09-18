#include "QInjector.h"

#include <QThread>
#include <QTimer>
#include <QDebug>
#include <QCoreApplication>

#include <windows.h>


QInjector::QInjector(void): QObject(0)
{
	proc = 0;
}

QInjector::~QInjector(void)
{
	delete proc;
}

	void QInjector::start(QString name)
	{
		if (!proc)
		{
			proc = new QProcess(this);
			proc->setObjectName("proc");
			QMetaObject::connectSlotsByName ( this );
			printf(" Win   starting \n" );
			proc->start(name);  
		}
	}




void QInjector::on_proc_started()
{
	QTimer::singleShot(500, this, SLOT(inject()));
}

void QInjector::inject()
{
	qDebug("QInjector::on_proc_started()");
	 _PROCESS_INFORMATION * pi = proc->pid();
// PROCESS_CREATE_THREAD|PROCESS_VM_WRITE|PROCESS_VM_READ|PROCESS_QUERY_INFORMATION|PROCESS_VM_OPERATION|THREAD_QUERY_INFORMATION
//	 HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, 
	 HANDLE hProcess = OpenProcess(PROCESS_CREATE_PROCESS|PROCESS_CREATE_THREAD|
						PROCESS_DUP_HANDLE|PROCESS_QUERY_INFORMATION|PROCESS_SET_INFORMATION|PROCESS_SET_QUOTA|PROCESS_VM_OPERATION|
						PROCESS_VM_READ|PROCESS_VM_WRITE, 
//	 HANDLE hProcess = OpenProcess(PROCESS_CREATE_THREAD|PROCESS_VM_WRITE|PROCESS_VM_READ|PROCESS_QUERY_INFORMATION|PROCESS_VM_OPERATION|THREAD_QUERY_INFORMATION, 
		 FALSE, pi->dwProcessId );

 	qDebug("QInjector::on_proc_started() %d ", pi->dwProcessId);


	if (hProcess == INVALID_HANDLE_VALUE)
	{
		qDebug("cannot open that pid\n");
		return ;
	}
	const char * dllFile = "S:\\Projects\\martlet\\bin\\QtLoad.dll";
	PVOID mem = VirtualAllocEx(hProcess, NULL, strlen(dllFile) + 1, MEM_COMMIT, PAGE_READWRITE);

	if (mem == NULL)
	{
		qDebug("can't allocate memory in that pid\n");
		CloseHandle(hProcess);
		return ;
	}

	if (WriteProcessMemory(hProcess, mem, (void*)dllFile, strlen(dllFile) + 1, NULL) == 0)
	{
		qDebug( "can't write to memory in that pid\n");
		VirtualFreeEx(hProcess, mem, strlen(dllFile) + 1, MEM_RELEASE);
		CloseHandle(hProcess);
		return ;
	}
	qDebug("CreateRemoteThread");
	HANDLE hThread = CreateRemoteThread(hProcess, NULL, 0, (LPTHREAD_START_ROUTINE) GetProcAddress(GetModuleHandle(L"KERNEL32.DLL"),"LoadLibraryA"), mem, 0, NULL);
	if (hThread == INVALID_HANDLE_VALUE)
	{
		qDebug("can't create a thread in that pid\n");
		VirtualFreeEx(hProcess, mem, strlen(dllFile) + 1, MEM_RELEASE);
		CloseHandle(hProcess);
		return ;
	}

	WaitForSingleObject(hThread, INFINITE);

	HANDLE hLibrary = NULL;
	if (!GetExitCodeThread(hThread, (LPDWORD)&hLibrary))
	{
		qDebug("can't get exit code for thread GetLastError() = %i.\n", GetLastError());
		CloseHandle(hThread);
		VirtualFreeEx(hProcess, mem, strlen(dllFile) + 1, MEM_RELEASE);
		CloseHandle(hProcess);
		return ;
	}

	CloseHandle(hThread);
	VirtualFreeEx(hProcess, mem, strlen(dllFile) + 1, MEM_RELEASE);

	if (hLibrary == NULL)
	{
		hThread = CreateRemoteThread(hProcess, NULL, 0, (LPTHREAD_START_ROUTINE) GetProcAddress(GetModuleHandle(L"KERNEL32.DLL"),"GetLastError"), 0, 0, NULL);
		if (hThread == INVALID_HANDLE_VALUE)
		{
			qDebug("LoadLibraryA returned NULL and can't get last error.\n");
			CloseHandle(hProcess);
			return ;
		}

		WaitForSingleObject(hThread, INFINITE);
		DWORD error;
		GetExitCodeThread(hThread, &error);

		CloseHandle(hThread);

		qDebug("LoadLibrary return NULL, GetLastError() is %i\n", error);
		CloseHandle(hProcess);
		return ;
	}

	CloseHandle(hProcess);

	qDebug("injected %08x\n", (DWORD)hLibrary);

}

void QInjector::on_proc_stateChanged ( QProcess::ProcessState newState )
{
}

void QInjector::on_proc_finished ( int exitCode, QProcess::ExitStatus exitStatus )
{
	QCoreApplication::exit();
}
