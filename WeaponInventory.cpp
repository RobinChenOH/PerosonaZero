#include "stdafx.h"
extern HFONT hFont_title;
extern HFONT hFont_text;

inline void Link(WeaponNode *precursor, WeaponNode *successor) {//����ָ����
	precursor->next = successor;
	successor->pre = precursor;
}

void Store(WeaponTempInventory &t_inv, WeaponBuilder *n_wb){
	t_inv.Store(n_wb);
}

WeaponNode::WeaponNode() :MyObject(nullobj, -1, -1), weapon(NULL), pre(NULL), next(NULL) {}

WeaponNode::WeaponNode(NormalWeapon *new_weapon) : MyObject(nullobj, 0, 0), weapon(new_weapon), pre(NULL), next(NULL) {
	if (weapon != nullptr) {
		switch (weapon->Get_Number()) {
		case 0:
			SetAttribute(dagger, MOTIONLESS, true, this->show); break;
		case 1:
			SetAttribute(tsunami, MOTIONLESS, true, this->show); break;
		case 2:
			SetAttribute(shortblade, MOTIONLESS, true, this->show); break;
		case 10:
			SetAttribute(empblade, MOTIONLESS, true, this->show); break;
		case 11:
			SetAttribute(uchigatana, MOTIONLESS, true, this->show); break;
		case 12:
			SetAttribute(longblade, MOTIONLESS, true, this->show); break;
		case 20:
			SetAttribute(frostheart, MOTIONLESS, true, this->show); break;
		case 21:
			SetAttribute(moonblade, MOTIONLESS, true, this->show); break;
		case 22:
			SetAttribute(condemn, MOTIONLESS, true, this->show); break;
		case 23:
			SetAttribute(electroblade, MOTIONLESS, true, this->show); break;
		case 24:
			SetAttribute(fireblade, MOTIONLESS, true, this->show); break;
		case 25:
			SetAttribute(starblade, MOTIONLESS, true, this->show); break;
		default:break;
		}
		x = MAP_WIDTH/2 - width / 2; y = MAP_HEIGHT/2 - height / 2;
	}
}

WeaponNode::~WeaponNode(){//����������
	next = NULL;
	delete(next);
	pre = NULL;
	delete(pre);
	delete(weapon);
}

void WeaponNode::Show(HDC &mdc, HDC &bufdc){
	if (show) {
		Select(mdc, bufdc);

		SetBkColor(mdc, TRANSPARENT);
		//�����������
		CString text = weapon->Get_Name();
		CRect rc(70, 90, 300, 200);
		SetTextColor(mdc, RGB(50, 34, 117));
		SelectObject(mdc, hFont_title);
		DrawText(mdc, text, text.GetLength(), &rc, DT_LEFT);

		//���ȫ������ֵ
		SetTextColor(mdc, RGB(110, 195, 201));
		SelectObject(mdc, hFont_text);
		CString affix;
		text.Format(_T("��ɵ��˺����%d%%\n\n"),weapon->Get_atkED().value);

		//�����������ֵ
		if (weapon->Get_CriticalChance().type != NON_ELEMENT) {
			affix.Format(_T("�����������%d%%\n\n"), weapon->Get_CriticalChance().value);
			text += affix;
		}
		if (weapon->Get_CriticalDamage().type != NON_ELEMENT) {
			affix.Format(_T("�����˺����%d%%\n\n"), weapon->Get_CriticalDamage().value);
			text += affix;
		}

		//���Ԫ������ֵ
		if (weapon->Get_PenetrateED().type != NON_ELEMENT) {
			affix.Format(_T("��͸�˺����%d%%\n\n"), weapon->Get_PenetrateED().value);
			text += affix;
		}
		if (weapon->Get_ElementED().type != NON_ELEMENT) {
			text += Get_ElementName(weapon->Get_ElementED().type, ELEMENT_ELE);
			affix.Format(_T("�˺����%d%%\n\n"), weapon->Get_ElementED().value);
			text += affix;
		}
		if (weapon->Get_DotED().type != NON_ELEMENT) {
			text += Get_ElementName(weapon->Get_DotED().type, ELEMENT_DOT);
			affix.Format(_T("�˺����%d%%\n\n"), weapon->Get_DotED().value);
			text += affix;
		}
		SetRect(&rc, 70, 170, 300, 500);
		DrawText(mdc, text, text.GetLength(), &rc, DT_LEFT);

		//�����Ч��׺
		if (weapon->Get_Rarity() == RELIC) {
			SetTextColor(mdc, RGB(115, 136, 193));
			text = weapon->Get_SpecialEffects();
			SetRect(&rc, 70, 500, 600, 1000);
			DrawText(mdc, text, text.GetLength(), &rc, DT_LEFT);
		}
	}
}

