#pragma once

#include <vector>
#include "Graphics.h"
#include "TileMap.h"
#include "Surface.h"
#include "Mouse.h"
#include "Keyboard.h"
#include "Button.h"
#include <string>
#include "Codex.h"
#include "Anim.h"

class LevelEditor
{
private:
	enum class Tile2Char
	{
		Empty = int( '0' ),
		Wall = int( '1' ),
		Player = int( 'P' ),
		Enemy = int( 'E' ),
		Stairs = int( 'S' ),
		KeyWall = int( 'L' ),
		Key = int( 'K' ),
		SpikeWallLeft = int( 'T' ),
		SpikeWallRight = int( 'Y' ),
		DeathBall = int( 'B' )
	};
public:
	LevelEditor();

	void Update( const Mouse& ms,const Keyboard& kbd );
	void Draw( Graphics& gfx ) const;

	bool CheckReturning( const Mouse& ms );
private:
	void PutTile( int x,int y,Tile2Char c );

	void PublishLevel();
	void WriteToFile( const std::string& fileName ) const;
	std::string GetNewestFileName() const;

	Tile2Char GetTile( int x,int y ) const;
	const Surface* const Tile2Surf( Tile2Char tileType ) const;
	const Anim& Tile2Anim( Tile2Char toTest ) const;
	bool IsFlipped( Tile2Char test ) const;
	bool IsAnim( Tile2Char toTest ) const;
private:
	static int nInstances;

	std::vector<Tile2Char> tiles;
	static constexpr Vei2 nTiles = TileMap::nTiles;
	static constexpr Vei2 tileSize = TileMap::GetTileSize();
	Tile2Char brush = Tile2Char::Wall;
	Vei2 brushPos = { 0,0 };
	const Surface floorSpr = { "Images/Floor.bmp",40,40 };
	const Surface wallSpr = { "Images/Wall1.bmp",40,40 };
	const Surface playerSpr = { "Images/Player.bmp",32,32 };
	const Surface enemySpr = { { "Images/EggEnemyAnim.bmp",RectI{ { 0,0 },16,16 } },32,32 };
	const Surface stairsSpr = { "Images/Stairs.bmp",32,32 };
	const Surface keyWallSpr = { "Images/KeyWall.bmp",40,40 };
	const Surface keySpr = { "Images/Key.bmp",32,32 };
	const Surface deathBallSpr = { "Images/DeathBallAnim.bmp",32 * 4,8 * 4 };
	const Surface spikeWallSpr = { "Images/SpikeWallAnim.bmp",50 * 4,10 * 4 };

	static constexpr Vei2 menuCenter = { Graphics::GameScreenWidth +
		( Graphics::ScreenWidth - Graphics::GameScreenWidth ) / 2,0 };
	static constexpr int halfMenuWidth = menuCenter.x - Graphics::GameScreenWidth;
	static constexpr Vei2 qMenuW = { halfMenuWidth / 2,0 }; // quarter menu width

	Button backToMenu = { menuCenter + Vei2{ 0,32 },"Menu" };
	Button saveMap = { menuCenter + Vei2{ 0,64 * 8 },"Save" };

	static constexpr Vei2 menuTopLeft = { Graphics::GameScreenWidth,64 };
	static constexpr int bBSize = 48; // Big button size including padding
	static constexpr int sBSize = 40; // Small button size with padding
	static constexpr int mPadding = 16;
	static constexpr int start = 64 + 16;

	Anim spikeWallAnim;
	Anim deathBallAnim;

	ImageButton floor = { menuCenter - qMenuW + Vei2( 0,start + mPadding ),floorSpr };
	ImageButton wall = { menuCenter + qMenuW + Vei2( 0,start + mPadding ),wallSpr };
	ImageButton player = { menuCenter - qMenuW + Vei2( 0,start + mPadding * 2 + bBSize ),playerSpr };
	ImageButton enemy = { menuCenter + qMenuW + Vei2( 0,start + mPadding * 2 + bBSize ),enemySpr };
	ImageButton stairs = { menuCenter - qMenuW + Vei2( 0,start + mPadding * 3 + bBSize + sBSize ),stairsSpr };
	ImageButton keyWall = { menuCenter + qMenuW + Vei2( 0,start + mPadding * 3 + bBSize + sBSize ),keyWallSpr };
	ImageButton key = { menuCenter - qMenuW + Vei2( 0,start + mPadding * 4 + bBSize + sBSize * 2 ),keySpr };
	AnimButton deathBall = { menuCenter + qMenuW + Vei2( 0,start + mPadding * 4 + bBSize + sBSize * 2 ),deathBallAnim };
	AnimButton lSpikeWall = { menuCenter - qMenuW + Vei2( 0,start + mPadding * 5 + bBSize + sBSize * 3 ),spikeWallAnim };
	AnimButton rSpikeWall = { menuCenter + qMenuW + Vei2( 0,start + mPadding * 5 + bBSize + sBSize * 3 ),spikeWallAnim };
	// Man that was gross let's hope I come up with a better way to do this next time.

	static constexpr RectI wndRect = { { 0,0 },Graphics::GameScreenWidth,Graphics::GameScreenHeight };

	float fadeProgress = 0.0f;
	static constexpr float fadeSpeed = 0.0076f;
	const Font* const textFont = Codex<Font>::Retrieve( "Fonts/LuckyPixel24x36.bmp" );
};