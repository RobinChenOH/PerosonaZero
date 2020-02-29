#include "stdafx.h"

Item::Item(int new_rarity, int i) : rarity(new_rarity), number(i) {}

const int & Item::Get_Rarity() { return rarity; }
const int & Item::Get_Number() { return number; }
const CString & Item::Get_Name() { return name; }

NormalWeapon::NormalWeapon(int new_rarity, int i, int new_al, int new_au, DamageBuilder new_atkED) : Item(new_rarity, i),//���캯��������ϡ�жȣ��������Ƿ����ɱ������׺
	atkED({ new_atkED.type,(new_atkED.type >= 0 ? Random(new_atkED.upper,new_atkED.lower) : 0) }), atk_lower(new_al), atk_upper(new_au) {
	critical_chance = { -1,0 }; critical_damage = { -1,0 };
	switch (rarity) {//��ϡ�жȾ�����ſ���
	case NORMAL:
		name = normal_weapon_name[i]; break;
	case LEGENDARY:
		name = legendary_weapon_name[i - 10]; break;
	case RELIC:
		name = relic_weapon_name[i - 20]; break;
	default:break;
	}
	//��ֻ��40%�������ɱ������ʴ�׺��50%�������ɱ����˺���׺
	if (Random(10, 1) <= 4) {
		critical_chance.type = 0;
		switch (rarity) {
		case NORMAL:
			critical_chance.value = Random(10, 6); break;
		case LEGENDARY:
			critical_chance.value = Random(15, 11); break;
		case RELIC:
			critical_chance.value = Random(30, 26); break;
		default:break;
		}
	}
	if (Random(10, 1) <= 5) {
		critical_damage.type = 0;
		switch (rarity) {
		case NORMAL:
			critical_damage.value = Random(50, 35); break;
		case LEGENDARY:
			critical_damage.value = Random(80, 65); break;
		case RELIC:
			critical_damage.value = Random(100, 85); break;
		default:break;
		}
	}
}

const int NormalWeapon::Get_atkVL() { return Random(atk_upper, atk_lower); }
const int & NormalWeapon::Get_atkLower() { return atk_lower; }
const int & NormalWeapon::Get_atkUpper() { return atk_upper; }
const DamageStorage & NormalWeapon::Get_atkED() { return atkED; }
const DamageStorage & NormalWeapon::Get_CriticalChance() { return critical_chance; }
const DamageStorage & NormalWeapon::Get_CriticalDamage() { return critical_damage; }
const DamageStorage & NormalWeapon::Get_PenetrateED() { return NULLDAMAGE; }
const DamageStorage & NormalWeapon::Get_ElementED() { return NULLDAMAGE; }
const DamageStorage & NormalWeapon::Get_DotED() { return NULLDAMAGE; }
const SpecialDamageStorage & NormalWeapon::Get_SpecialEffect() { return NULLSPECIAL; }

CString & NormalWeapon::Get_SpecialEffects(){
	CString str("\0");
	return str;
}

LegendaryWeapon::LegendaryWeapon(int new_rarity, int i, int new_al, int new_au, DamageBuilder new_atkED, DamageBuilder new_penetrateED,
	DamageBuilder new_elementED, DamageBuilder new_dotED) :
	NormalWeapon(new_rarity, i, new_al, new_au, new_atkED),//��ʼ��ϡ�жȡ����ơ�����������ֵ
	//�������˾�ֻ��type�Ǹ�ʹ����
	penetrateED({ new_penetrateED.type,(new_penetrateED.type >= 0 ? Random(new_penetrateED.upper,new_penetrateED.lower) : 0) }),
	elementED({ new_elementED.type,(new_elementED.type >= 0 ? Random(new_elementED.upper,new_elementED.lower) : 0) }),
	dotED({ new_dotED.type,(new_dotED.type >= 0 ? Random(new_dotED.upper,new_dotED.lower) : 0) }) {}

const DamageStorage & LegendaryWeapon::Get_PenetrateED() { return penetrateED; }
const DamageStorage & LegendaryWeapon::Get_ElementED() { return elementED; }
const DamageStorage & LegendaryWeapon::Get_DotED() { return dotED; }

