#include "ngpc.h"
#include "ngpc.h"
#include "library.h"
#include "robotron.h"
#include "script.h"

//Tiles
#include "Tiles/rtShot.c"
#include "Tiles/Sprites/rtRobotron.c"
#include "Tiles/rtBorder.c"
#include "Tiles/rtLogo.c"
#include "Tiles/NGPCLogo.c"
#include "Tiles/rtFont.c"
#include "Tiles/rtBlogLogo.c"

//Levels
#include "levels.c"


volatile u8 iFamilyCollisionLoop;

const unsigned char rtDirectionList[8]={DIR_NORTH, DIR_NORTH+DIR_EAST, DIR_EAST, DIR_EAST+DIR_SOUTH, DIR_SOUTH, DIR_SOUTH+DIR_WEST, DIR_WEST, DIR_WEST+DIR_NORTH};

void rtCreatePalette()
{
	//Create the system palettes
	SetPalette(SCR_1_PLANE, PAL_DEFAULT, 0, RGB(15,15,0),RGB(8,4,0),RGB(15,0,0));
	SetPalette(SCR_1_PLANE, PAL_BORDER, 0, RGB(15,0,0), RGB(8,12,0), RGB(0,0,15));
	SetPalette(SCR_1_PLANE, PAL_LOGO, 0, RGB(15,15,0), RGB(15,0,0), 0);
	SetPalette(SCR_1_PLANE, PAL_ATTRACTTEXT, 0, RGB(15,15,15), RGB(15,15,15), RGB(15,15,15));

	SetPalette(SCR_2_PLANE, PAL_DEFAULT, 0, RGB(4,2,0), RGB(8,4,0), RGB(15,7,0));
	SetPalette(SCR_2_PLANE, PAL_NGPCLOGO, 0, RGB(15,0,0), RGB(0,15,0), RGB(0,0,15));
	SetPalette(SCR_2_PLANE, PAL_NGPCLOGO+1, 0, RGB(0,15,0), RGB(8,12,0), RGB(0,0,15));
	SetPalette(SCR_2_PLANE, PAL_NGPCLOGO+2, 0, RGB(0,0,15), RGB(8,12,0), RGB(0,0,15));
	SetPalette(SCR_2_PLANE, PAL_NGPCLOGO+3, 0, RGB(15,15,0), RGB(8,12,0), RGB(0,0,15));
	SetPalette(SCR_2_PLANE, PAL_NGPCLOGO+4, 0, RGB(15,0,15), RGB(8,12,0), RGB(0,0,15));
	SetPalette(SCR_2_PLANE, PAL_NGPCLOGO+5, 0, RGB(0,15,15), RGB(8,12,0), RGB(0,0,15));
	SetPalette(SCR_2_PLANE, PAL_NGPCLOGO+6, 0, RGB(15,15,15), RGB(8,12,0), RGB(0,0,15));
	SetPalette(SPRITE_PLANE, PAL_DEFAULT, 0, RGB(15,15,0), RGB(0,8,15), RGB(0,0,15));
	SetPalette(SPRITE_PLANE, PAL_PLAYER, 0, RGB(15,0,0), RGB(0,15,0), RGB(15,15,15));
	SetPalette(SPRITE_PLANE, PAL_SHOT, 0, RGB(12,2,9), RGB(6,2,1), RGB(15,12,5));

	SetPalette(SPRITE_PLANE, PAL_ROBOTRON+TYPE_PLAYER, 0, RGB(15,0,0), RGB(0,0,15), RGB(15,15,15));
	SetPalette(SPRITE_PLANE, PAL_ROBOTRON+TYPE_MOM, 0, RGB(15,8,15), RGB(15,15,0), RGB(15,15,15));
	SetPalette(SPRITE_PLANE, PAL_ROBOTRON+TYPE_DAD, 0, RGB(0,0,15), RGB(15,15,0), RGB(15,8,0));
	SetPalette(SPRITE_PLANE, PAL_ROBOTRON+TYPE_MIKEY, 0, RGB(15,0,0), RGB(8,4,0), RGB(15,8,12));
	SetPalette(SPRITE_PLANE, PAL_ROBOTRON+TYPE_GRUNT, 0, RGB(15,0,0), RGB(0,15,0), RGB(15,15,15));
	SetPalette(SPRITE_PLANE, PAL_ROBOTRON+TYPE_ELECTRODE, 0, RGB(15,0,0), RGB(13,3,3), RGB(11,1,4));
	SetPalette(SPRITE_PLANE, PAL_ROBOTRON+TYPE_HULK, 0, RGB(15,0,0), RGB(0,15,0), RGB(15,15,15));
	SetPalette(SPRITE_PLANE, PAL_ROBOTRON+TYPE_SPHEROID, 0, RGB(15,0,0), RGB(0,0,0), RGB(0,0,0));
	SetPalette(SPRITE_PLANE, PAL_ROBOTRON+TYPE_ENFORCER, 0, RGB(0,0,15), RGB(15,15,15), RGB(15,0,0));
	SetPalette(SPRITE_PLANE, PAL_ROBOTRON+TYPE_BRAIN, 0, RGB(0,0,15), RGB(0,15,0), RGB(15,0,15));
	SetPalette(SPRITE_PLANE, PAL_ROBOTRON+TYPE_QUARK, 0, RGB(0,0,15), RGB(15,0,15), RGB(15,15,15));
	SetPalette(SPRITE_PLANE, PAL_ROBOTRON+TYPE_TANK, 0, RGB(15,0,0), RGB(0,15,0), RGB(0,0,15));
	SetPalette(SPRITE_PLANE, PAL_ROBOTRON+TYPE_ENFORCER_SHOT, 0, RGB(15,0,0), RGB(0,15,0), RGB(0,0,15));
	SetPalette(SPRITE_PLANE, PAL_ROBOTRON+TYPE_TANK_SHOT, 0, RGB(15,0,0), RGB(0,15,0), RGB(0,0,15));
	SetPalette(SPRITE_PLANE, PAL_ROBOTRON+TYPE_BRAIN_SHOT, 0, RGB(15,0,0), RGB(0,15,0), RGB(0,0,15));
	SetPalette(SPRITE_PLANE, PAL_ROBOTRON+TYPE_PROG, 0, RGB(15,15,15), RGB(15,15,15), RGB(15,15,15));
}

PLAYER rtCreatePlayer()
{
	u8 iLoop;
	PLAYER sprPlayer;

	//Setup the player sprite

	sprPlayer.Lives=3;
	sprPlayer.Score=0;
	sprPlayer.FamilyMultiplier=1;
	sprPlayer.Flags=0;
	sprPlayer.sprPlayer.xPosition=9216;
	sprPlayer.sprPlayer.yPosition=9216;
	sprPlayer.sprPlayer.Tile=TILEPLAYER;
	sprPlayer.sprPlayer.Animation=0;
	sprPlayer.sprPlayer.Direction=0;
	sprPlayer.Index=SPRITEPLAYER;
	sprPlayer.ShotDirection=DIR_SOUTH;
	sprPlayer.ShotTimer=0;

	return sprPlayer;
}

LEVEL rtCreateLevel(u8 LevelNumber)
{
	LEVEL levRobotron;
	u8 iTypeLoop;
	u8 iLoop;
	u8 iRobotronBound;

	//Create a level containing a set number of Grunts, Hulks, Brains, Tanks and The Last Human Family
	//Basically the level "definition" is the number of each type of robotron which are then spawned randomly

	iLoop=0;

	levRobotron.EnemyCount=0;
	iRobotronBound=0;
	//Enumerate through the various robtron types...
	for (iTypeLoop=0;iTypeLoop<=TYPE_TANK;iTypeLoop++)
	{
		//Some types count as "target" enemies.
		if (iTypeLoop>TYPE_HULK)
		{
			levRobotron.EnemyCount+=rtLevel[LevelNumber][iTypeLoop];
		}
		//All types count towards the overall count
		iRobotronBound+=rtLevel[LevelNumber][iTypeLoop];
		//Create our new enemy objects of the current type.
		// Should really make sure that they're not "too" close to the centre of the screen.
		for(;iLoop<iRobotronBound;iLoop++)
		{
			levRobotron.Robotron[iLoop].Index=SPRITEROBOTRON+iLoop;
			levRobotron.Robotron[iLoop].sprRobotron.xPosition=MIN_X+((u16)QRandom()<<6);
			levRobotron.Robotron[iLoop].sprRobotron.yPosition=MIN_Y+((u16)QRandom()<<6);
			levRobotron.Robotron[iLoop].sprRobotron.Tile=TILEROBOTRON+iLoop;
			levRobotron.Robotron[iLoop].sprRobotron.Animation=0;
			levRobotron.Robotron[iLoop].Type=iTypeLoop;
			levRobotron.Robotron[iLoop].sprRobotron.Direction=DIR_EAST;
			levRobotron.Robotron[iLoop].Flags=ROBOTRON_ACTIVE;
			levRobotron.Robotron[iLoop].DecisionTimer=0;
			levRobotron.Robotron[iLoop].Decision=0;
		}
	}
	for(;iLoop<MAX_ROBOTRON;iLoop++)
	{
		levRobotron.Robotron[iLoop].Index=SPRITEROBOTRON+iLoop;
		levRobotron.Robotron[iLoop].sprRobotron.xPosition=0;
		levRobotron.Robotron[iLoop].sprRobotron.yPosition=0;
		levRobotron.Robotron[iLoop].sprRobotron.Tile=TILEROBOTRON+iLoop;
		levRobotron.Robotron[iLoop].sprRobotron.Animation=0;
		levRobotron.Robotron[iLoop].Type=0;
		levRobotron.Robotron[iLoop].sprRobotron.Direction=DIR_NORTH;
		levRobotron.Robotron[iLoop].Flags=0;
		levRobotron.Robotron[iLoop].DecisionTimer=0;
		levRobotron.Robotron[iLoop].Decision=0;
	}

	return levRobotron;
}

PLAYER rtMovePlayer(PLAYER sprPlayer, GAME gmRobotron)
{
	u16 XPos;
   	u16 YPos;
	u8 iLoop;
	//Get input and move the current player sprite. Don't worry about collisions here.

	if ((JOYPAD & J_UP) && (sprPlayer.sprPlayer.yPosition>MIN_Y))
	{
		sprPlayer.sprPlayer.yPosition-=gmRobotron.PlayerSpeed;
		sprPlayer.sprPlayer.Direction=DIR_NORTH;
	}
	else if ((JOYPAD & J_DOWN) && (sprPlayer.sprPlayer.yPosition<MAX_Y))
	{
		sprPlayer.sprPlayer.yPosition+=gmRobotron.PlayerSpeed;
		sprPlayer.sprPlayer.Direction=DIR_SOUTH;
	}
	if ((JOYPAD & J_LEFT) && (sprPlayer.sprPlayer.xPosition>MIN_X))
	{
		sprPlayer.sprPlayer.xPosition-=gmRobotron.PlayerSpeed;
		sprPlayer.sprPlayer.Direction=DIR_WEST;
	}
	else if ((JOYPAD & J_RIGHT) && (sprPlayer.sprPlayer.xPosition<MAX_X))
	{
		sprPlayer.sprPlayer.xPosition+=gmRobotron.PlayerSpeed;
		sprPlayer.sprPlayer.Direction=DIR_EAST;
	}
	if (JOYPAD & J_A)
	{
		//Rotate shot direction anticlockwise
		if (!(sprPlayer.KeyState & J_A))
		{
			sprPlayer.ShotDirection++;
			if (sprPlayer.ShotDirection>7) sprPlayer.ShotDirection=0;
		}
	}
	if (JOYPAD & J_B)
	{
		//Rotate shot direction clockwise
		if (!(sprPlayer.KeyState & J_B))
		{
			sprPlayer.ShotDirection--;
			if (sprPlayer.ShotDirection>7) sprPlayer.ShotDirection=7;
		}
	}
	//Save the current keystate (this helps us to determine whether the user
	//has "tapped" a key or is holding it down. If the keystate hasn't changed
	//since the last iteration then it's classed as a hold.
	sprPlayer.KeyState=JOYPAD;

	//Auto-fire
	if (sprPlayer.ShotTimer==0)
	{
		//Create a new shot (if we can)
		PlaySound(SND_SHOOT);
		for (iLoop=0;iLoop<MAX_SHOT;iLoop++)
		{
			if (!(sprPlayer.Shot[iLoop].Flags&SHOT_ACTIVE))
			{
				sprPlayer.Shot[iLoop].sprShot.xPosition=sprPlayer.sprPlayer.xPosition;
				sprPlayer.Shot[iLoop].sprShot.yPosition=sprPlayer.sprPlayer.yPosition;
				sprPlayer.Shot[iLoop].Flags=SHOT_ACTIVE;
				sprPlayer.Shot[iLoop].sprShot.Direction=rtDirectionList[sprPlayer.ShotDirection];
				CopySpriteTile((u16*)rtShot, sprPlayer.Shot[iLoop].sprShot.Tile, sprPlayer.Shot[iLoop].sprShot.Direction);
				iLoop=MAX_SHOT;
			}
		}
	}

	//Move our shots
	for (iLoop=0;iLoop<=MAX_SHOT;iLoop++)
	{
		if (sprPlayer.Shot[iLoop].Flags&SHOT_ACTIVE)
		{
			if (sprPlayer.Shot[iLoop].sprShot.Direction & DIR_NORTH)
			{
				if (sprPlayer.Shot[iLoop].sprShot.yPosition>MIN_Y)
				{
					sprPlayer.Shot[iLoop].sprShot.yPosition-=gmRobotron.ShotSpeed;
				}
				else
				{
					sprPlayer.Shot[iLoop].Flags=SHOT_INACTIVE;
					sprPlayer.Shot[iLoop].sprShot.Direction=0;
					CopySpriteTile((u16*)rtShot, sprPlayer.Shot[iLoop].sprShot.Tile, sprPlayer.Shot[iLoop].sprShot.Direction);
				}
			}
			if (sprPlayer.Shot[iLoop].sprShot.Direction & DIR_EAST)
			{
				if (sprPlayer.Shot[iLoop].sprShot.xPosition<MAX_X)
				{
					sprPlayer.Shot[iLoop].sprShot.xPosition+=gmRobotron.ShotSpeed;
				}
				else
				{
					sprPlayer.Shot[iLoop].Flags=SHOT_INACTIVE;
					sprPlayer.Shot[iLoop].sprShot.Direction=0;
					CopySpriteTile((u16*)rtShot, sprPlayer.Shot[iLoop].sprShot.Tile, sprPlayer.Shot[iLoop].sprShot.Direction);
				}
			}
			if (sprPlayer.Shot[iLoop].sprShot.Direction & DIR_SOUTH)
			{
				if (sprPlayer.Shot[iLoop].sprShot.yPosition<MAX_Y)
				{
					sprPlayer.Shot[iLoop].sprShot.yPosition+=gmRobotron.ShotSpeed;
				}
				else
				{
					sprPlayer.Shot[iLoop].Flags=SHOT_INACTIVE;
					sprPlayer.Shot[iLoop].sprShot.Direction=0;
					CopySpriteTile((u16*)rtShot, sprPlayer.Shot[iLoop].sprShot.Tile, sprPlayer.Shot[iLoop].sprShot.Direction);
				}
			}
			if (sprPlayer.Shot[iLoop].sprShot.Direction & DIR_WEST)
			{
				if (sprPlayer.Shot[iLoop].sprShot.xPosition>MIN_X)
				{
					sprPlayer.Shot[iLoop].sprShot.xPosition-=gmRobotron.ShotSpeed;
				}
				else
				{
					sprPlayer.Shot[iLoop].Flags=SHOT_INACTIVE;
					sprPlayer.Shot[iLoop].sprShot.Direction=0;
					CopySpriteTile((u16*)rtShot, sprPlayer.Shot[iLoop].sprShot.Tile, sprPlayer.Shot[iLoop].sprShot.Direction);
				}
			}
			SetSpritePosition(SPRITESHOT+iLoop, sprPlayer.Shot[iLoop].sprShot.xPosition>>7, sprPlayer.Shot[iLoop].sprShot.yPosition>>7);
		}
	}

	sprPlayer.ShotTimer+=gmRobotron.ShotFrequency;
	sprPlayer.sprPlayer.Animation^=1;

	CopySpriteTile((u16*)rtRobotron, sprPlayer.sprPlayer.Tile,(sprPlayer.sprPlayer.Direction<<1)+sprPlayer.sprPlayer.Animation);
	SetSpritePosition(SPRITEPLAYER, sprPlayer.sprPlayer.xPosition>>7, sprPlayer.sprPlayer.yPosition>>7);

	return sprPlayer;
}

