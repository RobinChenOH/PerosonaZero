#pragma once
class CoolDown {
public:
	CoolDown(DWORD, DWORD);
	bool On_CoolDown();//������ȴ
	void Trigger();//����
	bool SysTrigger();//����ϵ��
protected:
	DWORD tLastTrigger;//���һ�δ�����ʱ��
	DWORD tPre;//��һ�δ�������Ч����ʱ��
	DWORD tNow;//���ڵ�ʱ��
	DWORD interval;//����ϵ��
	DWORD cd;//����cd
};

class Dot{//Dot��
public:
	Dot();
	void SetElement(const int &);//����dot����
	int &Get_State();//����dot����
	bool DotValidate();//dot�Ƿ�Ӧ��Ч��
	bool DotEnd();//dot�Ƿ������

	void UpdateStart();//����start
	void UpdatePre();//����pre
	void UpdateSpan(DWORD);
	void UpdateInterval(DWORD);

	void Clear();//���dot
private:
	int dot_state;//Dot��״̬
	DWORD dot_pre;//dot��һ����Ч��ʱ��
	DWORD dot_start;//dot��ʼʱ��
	DWORD dot_now;//dot���ڵ�ʱ��
	DWORD dot_span;//dot����ʱ��
	DWORD dot_interval;//dot��Ч��ʱ����
};

