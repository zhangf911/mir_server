#ifndef LIBRARY_RANDOMNUMBER_H
#define LIBRARY_RANDOMNUMBER_H

#include "Type.h"
#include <time.h>

namespace Library
{
	//用当前种子产生随机数 
	const unsigned long maxshort=65536L; 
	const unsigned long multiplier=1194211693L; 
	const unsigned long adder=12345L; 

	class RandomNumber 
	{ 
	private: 
		//存放种子的私有成员 
		unsigned long randSeed; 
	public: 
		//构造函数 。缺省值0表示系统自动给出种子 
		//产生0<=value中，用参数0调用时， 它反回一个无符号长整数（32位），表示从基准时间（1970.1.1.午夜或者1904.1.1午夜）至今已经过去的秒数。 任何情况下产生的数都是巨大的无符号型长整数.基于两者的选择，我们很理所当然地用一个选择语句来描述： 
		RandomNumber(unsigned long s = 0) 
		{ 
			if(s==0) 
				randSeed=static_cast<unsigned long>(time(0));//系统时间作种子 
			else 
				randSeed=s; //用户提供种子 
		} 

		//用常量来产生新的无符号的种子： randSeed=multiplier*randSeed+adder;
		unsigned short Random(unsigned long n) 
		{ 
			randSeed=multiplier*randSeed+adder; 
			return (unsigned short)((randSeed>>16)%n); 
		} 

		// 随机浮点值值0~1
		double FloatRandom(void) 
		{ 
			return Random(maxshort)/double(maxshort); 
		}

		// 获取随机范围值
		static unsigned int GetRandom(unsigned int INstart, unsigned int INend)
		{
			static RandomNumber randomGen;
			return static_cast<unsigned int>((INend - INstart + 1) * randomGen.FloatRandom()) + INstart;
		}
	};
};


#endif