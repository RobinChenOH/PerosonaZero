#include "stdafx.h"
extern ObjectQueue object_queue;

MyQueue::MyQueue(int maximum) :maximum(maximum), length(0) {}

MyQueue::~MyQueue() {}

bool MyQueue::Full() {
	return (length == maximum);
}

MonsterNode::MonsterNode() :monster(NULL), next(NULL) {}

MonsterNode::MonsterNode(Monster *new_monster) : monster(new_monster), next(NULL) {}

SkillNode::SkillNode() : skill(NULL), next(NULL) {}

SkillNode::SkillNode(Skill *new_skill) : skill(new_skill), next(NULL) {}

Skill * SkillNode::Get_Skill() {
	return skill;
}

MonsterQueue::MonsterQueue() : MyQueue(MONSTER_MAXIMUM) {
	head = new MonsterNode;
	head->next = tail;//队首的下一个元素为队尾
}

bool MonsterQueue::Empty() {
	return (head->next == nullptr);
}

int MonsterQueue::Get_Front() {//查找最前方元素
	int front = 1200;
	if (head->next == NULL) {
		return front;
	}
	for (MonsterNode *temp = head->next; temp != NULL; temp = temp->next) {
		if (temp->monster->C_X() < front) {//若怪物的中心坐标小于最前方坐标
			front = temp->monster->C_X();//更新
		}
	}
	return front;
}

void MonsterQueue::InQueue(Monster *new_monster) {//入队，在队尾操作
	if (!Full()) {//若未满
				  //入队
		MonsterNode *temp = new MonsterNode(new_monster);//初始化一个怪物节点
		if (Empty()) {
			tail = temp;//若尾节点为空，则初始化尾节点
			head->next = tail;
		}
		else {
			tail->next = temp;//尾节点的指针域指向该节点
			tail = temp;//该节点成为新尾节点
		}
		length++;
	}
}

void MonsterQueue::OutQueue(MonsterNode *pre_monster) {//出队,传入的参数为将删除的节点的前驱指针
	if (!Empty()) {//若未空
		if (pre_monster->next != tail) {//若将要删除的不是尾节点
			MonsterNode *temp = pre_monster->next;//暂存该节点
			pre_monster->next = temp->next;//删除
		}
		else {//若删除的是尾节点，则直接删除
			pre_monster->next = NULL;
			tail = pre_monster;
		}
		length--;
	}
}

void MonsterQueue::Clear() {
	head->next = nullptr;
	length = 0;
}

void MonsterQueue::Select(HDC &mdc, HDC &bufdc) {
	for (MonsterNode *temp = head->next, *pre = head; temp != NULL; pre = temp, temp = temp->next) {//逐个选取每个怪物
		temp->monster->Select(mdc, bufdc);
		if (temp->monster->Get_State() == DEAD&&temp->monster->End()) {//若怪物死亡
			if (temp->monster->Arcane_Detonation()) {//若触发奥能爆炸
				int value = temp->monster->ArcanePower();
				UnderAttack(value, 400, temp->monster);
			}
			OutQueue(pre);//怪物出队，播放击杀动画
			YAuxObject *obj = new YAuxObject(kill, temp->monster->X() - 20, temp->monster->Y() + 40);
			obj->SetShow(true); obj->SetLoop(false);
			object_queue.InQueue(obj);
		}
	}
}

void MonsterQueue::IFrame() {
	for (MonsterNode *temp = head->next; temp != NULL; temp = temp->next) {
		temp->monster->IFrame();//全体成员增帧
	}
}

void MonsterQueue::MoveToPlayer(Player &player) {
	for (MonsterNode *temp = head->next; temp != NULL; temp = temp->next) {
		if (temp->monster->State() != DEAD) {
			temp->monster->MoveToPlayer(player);
		}
	}
}

void MonsterQueue::CauseDamage(Player &player) {
	for (MonsterNode *temp = head->next; temp != NULL; temp = temp->next) {
		if (temp->monster->State() != DEAD) {
			if (abs(temp->monster->C_X() - player.C_X() <= temp->monster->Get_Range())&&!temp->monster->FrostBited()) {
				temp->monster->CauseDamage(player);
				if (abs(temp->monster->C_X() - player.C_X() >= temp->monster->Get_Range())) {
					temp->monster->Move(); break;
				}
			}
		}
	}
}

void MonsterQueue::UnderAttack(int &value, int radius,Monster *monster){
	if (!Empty())
		for (MonsterNode *tmp = head->next, *pre = head; tmp != NULL; pre = tmp, tmp = tmp->next) {//遍历整个怪物队列
			if (abs(tmp->monster->C_X() - monster->C_X()) <= radius) {
				tmp->monster->UnderAttack(value);
			}
		}
}

SkillQueue::SkillQueue() :MyQueue(10) {
	head = new SkillNode;
	head->next = tail;//队首的下一个元素为队尾
}

