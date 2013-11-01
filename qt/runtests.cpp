
#include <qdebug.h>
#include <qstring.h>
#include <qpair.h>
#include <qlist.h>
#include <QtGlobal>
#include <QTime>
#include <QCoreApplication>
#include "runtests.h"

using namespace libhfp;

void runTests(HfpSession *session) {
	Q_ASSERT(session);
	typedef QPair<QString, QString> Pair;
	QList< Pair> commands; /* Command and description pair */
	commands << Pair("Nonsense",	"(nonsense invalid command)");
	commands << Pair("AT+NONSENSE",	"(nonsense AT command)");
	commands << Pair("AT+COPS?", "Current Network Operator");
	commands << Pair("AT+CMEE", "Enable extended error code information");
/* These commands cause the phone to ask for user input and prevent the rest of the tests from running, so commenting out for now
	commands << Pair("AT+ATD450", "Dial given number");
	commands << Pair("AT+CHUP", "Terminate a call process");
	commands << Pair("AT+BLDN", "Redial last number");
	commands << Pair("AT+BVRA=1", "Enable voice activation");
*/
	commands << Pair("AT+CHUP", "Terminate a call process");
	commands << Pair("AT+CLIP=0", "Disable CLIP messages");
	commands << Pair("AT+CLIP=1", "Enable CLIP messages");
	commands << Pair("AT+NREC=0", "Disable echo canceling");
	commands << Pair("AT+NREC=1", "Enable echo canceling");
	commands << Pair("AT+BVRA=0", "Disable voice activation");
	commands << Pair("AT+BINP=1", "Request last dialed phone number");
	commands << Pair("AT+VTS=2", "Transmit DTMF code");
	commands << Pair("AT+VGS=30", "Set speaker volume");
	commands << Pair("AT+VTM=30", "Set microphone volume");
	commands << Pair("AT+BTRH?", "Put incoming call on hold");
	commands << Pair("AT+CNUM", "Get subscriber number");
	commands << Pair("AT+CIND=?", "Get indicator event reporting");
	commands << Pair("AT+CLCC", "Query call list");
	commands << Pair("AT+CHLD=2", "Put call on hold");
	commands << Pair("AT+CHLD=0", "Release all active calls");
	commands << Pair("AT+CHLD=10", "Release active call 0");
	//The following aren't part of HFP or HFS but are often implemented anyway

	commands << Pair("AT+CSCS=GSM", "Set alphabet to GSM");
/* This prevents the reset of the tests from working 
	commands << Pair("AT+CSCS=HEX", "Set alphabet to Hex");
*/
	commands << Pair("AT+CPBS=SM", "Set phonebook memory storage to simcard");
	commands << Pair("AT+CPBR=?", "Current phonebook memory storage");
	commands << Pair("AT+CPBS=MC", "Set phonebook memory storage to missed calls list");
	commands << Pair("AT+CPBR=1,99", "Read last 99 phone book entries from missed calls");
	commands << Pair("AT+CPBR=1,9", "Read last 9 phone book entries from missed calls");
	commands << Pair("AT+CPBR=1", "Read the last missed call");
	commands << Pair("AT+MPBR=1,99", "Read last 99 phone book entries using MPBR from missed calls");
	commands << Pair("AT+CPBS=ME", "Set phonebook memory storage to internal memory");
	commands << Pair("AT+CPBR=1,9", "Read first 9 phone book entries from internal memory");
	commands << Pair("AT+CPBR=1,99", "Read first 99 phone book entries from internal memory");
	commands << Pair("AT+CPBR=1", "Read first phone book entry from internal memory");
	commands << Pair("AT+MPBF=\"Saki\"", "Find 'Saki' in phonebook");
	commands << Pair("AT+MPBF=Saki", "Find 'Saki' in phonebook");
	commands << Pair("AT+MPBR=?", "Current phonebook memory storage using MPBR");
	commands << Pair("AT+XEVENT=DON", "State information about headset");

	//Even more GSM AT commands that I've found on the web that are sometimes implemented
	commands << Pair("AT+CPMS=?", "List locations that we can save SMS messages");
	commands << Pair("AT+CMGF=0", "Display SMS entries in binary");
	commands << Pair("AT+CMGF=1", "Display SMS entries in text");
	commands << Pair("AT+CMGL=?", "Return the option on which messages you wish to display");
	commands << Pair("AT+CMGL=\"ALL\"", "Display SMS messages from All sources");
	commands << Pair("AT#PMODE=1", "Set to pmode to retrieve text messages (Samsung only?)");
	commands << Pair("AT#PSRMR", "Parameters to obtain text messages (Samsung only?)");
	commands << Pair("AT&F", "Enable local echo");
	commands << Pair("ATi0", "Get manufacturer");
	commands << Pair("ATi1", "Get IMEI");
	commands << Pair("AT+FSCD=\"/\"", "Change to folder '/'");
	commands << Pair("AT+FSDI=\"/\"", "Get directory info on '/'");
	commands << Pair("AT+FSDL=\"/\"", "Get list of directories in '/'");
	commands << Pair("AT+FSFE=0,\"/\"", "Delete a file ('/')");
	commands << Pair("AT+GMI","Get manufacturer name");
	commands << Pair("AT+CGSN","Get IMEI");
	commands << Pair("AT+CGMR","OS revision");
	commands << Pair("AT+CGMM","Make and model of phone");
	commands << Pair("AT+CNUM","Get subscriber name/number");
	commands << Pair("AT+CLAC","Return list of supported AT commands");
	commands << Pair("AT+MODE=22","Prepare Motorola phone for OBEX commands");
	commands << Pair("AT+MODE=0","Return phone to simply AT comands");
	commands << Pair("AT#PBDYN?","Return this phone number");

	foreach(const Pair &command, commands) {
		qDebug() << "Sending " << command.first << "=" << command.second;
		HfpPendingCommand *cmd = session->CmdGenericAtCommand(command.first);
		if(!cmd) {
			qDebug() << "Failed to send command!";
		} else {
			delete cmd;
			//Wait for bluetooth to reply
			QTime dieTime= QTime::currentTime().addMSecs(100);
			while( QTime::currentTime() < dieTime )
				QCoreApplication::processEvents();
		}
	}
}
