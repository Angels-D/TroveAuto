;@Ahk2Exe-UpdateManifest 2
;@Ahk2Exe-SetName TroveAuto
;@Ahk2Exe-SetProductVersion 2.4.10
;@Ahk2Exe-SetCopyright GPL-3.0 license
;@Ahk2Exe-SetLanguage Chinese_PRC
;@Ahk2Exe-SetMainIcon TroveAuto.ico
;@Ahk2Exe-SetDescription Trove自动脚本`, 解放双手
#SingleInstance Prompt

; DLL封装
#DllLoad Module
CloseHandle := DynaCall("CloseHandle", ["c=ui"])
OpenProcess := DynaCall("OpenProcess", ["ui=uicui", 3], 0x38, 0)
GetProcessBaseAddress := DynaCall("GetWindowLongPtr", ["ui=tiui"])
ReadProcessMemory := DynaCall("ReadProcessMemory", ["c=uiuituit"])
WriteProcessMemory := DynaCall("WriteProcessMemory", ["c=uiuituit"])

AobScan := DynaCall("Module\AobScanFindSig", ["ui=tuiuiaui6ui6i"])
UpdateConfig := DynaCall("Module\UpdateConfig", ["aa"])
FunctionOn := DynaCall("Module\FunctionOn", ["uiaai"])
FunctionOff := DynaCall("Module\FunctionOff", ["uia"])

WhichTarget := DynaCall("Module\WhichTarget", ["uituia"])

SetTitleMatchMode("RegEx")

config := _Config(
    "config.ini",
    Map(
        "Global", Map(
            "GameTitle", "Trove.exe",
            "GamePath", "",
            "ConfigVersion", "20250329160000",
            "AppVersion", "20250329160000",
            "Source", "https://github.com/Angels-D/TroveAuto/",
            "Mirror", "https://github.moeyy.xyz/",
            "StrCrypto", "y(Hn,(}I+2209Zd^s5(E%vfpoKh.I=",
            "Cheat", "Enter 你的30条命秘籍",
        ),
        "RefreshTime", Map("Value", "3000",),
        "AttackTime", Map("Value", "1000",),
        "HealthTime", Map("Value", "3000",),
        "UseLogTime", Map("Value", "3000",),
        "TP", Map(
            "Delay", "50",
            "Step", "4",
            "Distance", "4",
            "HotKey", "3",
            "WhiteList", "",
        ),
        "SpeedUp", Map(
            "Delay", "100",
        ),
        "AutoAim", Map(
            "Delay", "50",
            "TargetList", ".*chest_quest_.*",
            "NoTargetList", ".*pet.*,.*placeable.*,.*services.*,.*client.*,.*abilities.*",
        ),
        "Key", Map(
            "Press", "e",
            "Fish", "f",
        ),
        "Address", Map(
            "Animation", "0x829535",
            "Attack", "0x938FF8",
            "Breakblocks", "0x9D5793",
            "ByPass", "0x1520A6",
            "ClipCam", "0xA85BCA",
            "Dismount", "0x3CB5EE",
            "Fish", "0x11CB76C",
            "LockCam", "0xC5EBD5",
            "Map", "0xAEB4ED",
            "Mining", "0x920368",
            "MiningGeode", "0x9BFDD7",
            "NoClip", "0x6E9FE2",
            "Player", "0x11F9D40",
            "World", "0x11F74BC",
            "Zoom", "0xA83B06",
        ),
        "Address_Offset", Map(
            "Name", "0x0,0x28,0x1D0,0x0",
            "Player_Health", "0x0,0x28,0x1A4,0x80",
            "Player_Coord_X", "0x0,0x28,0xC4,0x4,0x80",
            "Player_Coord_Y", "0x0,0x28,0xC4,0x4,0x84",
            "Player_Coord_Z", "0x0,0x28,0xC4,0x4,0x88",
            "Player_Coord_XVel", "0x0,0x28,0xC4,0x4,0xB0",
            "Player_Coord_YVel", "0x0,0x28,0xC4,0x4,0xB4",
            "Player_Coord_ZVel", "0x0,0x28,0xC4,0x4,0xB8",
            "Player_Cam_V", "0x4,0x2C",
            "Player_Cam_H", "0x4,0x28",
            "Player_Cam_XPer", "0x4,0x24,0x84,0x0,0x100",
            "Player_Cam_YPer", "0x4,0x24,0x84,0x0,0x104",
            "Player_Cam_ZPer", "0x4,0x24,0x84,0x0,0x108",
            "World_Player_Count", "0xFC,0x2C",
            "World_Player_Base", "0xFC,0x00",
            "World_Player_Name", "0x1D0,0x00",
            "World_Player_X", "0xC4,0x04,0x80",
            "World_Player_Y", "0xC4,0x04,0x84",
            "World_Player_Z", "0xC4,0x04,0x88",
            "Fish_Take_Water", "0x68,0xE4,0x3C4",
            "Fish_Take_Lava", "0x68,0xE4,0x898",
            "Fish_Take_Choco", "0x68,0xE4,0x62C",
            "Fish_Take_Plasma", "0x68,0xE4,0xB00",
            "Fish_State_Water", "0x68,0xF4,0xBA0",
            "Fish_State_Lava", "0x68,0xF4,0x938",
            "Fish_State_Choco", "0x68,0xF4,0xE08",
            "Fish_State_Plasma", "0x68,0xF4,0x6CC",
        ),
        "Features_Change", Map(
            "Animation", "0x4C,0x44",
            "Attack", "0xF0,0xF1",
            "Breakblocks", "0x01,0x00",
            "ByPass", "0x47,0x67",
            "ClipCam", "0x909090,0x0F2901",
            "Dismount", "0xEB,0x74",
            "LockCam", "0xEB,0x74",
            "Map", "0xEB,0x77",
            "Mining", "0xF0,0xF1",
            "MiningGeode", "0xF0,0xF1",
            "NoClip", "0xEB,0x74",
            "Zoom", "0x57,0x5F",
        ),
        "Address_Offset_Signature", Map(
            "Attack", "1,DF F1 DD D8 72 1F",
            "Animation", "3,F3 0F 11 44 24 24 F3 0F 58 84 24 80 00 00 00 50 F3 0F 11 43 24 E8 XX XX XX XX 8D 44 24 34 50",
            "Breakblocks", "3,80 7F XX 00 0F 84 XX XX XX XX 8B 4B 08 E8 XX XX XX XX FF 75 0C 8B 4D 10 8B F0 FF 75 08 8B 45 14 83 EC 0C 8B 3E 8B D4 6A 01 89 0A 8B CE 89 42 04 8B 45 18",
            "ByPass", "1,DC 67 68 C6",
            "ClipCam", "0,0F 29 01 C7 41 34 00 00 00 00 0F",
            "Dismount", "0,74 XX 8B 07 8B CF 6A 00 6A 00 FF 50",
            "Fish", "0,10 14 XX XX 00 00 00 00 FF 00 00 00 00",
            "LockCam", "0,74 05 8B 01 FF 50 0C 8B E5",
            "Map", "0,77 XX B8 XX XX XX XX F3 0F 10 08 F3 0F 11 89 XX XX XX XX 8B 89",
            "Mining", "1,DF F1 DD D8 72 61",
            "MiningGeode", "1,DF F1 DD D8 72 35 8D",
            "NoClip", "-1443, 74 31 FF 73 14 8B 47 04 2B 07",
            "Player", "20,55 8B EC 83 E4 F8 83 EC 08 F3 0F 2A 45 10 56 8B F1 57 8B 3D",
            "World", "10,55 8B EC 83 7D 08 04 75 10 A1 XX XX XX XX 85 C0 74 07 C6 80 59 01 00 00 01 5D C2 04 00",
            "Zoom", "3,F3 0F 11 5F 2C",
            "Use_R", "-384,FE FF FF FF 00 00 00 00 65 CF XX XX 0C 00 00 00 55 CF",
            "Use_T", "-384,FE FF FF FF 00 00 00 00 65 CF XX XX 0E 00 00 00 55 CF",
        )
    )
)
config.Load()

MainGui := Gui("-DPIScale +Resize +MaxSize HScroll VScroll", "Trove辅助")
MainGui.Add("Tab3", "vTab", ["主页", "面板", "其他功能", "设置", "关于"])

; 主页内容
MainGui["Tab"].UseTab("主页")
MainGui.Add("Text", "x+60 y+70", "游戏路径:")
MainGui.Add("Edit", "w200 h70 vGamePath", config.data["Global"]["GamePath"])
MainGui.Add("Button", "Section vGamePathBtn", "获取游戏路径")
MainGui.Add("Button", "ys vGameStartBtn", "启动游戏")
MainGui.Add("Text", "xs w200", "说明: 当前使用Steam打开游戏会强制绑定账号, 直接使用官方启动器即可跳过绑定")
MainGui.Add("Button", "w200 vModsPathBtn", "Mods文件夹")
MainGui.Add("Link", "w200", "
    (
        说明: 本游戏支持模组, 可通过各公会群和Steam创意工坊等渠道下载, Mod制作或下载可使用
        <a href="https://github.com/DazoTrove/TroveTools.NET/">TroveTools.NET</a>等工具
    )"
)
MainGui.Add("Button", "w200 vModCfgsPathBtn", "ModCfgs文件夹")
MainGui.Add("Link", "w200", Format("说明: Cfgs用于保存某些Mod的配置信息,一般位于<a href=`"file:///{1}\Trove\ModCfgs\`">%AppData%\Trove\ModCfgs\</a>中", A_AppData))
MainGui.Add("Text", "w200", "Mod使用教程: 后缀为.tmod的文件存放在Mods文件夹, 后缀为.cfg的文件存放在ModCfgs文件夹, 放置后重启游戏生效")
MainGui.Add("Link", "w200", "附: 官方邮箱<a href=`"mailto:support@gamigo.com`">support@gamigo.com</a>(通过此邮箱询问交易问题、账号问题等内容,注意使用英文描述")
MainGui.Add("Link", "w200 cRed", "
    (
        推荐: 
        > <a href="https://github.com/Sly0511/RenewedTroveTools/">RenewedTroveTools</a>工具
        管理你的Mod和CFG文件, 还有装备推荐、模拟加点、模组开发管理、模组下载等功能

        > <a href="https://qm.qq.com/q/mu0FmpznQm">Trove ToolBox</a>工具
        管理你的游戏登录, 还有多开窗口自动排列、崩溃重启、防掉线等功能
    )"
)
MainGui.Add("Button", "y+10 w200 h40 vUseLogPathBtn", "物品栏使用日志文件夹")
MainGui.Add("Button", "y+10 w200 h40 vConfigFileBtn", "打开配置文件")

; 面板内容
MainGui["Tab"].UseTab("面板")
MainGui.Add("Button", "x+50 y+10 w50 Section vResetBtn", "重置")
MainGui.Add("Button", "ys w50 vRefreshBtn", "刷新")
MainGui.Add("Button", "ys x+50 w70 vStartBtn", "启动")
MainGui.Add("Text", "xs w70 Section", "玩家列表:")
MainGui.Add("DropDownList", "ys w150 vSelectGame")
MainGui.Add("Text", "xs w70 Section", "脚本动作:")
MainGui.Add("DropDownList", "ys w150 vSelectAction", ["自动按键", "钓鱼"])
MainGui.Add("GroupBox", "xs-40 y+20 w310 r9 Section", "自动按键配置区")
MainGui.Add("Text", "xp+10 yp+30 Section", "频率(毫秒):")
MainGui.Add("Edit", "ys w120 vInterval")
MainGui.Add("ListView", "xs w290 Section NoSortHdr Checked -Multi vHotKeyBox", ["热键", "持续时间", "间隔时间", "次数"])
MainGui.Add("CheckBox", "xs Section w140 vAutoBtn_Key_Click_LEFT", "自动左击")
MainGui.Add("CheckBox", "ys w140 vAutoBtn_Key_Click_RIGHT", "自动右击")
MainGui.Add("CheckBox", "xs Section w200 vAutoBtn_NoTop", "前台时禁用")
MainGui.Add("GroupBox", "xs-10 ys+40 w310 r7 Section", "功能区")
for key, value in Map(
    "Animation", "隐藏特效",
    "Attack", "自动攻击",
    "Breakblocks", "打破障碍",
    "ByPass", "绕过",
    "ClipCam", "视角遮挡",
    "Dismount", "保持骑乘",
    "Health", "自动复活",
    "LockCam", "视角固定",
    "Map", "地图放大",
    "Mining", "快速挖矿",
    "MiningGeode", "快速挖矿(晶洞)",
    "NoClip", "穿墙",
    "UseLog", "物品栏计数",
    "Zoom", "视野放大",
)
    MainGui.Add("CheckBox", (Mod(A_Index, 2) ? ((A_Index == 1 ? "xp+10 yp+30" : "xs") " Section") : "ys") " w140 v" key, value)
MainGui.Add("GroupBox", "xs-10 ys+40 w310 r4.2 Section", "跟随目标       正则表达式 逗号分割")
MainGui.Add("CheckBox", "xp+80 yp vFollowTarget")
MainGui.Add("Text", "xs+10 ys+30 Section", "玩家列表:")
MainGui.Add("Edit", "ys w205 vFollowTarget_PlayerName")
MainGui.Add("Text", "xs ys+30 Section", "实体列表:")
MainGui.Add("Edit", "ys w205 vFollowTarget_TargetName")
MainGui.Add("CheckBox", "xs w90 Section vFollowTarget_TargetBoss", "跟踪Boss")
MainGui.Add("CheckBox", "ys w90 vFollowTarget_TargetList", "全局名单")
MainGui.Add("CheckBox", "ys w90 vFollowTarget_ScanAll", "扫图模式")
MainGui.Add("GroupBox", "xs-10 ys+40 w310 r2 Section", "矢量移动       WASD/Shift/Space移动")
MainGui.Add("CheckBox", "xp+80 yp vSpeedUp")
MainGui.Add("Text", "xs+10 ys+30 Section", "加速倍率:")
MainGui.Add("Edit", "ys w205 vSpeedUp_SpeedUpRate")
MainGui.Add("GroupBox", "xs-10 ys+50 w310 r3 Section", "自动瞄准")
MainGui.Add("CheckBox", "xp+80 yp vAutoAim")
MainGui.Add("Text", "xs+10 ys+30 Section", "瞄准范围:")
MainGui.Add("Edit", "ys w205 vAutoAim_AimRange")
MainGui.Add("CheckBox", "xs w90 Section vAutoAim_TargetBoss", "锁定Boss")
MainGui.Add("CheckBox", "ys w90 vAutoAim_TargetNormal", "锁定小怪")
MainGui.Add("CheckBox", "ys w90 vAutoAim_TargetPlant", "锁定植物")
MainGui.Add("Text", "xs+40 ys+50 cRed", "任何脚本都有风险, 请慎用!")

; 其他功能内容
MainGui["Tab"].UseTab("其他功能")
MainGui.Add("GroupBox", "xs-10 y+10 w310 r3.5 Section", "崩溃相关")
MainGui.Add("GroupBox", "xs+10 ys+30 w290 r2 Section", "自动刷新")
MainGui.Add("CheckBox", "xp+110 yp vAutoRefresh")
MainGui.Add("Text", "xs+10 ys+30 w100 Section", "刷新间隔(ms):")
MainGui.Add("Edit", "ys w140 vRefreshTime", config.data["RefreshTime"]["Value"])
MainGui.Add("GroupBox", "xs-20 y+40 w310 r13 Section", "传送相关")
MainGui.Add("GroupBox", "xs+10 ys+30 w290 r3 Section", "当前玩家传送")
MainGui.Add("CheckBox", "xp+110 yp vTP")
MainGui.Add("Text", "xs+10 ys+30 w90 Section", "传送距离:")
MainGui.Add("Edit", "ys w150 vDistanceTP", config.data["TP"]["Distance"])
MainGui.Add("Text", "xs w90 Section", "传送热键:")
MainGui.Add("HotKey", "ys w150 vHotKeyTP", config.data["TP"]["HotKey"])
MainGui.Add("GroupBox", "xs-10 ys+40 w290 r7.2 Section", "指定坐标传送")
MainGui.Add("Text", "xs+10 ys+30 w90 Section", "玩家名:")
MainGui.Add("Edit", "ys w150 vTPPlayerName")
MainGui.Add("Text", "xs w30 Section", "X:")
MainGui.Add("Edit", "ys w210 vTPtoX", 0)
MainGui.Add("Text", "xs w30 Section", "Y:")
MainGui.Add("Edit", "ys w210 vTPtoY", 0)
MainGui.Add("Text", "xs w30 Section", "Z:")
MainGui.Add("Edit", "ys w210 vTPtoZ", 0)
MainGui.Add("Button", "xs w250 vTPtoXYZBtn", "传送")
MainGui.Add("GroupBox", "xs-20 y+30 w310 r15.5 Section", "目标扫描相关")
MainGui.Add("CheckBox", "xs+10 ys+30 Section vTop_AutoAim", "当前玩家静默攻击瞄准(鼠标左键)")
MainGui.Add("CheckBox", "xs w270 vTop_WhichTarget", "当前玩家扫描目标信息(鼠标中键)")
MainGui.Add("Text", "xs Section", "扫描范围:")
MainGui.Add("Edit", "ys w170 vTop_AutoAim_AimRange", 45)
MainGui.Add("CheckBox", "xs w85 Section checked vTop_AutoAim_TargetBoss", "锁定Boss")
MainGui.Add("CheckBox", "ys w80 vTop_AutoAim_TargetNormal", "锁定小怪")
MainGui.Add("CheckBox", "ys w80 vTop_AutoAim_TargetPlant", "锁定植物")
MainGui.Add("GroupBox", "xs ys+40 w290 r4 Section", "目标名单     正则表达式 逗号隔开")
MainGui.Add("Edit", "xs+10 ys+30 w260 h80 vTargetListAutoAim", config.data["AutoAim"]["TargetList"])
MainGui.Add("GroupBox", "xs w290 r4 Section", "非目标名单   正则表达式 逗号隔开")
MainGui.Add("Edit", "xs+10 ys+30 w260 h80 vNoTargetListAutoAim", config.data["AutoAim"]["NoTargetList"])
MainGui.Add("Text", "xs+60 y+35", "部分内容保存后生效")

; 设置内容
MainGui["Tab"].UseTab("设置")
MainGui.Add("Text", "x+40 y+10 w100 Section", "游戏标题:")
MainGui.Add("Edit", "ys w150 vGameTitle", config.data["Global"]["GameTitle"])
for key, value in Map(
    "Animation", "隐藏特效",
    "Attack", "自动攻击",
    "Breakblocks", "打破障碍",
    "ByPass", "绕过",
    "ClipCam", "视角遮挡",
    "Dismount", "保持骑乘",
    "Fish", "钓鱼",
    "LockCam", "视角固定",
    "Map", "地图放大",
    "Mining", "快速挖矿",
    "MiningGeode", "快速挖矿(晶洞)",
    "NoClip", "穿墙",
    "Player", "玩家",
    "World", "世界",
    "Zoom", "视野放大",
) {
    MainGui.Add("Text", "xs w100 Section", value "地址:")
    MainGui.Add("Edit", "ys w150 v" key "Address", config.data["Address"][key])
}
MainGui.Add("Text", "xs w100 Section", "交互按键:")
MainGui.Add("HotKey", "ys w150 vPressKey", config.data["Key"]["Press"])
MainGui.Add("Text", "xs w100 Section", "钓鱼按键:")
MainGui.Add("HotKey", "ys w150 vFishKey", config.data["Key"]["Fish"])
MainGui.Add("Text", "xs w100 Section", "攻击扫描(ms):")
MainGui.Add("Edit", "ys w150 vAttackTime", config.data["AttackTime"]["Value"])
MainGui.Add("Text", "xs w100 Section", "血量扫描(ms):")
MainGui.Add("Edit", "ys w150 vHealthTime", config.data["HealthTime"]["Value"])
MainGui.Add("Text", "xs w100 Section", "物品扫描(ms):")
MainGui.Add("Edit", "ys w150 vUseLogTime", config.data["UseLogTime"]["Value"])
MainGui.Add("Text", "xs w100 Section", "步进距离:")
MainGui.Add("Edit", "ys w150 vStepTP", config.data["TP"]["Step"])
MainGui.Add("Text", "xs w100 Section", "传送频率(ms):")
MainGui.Add("Edit", "ys w150 vDelayTP", config.data["TP"]["Delay"])
MainGui.Add("Text", "xs w100 Section", "加速频率(ms):")
MainGui.Add("Edit", "ys w150 vDelaySpeedUp", config.data["SpeedUp"]["Delay"])
MainGui.Add("Text", "xs w100 Section", "自瞄频率(ms):")
MainGui.Add("Edit", "ys w150 vDelayAutoAim", config.data["AutoAim"]["Delay"])
MainGui.Add("Text", "xs w100 Section", "跟随白名单:")
MainGui.Add("Edit", "ys w150 r1 vWhiteListTP", config.data["TP"]["WhiteList"])
MainGui.Add("Text", "xs w100 Section", "镜像源:")
MainGui.Add("Edit", "ys w150 r1 vMirror", config.data["Global"]["Mirror"])
MainGui.Add("Button", "xs w80 Section vSaveBtn", "保存")
MainGui.Add("Button", "ys w80 vUpdateFromInternetBtn", "联网更新")
MainGui.Add("Button", "ys w80 vUpdateFromLocalBtn", "本地更新")

; 关于内容
MainGui["Tab"].UseTab("关于")
MainGui.Add("ActiveX", "w150 h150 x+30 y+100 Center",
    "mshtml:<img src='https://cdn.jsdelivr.net/gh/Angels-D/Angels-D.github.io/medias/avatar.jpg' style='width:150px;'/>")
MainGui.Add("Text", , "作者: とても残念だ(AnglesD)")
MainGui.Add("Text", "cRed", "本软件完全开源免费, 仅供学习使用！")
MainGui.Add("Link", , Format("
    (
        许可协议: <a href="https://www.gnu.org/licenses/gpl-3.0.zh-cn.html/">GPL-3.0 license</a>`n
        博客: <a href="https://Angels-D.github.io/">https://Angels-D.github.io</a>`n
        源码: <a href="https://github.com/Angels-D/TroveAuto">Angels-D/TroveAuto On Github</a>`n
        应用版本: {1}`n
    )", config.data["Global"]["AppVersion"])
)
MainGui.Add("Button", "y+30 w200 h60 vDownloadBtn", "最新版脚本下载")

