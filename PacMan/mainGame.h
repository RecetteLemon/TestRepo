#pragma once
#include "gameNode.h"

//한 타일 규격 32 32X32
#define TILESIZE 32

//타일 갯수
#define TILEX 20
#define TILEY 20

//총 사이즈
#define TILESIZEX TILESIZE * TILEX
#define TILESIZEY TILESIZE * TILEY

//타일 셋 규격
#define SAMPLETILEX 17	
#define SAMPLETILEY 3

enum TERRAIN
{
	TR_CEMENT, TR_DESERT, TR_GRASS, TR_WATER, TR_END 
};

enum OBJECT
{
	OBJ_BLOCK1, OBJ_BLOCK3, OBJ_BLOCKS, 
	OBJ_FLAG1, OBJ_FLAG2,
	OBJ_TANK1, OBJ_TANK2, OBJ_NONE
};

//포지션(리스폰 위치 셋팅)
enum POS
{
	POS_FLAG1, POS_FLAG2, POS_TANK1, POS_TANK2
};

struct tagTile
{
	TERRAIN terrain;		//지형 이넘문
	OBJECT obj;				//오브젝트 이넘문
	RECT rc;				//렉트
	int terrainFrameX;		//지형 프레임 번호
	int terrainFrameY;
	int objFrameX;			//오브젝트 프레임 번호
	int objFrameY;
};

//타일셋
struct tagSampleTile
{
	RECT rcTile;
	int terrainFrameX;
	int terrainFrameY;
};

//현재 타일 정보
struct tagCurrentTile
{
	int x;
	int y;
};


class mainGame : public gameNode
{
private:
	HWND _btnSave;
	HWND _btnLoad;
	HWND _btnTerrainDraw;
	HWND _btnObjDraw;
	HWND _btnEraser;

	tagCurrentTile _currentTile;
	tagSampleTile _sampleTiles[SAMPLETILEX * SAMPLETILEY];
	tagTile _tiles[TILEX * TILEY];

	int _pos[2];

public:
	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	virtual void setup(void);
	virtual void setMap(void);
	virtual void save(void);
	virtual void load(void);

	TERRAIN terrainSelect(int frameX, int frameY);
	OBJECT objSelect(int frameX, int frameY);

	mainGame();
	~mainGame();
};

