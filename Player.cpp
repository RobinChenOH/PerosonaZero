#include "stdafx.h"
extern bool levelup;							// 是否升级
extern HFONT hFont_message_title;
extern HFONT hFont_message_text;
extern ObjectQueue critical_queue;

Player::Player() :MyObject(player_prepare, 0, 150), level(1), experience(0), experience_maximum(150), velocity(7),
health(200), current_health(200), regeneration_health(25), mana(120), current_mana(120), regeneration_mana(10),
attack_ability(20) {
	//初始等级1，经验值0，升至下一级需要150经验，速度为10码/s，生命值2.0，法力值120，回蓝10/s，坐标位于最左端
	//增伤值、减耗值、抗性均为0
	state = MOTIONLESS; fv = 40;
	health_pre = GetTickCount();
	mana_pre = GetTickCount();
	LoadWeapon(inventory.Read());
	enhanced_damage.Enhance_Damage(CRI_STR_CHANCE, 0, 10);
	enhanced_damage.Enhance_Damage(CRI_STR_DAMAGE, 0, 50);
}

void Player::Wait(){
	if (state != MOTIONLESS) {
		SetAttribute(player_prepare, MOTIONLESS, true, true);
	}
}

void Player::Move(){
	if (state != MOVE) {
		SetAttribute(player_run, MOVE, true, true);
		frame = 9;
		velocity = 7;
	}
}

void Player::MoveRight(){
	x += velocity;
}

void Player::MoveLeft() {
	x -= velocity;
}

void Player::Decease(){
	SetAttribute(player_dead, DEAD, false, true);
	y += 100;
}

void Player::Revive(){
	current_health = health*0.3;
	current_mana = mana;
}

void Player::DrinkHealthPotions(){
	current_health = health*0.8;
}

void Player::DrinkManaPotions(){
	current_mana = mana*0.8;
}

void Player::GainExperience(const int &bonus) {
	experience += bonus;//获取经验值
	if (experience >= experience_maximum) LevelUp();//若经验值达到满值，升级
}

void Player::LevelUp(){
	for (;experience >= experience_maximum; experience -= experience_maximum, experience_maximum *= Get_Coefficient(LEVELMAX_UP)) {
		//循环执行，在经验值小于最大经验槽时结束循环，每次循环结束调整当前经验值和经验槽
		level++;//每次循环都使人物升级一次
		attack_ability *= Get_Coefficient(ATTACK_UP);
		health *= Get_Coefficient(HEALTH_UP);
		mana *= Get_Coefficient(MANA_UP);
		regeneration_health *= 1.1;
		regeneration_mana *= 1.1;

		current_health = health;
		current_mana = mana;
		levelup = true;
	}
}

void Player::Collect(WeaponTempInventory &t_inv){
	NormalWeapon *temp = t_inv.Discard(this->c_x);//获得武器
	if (temp != nullptr) {
		inventory.Store(temp);//存入武器
	}
}

void Player::CollectWeapon(NormalWeapon *temp){
	inventory.Store(temp);
}

void Player::BrowseInventory(HDC & mdc, HDC & bufdc){
	inventory.Browse(mdc, bufdc);//浏览武器库
	//输出人物信息
	CString affix;
	SetBkColor(mdc, TRANSPARENT);
	CRect rc(1100, 50, 1200, 200);
	SelectObject(mdc, hFont_message_title);
	SetTextColor(mdc, RGB(255, 0, 0));
	CString title("人物属性");
	DrawText(mdc, title, title.GetLength(), &rc, DT_LEFT);
	
	SetRect(&rc, 1000, 100, 1200, 640);
	SetBkColor(mdc, RGB(14, 14, 14));
	SelectObject(mdc, hFont_message_text);
	SetTextColor(mdc, RGB(255, 0, 100));
	CString info;
	ReadBasicAttributes(mdc, info);
	ReadEnhancedDamage(mdc, info);
	ReadResistance(mdc, info);
	
	DrawText(mdc, info, info.GetLength(), &rc, DT_LEFT);
}