GAME rtAttractMode(GAME gmPrevious, HIGHSCOREENTRY hstRobotron[], u16 StartFrame, u16 LastScore)
{
	GAME gameReturn;

	u8 iLoopX;
	u8 iLoopY;
	u8 iLoopBorder;
	u8 iLoopSprite;
	u8 iPalette;
	u8 iBorderPalette;
	u8 iBorderPaletteStart;
	u8 iBorderWhiteLogo;
	u8 iBorderID;
	u8 iAttractMode;
	u16 iAttractFrame;
	u8 iAttractTimer;
	ROBOTRON rtAttractSprite[11];

	const u8 BorderPattern[2][34][3]={
		{{SCR_2_PLANE,0,0},{SCR_2_PLANE,2,0},{SCR_2_PLANE,4,0},{SCR_2_PLANE,6,0},{SCR_2_PLANE,8,0},{SCR_2_PLANE,10,0},{SCR_2_PLANE,12,0},{SCR_2_PLANE,14,0},{SCR_2_PLANE,16,0},{SCR_2_PLANE,18,0},{SCR_2_PLANE,18,2},{SCR_2_PLANE,18,4},{SCR_2_PLANE,18,6},{SCR_2_PLANE,18,8},{SCR_2_PLANE,18,10},{SCR_2_PLANE,18,12},{SCR_2_PLANE,18,14},{SCR_2_PLANE,18,16},{SCR_2_PLANE,16,16},{SCR_2_PLANE,14,16},{SCR_2_PLANE,12,16},{SCR_2_PLANE,10,16},{SCR_2_PLANE,8,16},{SCR_2_PLANE,6,16},{SCR_2_PLANE,4,16},{SCR_2_PLANE,2,16},{SCR_2_PLANE,0,16},{SCR_2_PLANE,0,14},{SCR_2_PLANE,0,12},{SCR_2_PLANE,0,10},{SCR_2_PLANE,0,8},{SCR_2_PLANE,0,6},{SCR_2_PLANE,0,4},{SCR_2_PLANE,0,2}},
		{{SCR_2_PLANE,1,0},{SCR_2_PLANE,3,0},{SCR_2_PLANE,5,0},{SCR_2_PLANE,7,0},{SCR_2_PLANE,9,0},{SCR_2_PLANE,11,0},{SCR_2_PLANE,13,0},{SCR_2_PLANE,15,0},{SCR_2_PLANE,17,0},{SCR_2_PLANE,18,1},{SCR_2_PLANE,18,3},{SCR_2_PLANE,18,5},{SCR_2_PLANE,18,7},{SCR_2_PLANE,18,9},{SCR_2_PLANE,18,11},{SCR_2_PLANE,18,13},{SCR_2_PLANE,18,15},{SCR_2_PLANE,17,16},{SCR_2_PLANE,15,16},{SCR_2_PLANE,13,16},{SCR_2_PLANE,11,16},{SCR_2_PLANE,9,16},{SCR_2_PLANE,7,16},{SCR_2_PLANE,5,16},{SCR_2_PLANE,3,16},{SCR_2_PLANE,1,16},{SCR_2_PLANE,0,15},{SCR_2_PLANE,0,13},{SCR_2_PLANE,0,11},{SCR_2_PLANE,0,9},{SCR_2_PLANE,0,7},{SCR_2_PLANE,0,5},{SCR_2_PLANE,0,3},{SCR_2_PLANE,0,1}}
	};

	gameReturn=gmPrevious;
	// Comment this line out to allow "continuous" progression through the levels. Handy for testing.
	gameReturn.Level=0;

	//Draw logo's and allow the user to start a game/select difficulty etc

	ClearScreen(SCR_1_PLANE);
	ClearScreen(SCR_2_PLANE);
	ClearSprites();
	InstallTileSetAt(rtLogo, sizeof(rtLogo)/2, LogoTileBase);
	InstallTileSetAt(NGPCLogo, sizeof(NGPCLogo)/2, NGPCLogoTileBase);
	InstallTileSetAt(rtBlogLogo, sizeof(rtBlogLogo)/2, BlogLogoTileBase);

	iBorderID=0;

	iPalette=0;
	iBorderPaletteStart=5;

	iBorderPalette=0;
	iBorderWhiteLogo=33;

	// Set up our Attract Mode
	rtAttractSprite[0].Index=SPRITEROBOTRON+0;
	rtAttractSprite[0].sprRobotron.xPosition=ATTRACT_X;
	rtAttractSprite[0].sprRobotron.yPosition=ATTRACT_Y;
	rtAttractSprite[0].sprRobotron.Tile=TILEATTRACT+0;
	rtAttractSprite[0].sprRobotron.Animation=0;
	rtAttractSprite[0].Type=TYPE_GRUNT;
	rtAttractSprite[0].sprRobotron.Direction=DIR_EAST;
	rtAttractSprite[0].Flags=ROBOTRON_DEAD;
	rtAttractSprite[0].DecisionTimer=90;
	rtAttractSprite[0].Decision=120;
	rtAttractSprite[1].Index=SPRITEROBOTRON+1;
	rtAttractSprite[1].sprRobotron.xPosition=ATTRACT_X;
	rtAttractSprite[1].sprRobotron.yPosition=ATTRACT_Y;
	rtAttractSprite[1].sprRobotron.Tile=TILEATTRACT+1;
	rtAttractSprite[1].sprRobotron.Animation=1;
	rtAttractSprite[1].Type=TYPE_HULK;
	rtAttractSprite[1].sprRobotron.Direction=DIR_EAST;
	rtAttractSprite[1].Flags=ROBOTRON_DEAD;
	rtAttractSprite[1].DecisionTimer=100;
	rtAttractSprite[1].Decision=130;
	rtAttractSprite[2].Index=SPRITEROBOTRON+2;
	rtAttractSprite[2].sprRobotron.xPosition=ATTRACT_X;
	rtAttractSprite[2].sprRobotron.yPosition=ATTRACT_Y;
	rtAttractSprite[2].sprRobotron.Tile=TILEATTRACT+2;
	rtAttractSprite[2].sprRobotron.Animation=1;
	rtAttractSprite[2].Type=TYPE_SPHEROID;
	rtAttractSprite[2].sprRobotron.Direction=DIR_EAST;
	rtAttractSprite[2].Flags=ROBOTRON_DEAD;
	rtAttractSprite[2].DecisionTimer=110;
	rtAttractSprite[2].Decision=140;
	rtAttractSprite[3].Index=SPRITEROBOTRON+3;
	rtAttractSprite[3].sprRobotron.xPosition=ATTRACT_X;
	rtAttractSprite[3].sprRobotron.yPosition=ATTRACT_Y;
	rtAttractSprite[3].sprRobotron.Tile=TILEATTRACT+3;
	rtAttractSprite[3].sprRobotron.Animation=1;
	rtAttractSprite[3].Type=TYPE_ENFORCER;
	rtAttractSprite[3].sprRobotron.Direction=DIR_EAST;
	rtAttractSprite[3].Flags=ROBOTRON_DEAD;
	rtAttractSprite[3].DecisionTimer=120;
	rtAttractSprite[3].Decision=150;
	rtAttractSprite[4].Index=SPRITEROBOTRON+4;
	rtAttractSprite[4].sprRobotron.xPosition=ATTRACT_X;
	rtAttractSprite[4].sprRobotron.yPosition=ATTRACT_Y;
	rtAttractSprite[4].sprRobotron.Tile=TILEATTRACT+4;
	rtAttractSprite[4].sprRobotron.Animation=1;
	rtAttractSprite[4].Type=TYPE_BRAIN;
	rtAttractSprite[4].sprRobotron.Direction=DIR_EAST;
	rtAttractSprite[4].Flags=ROBOTRON_DEAD;
	rtAttractSprite[4].DecisionTimer=130;
	rtAttractSprite[4].Decision=160;
	rtAttractSprite[5].Index=SPRITEROBOTRON+5;
	rtAttractSprite[5].sprRobotron.xPosition=ATTRACT_X;
	rtAttractSprite[5].sprRobotron.yPosition=ATTRACT_Y;
	rtAttractSprite[5].sprRobotron.Tile=TILEATTRACT+5;
	rtAttractSprite[5].sprRobotron.Animation=1;
	rtAttractSprite[5].Type=TYPE_QUARK;
	rtAttractSprite[5].sprRobotron.Direction=DIR_EAST;
	rtAttractSprite[5].Flags=ROBOTRON_DEAD;
	rtAttractSprite[5].DecisionTimer=140;
	rtAttractSprite[5].Decision=170;
	rtAttractSprite[6].Index=SPRITEROBOTRON+6;
	rtAttractSprite[6].sprRobotron.xPosition=ATTRACT_X;
	rtAttractSprite[6].sprRobotron.yPosition=ATTRACT_Y;
	rtAttractSprite[6].sprRobotron.Tile=TILEATTRACT+6;
	rtAttractSprite[6].sprRobotron.Animation=1;
	rtAttractSprite[6].Type=TYPE_TANK;
	rtAttractSprite[6].sprRobotron.Direction=DIR_EAST;
	rtAttractSprite[6].Flags=ROBOTRON_DEAD;
	rtAttractSprite[6].DecisionTimer=150;
	rtAttractSprite[6].Decision=180;

	iAttractMode=0;
	iAttractFrame=StartFrame;
	iAttractTimer=0;

	while (!(JOYPAD & J_A))
	{

		// Switch between the logo screen, game rules (SAVE THE LAST HUMAN FAMILY) and high score table.
		// Basically, use iAttractFrame to display different tableaus
		switch (iAttractFrame)
		{
			case 0:
				// Draw the credits lines...
				//Draw the logo
				for(iLoopX=0;iLoopX<=17;iLoopX++)
				{
					for(iLoopY=0;iLoopY<=7;iLoopY++)
					{
						PutTile(SCR_1_PLANE, PAL_LOGO, iLoopX+1, iLoopY+3, LogoTileBase+((u16)iLoopY*18)+(u16)iLoopX);
					}
				}
				PrintString(SCR_1_PLANE, PAL_DEFAULT, 2, 11, "  PRESENTED BY  ");
				PrintString(SCR_1_PLANE, PAL_DEFAULT, 2, 12, "                ");
				for(iLoopX=0;iLoopX<=11;iLoopX++)
				{
					PutTile(SCR_1_PLANE, PAL_LOGO, 4+iLoopX, 13, BlogLogoTileBase+iLoopX);
				}
				PrintString(SCR_1_PLANE, PAL_DEFAULT, 2, 14, "                ");
				break;
			case 90:
				//Introduce the Robotrons
				PrintString(SCR_1_PLANE, PAL_DEFAULT, 2, 11, "                ");
				PrintString(SCR_1_PLANE, PAL_DEFAULT, 2, 12, "                ");
				PrintString(SCR_1_PLANE, PAL_DEFAULT, 2, 13, "BEWARE THE EVIL ");
				PrintString(SCR_1_PLANE, PAL_DEFAULT, 2, 14, "   ROBOTRONS    ");

				break;
			case 300:
				//Introduce the Player
				PrintString(SCR_1_PLANE, PAL_DEFAULT, 2, 11, "                ");
				PrintString(SCR_1_PLANE, PAL_DEFAULT, 2, 12, "                ");
				PrintString(SCR_1_PLANE, PAL_DEFAULT, 2, 13, "   ARE YOU A    ");
				PrintString(SCR_1_PLANE, PAL_DEFAULT, 2, 14, " ROBOTRON HERO? ");
				break;
			case 400:
				//Introduce the Last Human Family
				PrintString(SCR_1_PLANE, PAL_DEFAULT, 2, 11, "                ");
				PrintString(SCR_1_PLANE, PAL_DEFAULT, 2, 12, "                ");
				PrintString(SCR_1_PLANE, PAL_DEFAULT, 2, 13, " SAVE THE LAST  ");
				PrintString(SCR_1_PLANE, PAL_DEFAULT, 2, 14, " HUMAN  FAMILY  ");
				break;
			case 600:
				//Clear the logo area
				for(iLoopX=0;iLoopX<=17;iLoopX++)
				{
					for(iLoopY=0;iLoopY<=7;iLoopY++)
					{
						PutTile(SCR_1_PLANE, PAL_LOGO, iLoopX+1, iLoopY+3, 32);
					}
				}

				//Show the high score table
				PrintString(SCR_1_PLANE, PAL_DEFAULT, 2, 11, "                ");
				PrintString(SCR_1_PLANE, PAL_DEFAULT, 2, 12, "                ");
				PrintString(SCR_1_PLANE, PAL_DEFAULT, 2, 13, "   YOUR SCORE   ");
				PrintString(SCR_1_PLANE, PAL_DEFAULT, 2, 14, "    99999999    ");
				PrintDecimal(SCR_1_PLANE, PAL_DEFAULT, 6, 14, LastScore, 8);
				// Can fit into two columns if we put the score under the initials...
				for(iLoopX=0;iLoopX<2;iLoopX++)
				{
						for(iLoopY=0;iLoopY<5;iLoopY++)
						{
							PrintString(SCR_1_PLANE, PAL_ATTRACTTEXT, 2  + (iLoopX*8),3 + iLoopY*2, hstRobotron[iLoopY*2+iLoopX].Initials);
							PrintDecimal(SCR_1_PLANE, PAL_LOGO, 2  + (iLoopX*8),4 + iLoopY*2, hstRobotron[iLoopY*2+iLoopX].Score, 7);
						}
				}
		}

		for(iLoopSprite=0;iLoopSprite<11;iLoopSprite++)
		{
			// Create the sprite on frame .DecisionTimer
			if (rtAttractSprite[iLoopSprite].DecisionTimer==iAttractFrame)
			{
				// Create the sprite
				// These appear to be being created on one of the scroll planes?
				// Are my tile bases overlapping?
				// Yes. Exactly that - the Robotron Logo was running @144 chars and starting at position 128...
				rtAttractSprite[iLoopSprite].Flags=ROBOTRON_ACTIVE;
				rtAttractSprite[iLoopSprite].sprRobotron.xPosition=ATTRACT_X;
				rtAttractSprite[iLoopSprite].sprRobotron.yPosition=ATTRACT_Y;
				CopySpriteTile((u16*)rtRobotron, rtAttractSprite[iLoopSprite].sprRobotron.Tile, (rtAttractSprite[iLoopSprite].Type<<5)+(rtAttractSprite[iLoopSprite].sprRobotron.Direction<<1)+rtAttractSprite[iLoopSprite].sprRobotron.Animation);
				SetSprite(rtAttractSprite[iLoopSprite].Index, rtAttractSprite[iLoopSprite].sprRobotron.Tile, 0, rtAttractSprite[iLoopSprite].sprRobotron.xPosition>>7, rtAttractSprite[iLoopSprite].sprRobotron.yPosition>>7, PAL_ROBOTRON+(u8)rtAttractSprite[iLoopSprite].Type);
			}
			// Delete the sprite on frame .Decision
			if (rtAttractSprite[iLoopSprite].Decision==iAttractFrame)
			{
				// Destroy the sprite
				rtAttractSprite[iLoopSprite].Flags=ROBOTRON_DEAD;
				CopySpriteTile((u16*)rtRobotron, rtAttractSprite[iLoopSprite].sprRobotron.Tile, 0);
			}
			// Animate/Move the sprite on anything in the middle...
			if (rtAttractSprite[iLoopSprite].DecisionTimer<iAttractFrame&&rtAttractSprite[iLoopSprite].Decision>iAttractFrame)
			{
				// Move the sprite, why they no move?
				rtAttractSprite[iLoopSprite].sprRobotron.xPosition+=(gameReturn.GruntSpeed<<4);
				rtAttractSprite[iLoopSprite].sprRobotron.Animation^=1;
				CopySpriteTile((u16*)rtRobotron, rtAttractSprite[iLoopSprite].sprRobotron.Tile, (rtAttractSprite[iLoopSprite].Type<<5)+(rtAttractSprite[iLoopSprite].sprRobotron.Direction<<1)+rtAttractSprite[iLoopSprite].sprRobotron.Animation);
				SetSpritePosition(rtAttractSprite[iLoopSprite].Index, rtAttractSprite[iLoopSprite].sprRobotron.xPosition>>7, rtAttractSprite[iLoopSprite].sprRobotron.yPosition>>7);
			}
		}

		iPalette++;
		SetPalette(SCR_1_PLANE, PAL_LOGO, 0, RGB(15,15,0), RGB(15,0,0), iPalette);
		SetPalette(SCR_1_PLANE, PAL_ATTRACTTEXT, 0, iPalette, iPalette, iPalette);
		iBorderID^=1;
		if(iBorderID==1)
		{
			PutTile(SCR_2_PLANE, PAL_NGPCLOGO, 0,0,0);
			PutTile(SCR_2_PLANE, PAL_NGPCLOGO, 19,0,0);
			PutTile(SCR_2_PLANE, PAL_NGPCLOGO, 0,17,0);
			PutTile(SCR_2_PLANE, PAL_NGPCLOGO, 19,17,0);
		}
		iBorderPalette=iBorderPaletteStart;
		for(iLoopBorder=0;iLoopBorder<34;iLoopBorder++)
		{
			if(iLoopBorder==iBorderWhiteLogo)
			{
				PutTile(BorderPattern[iBorderID][iLoopBorder][0], PAL_NGPCLOGO+6, BorderPattern[iBorderID][iLoopBorder][1],BorderPattern[iBorderID][iLoopBorder][2],NGPCLogoTileBase+0);
				PutTile(BorderPattern[iBorderID][iLoopBorder][0], PAL_NGPCLOGO+6, BorderPattern[iBorderID][iLoopBorder][1]+1,BorderPattern[iBorderID][iLoopBorder][2],NGPCLogoTileBase+1);
				PutTile(BorderPattern[iBorderID][iLoopBorder][0], PAL_NGPCLOGO+6, BorderPattern[iBorderID][iLoopBorder][1],BorderPattern[iBorderID][iLoopBorder][2]+1,NGPCLogoTileBase+2);
				PutTile(BorderPattern[iBorderID][iLoopBorder][0], PAL_NGPCLOGO+6, BorderPattern[iBorderID][iLoopBorder][1]+1,BorderPattern[iBorderID][iLoopBorder][2]+1,NGPCLogoTileBase+3);
			}
			else
			{
				PutTile(BorderPattern[iBorderID][iLoopBorder][0], PAL_NGPCLOGO+iBorderPalette, BorderPattern[iBorderID][iLoopBorder][1],BorderPattern[iBorderID][iLoopBorder][2],NGPCLogoTileBase+0);
				PutTile(BorderPattern[iBorderID][iLoopBorder][0], PAL_NGPCLOGO+iBorderPalette, BorderPattern[iBorderID][iLoopBorder][1]+1,BorderPattern[iBorderID][iLoopBorder][2],NGPCLogoTileBase+1);
				PutTile(BorderPattern[iBorderID][iLoopBorder][0], PAL_NGPCLOGO+iBorderPalette, BorderPattern[iBorderID][iLoopBorder][1],BorderPattern[iBorderID][iLoopBorder][2]+1,NGPCLogoTileBase+2);
				PutTile(BorderPattern[iBorderID][iLoopBorder][0], PAL_NGPCLOGO+iBorderPalette, BorderPattern[iBorderID][iLoopBorder][1]+1,BorderPattern[iBorderID][iLoopBorder][2]+1,NGPCLogoTileBase+3);
			}
			iBorderPalette++;
			if(iBorderPalette>5) iBorderPalette=0;
		}
		iBorderWhiteLogo--;
		if(iBorderWhiteLogo>33) iBorderWhiteLogo=33;
		iBorderPaletteStart-=iBorderID;
		if(iBorderPaletteStart>5) iBorderPaletteStart=5;
		Sleep(6);

		// Print the current script...
		for(iLoopX=0;iLoopX<=15;iLoopX++)
		{
			PutTile(SCR_1_PLANE, PAL_ATTRACTTEXT, 2+iLoopX, 15, sScript[iAttractFrame+iLoopX]);
		}

		iAttractTimer++;
		if (iAttractTimer>=2)
		{
			iAttractFrame++;
			iAttractTimer=0;
			if (iAttractFrame>SCRIPT_LEN)
				iAttractFrame=0;
		}

	}

	ClearScreen(SCR_1_PLANE);
	ClearScreen(SCR_2_PLANE);
	ClearSprites();
	Sleep(60);


	return gameReturn;
}

