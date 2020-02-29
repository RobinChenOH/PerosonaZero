#pragma once

class Damage{//�˺��࣬������������Ч��
public:
	Damage();
	void Enhance_Damage(int type, int object, int value);//�����ض��Ķ���
	void Weaken_Damage(int type, int object, int value);//�����ض��Ķ���
	const int &Get_Damage(int type, int object);//���ؾ�����������
protected:
	int attackED;//�����˺�����
	int penetrateED;//��͸������
	int critical_strike_chance;//��������
	int critical_strike_damage;//�����˺�
	int element_damage[4];//Ԫ���˺�����ֵ
	int dot_damage[4];//Ԫ��dot���˺�����ֵ
	int independentED[IND_ED_OBJ_MAX];//��������
	int vulnerableED[VUL_ED_OBJ_MAX];//����������,0Ϊ�������ˣ�1~4ΪԪ������
	int stateED[STA_ED_OBJ_MAX];//״̬������
	int discriminatoryED[DIS_ED_OBJ_MAX];//����������
};

class Affinity {//�����࣬�������м���Ч��
public:
	Affinity();
	void Enhance_Affinity(int type, int object, int value);//�׺��ض��Ķ���
	void Weaken_Affinity(int type, int object, int value);//�������ض��Ķ���ļ���ֵ
	const int &Get_Affinity(int type, int object);//���ؾ������ļ���ֵ
protected:
	int attackAF;
	int elementAF[ELE_AF_OBJ_MAX];//Ԫ�������
	int actionAF[ACT_AF_OBJ_MAX];//��ʽ�����
};

class Defense {//�����࣬�������з���Ч��
public:
	Defense();
	void Enhance_Defense(int type, int object, int value);//�����ض��Ķ���
	void Weaken_Defense(int type, int object, int value);//�������ض��Ķ���ļ���ֵ
	const int &Get_Defense(int type, int object);//���ؾ������ļ���ֵ
protected:
	int armor;//���ף���Ԫ�ؿ��Էֿ�����
	int elementPT[ELE_PT_OBJ_MAX];//Ԫ�ؿ���
	int statePT[STA_PT_OBJ_MAX];//״̬�����
};