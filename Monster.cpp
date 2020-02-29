#include "stdafx.h"
extern WeaponTempInventory temp_inventory;
extern int basic_level;

Monster::Monster(MyObjectBuilder *mobj, int x, int y, int exp, int v, int hls, float atk, int arm, int obj, int rg, int et) : MyObject(mobj[MOVE], x, y),
monster_experience(exp), velocity(v), current_velocity(v), health(hls), current_health(health), damage(atk), armor(arm), object(obj), range(rg), element_type(et), attacked(false),
dot_enhanced_damage(0), image_head(mobj), arcane_detonation(false), faint(false) {}

void Monster::Attack() {
	if (state != ATTACK) {
		SetAttribute(image_head[ATTACK], ATTACK, true, this->show);
	}
}

void Monster::CauseDamage(Player &player) {
	Attack();
	if (End()) {
		float atk_value = damage*(1 + element_damage[element_type] * 0.01);//获取基础攻击伤害值并元素增伤一次
		float M = player.Get_Resistance().Get_Defense(ARM_PT, 0) / (player.Get_Resistance().Get_Defense(ARM_PT, 0) + 200);//护甲减伤系数
		float N = player.Get_Resistance().Get_Defense(ELE_PT, element_type) / (player.Get_Resistance().Get_Defense(ELE_PT, element_type) + 100);//抗性减伤系数
		atk_value *= (1 - M)*(1 - N);//人物自身减伤
		player.GetHurt((int)atk_value);
	}
}

void Monster::Move() {
	if (state != MOVE) {
		SetAttribute(image_head[MOVE], MOVE, true, this->show);
	}
}

void Monster::Dead() {
	if (state != DEAD) {
		SetAttribute(image_head[DEAD], DEAD, true, this->show);
		if (dot.Get_State() == ARCANE) arcane_detonation = true;
		DropItem();
	}
}

void Monster::Thrust() {
	if (state != ATTACK) {
		current_velocity = 40;//速度激增
		SetAttribute(image_head[ATTACK], ATTACK, true, this->show);
		damage *= 3;
	}
}

void Monster::Select(HDC &mdc, HDC &bufdc) {
	if (show) {//若显示，则对图片进行透明处理，并贴血条，进行dot值的判定，对怪物造成dot伤害
		SelectObject(bufdc, image);
		BitBlt(mdc, x, y, width, height, bufdc, width * cframe, height, SRCAND);
		BitBlt(mdc, x, y, width, height, bufdc, width * cframe, 0, SRCPAINT);
		healthbar.SetXY(x, y - 100);
		healthbar.Select(mdc, bufdc, Health_rate());

		if (dot.Get_State() != NON_ELEMENT) {
			if (dot.DotValidate()) {//如果时间间隔到达，则dot生效
				switch (dot.Get_State()) {
				case FIRE: Combust(); break;
				case ARCANE:ArcanePower(); break;
				case FROST: FrostBite(); break;
				case ELECTRICITY:Paralyze(); break;
				default:break;
				}
				dot.UpdatePre();//更新上一次触发dot的时间
			}
			if (dot.DotEnd()) {//若dot结束
				dot.Clear();//重置dot
				SetAttribute(image_head[this->state], this->state, this->loop, this->show);//重置图片
				current_velocity = velocity;//重置速度
				faint = false;
			}
		}
	}
}

void Monster::DropItem() {
	int probability = 20;
	int result = Random(100, 1);
	if (result <= probability) {//掉落武器
		int coe = Random(10, 1);
		int rarity = NORMAL;//30%几率普通
		if (coe >= 4 && coe <= 8) rarity = LEGENDARY;//50%几率传奇
		if (coe == 9 || coe == 10) rarity = RELIC;//20%几率遗物
		int caly = y + height / 2;
		WeaponBuilder *temp = new WeaponBuilder(x, caly, rarity);
		temp_inventory.Store(temp);
	}
}

void Monster::MoveToPlayer(Player &player) {
	if (!faint) {
		if (player.C_X() <= c_x) MoveLeft();
		else MoveRight();
		if (abs(C_X() - player.C_X()) <= range) {
			Attack();
		}
		else if (object == MUMMY) Thrust();
		else Move();
	}
}

void Monster::MoveLeft() {
	x -= current_velocity;
}

void Monster::MoveRight() {
	x += current_velocity;
}

void Monster::MoveLeft(const int &velocity) {
	x -= velocity;
}

void Monster::MoveRight(const int &velocity) {
	x += velocity;
}

void Monster::UnderAttack(int &value) {
	current_health -= value;
	if (current_health <= 0) Dead();
}

void Monster::UpdateDot(const int &e_type, int span, int interval) {//更新dot
	dot.SetElement(e_type);
	dot.UpdateSpan(span);
	dot.UpdateInterval(interval);
	dot.UpdateStart();
	dot.UpdatePre();
}

void Monster::UnderDot(const int &e_type,const int &coe) {//更新怪物的图片
	if (dot.Get_State() != e_type) {
		UpdateDot(e_type, 3000, 250);
		dot_enhanced_damage = coe;
		switch (e_type) {
		case FIRE:SetAttribute(image_head[COMBUST], this->state, this->loop, this->show); break;
		case ARCANE:SetAttribute(image_head[ARCANEPOWER], this->state, this->loop, this->show); break;
		case FROST:SetAttribute(image_head[FROSTBITE], this->state, this->loop, this->show); break;
		case ELECTRICITY:SetAttribute(image_head[PARALYZE], this->state, this->loop, this->show); break;
		default:break;
		}
	}
}

