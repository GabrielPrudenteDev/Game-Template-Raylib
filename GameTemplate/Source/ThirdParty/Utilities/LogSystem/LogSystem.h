#pragma once
#include "CoreMinimal.h"

// Marcio Freitas  YouTube -> gamedevlog
#define STRNOEXPAND(a) #a
#define STR(a) STRNOEXPAND(a)
#define LOGCONTEXT (__FILE__ " Line: " STR(__LINE__))

#define GT_LOG(ELogType, ELogVerbosity, ...) FLogSystem::CreateGTLog(ELogType, ELogVerbosity, LOGCONTEXT, __VA_ARGS__)
#define GT_FASTLOG(...) FLogSystem::CreateGTLog(ELogType::LogTemp, ELogVerbosity::LogWarning, nullptr, __VA_ARGS__)
#define GT_ASSERT(Pointer) if(Pointer == nullptr) {GT_LOG(ELogType::LogBoth, ELogVerbosity::LogError, typeid(Pointer).name(), " Assert Error!");}

enum class ELogType
{
	LogTemp,
	LogFile,
	LogBoth
};

enum class ELogVerbosity
{
	LogInfo = 7,
	LogWarning = 6,
	LogSuccess = 2,
	LogError = 4
};

class FLogOut
{
public:

	string& GetMessage() { return m_messager; }

	friend std::ostream& operator << (std::ostream& out, FLogOut LogOut)
	{
		out << LogOut.m_messager;
		return out;
	}

	void operator = (const char* In)
	{
		m_messager = In;
	}

	void operator = (string In)
	{
		m_messager = In;
	}

	void operator << (const char* In)
	{
		m_messager.append(In);
	}

	void operator << (string In)
	{
		m_messager += In;
	}

	void operator << (bool In)
	{
		m_messager += (In) ? "'True'" : "'False'";
	}

	void operator << (size_t In)
	{
		m_messager += std::to_string(In);
	}

	void operator << (int In)
	{
		m_messager += std::to_string(In);
	}

	void operator << (float In)
	{
		m_messager += FormatReal(std::to_string(In));
	}

	void operator << (double In)
	{
		m_messager += FormatReal(std::to_string(In));
	}

	void operator << (Vector2 In)
	{
		m_messager += "X:";
		m_messager += FormatReal(std::to_string(In.x));
		m_messager += " Y:";
		m_messager += FormatReal(std::to_string(In.y));
	}

	void operator << (Vector3 In)
	{
		m_messager += "X:";
		m_messager += FormatReal(std::to_string(In.x));
		m_messager += " Y:";
		m_messager += FormatReal(std::to_string(In.y));
		m_messager += " Z:";
		m_messager += FormatReal(std::to_string(In.z));
	}

private:

	string m_messager;

	string& FormatReal(string& Source)
	{
		size_t ptr = Source.find(".");
		Source.erase(ptr+=3, Source.back());
		return Source;
	}

};

class FLogSystem
{
public:

	FLogSystem();

	template<typename ... TMessage>
	static void CreateGTLog(ELogType LogType, ELogVerbosity LogVerbosity, const char* Context, TMessage ... Message);

private:

	static void PrintLog(ELogVerbosity LogVerbosity, FLogOut& LogMessages);

	static void WriteLog(FLogOut& LogOut);

	static string GetCurrentDate();

};

template<typename ... TMessage>
void FLogSystem::CreateGTLog(ELogType LogType, ELogVerbosity LogVerbosity,const char* Context, TMessage ... Message)
{
	FLogOut logOut;
	string filePath;
	bool bShippingMode = false;

#ifdef SHIPPING_MODE
	bShippingMode = true;
#endif // SHIPPINGMODE

	if (bShippingMode && LogVerbosity != ELogVerbosity::LogError) {
		return;
	}

	switch (LogVerbosity)
	{
	case ELogVerbosity::LogInfo:
		logOut = "GT_Log Info-> ";
		break;
	case ELogVerbosity::LogWarning:
		logOut = "GT_Log Warning-> ";
		break;
	case ELogVerbosity::LogSuccess:
		logOut = "GT_Log Success-> ";
		break;
	case ELogVerbosity::LogError:
		logOut = "GT_Log Error-> ";
		break;
	}

	// Log assembly
	if (Context == nullptr) {
		logOut = "GT_FastLog-> ";
	}
	else {
		filePath = Context;
		filePath.erase(0, filePath.find(GAME_NAME));
		logOut << "'";
		logOut << filePath;
		logOut << "'";
		logOut << " ";
	}

	((logOut << std::forward<TMessage>(Message)), ...);
	logOut << "\n";

	switch (LogType)
	{
	case ELogType::LogTemp: {
		FLogSystem::PrintLog(LogVerbosity, logOut);
	}
		break;
	case ELogType::LogFile: {
		FLogSystem::WriteLog(logOut);
	}
		break;
	case ELogType::LogBoth: {
		FLogSystem::PrintLog(LogVerbosity, logOut);
		FLogSystem::WriteLog(logOut);
	}
		break;
	}
};
