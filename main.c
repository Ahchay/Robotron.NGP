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
			while (!(JOYPAD&J_A));
			PlaySound(iLoop);
			//Don't start again until the player releases the A button
			while (JOYPAD&J_A);
		}
	}

	//Create system palette
	rtCreatePalette();

	// Set default game parameters. Basically, speed of enemies.
	// These could increase over time and/or with the difficulty?
	// Will be exposed as a hidden menu under the "OPTION" button
	// within the attract mode
	gRobotron.Difficulty=1;
	gRobotron.ShotSpeed=128; //One pixel per frame
	gRobotron.PlayerSpeed=64;
	gRobotron.GruntSpeed=16;
	gRobotron.HulkSpeed=8;
	gRobotron.FamilySpeed=4;
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

	//gRobotron.HighScoreTable={{"ELX",10000},{"EUG",8000},{"AKA",8000},{"TSB",8000},{"BOF",8000},{"KOW",8000},{"RKY",8000},{"MOM",8000},{"DAD",8000},{"MKY",8000}};
	gRobotron.HighScoreTable[0].HeroInitials = "ELX";

	while(1)
	{
		ClearSprites();

		gRobotron=rtAttractMode(gRobotron);

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

		// work out if we have a high score?
		PrintString(SCR_1_PLANE, PAL_BORDER, 8, 8, "GAME OVER");
		PrintString(SCR_1_PLANE, PAL_BORDER, 7, 10, "FINAL SCORE");
		PrintDecimal(SCR_1_PLANE, PAL_BORDER, 8, 11, sprPlayer.Score, 8);

		while (!(JOYPAD&J_A));
		while (JOYPAD&J_A);

	}
}