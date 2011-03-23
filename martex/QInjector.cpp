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

#include "QInjector.h"

#include <QThread>
#include <QTimer>
#include <QDebug>
#include <QCoreApplication>
#include <QDir>
#include <QFile>
#include <QMessageBox>

QInjector::QInjector(void): QObject(0)
{
	proc = 0;
}

QInjector::~QInjector(void)
{
    if (proc) proc->close();
	delete proc;
}

QString QInjector::libraryPath()
{
#ifdef Q_OS_WIN
    const QString libraryExtension(".dll");
    const QString libraryVersion("");
#endif
#ifdef Q_OS_LINUX
    const QString libraryExtension(".so");
    const QString libraryVersion("");
#endif
    const QString libName("libQtLoad");
    const QString r = QDir::cleanPath(QDir::currentPath()+QDir::separator()+libName+libraryVersion+libraryExtension).replace("/", "\\");
    const QFileInfo fi(r);
    Q_ASSERT(fi.exists());
    return r;
}

bool QInjector::libraryFileExists()
{
    return QFile::exists (libraryPath());
}

void QInjector::start(QString name)
{

    if (!proc)
    {
        qDebug(Q_FUNC_INFO);
        proc = new QProcess(this);
        proc->setObjectName("proc");
        QMetaObject::connectSlotsByName ( this );
        QStringList env = QProcess::systemEnvironment();
        // Does nothing on Windows
        env << QString("LD_PRELOAD=%1").arg(libraryPath());
        proc->setEnvironment(env);
//        qDebug() << env;
//        qDebug("Starting !!!! ");
        proc->start(name);
//        QMessageBox::information(0, "PID", QString::number(proc->pid()));
#ifndef Q_OS_WIN
        proc->waitForFinished();
#endif
    }
}

void QInjector::on_proc_started()
{
	QTimer::singleShot(500, this, SLOT(inject()));
}

#ifdef Q_OS_WIN

#include <windows.h>

bool insertDll(DWORD procID, std::string dll)
{
    //Find the address of the LoadLibrary api, luckily for us, it is loaded in the same address for every process
    HMODULE hLocKernel32 = GetModuleHandle("Kernel32");
    FARPROC hLocLoadLibrary = GetProcAddress(hLocKernel32, "LoadLibraryA");

    //Adjust token privileges to open system processes
    HANDLE hToken;
    TOKEN_PRIVILEGES tkp;
    if(OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken))
    {
        LookupPrivilegeValue(NULL, SE_DEBUG_NAME, &tkp.Privileges[0].Luid);
        tkp.PrivilegeCount = 1;
        tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
        AdjustTokenPrivileges(hToken, 0, &tkp, sizeof(tkp), NULL, NULL);
    }

    //Open the process with all access
    HANDLE hProc = OpenProcess(PROCESS_ALL_ACCESS, FALSE, procID);
    QMessageBox::information(0, "injector", QString("!!%1!!   111 %2").arg(procID).arg((int)hProc));
    //Allocate memory to hold the path to the Dll File in the process's memory
    dll += '\0';
    LPVOID hRemoteMem = VirtualAllocEx(hProc, NULL, dll.size(), MEM_COMMIT, PAGE_READWRITE);

    //Write the path to the Dll File in the location just created
    DWORD numBytesWritten;
    WriteProcessMemory(hProc, hRemoteMem, dll.c_str(), dll.size(), &numBytesWritten);
    QMessageBox::information(0, "injector", QString("222 '%1'").arg(numBytesWritten));

    //Create a remote thread that starts begins at the LoadLibrary function and is passed are memory pointer
    HANDLE hRemoteThread = CreateRemoteThread(hProc, NULL, 0, (LPTHREAD_START_ROUTINE)hLocLoadLibrary, hRemoteMem, 0, NULL);
    QMessageBox::information(0, "injector", QString("333 '%1'").arg((int)hRemoteThread));

    //Wait for the thread to finish
    bool res = false;
    if (hRemoteThread)
    {
        QMessageBox::information(0, "injector", QString("444 '%1'").arg((int)hRemoteThread));

        WaitForSingleObject(hRemoteThread, INFINITE);
        res = true;
    }

    //Free the memory created on the other process
    VirtualFreeEx(hProc, hRemoteMem, dll.size(), MEM_RELEASE);
    QMessageBox::information(0, "injector", "555");

    //Release the handle to the other process
    CloseHandle(hProc);
    QMessageBox::information(0, "injector", "666");

    return res;
}


void QInjector::inject()
{

	qDebug("QInjector::on_proc_started()");
        QMessageBox::information(0, "injector", libraryPath());
        _PROCESS_INFORMATION * pi = proc->pid();
        insertDll(pi->dwProcessId, libraryPath().toStdString());
        proc->waitForFinished();
/*
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
*/
}
#endif

#ifdef Q_OS_LINUX

void QInjector::inject()
{
    
}

#endif


void QInjector::on_proc_stateChanged ( QProcess::ProcessState /*newState*/ )
{
}

void QInjector::on_proc_finished ( int /*exitCode*/, QProcess::ExitStatus /*exitStatus*/ )
{
	QCoreApplication::exit();
}
