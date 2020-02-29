#pragma once
class WeaponInventory;//声明类，以使用friend关键字
class WeaponTempInventory;

class WeaponNode :public MyObject {//武器节点，只用来作为武器库链表的基本元素
	friend WeaponInventory;//声明武器库为武器节点的友元类，由于节点和链表通常绑定，可视为一体，因此对彼此开放受限成员不影响安全性
public:
	WeaponNode();
	WeaponNode(NormalWeapon *);//构造函数，默认类型为普通武器，可以用多态性指向更高级的传奇武器和遗物武器
	virtual ~WeaponNode();//析构函数
	void Show(HDC &, HDC &);//显示武器
	WeaponNode *Pre();//前驱指针访问器
	WeaponNode *Next();//后继指针访问器
protected:
	NormalWeapon *weapon;//武器数据域
	WeaponNode *pre;//前驱指针域
	WeaponNode *next;//后继指针域
	friend void Link(WeaponNode *, WeaponNode *);//辅助函数，链接两个指针
};

class WeaponInventory :public MyObject {//武器库，双向链表类
public:
	WeaponInventory();//初始化一个武器库,默认会有一件武器且最少手上会持有一件武器
	virtual ~WeaponInventory();//析构函数
	void Store(NormalWeapon *);//存放一个武器到武器库中
	void BrowseNext();//浏览下一件武器
	void BrowsePre();//浏览上一件武器
	void SelectWeapon();//确认该武器
	void DiscardWeapon();//删除该武器
	NormalWeapon * Read();//读取武器库当前选中的武器，返回武器数据，用于更新人物属性值

	WeaponNode * Head();//读取武器库的头指针
	WeaponNode * Tail();//读取武器库的尾指针
	bool Empty();//武器库是否为空
	bool Full();//武器库是否已满
	void Delete();//删除武器库

	void Browse(HDC &mdc, HDC &bufdc);//浏览武器库，调用current节点的Select函数显示
	void IFrame();//增帧
protected:
	WeaponNode * Discard(WeaponNode *);//丢弃选中的武器,由于是从武器库中删除因此可以直接删除武器节点
	WeaponNode *head;//头指针，方便构建链表，并作为搜索时的一个线索
	WeaponNode *current;//当前节点，记录玩家选择的武器，每次更换武器时会从当前节点开始搜索
	WeaponNode *tail;//尾指针，方便把武器存放到表尾
	WeaponNode *help;//辅助指针，在遍历时用于指向前驱或后继指针
	int maximum;//武器库容量，默认设置为最多容纳10件武器
	int length;//当前武器库已有的武器数
};

class WeaponBuilder :public TempItem {
	friend WeaponTempInventory;
public:
	WeaponBuilder();
	WeaponBuilder(int &, int &, int &);//构造函数，为怪物的坐标及武器稀有度
	virtual ~WeaponBuilder();
	int &Rarity();
	void MoveLeft(const int &distance);
	void MoveRight(const int &distance);
protected:
	int rarity;
	WeaponBuilder *next;
};

class WeaponTempInventory {
public:
	WeaponTempInventory();//构造函数
	virtual ~WeaponTempInventory();//析构函数
	void Store(WeaponBuilder *);//存入临时武器库
	friend void Store(WeaponTempInventory &, WeaponBuilder *);
	NormalWeapon * Discard(int &x);//丢弃临时武器
	void Clear();//清空
	void Select(HDC &, HDC &);
	bool Empty();//是否为空
	WeaponBuilder *Head();//头指针访问器
	void MoveLeft(const int &distance);
	void MoveRight(const int &distance);
protected:
	WeaponBuilder *head;//头指针
	WeaponBuilder *current;//当前指针,总是指向被丢弃的武器的前驱指针，方便查找
	int length;
};