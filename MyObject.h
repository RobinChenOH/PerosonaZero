#pragma once
class MyObject{
public:
	MyObject(MyObjectBuilder &, int x, int y);
	//������
	virtual void IFrame();//��֡
	virtual void Select(HDC &, HDC &);//ѡ��ͼƬ����mdc��ͼ
	void CSelect(HDC &, HDC &);
	void PSelect(HDC &, HDC &);
	virtual void TransSelect(HDC &, HDC &, int, int, int);
	void SetXY(int,int);//�޸�����ֵ
	void SetShow(bool);//show�޸���
	void SetLoop(bool);//loop�޸���
	void SetAttribute(MyObjectBuilder &mob, int n_state, int n_loop, int n_show);//�޸�����ֵ
	void ReSetCFrame();//���õ�ǰ֡
	//������
	const HBITMAP &Image();
	const int &Width();
	const int &Height();
	const int &Cframe();
	const int &Frame();
	const int &X();
	const int &Y();
	const int &C_X();
	const int &C_Y();
	const int &Fv();
	const int &State();
	const bool &Show();
	virtual bool End();//�Ƿ񲥷����

protected:
	HBITMAP image;//ͼƬ�������������й���
	int width;//���
	int height;//�߶�
	int frame;//֡��
	int cframe;//��ǰ֡
	int fv;//֡��
	int x;//��ͼ�����Ͻ�����
	int y;
	int c_x;//��������
	int c_y;
	int state;//״̬
	bool loop;//�Ƿ�ѭ������
	bool show;//�Ƿ���ʾͼ��
};

class YAuxObject: public MyObject{
public:
	YAuxObject(MyObjectBuilder &, int x, int y);
	//������
	virtual void IFrame();
	virtual void Select(HDC &, HDC &);
	virtual void TransSelect(HDC &, HDC &, int r, int g, int b);
	//������
	const int &YCframe();
	const int &YFrame();
	virtual bool End();
protected:
	int yframe;
	int ycframe;
};

class TempItem :public MyObject {
public:
	TempItem();
	TempItem(int &, int &);
};