#pragma once
class Boss :public Monster {//Boss¼Ì³ĞMonsterµÄÊôĞÔ
public:
	Boss(MyObjectBuilder *, BossDesign &, int, int);
};

class MachineGril :public Boss {
public:
	MachineGril(int, int);
};