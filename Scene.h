#pragma once
class Scene :public MyObject {
public:
	Scene();
	~Scene();
	void MoveLeft(const int &);
	void MoveRight(const int &);
	void Switch();//«–ªª≥°æ∞
	void Reload();//÷ÿ–¬‘ÿ»ÎÕº∆¨
	void Clear();//Õ£÷π
	const int &Serial();//∑µªÿ–Ú∫≈
private:
	int serial;
};