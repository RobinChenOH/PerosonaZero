// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // 从 Windows 头中排除极少使用的资料
// Windows 头文件: 
#include <Windows.h>
#include "mmsystem.h"//导入声音头文件
#pragma comment(lib,"winmm.lib")//导入声音头文件库
// C 运行时头文件
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <ctime>
#include <cstdlib>
#include <string>
#include <iostream>
#include "resource.h"
#include "atlimage.h"
#include "MacroDefination.h"
#include "Path.h"
#include "Auxiliary.h"
#include "MyObject.h"
#include "HealthBar.h"
#include "Dot.h"
#include "Damage.h"
#include "Item.h"
#include "WeaponInventory.h"
#include "Skill.h"
#include "Monster.h"
#include "Boss.h"
#include "MyQueue.h"
#include "Scene.h"
#include "Player.h"

// TODO: 在此处引用程序需要的其他头文件
