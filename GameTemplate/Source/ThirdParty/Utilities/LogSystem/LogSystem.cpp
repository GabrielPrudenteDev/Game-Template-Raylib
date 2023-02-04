#include "LogSystem.h"
#include "Platform/Platform.h"
#include <stdarg.h>
#include <fstream>
#include <ctime>

FLogSystem::FLogSystem()
{
	
}

void FLogSystem::PrintLog(ELogVerbosity LogVerbosity, FLogOut& LogMessages)
{
#ifdef DEBUG_MODE
	FPlatform::SetConsoleTextAttribute((int)LogVerbosity);
	std::cout << LogMessages;
	FPlatform::ResetConsoleDefaultAttributes();
#endif // DEBUGMODE
}

void FLogSystem::WriteLog(FLogOut& LogOut)
{
	std::ofstream logFile;
	string stringOut = GetCurrentDate();

	logFile.open("LogFile.txt", std::ofstream::app | std::ofstream::out);

	if (!logFile.is_open()) {
		return;
	}

	stringOut += LogOut.GetMessage();
	logFile << stringOut;

	logFile.flush();

	logFile.close();

}

string FLogSystem::GetCurrentDate()
{
	string currentDate;
	time_t timer;
	struct tm* horarioLocal;

	time(&timer); // Obtem informações de data e hora
	horarioLocal = localtime(&timer); // Converte a hora atual para a hora local

	int dia = horarioLocal->tm_mday;
	int mes = horarioLocal->tm_mon + 1;
	int ano = horarioLocal->tm_year + 1900;

	int hora = horarioLocal->tm_hour;
	int min = horarioLocal->tm_min;
	int sec = horarioLocal->tm_sec;

	currentDate = "Date-> ";
	currentDate += std::to_string(mes);
	currentDate += "/";
	currentDate += std::to_string(dia);
	currentDate += "/";
	currentDate += std::to_string(ano);

	currentDate += " ";
	currentDate += std::to_string(hora);
	currentDate += ":";
	currentDate += std::to_string(min);
	currentDate += ":";
	currentDate += std::to_string(sec);
	currentDate += " ";

	return currentDate;
}
