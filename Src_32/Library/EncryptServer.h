#ifndef	ENCRYPTSERVER_H
#define ENCRYPTSERVER_H


#include <string>


// 3个随机数
#define		aaa	0x8E
#define		bbb	0x39
#define		ccc	0x28

////////////////////////////////////////////////////////////////////////////////////////////////////
template <unsigned long key1, unsigned long key2>
class	EncryptServer
{
public:
	EncryptServer(){ /*Init();*/ }
public:
	void Init() { m_nPos1 = m_nPos2 = 0; m_cGlobalEncrypt.Init(); }
	void Encrypt(char * bufMsg, int nLen, int nBegin = 0, bool bMove = false);
	void Encrypt(string&  strMsg, int nLen, int nBegin = 0, bool bMove = false);
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
				// 生成 ABC
				int	a1, b1, c1, fst1;
				a1 = ((key1 >> 0) & 0xFF) ^ aaa;
				b1 = ((key1 >> 8) & 0xFF) ^ bbb;
				c1 = ((key1 >> 24) & 0xFF) ^ ccc;
				fst1 = (key1 >> 16) & 0xFF;

				int	a2, b2, c2, fst2;
				a2 = ((key2 >> 0) & 0xFF) ^ aaa;
				b2 = ((key2 >> 8) & 0xFF) ^ bbb;
				c2 = ((key2 >> 24) & 0xFF) ^ ccc;
				fst2 = (key2 >> 16) & 0xFF;

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

template <unsigned long key1, unsigned long key2>
inline void EncryptServer<key1, key2>::Encrypt(char * bufMsg, int nLen, int nBegin /*= 0*/, bool bMove /*= true*/)
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
			// 恢复指针
			m_nPos1 = nOldPos1;
			m_nPos2 = nOldPos2;
		}
	}
	catch (...){ /*LOGCATCH("Encrypt fail.");*/ }

	std::cout << "bufMsg[0]:" << bufMsg[0] << "bufMsg[1]:" << bufMsg[1] << endl;

}

template <unsigned long key1, unsigned long key2>
inline void EncryptServer<key1, key2>::Encrypt(string& strMsg, int nLen, int nBegin /*= 0*/, bool bMove /*= true*/)
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

		if (!bMove)
		{
			// 恢复指针
			m_nPos1 = nOldPos1;
			m_nPos2 = nOldPos2;
		}
	}
	catch (...){ /*LOGCATCH("Encrypt fail.");*/ }
}

#endif	// ENCRYPTSERVER_H
