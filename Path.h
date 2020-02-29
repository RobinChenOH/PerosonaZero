#pragma once

struct MyObjectBuilder {
	char *path;
	int width;
	int height;
	int x_frame;
	int y_frame;
};

static MyObjectBuilder nullobj{ NULL,0,0,1,1 };

static MyObjectBuilder player_prepare{ "Image\\player\\prepare.bmp",2480, 666 ,10,2 };
static MyObjectBuilder player_run{ "Image\\player\\run.bmp",4400, 800, 11, 2 };
static MyObjectBuilder player_dead{ "Image\\player\\dead.bmp",2412, 512, 7, 2 };
static MyObjectBuilder player_curse{ "Image\\player\\curse3.bmp",2520, 720, 7, 2 };
static MyObjectBuilder player_attack{ "Image\\player\\attack.bmp",6000, 720, 15, 2 };
static MyObjectBuilder player_defend{ "Image\\player\\defend.bmp",2000, 800, 5, 2 };

static MyObjectBuilder item_drop{ "Image\\UI\\item_disposed.bmp",112,200,1,2 };
static MyObjectBuilder quin{ "Image\\UI\\quin.bmp",100,200,1,2 };
static MyObjectBuilder kill{ "Image\\SpecialEffects\\killt.bmp",1024,1024,4,5 };
static MyObjectBuilder critical{ "Image\\UI\\criticals.bmp",909,108,6,2 };

static MyObjectBuilder levelupbmp{ "Image\\UI\\levelup.bmp" ,238, 153, 1, 1 };
static MyObjectBuilder scene0{ "Image\\UI\\levelupbgt.bmp" ,12000, 640, 10, 1 };
static MyObjectBuilder scene1{ "Image\\map\\first.bmp" ,3689, 640, 1, 1 };
static MyObjectBuilder scene2{ "Image\\map\\second.bmp" ,3790, 640, 1, 1 };
static MyObjectBuilder scene3{ "Image\\map\\third.bmp" ,3723, 640, 1, 1 };

static MyObjectBuilder zombie_image[10] = {
	{ "Image\\512\\m\\m3walk.bmp" ,1600,400,8,2 },
	{ "Image\\512\\m\\m3attack.bmp" ,800,400,4,2 },
	{ "Image\\512\\m\\m3dead.bmp" ,800,400,4,2 },
	{ "Image\\512\\m\\m3walkfire.bmp" ,1600,400,8,2 },
	{ "Image\\512\\m\\m3walkarcane.bmp" ,1600,400,8,2 },
	{ "Image\\512\\m\\m3walkfrost.bmp" ,1600,400,8,2 },
	{ "Image\\512\\m\\m3walkelectricity.bmp" ,1600,400,8,2 }
};

static MyObjectBuilder mummy_image[10] = {
	{ "Image\\512\\m\\m4walk.bmp" ,400,400,2,2 },
	{ "Image\\512\\m\\m4waa.bmp" ,1200,400,6,2 },
	{ "Image\\512\\m\\m4dead.bmp" ,800,400,4,2 },
	{ "Image\\512\\m\\m4waafire.bmp" ,1200,400,6,2 },
	{ "Image\\512\\m\\m4waaarcane.bmp" ,1200,400,6,2 },
	{ "Image\\512\\m\\m4waafrost.bmp" ,1200,400,6,2 },
	{ "Image\\512\\m\\m4waaelectricity.bmp" ,1200,400,6,2 }
};

static MyObjectBuilder gargoyles_image[10] = {
	{ "Image\\512\\m\\m5walk.bmp" ,800,400,4,2 },
	{ "Image\\512\\m\\m5attack.bmp" ,800,400,4,2 },
	{ "Image\\512\\m\\m5dead.bmp" ,800,400,4,2 },
	{ "Image\\512\\m\\m5walkfire.bmp" ,1600,400,8,2 },
	{ "Image\\512\\m\\m5walkarcane.bmp" ,1600,400,8,2 },
	{ "Image\\512\\m\\m5walkfrost.bmp" ,1600,400,8,2 },
	{ "Image\\512\\m\\m5walkelectricity.bmp" ,1600,400,8,2 }
};

static MyObjectBuilder cattle_image[10] = {
	{ "Image\\512\\m\\m2walk.bmp" ,400,400,2,2 },
	{ "Image\\512\\m\\m2attack.bmp" ,1200,400,6,2 },
	{ "Image\\512\\m\\m2dead.bmp" ,800,400,4,2 },
	{ "Image\\512\\m\\m2walkfire.bmp" ,1600,400,8,2 },
	{ "Image\\512\\m\\m2walkarcane.bmp" ,1600,400,8,2 },
	{ "Image\\512\\m\\m2walkfrost.bmp" ,1600,400,8,2 },
	{ "Image\\512\\m\\m2walkelectricity.bmp" ,1600,400,8,2 }
};

