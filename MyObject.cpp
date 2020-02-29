#include "stdafx.h"

MyObject::MyObject(MyObjectBuilder &mob, int x, int y): width(mob.width / mob.x_frame), height(mob.height / mob.y_frame),
frame(mob.x_frame), cframe(0), x(x), y(y), c_x(x + width / 2), c_y(y + height / 2), loop(true), show(true), fv(100), state(MOVE),
image((HBITMAP)LoadImageA(NULL, mob.path, IMAGE_BITMAP, mob.width, mob.height, LR_LOADFROMFILE)) {}

void MyObject::IFrame(){
	if (End()) {//若已是最后一帧，则根据是否循环重置帧
		if (loop) cframe = 0;
	}
	else {
		cframe++;
	}//否则若循环播放，则播放为下一帧
}

void MyObject::Select(HDC &mdc, HDC &bufdc){
	if (show) {//若显示，则对图片进行透明处理
		SelectObject(bufdc, image);
		BitBlt(mdc, x, y, width, height, bufdc, width * cframe, height, SRCAND);
		BitBlt(mdc, x, y, width, height, bufdc, width * cframe, 0, SRCPAINT);
	}
}

void MyObject::CSelect(HDC &mdc, HDC &bufdc){
	if (show) {//若显示，则直接复制
		SelectObject(bufdc, image);
		BitBlt(mdc, 0, 0, width, height, bufdc, 0, 0, SRCCOPY);
	}
}

void MyObject::PSelect(HDC &mdc, HDC &bufdc){
	if (show) {//若显示，则直接复制
		SelectObject(bufdc, image);
		BitBlt(mdc, 0, 0, width, height, bufdc, width*cframe , 0, SRCPAINT);
	}
}

void MyObject::TransSelect(HDC &mdc, HDC &bufdc, int r, int g, int b){
	if (show) {//若显示，则对该图片的RGB值进行透明处理
		SelectObject(bufdc, image);
		TransparentBlt(mdc, 600 - width / 2, 320 - height / 2, width, height, bufdc, 0, 0, width, height, RGB(r, g, b));
	}
}

void MyObject::SetXY(int new_x,int new_y){
	x = new_x; y = new_y;
}

void MyObject::SetShow(bool control){
	show = control;
}

void MyObject::SetLoop(bool n_loop){
	loop = n_loop;
}

void MyObject::SetAttribute(MyObjectBuilder & mob, int n_state, int n_loop, int n_show){
	image = (HBITMAP)LoadImageA(NULL, mob.path, IMAGE_BITMAP, mob.width, mob.height, LR_LOADFROMFILE);
	width = mob.width / mob.x_frame;
	height = mob.height / mob.y_frame;
	frame = mob.x_frame;
	cframe = 0;
	state = n_state;
	loop = n_loop;
	show = n_show;
}

void MyObject::ReSetCFrame(){
	cframe = 0;
}

const HBITMAP & MyObject::Image(){
	return image;
}

const int & MyObject::Width(){
	return width;
}

const int & MyObject::Height(){
	return height;
}

const int & MyObject::Cframe(){
	return cframe;
}

const int & MyObject::Frame(){
	return frame;
}

const int & MyObject::X(){
	return x;
}

const int & MyObject::Y(){
	return y;
}

const int & MyObject::C_X(){
	c_x = x + width / 2;
	return c_x;
}

const int & MyObject::C_Y(){
	c_y = y + height / 2;
	return c_y;
}

const int & MyObject::Fv(){
	return fv;
}

const int & MyObject::State(){
	return state;
}

const bool & MyObject::Show(){
	return show;
}

bool MyObject::End(){
	return (cframe == frame - 1);
}

TempItem::TempItem() : MyObject(nullobj, -1, -1) {}

TempItem::TempItem(int &x, int &y) : MyObject(nullobj, x, y) {
	if (Random(1, 0) == 1) SetAttribute(item_drop,  MOTIONLESS, false, true);
	else SetAttribute(quin, MOTIONLESS, false, true);
}

YAuxObject::YAuxObject(MyObjectBuilder &mob, int x, int y) : MyObject(mob, x, y), yframe(mob.y_frame), ycframe(0) {}

void YAuxObject::IFrame(){
	if (cframe == frame - 1) {
		if (ycframe == yframe - 1) {
			if (loop) { cframe = 0; ycframe = 0; }
		}
		else { ycframe++; cframe = 0; }
	}
	else {
		cframe++;
	}//否则若循环播放，则播放为下一帧
}

void YAuxObject::Select(HDC &mdc, HDC &bufdc){
	SelectObject(bufdc, image);
}

void YAuxObject::TransSelect(HDC &mdc, HDC &bufdc, int r, int g, int b){
	SelectObject(bufdc, image);
	TransparentBlt(mdc, x, y, width, height, bufdc, width*cframe, height*ycframe, width, height, RGB(r, g, b));
}

const int & YAuxObject::YCframe(){
	return ycframe;
}

const int & YAuxObject::YFrame(){
	return yframe;
}

bool YAuxObject::End(){
	return (cframe == frame - 1 && ycframe == yframe - 1);
}
