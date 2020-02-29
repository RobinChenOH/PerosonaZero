#pragma once
class WeaponInventory;//�����࣬��ʹ��friend�ؼ���
class WeaponTempInventory;

class WeaponNode :public MyObject {//�����ڵ㣬ֻ������Ϊ����������Ļ���Ԫ��
	friend WeaponInventory;//����������Ϊ�����ڵ����Ԫ�࣬���ڽڵ������ͨ���󶨣�����Ϊһ�壬��˶Ա˴˿������޳�Ա��Ӱ�찲ȫ��
public:
	WeaponNode();
	WeaponNode(NormalWeapon *);//���캯����Ĭ������Ϊ��ͨ�����������ö�̬��ָ����߼��Ĵ�����������������
	virtual ~WeaponNode();//��������
	void Show(HDC &, HDC &);//��ʾ����
	WeaponNode *Pre();//ǰ��ָ�������
	WeaponNode *Next();//���ָ�������
protected:
	NormalWeapon *weapon;//����������
	WeaponNode *pre;//ǰ��ָ����
	WeaponNode *next;//���ָ����
	friend void Link(WeaponNode *, WeaponNode *);//������������������ָ��
};

class WeaponInventory :public MyObject {//�����⣬˫��������
public:
	WeaponInventory();//��ʼ��һ��������,Ĭ�ϻ���һ���������������ϻ����һ������
	virtual ~WeaponInventory();//��������
	void Store(NormalWeapon *);//���һ����������������
	void BrowseNext();//�����һ������
	void BrowsePre();//�����һ������
	void SelectWeapon();//ȷ�ϸ�����
	void DiscardWeapon();//ɾ��������
	NormalWeapon * Read();//��ȡ�����⵱ǰѡ�е������������������ݣ����ڸ�����������ֵ

	WeaponNode * Head();//��ȡ�������ͷָ��
	WeaponNode * Tail();//��ȡ�������βָ��
	bool Empty();//�������Ƿ�Ϊ��
	bool Full();//�������Ƿ�����
	void Delete();//ɾ��������

	void Browse(HDC &mdc, HDC &bufdc);//��������⣬����current�ڵ��Select������ʾ
	void IFrame();//��֡
protected:
	WeaponNode * Discard(WeaponNode *);//����ѡ�е�����,�����Ǵ���������ɾ����˿���ֱ��ɾ�������ڵ�
	WeaponNode *head;//ͷָ�룬���㹹����������Ϊ����ʱ��һ������
	WeaponNode *current;//��ǰ�ڵ㣬��¼���ѡ���������ÿ�θ�������ʱ��ӵ�ǰ�ڵ㿪ʼ����
	WeaponNode *tail;//βָ�룬�����������ŵ���β
	WeaponNode *help;//����ָ�룬�ڱ���ʱ����ָ��ǰ������ָ��
	int maximum;//������������Ĭ������Ϊ�������10������
	int length;//��ǰ���������е�������
};

class WeaponBuilder :public TempItem {
	friend WeaponTempInventory;
public:
	WeaponBuilder();
	WeaponBuilder(int &, int &, int &);//���캯����Ϊ��������꼰����ϡ�ж�
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
	WeaponTempInventory();//���캯��
	virtual ~WeaponTempInventory();//��������
	void Store(WeaponBuilder *);//������ʱ������
	friend void Store(WeaponTempInventory &, WeaponBuilder *);
	NormalWeapon * Discard(int &x);//������ʱ����
	void Clear();//���
	void Select(HDC &, HDC &);
	bool Empty();//�Ƿ�Ϊ��
	WeaponBuilder *Head();//ͷָ�������
	void MoveLeft(const int &distance);
	void MoveRight(const int &distance);
protected:
	WeaponBuilder *head;//ͷָ��
	WeaponBuilder *current;//��ǰָ��,����ָ�򱻶�����������ǰ��ָ�룬�������
	int length;
};