;@Ahk2Exe-UpdateManifest 2
;@Ahk2Exe-SetName TroveAuto
;@Ahk2Exe-SetProductVersion 2.2.8
;@Ahk2Exe-SetCopyright GPL-3.0 license
;@Ahk2Exe-SetLanguage Chinese_PRC
;@Ahk2Exe-SetMainIcon TroveAuto.ico
;@Ahk2Exe-SetDescription Trove自动脚本`, 解放双手
#SingleInstance Prompt

SetTitleMatchMode("RegEx")

config := _Config(
    "config.ini",
    Map(
        "Global", Map(
            "GameTitle", "Trove.exe",
            "GamePath", "",
            "ConfigVersion", "20240702180000",
            "AppVersion", "20240702180000",
            "Source", "https://github.com/Angels-D/TroveAuto/",
            "Mirror", "https://github.moeyy.xyz/",
        ),
        "RestartTime", Map("Value", "5000",),
        "Key", Map(
            "Fish", "f",
        ),
        "Address", Map(
            "Animation", "0x73F805",
            "Attack", "0xAF6D48",
            "Breakblocks", "0x820E43",
            "ClipCam", "0xA331CA",
            "Dismount", "0x32D61E",
            "Fish", "0x1080634",
            "LockCam", "0xA1C8D5",
            "Map", "0x83368D",
            "Mining", "0xA744D8",
            "MiningGeode", "0xAAA427",
            "Name", "0x8D6168",
            "Zoom", "0xA31146",
        ),
        "Address_Offset", Map(
            "Name", "0x0,0x10,0x0",
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
            "Attack", "0xF0,0xF1",
            "Dismount", "0xEB,0x74",
            "Mining", "0xF0,0xF1",
            "MiningGeode", "0xF0,0xF1",
            "Breakblocks", "0x01,0x00",
            "Map", "0xEB,0x77",
            "Zoom", "0x57,0x5F",
            "ClipCam", "0x909090,0x0F2901",
            "LockCam", "0xEB,0x74",
            "Animation", "0x4C,0x44",
        ),
        "Address_Offset_Signature", Map(
            "Attack", "1,DF F1 DD D8 72 1F",
            "Dismount", "0,74 XX 8B 07 8B CF 6A 00 6A 00 FF 50",
            "Mining", "1,DF F1 DD D8 72 61",
            "MiningGeode", "1,DF F1 DD D8 72 35 8D",
            "Breakblocks", "3,80 7F XX 00 0F 84 XX XX XX XX 8B 4B 08 E8 XX XX XX XX FF 75 0C 8B 4D 10 8B F0 FF 75 08 8B 45 14 83 EC 0C 8B 3E 8B D4 6A 01 89 0A 8B CE 89 42 04 8B 45 18",
            "Map", "0,77 XX B8 XX XX XX XX F3 0F 10 08 F3 0F 11 89 XX XX XX XX 8B 89",
            "Zoom", "3,F3 0F 11 5F 2C",
            "ClipCam", "0,0F 29 01 C7 41 34 00 00 00 00 0F",
            "LockCam", "0,74 05 8B 01 FF 50 0C 8B E5",
            "Animation", "3,F3 0F 11 44 24 24 F3 0F 58 84 24 80 00 00 00 50 F3 0F 11 43 24 E8 XX XX XX XX 8D 44 24 34 50",
            "Fish", "0,10 14 XX XX 00 00 00 00 FF 00 00 00 00",
            "Name", "-9,FF 70 1C FF 70 18 8D 45 B0",
        )
    )
)
config.Load()

MainGui := Gui("-DPIScale", "Trove辅助")
MainGui.Add("Tab3", "vTab", ["主页", "面板", "设置", "关于"]) ; 监控,注册账号

; 主页内容
MainGui["Tab"].UseTab("主页")
MainGui.Add("Text", "x+50 y+30", "游戏路径:")
MainGui.Add("Edit", "w200 vGamePath", config.data["Global"]["GamePath"])
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
        新: 强烈推荐使用<a href="https://github.com/Sly0511/RenewedTroveTools/">RenewedTroveTools</a>
        工具管理你的Mod和CFG文件, 还有装备推荐、模拟加点、模组开发管理、模组下载等功能
    )"
)

; 面板内容
MainGui["Tab"].UseTab("面板")
MainGui.Add("Button", "x+40 y+20 w50 Section vResetBtn", "重置")
MainGui.Add("Button", "ys w50 vRefreshBtn", "刷新")
MainGui.Add("Button", "ys x+50 vStartBtn", "启动")
MainGui.Add("Text", "xs w70 Section", "玩家列表:")
MainGui.Add("DropDownList", "ys w130 vSelectGame")
MainGui.Add("Text", "xs w70 Section", "脚本动作:")
MainGui.Add("DropDownList", "ys w130 vSelectAction", ["自动按键", "钓鱼"])
MainGui.Add("GroupBox", "xs-20 y+20 w290 r9 Section", "自动按键配置区")
MainGui.Add("Text", "xp+10 yp+30 Section", "频率(毫秒):")
MainGui.Add("Edit", "ys w100 vInterval")
MainGui.Add("ListView", "xs w250 Section NoSortHdr Checked -Multi vHotKeyBox", ["热键", "持续时间", "间隔时间", "次数"])
MainGui.Add("CheckBox", "xs Section w130 vAutoBtn_Key_Click_LEFT", "自动左击")
MainGui.Add("CheckBox", "ys w130 vAutoBtn_Key_Click_RIGHT", "自动右击")
MainGui.Add("CheckBox", "xs Section w200 vAutoBtn_NoTop", "前台时禁用")
MainGui.Add("GroupBox", "xs-10 ys+40 w290 r6 Section", "功能区")
for key, value in Map(
    "Attack", "自动攻击",
    "Dismount", "保持骑乘",
    "Mining", "快速挖矿",
    "MiningGeode", "快速挖矿(晶洞)",
    "Breakblocks", "打破障碍",
    "Map", "地图放大",
    "Zoom", "视野放大",
    "ClipCam", "视角遮挡",
    "LockCam", "视角固定",
    "Animation", "隐藏特效",
)
    MainGui.Add("CheckBox", (Mod(A_Index, 2) ? ((A_Index == 1 ? "xp+10 yp+30" : "xs") " Section") : "ys") " w130 v" key, value)
MainGui.Add("GroupBox", "xs-10 ys+70 w290 r3 Section", "崩溃自启          实验性功能")
MainGui.Add("CheckBox", "xp+80 yp vAutoRestart")
MainGui.Add("Text", "xs+10 ys+30 Section", "账号:")
MainGui.Add("Edit", "ys w200 vAccount")
MainGui.Add("Text", "xs Section", "密码:")
MainGui.Add("Edit", "ys w200 vPassword")
MainGui.Add("Text", "xs+40 ys+50 cRed", "任何脚本都有风险, 请慎用!")

; 设置内容
MainGui["Tab"].UseTab("设置")
MainGui.Add("Text", "x+50 y+50 w100 Section", "游戏标题:")
MainGui.Add("Edit", "ys w100 vGameTitle", config.data["Global"]["GameTitle"])
for key, value in Map(
    "Name", "账号",
    "Fish", "钓鱼",
    "Attack", "自动攻击",
    "Dismount", "保持骑乘",
    "Mining", "快速挖矿",
    "MiningGeode", "快速挖矿(晶洞)",
    "Breakblocks", "打破障碍",
    "Map", "地图放大",
    "Zoom", "视野放大",
    "ClipCam", "视角遮挡",
    "LockCam", "视角固定",
    "Animation", "隐藏特效",
) {
    MainGui.Add("Text", "xs w100 Section", value "地址:")
    MainGui.Add("Edit", "ys w100 v" key "Address", config.data["Address"][key])
}
MainGui.Add("Text", "xs w100 Section", "钓鱼按键:")
MainGui.Add("HotKey", "ys w100 vFishKey", config.data["Key"]["Fish"])
MainGui.Add("Text", "xs w100 Section", "自启扫描(毫秒):")
MainGui.Add("Edit", "ys w100 vRestartTime", config.data["RestartTime"]["Value"])
MainGui.Add("Text", "xs w100 Section", "镜像源:")
MainGui.Add("Edit", "ys w100 vMirror", config.data["Global"]["Mirror"])
MainGui.Add("Button", "xs w40 Section vSaveBtn", "保存")
MainGui.Add("Button", "ys w75 vUpdateFromInternetBtn", "联网更新")
MainGui.Add("Button", "ys w75 vUpdateFromLocalBtn", "本地更新")

; 关于内容
MainGui["Tab"].UseTab("关于")
MainGui.Add("ActiveX", "w150 h150 y+100 Center",
    "mshtml:<img src='https://cdn.jsdelivr.net/gh/Angels-D/Angels-D.github.io/medias/avatar.jpg' style='width:150px;'/>")
MainGui.Add("Text", , "作者: AnglesD 游戏ID: D_FairyTail")
MainGui.Add("Text", "cRed", "本软件完全开源免费, 仅供学习使用！")
MainGui.Add("Link", , "
    (
        博客: `n<a href="https://Angels-D.github.io/">https://Angels-D.github.io/</a>`n
        源码: `n<a href="https://github.com/Angels-D/TroveAuto">https://github.com/Angels-D/TroveAuto</a>`n
        公会推广: `n<a target="_blank" href="https://qm.qq.com/cgi-bin/qm/qr?k=vOppyOHhd2WOrA6jJ9Yd-qi8EZQvHjnk&jump_from=webapi">AshesWithoutFire[群号:423933990]</a>
    )"
)
MainGui.Add("Button", "y+30 w200 h60 vDownloadBtn", "最新版脚本下载")

; 绑定交互
MainGui.OnEvent("Close", Close, -1)
MainGui["GamePathBtn"].OnEvent("Click", GetGamePath)
MainGui["GameStartBtn"].OnEvent("Click", GameStart)
MainGui["ModsPathBtn"].OnEvent("Click", OpenModsPath)
MainGui["ModCfgsPathBtn"].OnEvent("Click", OpenModCfgsPath)
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
MainGui["AutoRestart"].OnEvent("Click", AutoRestart)
MainGui["Account"].OnEvent("Change", Account)
MainGui["Password"].OnEvent("Change", Password)
for key in ["Attack", "Dismount", "Mining", "MiningGeode"
    , "Breakblocks", "Map", "Zoom", "ClipCam", "LockCam", "Animation"]
    MainGui[key].OnEvent("Click", Features)

; 托盘图标
A_TrayMenu.Delete()
A_TrayMenu.Add("显示", (ItemName, ItemPos, MyMenu) => (MainGui.Show()))
A_TrayMenu.Add("重新启动", (ItemName, ItemPos, MyMenu) => (Reload()))
A_TrayMenu.Add("退出", (ItemName, ItemPos, MyMenu) => (ExitApp()))

; 交互函数
Close(thisGui) {
    Result := MsgBox("是: 关闭脚本`n否: 最小化到托盘", , 3)
    switch Result {
        case "Yes":
            ExitApp
        case "No":
        default:
            return true
    }
}
GetGamePath(GuiCtrlObj, Info) {
    try {
        GamePath := WinGetProcessPath("ahk_exe i)" config.data["Global"]["GameTitle"] "|Glyph.*")
        RegExMatch(GamePath, "i)^(.*?Trove)", &GamePath)
        MainGui["GamePath"].Value := GamePath[0]
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
Reset(GuiCtrlObj := unset, Info := unset) {
    Game.Reset()
    UIReset()
}
Refresh(GuiCtrlObj := unset, Info := unset) {
    Game.Refresh()
    UIReset()
}
UIReset() {
    for key in ["Attack", "Dismount", "Mining", "MiningGeode"
        , "Breakblocks", "Map", "Zoom", "ClipCam", "LockCam", "Animation"
        , "AutoBtn_Key_Click_LEFT", "AutoBtn_Key_Click_RIGHT", "AutoBtn_NoTop", "HotKeyBox"
        , "Interval", "SelectAction", "StartBtn", "AutoRestart", "Account", "Password"]
        MainGui[key].Enabled := false
    for key in ["Attack", "Dismount", "Mining", "MiningGeode"
        , "Breakblocks", "Map", "Zoom", "ClipCam", "LockCam", "Animation"
        , "AutoBtn_Key_Click_LEFT", "AutoBtn_Key_Click_RIGHT", "AutoBtn_NoTop"
        , "Interval", "SelectAction", "AutoRestart", "Account", "Password"]
        try MainGui[key].Value := ""
        catch
            MainGui[key].Value := 0
    MainGui["HotKeyBox"].Delete()
}
Start(GuiCtrlObj, Info) {
    if (Game.Lists[MainGui["SelectGame"].Text].running) {
        MainGui["StartBtn"].Text := "启动"
        for key in ["SelectAction", "Interval"]
            MainGui[key].Enabled := true
        Game.Lists[MainGui["SelectGame"].Text].running := false
        switch MainGui["SelectAction"].Text {
            case "钓鱼":
                Game.Lists[MainGui["SelectGame"].Text].AutoFish()
            default:
                for key in ["HotKeyBox", "AutoBtn_Key_Click_LEFT", "AutoBtn_Key_Click_RIGHT", "AutoBtn_NoTop"]
                    MainGui[key].Enabled := true
                Game.Lists[MainGui["SelectGame"].Text].AutoBtn()
        }
    }
    else {
        MainGui["StartBtn"].Text := "关闭"
        for key in ["SelectAction", "Interval"]
            MainGui[key].Enabled := false
        Game.Lists[MainGui["SelectGame"].Text].running := true
        switch MainGui["SelectAction"].Text {
            case "钓鱼":
                Game.Lists[MainGui["SelectGame"].Text].AutoFish()
            default:
                for key in ["HotKeyBox", "AutoBtn_Key_Click_LEFT", "AutoBtn_Key_Click_RIGHT", "AutoBtn_NoTop"]
                    MainGui[key].Enabled := false
                Game.Lists[MainGui["SelectGame"].Text].AutoBtn()
        }
    }
}
Save(GuiCtrlObj := unset, Info := unset) {
    for sect, data in config.data {
        if (sect == "Address_Offset" or sect == "Features_Change" or sect == "Address_Offset_Signature")
            Continue
        for key in data
            try config.data[sect][key] := MainGui[key sect].Value
            catch
                try config.data[sect][key] := MainGui[key].Value
    }
    config.Save()
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
    if not WinExist("Trove") {
        MsgBox("请先启动游戏, 再进行扫描")
        return
    }
    shell := ComObject("WScript.Shell")
    for key, value in config.data["Address"] {
        signature := StrSplit(config.data["Address_Offset_Signature"][key], ',')
        exec := shell.Exec("PtrFind.exe " signature[2])
        value := Format("0x{1:X}", exec.StdOut.ReadAll() + signature[1])
        MainGui[key "Address"].Text := value
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
    Game.Lists[MainGui["SelectGame"].Text].action := GuiCtrlObj.Text
    MainGui["AutoRestart"].Enabled := true
    MainGui["Account"].Value := Game.Lists[MainGui["SelectGame"].Text].setting["Account"]
    MainGui["Password"].Value := Game.Lists[MainGui["SelectGame"].Text].setting["Password"]
    MainGui["Account"].Enabled := MainGui["Password"].Enabled := !Game.Lists[MainGui["SelectGame"].Text].setting["AutoRestart"]
    MainGui["AutoRestart"].Value := Game.Lists[MainGui["SelectGame"].Text].setting["AutoRestart"]
    for key in ["Attack", "Dismount", "Mining", "MiningGeode"
        , "Breakblocks", "Map", "Zoom", "ClipCam", "LockCam", "Animation"] {
        MainGui[key].Enabled := true
        MainGui[key].Value := Game.Lists[MainGui["SelectGame"].Text].setting["Features"][key]
    }
    for key in ["HotKeyBox", "AutoBtn_Key_Click_LEFT", "AutoBtn_Key_Click_RIGHT", "AutoBtn_NoTop"]
        MainGui[key].Enabled := false
    MainGui["HotKeyBox"].Delete()
    for key in Game.Lists[MainGui["SelectGame"].Text].setting["AutoBtn"]["keys"]
        MainGui["HotKeyBox"].Add(key.enabled ? "+Check" : "-Check", key.key, key.holdtime, key.interval, key.count)
    for key in ["Key_Click_LEFT", "Key_Click_RIGHT", "NoTop"]
        MainGui["AutoBtn_" key].Value := Game.Lists[MainGui["SelectGame"].Text].setting["AutoBtn"][key]
    switch GuiCtrlObj.Text {
        case "自动按键":
            MainGui["Interval"].Value := Game.Lists[MainGui["SelectGame"].Text].setting["AutoBtn"]["interval"]
            if (!Game.Lists[MainGui["SelectGame"].Text].running)
                for key in ["HotKeyBox", "AutoBtn_Key_Click_LEFT", "AutoBtn_Key_Click_RIGHT", "AutoBtn_NoTop"]
                    MainGui[key].Enabled := true
        case "钓鱼":
            MainGui["Interval"].Value := Game.Lists[MainGui["SelectGame"].Text].setting["Fish"]["interval"]
    }
}
Features(GuiCtrlObj, Info) {
    Game.Lists[MainGui["SelectGame"].Text].setting["Features"][GuiCtrlObj.Name] := GuiCtrlObj.Value
    Game.Lists[MainGui["SelectGame"].Text].Features(GuiCtrlObj.Name, GuiCtrlObj.Value)
}
Interval(GuiCtrlObj, Info) {
    switch MainGui["SelectAction"].Text {
        case "自动按键":
            Game.Lists[MainGui["SelectGame"].Text].setting["AutoBtn"]["interval"] := GuiCtrlObj.value
        case "钓鱼":
            Game.Lists[MainGui["SelectGame"].Text].setting["Fish"]["interval"] := GuiCtrlObj.value
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
            if not isAdd and Item
                key := Game.Lists[MainGui["SelectGame"].Text].setting["AutoBtn"]["keys"][Item]
            else {
                if (Item)
                    Item := GuiCtrlObj.Insert(Item, "+Check")
                else Item := GuiCtrlObj.Add("+Check")
                    key := Game.Key(true)
                    Game.Lists[MainGui["SelectGame"].Text].setting["AutoBtn"]["keys"].InsertAt(Item, key)
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
AutoRestart(GuiCtrlObj, Info) {
    if GuiCtrlObj.Value and not MainGui["Account"].Value or not MainGui["Password"] {
        MsgBox("账号密码不能为空")
        GuiCtrlObj.Value := false
        return
    }
    MainGui["Account"].Enabled := MainGui["Password"].Enabled := !GuiCtrlObj.Value
    Game.Lists[MainGui["SelectGame"].Text].setting["AutoRestart"] := GuiCtrlObj.Value
    SetTimer(Game.Lists[MainGui["SelectGame"].Text].AutoRestartFunc, GuiCtrlObj.Value ? config.data["RestartTime"]["Value"] : false)
}
Account(GuiCtrlObj, Info) {
    Game.Lists[MainGui["SelectGame"].Text].setting["Account"] := GuiCtrlObj.Value
}
Password(GuiCtrlObj, Info) {
    Game.Lists[MainGui["SelectGame"].Text].setting["Password"] := GuiCtrlObj.Value
}

; DLL封装
CloseHandle := DynaCall("CloseHandle", ["c=ui"])
OpenProcess := DynaCall("OpenProcess", ["ui=uicui", 3], 0x38, 0)
ReadProcessMemory := DynaCall("ReadProcessMemory", ["c=uiuituit"])
WriteProcessMemory := DynaCall("WriteProcessMemory", ["c=uiuituit"])

; 核心类

; Config Class
class _Config {
    __New(path, data) {
        this.path := path
        this.data := data
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
        STOP := false
        ReadProcessMemory := DynaCall("ReadProcessMemory",["c=uiuituit"])
        ReadMemoryINT(MADDRESS,PID,ProcessHandle) {
            MVALUE := Buffer(4,0)
            ReadProcessMemory(ProcessHandle,MADDRESS,MVALUE,4)
            return NumGet(Mvalue,"Int")
        }
        NatualPress(npbtn,pid,holdtime := 0) {
            SetKeyDelay(,Random(66, 122) + holdtime)
            ControlSend("{Blind}" "{" npbtn "}",, "ahk_pid " pid)
        }
        AutoBtn(Pid,Interval,NoTop) {
            Global STOP, keys
            loop{
                Sleep(500)
            }until(IsSet(keys) or STOP)
            loop{
                Sleep(Interval)
                try {
                    for key in keys["btn"]
                        if (key.enabled)
                            Loop key.count {
                                if(STOP)
                                    return
                                if(NoTop and WinGetPID("A") == Pid)
                                    break
                                NatualPress(key.key, Pid, key.holdtime)
                                Sleep(key.interval)
                            }
                    for key in ["LEFT", "RIGHT"]
                        if (keys["Click_" key] and not STOP)
                            if (WinGetPID("A") != Pid)
                                ControlClick(, "ahk_pid " Pid, , key, , "NA")
                            else if(not NoTop)
                                Click(key)
                }
            }until(STOP)
        }
        AutoFish(Pid,FishKey,Interval,Take_Address,State_Address,ProcessHandle){
            Global STOP
            Flag := true
            loop{
                Sleep(Interval)
                TakeFlag := false
                StateFlag := false
                for key in Take_Address
                    TakeFlag |= ReadMemoryINT(key,Pid,ProcessHandle)
                for key in State_Address
                    StateFlag |= ReadMemoryINT(key,Pid,ProcessHandle)
                if(!StateFlag) {
                    NatualPress(FishKey,Pid)
                    Flag := true
                }
                if (TakeFlag) {
                    if (Flag) {
                        Sleep(1000)
                        Flag := false
                    }
                    else {
                        NatualPress(FishKey,Pid)
                        Flag := true
                    }
                }
            }until(STOP)
        }
        {1}
    )"
    action := "自动按键"
    running := false
    setting := Map(
        "Account", "",
        "Password", "",
        "AutoRestart", false,
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
                Game.Key(false, "q", 0, 500),
                Game.Key(false, "r", 5000, 500),
                Game.Key(false, "t", 5000, 500),
                Game.Key(false, "e", 5000, 500)
            ],
            "Key_Click_LEFT", false,
            "Key_Click_RIGHT", false,
        ),
    )
    __New(id) {
        this.GetBase(id)
        this.name := this.GetName(config.data["Address"]["Name"])
        for key in ["Attack", "Dismount", "Mining", "MiningGeode"
            , "Breakblocks", "Map", "Zoom", "ClipCam", "LockCam", "Animation",]
            this.setting["Features"][key] := false
        this.AutoRestartFunc := ObjBindMethod(this, "AutoRestart")
        this.FeaturesAttackFunc := ObjBindMethod(this, "Features_Attack")
    }
    static Reset() {
        for Key, Value in Game.Lists
            Value.StopAll()
        Game.Lists.Clear()
        Game.Refresh()
    }
    static Refresh() {
        LOADING := false
        GameIDs_HOLD := Map()
        MainGui["SelectGame"].Delete()
        GameIDs := WinGetList("ahk_exe " config.data["Global"]["GameTitle"])
        for Key, Value in Game.Lists.Clone() {
            if not WinExist("ahk_id " Value.id) {
                Game.Lists[Key].StopAll(true)
            } else {
                GameIDs_HOLD[Value.id] := ""
                MainGui["SelectGame"].Add([Value.Name])
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
                        for key in ["Attack", "Dismount", "Mining", "MiningGeode"
                            , "Breakblocks", "Map", "Zoom", "ClipCam", "LockCam", "Animation",]
                            theGame.Features(key, theGame.setting["Features"][key])
                    }
                    else Game.Lists[theGame.name] := theGame
                    MainGui["SelectGame"].Add([theGame.name])
                }
                else LOADING := true
            }
        }
        return LOADING
    }
    GetBase(id) {
        this.id := id
        this.pid := WingetPID("ahk_id " id)
        this.ProcessHandle := OpenProcess(this.pid)
        this.BaseaAddress := this.getProcessBaseAddress(id)
        for key in ["Water", "Lava", "Choco", "Plasma"] {
            this.setting["Fish"]["take_address"][key] := this.GetAddressOffset(
                config.data["Address"]["Fish"], StrSplit(config.data["Address_Offset"]["Fish_" "Take_" key], ",")
            )
            this.setting["Fish"]["state_address"][key] := this.GetAddressOffset(
                config.data["Address"]["Fish"], StrSplit(config.data["Address_Offset"]["Fish_" "State_" key], ",")
            )
        }
    }
    AutoBtn() {
        try
            this.thread["STOP"] := true
        if (this.running)
        {
            this.thread := Worker(Format(Game.ScriptAHK, Format('{1}({2},{3},{4})'
                , "AutoBtn", this.pid, this.setting["AutoBtn"]["interval"], this.setting["AutoBtn"]["NoTop"])))
            this.thread["keys"] := Map(
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
        try this.thread["STOP"] := true
        if (this.running)
            this.thread := Worker(Format(Game.ScriptAHK, Format('{1}({2},"{3}",{4},[{5}],[{6}],{7})'
                , "AutoFish", this.pid, config.data["Key"]["Fish"], this.setting["Fish"]["interval"], Take_Address, State_Address, this.ProcessHandle)))
    }
    AutoRestart() {
        if not WinExist("ahk_id " this.id) {
            if Game.Refresh()
                return
            try WinActivate("Glyph")
            catch {
                GameStart()
                Sleep(10000)
            }
            try {
                if WinWaitActive("登录 Glyph", , 3) or WinWaitActive("Glyph", , 15) {
                    WinSetAlwaysOnTop(1, "Glyph")
                    WinGetPos(&X, &Y, &W, &H, "Glyph")
                    if ( not WinWaitActive("登录 Glyph", , 0.5)
                        and not ImageSearch(&OutputVarX, &OutputVarY, 0, 0, W, H, "image/select1.png")
                        and not ImageSearch(&OutputVarX, &OutputVarY, 0, 0, W, H, "image/select2.png")
                        and ImageSearch(&OutputVarX, &OutputVarY, 0, 0, W, H, "image/select3.png")
                        or ImageSearch(&OutputVarX, &OutputVarY, 0, 0, W, H, "image/select4.png")) {
                        ControlClick("x" OutputVarX " y" OutputVarY, "Glyph", , , , "NA")
                        ImageSearch(&OutputVarX, &OutputVarY, 0, 0, W, H, "*2 image/logout1.png")
                            or ImageSearch(&OutputVarX, &OutputVarY, 0, 0, W, H, "*2 image/logout2.png")
                        ControlClick("x" OutputVarX " y" OutputVarY, "Glyph", , , , "NA")
                        Sleep(3000)
                    }
                    if ( not WinWaitActive("登录 Glyph", , 3)
                        and ImageSearch(&OutputVarX, &OutputVarY, 0, 0, W, H, "image/select1.png")
                        or ImageSearch(&OutputVarX, &OutputVarY, 0, 0, W, H, "image/select2.png")) {
                        ImageSearch(&OutputVarX, &OutputVarY, 0, 0, W, H, "image/start1.png")
                            or ImageSearch(&OutputVarX, &OutputVarY, 0, 0, W, H, "image/start2.png")
                            or ImageSearch(&OutputVarX, &OutputVarY, 0, 0, W, H, "image/start3.png")
                        ControlClick("x" OutputVarX " y" OutputVarY, "Glyph", , , , "NA")
                        Sleep(3000)
                    }
                    WinGetPos(&X, &Y, &W, &H, "登录 Glyph")
                    if (ImageSearch(&OutputVarX, &OutputVarY, 0, 0, W, H, "image/login1.png")
                        or ImageSearch(&OutputVarX, &OutputVarY, 0, 0, W, H, "image/login2.png")) {
                        SetKeyDelay(10, 20)
                        ControlSend(this.setting["Account"] "{Tab}" this.setting["Password"], , "登录 Glyph")
                        ControlClick("x" OutputVarX " y" OutputVarY, "登录 Glyph", , , , "NA")
                        Sleep(30000)
                    }
                }
            }
        }
    }
    StopAll(keepStatus := false) {
        running := this.running
        this.running := false
        try this.thread["STOP"] := true
        CloseHandle(this.ProcessHandle)
        if keepStatus
            this.running := running
    }
    Features_Attack() {
        this.WriteMemory(
            config.data["Address"]["Attack"],
            StrSplit(config.data["Features_Change"]["Attack"], ",")[1]
        )
        Sleep(300)
        this.WriteMemory(
            config.data["Address"]["Attack"],
            StrSplit(config.data["Features_Change"]["Attack"], ",")[2]
        )
    }
    Features(Name, Value) {
        if (Name == "Attack")
            SetTimer(this.FeaturesAttackFunc, Value ? 1000 : 0)

        this.WriteMemory(
            config.data["Address"][Name],
            StrSplit(config.data["Features_Change"][Name], ",")[Value ? 1 : 2]
        )
    }
    GetName(Address) {
        Address := this.GetAddressOffset(Address, StrSplit(config.data["Address_Offset"]["Name"], ","))
        return this.ReadMemory(Address, "Str")
    }
    GetAddressOffset(Address, Offset) {
        Address := this.ReadMemory(this.BaseaAddress + Address, "Int")
        loop Offset.Length - 1
            Address := this.ReadMemory(Address + Offset[A_Index], "Int")
        return Address + Offset[-1]
    }
    getProcessBaseAddress(id) {
        return DllCall(A_PtrSize = 4 ? "GetWindowLong" : "GetWindowLongPtr", "Ptr", id, "Int", -6, "Int64")
    }
    ReadMemory(Maddress, Readtype, Len := unset) {
        if (Readtype == "Int") {
            Len := IsSet(Len) ? Len : 4
            Mvalue := Buffer(Len, 0)
            ReadProcessMemory(this.ProcessHandle, Maddress, Mvalue, Len)
            return NumGet(Mvalue, "Int")
        }
        else if (Readtype == "Str") {
            Len := IsSet(Len) ? Len : 15
            Mvalue := Buffer(Len, 0)
            ReadProcessMemory(this.ProcessHandle, Maddress, Mvalue, Len)
            return StrGet(Mvalue, "utf-8")
        }
        throw ValueError("错误的读取类型", -1, Readtype)
    }
    WriteMemory(Address, Value) {
        Len := (StrLen(Value) - 2) // 2
        Mvalue := Buffer(Len)
        loop Len
            NumPut("UChar", "0x" SubStr(Value, 1 + A_Index * 2, 2), Mvalue, A_Index - 1)
        WriteProcessMemory(this.ProcessHandle, this.BaseaAddress + Address, Mvalue, Len)
    }
}

Reset()
MainGui.Show()
Persistent