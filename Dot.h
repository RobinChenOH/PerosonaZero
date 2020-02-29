#pragma once
class CoolDown {
public:
	CoolDown(DWORD, DWORD);
	bool On_CoolDown();//尚在冷却
	void Trigger();//触发
	bool SysTrigger();//触发系数
protected:
	DWORD tLastTrigger;//最近一次触发的时间
	DWORD tPre;//上一次触发技能效果的时间
	DWORD tNow;//现在的时间
	DWORD interval;//触发系数
	DWORD cd;//技能cd
};

class Dot{//Dot类
public:
	Dot();
	void SetElement(const int &);//设置dot类型
	int &Get_State();//返回dot类型
	bool DotValidate();//dot是否应生效了
	bool DotEnd();//dot是否结束了

	void UpdateStart();//更新start
	void UpdatePre();//更新pre
	void UpdateSpan(DWORD);
	void UpdateInterval(DWORD);

	void Clear();//清除dot
private:
	int dot_state;//Dot的状态
	DWORD dot_pre;//dot上一次生效的时间
	DWORD dot_start;//dot开始时间
	DWORD dot_now;//dot现在的时间
	DWORD dot_span;//dot持续时间
	DWORD dot_interval;//dot生效的时间间隔
};