void Player::SelectWeapon(){
	UnloadWeapon(inventory.Read());//卸下武器
	inventory.SelectWeapon();//选择武器
	LoadWeapon(inventory.Read());//装上武器
}

void Player::RegenerateHealth(){
	health_now = GetTickCount();
	if (health_now - health_pre >= 100) {
		if (current_health + regeneration_health*0.1 >= health) current_health = health;//若生命即将满，则置满
		else current_health += regeneration_health*0.1;//否则恢复生命
		health_pre = GetTickCount();//更新上一次时间
	}
}

void Player::RegenerateMana(){
	mana_now = GetTickCount();
	if (mana_now - mana_pre >= 100) {
		if (current_mana + regeneration_mana*0.1 >= mana) current_mana = mana;//若法力即将满，则置满
		else current_mana += regeneration_mana*0.1;//否则恢复法力
		mana_pre = GetTickCount();//更新上一次时间
	}
}

void Player::Curse(){
	SetAttribute(player_curse, CURSE, false, this->show);
}

void Player::Attack(){
	SetAttribute(player_attack, ATTACK, false, this->show);
}

void Player::CauseDamage(Skill *skill, Monster *monster) {
	//人物方面的增伤
	float atk_value = inventory.Read()->Get_atkVL()*(1 + attack_ability*0.01);//随机在武器白字上下限选取一个数字作为基础伤害值
	atk_value *= (1 + (float)skill->Get_MagnificationFactor()*0.01);//技能对于伤害的放大
	atk_value *= (1 + (float)enhanced_damage.Get_Damage(ATK_ED, 0)*0.01);//百分比增伤
	atk_value *= (1 + (float)enhanced_damage.Get_Damage(ELE_ED, skill->Get_ElementType())*0.01);//元素增伤
	atk_value *= (1 + (float)enhanced_damage.Get_Damage(IND_ED, skill->Get_ActionType())*0.01);//独立增伤
	atk_value *= (1 + (float)enhanced_damage.Get_Damage(STA_ED, state)*0.01);//状态增伤
	if (Random(100, 0) <= (float)enhanced_damage.Get_Damage(CRI_STR_CHANCE, 0)) {//若0至100内随机选取的数字小于等于暴击几率，则判定为暴击
		atk_value *= (1 + (float)enhanced_damage.Get_Damage(CRI_STR_DAMAGE, 0)*0.01);//暴击增伤
		MyObject *cri = new MyObject(critical, monster->X(), monster->Y());
		cri->SetShow(true); cri->SetLoop(false);
		critical_queue.InQueue(cri);
	}

																			  //怪物方面的增减伤
	monster->Vulnerate(0, (float)enhanced_damage.Get_Damage(VUL_ED, 0));//使怪物受更多全局易伤
	monster->Vulnerate(skill->Get_ElementType() + 1, (float)enhanced_damage.Get_Damage(VUL_ED, skill->Get_ElementType() + 1));//使怪物受更多元素易伤
	atk_value *= monster->DR_Coe(enhanced_damage.Get_Damage(PEN_ED, 0), skill->Get_ElementType());//怪物自身减伤
	atk_value *= (1 + monster->Get_VulValue(0));//全局易伤
	atk_value *= (1 + monster->Get_VulValue(skill->Get_ElementType()));//元素增伤
	atk_value *= (1 + (float)enhanced_damage.Get_Damage(DIS_ED, monster->Get_Object())*0.01);//歧视类增伤
	int atk_int_value = (int)atk_value;

	//将最后放大得到的伤害值传递给怪物，并传递dot增伤系数，触发dot
	monster->UnderDot(skill->Get_ElementType(), (float)enhanced_damage.Get_Damage(DOT_ED, skill->Get_ElementType()));
	monster->UnderAttack(atk_int_value);
	//如果怪物死亡则获取经验
	if (monster->Get_State() == DEAD && !monster->attacked) {
		GainExperience(monster->Get_Bonus());
		monster->attacked = true;
	}
}

