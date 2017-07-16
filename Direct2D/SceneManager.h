#pragma once
#include "SingletonBase.h"
#include <map>

class Scene;



class SceneManager : public SingletonBase<SceneManager>
{
public:
	typedef map<string, Scene*> mapSceneList;
	typedef map<string, Scene*>::iterator mapSceneIter;

private:
	static Scene* _currentScene; //���� ��
	static Scene* _loadingScene;	//�ε� ��
	static Scene* _readyScene;	//�غ�� ��(���Ƴ���)

	mapSceneList _mSceneList;
	mapSceneList _mLoadingSceneList;

	DWORD _loadThreadID;

	
public:
	SceneManager();
	~SceneManager();

	HRESULT Init();
	void Release();
	void Update();
	void Render();

	Scene* AddScene(string sceneName, Scene* scene);
	Scene* FindScene(string sceneName);
	Scene* AddLoadingScene(string loadingSceneName, Scene* scene);

	HRESULT ChangeScene(string sceneName);
	HRESULT ChangeScene(string sceneName, string loadingSceneName);

	//�ε� �����带 ���� ������ �Լ�
	friend DWORD CALLBACK LoadingThread(LPVOID prc);


};