RelicWeapon::RelicWeapon(int i, int new_al, int new_au, DamageBuilder new_atkED, DamageBuilder new_penED, DamageBuilder rw_element[], DamageBuilder rw_dot[],
	SpecialDamageBuilder rw_special[]) :
	LegendaryWeapon(RELIC, i, new_al, new_au, new_atkED, new_penED, rw_element[i - 20], rw_dot[i - 20]),
	special_effect({ rw_special[i - 20].effect_type,rw_special[i - 20].concrete_type,rw_special[i - 20].object,Random(rw_special[i - 20].upper,rw_special[i - 20].lower) }) {
	special_content = relic_weapon_special[i - 20];//������Ч����
}

const SpecialDamageStorage & RelicWeapon::Get_SpecialEffect() { return special_effect; }

CString & RelicWeapon::Get_SpecialEffects(){
	return special_content;
}

NormalWeapon * CreateWeapon(WeaponBuilder * w_builder){
	switch (w_builder->Rarity()) {//����ϡ�жȹ�������
	case NORMAL: {//��ͨ����
		int item_choice = Random(NW_TYPE_MAXIMUM - 1, 0);//���ѡ��һ����ͨ���������
		int atk_flag = Random(1, 0);//�����Ƿ����ɹ���������ֵ
		int atk_upper = 5, atk_lower = 0;//��������������
		DamageBuilder n_db = { atk_flag - 1 ,atk_upper,atk_lower };//��������
		NormalWeapon *temp = new NormalWeapon(NORMAL, item_choice, 0, 5, n_db);//��������
		return temp;
		break;
	}
	case LEGENDARY: {//��������
		int item_choice = Random(LW_TYPE_MAXIMUM - 1, 0);//���ѡ��һ���������������
		int choice[10] = { -1,-1,-1,-1 };//����������ֵ����͸������ֵ��Ԫ�����ˡ�dot����
		int affix_num = 0;//�����ɵĴ�׺������Ҳ���ڿ��Ƶ�ǰ���ɵĴ�׺
		int affix_choice;//���ѡ��ѡ�񵽵Ĵ�׺����0��9���ѡ�������
		while (affix_num < 3) {//�ܹ�����������׺
			affix_choice = Random(3, 0);//��������׺��ѡ��һ��
			if (choice[affix_choice] == -1) {//���ô�׺δ����
				choice[affix_choice] = 0;//�����ɸ�����׺
				if (affix_choice == 2 || affix_choice == 3) choice[affix_choice] = Random(3, 0);//���ΪԪ�����˻�dot���������ɶ�Ӧ��Ԫ��
				else choice[affix_choice] = 0;//�������ɴ�׺����
				affix_num++;//��׺��������
			}
			else continue;//����ִ����һ��ѭ��
		}
		//��������
		DamageBuilder atk = { choice[0],10,5 };
		DamageBuilder pen = { choice[1],10,5 };
		DamageBuilder ele = { choice[2],15,11 };
		DamageBuilder dot = { choice[3],9,4 };
		LegendaryWeapon *temp = new LegendaryWeapon(LEGENDARY, item_choice + 10, 6, 10, atk, pen, ele, dot);//��������
		return temp;
		break;
	}
	case RELIC: {//��������
		int item_choice = Random(RW_TYPE_MAXIMUM - 1, 0);//���ѡ��һ���������������
		int atk_flag = Random(10, 1);
		int pen_flag = Random(10, 1);
		DamageBuilder atk = { (atk_flag >= 7 ? 0 : -1), 15, 10 };//�ٷ�֮��ʮ�������ɹ���������ֵ
		DamageBuilder pen = { (pen_flag >= 7 ? 0 : -1), 15, 10 };//�ٷ�֮��ʮ�������ɴ�͸������ֵ
		RelicWeapon *temp = new RelicWeapon(item_choice + 20 , 20, 25, atk, pen, rw_element, rw_dot, rw_special);
		return temp;
		break;
	}
	default:
		return nullptr; break;
	}
}