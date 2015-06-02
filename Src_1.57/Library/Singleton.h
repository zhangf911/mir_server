#ifndef LIBRARY_SINGLETON_H
#define LIBRARY_SINGLETON_H

#include <mutex>

template <class DataType>
class Singleton
{
public:
	static DataType* Instance()
	{
		static DataType* _instance = NULL;
		static std::mutex lock;
		if(!_instance)
		{
			std::lock_guard<std::mutex> monitor(lock);
			if(!_instance)
			{
				_instance = new DataType;
			}
		}
		return _instance;
	};

	static void DestroyInstance()
	{
		DataType* _instance = Instance();
		if(_instance)
		{
			delete _instance;
			_instance = NULL;
		}
	}

protected:
	Singleton(){};

	~Singleton(){};
};


#endif