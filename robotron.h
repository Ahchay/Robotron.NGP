#define MAX_ROBOTRON 50
#define MAX_SHOT 5
#define MAX_SPRITE 63
#define HIGH_SCORE_TABLE_SIZE 10

typedef struct Sprite
{
	u16 xPosition;
	u16 yPosition;
	u16 Tile;
	u16 Animation;
	u16 Direction;
} SPRITE;

typedef struct Laser
{
	u8 Index;
	SPRITE sprShot;
	u8 Flags;
} LASER;

typedef struct Player
{
	u8 Index;
	SPRITE sprPlayer;
	u8 Lives;
	u8 FamilyMultiplier;
	u8 Flags;
	u16 Score;
	u8 ShotDirection;
	u16 ShotTimer;
	u8 ShotCount;
	u16 KeyState;
	LASER Shot[MAX_SHOT];
} PLAYER;

typedef struct Robotron
{
	u8 Index;
	SPRITE sprRobotron;
	u16 Type;
	u8 Flags;
	u16 DecisionTimer;
	u16 Decision;
} ROBOTRON;

typedef struct Level
{
	u8 EnemyCount;
	ROBOTRON Robotron[MAX_ROBOTRON];
} LEVEL;

typedef struct HighScoreEntry
{
	char Initials[3];
	u16 Score;
} HIGHSCOREENTRY;

typedef struct Game
{
	u8 Difficulty;
	u8 Level;
	u16 ShotSpeed;
	u16 PlayerSpeed;
	u16 GruntSpeed;
	u16 HulkSpeed;
	u16 FamilySpeed;
	u16 ProgSpeed;
	u16 SpheroidSpeed;
	u16 EnforcerSpeed;
	u16 EnforcerShotSpeed;
	u16 BrainSpeed;
	u16 BrainShotSpeed;
	u16 QuarkSpeed;
	u16 TankSpeed;
	u16 TankShotSpeed;
	u16 ShotFrequency;
} GAME;

#define GeneralTileBase 128
#define BorderTileBase 128
#define SpriteTileBase 256
#define LogoTileBase 144
#define NGPCLogoTileBase 140
#define BlogLogoTileBase 128

#define COLLISION_MISSED 0
#define COLLISION_HIT 1

#define PAL_DEFAULT 0
#define PAL_BORDER 2
#define PAL_NGPCLOGO 2
#define PAL_LOGO 3
#define PAL_ATTRACTTEXT 4
#define PAL_LIVES 5
#define PAL_PLAYER 1
#define PAL_SHOT 2
#define PAL_ROBOTRON 3
#define PAL_CLEAR 0

//Robotron (sprite really) order is important.
//First we have the human family/Progs
//A prog is "just" going to be a palette shifted family...
#define TYPE_PLAYER 0
#define TYPE_MOM 1
#define TYPE_DAD 2
#define TYPE_MIKEY 3
//Electrodes
#define TYPE_ELECTRODE 4
//Then we have the indestructible Robotron type
#define TYPE_HULK 5
//And finally, we have the normal Robotron types (which count towards level completion)
#define TYPE_GRUNT 6
#define TYPE_SPHEROID 7
#define TYPE_ENFORCER 8
#define TYPE_BRAIN 9
#define TYPE_QUARK 10
#define TYPE_TANK 11

//Followed by the Robotron shot types (these might have to share a palette, and will be used for Progs too)
#define TYPE_ENFORCER_SHOT 12
#define TYPE_TANK_SHOT 13
#define TYPE_BRAIN_SHOT 14
#define TYPE_PROG 12

#define TILEPLAYER SpriteTileBase
#define TILESHOT SpriteTileBase+1
#define TILEROBOTRON TILESHOT+1+MAX_SHOT
#define TILEATTRACT 16

#define SPRITEPLAYER 0
#define SPRITESHOT 1
#define SPRITEROBOTRON SPRITESHOT+1+MAX_SHOT

//Flags. These will be used by various sprite types to set active/inactive/dead/etc
//They will act as bitwise indicators into the sprite.Flags property so can be added up...
#define SHOT_INACTIVE 0
#define SHOT_ACTIVE 1

