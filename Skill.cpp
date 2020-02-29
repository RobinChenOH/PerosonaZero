#include "stdafx.h"
using namespace std;

Skill::Skill(MyObjectBuilder *mob, int et, int at, int p_x, int p_y, int rg, int aoe, int ve, DWORD interval, DWORD cd) :MyObject(mob[et], p_x, p_y), element_type(et), action_type(at),
mana_cost(10), attack_range(rg), aoe_range(aoe), velocity(ve), object((ELEMENT_UPPER + 1)*action_type + element_type), image_head(mob), skill_cd(interval, cd) {//确定参数和法力消耗值,并计算技能编号
	switch (element_type) {//根据元素微调伤害放大系数
	case FIRE:magnification_factor = 110;
	case ARCANE:magnification_factor = 120; break;
	case FROST:magnification_factor = 100; break;
	case ELECTRICITY:magnification_factor = 130; break;
	default:break;
	}
}

void Skill::Enroute() { x += velocity; }

void Skill::NotWork(){
	if (state != MOVE) { 
		SetAttribute(image_head[element_type], MOVE, true, true);
	}
}

void Skill::Work(){
	if (action_type == STARSTRIKE&&element_type == ELECTRICITY) {
		if (state != ATTACK) state = ATTACK;
	}
	else {
		if (state != ATTACK) SetAttribute(image_head[element_type + 4], ATTACK, false, true);
	}
}

void Skill::SetElementType(int new_et) { element_type = new_et; }
const int & Skill::Get_Object() { return object; }
const int & Skill::Get_ElementType() { return element_type; }
const int & Skill::Get_ActionType() { return action_type; }
const int & Skill::Get_MagnificationFactor() { return magnification_factor; }
const int & Skill::Get_ManaCost() { return mana_cost; }
const int & Skill::Get_AttackRange() { return attack_range; }
const int & Skill::Get_AOERange() { return aoe_range; }

CoolDown & Skill::Skill_CD(){
	return skill_cd;
}

MissileSkill::MissileSkill(int et, int p_x, int p_y) : Skill(Missile, et, MISSILE, p_x, p_y, 1000, 0, 20, 0, 0) {
	//根据元素类型再调整一次伤害放大倍数
	//根据元素类型载入图片
	switch (element_type) {
	case FIRE:PlaySound(_T("Music\\fireballenroute.wav"), NULL, SND_FILENAME | SND_ASYNC); break;
	case ARCANE:PlaySound(_T("Music\\frost.wav"), NULL, SND_FILENAME | SND_ASYNC); break;
	case FROST:PlaySound(_T("Music\\fireballenroute.wav"), NULL, SND_FILENAME | SND_ASYNC); break;
	case ELECTRICITY:PlaySound(_T("Music\\electroball.wav"), NULL, SND_FILENAME | SND_ASYNC); break;
	}
}

bool MissileSkill::EndEnroute(){
	return (C_X() >= attack_range);
}

bool MissileSkill::Collide(MonsterQueue &m_q){
	if (C_X() >= m_q.Get_Front()) {
		switch (element_type) {
		case FIRE:PlaySound(_T("Music\\combust.wav"), NULL, SND_FILENAME | SND_ASYNC); break;
		case ARCANE:PlaySound(_T("Music\\arcanepower.wav"), NULL, SND_FILENAME | SND_ASYNC); break;
		case FROST:PlaySound(_T("Music\\frostbite.wav"), NULL, SND_FILENAME | SND_ASYNC); break; break;
		case ELECTRICITY:PlaySound(_T("Music\\electroballwork.wav"), NULL, SND_FILENAME | SND_ASYNC); break;
		dafault:break;
		}
	}
	return (C_X() >= m_q.Get_Front());
}

ChannellingSkill::ChannellingSkill(int et, int p_x, int p_y, int r) : Skill(Ray, et, RAY, p_x, p_y, 664, 0, 20, 300, 0), radius(r) {
	mana_cost = 50;
	attack_range = 640;
}

bool ChannellingSkill::EndEnroute(){
	return false;
}

bool ChannellingSkill::Collide(MonsterQueue &m_q){
	return true;
}

void ChannellingSkill::SetElementType(int ne){
	element_type = ne;
	SetAttribute(image_head[element_type], MOVE, true, true);
	switch (ne) {
	case FIRE:mana_cost = 50; break;
	case ARCANE:mana_cost = 60; magnification_factor *= 1.5; break;
	case FROST:mana_cost = 30; magnification_factor = 0; break;
	case ELECTRICITY:mana_cost = 40; magnification_factor *= 0.1; break;
	}
}

StarStrikeSkill::StarStrikeSkill(int et, int p_x, int p_y, int r, int d_x, int d_y) : Skill(Starstrike, et, STARSTRIKE, p_x, p_y, d_x, r, 30, 0, 8000), radius(r), d_x(d_x), d_y(d_y)
{
	mana_cost = 50;
	magnification_factor *= 2.0;
	attack_range = d_x;
	float w = d_x - x, h = d_y - y;
	float i = sqrt(x*x + y*y);
	v_x = velocity*w / i;
	v_y = velocity*h / i;
	if (element_type == ELECTRICITY) x = d_x;

	switch (element_type) {
	case FIRE:PlaySound(_T("Music\\firestarwork.wav"), NULL, SND_FILENAME | SND_ASYNC); break;
	case ARCANE:PlaySound(_T("Music\\arcane.wav"), NULL, SND_FILENAME | SND_ASYNC); break;
	case FROST:
	case ELECTRICITY:PlaySound(_T("Music\\thunder.wav"), NULL, SND_FILENAME | SND_ASYNC); break;
	}
}

void StarStrikeSkill::Enroute(){
	if (element_type != ELECTRICITY) {
		x += v_x; y += v_y;
	}
}

bool StarStrikeSkill::EndEnroute(){
	if (element_type == ELECTRICITY) return (End());
	return (y >= d_y);
}

bool StarStrikeSkill::Collide(MonsterQueue &m_q){
	if (EndEnroute()) {
		return true;
	}
	else return false;
}