void Player::UnderAttack(){
	if (state != HURT&&state != DEAD) {
		SetAttribute(player_defend, HURT, true, this->show);
		velocity = 0;
	}
}

void Player::GetHurt(int value){
	if (state != DEAD) {
		UnderAttack();
		current_health -= value;
		if (current_health <= 0) Decease();
	}
}

bool Player::ExpendMana(Skill *skill){
	float mana_cost = skill->Get_ManaCost();//读入技能的法力消耗值
											//计算减耗百分比，为(1-全局减耗)(1-元素减耗)(1-方式减耗)
	float total_affinity = (1 - affinity.Get_Affinity(ATK_AF, 0)*0.01) *(1 - affinity.Get_Affinity(ELE_AF, skill->Get_ElementType())*0.01)*(1 - affinity.Get_Affinity(ACT_AF, skill->Get_ActionType())*0.01);
	mana_cost *= total_affinity;
	if (current_mana < mana_cost) {//若当前法力值小于给定的法力消耗值
		return false;//施法失败
	}
	current_mana -= mana_cost;//否则减少法力值，施法成功
	return true;
}

const int & Player::Velocity(){
	return velocity;
}

const int & Player::State(){
	return state;
}

const int & Player::Level(){
	return level;
}

const float & Player::Get_Coefficient(const int &choice){
	switch (choice) {
	case ATTACK_UP:
		if (level >= 0 && level <= 10) return 1.5;//0到10级增伤1.5倍
		else if (level > 10 && level <= 20) return 1.7;//10到20级增伤1.7倍
		else return 1.0;//20级以上不再增伤
		break;
	case HEALTH_UP:
		if (level >= 0 && level <= 10) return 1.25;//0到10级增加1.5倍
		else if (level > 10 && level <= 20) return 1.15;//10到20级增加1.3倍
		else return 1.0;//20级以上不再增加
		break;
	case MANA_UP:
		if (level >= 0 && level <= 10) return 1.1;//0到10级增加1.1倍
		else if (level > 10 && level <= 20) return 1.05;//10到20级增加1.05倍
		else return 1.0;//20级以上不再增加
		break;
	case ARMOR_UP:
		if (level >= 0 && level <= 10) return 1.1;//0到10级增加1.1倍
		else if (level > 10 && level <= 20) return 1.2;//10到20级增加1.2倍
		else return 1.0;//20级以上不再增加
		break;
	case LEVELMAX_UP:
		if (level >= 0 && level <= 10) return 2.0;//0到10级增加2.0倍
		else if (level > 10 && level <= 20) return 1.5;//10到20级增加3.0倍
		else return 2.0;//20级以上为5.0倍
		break;
	default:break;
	}
}

Damage & Player::Get_Damage(){
	return enhanced_damage;
}

Affinity & Player::Get_Affinity(){
	return affinity;
}

Defense & Player::Get_Resistance(){
	return resistance;
}

float Player::Health_rate(){
	return (float)current_health / (float)health;
}

float Player::Mana_rate() {
	return (float)current_mana / (float)mana;
}

WeaponInventory * Player::Inventory(){
	return &inventory;
}

void Player::IFrame(){
	if (state == MOVE) {
		if (cframe == 8) cframe = 1;
		else cframe++;
	}
	else if (state == HURT) {
		if (End()) cframe = 2;
		else cframe++;
	}
	else {
		if (End()) {//若已是最后一帧，则根据是否循环重置帧
			if (loop) cframe = 0;
		}
		else cframe++;//否则若循环播放，则播放为下一帧
	}
}

void Player::Select(HDC &mdc, HDC &bufdc){
	SelectObject(bufdc, image);
	BitBlt(mdc, x, y, width, height, bufdc, width * cframe, height, SRCAND);
	BitBlt(mdc, x, y, width, height, bufdc, width * cframe, 0, SRCPAINT);
	if (current_health < health) RegenerateHealth();
	if (current_mana < mana) RegenerateMana();
}

