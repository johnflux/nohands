
#include <qdebug.h>
#include <qstring.h>
#include <qpair.h>
#include <qlist.h>
#include <QtGlobal>
#include "runtests.h"

void runTests(libhfp::HfpSession *session) {
	Q_ASSERT(session);
	typedef QPair<QString, QString> Pair;
	QList< Pair> commands; /* Command and description pair */
	commands << Pair("Nonsense",	"(nonsense invalid command)");
	//		        commands << Pair("AT+NONSENSE",	"(nonsense AT command)");
	commands << Pair("AT+NREC=0", "Disable echo canceling");
	commands << Pair("AT+NREC=1", "Enable echo canceling");
	foreach(const Pair &command, commands) {
		qDebug() << "Sending " << command.first << "=" << command.second;
		delete session->CmdGenericAtCommand(command.first);
	}
}
