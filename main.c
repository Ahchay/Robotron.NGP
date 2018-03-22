#include "ngpc.h"
#include "carthdr.h"
#include "library.h"
#include "robotron.h"

// Sound effects
// Blatantly stolen from other peoples games... Sorry...
const SOUNDEFFECT rtSounds[NUM_SOUNDS] = {
	// Channel, Length, Repeat, InitialTone;  ToneStep, ToneSpeed, ToneOWB, ToneLowerLimit, ToneUpperLimit, InitialVol, VolStep, VolSpeed, VolOWB, VolLowerLimit, VolUpperLimit
	{ 0x01, 0x04, 0, 0x1F0, 0x10, 0x01, 0x02, 0x80, 0x80, 0x0f, 0,0,0,0,0 }, // SND_SHOOT
	{ 0x02, 0x20, 0, 0xE0, 0x10, 0x01, 0x01, 0x44, 0x82, 0x0f, 0,0,0,0,0 }, //SND_FADE
	{ 0x03, 0x01, 0, 0xE0, 0x00, 0x01, 0x01, 0x44, 0x82, 0x0f, 0,0,0,0,0 }, //SND_THUD
    { 0x00, 0x35, 0, 0x80, 0x08, 0x01, 0x02, 0x40, 0x80, 0x0f, 0,0,0,0,0 }, //SND_PLAYERDEATH
    { 0x00, 0x10, 0, 0x60, 0x00, 0x01, 0x01, 0x44, 0x82, 0x0f, 0,0,0,0,0 }, //SND_ROBOTDEATH
    { 0x01, 0x10, 0, 0x70, 0x04, 0x01, 0x00, 0x44, 0x82, 0x0f, 0,0,0,0,0 }, //SND_PLAYERSHOT
    { 0x01, 0x10, 0, 0x350, 0x04, 0x02, 0x00, 0x44, 0x82, 0x0f, 0,0,0,0,0 }, //SND_ROBOTSHOT
	{ 0x01, 0x60, 0, 0x60, 0x08, 0x01, 0x02, 0x40, 0x80, 0x0f, 0,0,0,0,0 }, // SND_SIREN
	{ 0x02, 0x40, 0, 0x80, 0x20, 0x01, 0x01, 0x44, 0x82, 0x0f, 0,0,0,0,0 } // SND_CHIRP
};

const char rtSoundName[NUM_SOUNDS][16] = {"SND_SHOOT","SND_FADE","SND_THUD","SND_PLAYERDEATH","SND_ROBOTDEATH","SND_PLAYERSHOT","SND_ROBOTSHOT","SND_SIREN","SND_CHIRP"};