HIGHSCOREENTRY rtEnterInitials(u16 Score)
{
	HIGHSCOREENTRY hstNewHero = {"AAA",0};
	u8 iPosition=0;
	u8 iOldPosition=1;
	u8 jpPrev;
	u8 jpThis;

	hstNewHero.Score=Score;

	// Allow player to enter their initials...
	rtDrawLevel();

	// Set base palettes
	rtCreatePalette();

	PrintString(SCR_1_PLANE, PAL_LOGO, 2, 4, "CONGRATULATIONS!");
	PrintString(SCR_1_PLANE, PAL_LOGO, 2, 5, "   YOU ARE A    ");
	PrintString(SCR_1_PLANE, PAL_LOGO, 2, 6, " ROBOTRON HERO  ");

	PrintDecimal(SCR_1_PLANE, PAL_ATTRACTTEXT, 6, 8, hstNewHero.Score, 8);

	PrintString(SCR_1_PLANE, PAL_BORDER, 8, 11, hstNewHero.Initials);

	PrintString(SCR_1_PLANE, PAL_DEFAULT, 2, 14, " PLEASE  ENTER");
	PrintString(SCR_1_PLANE, PAL_DEFAULT, 2, 15, " YOUR INITIALS");

	jpPrev=JOYPAD;

	// Wait for the A button to be released (in case it's held down from the game)
	while ((JOYPAD&J_A));

	// So, Left/Right to choose the letter. Up/Down to change it... A button to confirm
	while (!(JOYPAD&J_A))
	{
		jpThis=JOYPAD;
		if (jpThis!=jpPrev)
		{
			if ((jpThis&J_LEFT)&&(!(jpPrev&J_LEFT)))
			{
				if (iPosition==0)
					iPosition=2;
				else
					iPosition--;
			}
			if ((jpThis&J_RIGHT)&&(!(jpPrev&J_RIGHT)))
			{
				if (iPosition==2)
					iPosition=0;
				else
					iPosition++;
			}
			// Restrict to low-order ASCII Space(32) through to Z (90) only
			if ((jpThis&J_UP)&&(!(jpPrev&J_UP)))
			{
				if(hstNewHero.Initials[iPosition]==90)
					hstNewHero.Initials[iPosition]=32;
				else
					hstNewHero.Initials[iPosition]++;
				PrintString(SCR_1_PLANE, PAL_BORDER, 8, 11, hstNewHero.Initials);
			}
			if ((jpThis&J_DOWN)&&(!(jpPrev&J_DOWN)))
			{
				if(hstNewHero.Initials[iPosition]==32)
					hstNewHero.Initials[iPosition]=90;
				else
					hstNewHero.Initials[iPosition]--;
				PrintString(SCR_1_PLANE, PAL_BORDER, 8, 11, hstNewHero.Initials);
			}
			jpPrev=jpThis;
		}

		if (iPosition!=iOldPosition)
		{
			PrintString(SCR_1_PLANE, PAL_BORDER, 8, 12, "   ");
			PutTile(SCR_1_PLANE, PAL_ROBOTRON+TYPE_PLAYER, 8+iPosition, 12, 127);
			iOldPosition=iPosition;
		}

	}

	return hstNewHero;
}

u8 rtCollision(SPRITE sprPlayer, SPRITE sprRobotron)
{
	u16 xDistance;
	u16 yDistance;
	u8 iReturn;
	//Routine to determine collision between player and beastie

	//Collision will occur when there is less than 8 points betwixt the centre's of
	//the two sprites

	//Don't forget
	//Need to allow for the wrap around point...

	//Set the default collision
	iReturn=COLLISION_MISSED;

	if (sprPlayer.xPosition<sprRobotron.xPosition)
	{
		xDistance=sprRobotron.xPosition-sprPlayer.xPosition;
	}
	else
	{
		xDistance=sprPlayer.xPosition-sprRobotron.xPosition;
	}

	if (sprPlayer.yPosition<sprRobotron.yPosition)
	{
		yDistance=sprRobotron.yPosition-sprPlayer.yPosition;
	}
	else
	{
		yDistance=sprPlayer.yPosition-sprRobotron.yPosition;
	}

	//Scale is:
	//1024 units per tile (128 units per pixel)
	if ((xDistance<768) && (yDistance<768))
	{
		iReturn=COLLISION_HIT;
	}

	return iReturn;

}

// copies a new tile graphic into tile memory.
void CopySpriteTile(u16 * SpriteTiles, u16 TileNumber, u16 AnimNumber)
{
	u8 i;
	u16 * TileRam = TILE_RAM;
	//Our input parameter. NOT a global constant
	u16 * theSpriteAnim = (u16 *) SpriteTiles;

	TileRam += (TileNumber * 8);
	theSpriteAnim += (AnimNumber * 8);

	//We're only copying a single tile!
	for (i = 0; i < 8; i ++)
	{
		TileRam[i] = *theSpriteAnim++;
	}
}

void rtInitialise()
{
	u16 RugBitmap[17][8];

	u8 iMainLoop;
	u8 iLoopX;
	u8 iLoopY;
	u8 iTile;

	InstallTileSetAt(rtFont, sizeof(rtFont)/2, 32);


	//Just for kicks...
	SeedRandom();

	//Just copy random junk into the tile buffer...
	//See what it looks like!

	SetBackgroundColour(RGB(0, 0, 0));

	SetPalette(SCR_1_PLANE, 0, 0, RGB(15,0,0), RGB(0,15,0), RGB(0,0,15));

	CreateBitmap((u16*)RugBitmap, 32, 32);
	CopyBitmap((u16*)RugBitmap, GeneralTileBase);

	iTile=0;

	//Draw the bitmap a few times
	for (iLoopX=0;iLoopX<20;iLoopX++)
	{
		for (iLoopY=0;iLoopY<19;iLoopY++)
		{
			PutTile(SCR_1_PLANE, 0, iLoopX, iLoopY, GeneralTileBase+iTile);
			iTile++;
			if (iTile>=16)
			{
				iTile=0;
			}
		}
	}

	for (iMainLoop=0;iMainLoop<4;iMainLoop++)
	{
		for (iLoopX=0;iLoopX<32;iLoopX++)
		{
			for (iLoopY=0;iLoopY<32;iLoopY++)
			{
				SetPixel((u16*)RugBitmap, iLoopX, iLoopY, GetRandom(4));
			}
		}

		CopyBitmap((u16*)RugBitmap, GeneralTileBase);

		Sleep(15);
	}

	//Popup a "All test indicate operational" message...
	ClearScreen(SCR_1_PLANE);
	ClearSprites();

	SetPalette(SCR_1_PLANE, 0, 0, RGB(15,15,15), RGB(0,15,0), RGB(0,0,15));

	PrintString(SCR_1_PLANE, 0, 0, 8, "   INITIAL TESTS");
	PrintString(SCR_1_PLANE, 0, 0, 9, "INDICATE OPERATIONAL");

	//Then, wait a while before leaving
	Sleep(60);
}

void rtDrawLevel()
{
	u8 iLoop;

	rtCreatePalette();

	InstallTileSetAt(rtBorder, sizeof(rtBorder)/2, BorderTileBase);

	ClearScreen(SCR_1_PLANE);
	ClearScreen(SCR_2_PLANE);

	PutTile(SCR_1_PLANE, PAL_BORDER, 0, 1, BorderTileBase+rtBorderTopLeft);
	PutTile(SCR_1_PLANE, PAL_BORDER, 19, 1, BorderTileBase+rtBorderTopRight);
	PutTile(SCR_1_PLANE, PAL_BORDER, 0, 18, BorderTileBase+rtBorderBottomLeft);
	PutTile(SCR_1_PLANE, PAL_BORDER, 19, 18, BorderTileBase+rtBorderBottomRight);

	for (iLoop=1;iLoop<19;iLoop++)
	{
		PutTile(SCR_1_PLANE, PAL_BORDER, iLoop, 1, BorderTileBase+rtBorderTop);
		PutTile(SCR_1_PLANE, PAL_BORDER, iLoop, 18, BorderTileBase+rtBorderBottom);
	}
	for (iLoop=2;iLoop<18;iLoop++)
	{
		PutTile(SCR_1_PLANE, PAL_BORDER, 0, iLoop, BorderTileBase+rtBorderLeft);
		PutTile(SCR_1_PLANE, PAL_BORDER, 19, iLoop, BorderTileBase+rtBorderRight);
	}
}

