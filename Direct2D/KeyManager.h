#pragma once
#include "SingletonBase.h"
#include <bitset>

//������ �� �ִ� Ű �� ���
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

	//Ű�� �ѹ� ������
	bool IsOnceKeyDown(int key);
	//Ű�� ������ ����
	bool IsOnceKeyUp(int key);
	//Ű�� ��� ������ ������
	bool IsStayKeyDown(int key);
	//��� Ű�� ���ٸ� ==capslock, numLockó�� ���������� �ҵ���
	//Lima ȭ����!!!
	bool IsToggleKey(int key);

	bitset<KEYMAX> GetKeyUp() { return _keyUp; }
	bitset<KEYMAX> GetKeyDown() { return _keyDown; }

	void SetKeyDown(int key, bool state) { _keyDown.set(key, state); }
	void SetKeyUp(int key, bool state) { _keyUp.set(key, state); }

	KeyManager();
	~KeyManager();
};

