#pragma once
//静态全局变量

static char	buf[50];			// 缓冲区大小
static int aux_time_srand = (unsigned int)time(NULL);

static CString normal_weapon_name[NW_TYPE_MAXIMUM] = { "匕首","海啸","短剑" };
static CString legendary_weapon_name[LW_TYPE_MAXIMUM] = { "君王剑","打刀","长剑" };
static CString relic_weapon_name[RW_TYPE_MAXIMUM] = { "霜心","月刃","天罚","杨教授的治疗","朝阳","星袭" };
static CString relic_weapon_special[RW_TYPE_MAXIMUM] = {
	"冰霜伤害会对敌人造成额外的伤害",
	"射线的法力消耗减少",
	"对不死生物造成额外的伤害",
	"瘫痪造成额外的伤害",
	"每次攻击都会使怪物受到的伤害提高",
	"流星的伤害提高"
};

//储存一些辅助函数，便于编写代码
CString Get_ElementName(int element_type, int option);//把某个整型变量对应的元素名称储存入字符串
CString Get_ActionName(int action_type);
CString Get_MonsterName(int object);
int Random(int upper, int lower);//在上下限之间生成一个随机值，用来决定词缀、增伤值等，设置成内联函数

struct MonsterUpdateController {
	int x;//坐标
	int num;//生成数量
	int rarity;//生成等级
};
static MonsterUpdateController m_controller[10] = {
	{1,4,NORMAL},{50,2,NORMAL},{250,1,LEGENDARY},{362,5,NORMAL},{500,2,RELIC},{700,7,NORMAL},{850,6,LEGENDARY},{1000,4,RELIC},{1150,1,LEGENDARY},{1300,3,RELIC}
};

struct DamageBuilder {//伤害生成器
	int type;//是否生成
	int upper;//伤害上限
	int lower;//伤害下限
};

struct DamageStorage {//伤害存储器
	int type;//伤害类型
	int value;//伤害值
};

struct SpecialDamageBuilder {//特效生成器
	int effect_type;//特效类型,0为增伤类，1为减耗类，2为防御类，3为距离类
	int concrete_type;//具体类型
	int object;//增伤对应的对象所对应的数值
	int upper;//特效上限
	int lower;//特效下限
};
struct SpecialDamageStorage {//特效存储器
	int effect_type;//特效类型,0为增伤类，1为减耗类，2为防御类，3为距离类
	int concrete_type;//具体类型
	int object;//增伤对应的对象所对应的数值
	int value;//特效数字
};
struct BossDesign {//boss属性生成器
	int experience;
	int velocity;
	int health;
	float atk;
	int armor;
	int object;
	int range;
	int element_type;
};

//遗物武器的元素、dot、特效伤方案
static DamageBuilder rw_element[RW_TYPE_MAXIMUM] = { { 2, 20, 15 }, { 1, 25, 20 }, { 0, 10, 5 },{3,15,7},{0,5,3},{0,9,4} };
static DamageBuilder rw_dot[RW_TYPE_MAXIMUM] = { { 2, 10, 8 }, { 1, 50, 40 }, { 0, 30, 20 },{3,30,20},{1,9,6},{0,14,2} };
static SpecialDamageBuilder rw_special[RW_TYPE_MAXIMUM] = {
{ INTENSIFY_ATTACK, VUL_ED, FROST + 1, 30, 25 },//霜心为易伤增伤，冰霜伤害对受到寒冷伤害的敌人造成额外增伤
{ ENERGY_AFFINITY, ACT_AF, RAY, 50, 40 },//月刃为状态增伤，引导技能时获得增伤
{ INTENSIFY_ATTACK, DIS_ED, ZOMBIE, 30, 25 },//天罚为歧视增伤，对僵尸造成额外伤害
{ INTENSIFY_ATTACK, DOT_ED, ELECTRICITY, 1100, 1000 },//杨教授的治疗提升瘫痪伤害
{ INTENSIFY_ATTACK, VUL_ED, NON_ELEMENT + 1, 10, 5},//朝阳提升易伤
{ INTENSIFY_ATTACK, IND_ED, STARSTRIKE, 100, 90} //星袭提升坠落伤害
};

static BossDesign boss1{ 2000,20,200,100,100,BOSS1,100,FIRE };