#pragma once
class Scene :public MyObject {
public:
	Scene();
	~Scene();
	void MoveLeft(const int &);
	void MoveRight(const int &);
	void Switch();//�л�����
	void Reload();//��������ͼƬ
	void Clear();//ֹͣ
	const int &Serial();//�������
private:
	int serial;
};