#include "stdafx.h"

CString Get_ElementName(int element_type, int option) {//将指定的数字代表的元素或dot储存在数组里
	switch (option) {//option为0代表元素，为1代表dot
	case ELEMENT_ELE:
		switch (element_type) {//按不同值存储元素名称
		case FIRE:return "火焰"; break;
		case ARCANE:return "奥术"; break;
		case FROST:return "冰霜"; break;
		case ELECTRICITY:return "闪电"; break;
		default:break;
		}
		break;
	case ELEMENT_DOT:
		switch (element_type) {//按不同值存储dot名称
		case FIRE:return "燃烧"; break;
		case ARCANE:return "奥能"; break;
		case FROST:return "霜燃"; break;
		case ELECTRICITY:return "瘫痪"; break;
		default:break;
		}
		break;
	default:break;
	}
}

CString Get_ActionName(int action_type){
	switch (action_type) {
	case MISSILE:return "飞弹"; break;
	case RAY:return "射线"; break;
	case STARSTRIKE:return "星袭"; break;
	default:break;
	}
}

CString Get_MonsterName(int object){
	switch (object) {
	case ZOMBIE:return "僵尸"; break;
	case MUMMY:return "木乃伊"; break;
	case GARGOYLES:return "石像鬼"; break;
	case CATTLE:return "牛魔"; break;
	default:break;
	}
}

int Random(int upper, int lower) {//在上下限之间生成一个随机值，用来决定词缀、增伤值等，设置成内联函数
	int seed = aux_time_srand + (int)time(0);
	srand(seed);//以系统时间作为随机数种子
	aux_time_srand = seed;
	return ((rand() % (upper - lower + 1)) + lower);//生成随机值，返回
}