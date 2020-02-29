#include "stdafx.h"

Dot::Dot() :dot_state(NON_ELEMENT), dot_start(0), dot_now(0), dot_span(0), dot_interval(0) {}

void Dot::SetElement(const int &e_type) {
	dot_state = e_type;
}

int & Dot::Get_State(){
	return dot_state;
}

bool Dot::DotValidate(){
	dot_now = GetTickCount();
	return (dot_now - dot_pre >= dot_interval);
}

bool Dot::DotEnd(){
	dot_now = GetTickCount();
	return (dot_now - dot_start >= dot_span);
}

void Dot::UpdateStart(){
	dot_start = GetTickCount();
}

void Dot::UpdatePre(){
	dot_pre = GetTickCount();
}

void Dot::UpdateSpan(DWORD span){
	dot_span = span;
}

void Dot::UpdateInterval(DWORD interval){
	dot_interval = interval;
	if (dot_state == FROST) dot_interval *= 0.3;
}

void Dot::Clear(){
	dot_state = NON_ELEMENT; dot_start = 0; dot_now = 0; dot_span = 0; dot_interval = 0;
}

CoolDown::CoolDown(DWORD interval, DWORD cd) :interval(interval), cd(cd), tLastTrigger(0), tNow(0), tPre(0) {}

bool CoolDown::On_CoolDown(){
	if (tNow == 0 && tLastTrigger == 0) {
		return false;
	}
	else {
		tNow = GetTickCount();
		return (tNow - tLastTrigger < cd);
	}
}

void CoolDown::Trigger(){
	tLastTrigger = GetTickCount();
	tPre = GetTickCount();
}

bool CoolDown::SysTrigger(){
	tNow = GetTickCount();
	if (tNow - tPre >= interval) {
		tPre = GetTickCount();
		return true;
	}
	else return false;
}
