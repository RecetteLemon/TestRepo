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
	static Scene* _currentScene; //현재 씬
	static Scene* _loadingScene;	//로딩 씬
	static Scene* _readyScene;	//준비된 씬(갈아끼울)

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

	//로딩 쓰레드를 위한 쓰레드 함수
	friend DWORD CALLBACK LoadingThread(LPVOID prc);


};

