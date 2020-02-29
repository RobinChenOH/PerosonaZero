#include "stdafx.h"
extern HFONT hFont_title;
extern HFONT hFont_text;

inline void Link(WeaponNode *precursor, WeaponNode *successor) {//更改指针域
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

WeaponNode::~WeaponNode(){//销毁武器域
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
		//输出武器名称
		CString text = weapon->Get_Name();
		CRect rc(70, 90, 300, 200);
		SetTextColor(mdc, RGB(50, 34, 117));
		SelectObject(mdc, hFont_title);
		DrawText(mdc, text, text.GetLength(), &rc, DT_LEFT);

		//输出全局增伤值
		SetTextColor(mdc, RGB(110, 195, 201));
		SelectObject(mdc, hFont_text);
		CString affix;
		text.Format(_T("造成的伤害提高%d%%\n\n"),weapon->Get_atkED().value);

		//输出暴击增伤值
		if (weapon->Get_CriticalChance().type != NON_ELEMENT) {
			affix.Format(_T("暴击几率提高%d%%\n\n"), weapon->Get_CriticalChance().value);
			text += affix;
		}
		if (weapon->Get_CriticalDamage().type != NON_ELEMENT) {
			affix.Format(_T("暴击伤害提高%d%%\n\n"), weapon->Get_CriticalDamage().value);
			text += affix;
		}

		//输出元素增伤值
		if (weapon->Get_PenetrateED().type != NON_ELEMENT) {
			affix.Format(_T("穿透伤害提高%d%%\n\n"), weapon->Get_PenetrateED().value);
			text += affix;
		}
		if (weapon->Get_ElementED().type != NON_ELEMENT) {
			text += Get_ElementName(weapon->Get_ElementED().type, ELEMENT_ELE);
			affix.Format(_T("伤害提高%d%%\n\n"), weapon->Get_ElementED().value);
			text += affix;
		}
		if (weapon->Get_DotED().type != NON_ELEMENT) {
			text += Get_ElementName(weapon->Get_DotED().type, ELEMENT_DOT);
			affix.Format(_T("伤害提高%d%%\n\n"), weapon->Get_DotED().value);
			text += affix;
		}
		SetRect(&rc, 70, 170, 300, 500);
		DrawText(mdc, text, text.GetLength(), &rc, DT_LEFT);

		//输出特效词缀
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
	//默认初始化时会有一件普通武器，并且武器库最少会储存一件武器
	NormalWeapon *basic=new NormalWeapon(NORMAL, 0, 2, 5, { true,2,1 });//创建普通武器
	//NormalWeapon *basic = new RelicWeapon(21, 2, 5, { -1,0,0 }, { -1,0,0 }, rw_element, rw_dot, rw_special);
	WeaponNode *temp = new WeaponNode(basic);//建立武器节点
	help = current = tail = temp;//当前指针和尾指针均指向该武器节点
	head = new WeaponNode;//初始化头指针
	Link(head, tail);//链接头指针和尾指针
}

WeaponInventory::~WeaponInventory(){
	Delete();
}

void WeaponInventory::Store(NormalWeapon *new_weapon){//贮藏武器
	if (Full()) {
		MessageBox(NULL, L"武器库已满!", _T("ERROR"), NULL);
	}
	else {
		WeaponNode *temp = new WeaponNode(new_weapon);//创建临时指针，数据域为该武器
		//由于至少会有一件武器，因此只需要向尾指针添加武器即可
		Link(tail, temp);//链接尾指针和当前指针
		tail = temp;//当前指针作为尾指针
		length++;//武器数增加1
	}
}

WeaponNode * WeaponInventory::Discard(WeaponNode *selected_weapon){//丢弃当前选中的武器
	if (Empty()) {
		MessageBox(NULL, L"武器库已空!", _T("ERROR"), NULL);
		return NULL;
	}
	else {
		if (selected_weapon == current) {//如果操纵的节点是当前节点，需要更改相应指针防止出错
			if (current == tail)//如果当前节点是尾节点
				current = current->pre;//将其指向前驱结点
			else
				current = current->next;//否则指向后继节点
		}
		WeaponNode *temp = new WeaponNode;
		if (selected_weapon == tail) {//若该武器节点处于尾位置，则直接重新设置尾指针即可
			temp = selected_weapon->pre;//记录当前节点的前驱节点(由于无后继节点只能储存前驱结点)
			temp->next = NULL;//将当前节点与其前驱节点断开
			delete(selected_weapon);//释放该武器占用的内存
			tail = temp;//重新设置尾节点
		}
		else {//若未处于尾位置，则链接前后指针并销毁当前指针，当前指针设置为其前驱指针
			temp = selected_weapon->next;//记录当前节点的后继节点
			Link(selected_weapon->pre, selected_weapon->next);
			delete(selected_weapon);//释放该武器占用的内存
		}
		length--;//武器数减1
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
	if (help != tail) {//标志为真，未到尾部
		help = help->next;
	}
	else {
		MessageBox(NULL, L"已是最后一件武器!", _T("ERROR"), NULL);
	}
}

void WeaponInventory::BrowsePre(){
	if (help->pre != head) {//标志为真，未到头部
		help = help->pre;
	}
	else {
		MessageBox(NULL, L"已是第一件武器!", _T("ERROR"), NULL);
	}
}

void WeaponInventory::SelectWeapon(){
	current = help;//将选中的节点存入current指针
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

bool WeaponInventory::Empty(){//武器库是否为空，由于至少保存一件武器，因此到一件武器时就视为空（不可再丢弃）
	if (length == 1)
		return true;
	else
		return false;
}

bool WeaponInventory::Full(){//若武器库数量达到最大值，则武器库已满（不可再拾取）
	if (length == maximum)
		return true;
	else
		return false;
}

void WeaponInventory::Delete(){
	for (WeaponNode *temp = head->next; temp != NULL; temp = temp->next)//清空武器库
		delete(temp->pre);//删除每个节点的前驱节点
	head = NULL;//置空头指针
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

WeaponTempInventory::WeaponTempInventory():length(0){//初始化长度为0
	head = new WeaponBuilder;//初始化头指针
}

WeaponTempInventory::~WeaponTempInventory(){}

void WeaponTempInventory::Store(WeaponBuilder *n_wb){//存放一个武器构造器到临时武器库
	if (Empty())
		head->next = n_wb;//若武器库为空，则直接添加
	else//否则查找
		for (WeaponBuilder *temp = head; temp != NULL; temp = temp->next)//从头指针到尾指针遍历，查找到存放武器的位置（按x递增顺序排列，方便之后查找）
			if (temp->X() <= n_wb->X()) {
				if (temp->next == nullptr) {//若是尾指针，则直接接入
					temp->next = n_wb; break;
				}
				else if (temp->next->X() >= n_wb->X()) {//若需中间插入，则插入
					n_wb->next = temp->next;//接入节点后继指针
					temp->next = n_wb;//接入节点前驱指针
					break;
				}
			}
	length++;//武器库长度增加
}

NormalWeapon * WeaponTempInventory::Discard(int & x){
	for (WeaponBuilder *temp = head->next, *pre = head; temp != NULL; pre = temp, temp = temp->next) {//遍历链表，查找对应武器
		if (abs(x - temp->C_X()) <= PICK_RANGE) {//若拾取位置与下一件武器之差的绝对值在拾取范围之内，则拾取成功，返回构造好的武器
			pre->next = temp->next;//链接前驱指针与后继指针
			return CreateWeapon(temp);//构造武器
		}
	}
	return nullptr;//否则返回空指针
}

void WeaponTempInventory::Clear(){
	head->next = NULL;
}

void WeaponTempInventory::Select(HDC &mdc, HDC &bufdc){
	for (WeaponBuilder *temp = head->next; temp != NULL; temp = temp->next) {//逐个选取每个武器图
		temp->Select(mdc, bufdc);
	}
}

bool WeaponTempInventory::Empty() { return (length == 0); }//返回是否未空

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