static MyObjectBuilder boss_image[10] = {
	{ "Image\\monster\\boss1walk.bmp",2640,800,12,2 },
	{ "Image\\monster\\boss2.bmp",3000,800,10,2 },
	{ "Image\\monster\\boss1dead.bmp",3150,600,7,2 },
	{ "Image\\monster\\boss1walk.bmp",2640,800,12,2 },
	{ "Image\\monster\\boss1walk.bmp",2640,800,12,2 },
	{ "Image\\monster\\boss1walk.bmp",2640,800,12,2 },
	{ "Image\\monster\\boss1walkelectro.bmp",2640,800,12,2 }
};

static MyObjectBuilder boss1_debut{ "Image\\monster\\boss.bmp",5906,750,18,2 };
static MyObjectBuilder boss1_attack{ "Image\\monster\\boss2.bmp",3000,800,10,2 };
static MyObjectBuilder boss1_walk{ "Image\\monster\\boss1walk.bmp",2640,800,12,2 };
static MyObjectBuilder boss1_dead{ "Image\\monster\\boss1dead.bmp",3150,600,7,2 };

static MyObjectBuilder start_bg{ "Image\\UI\\UI.bmp",1500,720,1,1 };
static MyObjectBuilder gameover_bg{ "Image\\UI\\gameover.bmp",1500,640,1,1 };
static MyObjectBuilder gameinfo_bg{ "Image\\UI\\gameinfo.bmp",1500,640,1,1 };
static MyObjectBuilder inventory_bg{ "Image\\UI\\inventory.bmp",1500,640,1,1 };
static MyObjectBuilder dagger{ "Image\\player\\weapon\\dagger.bmp",300,600,1,2 };
static MyObjectBuilder tsunami{ "Image\\player\\weapon\\tsunami.bmp",600,640,1,2 };
static MyObjectBuilder shortblade{ "Image\\player\\weapon\\shortblade.bmp",500,1000,1,2 };
static MyObjectBuilder empblade{ "Image\\player\\weapon\\empblade.bmp",4800,640,8,2 };
static MyObjectBuilder uchigatana{ "Image\\player\\weapon\\uchigatana.bmp",600,700,1,2 };
static MyObjectBuilder longblade{ "Image\\player\\weapon\\longblade.bmp",3600,640,6,2 };
static MyObjectBuilder condemn{ "Image\\player\\weapon\\condemn.bmp",3000,600,10,2 };
static MyObjectBuilder moonblade{ "Image\\player\\weapon\\moonblade.bmp",1890,640,5,2 };
static MyObjectBuilder frostheart{ "Image\\player\\weapon\\frostheart.bmp",3600,640,6,2 };
static MyObjectBuilder electroblade{ "Image\\player\\weapon\\electroblade.bmp",5520,700,16,2 };
static MyObjectBuilder fireblade{ "Image\\player\\weapon\\fireblade.bmp",5625,650,15,2 };
static MyObjectBuilder starblade{ "Image\\player\\weapon\\starblade.bmp",7000,600,20,2 };

static MyObjectBuilder Missile[8] = {
	{ "Image\\SpecialEffects\\fireball.bmp",3000, 300 ,15,2 },
	{ "Image\\SpecialEffects\\ball2.bmp",3135, 332 ,11,2 },
	{ "Image\\SpecialEffects\\slash.bmp",1601, 400 ,8,2 },
	{ "Image\\SpecialEffects\\electricityball.bmp",2048, 256 ,16,2 },
	{ "Image\\SpecialEffects\\ball3.bmp",1425,332,5,2 },
	{ "Image\\SpecialEffects\\ball3.bmp",1425,332,5,2 },
	{ "Image\\SpecialEffects\\slashwork.bmp",599, 400 ,3,2 },
	{ "Image\\SpecialEffects\\ball3.bmp",1425,332,5,2 }
};

static MyObjectBuilder Ray[4] = {
	{ "Image\\SpecialEffects\\fireray.bmp",2500,50,3,2 },
	{ "Image\\SpecialEffects\\arcaneray.bmp",2560,332,4,2 },
	{ "Image\\SpecialEffects\\skillx.bmp",4480,440,7,2 },
	{ "Image\\SpecialEffects\\lightening3.bmp",4648,332,7,2 }
};

static MyObjectBuilder Starstrike[8] = {
	{ "Image\\SpecialEffects\\star.bmp",996, 332,6,2 },
	{ "Image\\SpecialEffects\\arcanestar.bmp",900, 200,9,2 },
	{ "Image\\SpecialEffects\\froststar.bmp",1480, 382,10,2 },
	{ "Image\\SpecialEffects\\electricitystar.bmp",1896, 1000,6,2 },
	{ "Image\\SpecialEffects\\firestarwork.bmp",2750, 200,11,2 },
	{ "Image\\SpecialEffects\\arcanestarwork.bmp",2750, 200,11,2 },
	{ "Image\\SpecialEffects\\froststarwork.bmp",2750, 200,11,2 },
	{ "Image\\SpecialEffects\\electricitystarwork.bmp",2750, 200,11,2 }
};

static MyObjectBuilder healthbar1{ "Image\\UI\\healthbar.bmp",343,46,1,2 };