WeaponNode * WeaponNode::Pre(){
	return pre;
}

WeaponNode * WeaponNode::Next(){
	return next;
}

WeaponInventory::WeaponInventory() :MyObject(inventory_bg, 0, 0), maximum(INVENTORY_MAXIMUM), length(1) {
	//Ĭ�ϳ�ʼ��ʱ����һ����ͨ�������������������ٻᴢ��һ������
	NormalWeapon *basic=new NormalWeapon(NORMAL, 0, 2, 5, { true,2,1 });//������ͨ����
	//NormalWeapon *basic = new RelicWeapon(21, 2, 5, { -1,0,0 }, { -1,0,0 }, rw_element, rw_dot, rw_special);
	WeaponNode *temp = new WeaponNode(basic);//���������ڵ�
	help = current = tail = temp;//��ǰָ���βָ���ָ��������ڵ�
	head = new WeaponNode;//��ʼ��ͷָ��
	Link(head, tail);//����ͷָ���βָ��
}

WeaponInventory::~WeaponInventory(){
	Delete();
}

void WeaponInventory::Store(NormalWeapon *new_weapon){//��������
	if (Full()) {
		MessageBox(NULL, L"����������!", _T("ERROR"), NULL);
	}
	else {
		WeaponNode *temp = new WeaponNode(new_weapon);//������ʱָ�룬������Ϊ������
		//�������ٻ���һ�����������ֻ��Ҫ��βָ�������������
		Link(tail, temp);//����βָ��͵�ǰָ��
		tail = temp;//��ǰָ����Ϊβָ��
		length++;//����������1
	}
}

WeaponNode * WeaponInventory::Discard(WeaponNode *selected_weapon){//������ǰѡ�е�����
	if (Empty()) {
		MessageBox(NULL, L"�������ѿ�!", _T("ERROR"), NULL);
		return NULL;
	}
	else {
		if (selected_weapon == current) {//������ݵĽڵ��ǵ�ǰ�ڵ㣬��Ҫ������Ӧָ���ֹ����
			if (current == tail)//�����ǰ�ڵ���β�ڵ�
				current = current->pre;//����ָ��ǰ�����
			else
				current = current->next;//����ָ���̽ڵ�
		}
		WeaponNode *temp = new WeaponNode;
		if (selected_weapon == tail) {//���������ڵ㴦��βλ�ã���ֱ����������βָ�뼴��
			temp = selected_weapon->pre;//��¼��ǰ�ڵ��ǰ���ڵ�(�����޺�̽ڵ�ֻ�ܴ���ǰ�����)
			temp->next = NULL;//����ǰ�ڵ�����ǰ���ڵ�Ͽ�
			delete(selected_weapon);//�ͷŸ�����ռ�õ��ڴ�
			tail = temp;//��������β�ڵ�
		}
		else {//��δ����βλ�ã�������ǰ��ָ�벢���ٵ�ǰָ�룬��ǰָ������Ϊ��ǰ��ָ��
			temp = selected_weapon->next;//��¼��ǰ�ڵ�ĺ�̽ڵ�
			Link(selected_weapon->pre, selected_weapon->next);
			delete(selected_weapon);//�ͷŸ�����ռ�õ��ڴ�
		}
		length--;//��������1
		return temp;
	}
}

void WeaponInventory::Browse(HDC & mdc, HDC & bufdc){
	SelectObject(bufdc, image);
	BitBlt(mdc, x, y, width, height, bufdc, 0, 0, SRCCOPY);
	help->SetShow(true);
	help->Show(mdc, bufdc);
}

void WeaponInventory::IFrame(){
	help->IFrame();
}

void WeaponInventory::BrowseNext(){
	if (help != tail) {//��־Ϊ�棬δ��β��
		help = help->next;
	}
	else {
		MessageBox(NULL, L"�������һ������!", _T("ERROR"), NULL);
	}
}

void WeaponInventory::BrowsePre(){
	if (help->pre != head) {//��־Ϊ�棬δ��ͷ��
		help = help->pre;
	}
	else {
		MessageBox(NULL, L"���ǵ�һ������!", _T("ERROR"), NULL);
	}
}