bool SkillQueue::Empty() {
	return (head->next == nullptr);
}

void SkillQueue::Clear(){
	head->next = NULL;
}

void SkillQueue::InQueue(Skill *new_skill) {
	if (!Full()) {//若未满
				  //入队
		SkillNode *temp = new SkillNode(new_skill);//初始化一个技能节点
		if (Empty()) {
			tail = temp;//若尾节点为空，则初始化尾节点
			head->next = tail;
		}
		else {
			tail->next = temp;//尾节点的指针域指向该节点
			tail = temp;//该节点成为新尾节点
		}
		length++;
	}
}

void SkillQueue::OutQueue(SkillNode *pre_skill) {
	if (!Empty()) {//若未空
		if (pre_skill->next != tail) {
			SkillNode *temp = pre_skill->next;//暂存该节点
			pre_skill->next = temp->next;//删除
		}
		else {
			pre_skill->next = NULL;
			tail = pre_skill;
		}
		length--;
	}
}

void SkillQueue::Select(HDC &mdc, HDC &bufdc) {
	for (SkillNode *temp = head->next; temp != NULL; temp = temp->next) {//逐个选取每个技能
		temp->skill->Select(mdc, bufdc);
	}
}

void SkillQueue::IFrame() {
	for (SkillNode *temp = head->next; temp != NULL; temp = temp->next) {//逐个选取每个技能
		temp->skill->IFrame();
	}
}

void SkillQueue::Play(Player &player, MonsterQueue &monster_queue) {
	if (!Empty()) {
		Skill *skill = head->next->skill;//初始化一个技能指针为第一个有效节点的技能指针，用于操作技能
		for (SkillNode *temp = head->next, *pre = head; temp != NULL; pre = temp, temp = temp->next, (temp == NULL ? skill = NULL : skill = temp->skill)) {//遍历技能队列
			switch (skill->State()) {
			case MOVE:
				if (skill->EndEnroute()) {//若技能已完毕，则出队
					if (skill->Collide(monster_queue)) skill->Work();//若发生碰撞，则技能生效
					else {
						if (temp->next != NULL) skill = temp->next->skill;//若不为尾节点，则重置为下一个节点的技能域
						else skill = NULL;//若为尾节点，则先置空
						OutQueue(pre);
						skill = tail->skill;//置为尾节点的技能域
					}
				}
				else {//否则继续飞行
					skill->Enroute();//火球继续飞行
					if (skill->Collide(monster_queue)) skill->Work();//若发生碰撞，则技能生效
				}
				break;
			case ATTACK:
				if (skill->End()) {//若攻击动画播放完毕，执行伤害
					MQ_UnderAttack(player, skill, monster_queue);
					if (temp->next != NULL) skill = temp->next->skill;
					else skill = NULL;
					OutQueue(pre);
				}
				break;
			}
		}
	}
}

ObjectNode::ObjectNode() :object(nullptr) {}

ObjectNode::ObjectNode(MyObject *obj) :object(obj) {}

ObjectQueue::ObjectQueue():MyQueue(20){
	head = new ObjectNode;
	head->next = tail;//队首的下一个元素为队尾
}

bool ObjectQueue::Empty()
{
	return (head->next == nullptr);
}

void ObjectQueue::InQueue(MyObject *obj){
	if (!Full()) {
		ObjectNode *temp = new ObjectNode(obj);
		if (Empty()) {//若为空，则初始化尾节点并重连
			tail = temp;
			head->next = tail;
		}
		else {
			tail->next = temp;//尾节点的指针域指向该节点
			tail = temp;//该节点成为新尾节点
		}
		length++;
	}
}

void ObjectQueue::OutQueue(){
	if (!Empty()) {
		head->next = head->next->next;
		length--;
	}
}

void ObjectQueue::Select(HDC &mdc, HDC &bufdc, bool clear){
	if (!Empty() && head->next->object->End() && clear) OutQueue();//若结束则清除，出队
	for (ObjectNode *temp = head->next; temp != NULL; temp = temp->next) {//逐个选取每个对象
		temp->object->Select(mdc, bufdc);
	}
}

void ObjectQueue::TransSelect(HDC &mdc, HDC &bufdc, int r, int g, int b, bool clear){
	if (!Empty() && head->next->object->End() && clear) OutQueue();//若结束则清除，出队
	for (ObjectNode *temp = head->next; temp != NULL; temp = temp->next) {//逐个选取每个对象
		temp->object->TransSelect(mdc, bufdc, r, g, b);
	}
}

void ObjectQueue::IFrame(){
	for (ObjectNode *temp = head->next; temp != NULL; temp = temp->next) {
		temp->object->IFrame();//全体成员增帧
	}
}

void ObjectQueue::Clear(){
	head->next = nullptr;
	length = 0;
}
