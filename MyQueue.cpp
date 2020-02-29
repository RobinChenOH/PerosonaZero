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
	head->next = tail;//���׵���һ��Ԫ��Ϊ��β
}

bool MonsterQueue::Empty() {
	return (head->next == nullptr);
}

int MonsterQueue::Get_Front() {//������ǰ��Ԫ��
	int front = 1200;
	if (head->next == NULL) {
		return front;
	}
	for (MonsterNode *temp = head->next; temp != NULL; temp = temp->next) {
		if (temp->monster->C_X() < front) {//���������������С����ǰ������
			front = temp->monster->C_X();//����
		}
	}
	return front;
}

void MonsterQueue::InQueue(Monster *new_monster) {//��ӣ��ڶ�β����
	if (!Full()) {//��δ��
				  //���
		MonsterNode *temp = new MonsterNode(new_monster);//��ʼ��һ������ڵ�
		if (Empty()) {
			tail = temp;//��β�ڵ�Ϊ�գ����ʼ��β�ڵ�
			head->next = tail;
		}
		else {
			tail->next = temp;//β�ڵ��ָ����ָ��ýڵ�
			tail = temp;//�ýڵ��Ϊ��β�ڵ�
		}
		length++;
	}
}

void MonsterQueue::OutQueue(MonsterNode *pre_monster) {//����,����Ĳ���Ϊ��ɾ���Ľڵ��ǰ��ָ��
	if (!Empty()) {//��δ��
		if (pre_monster->next != tail) {//����Ҫɾ���Ĳ���β�ڵ�
			MonsterNode *temp = pre_monster->next;//�ݴ�ýڵ�
			pre_monster->next = temp->next;//ɾ��
		}
		else {//��ɾ������β�ڵ㣬��ֱ��ɾ��
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
	for (MonsterNode *temp = head->next, *pre = head; temp != NULL; pre = temp, temp = temp->next) {//���ѡȡÿ������
		temp->monster->Select(mdc, bufdc);
		if (temp->monster->Get_State() == DEAD&&temp->monster->End()) {//����������
			if (temp->monster->Arcane_Detonation()) {//���������ܱ�ը
				int value = temp->monster->ArcanePower();
				UnderAttack(value, 400, temp->monster);
			}
			OutQueue(pre);//������ӣ����Ż�ɱ����
			YAuxObject *obj = new YAuxObject(kill, temp->monster->X() - 20, temp->monster->Y() + 40);
			obj->SetShow(true); obj->SetLoop(false);
			object_queue.InQueue(obj);
		}
	}
}

void MonsterQueue::IFrame() {
	for (MonsterNode *temp = head->next; temp != NULL; temp = temp->next) {
		temp->monster->IFrame();//ȫ���Ա��֡
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
		for (MonsterNode *tmp = head->next, *pre = head; tmp != NULL; pre = tmp, tmp = tmp->next) {//���������������
			if (abs(tmp->monster->C_X() - monster->C_X()) <= radius) {
				tmp->monster->UnderAttack(value);
			}
		}
}

SkillQueue::SkillQueue() :MyQueue(10) {
	head = new SkillNode;
	head->next = tail;//���׵���һ��Ԫ��Ϊ��β
}

bool SkillQueue::Empty() {
	return (head->next == nullptr);
}

void SkillQueue::Clear(){
	head->next = NULL;
}

void SkillQueue::InQueue(Skill *new_skill) {
	if (!Full()) {//��δ��
				  //���
		SkillNode *temp = new SkillNode(new_skill);//��ʼ��һ�����ܽڵ�
		if (Empty()) {
			tail = temp;//��β�ڵ�Ϊ�գ����ʼ��β�ڵ�
			head->next = tail;
		}
		else {
			tail->next = temp;//β�ڵ��ָ����ָ��ýڵ�
			tail = temp;//�ýڵ��Ϊ��β�ڵ�
		}
		length++;
	}
}

void SkillQueue::OutQueue(SkillNode *pre_skill) {
	if (!Empty()) {//��δ��
		if (pre_skill->next != tail) {
			SkillNode *temp = pre_skill->next;//�ݴ�ýڵ�
			pre_skill->next = temp->next;//ɾ��
		}
		else {
			pre_skill->next = NULL;
			tail = pre_skill;
		}
		length--;
	}
}

void SkillQueue::Select(HDC &mdc, HDC &bufdc) {
	for (SkillNode *temp = head->next; temp != NULL; temp = temp->next) {//���ѡȡÿ������
		temp->skill->Select(mdc, bufdc);
	}
}

void SkillQueue::IFrame() {
	for (SkillNode *temp = head->next; temp != NULL; temp = temp->next) {//���ѡȡÿ������
		temp->skill->IFrame();
	}
}

void SkillQueue::Play(Player &player, MonsterQueue &monster_queue) {
	if (!Empty()) {
		Skill *skill = head->next->skill;//��ʼ��һ������ָ��Ϊ��һ����Ч�ڵ�ļ���ָ�룬���ڲ�������
		for (SkillNode *temp = head->next, *pre = head; temp != NULL; pre = temp, temp = temp->next, (temp == NULL ? skill = NULL : skill = temp->skill)) {//�������ܶ���
			switch (skill->State()) {
			case MOVE:
				if (skill->EndEnroute()) {//����������ϣ������
					if (skill->Collide(monster_queue)) skill->Work();//��������ײ��������Ч
					else {
						if (temp->next != NULL) skill = temp->next->skill;//����Ϊβ�ڵ㣬������Ϊ��һ���ڵ�ļ�����
						else skill = NULL;//��Ϊβ�ڵ㣬�����ÿ�
						OutQueue(pre);
						skill = tail->skill;//��Ϊβ�ڵ�ļ�����
					}
				}
				else {//�����������
					skill->Enroute();//�����������
					if (skill->Collide(monster_queue)) skill->Work();//��������ײ��������Ч
				}
				break;
			case ATTACK:
				if (skill->End()) {//����������������ϣ�ִ���˺�
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
	head->next = tail;//���׵���һ��Ԫ��Ϊ��β
}

bool ObjectQueue::Empty()
{
	return (head->next == nullptr);
}

void ObjectQueue::InQueue(MyObject *obj){
	if (!Full()) {
		ObjectNode *temp = new ObjectNode(obj);
		if (Empty()) {//��Ϊ�գ����ʼ��β�ڵ㲢����
			tail = temp;
			head->next = tail;
		}
		else {
			tail->next = temp;//β�ڵ��ָ����ָ��ýڵ�
			tail = temp;//�ýڵ��Ϊ��β�ڵ�
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
	if (!Empty() && head->next->object->End() && clear) OutQueue();//�����������������
	for (ObjectNode *temp = head->next; temp != NULL; temp = temp->next) {//���ѡȡÿ������
		temp->object->Select(mdc, bufdc);
	}
}

void ObjectQueue::TransSelect(HDC &mdc, HDC &bufdc, int r, int g, int b, bool clear){
	if (!Empty() && head->next->object->End() && clear) OutQueue();//�����������������
	for (ObjectNode *temp = head->next; temp != NULL; temp = temp->next) {//���ѡȡÿ������
		temp->object->TransSelect(mdc, bufdc, r, g, b);
	}
}

void ObjectQueue::IFrame(){
	for (ObjectNode *temp = head->next; temp != NULL; temp = temp->next) {
		temp->object->IFrame();//ȫ���Ա��֡
	}
}

void ObjectQueue::Clear(){
	head->next = nullptr;
	length = 0;
}
