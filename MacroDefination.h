#pragma once
#define NORMAL 0
#define LEGENDARY 1
#define RELIC 2
#define NULLDAMAGE DamageStorage{-1,0}
#define NULLSPECIAL SpecialDamageStorage{-1,-1,0,0}
#define PICK_RANGE 100
#define LEFT 0
#define RIGHT 1
#define MAP_WIDTH 1500
#define MAP_HEIGHT 640

#define SCENE_WIDTH 1200//������
#define SCENE_HEIGHT 640//����߶�

//Ԫ��
#define NON_ELEMENT -1
#define FIRE 0//����Ԫ��
#define ARCANE 1//����Ԫ��
#define FROST 2//��˪Ԫ��
#define ELECTRICITY 3//����Ԫ��
#define ELEMENT_ELE 0//Ԫ������
#define ELEMENT_DOT 1//DOT����
#define ELEMENT_LOWER -1//Ԫ�ص��½磬����Ϸ�ڱ�ʾԪ�����������ֵ���Сֵ��Ҳ������Ԫ�ػ������˺�����
#define ELEMENT_UPPER 3//Ԫ�ص��Ͻ磬����Ϸ�ڱ�ʾԪ�����������ֵ����ֵ

//ѡ��
#define INTENSIFY_ATTACK 0//����
#define ENERGY_AFFINITY 1//����
#define FORTIFY_DEFENCE 2//����
#define ATTACK_UP 0//����������
#define HEALTH_UP 1//Ѫ������
#define MANA_UP 2//��������
#define ARMOR_UP 3//��������
#define LEVELMAX_UP 4//���������

//����
#define ATK_ED 0//�����˺����� ED:Enhanced Damage
#define PEN_ED 1//��͸����
#define CRI_STR_CHANCE 2//��������
#define CRI_STR_DAMAGE 3//�����˺�
#define ELE_ED 4//Ԫ������,Ϊĳ���ض�Ԫ������
#define DOT_ED 5//DOT����,Ϊĳ���ض�dot����
#define IND_ED 6//��������,ʹĳ�����͵��˺����ܻ�ö��������������ֵ���硰ʹ��Ϯ��ɶ�����˺���
#define VUL_ED 7//��������,ʹĳ�����͵ļ��ܻ���ܵ����˺��Ĺ���������debuff��ʹ���ܵ������˺����硰ÿ�ι�������ʹ�õ����ܵ����˺����1.0%��
#define STA_ED 8//״̬����,ʹ���ﴦ��ĳ��״̬ʱ����ȫ������buff����ɸ����˺����硰�ͷ���������ʱ����ɵ��˺����30%��
#define DIS_ED 9//��������,ʹ�����ĳ�־����ض����Եĵ�����ɸ����˺����硰�Խ�ʬ��ɵ��˺����15%��
#define IND_ED_OBJ_MAX 3//�����������˶������
#define VUL_ED_OBJ_MAX 8//������������˶������
#define STA_ED_OBJ_MAX 1//���״̬�����˶������
#define DIS_ED_OBJ_MAX 2//������������˶������
//����
#define ATK_AF 0//���м��� AF:Affinity
#define ELE_AF 1//Ԫ�ؼ���,Ϊĳ���ض�Ԫ�ؼ���
#define ACT_AF 2//��ʽ����,Ϊĳ�����͵ļ��ܼ���
#define ELE_AF_OBJ_MAX 4//���Ԫ������Ķ������
#define ACT_AF_OBJ_MAX 4//���ʽ����Ķ������
//����
#define ARM_PT 0//���׼��� PT:Protection
#define ELE_PT 1//Ԫ�ؿ���,Ϊĳ��toe��Ԫ�ؼ���
#define STA_PT 2//״̬����,ʹ���ﴦ��ĳ��״̬ʱ����ȫ�ּ���buff
#define ELE_PT_OBJ_MAX 4//���Ԫ�ؿ��Ը���
#define STA_PT_OBJ_MAX 1//���״̬����˶������
//��ʽ
#define MISSILE 0
#define RAY 1
#define STARSTRIKE 2
//״̬
#define MOVE 0
#define ATTACK 1
#define DEAD 2
#define COMBUST 3
#define ARCANEPOWER 4
#define FROSTBITE 5
#define PARALYZE 6
#define FAINT 7
#define MOTIONLESS 10
#define HURT 11
#define CURSE 12
#define THRUST 13
//������غ궨��
#define INVENTORY_MAXIMUM 20//����������
#define MONSTER_MAXIMUM 30//�����������
#define MONSTER_UPDATE_MAXIMUM 15//���ˢ�¹�������
#define NW_TYPE_MAXIMUM 3//ÿ�����͵���������ж�����
#define LW_TYPE_MAXIMUM 3
#define RW_TYPE_MAXIMUM 6
//������
#define ZOMBIE 0
#define MUMMY 1
#define GARGOYLES 2
#define CATTLE 3
#define BOSS1 4