#pragma once

class Damage{//伤害类，包含所有增伤效果
public:
	Damage();
	void Enhance_Damage(int type, int object, int value);//增伤特定的对象
	void Weaken_Damage(int type, int object, int value);//削弱特定的对象
	const int &Get_Damage(int type, int object);//返回具体对象的增伤
protected:
	int attackED;//基础伤害增伤
	int penetrateED;//穿透力增伤
	int critical_strike_chance;//暴击几率
	int critical_strike_damage;//暴击伤害
	int element_damage[4];//元素伤害增伤值
	int dot_damage[4];//元素dot的伤害增伤值
	int independentED[IND_ED_OBJ_MAX];//独立增伤
	int vulnerableED[VUL_ED_OBJ_MAX];//易伤类增伤,0为所有增伤，1~4为元素增伤
	int stateED[STA_ED_OBJ_MAX];//状态类增伤
	int discriminatoryED[DIS_ED_OBJ_MAX];//歧视类增伤
};

class Affinity {//减耗类，包含所有减耗效果
public:
	Affinity();
	void Enhance_Affinity(int type, int object, int value);//亲和特定的对象
	void Weaken_Affinity(int type, int object, int value);//削弱对特定的对象的减耗值
	const int &Get_Affinity(int type, int object);//返回具体对象的减耗值
protected:
	int attackAF;
	int elementAF[ELE_AF_OBJ_MAX];//元素类减耗
	int actionAF[ACT_AF_OBJ_MAX];//方式类减耗
};

class Defense {//防御类，包含所有防御效果
public:
	Defense();
	void Enhance_Defense(int type, int object, int value);//减伤特定的对象
	void Weaken_Defense(int type, int object, int value);//削弱对特定的对象的减伤值
	const int &Get_Defense(int type, int object);//返回具体对象的减伤值
protected:
	int armor;//护甲，与元素抗性分开计算
	int elementPT[ELE_PT_OBJ_MAX];//元素抗性
	int statePT[STA_PT_OBJ_MAX];//状态类减伤
};