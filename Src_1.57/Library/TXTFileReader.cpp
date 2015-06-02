#include "TXTFileReader.h"

TXTFileReader::TXTFileReader()
{
	m_txtDataMap.clear();
}

TXTFileReader::~TXTFileReader()
{
	m_txtDataMap.clear();
}

bool TXTFileReader::LoadTXTFile(const char* INfileName)
{
	ifstream infile(INfileName);
	if (!infile)
	{
		cout << "Open File Failed!" << endl;
		return false;
	}

	while (!infile.eof())
	{
		string line;
		getline(infile, line);

		if(line.compare("") == 0)
		{
			continue;
		}
		if(line.compare("\r") == 0)
		{
			continue;
		}
		if(line.compare("\r\n") == 0)
		{
			continue;
		}

		vector<string> dataVector;
		stringstream ss(line);
		while (!ss.eof())
		{
			string data;
			getline(ss, data, '\t');
			if(data.compare("") == 0)
			{
				continue;
			}
			if(data.compare("\r") == 0)
			{
				continue;
			}
			if(data.compare("\r\n") == 0)
			{
				continue;
			}
			
			int returnPos = data.find_first_of('\r');
			if(returnPos != std::string::npos)
			{
				data = data.substr(0, returnPos);
			}

			dataVector.push_back(data);
		}
		if(dataVector.empty())
		{
			continue;
		}
		m_txtDataMap.push_back(dataVector);
	}

	return true;
}

int TXTFileReader::ReadInt(UInt32 INline, UInt32 INindex)
{
	INline = INline + EDataStartLine;
	if(INline >= EDataStartLine && INline < m_txtDataMap.size())
	{
		vector<string>& dataVector = m_txtDataMap[INline];
		if(INindex < dataVector.size())
		{
			if(m_txtDataMap[EDataTypeLine][INindex].compare("INT") == 0 ||
				m_txtDataMap[EDataTypeLine][INindex].compare("int") == 0)
			{
				return atoi(m_txtDataMap[INline][INindex].c_str());
			}
		}
	}

	throw 1;
}

double TXTFileReader::ReadFloat(UInt32 INline, UInt32 INindex)
{
	INline = INline + EDataStartLine;
	if(INline >= EDataStartLine && INline < m_txtDataMap.size())
	{
		vector<string>& dataVector = m_txtDataMap[INline];
		if(INindex < dataVector.size())
		{
			if(m_txtDataMap[EDataTypeLine][INindex].compare("FLOAT") == 0 || 
				m_txtDataMap[EDataTypeLine][INindex].compare("float") == 0)
			{
				return atof(m_txtDataMap[INline][INindex].c_str());
			}
		}
	}

	throw 1;
}

const string& TXTFileReader::ReadString(UInt32 INline, UInt32 INindex)
{
	INline = INline + EDataStartLine;
	if (INline >= EDataStartLine && INline < m_txtDataMap.size())
	{
		vector<string>& dataVector = m_txtDataMap[INline];
		if (INindex < dataVector.size())
		{
			if (m_txtDataMap[EDataTypeLine][INindex].compare("STRING") == 0 || 
				m_txtDataMap[EDataTypeLine][INindex].compare("string") == 0)
			{
				return m_txtDataMap[INline][INindex];
			}
		}
	}

	throw 1;
}

UInt32 TXTFileReader::GetRecordCount()
{
	return static_cast<UInt32>(m_txtDataMap.size()) - EDataStartLine;
}

UInt32 TXTFileReader::GetFieldCount()
{
	return static_cast<UInt32>(m_txtDataMap[0].size());
}

void TXTFileReader::Print()
{
	for (auto it = m_txtDataMap.begin(); it != m_txtDataMap.end(); ++it)
	{
		for (auto dataIt = it->begin(); dataIt != it->end(); ++dataIt)
		{
			cout << *dataIt << "\t";
		}
		cout << endl;
	}
}