#pragma once
template <typename T>
class SingletonBase
{
protected:
	//싱글톤 인스턴스 선언
	static T* singleton;

	SingletonBase(void) {};
	~SingletonBase(void) {};

public:
	static T* GetSingleton(void);
	void ReleaseSingleton(void);
};

//싱글톤 초기화
template <typename T>
T* SingletonBase<T>::singleton = 0;

//싱글톤 값 가져온다
template <typename T>
T* SingletonBase<T>::GetSingleton(void)
{
	if (!singleton) singleton = new T;

	return singleton;
}

//싱글톤 메모리 해제
template<typename T>
void SingletonBase<T>::ReleaseSingleton(void)
{
	if (singleton)
	{
		delete singleton;

		singleton = 0;
	}
}