void Player::UnloadWeapon(NormalWeapon * current){
	enhanced_damage.Weaken_Damage(ATK_ED, 0, current->Get_atkED().value);
	if (current->Get_CriticalChance().type > -1)
		enhanced_damage.Weaken_Damage(CRI_STR_CHANCE, 0, current->Get_CriticalChance().value);
	if (current->Get_CriticalDamage().type > -1)
		enhanced_damage.Weaken_Damage(CRI_STR_DAMAGE, 0, current->Get_CriticalDamage().value);
	//若非普通武器，继续读入初级增伤值
	if (inventory.Read()->Get_Rarity() != NORMAL) {
		if (current->Get_PenetrateED().type > -1)
			enhanced_damage.Weaken_Damage(PEN_ED, 0, current->Get_PenetrateED().value);
		if (current->Get_ElementED().type > -1)
			enhanced_damage.Weaken_Damage(ELE_ED, current->Get_ElementED().type, current->Get_ElementED().value);
		if (current->Get_DotED().type > -1)
			enhanced_damage.Weaken_Damage(DOT_ED, current->Get_DotED().type, current->Get_DotED().value);
	}
	//若为遗物武器，继续读入特效增伤值
	if (current->Get_Rarity() == RELIC) {
		switch (current->Get_SpecialEffect().effect_type) {//决定是增伤、减耗还是减伤
		case INTENSIFY_ATTACK:
			enhanced_damage.Weaken_Damage(current->Get_SpecialEffect().concrete_type, current->Get_SpecialEffect().object, current->Get_SpecialEffect().value); break;
		case ENERGY_AFFINITY:
			affinity.Weaken_Affinity(current->Get_SpecialEffect().concrete_type, current->Get_SpecialEffect().object, current->Get_SpecialEffect().value); break;
		case FORTIFY_DEFENCE:
			resistance.Weaken_Defense(current->Get_SpecialEffect().concrete_type, current->Get_SpecialEffect().object, current->Get_SpecialEffect().value); break;
		}
	}
}

void Player::LoadWeapon(NormalWeapon * current){
	//首先读入攻击力增伤值
	enhanced_damage.Enhance_Damage(ATK_ED, 0, current->Get_atkED().value);
	if (current->Get_CriticalChance().type > -1)
		enhanced_damage.Enhance_Damage(CRI_STR_CHANCE, 0, current->Get_CriticalChance().value);
	if (current->Get_CriticalDamage().type > -1)
		enhanced_damage.Enhance_Damage(CRI_STR_DAMAGE, 0, current->Get_CriticalDamage().value);
	//若非普通武器，继续读入初级增伤值
	if (inventory.Read()->Get_Rarity() != NORMAL) {
		if (current->Get_PenetrateED().type > -1)
			enhanced_damage.Enhance_Damage(PEN_ED, 0, current->Get_PenetrateED().value);
		if (current->Get_ElementED().type > -1)
			enhanced_damage.Enhance_Damage(ELE_ED, current->Get_ElementED().type, current->Get_ElementED().value);
		if (current->Get_DotED().type > -1)
			enhanced_damage.Enhance_Damage(DOT_ED, current->Get_DotED().type, current->Get_DotED().value);
	}
	//若为遗物武器，继续读入特效增伤值
	if (current->Get_Rarity() == RELIC) {
		switch (current->Get_SpecialEffect().effect_type) {//决定是增伤、减耗还是减伤
		case INTENSIFY_ATTACK:
			enhanced_damage.Enhance_Damage(current->Get_SpecialEffect().concrete_type, current->Get_SpecialEffect().object, current->Get_SpecialEffect().value); break;
		case ENERGY_AFFINITY:
			affinity.Enhance_Affinity(current->Get_SpecialEffect().concrete_type, current->Get_SpecialEffect().object, current->Get_SpecialEffect().value); break;
		case FORTIFY_DEFENCE:
			resistance.Enhance_Defense(current->Get_SpecialEffect().concrete_type, current->Get_SpecialEffect().object, current->Get_SpecialEffect().value); break;
		}
	}
}

