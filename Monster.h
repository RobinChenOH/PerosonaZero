#pragma once

class Player;
class Monster :public MyObject//怪物类，抽象类，不可用于创建对象
{
public:
	Monster(MyObjectBuilder *mobj, int x, int y, int exp, int v, int hls, float atk, int arm, int obj, int rg, int et);//构造函数
	virtual void Attack();//攻击函数
	virtual void CauseDamage(Player &);//造成伤害函数
	virtual void Move();//移动函数
	virtual void Dead();//死亡函数
	virtual void Thrust();//刺击函数
	virtual void Select(HDC &, HDC &);//重载显示函数

	void DropItem();//掉落装备
	void MoveToPlayer(Player &);//朝玩家移动
	void MoveLeft();//左移函数
	void MoveRight();//右移函数
	void MoveLeft(const int &);//带参左移函数
	void MoveRight(const int &);//带参右移函数
	void UnderAttack(int &);//受击函数
	void UpdateAttributes(const int &);//根据人物等级设置怪物的属性
	void Vulnerate(const int &object, const int &value);//使怪物易伤
	friend Monster * CreateMonster(const int &, const int &);//返回一个属于某个稀有度的怪物，并根据人物等级设置怪物的属性

	//Dot函数
	void UpdateDot(const int &, int, int);//更新dot
	virtual void UnderDot(const int &, const int &);//怪物受到dot
	virtual void Combust();//燃烧
	virtual int ArcanePower();//奥能
	virtual void FrostBite();//霜燃
	virtual void Paralyze();//瘫痪

	//访问器
	const int &Velocity();//速度函数
	const int &Get_Range();//获取攻击范围
	const int &Get_State();//获取怪物状态
	const int &Get_Object();//获取怪物编号，用于歧视类增伤
	const int &Get_Armor();//获取护甲
	const int &Get_Resistance(const int &);//获取元素抗性
	const int &Get_VulValue(const int &);//获取易伤值
	const int &Get_Bonus();//获取击杀怪物能够获取的经验值
	bool Arcane_Detonation();//是否是奥能dot持续期
	bool FrostBited();//处于霜燃状态
	float Health_rate();//当前生命值与总生命之比
	float DR_Coe(const int &pen_ed,const int &e_type);//减伤系数
	bool attacked;

protected:
	MyObjectBuilder *image_head;//保存图片组的指针
	int object;//编号
	int monster_experience;//杀死怪物能够获取的经验值

	int velocity;//怪物速度
	int current_velocity;//怪物当前速度
	int health;//怪物生命值
	int current_health;//怪物当前生命值，生命值为零怪物死亡

	float damage;//攻击能力值，能力值越高，造成的伤害越高
	int range;//攻击范围，表示怪物攻击能作用于多大范围
	int dot_enhanced_damage;//dot增伤百分比，默认为0
	int element_type;//怪物元素类型
	int element_damage[4];//元素伤害
	int element_resistance[4];//元素抗性
	int armor;//护甲，与元素抗性分开计算
	int vul_value[VUL_ED_OBJ_MAX];//易伤值

	bool faint;//是否晕眩
	bool arcane_detonation;//是否触发奥能爆炸

	Dot dot;
	HealthBar healthbar;//血条
};

class Zombie :public Monster {//僵尸类，初级怪物，移动速度缓慢，生命值低
public:
	Zombie(int, int);
};

class Mummy :public Monster {//木乃伊类，精英怪物，移动速度快，生命值高，弱火
public:
	Mummy(int, int);
	void FrostBite();//重载霜燃效果
protected:
	int thrust_cd;//刺击的CD时间
	int pre;//上一次刺击的时间
};

class Gargoyles :public Monster {//石像鬼类，精英怪物，移动速度缓慢，生命值高，攻击强，弱电
public:
	Gargoyles(int, int);
};

class Cattle :public Monster {//牛魔类，中级怪物，移动速度缓慢，生命值低，弱冰
public:
	Cattle(int, int);
	virtual void Paralyze();//重载瘫痪效果
};