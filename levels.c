//Level definition

//{PLAYER, MOM, DAD, MIKEY, HULK, GRUNT, SPHEROID, ENFORCER, BRAIN, QUARK, TANK}
//PLAYER *must* equal zero.
//ENFORCER & TANK should always start at zero (they're generated by SPHEROID and QUARK 'trons)

const unsigned char rtLevel[40][12]=
{
//	{PLAYER,	MOM,	DAD,	MIKEY,	ELECTRODE,	HULK,	GRUNT,	SPHEROID,	ENFORCER,	BRAIN,	QUARK,	TANK}
{0,1,1,0,3,0,15,0,0,0,0,0},
{0,1,1,1,9,5,17,1,0,0,0,0},
{0,2,2,2,12,5,17,2,0,0,0,0},
{0,1,1,1,9,4,21,2,0,0,0,0},
{0,9,0,1,8,0,13,1,0,9,0,0},
{0,2,2,2,9,4,19,2,0,0,0,0},
{0,4,4,4,0,12,0,0,0,0,10,0},
{0,2,2,2,8,4,19,3,0,0,0,0},
{0,2,2,2,0,2,31,3,0,0,0,0},
{0,0,11,0,6,0,13,1,0,10,0,0},
{0,2,2,2,8,4,19,3,0,0,0,0},
{0,3,3,3,0,13,0,0,0,0,12,0},
{0,2,2,2,8,4,19,3,0,0,0,0},
{0,3,3,3,2,12,16,1,0,0,0,0},
{0,0,0,11,6,1,12,0,0,10,0,0},
{0,2,2,2,9,2,21,3,0,0,0,0},
{0,3,3,3,0,14,0,0,0,0,12,0},
{0,2,2,2,8,4,19,3,0,0,0,0},
{0,1,1,1,0,1,32,2,0,0,0,0},
{0,4,4,4,5,1,11,1,0,11,0,0},
{0,2,2,2,8,4,19,3,0,0,0,0},
{0,3,3,3,0,15,0,0,0,0,12,0},
{0,2,2,2,8,4,19,3,0,0,0,0},
{0,3,3,3,0,13,0,6,0,0,7,0},
{0,12,0,0,6,0,12,0,0,10,0,0},
{0,2,2,2,8,4,19,3,0,0,0,0},
{0,3,3,3,0,16,0,0,0,0,12,0},
{0,2,2,2,8,4,19,3,0,0,1,0},
{0,1,1,1,0,2,32,2,0,0,0,0},
{0,0,11,0,7,0,11,0,0,10,0,0},
{0,2,2,2,8,4,19,3,0,0,1,0},
{0,3,3,3,0,16,0,0,0,0,13,0},
{0,2,2,2,8,4,19,3,0,0,1,0},
{0,2,2,2,0,15,18,1,0,0,1,0},
{0,0,0,11,4,1,12,0,0,10,1,0},
{0,2,2,2,8,4,19,3,0,0,1,0},
{0,3,3,3,0,16,0,0,0,0,14,0},
{0,2,2,2,8,4,19,3,0,0,1,0},
{0,1,1,1,0,2,32,2,0,0,0,0},
{0,4,4,4,4,1,12,0,0,10,0,0}
};