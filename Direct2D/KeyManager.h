#pragma once
#include "SingletonBase.h"
#include <bitset>

//눌려질 수 있는 키 다 등록
#define KEYMAX 256

using namespace std;

class KeyManager : public SingletonBase<KeyManager>
{
private:
	bitset<KEYMAX> _keyUp;
	bitset<KEYMAX> _keyDown;

public:
	HRESULT Init(void);
	void Release(void);

	//키를 한번 누르면
	bool IsOnceKeyDown(int key);
	//키를 눌렀다 떼면
	bool IsOnceKeyUp(int key);
	//키를 계속 누르고 있으면
	bool IsStayKeyDown(int key);
	//토글 키를 쓴다면 ==capslock, numLock처럼 눌러놓으면 불들어옴
	//Lima 화이팅!!!
	bool IsToggleKey(int key);

	bitset<KEYMAX> GetKeyUp() { return _keyUp; }
	bitset<KEYMAX> GetKeyDown() { return _keyDown; }

	void SetKeyDown(int key, bool state) { _keyDown.set(key, state); }
	void SetKeyUp(int key, bool state) { _keyUp.set(key, state); }

	KeyManager();
	~KeyManager();
};

