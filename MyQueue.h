#pragma once
class MyQueue;
class ObjectQueue;
class MonsterQueue;
class SkillQueue;

class ObjectNode {//ͼƬ����ڵ�
	friend ObjectQueue;
public:
	ObjectNode();
	ObjectNode(MyObject *);
private:
	MyObject *object;//������
	ObjectNode *next;//ָ����
};

class MonsterNode {//����ڵ�
	friend MonsterQueue;
public:
	MonsterNode();
	MonsterNode(Monster *);//���캯��
	friend void MQ_UnderAttack(Player &, Skill *, MonsterQueue &);
private:
	Monster *monster;//������
	MonsterNode *next;//ָ����
};

class SkillNode {//���ܽڵ�
	friend SkillQueue;
public:
	SkillNode();
	SkillNode(Skill *);//���캯��
	Skill *Get_Skill();//��ü���
private:
	Skill *skill;//������
	SkillNode *next;//ָ����
};

class MyQueue {
public:
	MyQueue(int);
	~MyQueue();
	virtual bool Empty() = 0;
	virtual bool Full();

protected:
	int maximum;//������󴢴������
	int length;//���г���
};

class ObjectQueue :public MyQueue {
public:
	ObjectQueue();
	bool Empty();
	void InQueue(MyObject *);
	void OutQueue();
	void Select(HDC &, HDC &, bool clear);
	void TransSelect(HDC &, HDC &, int r, int g, int b, bool);
	void IFrame();
	void Clear();
private:
	ObjectNode *head;
	ObjectNode *tail;
};

class MonsterQueue :public MyQueue {
public:
	MonsterQueue();
	bool Empty();
	int Get_Front();//������ǰ��Ԫ��
	void InQueue(Monster *);//���
	void OutQueue(MonsterNode *);//����
	void Clear();
	void Select(HDC &,HDC &);//ѡȡ����Ӧ����ʾ�Ĺ���
	void IFrame();//���й�����֡
	void MoveToPlayer(Player &);//�����ڹ��ﳯ����ƶ�
	void CauseDamage(Player &);//�����ڹ��﹥�����
	void UnderAttack(int &, int, Monster *);//������ֵ�Ͱ뾶ֱ������˺�
	friend void MQ_UnderAttack(Player &, Skill *, MonsterQueue &);
private:
	MonsterNode *head;//����ָ��
	MonsterNode *tail;//��βָ��
};

class SkillQueue :public MyQueue {
public:
	SkillQueue();
	bool Empty();
	void Clear();
	void InQueue(Skill *);//���
	void OutQueue(SkillNode *);//����
	void Select(HDC &, HDC &);//ѡȡ����Ӧ����ʾ�ļ���
	void IFrame();//���м�����֡
	void Play(Player &, MonsterQueue &);//����ִ��
private:
	SkillNode *head;//����ָ��
	SkillNode *tail;//��βָ��
};