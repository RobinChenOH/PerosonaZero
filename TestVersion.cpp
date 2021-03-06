//TestVersion.cpp: 定义应用程序的入口点。
//

#include "stdafx.h"
#include "TestVersion.h"
#define MAX_LOADSTRING 100

// 全局变量: 
HFONT hFont_title = CreateFont(40, 0, 0, 0, FW_HEAVY, 0, 0, 0, GB2312_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, _T("方正正中黑简体"));
HFONT hFont_text = CreateFont(25, 0, 0, 0, FW_NORMAL, 0, 0, 0, GB2312_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, _T("方正正中黑简体"));
HFONT hFont_message_title = CreateFont(30, 0, 0, 0, FW_HEAVY, 0, 0, 0, GB2312_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, _T("微软雅黑"));
HFONT hFont_message_text = CreateFont(20, 0, 0, 0, FW_NORMAL, 0, 0, 0, GB2312_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, _T("微软雅黑"));

HWND	hWnd;
HINSTANCE hInst;                                // 当前实例
HDC hdc, mdc, bufdc;							// HDC实例
Player player;									// 人物角色
Scene background;								// 界面背景
MonsterQueue monster_queue;						// 怪物队列
SkillQueue skill_queue;							// 技能队列
CoolDown star_cd(0, 4000);						// 流星cd
ObjectQueue object_queue;						// 击杀图标队列
ObjectQueue critical_queue;						// 暴击图标队列
WeaponTempInventory temp_inventory;				// 临时武器栏
HealthBar healthbar;							// 血条
HealthBar manabar;								// 蓝条
MyObject levelupbg(scene0, 0, 0);				// 升级时的背景贴图
MyObject levelupimg(levelupbmp, 200, 300);		// level up图标
MyObject start_scene(start_bg, 0, 0);			// 开始界面
MyObject gameover_scene(gameover_bg, 0, 0);		// 死亡界面
MyObject gameinfo_scene(gameinfo_bg, 0, 0);		// 游戏说明
ChannellingSkill *ray = new ChannellingSkill(ELECTRICITY, player.C_X() + 120, player.C_Y(), 5);//射线
MachineGril *gril = new MachineGril(1300, 150);
WCHAR szTitle[MAX_LOADSTRING];                  // 标题栏文本
WCHAR szWindowClass[MAX_LOADSTRING];            // 主窗口类名

bool gamestart = true;							// 开始界面
bool gameinfo = false;							// 游戏说明
bool gameover = false;							// 游戏结束
bool gamepause = false;							// 游戏暂停
bool gamestop = false;							// 控制游戏最终是否播放的标志位
bool levelup = false;							// 是否升级
bool select_ready = false;						// 是否准备接收下一个按键
bool browse_ready = false;						// 是否准备浏览武器库
bool boss_update = false;						// 是否已刷新boss
int selected_element = FIRE;					// 选中元素
int destX = 500, destY = 350;					// 当前鼠标位置
int m_controller_i = 0;							// 控制怪物生成
int basic_level = 0;							// 基础等级