void Player::ReadBasicAttributes(HDC &mdc, CString &info){//读基础属性
	CString affix;
	affix.Format(_T("当前等级:%d\n生命值上限:%d\n每秒回复生命:%d\n法力值上限:%d\n每秒回复法力:%d\n当前经验:%d\n升到下一级还需%d经验\n\n"),
		level, health, regeneration_health, mana, regeneration_mana, experience, experience_maximum - experience);
	info += affix;
}

void Player::ReadEnhancedDamage(HDC &mdc, CString &info){//读特效
	CString affix;
	float lower = (float)Inventory()->Read()->Get_atkLower()*(1 + attack_ability*0.01);
	float upper = (float)Inventory()->Read()->Get_atkUpper()*(1 + attack_ability*0.01);
	affix.Format(_T("基础伤害:%f-%f\n"), lower, upper);
	info += affix;
	affix.Format(_T("所有伤害提高:%d%%\n穿透力伤害提高%d%%\n暴击几率:%d%%\n暴击伤害:%d%%\n"), enhanced_damage.Get_Damage(ATK_ED, 0), enhanced_damage.Get_Damage(PEN_ED, 0),
		enhanced_damage.Get_Damage(CRI_STR_CHANCE, 0), enhanced_damage.Get_Damage(CRI_STR_DAMAGE, 0));
	info += affix;
	for (int i = 0; i <= ELEMENT_UPPER; i++) {
		if (enhanced_damage.Get_Damage(ELE_ED, i) > 0) {
			info += Get_ElementName(i, ELEMENT_ELE);
			affix.Format(_T("伤害提高%d%%\n"), enhanced_damage.Get_Damage(ELE_ED, i));
			info += affix;
		}
	}
	for (int i = 0; i <= ELEMENT_UPPER; i++) {
		if (enhanced_damage.Get_Damage(DOT_ED, i) > 0) {
			info += Get_ElementName(i, ELEMENT_DOT);
			affix.Format(_T("伤害提高%d%%\n"), enhanced_damage.Get_Damage(DOT_ED, i));
			info += affix;
		}
	}
	for (int i = 0; i <= ELEMENT_UPPER + 1; i++) {//易伤增伤
		if (enhanced_damage.Get_Damage(VUL_ED, i) > 0) {
			if (i == 0) {
				affix.Format(_T("对所有怪物提升%d%%的伤害\n"), enhanced_damage.Get_Damage(VUL_ED, i));
				info += affix;
			}
			else {
				info += Get_ElementName(i - 1, ELEMENT_ELE);
				affix.Format(_T("伤害会使敌人承受额外%d%%的伤害\n"), enhanced_damage.Get_Damage(VUL_ED, i));
				info += affix;
			}
		}
	}
	for (int i = 0; i < IND_ED_OBJ_MAX; i++) {//独立增伤
		if (enhanced_damage.Get_Damage(IND_ED, i) > 0) {
			info += Get_ActionName(i);
			affix.Format(_T("伤害提高%d%%\n"), enhanced_damage.Get_Damage(IND_ED, i));
			info += affix;
		}
	}
	for (int i = 0; i < DIS_ED_OBJ_MAX; i++) {//歧视增伤
		if (enhanced_damage.Get_Damage(DIS_ED, i) > 0) {
			info += "对" + Get_MonsterName(i) + "造成的伤害提高";
			affix.Format(_T("%d%%\n"), enhanced_damage.Get_Damage(DIS_ED, i));
			info += affix;
		}
	}
}

void Player::ReadResistance(HDC &mdc, CString &info){
	CString affix;
	affix.Format(_T("\n护甲值:%d\n火焰抗性:%d\n奥术抗性:%d\n冰霜抗性:%d\n闪电抗性:%d\n"), resistance.Get_Defense(ARM_PT, 0), resistance.Get_Defense(ELE_PT, FIRE),
		resistance.Get_Defense(ELE_PT, ARCANE), resistance.Get_Defense(ELE_PT, FROST), resistance.Get_Defense(ELE_PT, ELECTRICITY));
	info += affix;
}
