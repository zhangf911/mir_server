#include "IniFileReader.h"

IniFileReader::IniFileReader()
{
	Clear();
}

IniFileReader::~IniFileReader()
{
	Clear();
}

bool IniFileReader::LoadIniFile(const char* INfileName)
{
	Clear();

	ifstream infile(INfileName);
	if (!infile)
	{
		cout << "Open File '" << INfileName << "' Failed!" << endl;
		return false;
	}

	string curSecName = "";
	while (!infile.eof())
	{
		string line;
		getline(infile, line);

		// È¥³ý×¢ÊÍ
		int commentPos = line.find_first_of(';');
		if(commentPos != std::string::npos)
		{
			line = line.substr(0, commentPos);
		}

		// ¶Î½âÎö
		int secStartPos = line.find_first_of('[');
		if(secStartPos != std::string::npos)
		{
			string secName = "";
			int secEndPos = line.find_first_of(']');
			if(secEndPos != std::string::npos)
			{
				if (secEndPos > secStartPos + 1)
				{
					secName = line.substr(secStartPos + 1, secEndPos - secStartPos - 1);
				}

				if(secName.compare("") == 0)
				{
					continue;
				}
				else
				{
					curSecName = secName;
					continue;
				}
			}
		}

		int equPos = line.find_first_of('=');
		if (equPos != std::string::npos)
		{
			string key = line.substr(0, equPos);
			string value = line.substr(equPos + 1);

			int nonBlackPos = key.find_first_not_of(' ');
			if (nonBlackPos != std::string::npos)
			{
				key = key.substr(nonBlackPos);
			}
			nonBlackPos = key.find_first_of(' ');
			if (nonBlackPos != std::string::npos)
			{
				key = key.substr(0, nonBlackPos);
			}

			nonBlackPos = value.find_first_not_of(' ');
			if (nonBlackPos != std::string::npos)
			{
				value = value.substr(nonBlackPos);
			}
			nonBlackPos = value.find_first_of(' ');
			if (nonBlackPos != std::string::npos)
			{
				value = value.substr(0, nonBlackPos);
			}

			int returnPos = value.find_first_of('\r');
			if(returnPos != std::string::npos)
			{
				value = value.substr(0, returnPos);
			}

			auto it = m_iniDataMap.find(curSecName);
			if (it != m_iniDataMap.end())
			{
				it->second[key] = value;
			}
			else
			{
				map<string, string> keyValue;
				keyValue[key] = value;
				m_iniDataMap[curSecName] = keyValue;
			}
		}
	}

	return true;
}

void IniFileReader::Clear()
{
	m_iniDataMap.clear();
}

int IniFileReader::ReadInt(const string& INsectionName, const string& INkeyName)
{
	auto it = m_iniDataMap.find(INsectionName);
	if(it != m_iniDataMap.end())
	{
		auto keyIt = it->second.find(INkeyName);
		if(keyIt != it->second.end())
		{
			return atoi(keyIt->second.c_str());
		}
	}

	return 0;
}

double IniFileReader::ReadFloat(const string& INsectionName, const string& INkeyName)
{
	auto it = m_iniDataMap.find(INsectionName);
	if(it != m_iniDataMap.end())
	{
		auto keyIt = it->second.find(INkeyName);
		if(keyIt != it->second.end())
		{
			return atof(keyIt->second.c_str());
		}
	}

	return 0.0;
}

const string& IniFileReader::ReadString(const string& INsectionName, const string& INkeyName)
{
	auto it = m_iniDataMap.find(INsectionName);
	if(it != m_iniDataMap.end())
	{
		auto keyIt = it->second.find(INkeyName);
		if(keyIt != it->second.end())
		{
			return keyIt->second;
		}
	}

	return string("");
}

void IniFileReader::Print()
{
	for (auto it = m_iniDataMap.begin(); it != m_iniDataMap.end(); ++it)
	{
		cout << "[" << it->first << "]" << endl;
		for (auto keyIt = it->second.begin(); keyIt != it->second.end(); ++keyIt)
		{
			cout << keyIt->first << "=" << keyIt->second << endl;
		}
	}
}