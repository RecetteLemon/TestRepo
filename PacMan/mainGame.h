#pragma once
#include "gameNode.h"

//�� Ÿ�� �԰� 32 32X32
#define TILESIZE 32

//Ÿ�� ����
#define TILEX 20
#define TILEY 20

//�� ������
#define TILESIZEX TILESIZE * TILEX
#define TILESIZEY TILESIZE * TILEY

//Ÿ�� �� �԰�
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

//������(������ ��ġ ����)
enum POS
{
	POS_FLAG1, POS_FLAG2, POS_TANK1, POS_TANK2
};

struct tagTile
{
	TERRAIN terrain;		//���� �̳ѹ�
	OBJECT obj;				//������Ʈ �̳ѹ�
	RECT rc;				//��Ʈ
	int terrainFrameX;		//���� ������ ��ȣ
	int terrainFrameY;
	int objFrameX;			//������Ʈ ������ ��ȣ
	int objFrameY;
};

//Ÿ�ϼ�
struct tagSampleTile
{
	RECT rcTile;
	int terrainFrameX;
	int terrainFrameY;
};

//���� Ÿ�� ����
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

