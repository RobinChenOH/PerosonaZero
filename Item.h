#pragma once
//��Ʒ��ϡ�ж����֣���Ϊ��ͨ�����������
//��ͨ��Ʒֻ���ӹ����������Ȼ�������
//������Ʒ������Ԫ���˺�����
//�������������¼��ܡ���Ч��
class WeaponBuilder;

class Item //��Ʒ�࣬��ʾ���Ե������Ʒ��������
{
public:
	Item(int, int);//���캯�������ض�ϡ�жȺ���Ź���һ����Ʒ
	//virtual void Show_Amap;//�ڵ�ͼ��չʾ��Ʒ����image_show����پ�����������Ʒ�ĵ�����ʰȡ
	//������
	const int &Get_Rarity();//ϡ�жȵķ�����
	const CString &Get_Name();//�������Ʒ�����
	const int &Get_Number();//������ŵķ�����
protected:
	int number;//��Ʒ���
	CString name;//��Ʒ������
	int rarity;//ϡ�жȣ�����紫�ν������ã�0Ϊ��ͨ��1Ϊ���棬2Ϊ����
	int level;//�����ȼ����ȼ��������˵ķ���
};

class NormalWeapon :public Item {//��ͨ�����࣬�̳�����Ʒ�࣬��Ϊ������Ļ���
public:
	NormalWeapon(int new_rarity, int i, int new_al, int new_au, DamageBuilder new_atkED);//���캯��������Ϊϡ�жȺ����ơ��ٷֱ�����ֵ����������
	//������
	const int Get_atkVL();//�������һ��λ�ڹ������޺͹������޵�ֵ
	const int &Get_atkLower();//�����˺�����
	const int &Get_atkUpper();//�����˺�����
	const DamageStorage &Get_atkED();//�ٷֱ�����ֵ������
	const DamageStorage &Get_CriticalChance();//�������ʷ�����
	const DamageStorage &Get_CriticalDamage();//�����˺�������
	const virtual DamageStorage &Get_PenetrateED();//��͸ֵ������
	const virtual DamageStorage &Get_ElementED();//Ԫ������ֵ������
	const virtual DamageStorage &Get_DotED();//DOT����ֵ������
	const virtual SpecialDamageStorage &Get_SpecialEffect();//������Чֵ������
	virtual CString &Get_SpecialEffects();//������Ч������
	friend NormalWeapon* CreateWeapon(WeaponBuilder *w_builder);//����������������һ������
protected:
	DamageStorage atkED;//�ٷֱ�����ֵ
	DamageStorage critical_chance;//��������
	DamageStorage critical_damage;//�����˺�
	int atk_lower;//����ֵ����
	int atk_upper;//����ֵ����
};

class LegendaryWeapon :public NormalWeapon {//���������������������������׺����ֵ���з�Χ����
public:
	LegendaryWeapon(int new_rarity, int i , int new_al, int new_au, DamageBuilder new_atkED, DamageBuilder new_penetrateED,
		DamageBuilder new_elementED, DamageBuilder new_dotED);//���������Ĺ��캯��
	//������
	const virtual DamageStorage &Get_PenetrateED();//��͸ֵ������
	const virtual DamageStorage &Get_ElementED();//Ԫ������ֵ������
	const virtual DamageStorage &Get_DotED();//Dot����ֵ������
protected:
	DamageStorage penetrateED;
	DamageStorage elementED;
	DamageStorage dotED;
};

class RelicWeapon :public LegendaryWeapon {//�����������ɹ̶�����ض������Բ��ڸ߷�Χ�����������Ӷ������������
public:
	RelicWeapon(int i, int new_al, int new_au, DamageBuilder new_atkED, DamageBuilder new_penED,DamageBuilder rw_element[], DamageBuilder rw_dot[], 
		SpecialDamageBuilder rw_special[]);//���캯�������ɴ�׺����ЧЧ������Ч����
	//������
	const virtual SpecialDamageStorage &Get_SpecialEffect();//������Чֵ������
	virtual CString &Get_SpecialEffects();//������Ч������
protected:
	SpecialDamageStorage special_effect;//������ЧЧ��
	CString special_content;//������Ч����
};