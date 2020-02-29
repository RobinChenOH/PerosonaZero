#pragma once
//物品按稀有度区分，分为普通，传奇和遗物
//普通物品只增加攻击、防御等基础属性
//传奇物品可增加元素伤害类型
//遗物可以随机到新技能、特效等
class WeaponBuilder;

class Item //物品类，表示可以掉落的物品，抽象类
{
public:
	Item(int, int);//构造函数，以特定稀有度和序号构造一个物品
	//virtual void Show_Amap;//在地图上展示物品，由image_show的真假决定，设置物品的掉落与拾取
	//访问器
	const int &Get_Rarity();//稀有度的访问器
	const CString &Get_Name();//武器名称访问器
	const int &Get_Number();//武器序号的访问器
protected:
	int number;//物品编号
	CString name;//物品的名称
	int rarity;//稀有度，由外界传参进行设置，0为普通，1为传奇，2为遗物
	int level;//武器等级，等级决定增伤的幅度
};

class NormalWeapon :public Item {//普通武器类，继承自物品类，作为武器族的基类
public:
	NormalWeapon(int new_rarity, int i, int new_al, int new_au, DamageBuilder new_atkED);//构造函数，参数为稀有度和名称、百分比增伤值和武器白字
	//访问器
	const int Get_atkVL();//随机返回一个位于攻击下限和攻击上限的值
	const int &Get_atkLower();//返回伤害下限
	const int &Get_atkUpper();//返回伤害上限
	const DamageStorage &Get_atkED();//百分比增伤值访问器
	const DamageStorage &Get_CriticalChance();//暴击几率访问器
	const DamageStorage &Get_CriticalDamage();//暴击伤害访问器
	const virtual DamageStorage &Get_PenetrateED();//穿透值访问器
	const virtual DamageStorage &Get_ElementED();//元素增伤值访问器
	const virtual DamageStorage &Get_DotED();//DOT增伤值访问器
	const virtual SpecialDamageStorage &Get_SpecialEffect();//武器特效值访问器
	virtual CString &Get_SpecialEffects();//武器特效访问器
	friend NormalWeapon* CreateWeapon(WeaponBuilder *w_builder);//由武器构造器生成一个武器
protected:
	DamageStorage atkED;//百分比增伤值
	DamageStorage critical_chance;//暴击几率
	DamageStorage critical_damage;//暴击伤害
	int atk_lower;//攻击值下限
	int atk_upper;//攻击值上限
};

class LegendaryWeapon :public NormalWeapon {//传奇武器，可随机到两到三条词缀，且值在中范围波动
public:
	LegendaryWeapon(int new_rarity, int i , int new_al, int new_au, DamageBuilder new_atkED, DamageBuilder new_penetrateED,
		DamageBuilder new_elementED, DamageBuilder new_dotED);//传奇武器的构造函数
	//访问器
	const virtual DamageStorage &Get_PenetrateED();//穿透值访问器
	const virtual DamageStorage &Get_ElementED();//元素增伤值访问器
	const virtual DamageStorage &Get_DotED();//Dot增伤值访问器
protected:
	DamageStorage penetrateED;
	DamageStorage elementED;
	DamageStorage dotED;
};

class RelicWeapon :public LegendaryWeapon {//遗物武器，可固定获得特定的属性并在高范围波动，且增加额外的增伤能力
public:
	RelicWeapon(int i, int new_al, int new_au, DamageBuilder new_atkED, DamageBuilder new_penED,DamageBuilder rw_element[], DamageBuilder rw_dot[], 
		SpecialDamageBuilder rw_special[]);//构造函数，生成词缀、特效效果及特效描述
	//访问器
	const virtual SpecialDamageStorage &Get_SpecialEffect();//武器特效值访问器
	virtual CString &Get_SpecialEffects();//武器特效访问器
protected:
	SpecialDamageStorage special_effect;//武器特效效果
	CString special_content;//武器特效描述
};