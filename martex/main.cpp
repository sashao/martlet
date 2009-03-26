#include <QtGui/QApplication>


       #include <stdio.h>
       #include <stdlib.h>
       #include <dlfcn.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    Widget w;
//    w.show();
	if (argc < 1) return -1;
	QString str(QObject::tr("translate me"));


//	void *handle;
//        double (*cosine)(double);
//        QCoreApplication * (*QCoreApplication_instance)();
//           char *error;

//           handle = dlopen("./libqtload/libQtLoad.so", RTLD_LAZY/* RTLD_NOW*/ | RTLD_GLOBAL);
/*           if (!handle) {
               fprintf(stderr, "%s\n", dlerror());
               exit(EXIT_FAILURE);
           }
*/
//           dlerror();    /* Clear any existing error */

           /* Writing: cosine = (double (*)(double)) dlsym(handle, "cos");
              would seem more natural, but the C99 standard leaves
              casting from "void *" to a function pointer undefined.
              The assignment used below is the POSIX.1-2003 (Technical
              Corrigendum 1) workaround; see the Rationale for the
              POSIX specification of dlsym(). */

           //*(void **) (&cosine) = dlsym(handle, "cos");
//           *(void **) (&QCoreApplication_instance) = dlsym(handle, "QCoreApplication::instance");
//           *(void **) (&QCoreApplication_instance) = dlsym(handle, "appInstance");

/*           if ((error = dlerror()) != NULL)  {
               fprintf(stderr, "%s\n", error);
               exit(EXIT_FAILURE);
           }

           printf("appInstance -01- %d\n", (*QCoreApplication_instance)());
           printf("appInstance -02- %d\n", QCoreApplication::instance());
           
           printf("Instance\n" );*/
//           execv("../Sphere/Sphere", NULL);

	    int ret;
            char *nargv[] = { (char *)0 };
            char *env[] = { "HOME=/home/oomel", "LOGNAME=oomel", "DISPLAY=:0.0", "LD_PRELOAD=./libqtload/libQtLoad.so", (char *)0 };
//            char *env[] = { "HOME=/usr/home", "LOGNAME=home", "DISPLAY=:0.0",  (char *)0 };
//            ret = execve ("../../qcontrol/Sphere/Sphere", cmd, env);
            ret = execve (argv[1], nargv, env);

//            printf("Instance\n" );

//           printf("cosine --- %f\n", (*cosine)(2.0));
//           printf("appInstance -1- %d\n", (*QCoreApplication_instance)());
//           printf("appInstance -2- %d\n", QCoreApplication::instance());
//           dlclose(handle);



    
//    QApplication::instance()->installEventFilter( new filter());
//    return a.exec();
}