; 绑定交互
MainGui.OnEvent("Close", Close, -1)
MainGui["GamePathBtn"].OnEvent("Click", GetGamePath)
MainGui["GameStartBtn"].OnEvent("Click", GameStart)
MainGui["ModsPathBtn"].OnEvent("Click", OpenModsPath)
MainGui["ModCfgsPathBtn"].OnEvent("Click", OpenModCfgsPath)
MainGui["UseLogPathBtn"].OnEvent("Click", OpenUseLogPath)
MainGui["ConfigFileBtn"].OnEvent("Click", ConfigFile)
MainGui["ResetBtn"].OnEvent("Click", Reset)
MainGui["RefreshBtn"].OnEvent("Click", Refresh)
MainGui["StartBtn"].OnEvent("Click", Start)
MainGui["SaveBtn"].OnEvent("Click", Save)
MainGui["UpdateFromInternetBtn"].OnEvent("Click", UpdateFromInternet)
MainGui["UpdateFromLocalBtn"].OnEvent("Click", UpdateFromLocal)
MainGui["DownloadBtn"].OnEvent("Click", DownloadExe)
MainGui["SelectGame"].OnEvent("Change", SelectGame)
MainGui["SelectAction"].OnEvent("Change", SelectAction)
MainGui["Interval"].OnEvent("Change", Interval)
MainGui["HotKeyBox"].OnEvent("ContextMenu", HotKeyMenu)
MainGui["HotKeyBox"].OnEvent("DoubleClick", HotKeyEdit)
MainGui["HotKeyBox"].OnEvent("ItemCheck", HotKeyCheck)
MainGui["AutoBtn_Key_Click_LEFT"].OnEvent("Click", AutoBtn_Key_Click_LEFT)
MainGui["AutoBtn_Key_Click_RIGHT"].OnEvent("Click", AutoBtn_Key_Click_RIGHT)
MainGui["AutoBtn_NoTop"].OnEvent("Click", AutoBtn_NoTop)
MainGui["FollowTarget"].OnEvent("Click", FollowTarget)
MainGui["AutoAim"].OnEvent("Click", AutoAim)
MainGui["SpeedUp"].OnEvent("Click", SpeedUp)
for key in ["FollowTarget_PlayerName", "FollowTarget_TargetName", "FollowTarget_TargetBoss", "FollowTarget_TargetList", "FollowTarget_ScanAll"
    , "SpeedUp_SpeedUpRate", "AutoAim_AimRange", "AutoAim_TargetBoss", "AutoAim_TargetNormal", "AutoAim_TargetPlant"] {
    try MainGui[key].OnEvent("Change", SomeUiSetChangeEvent)
    catch
        MainGui[key].OnEvent("Click", SomeUiSetChangeEvent)
}
for key in ["Animation", "Attack", "Breakblocks", "ByPass", "ClipCam", "Dismount"
    , "Health", "LockCam", "Map", "Mining", "MiningGeode", "NoClip", "UseLog", "Zoom"]
    MainGui[key].OnEvent("Click", Features)
