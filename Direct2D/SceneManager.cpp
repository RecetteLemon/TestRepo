#include "stdafx.h"
#include "SceneManager.h"
#include "Scene.h"

//로딩 쓰레드를 위한 쓰레드 함수
DWORD CALLBACK LoadingThread(LPVOID prc)
{
	//교체될 씬의 init(초기화) 함수 실행
	SceneManager::_readyScene->Init();

	//준비된 씬을 현재 씬으로!
	SceneManager::_currentScene = SceneManager::_readyScene;

	//로딩씬 해제
	SceneManager::_loadingScene->Release();
	SceneManager::_loadingScene = NULL;
	SceneManager::_readyScene = NULL;

	return 0;
}

Scene* SceneManager::_currentScene = NULL;
Scene* SceneManager::_loadingScene = NULL;
Scene* SceneManager::_readyScene = NULL;

SceneManager::SceneManager()
{
}


SceneManager::~SceneManager()
{
}

HRESULT SceneManager::Init()
{
	_currentScene = NULL;
	_loadingScene = NULL;
	_readyScene = NULL;
	
	
	return S_OK;
}

void SceneManager::Release()
{
	mapSceneIter miSceneList = _mSceneList.begin();

	for (; miSceneList != _mSceneList.end();)
	{
		if (miSceneList->second != NULL)
		{
			if (miSceneList->second == _currentScene) miSceneList->second->Release();

			SAFE_DELETE(miSceneList->second);
			miSceneList = _mSceneList.erase(miSceneList);
		}
		else ++miSceneList;
	}

	_mSceneList.clear();
}

void SceneManager::Update()
{
	if (_currentScene) _currentScene->Update();
}

void SceneManager::Render()
{
	if (_currentScene) _currentScene->Render();
}

Scene* SceneManager::AddScene(string sceneName, Scene* scene)
{
	if (!scene) return NULL;

	Scene* scn = FindScene(sceneName);

	if (scn) return scn;

	_mSceneList.insert(make_pair(sceneName, scene));

	return scene;
}

Scene* SceneManager::AddLoadingScene(string loadingSceneName, Scene* scene)
{
	if (!scene) return NULL;

	_mSceneList.insert(make_pair(loadingSceneName, scene));

	return scene;
}

Scene* SceneManager::FindScene(string sceneName)
{
	mapSceneIter key = _mSceneList.find(sceneName);

	if (key != _mSceneList.end())
	{
		return key->second;
	}

	return NULL;
}

HRESULT SceneManager::ChangeScene(string sceneName)
{
	//바꾸려하고 하는 씬을 찾는다
	mapSceneIter find = _mSceneList.find(sceneName);

	//그 씬을 찾지 못했으면
	if (find == _mSceneList.end()) return E_FAIL;

	//이미 그 씬이라면?
	if (find->second == _currentScene) return S_OK;

	//변경되는 씬이 초기화 성공하면
	if (SUCCEEDED(find->second->Init()))
	{
		if (_currentScene) _currentScene->Release();
		_currentScene = find->second;

		return S_OK;
	}

	return E_FAIL;
}

HRESULT SceneManager::ChangeScene(string sceneName, string loadingSceneName)
{
	//바꾸려하고 하는 씬을 찾는다
	mapSceneIter find = _mSceneList.find(sceneName);

	//그 씬을 찾지 못했으면
	if (find == _mSceneList.end()) return E_FAIL;

	//이미 그 씬이라면
	if (find->second == _currentScene) return S_OK;

	//바꾸려하는 로딩씬을 찾는다
	mapSceneIter findLoading = _mLoadingSceneList.find(loadingSceneName);

	//변경되는 씬이 초기화 성공하면
	if (SUCCEEDED(find->second->Init()))
	{
		//기존 씬이 있다면 해제해준다
		if (_currentScene) _currentScene->Release();

		//로딩씬을 먼저 보여준다.
		_loadingScene = findLoading->second;

		//로딩이 끝난 다음 변경 될 씬을 셋팅한다.
		_readyScene = find->second;

		CloseHandle(CreateThread(NULL, 0, LoadingThread, NULL, 0, &_loadThreadID));

	}

	return E_FAIL;
}