LEVEL rtMoveRobotrons(LEVEL levRobotron, GAME gmRobotron, PLAYER sprPlayer)
{
	u8 iRobotronLoop;
	//Move the robotrons :)

	for (iRobotronLoop=0;iRobotronLoop<=MAX_ROBOTRON;iRobotronLoop++)
	{
		if (levRobotron.Robotron[iRobotronLoop].Flags & ROBOTRON_ACTIVE)
		{
			//It's an active roby. What type is it?
			switch (levRobotron.Robotron[iRobotronLoop].Type)
			{
				case TYPE_ELECTRODE:
					//Move Grunt
					levRobotron.Robotron[iRobotronLoop]=rtMoveElectrode(levRobotron.Robotron[iRobotronLoop], gmRobotron, sprPlayer);
					break;
				case TYPE_GRUNT:
					//Move Grunt
					levRobotron.Robotron[iRobotronLoop]=rtMoveGrunt(levRobotron.Robotron[iRobotronLoop], gmRobotron, sprPlayer);
					break;
				case TYPE_HULK:
					//Move Hulk (the last human family use the same basic movement type
					levRobotron.Robotron[iRobotronLoop]=rtMoveHulk(levRobotron.Robotron[iRobotronLoop], gmRobotron, sprPlayer);
					break;
				case TYPE_SPHEROID:
					//Move the spheroid robotron. May also spawn enforcers.
					levRobotron=rtMoveSpheroid(iRobotronLoop, levRobotron, gmRobotron, sprPlayer);
					break;
				case TYPE_ENFORCER:
					//Move the enforcer robotron. May also spawn enforcer shots
					levRobotron=rtMoveEnforcer(iRobotronLoop, levRobotron, gmRobotron, sprPlayer);
					break;
				case TYPE_BRAIN:
					levRobotron=rtMoveBrain(iRobotronLoop, levRobotron, gmRobotron, sprPlayer);
					break;
				case TYPE_QUARK:
					levRobotron=rtMoveQuark(iRobotronLoop, levRobotron, gmRobotron, sprPlayer);
					break;
				case TYPE_TANK:
					levRobotron=rtMoveTank(iRobotronLoop, levRobotron, gmRobotron, sprPlayer);
					break;
				case TYPE_ENFORCER_SHOT:
					levRobotron.Robotron[iRobotronLoop]=rtMoveEnforcerShot(levRobotron.Robotron[iRobotronLoop], gmRobotron, sprPlayer);
					break;
				case TYPE_TANK_SHOT:
					levRobotron.Robotron[iRobotronLoop]=rtMoveTankShot(levRobotron.Robotron[iRobotronLoop], gmRobotron, sprPlayer);
					break;
				case TYPE_BRAIN_SHOT:
					levRobotron.Robotron[iRobotronLoop]=rtMoveBrainShot(levRobotron.Robotron[iRobotronLoop], gmRobotron, sprPlayer);
					break;
				case TYPE_MOM:
				case TYPE_DAD:
				case TYPE_MIKEY:
					//Move the last human family
					levRobotron.Robotron[iRobotronLoop]=rtMoveFamily(levRobotron.Robotron[iRobotronLoop], gmRobotron, sprPlayer);
					break;
			}
		}
	}

	// Palette shift the Prog
	SetPalette(SPRITE_PLANE, PAL_ROBOTRON+TYPE_PROG, 0, VBCounter, VBCounter, VBCounter);

	return levRobotron;
}

ROBOTRON rtMoveElectrode(ROBOTRON rtElectrode, GAME gmRobotron, PLAYER sprPlayer)
{
	//Move an Electrode.

	//Which, obviously, don't move... But we can animate them at least
	rtElectrode.sprRobotron.Animation^=1;

	CopySpriteTile((u16*)rtRobotron, rtElectrode.sprRobotron.Tile, (rtElectrode.Type<<5)+(rtElectrode.sprRobotron.Direction<<1)+rtElectrode.sprRobotron.Animation);
	SetSpritePosition(rtElectrode.Index, rtElectrode.sprRobotron.xPosition>>7, rtElectrode.sprRobotron.yPosition>>7);

	return rtElectrode;
}


ROBOTRON rtMoveGrunt(ROBOTRON rtGrunt, GAME gmRobotron, PLAYER sprPlayer)
{
	//Move a grunt

	//Nice and simple movement...
	if (rtGrunt.sprRobotron.xPosition<sprPlayer.sprPlayer.xPosition)
		rtGrunt.sprRobotron.xPosition+=gmRobotron.GruntSpeed;
	else if (rtGrunt.sprRobotron.xPosition>sprPlayer.sprPlayer.xPosition)
		rtGrunt.sprRobotron.xPosition-=gmRobotron.GruntSpeed;
	if (rtGrunt.sprRobotron.yPosition<sprPlayer.sprPlayer.yPosition)
		rtGrunt.sprRobotron.yPosition+=gmRobotron.GruntSpeed;
	else if (rtGrunt.sprRobotron.yPosition>sprPlayer.sprPlayer.yPosition)
		rtGrunt.sprRobotron.yPosition-=gmRobotron.GruntSpeed;

	rtGrunt.sprRobotron.Animation^=1;

	CopySpriteTile((u16*)rtRobotron, rtGrunt.sprRobotron.Tile, (rtGrunt.Type<<5)+(rtGrunt.sprRobotron.Direction<<1)+rtGrunt.sprRobotron.Animation);
	SetSpritePosition(rtGrunt.Index, rtGrunt.sprRobotron.xPosition>>7, rtGrunt.sprRobotron.yPosition>>7);

	return rtGrunt;
}

ROBOTRON rtMoveHulk(ROBOTRON rtHulk, GAME gmRobotron, PLAYER sprPlayer)
{
	//Move a hulk
	//Slightly more complicated movement. Not a *lot* more complicated but slightly...
	if (rtHulk.sprRobotron.Direction==DIR_NORTH)
	{
		//Move northwards
		if (rtHulk.sprRobotron.yPosition>MIN_Y)
		{
			rtHulk.sprRobotron.yPosition-=gmRobotron.HulkSpeed;
		}
		else
		{
			rtHulk.sprRobotron.Direction=DIR_SOUTH;
		}
	}
	if (rtHulk.sprRobotron.Direction==DIR_EAST)
	{
		//Move eastwards
		if (rtHulk.sprRobotron.xPosition<MAX_X)
		{
			rtHulk.sprRobotron.xPosition+=gmRobotron.HulkSpeed;
		}
		else
		{
			rtHulk.sprRobotron.Direction=DIR_WEST;
		}
	}
	if (rtHulk.sprRobotron.Direction==DIR_SOUTH)
	{
		//Move south
		if (rtHulk.sprRobotron.yPosition<MAX_Y)
		{
			rtHulk.sprRobotron.yPosition+=gmRobotron.HulkSpeed;
		}
		else
		{
			rtHulk.sprRobotron.Direction=DIR_NORTH;
		}
	}
	if (rtHulk.sprRobotron.Direction==DIR_WEST)
	{
		//Go west
		if (rtHulk.sprRobotron.xPosition>MIN_X)
		{
			rtHulk.sprRobotron.xPosition-=gmRobotron.HulkSpeed;
		}
		else
		{
			rtHulk.sprRobotron.Direction=DIR_EAST;
		}
	}

	//Then decide whether to change direction or not

	if (rtHulk.DecisionTimer==rtHulk.Decision)
	{
		rtHulk.DecisionTimer=0;
		switch (((u8)QRandom())>>6)
		{
		case 0:
			rtHulk.sprRobotron.Direction=DIR_NORTH;
			break;
		case 1:
			rtHulk.sprRobotron.Direction=DIR_EAST;
			break;
		case 2:
			rtHulk.sprRobotron.Direction=DIR_SOUTH;
			break;
		case 3:
			rtHulk.sprRobotron.Direction=DIR_WEST;
			break;
		}
		rtHulk.Decision=1+(u16)QRandom();

	}
	rtHulk.DecisionTimer++;
	rtHulk.sprRobotron.Animation^=1;

	//Move the sprite and go home...
	CopySpriteTile((u16*)rtRobotron, rtHulk.sprRobotron.Tile, (rtHulk.Type<<5)+(rtHulk.sprRobotron.Direction<<1)+rtHulk.sprRobotron.Animation);
	SetSpritePosition(rtHulk.Index, rtHulk.sprRobotron.xPosition>>7, rtHulk.sprRobotron.yPosition>>7);

	return rtHulk;
}

ROBOTRON rtMoveFamily(ROBOTRON rtFamily, GAME gmRobotron, PLAYER sprPlayer)
{
	//Move a Family member
	//Slightly more complicated movement. Not a *lot* more complicated but slightly...

	// If they've been Progged then they get a bit more aggressive
	// (i.e. Move faster, and the direction decision making is more of a homing in on the player)
	// Speed can be a multiplier of the FamilySpeed

	u8 iSpeedMultiplier;

	iSpeedMultiplier=1;
	if (rtFamily.Flags&FAMILY_PROG)
		iSpeedMultiplier=2;

	if (rtFamily.sprRobotron.Direction==DIR_NORTH)
	{
		//Move northwards
		if (rtFamily.sprRobotron.yPosition>MIN_Y)
		{
			rtFamily.sprRobotron.yPosition-=gmRobotron.FamilySpeed*iSpeedMultiplier;
		}
		else
		{
			rtFamily.sprRobotron.Direction=DIR_SOUTH;
		}
	}
	if (rtFamily.sprRobotron.Direction==DIR_EAST)
	{
		//Move eastwards
		if (rtFamily.sprRobotron.xPosition<MAX_X)
		{
			rtFamily.sprRobotron.xPosition+=gmRobotron.FamilySpeed*iSpeedMultiplier;
		}
		else
		{
			rtFamily.sprRobotron.Direction=DIR_WEST;
		}
	}
	if (rtFamily.sprRobotron.Direction==DIR_SOUTH)
	{
		//Move south
		if (rtFamily.sprRobotron.yPosition<MAX_Y)
		{
			rtFamily.sprRobotron.yPosition+=gmRobotron.FamilySpeed*iSpeedMultiplier;
		}
		else
		{
			rtFamily.sprRobotron.Direction=DIR_NORTH;
		}
	}
	if (rtFamily.sprRobotron.Direction==DIR_WEST)
	{
		//Go west
		if (rtFamily.sprRobotron.xPosition>MIN_X)
		{
			rtFamily.sprRobotron.xPosition-=gmRobotron.FamilySpeed*iSpeedMultiplier;
		}
		else
		{
			rtFamily.sprRobotron.Direction=DIR_EAST;
		}
	}

	//Then decide whether to change direction or not
	if (rtFamily.Flags&FAMILY_PROG)
	{
		// Home in on the player
		switch (rtFamily.sprRobotron.Direction)
		{
			case DIR_EAST:
				//x position should be less than the players
				if (sprPlayer.sprPlayer.xPosition-rtFamily.sprRobotron.xPosition<128)
				{
					//head north/south
					if (sprPlayer.sprPlayer.yPosition<rtFamily.sprRobotron.yPosition)
						rtFamily.sprRobotron.Direction=DIR_NORTH;
					else
						rtFamily.sprRobotron.Direction=DIR_SOUTH;
				}
				break;
			case DIR_WEST:
				// x position should be greater than the players
				if (rtFamily.sprRobotron.xPosition-sprPlayer.sprPlayer.xPosition<128)
				{
					//head north/south
					if (sprPlayer.sprPlayer.yPosition<rtFamily.sprRobotron.yPosition)
						rtFamily.sprRobotron.Direction=DIR_NORTH;
					else
						rtFamily.sprRobotron.Direction=DIR_SOUTH;
				}
				break;
			case DIR_SOUTH:
				//y position should be less than the players
				if (sprPlayer.sprPlayer.yPosition-rtFamily.sprRobotron.yPosition<128)
				{
					//head north/south
					if (sprPlayer.sprPlayer.xPosition<rtFamily.sprRobotron.xPosition)
						rtFamily.sprRobotron.Direction=DIR_NORTH;
					else
						rtFamily.sprRobotron.Direction=DIR_SOUTH;
				}
				break;
			case DIR_NORTH:
				//y position should be greater than the players
				if (rtFamily.sprRobotron.yPosition-sprPlayer.sprPlayer.yPosition<128)
				{
					//head north/south
					if (sprPlayer.sprPlayer.xPosition<rtFamily.sprRobotron.xPosition)
						rtFamily.sprRobotron.Direction=DIR_NORTH;
					else
						rtFamily.sprRobotron.Direction=DIR_SOUTH;
				}
				break;
		}
	}
	else
	{
		if (rtFamily.DecisionTimer==rtFamily.Decision)
		{
			rtFamily.DecisionTimer=0;
			switch (((u8)QRandom())>>6)
			{
			case 0:
				rtFamily.sprRobotron.Direction=DIR_NORTH;
				break;
			case 1:
				rtFamily.sprRobotron.Direction=DIR_EAST;
				break;
			case 2:
				rtFamily.sprRobotron.Direction=DIR_SOUTH;
				break;
			case 3:
				rtFamily.sprRobotron.Direction=DIR_WEST;
				break;
			}
			rtFamily.Decision=1+(u16)QRandom();

		}
	}
	rtFamily.DecisionTimer++;
	rtFamily.sprRobotron.Animation^=1;

	//Move the sprite and go home...
	CopySpriteTile((u16*)rtRobotron, rtFamily.sprRobotron.Tile, (rtFamily.Type<<5)+(rtFamily.sprRobotron.Direction<<1)+rtFamily.sprRobotron.Animation);
	SetSpritePosition(rtFamily.Index, rtFamily.sprRobotron.xPosition>>7, rtFamily.sprRobotron.yPosition>>7);

	return rtFamily;
}