#define FAMILY_PROG 4

#define PLAYER_DEAD 1

#define ROBOTRON_ACTIVE 1
#define ROBOTRON_DEAD 2

// Flags finished

#define ROBOTRON_SPAWNCOUNT 12

#define DIR_NORTH 1
#define DIR_EAST 2
#define DIR_SOUTH 4
#define DIR_WEST 8

#define MIN_X 640
#define MAX_X 18944
#define MIN_Y 2048
#define MAX_Y 18048

#define ATTRACT_X 1280
#define ATTRACT_Y 12288

#define CENTRE_X 9792
#define CENTRE_Y 10048

#define MIN_SAFE_X 5696
#define MAX_SAFE_X 13888
#define MIN_SAFE_Y 5952
#define MAX_SAFE_Y 14144

//SFX enum. Definitions loaded in main.c
enum
{
   SND_SHOOT = 1, // Pocketron
   SND_FADE,
   SND_THUD,
   SND_PLAYERDEATH, // Kerzrobo
   SND_ROBOTDEATH,
   SND_PLAYERSHOT,
   SND_ROBOTSHOT,
   SND_SIREN, // Ivan
   SND_CHIRP,
   NUM_SOUNDS = SND_CHIRP
};

//Function defines

u8 rtCollision(SPRITE sprPlayer, SPRITE sprRobotron);
void rtCreatePalette();
void CopySpriteTile(u16 * SpriteTiles, u16 TileNumber, u16 AnimNumber);
void rtInitialise();
GAME rtAttractMode(GAME gmRobotron, HIGHSCOREENTRY hstRobotron[], u16 StartFrame, u16 LastScore);
HIGHSCOREENTRY rtEnterInitials(u16 Score);
void rtCreatePalette();
PLAYER rtCreatePlayer();
LEVEL rtCreateLevel(u8 LevelNumber);
PLAYER rtMovePlayer(PLAYER sprPlayer, GAME gmRobotron);
void rtDrawLevel(u8 iLives);
LEVEL rtMoveRobotrons(LEVEL levRobotron, GAME gmRobotron, PLAYER sprPlayer);
ROBOTRON rtMoveElectrode(ROBOTRON rtElectrode, GAME gmRobotron, PLAYER sprPlayer);
ROBOTRON rtMoveGrunt(ROBOTRON rtGrunt, GAME gmRobotron, PLAYER sprPlayer);
ROBOTRON rtMoveHulk(ROBOTRON rtHulk, GAME gmRobotron, PLAYER sprPlayer);
ROBOTRON rtMoveFamily(ROBOTRON rtFamily, GAME gmRobotron, PLAYER sprPlayer);
ROBOTRON rtMoveProg(ROBOTRON rtProg, GAME gmRobotron, PLAYER sprPlayer);
LEVEL rtMoveSpheroid(u8 iSpheroid, LEVEL levRobotron, GAME gmRobotron, PLAYER sprPlayer);
LEVEL rtMoveEnforcer(u8 iEnforcer, LEVEL levRobotron, GAME gmRobotron, PLAYER sprPlayer);
LEVEL rtMoveBrain(u8 iBrain, LEVEL levRobotron, GAME gmRobotron, PLAYER sprPlayer);
LEVEL rtMoveQuark(u8 iQuark, LEVEL levRobotron, GAME gmRobotron, PLAYER sprPlayer);
LEVEL rtMoveTank(u8 iTank, LEVEL levRobotron, GAME gmRobotron, PLAYER sprPlayer);
ROBOTRON rtMoveEnforcerShot(ROBOTRON rtEnforcerShot, GAME gmRobotron, PLAYER sprPlayer);
ROBOTRON rtMoveTankShot(ROBOTRON rtTankShot, GAME gmRobotron, PLAYER sprPlayer);
ROBOTRON rtMoveBrainShot(ROBOTRON rtBrainShot, GAME gmRobotron, PLAYER sprPlayer);
void rtRobotronCollision(LEVEL * levRobotron, GAME gmRobotron, PLAYER * sprPlayer);
void rtLevelWarp(LEVEL * levRobotron, PLAYER * sprPlayer);
void ClearSprites();
void rtClearScreen();
