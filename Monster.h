#pragma once

class Player;
class Monster :public MyObject//�����࣬�����࣬�������ڴ�������
{
public:
	Monster(MyObjectBuilder *mobj, int x, int y, int exp, int v, int hls, float atk, int arm, int obj, int rg, int et);//���캯��
	virtual void Attack();//��������
	virtual void CauseDamage(Player &);//����˺�����
	virtual void Move();//�ƶ�����
	virtual void Dead();//��������
	virtual void Thrust();//�̻�����
	virtual void Select(HDC &, HDC &);//������ʾ����

	void DropItem();//����װ��
	void MoveToPlayer(Player &);//������ƶ�
	void MoveLeft();//���ƺ���
	void MoveRight();//���ƺ���
	void MoveLeft(const int &);//�������ƺ���
	void MoveRight(const int &);//�������ƺ���
	void UnderAttack(int &);//�ܻ�����
	void UpdateAttributes(const int &);//��������ȼ����ù��������
	void Vulnerate(const int &object, const int &value);//ʹ��������
	friend Monster * CreateMonster(const int &, const int &);//����һ������ĳ��ϡ�жȵĹ������������ȼ����ù��������

	//Dot����
	void UpdateDot(const int &, int, int);//����dot
	virtual void UnderDot(const int &, const int &);//�����ܵ�dot
	virtual void Combust();//ȼ��
	virtual int ArcanePower();//����
	virtual void FrostBite();//˪ȼ
	virtual void Paralyze();//̱��

	//������
	const int &Velocity();//�ٶȺ���
	const int &Get_Range();//��ȡ������Χ
	const int &Get_State();//��ȡ����״̬
	const int &Get_Object();//��ȡ�����ţ���������������
	const int &Get_Armor();//��ȡ����
	const int &Get_Resistance(const int &);//��ȡԪ�ؿ���
	const int &Get_VulValue(const int &);//��ȡ����ֵ
	const int &Get_Bonus();//��ȡ��ɱ�����ܹ���ȡ�ľ���ֵ
	bool Arcane_Detonation();//�Ƿ��ǰ���dot������
	bool FrostBited();//����˪ȼ״̬
	float Health_rate();//��ǰ����ֵ��������֮��
	float DR_Coe(const int &pen_ed,const int &e_type);//����ϵ��
	bool attacked;

protected:
	MyObjectBuilder *image_head;//����ͼƬ���ָ��
	int object;//���
	int monster_experience;//ɱ�������ܹ���ȡ�ľ���ֵ

	int velocity;//�����ٶ�
	int current_velocity;//���ﵱǰ�ٶ�
	int health;//��������ֵ
	int current_health;//���ﵱǰ����ֵ������ֵΪ���������

	float damage;//��������ֵ������ֵԽ�ߣ���ɵ��˺�Խ��
	int range;//������Χ����ʾ���﹥���������ڶ��Χ
	int dot_enhanced_damage;//dot���˰ٷֱȣ�Ĭ��Ϊ0
	int element_type;//����Ԫ������
	int element_damage[4];//Ԫ���˺�
	int element_resistance[4];//Ԫ�ؿ���
	int armor;//���ף���Ԫ�ؿ��Էֿ�����
	int vul_value[VUL_ED_OBJ_MAX];//����ֵ

	bool faint;//�Ƿ���ѣ
	bool arcane_detonation;//�Ƿ񴥷����ܱ�ը

	Dot dot;
	HealthBar healthbar;//Ѫ��
};

class Zombie :public Monster {//��ʬ�࣬��������ƶ��ٶȻ���������ֵ��
public:
	Zombie(int, int);
};

class Mummy :public Monster {//ľ�����࣬��Ӣ����ƶ��ٶȿ죬����ֵ�ߣ�����
public:
	Mummy(int, int);
	void FrostBite();//����˪ȼЧ��
protected:
	int thrust_cd;//�̻���CDʱ��
	int pre;//��һ�δ̻���ʱ��
};

class Gargoyles :public Monster {//ʯ����࣬��Ӣ����ƶ��ٶȻ���������ֵ�ߣ�����ǿ������
public:
	Gargoyles(int, int);
};

class Cattle :public Monster {//ţħ�࣬�м�����ƶ��ٶȻ���������ֵ�ͣ�����
public:
	Cattle(int, int);
	virtual void Paralyze();//����̱��Ч��
};