LEVEL rtMoveEnforcer(u8 iEnforcer, LEVEL levRobotron, GAME gmRobotron, PLAYER sprPlayer)
{
	//Move the Enforcer robotrons...

	//Basically, they mob the player (sort of like Grunts) although will occasionally
	//bugger off and sit in a corner.

	if (levRobotron.Robotron[iEnforcer].sprRobotron.Direction&DIR_NORTH)
	{
		//Move northwards
		if (levRobotron.Robotron[iEnforcer].sprRobotron.yPosition>MIN_Y)
		{
			levRobotron.Robotron[iEnforcer].sprRobotron.yPosition-=gmRobotron.EnforcerSpeed;
		}
		else
		{
			levRobotron.Robotron[iEnforcer].sprRobotron.Direction=levRobotron.Robotron[iEnforcer].sprRobotron.Direction-DIR_NORTH;
		}
	}
	if (levRobotron.Robotron[iEnforcer].sprRobotron.Direction&DIR_EAST)
	{
		//Move eastwards
		if (levRobotron.Robotron[iEnforcer].sprRobotron.xPosition<MAX_X)
		{
			levRobotron.Robotron[iEnforcer].sprRobotron.xPosition+=gmRobotron.EnforcerSpeed;
		}
		else
		{
			levRobotron.Robotron[iEnforcer].sprRobotron.Direction=levRobotron.Robotron[iEnforcer].sprRobotron.Direction-DIR_EAST;
		}
	}
	if (levRobotron.Robotron[iEnforcer].sprRobotron.Direction&DIR_SOUTH)
	{
		//Move south
		if (levRobotron.Robotron[iEnforcer].sprRobotron.yPosition<MAX_Y)
		{
			levRobotron.Robotron[iEnforcer].sprRobotron.yPosition+=gmRobotron.EnforcerSpeed;
		}
		else
		{
			levRobotron.Robotron[iEnforcer].sprRobotron.Direction=levRobotron.Robotron[iEnforcer].sprRobotron.Direction-DIR_SOUTH;
		}
	}
	if (levRobotron.Robotron[iEnforcer].sprRobotron.Direction&DIR_WEST)
	{
		//Go west
		if (levRobotron.Robotron[iEnforcer].sprRobotron.xPosition>MIN_X)
		{
			levRobotron.Robotron[iEnforcer].sprRobotron.xPosition-=gmRobotron.EnforcerSpeed;
		}
		else
		{
			levRobotron.Robotron[iEnforcer].sprRobotron.Direction=levRobotron.Robotron[iEnforcer].sprRobotron.Direction-DIR_WEST;
		}
	}

	//Then decide whether to change direction or not

	//Enforcers will randomly disappear, because their direction gets set to zero...
	//This could be because they've homed into a corner or, possibly, because they
	//Have exactly homed in on the players X or Y coords.
	//That would be bad...
	//The question is... Why doesn't the decision timer kick in when this happens?
	//Answer... Because, if the decision is set to Zero, then DecisionTimer has to loop
	//through the whole 16bit address space until it reaches zero again. If left for a
	//significantly long time then it would (eventually) recover and kick off again.
	//Practical Answer... Don't let the Decision target be set to Zero.
	//Although, fantastically, if we set the decision target to a significantly high number
	//then we should see the classic Corner Lurking behavious kick in.
	if (levRobotron.Robotron[iEnforcer].DecisionTimer==levRobotron.Robotron[iEnforcer].Decision)
	{
		//Change one direction randomly.
		//Should also randomly create a shot - which will shoot off in the direction of the
		//the player.
		levRobotron.Robotron[iEnforcer].DecisionTimer=0;
		levRobotron.Robotron[iEnforcer].sprRobotron.Direction=0;
		if(levRobotron.Robotron[iEnforcer].sprRobotron.xPosition<sprPlayer.sprPlayer.xPosition)
		{
			levRobotron.Robotron[iEnforcer].sprRobotron.Direction+=DIR_EAST;
		}
		else if(levRobotron.Robotron[iEnforcer].sprRobotron.xPosition>sprPlayer.sprPlayer.xPosition)
		{
			levRobotron.Robotron[iEnforcer].sprRobotron.Direction+=DIR_WEST;
		}
		if(levRobotron.Robotron[iEnforcer].sprRobotron.yPosition<sprPlayer.sprPlayer.yPosition)
		{
			levRobotron.Robotron[iEnforcer].sprRobotron.Direction+=DIR_SOUTH;
		}
		else if(levRobotron.Robotron[iEnforcer].sprRobotron.yPosition>sprPlayer.sprPlayer.yPosition)
		{
			levRobotron.Robotron[iEnforcer].sprRobotron.Direction+=DIR_NORTH;
		}

		//Make the Enforcers quite skittish.
		levRobotron.Robotron[iEnforcer].Decision=1+((u16)QRandom()>>1);
	}
	levRobotron.Robotron[iEnforcer].DecisionTimer++;
	levRobotron.Robotron[iEnforcer].sprRobotron.Animation^=1;

	//Move the sprite and go home...
	CopySpriteTile((u16*)rtRobotron, levRobotron.Robotron[iEnforcer].sprRobotron.Tile, (levRobotron.Robotron[iEnforcer].Type<<5)+(levRobotron.Robotron[iEnforcer].sprRobotron.Direction<<1)+levRobotron.Robotron[iEnforcer].sprRobotron.Animation);
	SetSpritePosition(levRobotron.Robotron[iEnforcer].Index, levRobotron.Robotron[iEnforcer].sprRobotron.xPosition>>7, levRobotron.Robotron[iEnforcer].sprRobotron.yPosition>>7);

	return levRobotron;
}

LEVEL rtMoveBrain(u8 iBrain, LEVEL levRobotron, GAME gmRobotron, PLAYER sprPlayer)
{

	//Brains...
	//Probably the only robotron with any active intelligence.
	//They will seek out the last human family and turn them into evil progs.
	//Oh, and they'll occasionally shoot - not too often though.
	//North/South/East/West movement only (whichever is furthest away)
	//Pick a member of the family and move towards it
	//The only "hard" bit is picking which member of the family to head towards.

	//So. We can use the .Decision flag to decide which member of the LHF to
	//head towards. If the flag is dead, then we go into our decision making
	//process to choose a new one.

	if ((levRobotron.Robotron[levRobotron.Robotron[iBrain].Decision].Flags==ROBOTRON_ACTIVE) && (levRobotron.Robotron[levRobotron.Robotron[iBrain].Decision].Type<TYPE_HULK))
	{
		//Target is still alive. Go there now.
		if (levRobotron.Robotron[iBrain].sprRobotron.xPosition<levRobotron.Robotron[levRobotron.Robotron[iBrain].Decision].sprRobotron.xPosition)
		{
			levRobotron.Robotron[iBrain].sprRobotron.xPosition+=gmRobotron.BrainSpeed;
			levRobotron.Robotron[iBrain].sprRobotron.Direction=DIR_EAST;
		}
		else if (levRobotron.Robotron[iBrain].sprRobotron.xPosition>levRobotron.Robotron[levRobotron.Robotron[iBrain].Decision].sprRobotron.xPosition)
		{
			levRobotron.Robotron[iBrain].sprRobotron.xPosition-=gmRobotron.BrainSpeed;
			levRobotron.Robotron[iBrain].sprRobotron.Direction=DIR_WEST;
		}
		else if (levRobotron.Robotron[iBrain].sprRobotron.yPosition<levRobotron.Robotron[levRobotron.Robotron[iBrain].Decision].sprRobotron.yPosition)
		{
			levRobotron.Robotron[iBrain].sprRobotron.yPosition+=gmRobotron.BrainSpeed;
			levRobotron.Robotron[iBrain].sprRobotron.Direction=DIR_SOUTH;
		}
		else if (levRobotron.Robotron[iBrain].sprRobotron.yPosition<levRobotron.Robotron[levRobotron.Robotron[iBrain].Decision].sprRobotron.yPosition)
		{
			levRobotron.Robotron[iBrain].sprRobotron.yPosition-=gmRobotron.BrainSpeed;
			levRobotron.Robotron[iBrain].sprRobotron.Direction=DIR_NORTH;
		}
	}
	else
	{
		//Target is either dead or has been collected by the player
		//<Terminator>Time to aquire a new target

	}

	// Also, very occasionally let off a warning shot

	levRobotron.Robotron[iBrain].sprRobotron.Animation^=1;

	//Move the sprite and go home...
	CopySpriteTile((u16*)rtRobotron, levRobotron.Robotron[iBrain].sprRobotron.Tile, (levRobotron.Robotron[iBrain].Type<<5)+(levRobotron.Robotron[iBrain].sprRobotron.Direction<<1)+levRobotron.Robotron[iBrain].sprRobotron.Animation);
	SetSpritePosition(levRobotron.Robotron[iBrain].Index, levRobotron.Robotron[iBrain].sprRobotron.xPosition>>7, levRobotron.Robotron[iBrain].sprRobotron.yPosition>>7);

	return levRobotron;
}

LEVEL rtMoveQuark(u8 iQuark, LEVEL levRobotron, GAME gmRobotron, PLAYER sprPlayer)
{
	u8 iTankLoop;

	//Quarks. Nice 'n simple.
	//Zip around the diagonals - bouncing when they hit the walls and
	//occasionally switching direction completely.
	//Drop Tanks as required...

	if (levRobotron.Robotron[iQuark].sprRobotron.Direction&DIR_NORTH)
	{
		//Move northwards
		if (levRobotron.Robotron[iQuark].sprRobotron.yPosition>MIN_Y)
		{
			levRobotron.Robotron[iQuark].sprRobotron.yPosition-=gmRobotron.QuarkSpeed;
		}
		else
		{
			levRobotron.Robotron[iQuark].sprRobotron.Direction=levRobotron.Robotron[iQuark].sprRobotron.Direction-DIR_NORTH+DIR_SOUTH;
		}
	}
	if (levRobotron.Robotron[iQuark].sprRobotron.Direction&DIR_EAST)
	{
		//Move eastwards
		if (levRobotron.Robotron[iQuark].sprRobotron.xPosition<MAX_X)
		{
			levRobotron.Robotron[iQuark].sprRobotron.xPosition+=gmRobotron.QuarkSpeed;
		}
		else
		{
			levRobotron.Robotron[iQuark].sprRobotron.Direction=levRobotron.Robotron[iQuark].sprRobotron.Direction-DIR_EAST+DIR_WEST;
		}
	}
	if (levRobotron.Robotron[iQuark].sprRobotron.Direction&DIR_SOUTH)
	{
		//Move south
		if (levRobotron.Robotron[iQuark].sprRobotron.yPosition<MAX_Y)
		{
			levRobotron.Robotron[iQuark].sprRobotron.yPosition+=gmRobotron.QuarkSpeed;
		}
		else
		{
			levRobotron.Robotron[iQuark].sprRobotron.Direction=levRobotron.Robotron[iQuark].sprRobotron.Direction-DIR_SOUTH+DIR_NORTH;
		}
	}
	if (levRobotron.Robotron[iQuark].sprRobotron.Direction&DIR_WEST)
	{
		//Go west
		if (levRobotron.Robotron[iQuark].sprRobotron.xPosition>MIN_X)
		{
			levRobotron.Robotron[iQuark].sprRobotron.xPosition-=gmRobotron.QuarkSpeed;
		}
		else
		{
			levRobotron.Robotron[iQuark].sprRobotron.Direction=levRobotron.Robotron[iQuark].sprRobotron.Direction-DIR_WEST+DIR_EAST;
		}
	}

	if (levRobotron.Robotron[iQuark].DecisionTimer==levRobotron.Robotron[iQuark].Decision)
	{
		//So. What next.
		//Remember. Quarks only move on diagonals...
		//Move randomly, and fire off a tank one in 5 turns.
		//This might be "too" random in that drunkard's walk might take over and the quark will just sort of bimble about on the spot.
		levRobotron.Robotron[iQuark].DecisionTimer=0;
		switch (((u8)QRandom())>>4)
		{
		case 0:
			levRobotron.Robotron[iQuark].sprRobotron.Direction=DIR_NORTH+DIR_EAST;
			break;
		case 1:
			levRobotron.Robotron[iQuark].sprRobotron.Direction=DIR_NORTH+DIR_WEST;
			break;
		case 2:
			levRobotron.Robotron[iQuark].sprRobotron.Direction=DIR_SOUTH+DIR_EAST;
			break;
		case 3:
			levRobotron.Robotron[iQuark].sprRobotron.Direction=DIR_SOUTH+DIR_WEST;
			break;
		default:
			iTankLoop=0;
			//Find the next available slot in the robotron list...
			while(iTankLoop<MAX_ROBOTRON)
			{
				if (!(levRobotron.Robotron[iTankLoop].Flags&ROBOTRON_ACTIVE))
				{
					levRobotron.Robotron[iTankLoop].sprRobotron.xPosition=levRobotron.Robotron[iQuark].sprRobotron.xPosition;
					levRobotron.Robotron[iTankLoop].sprRobotron.yPosition=levRobotron.Robotron[iQuark].sprRobotron.yPosition;
					levRobotron.Robotron[iTankLoop].sprRobotron.Direction=levRobotron.Robotron[iQuark].sprRobotron.Direction;
					levRobotron.Robotron[iTankLoop].sprRobotron.Animation=levRobotron.Robotron[iQuark].sprRobotron.Animation;
					levRobotron.Robotron[iTankLoop].Type=TYPE_TANK;
					levRobotron.Robotron[iTankLoop].DecisionTimer=0;
					levRobotron.Robotron[iTankLoop].Decision=0;
					levRobotron.Robotron[iTankLoop].Flags=ROBOTRON_ACTIVE;
					levRobotron.EnemyCount++;

					CopySpriteTile((u16*)rtRobotron, levRobotron.Robotron[iTankLoop].sprRobotron.Tile, (levRobotron.Robotron[iTankLoop].Type<<5)+(levRobotron.Robotron[iTankLoop].sprRobotron.Direction<<1)+levRobotron.Robotron[iTankLoop].sprRobotron.Animation);
					SetSprite(levRobotron.Robotron[iTankLoop].Index, levRobotron.Robotron[iTankLoop].sprRobotron.Tile, 0, levRobotron.Robotron[iTankLoop].sprRobotron.xPosition>>7, levRobotron.Robotron[iTankLoop].sprRobotron.yPosition>>7, PAL_ROBOTRON+(u8)levRobotron.Robotron[iTankLoop].Type);

					//Quarks never stop spawning - so no need to play with SpawnCount
					//Just quit the loop.
					iTankLoop=MAX_ROBOTRON;
				}
				iTankLoop++;
			}
			break;
		}
		levRobotron.Robotron[iQuark].Decision=1+(u16)QRandom();


	}

	levRobotron.Robotron[iQuark].DecisionTimer++;
	levRobotron.Robotron[iQuark].sprRobotron.Animation^=1;

	//Move the sprite and go home...
	CopySpriteTile((u16*)rtRobotron, levRobotron.Robotron[iQuark].sprRobotron.Tile, (levRobotron.Robotron[iQuark].Type<<5)+(levRobotron.Robotron[iQuark].sprRobotron.Direction<<1)+levRobotron.Robotron[iQuark].sprRobotron.Animation);
	SetSpritePosition(levRobotron.Robotron[iQuark].Index, levRobotron.Robotron[iQuark].sprRobotron.xPosition>>7, levRobotron.Robotron[iQuark].sprRobotron.yPosition>>7);

	return levRobotron;
}

