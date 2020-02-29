#pragma once
class MyObject{
public:
	MyObject(MyObjectBuilder &, int x, int y);
	//控制器
	virtual void IFrame();//增帧
	virtual void Select(HDC &, HDC &);//选择图片载入mdc贴图
	void CSelect(HDC &, HDC &);
	void PSelect(HDC &, HDC &);
	virtual void TransSelect(HDC &, HDC &, int, int, int);
	void SetXY(int,int);//修改坐标值
	void SetShow(bool);//show修改器
	void SetLoop(bool);//loop修改器
	void SetAttribute(MyObjectBuilder &mob, int n_state, int n_loop, int n_show);//修改属性值
	void ReSetCFrame();//重置当前帧
	//访问器
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
	virtual bool End();//是否播放完毕

protected:
	HBITMAP image;//图片，由派生类自行构造
	int width;//宽度
	int height;//高度
	int frame;//帧数
	int cframe;//当前帧
	int fv;//帧率
	int x;//贴图的左上角坐标
	int y;
	int c_x;//中心坐标
	int c_y;
	int state;//状态
	bool loop;//是否循环播放
	bool show;//是否显示图像
};

class YAuxObject: public MyObject{
public:
	YAuxObject(MyObjectBuilder &, int x, int y);
	//控制器
	virtual void IFrame();
	virtual void Select(HDC &, HDC &);
	virtual void TransSelect(HDC &, HDC &, int r, int g, int b);
	//访问器
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