#include "stdafx.h"

CString Get_ElementName(int element_type, int option) {//��ָ�������ִ����Ԫ�ػ�dot������������
	switch (option) {//optionΪ0����Ԫ�أ�Ϊ1����dot
	case ELEMENT_ELE:
		switch (element_type) {//����ֵͬ�洢Ԫ������
		case FIRE:return "����"; break;
		case ARCANE:return "����"; break;
		case FROST:return "��˪"; break;
		case ELECTRICITY:return "����"; break;
		default:break;
		}
		break;
	case ELEMENT_DOT:
		switch (element_type) {//����ֵͬ�洢dot����
		case FIRE:return "ȼ��"; break;
		case ARCANE:return "����"; break;
		case FROST:return "˪ȼ"; break;
		case ELECTRICITY:return "̱��"; break;
		default:break;
		}
		break;
	default:break;
	}
}

CString Get_ActionName(int action_type){
	switch (action_type) {
	case MISSILE:return "�ɵ�"; break;
	case RAY:return "����"; break;
	case STARSTRIKE:return "��Ϯ"; break;
	default:break;
	}
}

CString Get_MonsterName(int object){
	switch (object) {
	case ZOMBIE:return "��ʬ"; break;
	case MUMMY:return "ľ����"; break;
	case GARGOYLES:return "ʯ���"; break;
	case CATTLE:return "ţħ"; break;
	default:break;
	}
}

int Random(int upper, int lower) {//��������֮������һ�����ֵ������������׺������ֵ�ȣ����ó���������
	int seed = aux_time_srand + (int)time(0);
	srand(seed);//��ϵͳʱ����Ϊ���������
	aux_time_srand = seed;
	return ((rand() % (upper - lower + 1)) + lower);//�������ֵ������
}