LEVEL rtMoveTank(u8 iTank, LEVEL levRobotron, GAME gmRobotron, PLAYER sprPlayer)
{
	u8 iTankShotLoop;
	//Tanks.
	//Exactly the same movement pattern as their parents.
	//With added firing.

	if (levRobotron.Robotron[iTank].sprRobotron.Direction&DIR_NORTH)
	{
		//Move northwards
		if (levRobotron.Robotron[iTank].sprRobotron.yPosition>MIN_Y)
		{
			levRobotron.Robotron[iTank].sprRobotron.yPosition-=gmRobotron.TankSpeed;
		}
		else
		{
			levRobotron.Robotron[iTank].sprRobotron.Direction=levRobotron.Robotron[iTank].sprRobotron.Direction-DIR_NORTH+DIR_SOUTH;
		}
	}
	if (levRobotron.Robotron[iTank].sprRobotron.Direction&DIR_EAST)
	{
		//Move eastwards
		if (levRobotron.Robotron[iTank].sprRobotron.xPosition<MAX_X)
		{
			levRobotron.Robotron[iTank].sprRobotron.xPosition+=gmRobotron.TankSpeed;
		}
		else
		{
			levRobotron.Robotron[iTank].sprRobotron.Direction=levRobotron.Robotron[iTank].sprRobotron.Direction-DIR_EAST+DIR_WEST;
		}
	}
	if (levRobotron.Robotron[iTank].sprRobotron.Direction&DIR_SOUTH)
	{
		//Move south
		if (levRobotron.Robotron[iTank].sprRobotron.yPosition<MAX_Y)
		{
			levRobotron.Robotron[iTank].sprRobotron.yPosition+=gmRobotron.TankSpeed;
		}
		else
		{
			levRobotron.Robotron[iTank].sprRobotron.Direction=levRobotron.Robotron[iTank].sprRobotron.Direction-DIR_SOUTH+DIR_NORTH;
		}
	}
	if (levRobotron.Robotron[iTank].sprRobotron.Direction&DIR_WEST)
	{
		//Go west
		if (levRobotron.Robotron[iTank].sprRobotron.xPosition>MIN_X)
		{
			levRobotron.Robotron[iTank].sprRobotron.xPosition-=gmRobotron.TankSpeed;
		}
		else
		{
			levRobotron.Robotron[iTank].sprRobotron.Direction=levRobotron.Robotron[iTank].sprRobotron.Direction-DIR_WEST+DIR_EAST;
		}
	}

	if (levRobotron.Robotron[iTank].DecisionTimer==levRobotron.Robotron[iTank].Decision)
	{
		//So. What next.
		//Remember. Tanks only move on diagonals...
		levRobotron.Robotron[iTank].DecisionTimer=0;
		switch (((u8)QRandom())>>4)
		{
		case 0:
			levRobotron.Robotron[iTank].sprRobotron.Direction=DIR_NORTH+DIR_EAST;
			break;
		case 1:
			levRobotron.Robotron[iTank].sprRobotron.Direction=DIR_NORTH+DIR_WEST;
			break;
		case 2:
			levRobotron.Robotron[iTank].sprRobotron.Direction=DIR_SOUTH+DIR_EAST;
			break;
		case 3:
			levRobotron.Robotron[iTank].sprRobotron.Direction=DIR_SOUTH+DIR_WEST;
			break;
		default:
			//Shoot
			while(iTankShotLoop<MAX_ROBOTRON)
			{
				if (!(levRobotron.Robotron[iTankShotLoop].Flags&ROBOTRON_ACTIVE))
				{
					levRobotron.Robotron[iTankShotLoop].sprRobotron.xPosition=levRobotron.Robotron[iTank].sprRobotron.xPosition;
					levRobotron.Robotron[iTankShotLoop].sprRobotron.yPosition=levRobotron.Robotron[iTank].sprRobotron.yPosition;
					levRobotron.Robotron[iTankShotLoop].sprRobotron.Direction=0;
					if (levRobotron.Robotron[iTankShotLoop].sprRobotron.xPosition<sprPlayer.sprPlayer.xPosition)
					{
						levRobotron.Robotron[iTankShotLoop].sprRobotron.Direction+=DIR_EAST;
					}
					else if (levRobotron.Robotron[iTankShotLoop].sprRobotron.xPosition>sprPlayer.sprPlayer.xPosition)
					{
						levRobotron.Robotron[iTankShotLoop].sprRobotron.Direction+=DIR_WEST;
					}
					if (levRobotron.Robotron[iTankShotLoop].sprRobotron.yPosition<sprPlayer.sprPlayer.yPosition)
					{
						levRobotron.Robotron[iTankShotLoop].sprRobotron.Direction+=DIR_SOUTH;
					}
					else if (levRobotron.Robotron[iTankShotLoop].sprRobotron.yPosition>sprPlayer.sprPlayer.yPosition)
					{
						levRobotron.Robotron[iTankShotLoop].sprRobotron.Direction+=DIR_NORTH;
					}
					levRobotron.Robotron[iTankShotLoop].sprRobotron.Animation=levRobotron.Robotron[iTank].sprRobotron.Animation;
					levRobotron.Robotron[iTankShotLoop].Type=TYPE_TANK_SHOT;
					levRobotron.Robotron[iTankShotLoop].DecisionTimer=0;
					levRobotron.Robotron[iTankShotLoop].Decision=0;
					levRobotron.Robotron[iTankShotLoop].Flags=ROBOTRON_ACTIVE;

					CopySpriteTile((u16*)rtRobotron, levRobotron.Robotron[iTankShotLoop].sprRobotron.Tile, (levRobotron.Robotron[iTankShotLoop].Type<<5)+(levRobotron.Robotron[iTankShotLoop].sprRobotron.Direction<<1)+levRobotron.Robotron[iTankShotLoop].sprRobotron.Animation);
					SetSprite(levRobotron.Robotron[iTankShotLoop].Index, levRobotron.Robotron[iTankShotLoop].sprRobotron.Tile, 0, levRobotron.Robotron[iTankShotLoop].sprRobotron.xPosition>>7, levRobotron.Robotron[iTankShotLoop].sprRobotron.yPosition>>7, PAL_ROBOTRON+(u8)levRobotron.Robotron[iTankShotLoop].Type);

					//Tanks never stop shooting - so if they can shoot then they should do.
					//Just quit the loop.
					iTankShotLoop=MAX_ROBOTRON;
				}
				iTankShotLoop++;
			}

			break;
		}
		levRobotron.Robotron[iTank].Decision=1+(u16)QRandom();


	}

	levRobotron.Robotron[iTank].DecisionTimer++;
	levRobotron.Robotron[iTank].sprRobotron.Animation^=1;

	//Move the sprite and go home...
	CopySpriteTile((u16*)rtRobotron, levRobotron.Robotron[iTank].sprRobotron.Tile, (levRobotron.Robotron[iTank].Type<<5)+(levRobotron.Robotron[iTank].sprRobotron.Direction<<1)+levRobotron.Robotron[iTank].sprRobotron.Animation);
	SetSpritePosition(levRobotron.Robotron[iTank].Index, levRobotron.Robotron[iTank].sprRobotron.xPosition>>7, levRobotron.Robotron[iTank].sprRobotron.yPosition>>7);

	return levRobotron;
}

ROBOTRON rtMoveBrainShot(ROBOTRON rtBrainShot, GAME gmRobotron, PLAYER sprPlayer)
{
	// Similar movement pattern to the Progs - i.e. move in the current direction until level with the player and then home in...
	if (rtBrainShot.sprRobotron.Direction==DIR_NORTH)
	{
		//Move northwards
		if (rtBrainShot.sprRobotron.yPosition>MIN_Y)
		{
			rtBrainShot.sprRobotron.yPosition-=gmRobotron.BrainShotSpeed;
		}
		else
		{
			rtBrainShot.sprRobotron.Direction=DIR_SOUTH;
		}
		if (rtBrainShot.sprRobotron.yPosition-sprPlayer.sprPlayer.yPosition<128)
		{
			//head north/south
			if (sprPlayer.sprPlayer.xPosition<rtBrainShot.sprRobotron.xPosition)
				rtBrainShot.sprRobotron.Direction=DIR_NORTH;
			else
				rtBrainShot.sprRobotron.Direction=DIR_SOUTH;
		}
	}
	if (rtBrainShot.sprRobotron.Direction==DIR_EAST)
	{
		//Move eastwards
		if (rtBrainShot.sprRobotron.xPosition<MAX_X)
		{
			rtBrainShot.sprRobotron.xPosition+=gmRobotron.BrainShotSpeed;
		}
		else
		{
			rtBrainShot.sprRobotron.Direction=DIR_WEST;
		}
		//x position should be less than the players
		if (sprPlayer.sprPlayer.xPosition-rtBrainShot.sprRobotron.xPosition<128)
		{
			//head north/south
			if (sprPlayer.sprPlayer.yPosition<rtBrainShot.sprRobotron.yPosition)
				rtBrainShot.sprRobotron.Direction=DIR_NORTH;
			else
				rtBrainShot.sprRobotron.Direction=DIR_SOUTH;
		}

	}
	if (rtBrainShot.sprRobotron.Direction==DIR_SOUTH)
	{
		//Move south
		if (rtBrainShot.sprRobotron.yPosition<MAX_Y)
		{
			rtBrainShot.sprRobotron.yPosition+=gmRobotron.BrainShotSpeed;
		}
		else
		{
			rtBrainShot.sprRobotron.Direction=DIR_NORTH;
		}
		//y position should be less than the players
		if (sprPlayer.sprPlayer.yPosition-rtBrainShot.sprRobotron.yPosition<128)
		{
			//head north/south
			if (sprPlayer.sprPlayer.xPosition<rtBrainShot.sprRobotron.xPosition)
				rtBrainShot.sprRobotron.Direction=DIR_NORTH;
			else
				rtBrainShot.sprRobotron.Direction=DIR_SOUTH;
		}
	}
	if (rtBrainShot.sprRobotron.Direction==DIR_WEST)
	{
		//Go west
		if (rtBrainShot.sprRobotron.xPosition>MIN_X)
		{
			rtBrainShot.sprRobotron.xPosition-=gmRobotron.BrainShotSpeed;
		}
		else
		{
			rtBrainShot.sprRobotron.Direction=DIR_EAST;
		}
		// x position should be greater than the players
		if (rtBrainShot.sprRobotron.xPosition-sprPlayer.sprPlayer.xPosition<128)
		{
			//head north/south
			if (sprPlayer.sprPlayer.yPosition<rtBrainShot.sprRobotron.yPosition)
				rtBrainShot.sprRobotron.Direction=DIR_NORTH;
			else
				rtBrainShot.sprRobotron.Direction=DIR_SOUTH;
		}
	}


	rtBrainShot.sprRobotron.Animation^=1;

	//Move the sprite and go home...
	CopySpriteTile((u16*)rtRobotron, rtBrainShot.sprRobotron.Tile, (rtBrainShot.Type<<5)+(rtBrainShot.sprRobotron.Direction<<1)+rtBrainShot.sprRobotron.Animation);
	SetSpritePosition(rtBrainShot.Index, rtBrainShot.sprRobotron.xPosition>>7, rtBrainShot.sprRobotron.yPosition>>7);

	return rtBrainShot;
}

ROBOTRON rtMoveTankShot(ROBOTRON rtTankShot, GAME gmRobotron, PLAYER sprPlayer)
{
	// Just keeps going until destroyed
	if (rtTankShot.sprRobotron.Direction==DIR_NORTH)
	{
		//Move northwards
		if (rtTankShot.sprRobotron.yPosition>MIN_Y)
		{
			rtTankShot.sprRobotron.yPosition-=gmRobotron.TankShotSpeed;
		}
		else
		{
			rtTankShot.sprRobotron.Direction=DIR_SOUTH;
		}
	}
	if (rtTankShot.sprRobotron.Direction==DIR_EAST)
	{
		//Move eastwards
		if (rtTankShot.sprRobotron.xPosition<MAX_X)
		{
			rtTankShot.sprRobotron.xPosition+=gmRobotron.TankShotSpeed;
		}
		else
		{
			rtTankShot.sprRobotron.Direction=DIR_WEST;
		}

	}
	if (rtTankShot.sprRobotron.Direction==DIR_SOUTH)
	{
		//Move south
		if (rtTankShot.sprRobotron.yPosition<MAX_Y)
		{
			rtTankShot.sprRobotron.yPosition+=gmRobotron.TankShotSpeed;
		}
		else
		{
			rtTankShot.sprRobotron.Direction=DIR_NORTH;
		}
	}
	if (rtTankShot.sprRobotron.Direction==DIR_WEST)
	{
		//Go west
		if (rtTankShot.sprRobotron.xPosition>MIN_X)
		{
			rtTankShot.sprRobotron.xPosition-=gmRobotron.TankShotSpeed;
		}
		else
		{
			rtTankShot.sprRobotron.Direction=DIR_EAST;
		}
	}

	rtTankShot.sprRobotron.Animation^=1;

	//Move the sprite and go home...
	CopySpriteTile((u16*)rtRobotron, rtTankShot.sprRobotron.Tile, (rtTankShot.Type<<5)+(rtTankShot.sprRobotron.Direction<<1)+rtTankShot.sprRobotron.Animation);
	SetSpritePosition(rtTankShot.Index, rtTankShot.sprRobotron.xPosition>>7, rtTankShot.sprRobotron.yPosition>>7);

	return rtTankShot;
}

ROBOTRON rtMoveEnforcerShot(ROBOTRON rtEnforcerShot, GAME gmRobotron, PLAYER sprPlayer)
{
	// keep travelling until it hits either the edge or the player
	if (rtEnforcerShot.sprRobotron.Direction==DIR_NORTH)
	{
		//Move northwards
		if (rtEnforcerShot.sprRobotron.yPosition>MIN_Y)
		{
			rtEnforcerShot.sprRobotron.yPosition-=gmRobotron.EnforcerShotSpeed;
		}
		else
		{
			rtEnforcerShot.Flags=ROBOTRON_DEAD;
			rtEnforcerShot.sprRobotron.Direction=0;
			CopySpriteTile((u16*)rtRobotron, rtEnforcerShot.sprRobotron.Tile, 0);
		}
	}
	if (rtEnforcerShot.sprRobotron.Direction==DIR_EAST)
	{
		//Move eastwards
		if (rtEnforcerShot.sprRobotron.xPosition<MAX_X)
		{
			rtEnforcerShot.sprRobotron.xPosition+=gmRobotron.EnforcerShotSpeed;
		}
		else
		{
			rtEnforcerShot.Flags=ROBOTRON_DEAD;
			rtEnforcerShot.sprRobotron.Direction=0;
			CopySpriteTile((u16*)rtRobotron, rtEnforcerShot.sprRobotron.Tile, 0);
		}

	}
	if (rtEnforcerShot.sprRobotron.Direction==DIR_SOUTH)
	{
		//Move south
		if (rtEnforcerShot.sprRobotron.yPosition<MAX_Y)
		{
			rtEnforcerShot.sprRobotron.yPosition+=gmRobotron.EnforcerShotSpeed;
		}
		else
		{
			rtEnforcerShot.Flags=ROBOTRON_DEAD;
			rtEnforcerShot.sprRobotron.Direction=0;
			CopySpriteTile((u16*)rtRobotron, rtEnforcerShot.sprRobotron.Tile, 0);
		}
	}
	if (rtEnforcerShot.sprRobotron.Direction==DIR_WEST)
	{
		//Go west
		if (rtEnforcerShot.sprRobotron.xPosition>MIN_X)
		{
			rtEnforcerShot.sprRobotron.xPosition-=gmRobotron.EnforcerShotSpeed;
		}
		else
		{
			rtEnforcerShot.Flags=ROBOTRON_DEAD;
			rtEnforcerShot.sprRobotron.Direction=0;
			CopySpriteTile((u16*)rtRobotron, rtEnforcerShot.sprRobotron.Tile, 0);
		}
	}

	rtEnforcerShot.sprRobotron.Animation^=1;

	//Move the sprite and go home...
	CopySpriteTile((u16*)rtRobotron, rtEnforcerShot.sprRobotron.Tile, (rtEnforcerShot.Type<<5)+(rtEnforcerShot.sprRobotron.Direction<<1)+rtEnforcerShot.sprRobotron.Animation);
	SetSpritePosition(rtEnforcerShot.Index, rtEnforcerShot.sprRobotron.xPosition>>7, rtEnforcerShot.sprRobotron.yPosition>>7);

	return rtEnforcerShot;
}

