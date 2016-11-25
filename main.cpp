#include "view.h"
#include <QApplication>
#include <QTextCodec>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    #if defined(Q_OS_MAC64)
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF8"));//Mac环境下用UTF8编码
    #elif defined(Q_OS_WIN32)
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("GBK"));//Windows环境下使用GBK编码
    #endif

    return a.exec();
}
