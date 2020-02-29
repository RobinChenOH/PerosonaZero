#pragma once

class Player :public MyObject {
public:
	Player();//�޲ι��캯�������ڴ����µ���Ҷ���
	//�ж��ຯ��
	void Wait();//��ֹ���������ž�ֹ����
	void Move();//�ƶ������������ƶ�����
	void MoveRight();//���ƺ���
	void MoveLeft();//���ƺ���
	void Decease();//������������������������������һ���浵��
	void Revive();//����������ִ�������ͷ�
	void DrinkHealthPotions();//��������ҩˮ���ָ�80%����
	void DrinkManaPotions();//���·���ҩˮ���ָ�80%����

	//�����ຯ��
	void GainExperience(const int &);//��ȡ���麯�����޸�����ľ���ֵ
	void LevelUp();//�������������������������޸ĵȼ�����վ����
	void Collect(WeaponTempInventory &);//ʰȡ����������ʱ������ʰȡ��Ӧ�����������������������������������
	void CollectWeapon(NormalWeapon *);//ʰȡ����������ʰȡ���������������װ���������Ʒ
	void BrowseInventory(HDC &mdc, HDC &bufdc);//��������⺯������ͣ��Ϸ
	void SelectWeapon();//ѡȡװ��������װ��
	void RegenerateHealth();//�ָ�����
	void RegenerateMana();//�ָ�����ֵ

	//�����ຯ��
	void Curse();//ʩ������������ʩ�����������켼�ܣ���ͬ����������ͬԪ�غ͹�����ʽ
	void Attack();//������������״̬ѡ��ͬ��������
	void CauseDamage(Skill *, Monster *);//���Σ���ĳ�����ܴ���ֵ����м��㣬�ٶ�ָ����������˺�
	void UnderAttack();//�ܻ������������ܻ�����

	//�����ຯ��
	void GetHurt(int );//���˺�����������ֵ����
	bool ExpendMana(Skill *);//���ķ���ֵ���켼��

	//������
	const int &Velocity();//�ٶ�
	const int &State();//״̬
	const int &Level();//��ҵȼ�������ƽ��
	const float &Get_Coefficient(const int &);//��ȡ����ϵ��
	float Health_rate();//��ҵ�ǰ����ֵ��������ֵ֮��
	float Mana_rate();//��ҵ�ǰ����ֵ���ܷ���֮��
	Damage &Get_Damage();//�˺�
	Affinity &Get_Affinity();//����
	Defense &Get_Resistance();//����
	WeaponInventory *Inventory();//�����������

	//��д
	virtual void IFrame();
	virtual void Select(HDC &,HDC &);

private:
	//��������
	void UnloadWeapon(NormalWeapon *current);//ȡ������
	void LoadWeapon(NormalWeapon *current);//װ������
	void ReadBasicAttributes(HDC &, CString &);//��ʾ��������
	void ReadEnhancedDamage(HDC &, CString &);//��ʾ��������
	void ReadResistance(HDC &, CString &);//��ʾ����

	//�ȼ����
	int level;//��ҵȼ����ȼ���������������������
	int experience;//����ѻ�þ���ֵ
	int experience_maximum;//��ǰ�ȼ������ֵ������ֵ������Զ�����

	//�������
	int velocity;//����ٶ�
	//��������
	int attack_ability;//��������ֵ����Ϊ����֮һ����ȼ�����
	Damage enhanced_damage;//�˺�����ֵ

	//ʩ������
	int mana;//��ҷ���ֵ���ͷż�����Ҫ�ķѷ���ֵ
	int current_mana;//��ҵ�ǰ����ֵ
	int regeneration_mana;//ÿ��ظ�����
	Affinity affinity;//�˺��׺Ͷ�

	//��������
	int health;//�������ֵ
	int current_health;//��ҵ�ǰ����ֵ������ֵΪ���������
	int regeneration_health;//ÿ��ظ�����
	Defense resistance;//�˺�����

	//������,�������棬����ʰȡ�Ͷ���
	WeaponInventory inventory;

	//��ʱ��
	DWORD health_pre;
	DWORD health_now;
	DWORD mana_pre;
	DWORD mana_now;
};