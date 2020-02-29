#pragma once

class Player :public MyObject {
public:
	Player();//无参构造函数，用于创建新的玩家对象
	//行动类函数
	void Wait();//静止函数，播放静止动画
	void Move();//移动函数，播放移动动画
	void MoveRight();//右移函数
	void MoveLeft();//左移函数
	void Decease();//死亡函数，播放死亡动画并返回上一个存档点
	void Revive();//复生函数，执行死亡惩罚
	void DrinkHealthPotions();//喝下生命药水，恢复80%生命
	void DrinkManaPotions();//喝下法力药水，恢复80%法力

	//收益类函数
	void GainExperience(const int &);//获取经验函数，修改人物的经验值
	void LevelUp();//升级函数，播放升级动画，修改等级，清空经验槽
	void Collect(WeaponTempInventory &);//拾取函数，从临时武器库拾取对应坐标的武器构造器，构造武器返回武器库
	void CollectWeapon(NormalWeapon *);//拾取函数，播放拾取动画，向武器库和装备库添加物品
	void BrowseInventory(HDC &mdc, HDC &bufdc);//浏览武器库函数，暂停游戏
	void SelectWeapon();//选取装备，更新装备
	void RegenerateHealth();//恢复生命
	void RegenerateMana();//恢复法力值

	//攻击类函数
	void Curse();//施法函数，播放施法动画，构造技能，不同按键触发不同元素和攻击方式
	void Attack();//攻击函数，按状态选择不同攻击类型
	void CauseDamage(Skill *, Monster *);//传参，从某个技能传入值后进行计算，再对指定敌人造成伤害
	void UnderAttack();//受击函数，播放受击动画

	//减益类函数
	void GetHurt(int );//受伤害函数，生命值减少
	bool ExpendMana(Skill *);//消耗法力值构造技能

	//访问器
	const int &Velocity();//速度
	const int &State();//状态
	const int &Level();//玩家等级，用于平衡
	const float &Get_Coefficient(const int &);//获取升级系数
	float Health_rate();//玩家当前生命值与总生命值之比
	float Mana_rate();//玩家当前法力值与总法力之比
	Damage &Get_Damage();//伤害
	Affinity &Get_Affinity();//减耗
	Defense &Get_Resistance();//抗性
	WeaponInventory *Inventory();//武器库访问器

	//重写
	virtual void IFrame();
	virtual void Select(HDC &,HDC &);

private:
	//辅助函数
	void UnloadWeapon(NormalWeapon *current);//取下武器
	void LoadWeapon(NormalWeapon *current);//装上武器
	void ReadBasicAttributes(HDC &, CString &);//显示基础属性
	void ReadEnhancedDamage(HDC &, CString &);//显示增伤属性
	void ReadResistance(HDC &, CString &);//显示抗性

	//等级相关
	int level;//玩家等级，等级提升会提高玩家所有能力
	int experience;//玩家已获得经验值
	int experience_maximum;//当前等级最大经验值，经验值满后会自动升级

	//属性相关
	int velocity;//玩家速度
	//攻击能力
	int attack_ability;//攻击能力值，作为增伤之一，随等级提升
	Damage enhanced_damage;//伤害增伤值

	//施法能力
	int mana;//玩家法力值，释放技能需要耗费法力值
	int current_mana;//玩家当前法力值
	int regeneration_mana;//每秒回复能量
	Affinity affinity;//伤害亲和度

	//防御能力
	int health;//玩家生命值
	int current_health;//玩家当前生命值，生命值为零玩家死亡
	int regeneration_health;//每秒回复生命
	Defense resistance;//伤害抗性

	//武器栏,用链表储存，方便拾取和丢弃
	WeaponInventory inventory;

	//计时器
	DWORD health_pre;
	DWORD health_now;
	DWORD mana_pre;
	DWORD mana_now;
};