MainGui["AutoRefresh"].OnEvent("Click", AutoRefresh)
MainGui["TP"].OnEvent("Click", TP)
MainGui["TPtoXYZBtn"].OnEvent("Click", TPtoXYZ)
MainGui["Top_AutoAim"].OnEvent("Click", Top_AutoAim)
MainGui["Top_WhichTarget"].OnEvent("Click", Top_WhichTarget)


; 托盘图标
A_TrayMenu.Delete()
A_TrayMenu.Add("显示", (ItemName, ItemPos, MyMenu) => (MainGui.Show()))
A_TrayMenu.Add("重新启动", (ItemName, ItemPos, MyMenu) => (Game.Reset(), Reload()))
A_TrayMenu.Add("退出", (ItemName, ItemPos, MyMenu) => (Game.Reset(), ExitApp()))

; 交互函数
Close(thisGui) {
    Result := MsgBox("是: 关闭脚本`n否: 最小化到托盘", , 3)
    switch Result {
        case "Yes":
            Game.Reset()
            ExitApp
        case "No":
        default:
            return true
    }
}
GetGamePath(GuiCtrlObj, Info) {
    try {
        GamePathFromReg := () {
            for reg_path in ["HKCU\SOFTWARE\Microsoft\Windows\CurrentVersion\Explorer\FeatureUsage",
                "HKCU\Software\Microsoft\Windows NT\CurrentVersion\AppCompatFlags\Compatibility Assistant\Store"]
                loop reg reg_path, "R"
                    if (InStr(A_LoopRegName, "Trove\GlyphClientApp.exe") && FileExist(A_LoopRegName)) {
                        SplitPath(A_LoopRegName, , &dir)
                        return dir
                    }
            loop reg "HKLM\Software\Microsoft\Windows\CurrentVersion\Uninstall", "KR"
            {
                try
                    if (RegRead(, "DisplayName") == "Trove")
                        return RegRead(, "InstallLocation")
            }
        }()
        if ( not GamePathFromReg) {
            GamePath := WinGetProcessPath("ahk_exe i)" config.data["Global"]["GameTitle"] "|Glyph.*")
            RegExMatch(GamePath, "i)^(.*?Trove)", &GamePath)
            MainGui["GamePath"].Value := GamePath[0]
        }
        else
            MainGui["GamePath"].Value := GamePathFromReg
        Save()
    }
    catch
        MsgBox("请运行游戏或登陆器以检测路径")
}
GameStart(GuiCtrlObj := unset, Info := unset) {
    try Run(Format("{1}\GlyphClient.exe", config.data["Global"]["GamePath"]))
    catch
        MsgBox("游戏启动失败, 请检查游戏路径")
}
OpenModsPath(GuiCtrlObj, Info) {
    try Run(Format("explore {1}\Games\Trove\Live\mods", config.data["Global"]["GamePath"]))
    catch
        MsgBox("Mods文件夹打开失败, 请检查游戏路径")
}
OpenModCfgsPath(GuiCtrlObj, Info) {
    try Run(Format("explore {1}\Trove\ModCfgs\", A_AppData))
    catch
        MsgBox("ModCfgs文件夹打开失败, 请检查文件夹是否存在")
}
OpenUseLogPath(GuiCtrlObj, Info) {
    DirCreate("UseLog")
    try Run("explore UseLog\")
    catch
        MsgBox("日志文件夹打开失败, 请检查文件夹是否存在")
}
ConfigFile(GuiCtrlObj, Info) {
    try Run("config.ini")
    catch
        MsgBox("配置文件打开失败, 请先保存配置以生成")
}
Reset(GuiCtrlObj := unset, Info := unset) {
    Game.Reset()
    MainGui["SelectGame"].Text := ""
    Refresh()
}
Refresh(GuiCtrlObj := unset, Info := unset) {
    GameNameList := Game.Refresh()
    theGameName := MainGui["SelectGame"].Text
    MainGui["SelectGame"].Delete()
    MainGui["SelectGame"].Add(GameNameList)
    for name in GameNameList
        if (name == theGameName)
            MainGui["SelectGame"].Text := theGameName
    if (MainGui["SelectGame"].Text == "")
        UIReset()
}
UIReset() {
    for key in ["Animation", "Attack", "Breakblocks", "ByPass", "ClipCam", "Dismount"
        , "Health", "LockCam", "Map", "Mining", "MiningGeode", "NoClip", "UseLog", "Zoom"
        , "AutoBtn_Key_Click_LEFT", "AutoBtn_Key_Click_RIGHT", "AutoBtn_NoTop", "HotKeyBox"
        , "Interval", "SelectAction", "StartBtn", "FollowTarget", "FollowTarget_PlayerName"
        , "FollowTarget_TargetName", "FollowTarget_TargetBoss", "FollowTarget_TargetList", "FollowTarget_ScanAll"
        , "SpeedUp", "SpeedUp_SpeedUpRate", "AutoAim", "AutoAim_AimRange"
        , "AutoAim_TargetBoss", "AutoAim_TargetNormal", "AutoAim_TargetPlant"]
        MainGui[key].Enabled := false
    for key in ["Animation", "Attack", "Breakblocks", "ByPass", "ClipCam", "Dismount"
        , "Health", "LockCam", "Map", "Mining", "MiningGeode", "NoClip", "UseLog", "Zoom"
        , "AutoBtn_Key_Click_LEFT", "AutoBtn_Key_Click_RIGHT", "AutoBtn_NoTop"
        , "Interval", "SelectAction", "FollowTarget", "FollowTarget_PlayerName"
        , "FollowTarget_TargetName", "FollowTarget_TargetBoss", "FollowTarget_TargetList", "FollowTarget_ScanAll"
        , "SpeedUp", "SpeedUp_SpeedUpRate", "AutoAim", "AutoAim_AimRange"
        , "AutoAim_TargetBoss", "AutoAim_TargetNormal", "AutoAim_TargetPlant"]
        try MainGui[key].Value := ""
        catch
            MainGui[key].Value := 0
    MainGui["FollowTarget_ScanAll"].Visible := (config.data["Global"].has("Cheat")
        and config.data["Global"]["Cheat"] == "whosyourdaddy")
    MainGui["HotKeyBox"].Delete()
    MainGui["WhiteListTP"].Value := config.data["TP"]["WhiteList"]
}
Start(GuiCtrlObj, Info) {
    theGame := Game.Lists[MainGui["SelectGame"].Text]
    if (theGame.running) {
        MainGui["StartBtn"].Text := "启动"
        for key in ["SelectAction", "Interval"]
            MainGui[key].Enabled := true
        theGame.running := false
        switch MainGui["SelectAction"].Text {
            case "钓鱼":
                theGame.AutoFish()
            default:
                for key in ["HotKeyBox", "AutoBtn_Key_Click_LEFT", "AutoBtn_Key_Click_RIGHT", "AutoBtn_NoTop"]
                    MainGui[key].Enabled := true
                theGame.AutoBtn()
        }
    }
    else {
        if not MainGui["Interval"].Value {
            MsgBox("请设置频率")
            return
        }
        MainGui["StartBtn"].Text := "关闭"
        for key in ["SelectAction", "Interval"]
            MainGui[key].Enabled := false
        theGame.running := true
        switch MainGui["SelectAction"].Text {
            case "钓鱼":
                theGame.AutoFish()
            default:
                for key in ["HotKeyBox", "AutoBtn_Key_Click_LEFT", "AutoBtn_Key_Click_RIGHT", "AutoBtn_NoTop"]
                    MainGui[key].Enabled := false
                theGame.AutoBtn()
        }
    }
}
Save(GuiCtrlObj := unset, Info := unset) {
    for sect, data in config.data {
        if (sect == "Address_Offset" or sect == "Features_Change" or sect == "Address_Offset_Signature")
            Continue
        for key in data {
            try value := MainGui[key sect].Value
            catch
                try value := MainGui[key == "Value" ? sect : key].Value
                catch
                    value := config.data[sect][key]
            if ( not value and key != "GamePath" and key != "WhiteList") {
                MsgBox("配置项不能为空")
                return
            }
            config.data[sect][key] := value
        }
    }
    config.Save()
    config.UpdateDllConfig()
}
UpdateFromInternet(GuiCtrlObj, Info) {
    Source := config.data["Global"]["Source"] "releases/latest/download/config.ini"
    Mirror := config.data["Global"]["Mirror"] Source
    if (config.Update(Mirror) Or config.Update(Source)) {
        MainGui.Add("Text", "x+50 w100 Section", "游戏标题:")
        MainGui["GameTitle"].Text := config.data["Global"]["GameTitle"]
        for sect in ["Address", "Key"]
            for key, value in config.data[sect]
                MainGui[key sect].Text := config.data[sect][key]
        Save()
    }
    else MsgBox("更新失败, 请检查网络连接")
}
UpdateFromLocal(GuiCtrlObj, Info) {
    try GameID := WinGetID("ahk_exe " config.data["Global"]["GameTitle"])
    catch {
        MsgBox("请先启动游戏, 再进行扫描")
        return
    }
    BaseAddress := GetProcessBaseAddress(GameID, -6)
    Result := Buffer(1024, 0)
    for key, value in config.data["Address"] {
        pid := WinGetPID(GameID)
        signature := StrSplit(config.data["Address_Offset_Signature"][key], ',')
        size := AobScan(Result, Result.Size, pid, RegExReplace(StrReplace(signature[2], " "), "X|x", "?"), BaseAddress, 0x7FFFFFFF, 1)
        if (size) {
            value := NumGet(Result, "UInt") + signature[1]
            if (key == "Player" or key == "World" and size) {
                ProcessHandle := OpenProcess(Pid)
                ReadProcessMemory(ProcessHandle, value, Result, 4)
                value := NumGet(Result, "UInt")
                CloseHandle(ProcessHandle)
            }
            MainGui[key "Address"].Text := Format("0x{1:X}", value - BaseAddress)
        }
        else
            MainGui[key "Address"].Text := "0x7FFFFFFF"
    }
    Msgbox("检测完毕, 确认无误后请手动保存")
}
DownloadExe(GuiCtrlObj, Info) {
    Source := config.data["Global"]["Source"] "releases/latest/download/TroveAuto.exe"
    Mirror := config.data["Global"]["Mirror"] Source
    SelectedFile := FileSelect(18, "Trove辅助.exe", "保存路径", "可执行文件 (*.exe)")
    if not SelectedFile
        return
    try Download(Mirror, SelectedFile)
    catch
        try Download(Source, SelectedFile)
        catch
            MsgBox("下载失败, 请检查网络连接")
        else MsgBox("应用下载成功, 请打开最新版本")
    else MsgBox("应用下载成功, 请打开最新版本")
}
SelectGame(GuiCtrlObj, Info) {
    MainGui["SelectAction"].Text := Game.Lists[GuiCtrlObj.Text].action
    MainGui["StartBtn"].Text := Game.Lists[GuiCtrlObj.Text].running ? "关闭" : "启动"
    for key in ["SelectAction", "Interval"]
        MainGui[key].Enabled := !Game.Lists[GuiCtrlObj.Text].running
    MainGui["StartBtn"].Enabled := true
    SelectAction(MainGui["SelectAction"])
}
SelectAction(GuiCtrlObj, Info := unset) {
    theGame := Game.Lists[MainGui["SelectGame"].Text]
    theGame.action := GuiCtrlObj.Text
    for key in ["FollowTarget", "SpeedUp", "AutoAim"] {
        MainGui[key].Enabled := true
        for item in theGame.setting[key] {
            if (item == "On")
                MainGui[key].Value := theGame.setting[key][item]
            else {
                MainGui[key "_" item].Value := theGame.setting[key][item]
                MainGui[key "_" item].Enabled := !theGame.setting[key]["On"]
            }
        }
    }
    for key in ["Animation", "Attack", "Breakblocks", "ByPass", "ClipCam", "Dismount"
        , "Health", "LockCam", "Map", "Mining", "MiningGeode", "NoClip", "UseLog", "Zoom"] {
        MainGui[key].Enabled := true
        MainGui[key].Value := theGame.setting["Features"][key]
    }
    for key in ["HotKeyBox", "AutoBtn_Key_Click_LEFT", "AutoBtn_Key_Click_RIGHT", "AutoBtn_NoTop"]
        MainGui[key].Enabled := false
    MainGui["HotKeyBox"].Delete()
    for key in theGame.setting["AutoBtn"]["keys"]
        MainGui["HotKeyBox"].Add(key.enabled ? "+Check" : "-Check", key.key, key.holdtime, key.interval, key.count)
    for key in ["Key_Click_LEFT", "Key_Click_RIGHT", "NoTop"]
        MainGui["AutoBtn_" key].Value := theGame.setting["AutoBtn"][key]
    switch GuiCtrlObj.Text {
        case "自动按键":
            MainGui["Interval"].Value := theGame.setting["AutoBtn"]["interval"]
            if (!theGame.running)
                for key in ["HotKeyBox", "AutoBtn_Key_Click_LEFT", "AutoBtn_Key_Click_RIGHT", "AutoBtn_NoTop"]
                    MainGui[key].Enabled := true
        case "钓鱼":
            MainGui["Interval"].Value := theGame.setting["Fish"]["interval"]
    }
}
Features(GuiCtrlObj, Info) {
    theGame := Game.Lists[MainGui["SelectGame"].Text]
    theGame.setting["Features"][GuiCtrlObj.Name] := GuiCtrlObj.Value
    theGame.Features(GuiCtrlObj.Name, GuiCtrlObj.Value)
}
AutoRefresh(GuiCtrlObj, Info) {
    SetTimer(Refresh, GuiCtrlObj.Value ? config.data["RefreshTime"]["Value"] : 0)
}
TP(GuiCtrlObj, Info) {
    if (GuiCtrlObj.Value)
        Hotkey(MainGui["HotKeyTP"].Value, (*) {
            try
                if (WinGetProcessName("A") == config.data["Global"]["GameTitle"]) {
                    FunctionOn(WingetPID("A"), "SetByPass", "1", true)
                    FunctionOn(WingetPID("A"), "Tp2Forward", MainGui["DistanceTP"].Value "|" MainGui["DelayTP"].Value, true)
                }
            Send(MainGui["HotKeyTP"].Value)
        }, "On I1")
    else
        Hotkey(MainGui["HotKeyTP"].Value, , "Off")
    for key in ["StepTP", "DelayTP", "DistanceTP", "HotKeyTP"]
        MainGui[key].enabled := not GuiCtrlObj.Value
}
TPtoXYZ(GuiCtrlObj, Info) {
    if (Game.Lists.Has(MainGui["TPPlayerName"].Value))
        theGame := Game.Lists[MainGui["TPPlayerName"].Value]
    else {
        GameIDs := WinGetList("ahk_exe " config.data["Global"]["GameTitle"])
        for id in GameIDs {
            theGame := Game(id)
            if theGame.name == MainGui["TPPlayerName"].Value
                break
        }
    }
    if ( not theGame)
        return
    FunctionOn(WingetPID("A"), "SetByPass", "1", true)
    FunctionOn(theGame.pid, "Tp2Target"
        , MainGui["TPtoX"].Value "|"
        MainGui["TPtoY"].Value "|"
        MainGui["TPtoZ"].Value "|"
        MainGui["DelayTP"].Value "|10", true)
}
Top_AutoAim(GuiCtrlObj, Info) {
    if (GuiCtrlObj.Value)
        Hotkey("LButton", (*) {
            Click("Down")
            try
                if (WinGetProcessName("A") == config.data["Global"]["GameTitle"]) {
                    pid := WingetPID("A")
                    FunctionOn(pid, "AutoAim", Format("{1}|{2}|{3}|{4}|{5}|{6}|{7}|{8}"
                        , MainGui["Top_AutoAim_TargetBoss"].Value
                        , MainGui["Top_AutoAim_TargetPlant"].Value
                        , MainGui["Top_AutoAim_TargetNormal"].Value
                        , config.data["AutoAim"]["TargetList"]
                        , config.data["AutoAim"]["NoTargetList"]
                        , MainGui["Top_AutoAim_AimRange"].Value
                        , config.data["AutoAim"]["Delay"]), false)
                }
            while (GetKeyState("LButton", "P"))
                Sleep(100)
            if IsSet(pid)
                FunctionOff(pid, "AutoAim")
            Click("UP")
        }, "On I1")
    else
        Hotkey("LButton", , "Off")
    for key in ["Top_AutoAim_AimRange", "Top_AutoAim_TargetBoss", "Top_AutoAim_TargetNormal", "Top_AutoAim_TargetPlant"]
        MainGui[key].enabled := not GuiCtrlObj.Value
}
Top_WhichTarget(GuiCtrlObj, Info) {
    if (GuiCtrlObj.Value)
        Hotkey("MButton", (*) {
            Click("Middle Down")
            try
                if (WinGetProcessName("A") == config.data["Global"]["GameTitle"]) {
                    pid := WingetPID("A")
                    Mvalue := Buffer(1024, 0)
                    WhichTarget(pid, Mvalue, Mvalue.Size
                        , Format("{1}|{2}|{3}|{4}|{5}|{6}"
                            , MainGui["Top_AutoAim_TargetBoss"].Value
                            , MainGui["Top_AutoAim_TargetPlant"].Value
                            , MainGui["Top_AutoAim_TargetNormal"].Value
                            , config.data["AutoAim"]["TargetList"]
                            , config.data["AutoAim"]["NoTargetList"]
                            , MainGui["Top_AutoAim_AimRange"].Value))
                    result := StrSplit(StrGet(Mvalue, "utf-8"), ',')
                    if (result.Length >= 6) {
                        A_Clipboard := result[1]
                        ToolTip(Format("名称(见剪贴板): {1}`n等级: {2} 血量: {3}`n坐标(XYZ): {4},{5},{6}"
                            , result[1], result[2], result[3], result[4], result[5], result[6]))
                        SetTimer(() => ToolTip(), -3000)
                }
        }
            while (GetKeyState("MButton", "P"))
                Sleep(100)
                    Click("Middle UP")
        }, "On I1")
else
    Hotkey("MButton", , "Off")
for key in ["Top_AutoAim_AimRange", "Top_AutoAim_TargetBoss", "Top_AutoAim_TargetNormal", "Top_AutoAim_TargetPlant"]
    MainGui[key].enabled := not GuiCtrlObj.Value
}
Interval(GuiCtrlObj, Info) {
    theGame := Game.Lists[MainGui["SelectGame"].Text]
    switch MainGui["SelectAction"].Text {
        case "自动按键":
            theGame.setting["AutoBtn"]["interval"] := GuiCtrlObj.value
        case "钓鱼":
            theGame.setting["Fish"]["interval"] := GuiCtrlObj.value
    }
}
AutoBtn_Key_Click_LEFT(GuiCtrlObj, Info) {
    Game.Lists[MainGui["SelectGame"].Text].setting["AutoBtn"]["Key_Click_LEFT"] := GuiCtrlObj.Value
}
AutoBtn_Key_Click_RIGHT(GuiCtrlObj, Info) {
    Game.Lists[MainGui["SelectGame"].Text].setting["AutoBtn"]["Key_Click_RIGHT"] := GuiCtrlObj.Value
}
AutoBtn_NoTop(GuiCtrlObj, Info) {
    Game.Lists[MainGui["SelectGame"].Text].setting["AutoBtn"]["NoTop"] := GuiCtrlObj.Value
}
HotKeyMenu(GuiCtrlObj, Item, IsRightClick, X, Y) {
    HotKeyBoxMenu := Menu()
    HotKeyBoxMenu.Add("添加", (ItemName, ItemPos, MyMenu) {
        HotKeyEdit(GuiCtrlObj, Item, true)
    })
    if (Item)
        HotKeyBoxMenu.Add("删除", (ItemName, ItemPos, MyMenu) {
            GuiCtrlObj.Delete(Item)
            Game.Lists[MainGui["SelectGame"].Text].setting["AutoBtn"]["keys"].RemoveAt(Item)
        })
    HotKeyBoxMenu.Show()
}
HotKeyEdit(GuiCtrlObj, Item, isAdd := false) {
    MainGui.Opt("+Disabled")
    HotKeyBoxEdit := Gui("-DPIScale OwnDialogs Owner" MainGui.Hwnd)
    HotKeyBoxEdit.Add("Text", "w100", "热键:")
    HotKeyBoxEdit.Add("Edit", "ys w100 vHotKeyBox_Hotkey", Item ? GuiCtrlObj.GetText(Item, 1) : "")
    HotKeyBoxEdit.Add("Text", "xs w100 Section", "持续时间(毫秒):")
    HotKeyBoxEdit.Add("Edit", "ys w100 Number vHotKeyBox_HoldTime")
    HotKeyBoxEdit.Add("UpDown", "Range0-10000 0x80", Item ? GuiCtrlObj.GetText(Item, 2) : 0)
    HotKeyBoxEdit.Add("Text", "xs w100 Section", "间隔时间(毫秒):")
    HotKeyBoxEdit.Add("Edit", "ys w100 Number vHotKeyBox_Interval")
    HotKeyBoxEdit.Add("UpDown", "Range0-10000 0x80", Item ? GuiCtrlObj.GetText(Item, 3) : 100)
    HotKeyBoxEdit.Add("Text", "xs w100 Section", "次数:")
    HotKeyBoxEdit.Add("Edit", "ys w100 Number vHotKeyBox_Count")
    HotKeyBoxEdit.Add("UpDown", "Range1-1000 0x80", Item ? GuiCtrlObj.GetText(Item, 4) : 1)
    HotKeyBoxEdit.Add("Button", "xs Section vHotKeyBox_Save", "保存")
    HotKeyBoxEdit.Add("Button", "ys vHotKeyBox_Cancel", "取消")
    HotKeyBoxEdit["HotKeyBox_Save"].OnEvent("Click",
        (*) {
        theGame := Game.Lists[MainGui["SelectGame"].Text]
        if not isAdd and Item
            key := theGame.setting["AutoBtn"]["keys"][Item]
        else {
            if (Item)
                Item := GuiCtrlObj.Insert(Item, "+Check")
            else Item := GuiCtrlObj.Add("+Check")
            key := Game.Key(true)
            theGame.setting["AutoBtn"]["keys"].InsertAt(Item, key)
        }
        GuiCtrlObj.Modify(Item, ,
            HotKeyBoxEdit["HotKeyBox_Hotkey"].value,
            HotKeyBoxEdit["HotKeyBox_HoldTime"].value,
            HotKeyBoxEdit["HotKeyBox_Interval"].value,
            HotKeyBoxEdit["HotKeyBox_Count"].value
        )
        key.key := HotKeyBoxEdit["HotKeyBox_Hotkey"].value
        key.holdtime := HotKeyBoxEdit["HotKeyBox_HoldTime"].value
        key.interval := HotKeyBoxEdit["HotKeyBox_Interval"].value
        key.count := HotKeyBoxEdit["HotKeyBox_Count"].value
        WinClose()
    })
    HotKeyBoxEdit["HotKeyBox_Cancel"].OnEvent("Click", (*) => (WinClose()))
    HotKeyBoxEdit.OnEvent("Close", (*) => (MainGui.Opt("-Disabled")))
    HotKeyBoxEdit.Show("AutoSize")
}
HotKeyCheck(GuiCtrlObj, Item, Checked) {
    Game.Lists[MainGui["SelectGame"].Text].setting["AutoBtn"]["keys"][Item].enabled := Checked
}
FollowTarget(GuiCtrlObj, Info) {
    if GuiCtrlObj.Value {
        if not MainGui["FollowTarget_PlayerName"].Value and not MainGui["FollowTarget_TargetName"].Value
            and not MainGui["FollowTarget_TargetBoss"].Value and not MainGui["FollowTarget_TargetList"].Value {
            MsgBox("目标不能为空")
            GuiCtrlObj.Value := false
            return
        }
        else {
            for name in StrSplit(MainGui["FollowTarget_PlayerName"].Value, ",")
                if not InStr(config.data["TP"]["WhiteList"]
                    , Format("<{1}:{2}>", name, StrCrypto(name)), true) {
                    MsgBox("玩家" name "未允许跟随, 请配置跟随白名单")
                    GuiCtrlObj.Value := false
                    return
                }
        }
    }

    for key in ["PlayerName", "TargetName", "TargetBoss", "TargetList", "ScanAll"]
        MainGui["FollowTarget_" key].Enabled := !GuiCtrlObj.Value
    theGame := Game.Lists[MainGui["SelectGame"].Text]
    theGame.setting["FollowTarget"]["On"] := GuiCtrlObj.Value
    theGame.FollowTarget()
}
AutoAim(GuiCtrlObj, Info) {
    if GuiCtrlObj.Value and MainGui["AutoAim_AimRange"].Value == "" {
        MsgBox("配置不能为空")
        GuiCtrlObj.Value := false
        return
    }
    for key in ["AimRange", "TargetBoss", "TargetNormal", "TargetPlant"]
        MainGui["AutoAim_" key].Enabled := !GuiCtrlObj.Value
    theGame := Game.Lists[MainGui["SelectGame"].Text]
    theGame.setting["AutoAim"]["On"] := GuiCtrlObj.Value
    theGame.AutoAim()
}
SpeedUp(GuiCtrlObj, Info) {
    if GuiCtrlObj.Value and MainGui["SpeedUp_SpeedUpRate"].Value == "" {
        MsgBox("配置不能为空")
        GuiCtrlObj.Value := false
        return
    }
    MainGui["SpeedUp_SpeedUpRate"].Enabled := !GuiCtrlObj.Value
    theGame := Game.Lists[MainGui["SelectGame"].Text]
    theGame.setting["SpeedUp"]["On"] := GuiCtrlObj.Value
    theGame.SpeedUp()
}
SomeUiSetChangeEvent(GuiCtrlObj, Info) {
    kv := StrSplit(GuiCtrlObj.Name, "_")
    Game.Lists[MainGui["SelectGame"].Text].setting[kv[1]][kv[2]] := GuiCtrlObj.Value
}

StrCrypto(src, decode := false) {
    static chars := "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789!@#%*_+"
    static charsLen := StrLen(chars)
    key := config.data["Global"]["StrCrypto"]
    keyLen := StrLen(key)
    result := ""
    keyIndex := 1
    Loop Parse src {
        charPos := InStr(chars, A_LoopField, true) - 1
        if (charPos = -1) {
            result .= A_LoopField
            keyIndex := Mod(keyIndex, keyLen) + 1
            Continue
        }
        keyChar := SubStr(key, keyIndex, 1)
        direction := (keyIndex & 1) ? 1 : -1
        shift := Mod(Ord(keyChar), charsLen) * direction
        newPos := Mod(charPos + (decode ? -shift : shift) + charsLen, charsLen)
        result .= SubStr(chars, newPos + 1, 1)
        keyIndex := Mod(keyIndex, keyLen) + 1
    }
    return result
}

; 核心类

; Config Class
class _Config {
    __New(path, data) {
        this.path := path
        this.data := data
    }
    UpdateDllConfig() {
        UpdateConfig("Module::Feature::hideAnimation", this.data["Address"]["Animation"] "|-|-|-")
        UpdateConfig("Module::Feature::autoAttack", this.data["Address"]["Attack"] "|-|-|-")
        UpdateConfig("Module::Feature::breakBlocks", this.data["Address"]["Breakblocks"] "|-|-|-")
        UpdateConfig("Module::Feature::byPass", this.data["Address"]["ByPass"] "|-|-|-")
        UpdateConfig("Module::Feature::clipCam", this.data["Address"]["ClipCam"] "|-|-|-")
        UpdateConfig("Module::Feature::disMount", this.data["Address"]["Dismount"] "|-|-|-")
        UpdateConfig("Module::Feature::lockCam", this.data["Address"]["LockCam"] "|-|-|-")
        UpdateConfig("Module::Feature::unlockMapLimit", this.data["Address"]["Map"] "|-|-|-")
        UpdateConfig("Module::Feature::quickMining", this.data["Address"]["Mining"] "|-|-|-")
        UpdateConfig("Module::Feature::quickMiningGeode", this.data["Address"]["MiningGeode"] "|-|-|-")
        UpdateConfig("Module::Feature::noClip", this.data["Address"]["NoClip"] "|-|-|-")
        UpdateConfig("Module::Feature::unlockZoomLimit", this.data["Address"]["Zoom"] "|-|-|-")
        UpdateConfig("Game::Player::offsets", this.data["Address"]["Player"] "|0x0")
        UpdateConfig("Game::Player::Fish::offsets", this.data["Address"]["Fish"] "|0x68|0x0")
        UpdateConfig("Game::World::offsets", this.data["Address"]["World"] "|0x0")
    }
    Load(path := unset) {
        path := IsSet(path) ? path : this.path
        if ((NewConfigVersion := IniRead(path, "Global", "ConfigVersion", this.data["Global"]["ConfigVersion"])) <
            (OldConfigVersion := this.data["Global"]["ConfigVersion"])) {
            MsgBox(Format("警告: 配置文件非最新版本 {1} => {2}", OldConfigVersion, NewConfigVersion))
        }
        for sect, data in this.data
            for key, value in data
                if key != "AppVersion"
                    this.data[sect][key] := IniRead(path, sect, key, this.data[sect][key])
        this.UpdateDllConfig()
    }
    Save(path := unset) {
        path := IsSet(path) ? path : this.path
        for sect, data in this.data
            for key, value in data
                IniWrite(this.data[sect][key], path, sect, key)
    }
    Update(url) {
        try {
            Download(url, TempPath := A_Temp "\TroveAutoConfig.ini")
            if ((NewConfigVersion := IniRead(TempPath, "Global", "ConfigVersion")) >
                (OldConfigVersion := this.data["Global"]["ConfigVersion"])) {
                NewAppVersion := IniRead(TempPath, "Global", "AppVersion")
                OldAppVersion := this.data["Global"]["AppVersion"]
                this.Load(TempPath)
                MsgBox(Format("配置版本 {1} => {2} 已完成{3}", OldConfigVersion, NewConfigVersion,
                    NewAppVersion > OldAppVersion ? Format("`n警告: 程序本体存在最新版本 {1} => {2}", OldAppVersion, NewAppVersion) : ""))
            }
            else MsgBox("当前已是最新版本")
        }
        catch
            return false
        else return true
    }
}

; Game Class
class Game {
    class Key {
        __New(enabled := false, key := "", holdtime := 0, interval := 500, count := 1) {
            this.enabled := enabled
            this.key := key
            this.holdtime := holdtime
            this.interval := interval
            this.count := count
        }
    }
    static Lists := Map()
    static ActionsMap := Map(
        "钓鱼", "AutoFish",
        "自动按键", "AutoBtn",
    )
    static ScriptAHK := "
    (
        #NoTrayIcon
        InstallKeybdHook
        STOP := false
        ReadProcessMemory := DynaCall("ReadProcessMemory", ["c=uiuituit"])
        WriteProcessMemory := DynaCall("WriteProcessMemory", ["c=uiuituit"])
        ReadMemory(ProcessHandle, Maddress, Readtype := "Int", Len := 4, isNumber := True) {
            Mvalue := Buffer(Len, 0)
            ReadProcessMemory(ProcessHandle, Maddress, Mvalue, Mvalue.Size)
            return isNumber ? NumGet(Mvalue, Readtype) : StrGet(Mvalue, Readtype)
        }
        WriteMemory(ProcessHandle, Maddress, Value, IsBinary := True, Writetype := "Int", Len := 4, IsNumber := True) {
            if (IsBinary) {
                Mvalue := Buffer((StrLen(Value) - 2) // 2)
                loop Mvalue.Size
                    NumPut("UChar", "0x" SubStr(Value, 1 + A_Index * 2, 2), Mvalue, A_Index - 1)
                WriteProcessMemory(ProcessHandle, Maddress, Mvalue, Mvalue.Size)
                return
            }
            Mvalue := Buffer(Len, 0)
            IsNumber ? NumPut(Writetype, Value, Mvalue) : StrPut(Value, Mvalue, Mvalue.Size, Writetype)
            WriteProcessMemory(ProcessHandle, Maddress, Mvalue, Mvalue.Size)
        }
        GetAddressOffset(Maddress, Offset, ProcessHandle) {
            Address := ReadMemory(ProcessHandle, Maddress, "UInt")
            loop Offset.Length - 1
                Address := ReadMemory(ProcessHandle, Address + Offset[A_Index], "UInt")
            return Address + Offset[-1]
        }
        GetPlayerCoordinates(AddressCoordXYZ, AddressCamXYZPer, ProcessHandle) {
            x := ReadMemory(ProcessHandle, AddressCoordXYZ[1], "Float")
            y := ReadMemory(ProcessHandle, AddressCoordXYZ[2], "Float")
            z := ReadMemory(ProcessHandle, AddressCoordXYZ[3], "Float")
            xper := ReadMemory(ProcessHandle, AddressCamXYZPer[1], "Float")
            yper := ReadMemory(ProcessHandle, AddressCamXYZPer[2], "Float")
            zper := ReadMemory(ProcessHandle, AddressCamXYZPer[3], "Float")
            return [x, y, z, xper, yper, zper]
        }
        NatualPress(npbtn, pid, holdtime := 0) {
            ; SetKeyDelay(,Random(66, 122) + holdtime)
            ; try ControlSend("{Blind}" "{" Format("VK{{}:X{}}", GetKeyVK(npbtn)) "}", , "ahk_pid " pid)
            try {
                ControlSend("{Blind}" "{" Format("VK{{}:X{}}", GetKeyVK(npbtn)) " down" "}", , "ahk_pid " pid)
                Sleep(Random(66, 122) + holdtime)
                ControlSend("{Blind}" "{" Format("VK{{}:X{}}", GetKeyVK(npbtn)) " up" "}", , "ahk_pid " pid)
            }
        }
        AutoBtn(Pid, Interval, NoTop) {
            Global STOP, keys
            loop {
                Sleep(500)
            } until (IsSet(keys) or STOP)
            loop {
                Sleep(Interval)
                try {
                    for key in keys["btn"]
                        if (key.enabled and not STOP)
                            Loop key.count {
                                if (STOP)
                                    return
                                if (NoTop and WinGetPID("A") == Pid)
                                    break
                                NatualPress(key.key, Pid, key.holdtime)
                                Sleep(key.interval)
                            }
                    for key in ["LEFT", "RIGHT"]
                        if (keys["Click_" key] and not STOP)
                            if (WinGetPID("A") != Pid)
                                ControlClick(, "ahk_pid " Pid, , key, , "NA")
                            else if ( not NoTop)
                                Click(key)
                }
            } until (STOP)
        }
        AutoFish(Pid, FishKey, Interval, Take_Address, State_Address, ProcessHandle) {
            Global STOP
            Flag := true
            RePush := 0
            loop {
                Sleep(Interval)
                StateFlag := false
                for key in State_Address
                    StateFlag |= ReadMemory(ProcessHandle, key)
                if (!StateFlag) {
                    if (RePush < 10)
                        RePush := RePush + 1
                    Sleep((Random(66, 122) + Interval) * RePush)
                    for key in State_Address
                        StateFlag |= ReadMemory(ProcessHandle, key)
                    if (!StateFlag)
                        NatualPress(FishKey, Pid)
                    Sleep(3000)
                    Flag := true
                }
                TakeFlag := false
                for key in Take_Address
                    TakeFlag |= ReadMemory(ProcessHandle, key)
                if (TakeFlag) {
                    if (Flag) {
                        Sleep(1000)
                        Flag := false
                    }
                    else {
                        NatualPress(FishKey, Pid)
                        RePush := 0
                        Flag := true
                    }
                }
            } until (STOP)
        }
        UseLog(Pid, Name, BaseAddress, ProcessHandle, Interval, Use_R, Use_T) {
            Global STOP
            DirCreate("UseLog")
            AobScan := DynaCall("Module\AobScanFindSig", ["ui=tuiuiaui6ui6i"])
            FileObj := FileOpen("UseLog\" Name " " FormatTime(, "yyyy-MM-dd") ".txt", "a")
            Result := Buffer(1024, 0)
            signature_r := StrSplit(RegExReplace(StrReplace(Use_R, " "), "X|x", "?"), ',')
            signature_t := StrSplit(RegExReplace(StrReplace(Use_T, " "), "X|x", "?"), ',')
            value_r_old := value_t_old := 0
            Loop {
                Sleep(Interval)
                try size := AobScan(Result, Result.Size, Pid, signature_r[2], BaseAddress, 0x7FFFFFFF, 1)
                catch
                    continue
                address_r := size ? Format("0x{{}1:X{}}", NumGet(Result, "UInt") + signature_r[1]) : "0x7FFFFFFF"
                try size := AobScan(Result, Result.Size, Pid, signature_t[2], BaseAddress, 0x7FFFFFFF, 1)
                catch
                    continue
                address_t := size ? Format("0x{{}1:X{}}", NumGet(Result, "UInt") + signature_t[1]) : "0x7FFFFFFF"
                value_r := Integer(ReadMemory(ProcessHandle, address_r, "Double", 8))
                value_t := Integer(ReadMemory(ProcessHandle, address_t, "Double", 8))
                if (value_r < 0 or value_r > 9999 or value_t < 0 or value_t > 9999)
                    continue
                if (value_r_old != value_r || value_t_old != value_t) {
                    FileObj.WriteLine(FormatTime(, "yyyy-MM-dd hh:mm:ss") " R:" value_r " | T:" value_t)
                    FileObj.Read(0)
                    value_r_old := value_r
                    value_t_old := value_t
                }
            } until (STOP)
            FileObj.Close()
        }
        SpeedUp(Pid, ProcessHandle, AddressPlayer, OffsetsCoordXYZ, OffsetsCoordXYZVel, OffsetsCamXYZPer, SpeedUpRate, SpeedUpDelay) {
            global STOP
            loop {
                Sleep(SpeedUpDelay)
                AddressCoordXYZ := [
                    GetAddressOffset(AddressPlayer, OffsetsCoordXYZ[1], ProcessHandle),
                    GetAddressOffset(AddressPlayer, OffsetsCoordXYZ[2], ProcessHandle),
                    GetAddressOffset(AddressPlayer, OffsetsCoordXYZ[3], ProcessHandle)
                ]
                AddressCamXYZPer := [
                    GetAddressOffset(AddressPlayer, OffsetsCamXYZPer[1], ProcessHandle),
                    GetAddressOffset(AddressPlayer, OffsetsCamXYZPer[2], ProcessHandle),
                    GetAddressOffset(AddressPlayer, OffsetsCamXYZPer[3], ProcessHandle)
                ]
                AddressCoordXYZVel := [
                    GetAddressOffset(AddressPlayer, OffsetsCoordXYZVel[1], ProcessHandle),
                    GetAddressOffset(AddressPlayer, OffsetsCoordXYZVel[2], ProcessHandle),
                    GetAddressOffset(AddressPlayer, OffsetsCoordXYZVel[3], ProcessHandle)
                ]
                new_xvel := new_zvel := 0
                new_yvel := 1
                try
                    if (WinGetPID("A") == Pid) {
                        xyz_xyzper := GetPlayerCoordinates(AddressCoordXYZ, AddressCamXYZPer, ProcessHandle)
                        xper := xyz_xyzper[4]
                        zper := xyz_xyzper[6]
                        hrzMagnitude := sqrt(xper ** 2 + zper ** 2)
                        xMagnitude := xper / hrzMagnitude
                        zMagnitude := zper / hrzMagnitude
                        if (GetKeyState("W")) {
                            new_xvel := new_xvel + xMagnitude * SpeedUpRate
                            new_zvel := new_zvel + zMagnitude * SpeedUpRate
                        }
                        if (GetKeyState("A")) {
                            new_xvel := new_xvel + zMagnitude * SpeedUpRate
                            new_zvel := new_zvel - xMagnitude * SpeedUpRate
                        }
                        if (GetKeyState("S")) {
                            new_xvel := new_xvel - xMagnitude * SpeedUpRate
                            new_zvel := new_zvel - zMagnitude * SpeedUpRate
                        }
                        if (GetKeyState("D")) {
                            new_xvel := new_xvel - zMagnitude * SpeedUpRate
                            new_zvel := new_zvel + xMagnitude * SpeedUpRate
                        }
                        if (GetKeyState("Space")) {
                            new_yvel := new_yvel + SpeedUpRate
                        }
                        if (GetKeyState("Shift")) {
                            new_yvel := new_yvel - SpeedUpRate
                        }
                    }
                catch
                    continue
                WriteMemory(ProcessHandle, AddressCoordXYZVel[1], new_xvel, false, "Float")
                WriteMemory(ProcessHandle, AddressCoordXYZVel[2], new_yvel, false, "Float")
                WriteMemory(ProcessHandle, AddressCoordXYZVel[3], new_zvel, false, "Float")
            } until (STOP)
        }
        {1}
    )"
    action := "自动按键"
    running := false
    threads := Map()
    setting := Map(
        "FollowTarget", Map(
            "On", false,
            "PlayerName", "",
            "TargetName", "",
            "TargetBoss", false,
            "TargetList", false,
            "ScanAll", false,
        ),
        "SpeedUp", Map(
            "On", false,
            "SpeedUpRate", 50,
        ),
        "AutoAim", Map(
            "On", false,
            "AimRange", "45",
            "TargetBoss", true,
            "TargetNormal", false,
            "TargetPlant", false,
        ),
        "Features", Map(),
        "Fish", Map(
            "interval", "700",
            "take_address", Map(),
            "state_address", Map(),
        ),
        "AutoBtn", Map(
            "NoTop", false,
            "interval", "1000",
            "keys", [
                Game.Key(false, "Esc", 0, 500),
                Game.Key(false, "1", 0, 500),
                Game.Key(false, "2", 0, 500),
                Game.Key(false, "Q", 0, 500),
                Game.Key(false, "R", 5000, 500),
                Game.Key(false, "T", 5000, 500),
                Game.Key(false, "E", 5000, 500)
            ],
            "Key_Click_LEFT", false,
            "Key_Click_RIGHT", false,
        ),
    )
    __New(id) {
        this.GetBase(id)
        this.name := this.GetName(this.BaseAddress + config.data["Address"]["Player"])
        if (this.name == "")
            return

        for key in ["Animation", "Attack", "Breakblocks", "ByPass", "ClipCam", "Dismount"
            , "Health", "LockCam", "Map", "Mining", "MiningGeode", "NoClip", "UseLog", "Zoom"]
            this.setting["Features"][key] := false
        this.FeaturesAttackFunc := ObjBindMethod(this, "Features_Attack")
        this.FeaturesHealthFunc := ObjBindMethod(this, "Features_Health")

        named := Format("<{1}:{2}>", this.name, StrCrypto(this.name))
        if ( not InStr(config.data["TP"]["WhiteList"], named, true)) {
            if (StrLen(config.data["TP"]["WhiteList"]))
                config.data["TP"]["WhiteList"] .= ","
            config.data["TP"]["WhiteList"] .= named
        }
    }
    static Reset() {
        for Key, Value in Game.Lists
            Value.StopAll()
        Game.Lists.Clear()
    }
    static Refresh() {
        GameNameList := []
        GameIDs_HOLD := Map()
        GameIDs := WinGetList("ahk_exe " config.data["Global"]["GameTitle"])
        for Key, Value in Game.Lists {
            if not WinExist("ahk_id " Value.id) {
                Value.StopAll(true)
            } else {
                GameIDs_HOLD[Value.id] := ""
                GameNameList.Push(Value.Name)
            }
        }
        for key in GameIDs {
            if not GameIDs_HOLD.Has(key) {
                theGame := Game(key)
                if theGame.name != "" {
                    if Game.Lists.Has(theGame.name) {
                        theGame := Game.Lists[theGame.name]
                        theGame.GetBase(key)
                        if theGame.running {
                            switch theGame.action {
                                case "钓鱼":
                                    theGame.AutoFish()
                                default:
                                    theGame.AutoBtn()
                            }
                        }
                        for key, value in theGame.setting["Features"]
                            theGame.Features(key, value)
                        theGame.AutoAim()
                        theGame.FollowTarget()
                        theGame.SpeedUp()
                    }
                    else Game.Lists[theGame.name] := theGame
                    GameNameList.Push(theGame.name)
                }
            }
        }
        return GameNameList
    }
    GetBase(id) {
        this.id := id
        this.pid := WingetPID("ahk_id " id)
        this.ProcessHandle := OpenProcess(this.pid)
        this.BaseAddress := GetProcessBaseAddress(id, -6)
        for key in ["Water", "Lava", "Choco", "Plasma"] {
            this.setting["Fish"]["take_address"][key] := this.GetAddressOffset(
                this.BaseAddress + config.data["Address"]["Fish"], StrSplit(config.data["Address_Offset"]["Fish_" "Take_" key], ",")
            )
            this.setting["Fish"]["state_address"][key] := this.GetAddressOffset(
                this.BaseAddress + config.data["Address"]["Fish"], StrSplit(config.data["Address_Offset"]["Fish_" "State_" key], ",")
            )
        }
    }
    AutoBtn() {
        try this.threads["MainAuto"]["STOP"] := true
        if (this.running)
        {
            this.threads["MainAuto"] := Worker(Format(Game.ScriptAHK, Format('{1}({2},{3},{4})'
                , "AutoBtn", this.pid, this.setting["AutoBtn"]["interval"], this.setting["AutoBtn"]["NoTop"])))
            this.threads["MainAuto"]["keys"] := Map(
                "btn", this.setting["AutoBtn"]["keys"],
                "Click_LEFT", this.setting["AutoBtn"]["Key_Click_LEFT"],
                "Click_RIGHT", this.setting["AutoBtn"]["Key_Click_RIGHT"],
            )
        }
    }
    AutoFish() {
        for key, value in this.setting["Fish"]["take_address"]
            Take_Address .= value ","
        for key, value in this.setting["Fish"]["state_address"]
            State_Address .= value ","
        try this.threads["MainAuto"]["STOP"] := true
        if (this.running)
            this.threads["MainAuto"] := Worker(Format(Game.ScriptAHK, Format('{1}({2},"{3}",{4},[{5}],[{6}],{7})'
                , "AutoFish", this.pid, config.data["Key"]["Fish"], this.setting["Fish"]["interval"], Take_Address, State_Address, this.ProcessHandle)))
    }
    FollowTarget() {
        if (this.setting["FollowTarget"]["On"])
            FunctionOn(this.pid, "FollowTarget",
                Format("{1}|{2}|{3}|{4}|{5}|{6}|{7}"
                    , StrLen(this.setting["FollowTarget"]["PlayerName"]) == 0 ?
                        " " : this.setting["FollowTarget"]["PlayerName"]
                    , (StrLen(this.setting["FollowTarget"]["TargetName"]) == 0 ?
                        " " : this.setting["FollowTarget"]["TargetName"])
                    (this.setting["FollowTarget"]["TargetList"] ? config.data["AutoAim"]["TargetList"] : "")
                    , this.setting["FollowTarget"]["TargetList"] ? config.data["AutoAim"]["NoTargetList"] : " "
                    , this.setting["FollowTarget"]["TargetBoss"]
                    , this.setting["FollowTarget"]["ScanAll"]
                    , this.setting["SpeedUp"]["SpeedUpRate"]
                    , config.data["TP"]["Delay"])
                , false)
        else
            FunctionOff(this.pid, "FollowTarget")
    }
    AutoAim() {
        if (this.setting["AutoAim"]["On"])
            FunctionOn(this.pid, "AutoAim", Format("{1}|{2}|{3}|{4}|{5}|{6}|{7}|{8}"
                , this.setting["AutoAim"]["TargetBoss"]
                , this.setting["AutoAim"]["TargetPlant"]
                , this.setting["AutoAim"]["TargetNormal"]
                , config.data["AutoAim"]["TargetList"]
                , config.data["AutoAim"]["NoTargetList"]
                , this.setting["AutoAim"]["AimRange"]
                , config.data["AutoAim"]["Delay"]), false)
        else
            FunctionOff(this.pid, "AutoAim")
    }
    SpeedUp() {
        OffsetsCoordXYZ := Format("[{1}],[{2}],[{3}]"
            , config.data["Address_Offset"]["Player_Coord_X"]
            , config.data["Address_Offset"]["Player_Coord_Y"]
            , config.data["Address_Offset"]["Player_Coord_Z"]
        )
        OffsetsCoordXYZVel := Format("[{1}],[{2}],[{3}]"
            , config.data["Address_Offset"]["Player_Coord_XVel"]
            , config.data["Address_Offset"]["Player_Coord_YVel"]
            , config.data["Address_Offset"]["Player_Coord_ZVel"]
        )
        OffsetsCamXYZPer := Format("[{1}],[{2}],[{3}]"
            , config.data["Address_Offset"]["Player_Cam_XPer"]
            , config.data["Address_Offset"]["Player_Cam_YPer"]
            , config.data["Address_Offset"]["Player_Cam_ZPer"]
        )
        try this.threads["SpeedUp"]["STOP"] := true
        if (this.setting["SpeedUp"]["On"])
            this.threads["SpeedUp"] := Worker(Format(Game.ScriptAHK
                , Format('{1}({2},{3},{4},[{5}],[{6}],[{7}],{8},{9})'
                    , "SpeedUp", this.pid, this.ProcessHandle
                    , this.BaseAddress + config.data["Address"]["Player"]
                    , OffsetsCoordXYZ, OffsetsCoordXYZVel, OffsetsCamXYZPer
                    , this.setting["SpeedUp"]["SpeedUpRate"], config.data["SpeedUp"]["Delay"])))
    }
    StopAll(keepStatus := false) {
        running := this.running
        this.running := false
        for key in this.setting["Features"]
            this.Features(key, false)
        for key in this.threads
            try this.threads[key]["STOP"] := true
        CloseHandle(this.ProcessHandle)
        if keepStatus
            this.running := running
        else
            FunctionOff(this.pid, 0)
    }
    Features_Attack() {
        this.WriteMemory(
            this.BaseAddress + config.data["Address"]["Attack"],
            StrSplit(config.data["Features_Change"]["Attack"], ",")[1]
        )
        Sleep(300)
        this.WriteMemory(
            this.BaseAddress + config.data["Address"]["Attack"],
            StrSplit(config.data["Features_Change"]["Attack"], ",")[2]
        )
    }
    Features_Health() {
        if ( not this.ReadMemory(
            this.GetAddressOffset(
                this.BaseAddress + config.data["Address"]["Player"]
                , StrSplit(config.data["Address_Offset"]["Player_Health"], ","))
            , "Double", 8)) {
            this.NatualPress("E")
            Sleep(5000)
        }
    }
    Features(Name, Value) {
        switch Name {
            case "Attack":
                SetTimer(this.FeaturesAttackFunc, Value ? config.data["AttackTime"]["Value"] : 0)
            case "Health":
                SetTimer(this.FeaturesHealthFunc, Value ? config.data["HealthTime"]["Value"] : 0)
                return
            case "NoClip":
                FunctionOn(this.pid, "SetNoClip", String(Value), true)
                return
            case "UseLog":
                try this.threads["Log"]["STOP"] := true
                if (Value) {
                    this.threads["Log"] := Worker(Format(Game.ScriptAHK, Format('{1}({2},"{3}",{4},{5},{6},"{7}","{8}")'
                        , "UseLog", this.pid, this.name, this.BaseAddress, this.ProcessHandle, config.data["UseLogTime"]["Value"], config.data["Address_Offset_Signature"]["Use_R"], config.data["Address_Offset_Signature"]["Use_T"])))
                }
                return
        }
        this.WriteMemory(
            this.BaseAddress + config.data["Address"][Name],
            StrSplit(config.data["Features_Change"][Name], ",")[Value ? 1 : 2]
        )
    }
    GetName(Address) {
        Address := this.GetAddressOffset(Address, StrSplit(config.data["Address_Offset"]["Name"], ","))
        return this.ReadMemory(Address, "utf-8", 16, false)
    }
    GetAddressOffset(Maddress, Offset) {
        Address := this.ReadMemory(Maddress, "UInt")
        loop Offset.Length - 1
            Address := this.ReadMemory(Address + Offset[A_Index], "UInt")
        return Address + Offset[-1]
    }
    ReadMemory(Maddress, Readtype := "Int", Len := 4, isNumber := True) {
        Mvalue := Buffer(Len, 0)
        ReadProcessMemory(this.ProcessHandle, Maddress, Mvalue, Mvalue.Size)
        return isNumber ? NumGet(Mvalue, Readtype) : StrGet(Mvalue, Readtype)
    }
    WriteMemory(Maddress, Value, IsBinary := True, Writetype := "Int", Len := 4, IsNumber := True) {
        if (IsBinary) {
            Mvalue := Buffer((StrLen(Value) - 2) // 2)
            loop Mvalue.Size
                NumPut("UChar", "0x" SubStr(Value, 1 + A_Index * 2, 2), Mvalue, A_Index - 1)
            WriteProcessMemory(this.ProcessHandle, Maddress, Mvalue, Mvalue.Size)
            return
        }
        Mvalue := Buffer(Len, 0)
        IsNumber ? NumPut(Writetype, Value, Mvalue) : StrPut(Value, Mvalue, Mvalue.Size, Writetype)
        WriteProcessMemory(this.ProcessHandle, Maddress, Mvalue, Mvalue.Size)
    }
    NatualPress(npbtn, holdtime := 0) {
        try {
            ControlSend("{Blind}" "{" Format("VK{:X}", GetKeyVK(npbtn)) " down" "}", , "ahk_pid " this.pid)
            Sleep(Random(66, 122) + holdtime)
            ControlSend("{Blind}" "{" Format("VK{:X}", GetKeyVK(npbtn)) " up" "}", , "ahk_pid " this.pid)
        }
    }
}

Reset()
MainGui.Show()
Persistent

#HotIf WinActive("Trove辅助")
::wwssadadbaba::
{
    if (InStr(A_Clipboard, "whosyourdaddy")) {
        MainGui["FollowTarget_ScanAll"].Visible := true
        config.data["Global"]["Cheat"] := "whosyourdaddy"
        Save()
        MsgBox("轻度使用！")
    }
    else
        MsgBox("谁是你爸爸( •̀ ω •́ )y")
}
#HotIf