void Monster::Combust() {
	float atk_value = health * 0.04 * (1 + dot_enhanced_damage * 0.01);//计算dot值,燃烧基础每次燃烧最大生命值8%
	int pen_ed = 0;
	atk_value *= DR_Coe(pen_ed, FIRE);
	int atk_int_value = (int)atk_value;
	UnderAttack(atk_int_value);//造成伤害
}

int Monster::ArcanePower(){
	return (int)((float)(health*0.25 * (1 + dot_enhanced_damage * 0.01)));//奥能造成最大生命值25%的伤害
}

void Monster::FrostBite() {
	current_velocity *= 0.9;
	if (current_velocity == 0) faint = true;
}

void Monster::Paralyze(){
	float atk_value = health * 0.05 * (1 + dot_enhanced_damage * 0.01);//计算dot值,瘫痪每次造成最大生命值5%的伤害
	int atk_int_value = (int)atk_value;
	UnderAttack(atk_int_value);//造成伤害
	if (Random(1, 0) == 1) { current_velocity = 0; }
}

void Monster::UpdateAttributes(const int &level) {
	for (int i = 0; i < level; i++) {
		health *= 2.0;
		current_health *= 2.0;
		damage *= 2.0;
		armor *= 2.0;
	}
}

const int & Monster::Velocity() {
	return velocity;
}

const int & Monster::Get_Range() {
	return range;
}

const int & Monster::Get_State() {
	return state;
}

const int & Monster::Get_Object() {
	return object;
}

const int & Monster::Get_Armor() {
	return armor;
}

const int & Monster::Get_Resistance(const int &e_type) {
	return element_resistance[e_type];
}

const int & Monster::Get_VulValue(const int &object) {
	return vul_value[object];
}

const int & Monster::Get_Bonus() {
	return monster_experience;
}

bool Monster::Arcane_Detonation(){
	return arcane_detonation;
}

bool Monster::FrostBited(){
	if (dot.Get_State() == FROST) {
		SetAttribute(image_head[FROSTBITE], this->state, this->loop, this->show);
		return true;
	}
	else return false;
}

float Monster::Health_rate() {
	return (float)current_health / (float)health;
}

float Monster::DR_Coe(const int &pen_ed,const int &e_type){
	float M = armor / (armor + 200);//护甲减伤系数
	M *= (1 - (float)pen_ed*0.01);//穿透力增伤
	float N;
	if (element_resistance[e_type] <= -100) {
		N = -(float)(element_resistance[e_type] + 100) / (float)(element_resistance[e_type]);
	}
	else {
		N = (float)element_resistance[e_type] / (float)(element_resistance[e_type] + 100);//抗性减伤系数
	}
	return (1 - M)*(1 - N);
}

void Monster::Vulnerate(const int & object, const int &value) {
	vul_value[object] += value;
}

Zombie::Zombie(int x, int y) : Monster(zombie_image, x, y, 50, 5, 40, 10, 10, ZOMBIE, 50, NON_ELEMENT) {
	velocity = Random(7, 4);
	element_resistance[FIRE] = -60;
}

Mummy::Mummy(int x, int y) : Monster(mummy_image, x, y, 50, 5, 40, 10, 10, MUMMY, 50, NON_ELEMENT), thrust_cd(5000), pre(0) {
	velocity = Random(7, 4);
	element_resistance[FROST] = -50;
	element_resistance[FIRE] = -40;
}

void Mummy::FrostBite(){
	current_velocity *= 0.3;
}

Gargoyles::Gargoyles(int x, int y) : Monster(gargoyles_image, x, y, 50, 10, 100, 50, 100, GARGOYLES, 50, NON_ELEMENT) {
	velocity = Random(12, 8);
	element_resistance[ARCANE] = -70;
}

Cattle::Cattle(int x, int y) : Monster(cattle_image, x, y, 50, 15, 40, 10, 10, CATTLE, 50, NON_ELEMENT) {
	velocity = Random(15, 13);
	element_resistance[ELECTRICITY] = -30;
}

void Cattle::Paralyze(){
	float atk_value = 10 * (1 + dot_enhanced_damage * 0.01);//计算dot值
	int atk_int_value = (int)atk_value;
	UnderAttack(atk_int_value);//造成伤害
	if (Random(1, 0) == 1) { current_velocity = 0; }
}

Monster * CreateMonster(const int &level,const int &rarity) {
	//生成随机坐标
	int x = Random(1700, 1200);
	Monster *monster;
	switch (rarity) {
	case NORMAL: {//普通的为僵尸或者牛魔
		if (Random(1, 0) == 1) monster = new Zombie(x, 300);
		else monster = new Cattle(x, 300);
		break;
	}
	case LEGENDARY://传奇的为牛魔或者石像鬼
		if (Random(1, 0) == 1) monster = new Cattle(x, 300);
		else monster = new Gargoyles(x, 300);
		break;
	case RELIC: {//遗物的为石像鬼或者木乃伊
		if (Random(1, 0) == 1) monster = new Mummy(x, 300);
		else monster = new Gargoyles(x, 300);
		break;
	}
	default:monster = nullptr;
	}
	monster->UpdateAttributes(level);
	return monster;
}
