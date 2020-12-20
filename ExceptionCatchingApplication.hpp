#ifndef EXCEPTION_CATCHING_APPLICATION_HPP__
#define EXCEPTION_CATCHING_APPLICATION_HPP__

#include <QApplication>

#include "Logger.hpp"

class QObject;
class QEvent;

//
// We  can't  use the  GUI  after  QApplication::exit() is  called  so
// uncaught exceptions can get lost  on Windows systems where there is
// no console terminal, so here we override QApplication::notify() and
// wrap the  base class  call with  a try block  to catch  and display
// exceptions in a message box.
//
class ExceptionCatchingApplication
  : public QApplication
{
public:
  explicit ExceptionCatchingApplication (int& argc, char * * argv)
    : QApplication {argc, argv}
  {
  }
  bool notify (QObject * receiver, QEvent * e) override
  {
    try
      {
        return QApplication::notify (receiver, e);
      }
    catch (std::exception const& e)
      {
        LOG_FATAL (e.what ());
        throw;
      }
    catch (...)
      {
        LOG_FATAL ("Unexpected fatal error");
        throw;
      }
  }
};

#endif
