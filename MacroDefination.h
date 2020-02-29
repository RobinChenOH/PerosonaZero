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

#define SCENE_WIDTH 1200//界面宽度
#define SCENE_HEIGHT 640//界面高度

//元素
#define NON_ELEMENT -1
#define FIRE 0//火焰元素
#define ARCANE 1//奥术元素
#define FROST 2//冰霜元素
#define ELECTRICITY 3//闪电元素
#define ELEMENT_ELE 0//元素增伤
#define ELEMENT_DOT 1//DOT增伤
#define ELEMENT_LOWER -1//元素的下界，此游戏内表示元素所代表数字的最小值，也代表无元素或其他伤害生成
#define ELEMENT_UPPER 3//元素的上界，此游戏内表示元素所代表数字的最大值

//选项
#define INTENSIFY_ATTACK 0//增伤
#define ENERGY_AFFINITY 1//减耗
#define FORTIFY_DEFENCE 2//减伤
#define ATTACK_UP 0//攻击力升级
#define HEALTH_UP 1//血量升级
#define MANA_UP 2//蓝量升级
#define ARMOR_UP 3//护甲升级
#define LEVELMAX_UP 4//经验槽升级

//增伤
#define ATK_ED 0//基础伤害增伤 ED:Enhanced Damage
#define PEN_ED 1//穿透增伤
#define CRI_STR_CHANCE 2//暴击几率
#define CRI_STR_DAMAGE 3//暴击伤害
#define ELE_ED 4//元素增伤,为某种特定元素增伤
#define DOT_ED 5//DOT增伤,为某种特定dot增伤
#define IND_ED 6//独立增伤,使某种类型的伤害或技能获得独立计算的增伤数值，如“使星袭造成额外的伤害”
#define VUL_ED 7//易伤增伤,使某种类型的技能会对受到其伤害的怪物上易伤debuff，使其受到更多伤害，如“每次攻击都会使该敌人受到的伤害提高1.0%”
#define STA_ED 8//状态增伤,使人物处于某种状态时会获得全局增伤buff，造成更多伤害，如“释放引导技能时，造成的伤害提高30%”
#define DIS_ED 9//歧视增伤,使人物对某种具有特定属性的敌人造成更多伤害，如“对僵尸造成的伤害提高15%”
#define IND_ED_OBJ_MAX 3//最大独立类增伤对象个数
#define VUL_ED_OBJ_MAX 8//最大易伤类增伤对象个数
#define STA_ED_OBJ_MAX 1//最大状态类增伤对象个数
#define DIS_ED_OBJ_MAX 2//最大歧视类增伤对象个数
//减耗
#define ATK_AF 0//所有减耗 AF:Affinity
#define ELE_AF 1//元素减耗,为某种特定元素减耗
#define ACT_AF 2//方式减耗,为某种类型的技能减耗
#define ELE_AF_OBJ_MAX 4//最大元素类减耗对象个数
#define ACT_AF_OBJ_MAX 4//最大方式类减耗对象个数
//减伤
#define ARM_PT 0//护甲减伤 PT:Protection
#define ELE_PT 1//元素抗性,为某种toe顶元素减伤
#define STA_PT 2//状态减伤,使人物处于某种状态时会获得全局减伤buff
#define ELE_PT_OBJ_MAX 4//最大元素抗性个数
#define STA_PT_OBJ_MAX 1//最大状态类减伤对象个数
//方式
#define MISSILE 0
#define RAY 1
#define STARSTRIKE 2
//状态
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
//容量相关宏定义
#define INVENTORY_MAXIMUM 20//武器库容量
#define MONSTER_MAXIMUM 30//怪物队列容量
#define MONSTER_UPDATE_MAXIMUM 15//最多刷新怪物数量
#define NW_TYPE_MAXIMUM 3//每种类型的武器最多有多少种
#define LW_TYPE_MAXIMUM 3
#define RW_TYPE_MAXIMUM 6
//怪物编号
#define ZOMBIE 0
#define MUMMY 1
#define GARGOYLES 2
#define CATTLE 3
#define BOSS1 4