#pragma once
class Boss :public Monster {//Boss�̳�Monster������
public:
	Boss(MyObjectBuilder *, BossDesign &, int, int);
};

class MachineGril :public Boss {
public:
	MachineGril(int, int);
};