LEVEL rtMoveSpheroid(u8 iSpheroid, LEVEL levRobotron, GAME gmRobotron, PLAYER sprPlayer)
{
	u8 iEnforcerLoop;
	u8 iSpawnCount;
	//Move the spheroid robotrons...

	//Basically, they zip around the level at a good old pace (mostly in diagonals)
	//and drop Enforcers.

	if (levRobotron.Robotron[iSpheroid].sprRobotron.Direction&DIR_NORTH)
	{
		//Move northwards
		if (levRobotron.Robotron[iSpheroid].sprRobotron.yPosition>MIN_Y)
		{
			levRobotron.Robotron[iSpheroid].sprRobotron.yPosition-=gmRobotron.SpheroidSpeed;
		}
		else
		{
			levRobotron.Robotron[iSpheroid].sprRobotron.Direction=levRobotron.Robotron[iSpheroid].sprRobotron.Direction-DIR_NORTH+DIR_SOUTH;
		}
	}
	if (levRobotron.Robotron[iSpheroid].sprRobotron.Direction&DIR_EAST)
	{
		//Move eastwards
		if (levRobotron.Robotron[iSpheroid].sprRobotron.xPosition<MAX_X)
		{
			levRobotron.Robotron[iSpheroid].sprRobotron.xPosition+=gmRobotron.SpheroidSpeed;
		}
		else
		{
			levRobotron.Robotron[iSpheroid].sprRobotron.Direction=levRobotron.Robotron[iSpheroid].sprRobotron.Direction-DIR_EAST+DIR_WEST;
		}
	}
	if (levRobotron.Robotron[iSpheroid].sprRobotron.Direction&DIR_SOUTH)
	{
		//Move south
		if (levRobotron.Robotron[iSpheroid].sprRobotron.yPosition<MAX_Y)
		{
			levRobotron.Robotron[iSpheroid].sprRobotron.yPosition+=gmRobotron.SpheroidSpeed;
		}
		else
		{
			levRobotron.Robotron[iSpheroid].sprRobotron.Direction=levRobotron.Robotron[iSpheroid].sprRobotron.Direction-DIR_SOUTH+DIR_NORTH;
		}
	}
	if (levRobotron.Robotron[iSpheroid].sprRobotron.Direction&DIR_WEST)
	{
		//Go west
		if (levRobotron.Robotron[iSpheroid].sprRobotron.xPosition>MIN_X)
		{
			levRobotron.Robotron[iSpheroid].sprRobotron.xPosition-=gmRobotron.SpheroidSpeed;
		}
		else
		{
			levRobotron.Robotron[iSpheroid].sprRobotron.Direction=levRobotron.Robotron[iSpheroid].sprRobotron.Direction-DIR_WEST+DIR_EAST;
		}
	}

	//Then decide whether to change direction or not

	if (levRobotron.Robotron[iSpheroid].DecisionTimer==levRobotron.Robotron[iSpheroid].Decision)
	{
		//Change one direction randomly.
		levRobotron.Robotron[iSpheroid].DecisionTimer=0;
		switch (((u8)QRandom())>>6)
		{
		case 0:
			if (levRobotron.Robotron[iSpheroid].sprRobotron.Direction&DIR_NORTH)
			{
				levRobotron.Robotron[iSpheroid].sprRobotron.Direction=levRobotron.Robotron[iSpheroid].sprRobotron.Direction-DIR_NORTH+DIR_SOUTH;
			}
			else if (levRobotron.Robotron[iSpheroid].sprRobotron.Direction&DIR_SOUTH)
			{
				levRobotron.Robotron[iSpheroid].sprRobotron.Direction=levRobotron.Robotron[iSpheroid].sprRobotron.Direction-DIR_SOUTH+DIR_NORTH;
			}
			else
			{
				levRobotron.Robotron[iSpheroid].sprRobotron.Direction+=DIR_NORTH;
			}
			break;
		case 1:
			if (levRobotron.Robotron[iSpheroid].sprRobotron.Direction&DIR_WEST)
			{
				levRobotron.Robotron[iSpheroid].sprRobotron.Direction=levRobotron.Robotron[iSpheroid].sprRobotron.Direction-DIR_WEST+DIR_EAST;
			}
			else if (levRobotron.Robotron[iSpheroid].sprRobotron.Direction&DIR_EAST)
			{
				levRobotron.Robotron[iSpheroid].sprRobotron.Direction=levRobotron.Robotron[iSpheroid].sprRobotron.Direction-DIR_EAST+DIR_WEST;
			}
			else
			{
				levRobotron.Robotron[iSpheroid].sprRobotron.Direction+=DIR_EAST;
			}
			break;
		default:
			//Drop an enforcer...
			//We only drop a maximum of 4 enforcers.
			if((levRobotron.Robotron[iSpheroid].Flags&ROBOTRON_SPAWNCOUNT)<ROBOTRON_SPAWNCOUNT)
			{
				iEnforcerLoop=0;
				//Find the next available slot in the robotron list...
				while(iEnforcerLoop<MAX_ROBOTRON)
				{
					if (!(levRobotron.Robotron[iEnforcerLoop].Flags&ROBOTRON_ACTIVE))
					{
						levRobotron.Robotron[iEnforcerLoop].sprRobotron.xPosition=levRobotron.Robotron[iSpheroid].sprRobotron.xPosition;
						levRobotron.Robotron[iEnforcerLoop].sprRobotron.yPosition=levRobotron.Robotron[iSpheroid].sprRobotron.yPosition;
						levRobotron.Robotron[iEnforcerLoop].sprRobotron.Direction=levRobotron.Robotron[iSpheroid].sprRobotron.Direction;
						levRobotron.Robotron[iEnforcerLoop].sprRobotron.Animation=levRobotron.Robotron[iSpheroid].sprRobotron.Animation;
						levRobotron.Robotron[iEnforcerLoop].Type=TYPE_ENFORCER;
						levRobotron.Robotron[iEnforcerLoop].DecisionTimer=0;
						levRobotron.Robotron[iEnforcerLoop].Decision=0;
						levRobotron.Robotron[iEnforcerLoop].Flags=ROBOTRON_ACTIVE;
						levRobotron.EnemyCount++;

						CopySpriteTile((u16*)rtRobotron, levRobotron.Robotron[iEnforcerLoop].sprRobotron.Tile, (levRobotron.Robotron[iEnforcerLoop].Type<<5)+(levRobotron.Robotron[iEnforcerLoop].sprRobotron.Direction<<1)+levRobotron.Robotron[iEnforcerLoop].sprRobotron.Animation);
						SetSprite(levRobotron.Robotron[iEnforcerLoop].Index, levRobotron.Robotron[iEnforcerLoop].sprRobotron.Tile, 0, levRobotron.Robotron[iEnforcerLoop].sprRobotron.xPosition>>7, levRobotron.Robotron[iEnforcerLoop].sprRobotron.yPosition>>7, PAL_ROBOTRON+(u8)levRobotron.Robotron[iEnforcerLoop].Type);

						//Having created a new enforcer, we need to update the spawn count for this
						//Spheroid
						iSpawnCount=levRobotron.Robotron[iSpheroid].Flags&ROBOTRON_SPAWNCOUNT;
						levRobotron.Robotron[iSpheroid].Flags-=iSpawnCount;
						iSpawnCount=(iSpawnCount>>2)+1;
						levRobotron.Robotron[iSpheroid].Flags+=(iSpawnCount<<2);
						iEnforcerLoop=MAX_ROBOTRON;
					}
					iEnforcerLoop++;
				}
			}
			else
			{
				//Once the spheroid has dropped it's load...
				levRobotron.Robotron[iSpheroid].Flags=ROBOTRON_DEAD;
				levRobotron.EnemyCount--;
			}
			break;
		}
		//Make the spheroids quite skittish.
		levRobotron.Robotron[iSpheroid].Decision=((u16)QRandom()<<1);
	}
	levRobotron.Robotron[iSpheroid].DecisionTimer++;
	levRobotron.Robotron[iSpheroid].sprRobotron.Animation^=1;

	//Move the sprite and go home...
	CopySpriteTile((u16*)rtRobotron, levRobotron.Robotron[iSpheroid].sprRobotron.Tile, (levRobotron.Robotron[iSpheroid].Type<<5)+(levRobotron.Robotron[iSpheroid].sprRobotron.Direction<<1)+levRobotron.Robotron[iSpheroid].sprRobotron.Animation);
	SetSpritePosition(levRobotron.Robotron[iSpheroid].Index, levRobotron.Robotron[iSpheroid].sprRobotron.xPosition>>7, levRobotron.Robotron[iSpheroid].sprRobotron.yPosition>>7);

	return levRobotron;
}