void main()
{

	PLAYER sprPlayer;
	LEVEL levRobotron;
	GAME gRobotron;
	u8 iLoop;
	u16 iAttractFrame;
	u8 iScoreLoop;
	HIGHSCOREENTRY hstSwapScore;
	HIGHSCOREENTRY hstSwapScoreLast;
	HIGHSCOREENTRY hstRobotron[HIGH_SCORE_TABLE_SIZE]={{"EUG",50000},{"TSB",40000},{"BOF",30000},{"AKA",20000},{"KOW",10000},{"ROK",5000},{"MOM",4000},{"DAD",3000},{"MKY",1000},{"ROB",0}};

	InitNGPC();
	SysSetSystemFont();

	InitialiseQRandom();

	//Neotracker
	//NeoTracker_InstallDriver();
	InstallSoundDriver();
	InstallSounds(rtSounds, NUM_SOUNDS);

	//Williams rug pattern
	rtInitialise();

	// Hold down the Option button for Sound test...
	if(JOYPAD&J_OPTION)
	{
		//Quick sound test... Press A to cycle through...
		for(iLoop=1;iLoop<=NUM_SOUNDS;iLoop++)
		{
			PrintDecimal(SCR_1_PLANE,0,0,1,iLoop,2);
			PrintString(SCR_1_PLANE,0,0,0,"               ");
			PrintString(SCR_1_PLANE,0,0,0,rtSoundName[iLoop-1]);
			while (JOYPAD&J_A);
			PlaySound(iLoop);
			//Don't start again until the player releases the A button
			while (!(JOYPAD&J_A));
		}
	}

	//Create system palette
	rtCreatePalette();

	// Set default game parameters. Basically, speed of enemies.
	// These could increase over time and/or with the difficulty?
	// Will be exposed as a hidden menu under the "OPTION" button
	// within the attract mode. Maybe. Eventually.
	gRobotron.Difficulty=1;
	gRobotron.ShotSpeed=128; //One pixel per frame
	gRobotron.PlayerSpeed=64;
	gRobotron.GruntSpeed=16;
	gRobotron.HulkSpeed=8;
	gRobotron.FamilySpeed=4;
	gRobotron.ProgSpeed=64;
	gRobotron.SpheroidSpeed=48;
	gRobotron.EnforcerSpeed=48;
	gRobotron.EnforcerShotSpeed=48;
	gRobotron.BrainSpeed=6;
	gRobotron.BrainShotSpeed=6;
	gRobotron.TankSpeed=96;
	gRobotron.TankShotSpeed=96;
	gRobotron.QuarkSpeed=64;
	gRobotron.ShotFrequency=2048;
	gRobotron.Level=0;

	iAttractFrame=0;

	while(1)
	{
		ClearSprites();

		// Need to pass in the High Score Table as well...
		gRobotron=rtAttractMode(gRobotron, hstRobotron, iAttractFrame, sprPlayer.Score);

		//And create our level
		levRobotron=rtCreateLevel(gRobotron.Level);

		//Setup our hero
		sprPlayer=rtCreatePlayer();

		while (sprPlayer.Lives>0)
		{

			while ((sprPlayer.Lives>0) && (levRobotron.EnemyCount>0))
			{
 				//Warp the level in
				rtLevelWarp(&levRobotron, &sprPlayer);

				while ((sprPlayer.Flags==0) && (levRobotron.EnemyCount>0))
				{
					//Get Input
					sprPlayer=rtMovePlayer(sprPlayer, gRobotron);

					//Move enemies
					levRobotron=rtMoveRobotrons(levRobotron, gRobotron, sprPlayer);

					PlaySound(SND_THUD);
					//Collisions (also handles the VBLANK)
					rtRobotronCollision(&levRobotron, gRobotron, &sprPlayer);

					// Show score
					PrintDecimal(SCR_1_PLANE, PAL_BORDER, 1, 0, sprPlayer.Score, 8);
				}
				//Is the player dead? Or is it the end of the level?
				//The excitement mounts...
				if (sprPlayer.Flags==0)
				{
					//End level
					// Need to check for bounds here... If it goes over 40, loop back to 21...
					gRobotron.Level++;
					if (gRobotron.Level>40)
						gRobotron.Level=21;

					//And create our level
					levRobotron=rtCreateLevel(gRobotron.Level);
				}
				else
				{
					Sleep(5);
					//Reset the player flags
					sprPlayer.Flags=0;
					sprPlayer.Lives--;
				}
			}
		}

		//Game Over

		rtClearScreen();

		// work out if we have a high score and inject into the high score table if we do...
		for (iScoreLoop=0;iScoreLoop<HIGH_SCORE_TABLE_SIZE;iScoreLoop++)
		{
			if (sprPlayer.Score>hstRobotron[iScoreLoop].Score)
			{
				// Shuffle all lower scores down and inject new score into position
				hstSwapScoreLast=hstRobotron[iScoreLoop];
				hstRobotron[iScoreLoop]=rtEnterInitials(sprPlayer.Score);
				for (iScoreLoop++;iScoreLoop<HIGH_SCORE_TABLE_SIZE;iScoreLoop++)
				{
					hstSwapScore=hstRobotron[iScoreLoop];
					hstRobotron[iScoreLoop]=hstSwapScoreLast;
					hstSwapScoreLast=hstSwapScore;
				}
			}
		}

		// Wait for the A button to be released...
		while (JOYPAD&J_A);

		iAttractFrame=600;

	}
}