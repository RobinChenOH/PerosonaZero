#pragma once
class MyQueue;
class ObjectQueue;
class MonsterQueue;
class SkillQueue;

class ObjectNode {//图片对象节点
	friend ObjectQueue;
public:
	ObjectNode();
	ObjectNode(MyObject *);
private:
	MyObject *object;//数据域
	ObjectNode *next;//指针域
};

class MonsterNode {//怪物节点
	friend MonsterQueue;
public:
	MonsterNode();
	MonsterNode(Monster *);//构造函数
	friend void MQ_UnderAttack(Player &, Skill *, MonsterQueue &);
private:
	Monster *monster;//数据域
	MonsterNode *next;//指针域
};

class SkillNode {//技能节点
	friend SkillQueue;
public:
	SkillNode();
	SkillNode(Skill *);//构造函数
	Skill *Get_Skill();//获得技能
private:
	Skill *skill;//数据域
	SkillNode *next;//指针域
};

class MyQueue {
public:
	MyQueue(int);
	~MyQueue();
	virtual bool Empty() = 0;
	virtual bool Full();

protected:
	int maximum;//队列最大储存怪物数
	int length;//队列长度
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
	int Get_Front();//查找最前方元素
	void InQueue(Monster *);//入队
	void OutQueue(MonsterNode *);//出队
	void Clear();
	void Select(HDC &,HDC &);//选取所有应当显示的怪物
	void IFrame();//所有怪物增帧
	void MoveToPlayer(Player &);//队列内怪物朝玩家移动
	void CauseDamage(Player &);//队列内怪物攻击玩家
	void UnderAttack(int &, int, Monster *);//根据数值和半径直接造成伤害
	friend void MQ_UnderAttack(Player &, Skill *, MonsterQueue &);
private:
	MonsterNode *head;//队首指针
	MonsterNode *tail;//队尾指针
};

class SkillQueue :public MyQueue {
public:
	SkillQueue();
	bool Empty();
	void Clear();
	void InQueue(Skill *);//入队
	void OutQueue(SkillNode *);//出队
	void Select(HDC &, HDC &);//选取所有应当显示的技能
	void IFrame();//所有技能增帧
	void Play(Player &, MonsterQueue &);//技能执行
private:
	SkillNode *head;//队首指针
	SkillNode *tail;//队尾指针
};