void WeaponInventory::SelectWeapon(){
	current = help;//��ѡ�еĽڵ����currentָ��
}

void WeaponInventory::DiscardWeapon(){
	WeaponNode *temp = Discard(help);
	if (temp == NULL) {

	}
	help = current;
}

NormalWeapon * WeaponInventory::Read(){
	return current->weapon;
}

WeaponNode * WeaponInventory::Head(){
	return head;
}

WeaponNode * WeaponInventory::Tail(){
	return tail;
}

bool WeaponInventory::Empty(){//�������Ƿ�Ϊ�գ��������ٱ���һ����������˵�һ������ʱ����Ϊ�գ������ٶ�����
	if (length == 1)
		return true;
	else
		return false;
}

bool WeaponInventory::Full(){//�������������ﵽ���ֵ����������������������ʰȡ��
	if (length == maximum)
		return true;
	else
		return false;
}

void WeaponInventory::Delete(){
	for (WeaponNode *temp = head->next; temp != NULL; temp = temp->next)//���������
		delete(temp->pre);//ɾ��ÿ���ڵ��ǰ���ڵ�
	head = NULL;//�ÿ�ͷָ��
}

WeaponBuilder::WeaponBuilder() :rarity(-1), next(NULL) {};

WeaponBuilder::WeaponBuilder(int &x, int &y, int &r) :TempItem(x, y), rarity(r), next(NULL) {}

WeaponBuilder::~WeaponBuilder(){}

int & WeaponBuilder::Rarity() { return rarity; }

void WeaponBuilder::MoveLeft(const int & distance){
	x -= distance;
}

void WeaponBuilder::MoveRight(const int & distance){
	x += distance;
}

WeaponTempInventory::WeaponTempInventory():length(0){//��ʼ������Ϊ0
	head = new WeaponBuilder;//��ʼ��ͷָ��
}

WeaponTempInventory::~WeaponTempInventory(){}

void WeaponTempInventory::Store(WeaponBuilder *n_wb){//���һ����������������ʱ������
	if (Empty())
		head->next = n_wb;//��������Ϊ�գ���ֱ�����
	else//�������
		for (WeaponBuilder *temp = head; temp != NULL; temp = temp->next)//��ͷָ�뵽βָ����������ҵ����������λ�ã���x����˳�����У�����֮����ң�
			if (temp->X() <= n_wb->X()) {
				if (temp->next == nullptr) {//����βָ�룬��ֱ�ӽ���
					temp->next = n_wb; break;
				}
				else if (temp->next->X() >= n_wb->X()) {//�����м���룬�����
					n_wb->next = temp->next;//����ڵ���ָ��
					temp->next = n_wb;//����ڵ�ǰ��ָ��
					break;
				}
			}
	length++;//�����ⳤ������
}

NormalWeapon * WeaponTempInventory::Discard(int & x){
	for (WeaponBuilder *temp = head->next, *pre = head; temp != NULL; pre = temp, temp = temp->next) {//�����������Ҷ�Ӧ����
		if (abs(x - temp->C_X()) <= PICK_RANGE) {//��ʰȡλ������һ������֮��ľ���ֵ��ʰȡ��Χ֮�ڣ���ʰȡ�ɹ������ع���õ�����
			pre->next = temp->next;//����ǰ��ָ������ָ��
			return CreateWeapon(temp);//��������
		}
	}
	return nullptr;//���򷵻ؿ�ָ��
}

void WeaponTempInventory::Clear(){
	head->next = NULL;
}

void WeaponTempInventory::Select(HDC &mdc, HDC &bufdc){
	for (WeaponBuilder *temp = head->next; temp != NULL; temp = temp->next) {//���ѡȡÿ������ͼ
		temp->Select(mdc, bufdc);
	}
}

bool WeaponTempInventory::Empty() { return (length == 0); }//�����Ƿ�δ��

WeaponBuilder * WeaponTempInventory::Head(){
	return head;
}

void WeaponTempInventory::MoveLeft(const int & distance){
	for (WeaponBuilder *temp = head->next; temp != NULL; temp = temp->next) {
		temp->MoveLeft(distance);
	}
}

void WeaponTempInventory::MoveRight(const int & distance){
	for (WeaponBuilder *temp = head->next; temp != NULL; temp = temp->next) {
		temp->MoveRight(distance);
	}
}