// 此代码模块中包含的函数的前向声明: 
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
//播放类
void				MyPaint();//主界面绘画函数
void				BrowsePaint();//武器栏绘画函数
void				CharacterIFrame();//角色增帧
void				InventoryIFrame();//武器库增帧
//处理类
void				Ray_Attack();//射线处理函数
//切换类
void				SwitchMusic();//切换音乐
void				SwitchMap();//切换地图
void				ReStart();//重新开始
//刷新类
void				UpdateScene();//刷新界面
void				UpdateBattle();//刷新战斗
void				UpdateLevel();//刷新等级
void				CreateSkill(int, int);//创建技能
//移动类
void				PlayerMove(int direction);//人物移动函数
void				MapMove(int direction);//地图移动函数
void				Button_A();//A响应函数，左移
void				Button_D();//D响应函数，右移
void				Button_R();//R响应函数，投掷物、雷属性
void				Button_I();//I响应函数，浏览和退出武器库
void				Button_E();//E响应函数，确认、拾取、冰属性
void				Button_Q();//Q响应函数，取消、火属性
void				Button_W();//W响应函数，奥属性
void				Button_S();//S响应函数，普攻
void				Button_N();//N响应函数，暂停
void				Button_SPACE();//C响应函数，选择元素
void				Button_Ctrl();
void				Button_A_InBrowse();//浏览状态下的A响应函数，查看上一件武器，修改临时指针
void				Button_D_InBrowse();//浏览状态下的D响应函数，查看下一件武器，修改临时指针

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 在此放置代码。

    // 初始化全局字符串
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_TESTVERSION, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 执行应用程序初始化: 
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_TESTVERSION));

    MSG msg;
	GetMessage(&msg, NULL, 0, 0);
	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			if (gamestart) {
				SelectObject(bufdc, start_scene.Image());
				BitBlt(mdc, 0, 0, MAP_WIDTH, MAP_HEIGHT, bufdc, 0, 0, SRCCOPY);
				BitBlt(hdc, 0, 0, MAP_WIDTH, MAP_HEIGHT, mdc, 0, 0, SRCCOPY);
			}
			else if (gameinfo) {
				SelectObject(bufdc, gameinfo_scene.Image());
				BitBlt(mdc, 0, 0, MAP_WIDTH, MAP_HEIGHT, bufdc, 0, 0, SRCCOPY);
				BitBlt(hdc, 0, 0, MAP_WIDTH, MAP_HEIGHT, mdc, 0, 0, SRCCOPY);
			}
			else {
				if (!gameover) {//若游戏未结束
					if (!gamepause) {//若游戏未暂停
						UpdateScene();//刷新界面
						UpdateBattle();//刷新怪物
						UpdateLevel();//刷新等级
					}
				}
				else {//游戏结束
					gameover_scene.Select(mdc, bufdc);
					BitBlt(hdc, 0, 0, MAP_WIDTH, MAP_HEIGHT, mdc, 0, 0, SRCPAINT);
					Sleep(2000);
					ReStart();
				}
				gamestop = gameover || gamepause;
			}
		}
	}

    return (int) msg.wParam;
}



//
//  函数: MyRegisterClass()
//
//  目的: 注册窗口类。
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_TESTVERSION));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_TESTVERSION);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   函数: InitInstance(HINSTANCE, int)
//
//   目的: 保存实例句柄并创建主窗口
//
//   注释: 
//
//        在此函数中，我们在全局变量中保存实例句柄并
//        创建和显示主程序窗口。
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	HBITMAP bmp;
   hInst = hInstance; // 将实例句柄存储在全局变量中

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }
   MoveWindow(hWnd, 10, 10, MAP_WIDTH, MAP_HEIGHT, true);
   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   hdc = GetDC(hWnd);
   mdc = CreateCompatibleDC(hdc);
   bufdc = CreateCompatibleDC(hdc);

   manabar.SetXY(healthbar.X(), healthbar.Y() + 50);
   levelupbg.SetLoop(false);

   mciSendStringA("open Music\\Glowing_Cubes_In_Tne_Darkness.wav type avivideo alias start_music", buf, strlen(buf), NULL);
   mciSendStringA("open Music\\The_Clockwork.wav type avivideo alias level1", buf, strlen(buf), NULL);
   mciSendStringA("open Music\\Evening_Song.wav type avivideo alias level2", buf, strlen(buf), NULL);
   mciSendStringA("open Music\\In_The_Rain.wav type avivideo alias level3", buf, strlen(buf), NULL);

   mciSendStringA("play start_music repeat", buf, strlen(buf), NULL);

   bmp = CreateCompatibleBitmap(hdc, MAP_WIDTH, MAP_HEIGHT);
   SelectObject(mdc, bmp);

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

void MyPaint() {
	//背景为最底层，直接贴即可
	SelectObject(bufdc, background.Image());
	BitBlt(mdc, 0, 0, MAP_WIDTH, MAP_HEIGHT, bufdc, background.X(), 0, SRCCOPY);
	//其他对象调用自己的Select函数将图像载入上下文
	player.Select(mdc, bufdc);
	monster_queue.Select(mdc, bufdc);
	ray->Select(mdc, bufdc);
	skill_queue.Select(mdc, bufdc);
	temp_inventory.Select(mdc, bufdc);
	healthbar.Select(mdc, bufdc, player.Health_rate());
	manabar.Select(mdc, bufdc, player.Mana_rate());
	object_queue.TransSelect(mdc, bufdc, 47, 11, 24, true);
	critical_queue.Select(mdc, bufdc, true);

	skill_queue.Play(player, monster_queue);//播放技能
	Ray_Attack();
	BitBlt(hdc, 0, 0, MAP_WIDTH, MAP_HEIGHT, mdc, 0, 0, SRCCOPY);//贴图
	Sleep(player.Fv());//根据帧数睡眠
}

