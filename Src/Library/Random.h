#ifndef LIBRARY_RANDOMNUMBER_H
#define LIBRARY_RANDOMNUMBER_H

#include "Type.h"
#include <time.h>

namespace Library
{
	//�õ�ǰ���Ӳ�������� 
	const unsigned long maxshort=65536L; 
	const unsigned long multiplier=1194211693L; 
	const unsigned long adder=12345L; 

	class RandomNumber 
	{ 
	private: 
		//������ӵ�˽�г�Ա 
		unsigned long randSeed; 
	public: 
		//���캯�� ��ȱʡֵ0��ʾϵͳ�Զ��������� 
		//����0<=value�У��ò���0����ʱ�� ������һ���޷��ų�������32λ������ʾ�ӻ�׼ʱ�䣨1970.1.1.��ҹ����1904.1.1��ҹ�������Ѿ���ȥ�������� �κ�����²����������Ǿ޴���޷����ͳ�����.�������ߵ�ѡ�����Ǻ�������Ȼ����һ��ѡ������������� 
		RandomNumber(unsigned long s = 0) 
		{ 
			if(s==0) 
				randSeed=static_cast<unsigned long>(time(0));//ϵͳʱ�������� 
			else 
				randSeed=s; //�û��ṩ���� 
		} 

		//�ó����������µ��޷��ŵ����ӣ� randSeed=multiplier*randSeed+adder;
		unsigned short Random(unsigned long n) 
		{ 
			randSeed=multiplier*randSeed+adder; 
			return (unsigned short)((randSeed>>16)%n); 
		} 

		// �������ֵֵ0~1
		double FloatRandom(void) 
		{ 
			return Random(maxshort)/double(maxshort); 
		}

		// ��ȡ�����Χֵ
		static unsigned int GetRandom(unsigned int INstart, unsigned int INend)
		{
			static RandomNumber randomGen;
			return static_cast<unsigned int>((INend - INstart + 1) * randomGen.FloatRandom()) + INstart;
		}
	};
};


#endif