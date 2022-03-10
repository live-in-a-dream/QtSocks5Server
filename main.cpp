#include <QCoreApplication>
#include "Socks5Start.h"
#include "QMap"
#include "param.h"
#include "QString"
#include "utils.h"


void outputMessage(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
  static QMutex mutex;
  mutex.lock();

  QString text;
  switch(type)
  {
  case QtDebugMsg:
      text = QString("Debug:");
      break;

  case QtWarningMsg:
      text = QString("Warning:");
      break;

  case QtCriticalMsg:
      text = QString("Critical:");
      break;

  case QtFatalMsg:
      text = QString("Fatal:");
  }

  QString context_info = QString("File:(%1) Line:(%2)").arg(QString(context.file)).arg(context.line);
  QString current_date_time = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss ddd");
  QString current_date = QString("(%1)").arg(current_date_time);
  QString message = QString("%1 %2 %3 %4").arg(text).arg(context_info).arg(msg).arg(current_date);

  QFile file("log.txt");
  file.open(QIODevice::WriteOnly | QIODevice::Append);
  QTextStream text_stream(&file);
  text_stream << message << "\r\n";
  file.flush();
  file.close();

  mutex.unlock();
}

int main(int argc, char *argv[])
{

    QCoreApplication a(argc, argv);

    //读取配置
    Utils::Instance()->ReadIni();

    Socks5Start* s = new Socks5Start;

    for(int i=0;i<argc;i++){
        QString p(argv[i]);
        if(p.contains("-port=") || p.contains("-p=")){
            Param::port = p.split("=")[1].toInt();
            qWarning()<<"port:"<<Param::port;
        }
        if(p.contains("-username=")||p.contains("-u=")){
            Param::user = p.split("=")[1];
            qWarning()<<"username:"<<Param::user;
        }
        if(p.contains("-passwd=")||p.contains("-pwd=")){
            Param::pass = p.split("=")[1];
            qWarning()<<"passwd:"<<Param::pass;
        }

        if(p.contains("-log=")){
            Param::isLog = p.split("=")[1] == "1"?true:false;
            qWarning()<<"isLog:"<<Param::isLog;
        }
    }

    if(Param::isLog){
        qInstallMessageHandler(outputMessage);
    }

    s->start(Param::port);

    return a.exec();
}
