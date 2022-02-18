#ifndef IOUTPUTLOGGER_H
#define IOUTPUTLOGGER_H
#include <QObject>
#include <QPlainTextEdit>
#include <QMutex>
#include "StableDeclaration.h"

class IOutputLogger : public QObject
{
public:
    virtual void Print(const QString &) = 0;
    virtual void Print(QtMsgType type, const QString &) = 0;
protected:
    QMutex m_Mutex;
};

class COutputLoggerManager : public IOutputLogger
{
public:
    static COutputLoggerManager& GetInstance();
    void Print(const QString& strText) final;
    void Print(QtMsgType type, const QString& strText) final;
    void AddLogger(IOutputLogger* logger);
private:
    std::list<IOutputLogger*> m_lOutputLoggers;
};

class CPlainTextLogger : public IOutputLogger
{
public:
    CPlainTextLogger(QPlainTextEdit* pPlainTextEdit);

    void Print(const QString& strText) override;
    void Print(QtMsgType type, const QString& strText) override;
    void AddLogger(const IOutputLogger* logger);

private:
    QPlainTextEdit* m_pPlainTextEdit;
 };

class CConsoleLogger : public IOutputLogger
{
public:
    void Print(const QString& strText) override;
    void Print(QtMsgType type, const QString& strText) override;
};

#endif // IOUTPUTLOGGER_H
