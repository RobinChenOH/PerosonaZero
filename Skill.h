#pragma once
class MonsterQueue;
//技能类，表示人物角色和怪物可以操纵元素力量完成的攻击
//每种技能都由元素类型和攻击方式组成，但是操控元素的操作比较规整，可以作为基础属性最先初始化，由玩家选择攻击方式
//元素分为火焰、奥术、冰霜、闪电属性，分别有自己的dot
//攻击方式分为投掷型，引导型，坠落型
//除此之外技能还具有伤害放大系数、法力消耗值，和释放位置的坐标属性
//技能贴图的更改由人物向技能传参完成，技能的攻击由技能向人物传递参数再由人物增幅后进行攻击

class Skill :public MyObject{//抽象技能类，不可释放，定义技能的广义属性
public:
	//构造与抽象函数
	Skill(MyObjectBuilder *, int et, int at, int p_x, int p_y, int rg, int aoe, int ve, DWORD interval, DWORD cd);
	virtual void Enroute();//技能飞行时的函数，返回是否造成伤害
	virtual void NotWork();//未造成伤害时的函数
	virtual void Work();//造成伤害时的函数
	virtual bool EndEnroute() = 0;//飞行结束
	virtual bool Collide(MonsterQueue &) = 0;//碰撞
	//修改器与访问器
	void SetElementType(int);//元素类型修改器，人物在攻击的过程中会频繁改变元素类型因此需要设置修改器
	const int &Get_Object();//技能序号访问器
	const int &Get_ElementType();//元素类型访问器
	const int &Get_ActionType();//攻击方式访问器
	const int &Get_MagnificationFactor();//放大效果访问器
	const int &Get_ManaCost();//法力消耗值访问器
	const int &Get_AttackRange();//攻击距离访问器
	const int &Get_AOERange();//AOE伤害距离访问器
	CoolDown &Skill_CD();//CD时间访问器

protected:
	MyObjectBuilder *image_head;//图片队列
	int object;//技能对象的序号
	int element_type;//元素属性，0表示火焰，1表示奥术，2表示冰霜，3表示闪电
	int action_type;//攻击方式，0表示投掷型，1表示引导型，2表示爆破型，3表示坠落型，4表示增益型
	int magnification_factor;//技能对人物基本伤害的放大效果，百分比
	int mana_cost;//法力消耗值，法力低于最低消耗值将无法释放技能
	int velocity;//技能飞行速度
	int attack_range;//攻击距离
	int aoe_range;//AOE伤害距离
	CoolDown skill_cd;//技能cd
};

//五种完整技能类，只用于计算参数和传参，不用于造成伤害
class MissileSkill :public Skill{//飞弹型技能，继承自技能类
public:
	MissileSkill(int, int, int);//参数为元素类型及人物坐标
	virtual bool EndEnroute();//飞行结束
	virtual bool Collide(MonsterQueue &);//碰撞
};

class ChannellingSkill:public Skill {//引导型技能，继承自技能类
public:
	ChannellingSkill(int et, int p_x, int p_y, int r);
	virtual bool EndEnroute();
	virtual bool Collide(MonsterQueue &);
	void SetElementType(int);
protected:
	float radius;
};

class StarStrikeSkill :public Skill {//坠落型技能，继承自技能类
public:
	StarStrikeSkill(int et, int p_x, int p_y, int r, int d_x, int d_y);
	virtual void Enroute();
	virtual bool EndEnroute();//飞行结束
	virtual bool Collide(MonsterQueue &);//碰撞
protected:
	float radius;
	int d_x;
	int d_y;
	float v_x;
	float v_y;
};