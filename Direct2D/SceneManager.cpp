#include "stdafx.h"
#include "SceneManager.h"
#include "Scene.h"

//�ε� �����带 ���� ������ �Լ�
DWORD CALLBACK LoadingThread(LPVOID prc)
{
	//��ü�� ���� init(�ʱ�ȭ) �Լ� ����
	SceneManager::_readyScene->Init();

	//�غ�� ���� ���� ������!
	SceneManager::_currentScene = SceneManager::_readyScene;

	//�ε��� ����
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
	//�ٲٷ��ϰ� �ϴ� ���� ã�´�
	mapSceneIter find = _mSceneList.find(sceneName);

	//�� ���� ã�� ��������
	if (find == _mSceneList.end()) return E_FAIL;

	//�̹� �� ���̶��?
	if (find->second == _currentScene) return S_OK;

	//����Ǵ� ���� �ʱ�ȭ �����ϸ�
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
	//�ٲٷ��ϰ� �ϴ� ���� ã�´�
	mapSceneIter find = _mSceneList.find(sceneName);

	//�� ���� ã�� ��������
	if (find == _mSceneList.end()) return E_FAIL;

	//�̹� �� ���̶��
	if (find->second == _currentScene) return S_OK;

	//�ٲٷ��ϴ� �ε����� ã�´�
	mapSceneIter findLoading = _mLoadingSceneList.find(loadingSceneName);

	//����Ǵ� ���� �ʱ�ȭ �����ϸ�
	if (SUCCEEDED(find->second->Init()))
	{
		//���� ���� �ִٸ� �������ش�
		if (_currentScene) _currentScene->Release();

		//�ε����� ���� �����ش�.
		_loadingScene = findLoading->second;

		//�ε��� ���� ���� ���� �� ���� �����Ѵ�.
		_readyScene = find->second;

		CloseHandle(CreateThread(NULL, 0, LoadingThread, NULL, 0, &_loadThreadID));

	}

	return E_FAIL;
}

