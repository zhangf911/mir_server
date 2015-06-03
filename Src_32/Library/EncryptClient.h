#ifndef	ENCRYPTCLIENT_H
#define ENCRYPTCLIENT_H

using namespace std;
#include <stdlib.h>
#include <string>

template <unsigned char a1, unsigned char b1, unsigned char c1, unsigned char fst1,
	unsigned char a2, unsigned char b2, unsigned char c2, unsigned char fst2>
class	EncryptClient
{
public:
	EncryptClient(){ Init(); }
public:
	void Init() { m_nPos1 = m_nPos2 = 0; m_cGlobalEncrypt.Init(); }
	void Encrypt(char * bufMsg, int nLen, int nBegin = 0, bool bMove = false);
	void Encrypt(string& strMsg, int nLen, int nBegin = 0, bool bMove = false);
protected:
	int		m_nPos1;
	int		m_nPos2;
protected:
	class	EncryptCode
	{
	public:
		EncryptCode() { Init(); }
		void Init()
		{
			try{
				unsigned char	nCode = fst1;
				for (int i = 0; i < 256; i++)
				{
					m_bufEncrypt1[i] = nCode;
					nCode = (a1*nCode*nCode + b1*nCode + c1) % 256;
				}
				//assert(nCode == fst1);

				nCode = fst2;
				for (int i = 0; i < 256; i++)
				{
					m_bufEncrypt2[i] = nCode;
					nCode = (a2*nCode*nCode + b2*nCode + c2) % 256;
				}
				//assert(nCode == fst2);

			}
			catch (...){ /*LOGCATCH("Encrypt init fail.");*/ }
		}
		//	protected:
		unsigned char m_bufEncrypt1[256];
		unsigned char m_bufEncrypt2[256];
	}m_cGlobalEncrypt;		
};

template <unsigned char a1, unsigned char b1, unsigned char c1, unsigned char fst1,
	unsigned char a2, unsigned char b2, unsigned char c2, unsigned char fst2>
	inline void EncryptClient<a1, b1, c1, fst1, a2, b2, c2, fst2>::Encrypt(char * bufMsg, int nLen, int nBegin /*= 0*/, bool bMove /*= true*/)
{
		try{
			int		nOldPos1 = m_nPos1;
			int		nOldPos2 = m_nPos2;
			for (int i = 0; i < nLen; i++)
			{
				if (i < nBegin)
					continue;

				bufMsg[i] ^= m_cGlobalEncrypt.m_bufEncrypt1[m_nPos1];
				//bufMsg[i] ^= m_cGlobalEncrypt.m_bufEncrypt2[m_nPos2];
				if (++m_nPos1 >= 256)
				{
					m_nPos1 = 0;
					if (++m_nPos2 >= 256)
						m_nPos2 = 0;
				}
				//assert(m_nPos1 >= 0 && m_nPos1 < 256);
				//assert(m_nPos2 >= 0 && m_nPos2 < 256);
			}

			if (!bMove)
			{
				// »Ö¸´Ö¸Õë
				m_nPos1 = nOldPos1;
				m_nPos2 = nOldPos2;
			}
		}
		catch (...){ /*LOGCATCH("Encrypt fail."); */}
}

template <unsigned char a1, unsigned char b1, unsigned char c1, unsigned char fst1,
	unsigned char a2, unsigned char b2, unsigned char c2, unsigned char fst2>
	inline void EncryptClient<a1, b1, c1, fst1, a2, b2, c2, fst2>::Encrypt(string& strMsg, int nLen, int nBegin /*= 0*/, bool bMove /*= true*/)
{
		try{
			int		nOldPos1 = m_nPos1;
			int		nOldPos2 = m_nPos2;
			for (int i = 0; i < nLen; i++)
			{
				if (i < nBegin)
					continue;

				strMsg[i] ^= m_cGlobalEncrypt.m_bufEncrypt1[m_nPos1];
				//strMsg[i] ^= m_cGlobalEncrypt.m_bufEncrypt2[m_nPos2];
				if (++m_nPos1 >= 256)
				{
					m_nPos1 = 0;
					if (++m_nPos2 >= 256)
						m_nPos2 = 0;
				}
				//assert(m_nPos1 >= 0 && m_nPos1 < 256);
				//assert(m_nPos2 >= 0 && m_nPos2 < 256);
			}

			std::cout << "strmsg[0]:" << strMsg[0] << "strmsg[1]:" << strMsg[1] << endl;

			if (!bMove)
			{
				// »Ö¸´Ö¸Õë
				m_nPos1 = nOldPos1;
				m_nPos2 = nOldPos2;
			}
		}
		catch (...){ /*LOGCATCH("Encrypt fail.");*/ }
}


#endif	// ENCRYPTCLIENT_H
