#include "stdafx.h"

Damage::Damage() :attackED(0), penetrateED(0), critical_strike_chance(0), critical_strike_damage(0), element_damage(), dot_damage(), independentED(),
vulnerableED(), stateED(), discriminatoryED() {}

void Damage::Enhance_Damage(int type, int object, int value){
	switch (type) {
	case ATK_ED:attackED += value; break;
	case PEN_ED:penetrateED += value; break;
	case CRI_STR_CHANCE:critical_strike_chance += value; break;
	case CRI_STR_DAMAGE:critical_strike_damage += value; break;
	case ELE_ED:element_damage[object] += value; break;
	case DOT_ED:dot_damage[object] += value; break;
	case IND_ED:independentED[object] += value; break;
	case VUL_ED:vulnerableED[object] += value; break;
	case STA_ED:stateED[object] += value; break;
	case DIS_ED:discriminatoryED[object] += value; break;
	default:break;
	}
}

void Damage::Weaken_Damage(int type, int object, int value){
	switch (type) {
	case ATK_ED:attackED -= value; break;
	case PEN_ED:penetrateED -= value; break;
	case CRI_STR_CHANCE:critical_strike_chance -= value; break;
	case CRI_STR_DAMAGE:critical_strike_damage -= value; break;
	case ELE_ED:element_damage[object] -= value; break;
	case DOT_ED:dot_damage[object] -= value; break;
	case IND_ED:independentED[object] -= value; break;
	case VUL_ED:vulnerableED[object] -= value; break;
	case STA_ED:stateED[object] -= value; break;
	case DIS_ED:discriminatoryED[object] -= value; break;
	default:break;
	}
}

const int & Damage::Get_Damage(int type, int object){
	switch (type) {
	case ATK_ED:return attackED; break;
	case PEN_ED:return penetrateED; break;
	case CRI_STR_CHANCE:return critical_strike_chance; break;
	case CRI_STR_DAMAGE:return critical_strike_damage; break;
	case ELE_ED:return element_damage[object]; break;
	case DOT_ED:return dot_damage[object]; break;
	case IND_ED:return independentED[object]; break;
	case VUL_ED:return vulnerableED[object]; break;
	case STA_ED:return stateED[object]; break;
	case DIS_ED:return discriminatoryED[object]; break;
	default: break;
	}
}

Affinity::Affinity() :attackAF(0), elementAF(), actionAF() {}

void Affinity::Enhance_Affinity(int type, int object, int value){
	switch (type) {
	case ATK_AF:attackAF += value; break;
	case ELE_AF:elementAF[object] += value; break;
	case ACT_AF:actionAF[object] += value; break;
	default:break;
	}
}

void Affinity::Weaken_Affinity(int type, int object, int value){
	switch (type) {
	case ATK_AF:attackAF -= value; break;
	case ELE_AF:elementAF[object] -= value; break;
	case ACT_AF:actionAF[object] -= value; break;
	default:break;
	}
}

const int & Affinity::Get_Affinity(int type, int object){
	switch (type) {
	case ATK_AF:return attackAF; break;
	case ELE_AF:return elementAF[object]; break;
	case ACT_AF:return actionAF[object]; break;
	default:break;
	}
}

Defense::Defense() :armor(0), elementPT(), statePT() {}

void Defense::Enhance_Defense(int type, int object, int value){
	switch (type) {
	case ARM_PT:armor += value; break;
	case ELE_PT:elementPT[object] += value; break;
	case STA_PT:statePT[object] += value; break;
	default:break;
	}
}

void Defense::Weaken_Defense(int type, int object, int value){
	switch (type) {
	case ARM_PT:armor -= value; break;
	case ELE_PT:elementPT[object] -= value; break;
	case STA_PT:statePT[object] -= value; break;
	default:break;
	}
}

const int & Defense::Get_Defense(int type, int object){
	switch (type) {
	case ARM_PT:return armor; break;
	case ELE_PT:return elementPT[object]; break;
	case STA_PT:return statePT[object]; break;
	default:break;
	}
}