void CharacterIFrame(){
	player.IFrame();
	monster_queue.IFrame();
	skill_queue.IFrame();
	ray->IFrame();
	object_queue.IFrame();
	critical_queue.IFrame();
	if(levelup) levelupbg.IFrame();
}

void InventoryIFrame(){
	player.Inventory()->IFrame();
}

void Ray_Attack(){
	if (ray->Show() == true) {
		if (ray->Skill_CD().SysTrigger())
			MQ_UnderAttack(player, ray, monster_queue);
	}
}

void BrowsePaint(){
	player.BrowseInventory(mdc, bufdc);
	BitBlt(hdc, 0, 0, MAP_WIDTH, MAP_HEIGHT, mdc, 0, 0, SRCCOPY);//贴图
	Sleep(100);
}

void SwitchMusic(){
	switch (background.Serial()) {
	case 0:
		mciSendStringA("stop start_music", buf, strlen(buf), NULL);
		mciSendStringA("play level1 repeat", buf, strlen(buf), NULL); break;
	case 1:
		mciSendStringA("stop level1 ", buf, strlen(buf), NULL);
		mciSendStringA("play level2 repeat", buf, strlen(buf), NULL); break;
	case 2:
		mciSendStringA("stop level2 ", buf, strlen(buf), NULL);
		mciSendStringA("play level3 repeat", buf, strlen(buf), NULL); break;
	default:break;
	}
}

void SwitchMap(){
	monster_queue.Clear();
	temp_inventory.Clear();
	m_controller_i = 0;
	background.Switch();
	SwitchMusic();
	player.SetXY(0, 150);
	basic_level += 50;
}

void ReStart(){
	player.Wait();
	player.Revive();
	background.SetXY(0, 0);
	background.Clear();
	monster_queue.Clear();
	skill_queue.Clear();
	object_queue.Clear();
	critical_queue.Clear();
	temp_inventory.Clear();
	gamestart = true;
	gameover = false;
	gamepause = false;
	gamestop = false;
	levelup = false;
	select_ready = false;
	browse_ready = false;
	boss_update = false;
	selected_element = FIRE;
	destX = 500, destY = 350;
	m_controller_i = 0;	
	basic_level = 0;
}

void UpdateScene(){
	if (!browse_ready) {//若没有浏览武器库，则播放角色动画
		CharacterIFrame();
		MyPaint();
	}
	else {//否则浏览武器库
		InventoryIFrame();
		BrowsePaint();
	}
	if (player.State() == DEAD&&player.End()) gameover = true;//若人物死亡且已播放完死亡动画，则游戏结束
}

void UpdateBattle(){
	if (!browse_ready) {
		if (background.Serial() == 2 && background.X() >= 1200 && !boss_update) {//若到最终决战区域，刷新boss,不再刷怪
			gril->SetShow(true);//boss刷新
			monster_queue.InQueue(gril);//boss进入队列
			boss_update = true;//标志更新
		}
		else {
			if (m_controller_i < 10 && m_controller[m_controller_i].x <= background.X() && !monster_queue.Full()) { //刷新怪物
				for (int i = 0; i < m_controller[m_controller_i].num;) {
					Monster *monster = CreateMonster(player.Level() - 1 , m_controller[m_controller_i].rarity);
					monster->SetShow(true);
					monster_queue.InQueue(monster);
					i++;
				}
				m_controller_i++;
			}
		}
		monster_queue.MoveToPlayer(player);//怪物朝人物移动
		monster_queue.CauseDamage(player);//怪物攻击人物
		if ((player.State() == CURSE || player.State() == HURT) && player.End()) player.Wait();
		if (player.State() == MOTIONLESS) ray->SetShow(false);
	}
}

void CreateSkill(int et, int at){
	player.Curse();//先更改人物的状态
	switch (at) {
	case MISSILE: {
		MissileSkill *bullet = new MissileSkill(et, player.C_X() + 20, player.C_Y());
		if (player.ExpendMana(bullet)) {
			skill_queue.InQueue(bullet);
		}
		else delete(bullet);
		break;
	}
	case STARSTRIKE: {
		StarStrikeSkill *star = new StarStrikeSkill(et, 300, 0, 100, destX, 350);
		if (player.ExpendMana(star)) {
			skill_queue.InQueue(star);
		}
		else delete(star);
		break;
	}
	default:break;
	}
}