void rtRobotronCollision(LEVEL * levRobotron, GAME gmRobotron, PLAYER * sprPlayer)
{
	u8 iRobotronLoop;
	u8 iFamilyLoop;
	u8 iShotLoop;
	u8 iPaletteLoop;
	u8 iCollision;
	u8 iCurrentBlank;

	iCurrentBlank=GetCurrentTimer();

	//Collision Detection

	//We have three types of collision to worry about

	//Collision between Robotron & Shot

	//Collision between Robotron & Family

	//Collision between Robotron & Player

	//Collisions between Robotron & Shot and Robotron & Player can be handled by a single loop
	for (iRobotronLoop=0;iRobotronLoop<=MAX_ROBOTRON;iRobotronLoop++)
	{
		// Needs to be a bit cleverer... Family are dangerous if they have been turned into Progs...
		if 	((((*levRobotron).Robotron[iRobotronLoop].Type>TYPE_MIKEY)&&((*levRobotron).Robotron[iRobotronLoop].Flags&ROBOTRON_ACTIVE))||(((*levRobotron).Robotron[iRobotronLoop].Flags&FAMILY_PROG)&&((*levRobotron).Robotron[iRobotronLoop].Flags&ROBOTRON_ACTIVE)))
		{
			//Only bother with collision detection for enemy robotrons

			//Collision with the player
			iCollision=rtCollision((*levRobotron).Robotron[iRobotronLoop].sprRobotron, (*sprPlayer).sprPlayer);
			if (iCollision==COLLISION_HIT)
			{
				//Do a bit of palette shifting to show the death
				for(iPaletteLoop=0;iPaletteLoop<=128;iPaletteLoop++)
				{
					SetPalette(SPRITE_PLANE, PAL_PLAYER, 0, RGB(iPaletteLoop%16, (iPaletteLoop+8)%16,(iPaletteLoop+12)%16), RGB(iPaletteLoop%16, (iPaletteLoop+8)%16,(iPaletteLoop+12)%16), RGB(iPaletteLoop%16, (iPaletteLoop+8)%16,(iPaletteLoop+12)%16));
					Sleep(1);
				}
				// Reset the family multiplier
				(*sprPlayer).FamilyMultiplier=1;
				// Kill the player
				(*sprPlayer).Flags=PLAYER_DEAD;
			}
			else
			{
				//Collision with the shots
				for (iShotLoop=0;iShotLoop<=MAX_SHOT;iShotLoop++)
				{
					if ((*sprPlayer).Shot[iShotLoop].Flags&SHOT_ACTIVE)
					{
						iCollision=rtCollision((*levRobotron).Robotron[iRobotronLoop].sprRobotron, (*sprPlayer).Shot[iShotLoop].sprShot);
						if (iCollision==COLLISION_HIT)
						{
							//Destroy the shot
							(*sprPlayer).Shot[iShotLoop].Flags=SHOT_INACTIVE;
							(*sprPlayer).Shot[iShotLoop].sprShot.Direction=0;
							CopySpriteTile((u16*)rtShot, (*sprPlayer).Shot[iShotLoop].sprShot.Tile, 0);
							iShotLoop=MAX_SHOT;

							PlaySound(SND_ROBOTDEATH);

							//Decide what to do with the Robotron that we've just hit...
							switch ((*levRobotron).Robotron[iRobotronLoop].Type)
							{
								case TYPE_ELECTRODE:
								{
									(*levRobotron).Robotron[iRobotronLoop].Flags=ROBOTRON_DEAD;
									(*levRobotron).Robotron[iRobotronLoop].sprRobotron.Direction=0;
									CopySpriteTile((u16*)rtRobotron, (*levRobotron).Robotron[iRobotronLoop].sprRobotron.Tile, 0);
									(*sprPlayer).Score += 20;
									break;
								}
								case TYPE_GRUNT:
								{
									(*levRobotron).Robotron[iRobotronLoop].Flags=ROBOTRON_DEAD;
									(*levRobotron).Robotron[iRobotronLoop].sprRobotron.Direction=0;
									CopySpriteTile((u16*)rtRobotron, (*levRobotron).Robotron[iRobotronLoop].sprRobotron.Tile, 0);
									(*levRobotron).EnemyCount--;
									(*sprPlayer).Score += 100;
									break;
								}
								case TYPE_SPHEROID:
								{
									(*levRobotron).Robotron[iRobotronLoop].Flags=ROBOTRON_DEAD;
									(*levRobotron).Robotron[iRobotronLoop].sprRobotron.Direction=0;
									CopySpriteTile((u16*)rtRobotron, (*levRobotron).Robotron[iRobotronLoop].sprRobotron.Tile, 0);
									(*levRobotron).EnemyCount--;
									(*sprPlayer).Score += 200;
									break;
								}
								case TYPE_ENFORCER:
								{
									(*levRobotron).Robotron[iRobotronLoop].Flags=ROBOTRON_DEAD;
									(*levRobotron).Robotron[iRobotronLoop].sprRobotron.Direction=0;
									CopySpriteTile((u16*)rtRobotron, (*levRobotron).Robotron[iRobotronLoop].sprRobotron.Tile, 0);
									(*levRobotron).EnemyCount--;
									(*sprPlayer).Score += 150;
									break;
								}
							 	case TYPE_BRAIN:
								{
									(*levRobotron).Robotron[iRobotronLoop].Flags=ROBOTRON_DEAD;
									(*levRobotron).Robotron[iRobotronLoop].sprRobotron.Direction=0;
									CopySpriteTile((u16*)rtRobotron, (*levRobotron).Robotron[iRobotronLoop].sprRobotron.Tile, 0);
									(*levRobotron).EnemyCount--;
									(*sprPlayer).Score += 500;
									break;
								}
								case TYPE_QUARK:
								{
									(*levRobotron).Robotron[iRobotronLoop].Flags=ROBOTRON_DEAD;
									(*levRobotron).Robotron[iRobotronLoop].sprRobotron.Direction=0;
									CopySpriteTile((u16*)rtRobotron, (*levRobotron).Robotron[iRobotronLoop].sprRobotron.Tile, 0);
									(*levRobotron).EnemyCount--;
									(*sprPlayer).Score += 50;
									break;
								}
								case TYPE_TANK:
								{
									(*levRobotron).Robotron[iRobotronLoop].Flags=ROBOTRON_DEAD;
									(*levRobotron).Robotron[iRobotronLoop].sprRobotron.Direction=0;
									CopySpriteTile((u16*)rtRobotron, (*levRobotron).Robotron[iRobotronLoop].sprRobotron.Tile, 0);
									(*levRobotron).EnemyCount--;
									(*sprPlayer).Score += 1000;
									break;
								}
								case TYPE_TANK_SHOT:
								case TYPE_ENFORCER_SHOT:
								case TYPE_BRAIN_SHOT:
									//Destroy. But don't change enemy count or increase score.
									(*levRobotron).Robotron[iRobotronLoop].Flags=ROBOTRON_DEAD;
									(*levRobotron).Robotron[iRobotronLoop].sprRobotron.Direction=0;
									CopySpriteTile((u16*)rtRobotron, (*levRobotron).Robotron[iRobotronLoop].sprRobotron.Tile, 0);
									break;
								case (TYPE_HULK):
								{
									//Just bounce a bit...
									break;
								}
							}
						}
					}
				}
			}
		}
		else if ((*levRobotron).Robotron[iRobotronLoop].Flags&ROBOTRON_ACTIVE)
		{
			iCollision=rtCollision((*levRobotron).Robotron[iRobotronLoop].sprRobotron, (*sprPlayer).sprPlayer);
			if (iCollision==COLLISION_HIT)
			{
				//It's a family member. Destroy the object and increase the score.
				(*levRobotron).Robotron[iRobotronLoop].Flags=ROBOTRON_DEAD;
				(*levRobotron).Robotron[iRobotronLoop].sprRobotron.Direction=0;
				CopySpriteTile((u16*)rtRobotron, (*levRobotron).Robotron[iRobotronLoop].sprRobotron.Tile, 0);
				(*sprPlayer).Score+=(100 * (*sprPlayer).FamilyMultiplier);
				// Increase the family multiplier up to 10x
				if ((*sprPlayer).FamilyMultiplier == 5)
					(*sprPlayer).FamilyMultiplier=10;
				if ((*sprPlayer).FamilyMultiplier == 3)
					(*sprPlayer).FamilyMultiplier=5;
				if ((*sprPlayer).FamilyMultiplier == 2)
					(*sprPlayer).FamilyMultiplier=3;
				if ((*sprPlayer).FamilyMultiplier == 1)
					(*sprPlayer).FamilyMultiplier=2;
			}
		}
	}

	//Well, bugger me sideways. This appears to work...
	//The idea is that we watch the Vertical Blank and attempt to interrupt the collision checking if
	//it's taking too long. And, it seems to do the job - no noticable slowdown once the essential
	//collisions have been sorted out - and, hopefully, without any change in the accuracy of
	//said collision detection (there shouldn't be - objects will stay in collision for several
	//frames so - as long as everything is tested - there should be no noticable loss in accuracy.
	if (iFamilyCollisionLoop>MAX_ROBOTRON)
	{
		iFamilyCollisionLoop=0;
	}

	//Question is... Do we need to do this in the first loop as well?
	//I think we do.
	while ((iFamilyCollisionLoop<=MAX_ROBOTRON) && (iCurrentBlank==GetCurrentTimer()))
	{
		if ((((*levRobotron).Robotron[iFamilyCollisionLoop].Type==TYPE_HULK) || ((*levRobotron).Robotron[iFamilyCollisionLoop].Type==TYPE_BRAIN)) && ((*levRobotron).Robotron[iFamilyCollisionLoop].Flags&ROBOTRON_ACTIVE))
		{
			//Hulk and Brain Robotron/Family collisions
			//This is one of the things that is really slowing the game down.
			//I need to implement a timer - to pause the game for a while if the collision detection
			//is over quickly, and to interrupt *this* part of the collision detection if it takes
			//too long - and to resume at the same point the next time it comes in...
			//Check for family members
			for (iFamilyLoop=0;iFamilyLoop<=MAX_ROBOTRON;iFamilyLoop++)
			{
				if (((*levRobotron).Robotron[iFamilyLoop].Type<=TYPE_MIKEY) && ((*levRobotron).Robotron[iFamilyLoop].Flags&ROBOTRON_ACTIVE) && !((*levRobotron).Robotron[iFamilyLoop].Flags&FAMILY_PROG))
				{
					iCollision=rtCollision((*levRobotron).Robotron[iFamilyCollisionLoop].sprRobotron, (*levRobotron).Robotron[iFamilyLoop].sprRobotron);
					if (iCollision==COLLISION_HIT)
					{
						//Kill the humanoid or turn it into a Prog
						if ((*levRobotron).Robotron[iFamilyCollisionLoop].Type==TYPE_HULK)
						{
							(*levRobotron).Robotron[iFamilyLoop].Flags=ROBOTRON_DEAD;
							CopySpriteTile((u16*)rtRobotron, (*levRobotron).Robotron[iFamilyLoop].sprRobotron.Tile, 0);
						}
						else
						{
							(*levRobotron).Robotron[iFamilyLoop].Flags=FAMILY_PROG;
							// Change the palette for the family sprite
							// Easiest just to recreate the sprite?
							SetSprite((*levRobotron).Robotron[iFamilyLoop].Index, (*levRobotron).Robotron[iFamilyLoop].sprRobotron.Tile, 0, (*levRobotron).Robotron[iFamilyLoop].sprRobotron.xPosition>>7, (*levRobotron).Robotron[iFamilyLoop].sprRobotron.yPosition>>7, PAL_ROBOTRON+TYPE_PROG);
						}
						(*levRobotron).Robotron[iFamilyLoop].sprRobotron.Direction=0;
					}
				}
			}
		}
		iFamilyCollisionLoop++;
	}

	//Wait for the blank
	while (iCurrentBlank==GetCurrentTimer());
}

void rtLevelWarp(LEVEL * levRobotron, PLAYER * sprPlayer)
{
	u8 iRobotronLoop;

	u8 iShotLoop;
	//Warp in the next level
	//First of all. Let's do the funky robotron screen warp.
	rtClearScreen();

	//Move the player sprite to the centre of the screen.
	(*sprPlayer).sprPlayer.xPosition=CENTRE_X;
	(*sprPlayer).sprPlayer.yPosition=CENTRE_Y;
	(*sprPlayer).sprPlayer.Direction=DIR_SOUTH;
	(*sprPlayer).sprPlayer.Tile=TILEPLAYER;
	//Create the player sprite
	CopySpriteTile((u16*)rtRobotron, (*sprPlayer).sprPlayer.Tile,((*sprPlayer).sprPlayer.Direction<<1)+(*sprPlayer).sprPlayer.Animation);
	SetSprite(SPRITEPLAYER, (*sprPlayer).sprPlayer.Tile, 0, (*sprPlayer).sprPlayer.xPosition>>7, (*sprPlayer).sprPlayer.yPosition>>7, PAL_PLAYER);

	rtDrawLevel();

	for (iRobotronLoop=0;iRobotronLoop<MAX_ROBOTRON;iRobotronLoop++)
	{
		if ((*levRobotron).Robotron[iRobotronLoop].Flags&ROBOTRON_ACTIVE)
		{
			if ((*levRobotron).Robotron[iRobotronLoop].Type<=TYPE_TANK)
			{
				//Only bother doing this for "active" Robtotrons
				(*levRobotron).Robotron[iRobotronLoop].sprRobotron.xPosition=CENTRE_X;
				(*levRobotron).Robotron[iRobotronLoop].sprRobotron.yPosition=CENTRE_Y;
				//Just check to make sure that they're not in the safe zone
				while (((*levRobotron).Robotron[iRobotronLoop].sprRobotron.xPosition>=MIN_SAFE_X) && ((*levRobotron).Robotron[iRobotronLoop].sprRobotron.xPosition<=MAX_SAFE_X) && ((*levRobotron).Robotron[iRobotronLoop].sprRobotron.yPosition>=MIN_SAFE_Y) && ((*levRobotron).Robotron[iRobotronLoop].sprRobotron.yPosition<=MAX_SAFE_Y))
				{
					(*levRobotron).Robotron[iRobotronLoop].sprRobotron.xPosition=MIN_X+((u16)QRandom()<<6);
					(*levRobotron).Robotron[iRobotronLoop].sprRobotron.yPosition=MIN_Y+((u16)QRandom()<<6);
				}
				//And the Robotrons...
				CopySpriteTile((u16*)rtRobotron, (*levRobotron).Robotron[iRobotronLoop].sprRobotron.Tile, ((*levRobotron).Robotron[iRobotronLoop].Type<<5)+((*levRobotron).Robotron[iRobotronLoop].sprRobotron.Direction<<1)+(*levRobotron).Robotron[iRobotronLoop].sprRobotron.Animation);
				SetSprite(SPRITEROBOTRON+iRobotronLoop, (*levRobotron).Robotron[iRobotronLoop].sprRobotron.Tile, 0, (*levRobotron).Robotron[iRobotronLoop].sprRobotron.xPosition>>7, (*levRobotron).Robotron[iRobotronLoop].sprRobotron.yPosition>>7, PAL_ROBOTRON+(u8)(*levRobotron).Robotron[iRobotronLoop].Type);
			}
		}
	}

	//Reset all shots
	for (iShotLoop=0;iShotLoop<MAX_SHOT;iShotLoop++)
	{
		(*sprPlayer).Shot[iShotLoop].sprShot.xPosition=0;
		(*sprPlayer).Shot[iShotLoop].sprShot.yPosition=0;
		(*sprPlayer).Shot[iShotLoop].sprShot.Tile=TILESHOT+iShotLoop;
		(*sprPlayer).Shot[iShotLoop].Flags=SHOT_INACTIVE;
		(*sprPlayer).Shot[iShotLoop].sprShot.Direction=0;
		CopySpriteTile((u16*)rtShot, (*sprPlayer).Shot[iShotLoop].sprShot.Tile, 0);
		SetSprite(SPRITESHOT+iShotLoop, TILESHOT+iShotLoop, 0, 0, 0, PAL_SHOT);
	}
}

void ClearSprites()
{
	u8 iLoop;

	for (iLoop=0;iLoop<=MAX_SPRITE;iLoop++)
	{
		SetSprite(iLoop, 0, 0, 0, 0, 0);
	}
}

void rtClearScreen()
{
	//Do the funky Robotron screen clear...

	const unsigned short PaletteMap[8] = {RGB(15,0,0), RGB(0,15,0), RGB(0,0,15), RGB(0,0,0), RGB(15,0,15), RGB(15,15,0), RGB(0,15,15),RGB(15,15,15)};

	u8 iLoopWarp;
	u8 iLoopY;
	u8 iLoopX;
	u8 iLoopPalette;
	u8 iPalette;

	InstallTileSetAt(rtBorder, sizeof(rtBorder)/2, BorderTileBase);

	ClearSprites();

	PlaySound(SND_SIREN);

	//From the centre
	for(iLoopWarp=0;iLoopWarp<=8;iLoopWarp++)
	{
		//Shift the palette
		for(iLoopPalette=0;iLoopPalette<=iLoopWarp;iLoopPalette++)
		{
			//Work out the palette position (LoopWarp Mod 8)+LoopPalette
			iPalette=(iLoopWarp % 8)+iLoopPalette;
			if(iPalette>=8) iPalette-=8;
			SetPalette(SCR_1_PLANE, PAL_CLEAR+8-iLoopPalette, 0, PaletteMap[iPalette], RGB(0,0,0), RGB(0,0,0));
		}
		//Draw the next set of blocks
		iLoopX=10-iLoopWarp;
		iLoopY=9-iLoopWarp;
		for(;iLoopX<=11+iLoopWarp;iLoopX++)
		{
			PutTile(SCR_1_PLANE, PAL_CLEAR+iLoopWarp, iLoopX-1, iLoopY-1, BorderTileBase+rtBorderBlock);
		}
		for(;iLoopY<=10+iLoopWarp;iLoopY++)
		{
			PutTile(SCR_1_PLANE, PAL_CLEAR+iLoopWarp, iLoopX-1, iLoopY-1, BorderTileBase+rtBorderBlock);
		}
		for(;iLoopX>=10-iLoopWarp;iLoopX--)
		{
			PutTile(SCR_1_PLANE, PAL_CLEAR+iLoopWarp, iLoopX-1, iLoopY-1, BorderTileBase+rtBorderBlock);
		}
		for(;iLoopY>=9-iLoopWarp;iLoopY--)
		{
			PutTile(SCR_1_PLANE, PAL_CLEAR+iLoopWarp, iLoopX-1, iLoopY-1, BorderTileBase+rtBorderBlock);
		}
		Sleep(3);
	}
	for(iLoopWarp=0;iLoopWarp<=16;iLoopWarp++)
	{
		//Shift the palette
		for(iLoopPalette=0;iLoopPalette<=iLoopWarp;iLoopPalette++)
		{
			iPalette=(iLoopWarp % 8)+iLoopPalette;
			if(iPalette>=8) iPalette-=8;
			SetPalette(SCR_1_PLANE, PAL_CLEAR+8-iLoopPalette, 0, PaletteMap[iPalette], RGB(0,0,0), RGB(0,0,0));
		}
		Sleep(3);
	}
	//And then wipe from the centre...
	for(iLoopWarp=0;iLoopWarp<=8;iLoopWarp++)
	{
		//Draw the next set of blocks
		iLoopX=10-iLoopWarp;
		iLoopY=9-iLoopWarp;
		for(;iLoopX<=11+iLoopWarp;iLoopX++)
		{
			PutTile(SCR_1_PLANE, PAL_DEFAULT, iLoopX-1, iLoopY-1, BorderTileBase+rtBorderNull);
		}
		for(;iLoopY<=10+iLoopWarp;iLoopY++)
		{
			PutTile(SCR_1_PLANE, PAL_DEFAULT, iLoopX-1, iLoopY-1, BorderTileBase+rtBorderNull);
		}
		for(;iLoopX>=10-iLoopWarp;iLoopX--)
		{
			PutTile(SCR_1_PLANE, PAL_DEFAULT, iLoopX-1, iLoopY-1, BorderTileBase+rtBorderNull);
		}
		for(;iLoopY>=9-iLoopWarp;iLoopY--)
		{
			PutTile(SCR_1_PLANE, PAL_DEFAULT, iLoopX-1, iLoopY-1, BorderTileBase+rtBorderNull);
		}
		Sleep(3);
	}

}