#pragma once
//��̬ȫ�ֱ���

static char	buf[50];			// ��������С
static int aux_time_srand = (unsigned int)time(NULL);

static CString normal_weapon_name[NW_TYPE_MAXIMUM] = { "ذ��","��Х","�̽�" };
static CString legendary_weapon_name[LW_TYPE_MAXIMUM] = { "������","��","����" };
static CString relic_weapon_name[RW_TYPE_MAXIMUM] = { "˪��","����","�췣","����ڵ�����","����","��Ϯ" };
static CString relic_weapon_special[RW_TYPE_MAXIMUM] = {
	"��˪�˺���Ե�����ɶ�����˺�",
	"���ߵķ������ļ���",
	"�Բ���������ɶ�����˺�",
	"̱����ɶ�����˺�",
	"ÿ�ι�������ʹ�����ܵ����˺����",
	"���ǵ��˺����"
};

//����һЩ�������������ڱ�д����
CString Get_ElementName(int element_type, int option);//��ĳ�����ͱ�����Ӧ��Ԫ�����ƴ������ַ���
CString Get_ActionName(int action_type);
CString Get_MonsterName(int object);
int Random(int upper, int lower);//��������֮������һ�����ֵ������������׺������ֵ�ȣ����ó���������

struct MonsterUpdateController {
	int x;//����
	int num;//��������
	int rarity;//���ɵȼ�
};
static MonsterUpdateController m_controller[10] = {
	{1,4,NORMAL},{50,2,NORMAL},{250,1,LEGENDARY},{362,5,NORMAL},{500,2,RELIC},{700,7,NORMAL},{850,6,LEGENDARY},{1000,4,RELIC},{1150,1,LEGENDARY},{1300,3,RELIC}
};

struct DamageBuilder {//�˺�������
	int type;//�Ƿ�����
	int upper;//�˺�����
	int lower;//�˺�����
};

struct DamageStorage {//�˺��洢��
	int type;//�˺�����
	int value;//�˺�ֵ
};

struct SpecialDamageBuilder {//��Ч������
	int effect_type;//��Ч����,0Ϊ�����࣬1Ϊ�����࣬2Ϊ�����࣬3Ϊ������
	int concrete_type;//��������
	int object;//���˶�Ӧ�Ķ�������Ӧ����ֵ
	int upper;//��Ч����
	int lower;//��Ч����
};
struct SpecialDamageStorage {//��Ч�洢��
	int effect_type;//��Ч����,0Ϊ�����࣬1Ϊ�����࣬2Ϊ�����࣬3Ϊ������
	int concrete_type;//��������
	int object;//���˶�Ӧ�Ķ�������Ӧ����ֵ
	int value;//��Ч����
};
struct BossDesign {//boss����������
	int experience;
	int velocity;
	int health;
	float atk;
	int armor;
	int object;
	int range;
	int element_type;
};

//����������Ԫ�ء�dot����Ч�˷���
static DamageBuilder rw_element[RW_TYPE_MAXIMUM] = { { 2, 20, 15 }, { 1, 25, 20 }, { 0, 10, 5 },{3,15,7},{0,5,3},{0,9,4} };
static DamageBuilder rw_dot[RW_TYPE_MAXIMUM] = { { 2, 10, 8 }, { 1, 50, 40 }, { 0, 30, 20 },{3,30,20},{1,9,6},{0,14,2} };
static SpecialDamageBuilder rw_special[RW_TYPE_MAXIMUM] = {
{ INTENSIFY_ATTACK, VUL_ED, FROST + 1, 30, 25 },//˪��Ϊ�������ˣ���˪�˺����ܵ������˺��ĵ�����ɶ�������
{ ENERGY_AFFINITY, ACT_AF, RAY, 50, 40 },//����Ϊ״̬���ˣ���������ʱ�������
{ INTENSIFY_ATTACK, DIS_ED, ZOMBIE, 30, 25 },//�췣Ϊ�������ˣ��Խ�ʬ��ɶ����˺�
{ INTENSIFY_ATTACK, DOT_ED, ELECTRICITY, 1100, 1000 },//����ڵ���������̱���˺�
{ INTENSIFY_ATTACK, VUL_ED, NON_ELEMENT + 1, 10, 5},//������������
{ INTENSIFY_ATTACK, IND_ED, STARSTRIKE, 100, 90} //��Ϯ����׹���˺�
};

static BossDesign boss1{ 2000,20,200,100,100,BOSS1,100,FIRE };