void UpdateLevel(){
	if (levelup) {
		levelupbg.PSelect(mdc, bufdc);
		levelupimg.TransSelect(mdc, bufdc, 255, 255, 255);
		BitBlt(hdc, 0, 0, MAP_WIDTH, MAP_HEIGHT, mdc, 0, 0, SRCCOPY);//贴图
		if (levelupbg.End()) {
			levelupbg.ReSetCFrame();
			levelup = false;
		}
	}
}

void PlayerMove(int direction){
	if (direction == LEFT) player.MoveLeft();
	else player.MoveRight();
	UpdateScene();
	UpdateBattle();
}

void MapMove(int direction){
	for (int i = 0; i < 10; i++) {
		if (direction == LEFT) {
			background.MoveLeft(player.Velocity());
			temp_inventory.MoveRight(player.Velocity());
		}
		else {
			background.MoveRight(player.Velocity());
			temp_inventory.MoveLeft(player.Velocity());
		}
		UpdateScene();
		UpdateBattle();
	}
}

void Button_A(){//A键响应函数
	if (!gamestop) {
		if (browse_ready) {//若是浏览状态，则调用浏览状态的A响应函数
			Button_A_InBrowse();
		}
		else { //否则左移
			player.Move();//首先更改角色状态
			if (background.X() <= 0 || boss_update) {
				int d_x = player.X() - 50;//设置目标坐标为向左50码远的距离
				if (d_x < 0) d_x = 0;
				while (player.X() >= d_x) PlayerMove(LEFT);//人物移动
			}
			else {
				if (player.X() > SCENE_WIDTH / 2 - player.Width()) {//若角色坐标位于其能自由移动的范围
					int d_x = player.X() - 50;//设置目标坐标为向左50码远的距离
					while (player.X() != d_x&&player.X() > SCENE_WIDTH / 2 - player.Width()) PlayerMove(LEFT);//人物移动
				}
				else MapMove(LEFT);//否则地图移动
			}
			player.Wait();
		}
	}
}

void Button_D(){
	if (!gamestop) {
		if (browse_ready) {//若是浏览状态，则调用浏览状态的D响应函数
			Button_D_InBrowse();
		}
		else {//否则移动人物
			player.Move();
			if (background.X() >= background.Width() - MAP_WIDTH - 100 || boss_update) {
				int d_x = player.X() + 50;
				while (player.X() <= d_x) PlayerMove(RIGHT);

				if (player.X() >= MAP_WIDTH - (player.Width() / 2)) { 
					if (background.Serial() == 2) {
						background.Clear();
						ReStart();
					}
					else {
						SwitchMap();
					}
				}//若人物移动出地图，则切换地图
			}
			else if (player.X() < SCENE_WIDTH / 2 - player.Width()) {
				int d_x = player.X() + 50;
				while (player.X() <= d_x&&player.X() < SCENE_WIDTH / 2 - player.Width()) PlayerMove(RIGHT);
			}
			else MapMove(RIGHT);
			player.Wait();
		}
	}
}

void Button_R(){//第一次按下R键，表示构造投掷物，第二次按下R键，表示构造电属性
	if (!gamestop&& !browse_ready&&player.State() != CURSE&&player.State() != DEAD) {//游戏未结束、非浏览状态且人物未处于施法状态才进入技能构造
		if (select_ready) {
			selected_element = ELECTRICITY;//若准备更换元素，则更换为电元素
			select_ready = false;
		}
		else {
			CreateSkill(selected_element, MISSILE);
		}
	}
}

void Button_I(){
	browse_ready = !browse_ready;
}

void Button_E(){
	if (gameinfo) {//若是游戏信息浏览，则退出
		gamestart = true;
		gameinfo = false;
	}
	else {
		if (!gamestop && !browse_ready&&player.State() != CURSE&&player.State() != DEAD) {//若非浏览模式，则拾取武器
			if (select_ready) {
				selected_element = FROST;//若准备更换元素，则更换为冰元素
				select_ready = false;
			}
			else {//否则拾取武器
				player.Collect(temp_inventory);
			}
		}
		else if (browse_ready) {
			player.SelectWeapon();
		}
	}
}

