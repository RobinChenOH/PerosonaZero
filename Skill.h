#pragma once
class MonsterQueue;
//�����࣬��ʾ�����ɫ�͹�����Բ���Ԫ��������ɵĹ���
//ÿ�ּ��ܶ���Ԫ�����ͺ͹�����ʽ��ɣ����ǲٿ�Ԫ�صĲ����ȽϹ�����������Ϊ�����������ȳ�ʼ���������ѡ�񹥻���ʽ
//Ԫ�ط�Ϊ���桢��������˪���������ԣ��ֱ����Լ���dot
//������ʽ��ΪͶ���ͣ������ͣ�׹����
//����֮�⼼�ܻ������˺��Ŵ�ϵ������������ֵ�����ͷ�λ�õ���������
//������ͼ�ĸ������������ܴ�����ɣ����ܵĹ����ɼ��������ﴫ�ݲ�������������������й���

class Skill :public MyObject{//�������࣬�����ͷţ����弼�ܵĹ�������
public:
	//�����������
	Skill(MyObjectBuilder *, int et, int at, int p_x, int p_y, int rg, int aoe, int ve, DWORD interval, DWORD cd);
	virtual void Enroute();//���ܷ���ʱ�ĺ����������Ƿ�����˺�
	virtual void NotWork();//δ����˺�ʱ�ĺ���
	virtual void Work();//����˺�ʱ�ĺ���
	virtual bool EndEnroute() = 0;//���н���
	virtual bool Collide(MonsterQueue &) = 0;//��ײ
	//�޸����������
	void SetElementType(int);//Ԫ�������޸����������ڹ����Ĺ����л�Ƶ���ı�Ԫ�����������Ҫ�����޸���
	const int &Get_Object();//������ŷ�����
	const int &Get_ElementType();//Ԫ�����ͷ�����
	const int &Get_ActionType();//������ʽ������
	const int &Get_MagnificationFactor();//�Ŵ�Ч��������
	const int &Get_ManaCost();//��������ֵ������
	const int &Get_AttackRange();//�������������
	const int &Get_AOERange();//AOE�˺����������
	CoolDown &Skill_CD();//CDʱ�������

protected:
	MyObjectBuilder *image_head;//ͼƬ����
	int object;//���ܶ�������
	int element_type;//Ԫ�����ԣ�0��ʾ���棬1��ʾ������2��ʾ��˪��3��ʾ����
	int action_type;//������ʽ��0��ʾͶ���ͣ�1��ʾ�����ͣ�2��ʾ�����ͣ�3��ʾ׹���ͣ�4��ʾ������
	int magnification_factor;//���ܶ���������˺��ķŴ�Ч�����ٷֱ�
	int mana_cost;//��������ֵ�����������������ֵ���޷��ͷż���
	int velocity;//���ܷ����ٶ�
	int attack_range;//��������
	int aoe_range;//AOE�˺�����
	CoolDown skill_cd;//����cd
};

//�������������ֻ࣬���ڼ�������ʹ��Σ�����������˺�
class MissileSkill :public Skill{//�ɵ��ͼ��ܣ��̳��Լ�����
public:
	MissileSkill(int, int, int);//����ΪԪ�����ͼ���������
	virtual bool EndEnroute();//���н���
	virtual bool Collide(MonsterQueue &);//��ײ
};

class ChannellingSkill:public Skill {//�����ͼ��ܣ��̳��Լ�����
public:
	ChannellingSkill(int et, int p_x, int p_y, int r);
	virtual bool EndEnroute();
	virtual bool Collide(MonsterQueue &);
	void SetElementType(int);
protected:
	float radius;
};

class StarStrikeSkill :public Skill {//׹���ͼ��ܣ��̳��Լ�����
public:
	StarStrikeSkill(int et, int p_x, int p_y, int r, int d_x, int d_y);
	virtual void Enroute();
	virtual bool EndEnroute();//���н���
	virtual bool Collide(MonsterQueue &);//��ײ
protected:
	float radius;
	int d_x;
	int d_y;
	float v_x;
	float v_y;
};