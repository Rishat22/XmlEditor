#include <QDateTime>
#include <QDebug>
#include <iostream>
#include "COutputLogger.h"

COutputLoggerManager& COutputLoggerManager::GetInstance()
{
	static COutputLoggerManager loggerManager;
	return loggerManager;
}

void COutputLoggerManager::Print(const QString& strText)
{
	for(const auto& crOutputLogger: m_lOutputLoggers)
	{
		crOutputLogger->Print(strText);
	}
}

void COutputLoggerManager::Print(QtMsgType type, const QString& strText)
{
	for(const auto& crOutputLogger: m_lOutputLoggers)
	{
		crOutputLogger->Print(type, strText);
	}
}

void COutputLoggerManager::AddLogger(IOutputLogger* logger)
{
	m_lOutputLoggers.push_back(logger);
}

CPlainTextLogger::CPlainTextLogger(QPlainTextEdit* pPlainTextEdit)
{
	m_pPlainTextEdit = pPlainTextEdit;
}

void CPlainTextLogger::Print(const QString& strText)
{
	QMutexLocker locker(&m_Mutex);
	QDateTime curDateTime;
	QString resultMsg = curDateTime.currentDateTime().toString("dd.MM hh:mm:ss") + " ";
	resultMsg = resultMsg + strText;
	m_pPlainTextEdit->appendPlainText(resultMsg);
}

void CPlainTextLogger::Print(QtMsgType type, const QString& strText)
{
	QTextCharFormat tf = m_pPlainTextEdit->currentCharFormat();
	switch (type)
	{
		case QtInfoMsg:
		{
			tf.setForeground(Qt::darkGreen);
			break;
		}
		case QtDebugMsg:
		{
			tf.setForeground(Qt::darkGray);
			break;
		}
		case QtWarningMsg:
		{
			tf.setForeground(QColor(164, 164, 12));
			break;
		}
		case QtCriticalMsg:
		{
			tf.setForeground(Qt::red);
			break;
		}
		case QtFatalMsg:
		{
			tf.setForeground(Qt::red);
			break;
		}
		default:
			break;
	}
	m_pPlainTextEdit->setCurrentCharFormat(tf);

	Print(strText);
}

void CConsoleLogger::Print(const QString& strText)
{
	QMutexLocker locker(&m_Mutex);
	QDateTime curDateTime;
	QString resultMsg = curDateTime.currentDateTime().toString("dd.MM hh:mm:ss") + " ";
	resultMsg = resultMsg + strText;
	std::cout << resultMsg.toLocal8Bit().data() << std::endl;
}

void CConsoleLogger::Print(QtMsgType type, const QString& strText)
{
	QString coloredMessage = strText;
	switch (type)
	{
		case QtInfoMsg:
		{
			coloredMessage = QString("\033[0m \033[1;32m%1\033[0m").arg(strText);
			break;
		}
		case QtWarningMsg:
		{
			coloredMessage = QString("\033[0m \033[1;33m%1\033[0m").arg(strText);
			break;
		}
		case QtCriticalMsg:
		{
			coloredMessage = QString("\033[0m \033[1;31m%1\033[0m").arg(strText);
			break;
		}
		default:
			break;
	}
	Print(coloredMessage);
}