void Button_Q() {//构造火元素或者流星
	if (!gamestop && !browse_ready&&player.State() != CURSE&&player.State() != DEAD) {
		if (select_ready) {
			selected_element = FIRE;//若准备更换元素，则更换为火元素
			select_ready = false;
		}
		else {
			if (!star_cd.On_CoolDown()) {
				star_cd.Trigger();
				CreateSkill(selected_element, STARSTRIKE);
			}
		}
	}
	else if (browse_ready) {
		player.Inventory()->DiscardWeapon();
	}
}

void Button_W(){
	if (!gamestop && !browse_ready&&player.State() != CURSE&&player.State() != DEAD) {
		if (select_ready) {
			selected_element = ARCANE;//若准备更换元素，则更换为奥术元素
			select_ready = false;
		}
		else {//否则显示射线
			player.Curse();
			if (player.ExpendMana(ray)) {
				ray->SetElementType(selected_element);
				ray->SetXY(player.C_X() + 120, player.C_Y());
				ray->SetShow(true);
			}
		}
	}
}

void Button_S() {
}

void Button_N(){
	gamepause = !gamepause;
}

void Button_SPACE(){
	select_ready = true;
}

void Button_Ctrl(){

}

void Button_A_InBrowse(){
	player.Inventory()->BrowsePre();
}

void Button_D_InBrowse(){
	player.Inventory()->BrowseNext();
}

void MQ_UnderAttack(Player &player, Skill *skill, MonsterQueue &m_q){
	if (!m_q.Empty()) 
		for (MonsterNode *tmp = m_q.head->next, *pre = m_q.head; tmp != NULL; pre = tmp, tmp = tmp->next) {//遍历整个怪物队列
			switch (skill->Get_ActionType()) {//根据技能的攻击方式来判定攻击位置
			case RAY://若是射线，则以中心坐标差是否进入技能攻击距离判定
				if (tmp->monster->C_X() - skill->C_X() <= skill->Get_AttackRange())
					player.CauseDamage(skill, tmp->monster);
				break;
			case MISSILE:
				if (tmp->monster->C_X() - skill->C_X() <= skill->Get_AOERange()) //若该怪物的中心坐标与技能中心坐标之差在技能的AOE范围内
					player.CauseDamage(skill, tmp->monster);//则人物传参造成伤害
				break;
			case STARSTRIKE:
				if (tmp->monster->C_X() - skill->C_X() <= skill->Get_AOERange())
					player.CauseDamage(skill, tmp->monster);
				break;
			}
		}
}
//
//  函数: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  目的:    处理主窗口的消息。
//
//  WM_COMMAND  - 处理应用程序菜单
//  WM_PAINT    - 绘制主窗口
//  WM_DESTROY  - 发送退出消息并返回
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
	{
	case WM_KEYDOWN:
		if (gamestart) break;
		switch (wParam){
		case 'r':case 'R':
			Button_R(); break;
		case 'd':case 'D':
			Button_D(); break;
		case 'a':case 'A':
			Button_A(); break;
		case 'i':case 'I':
			Button_I(); break;
		case 'e':case'E':
			Button_E(); break;
		case 'q':case'Q':
			Button_Q(); break;
		case 'w':case 'W':
			Button_W(); break;
		case 's':case 'S':
			Button_S(); break;
		case 'n':case 'N':
			Button_N(); break;
		case ' ':
			Button_SPACE(); break;
		default:break;
		}
	case WM_KEYUP:break;
	case WM_LBUTTONDOWN:
		if (gamestart) {
			if (destX >= 750 && destX <= 1070 && destY >= 360 && destY <= 492) {//开始游戏
				gamestart = false;
				SwitchMap();
			}
			else if (destX >= 700 && destX <= 967 && destY >= 145 && destY <= 226) {//游戏说明
				gamestart = false;
				gameinfo = true;
			}
			else if (destX >= 1220 && destX <= 1360 && destY >= 14 && destY <= 84) {//退出游戏
				ClipCursor(NULL);
				DeleteDC(mdc);
				DeleteDC(bufdc);
				ReleaseDC(hWnd, hdc);
				PostQuitMessage(0);
			}
		}
	case WM_MOUSEMOVE:
		destX = LOWORD(lParam);
		destY = HIWORD(lParam);
		break;
	case WM_RBUTTONDOWN:break;
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 分析菜单选择: 
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
	case WM_DESTROY:
		ClipCursor(NULL);
		DeleteDC(mdc);
		DeleteDC(bufdc);
		ReleaseDC(hWnd, hdc);
		PostQuitMessage(0);
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// “关于”框的消息处理程序。
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}