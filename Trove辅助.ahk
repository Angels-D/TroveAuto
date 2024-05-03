;@Ahk2Exe-SetLanguage Chinese_PRC
;@Ahk2Exe-SetMainIcon Trove辅助.ico
;@Ahk2Exe-UpdateManifest 2
#SingleInstance Prompt
; #NoTrayIcon
SetTitleMatchMode("RegEx")

config := _Config(
    "config.ini",
    Map("Global",Map(
            "GameTitle","Trove.exe",
            "GamePath","",
            "ConfigVersion","20240503103000",
            "AppVersion","20240503103000",
        ),
        "HoldTime",Map("Value","3000",),
        "RestartTime",Map("Value","5000",),
        "Key",Map(
            "PressR","r",
            "PressT","t",
            "PressE","e",
            "Fish","f",
        ),
        "Address",Map(
            "Attack","0xB3B188",
            "Dismount","0x33231E",
            "Mining","0x9D74A8",
            "MiningGeode","0x836497",
            "Breakblocks","0x9599F3",
            "Map","0x9EA88D",
            "Zoom","0x937216",
            "ClipCam","0x93929A",
            "LockCam","0xB40405",
            "Animation","0x73CB75",
            "Fish","0x107EB3C",
            "Name","0x10863E0",
        ),
        "Address_Offset",Map(
            "Name","0x10,0x0",
            "Fish_Take_Water","0x68,0xE4,0x3C4",
            "Fish_Take_Lava","0x68,0xE4,0x898",
            "Fish_Take_Choco","0x68,0xE4,0x62C",
            "Fish_Take_Plasma","0x68,0xE4,0xB00",
            "Fish_State_Water","0x68,0xF4,0xBA0",
            "Fish_State_Lava","0x68,0xF4,0x938",
            "Fish_State_Choco","0x68,0xF4,0xE08",
            "Fish_State_Plasma","0x68,0xF4,0x6CC",
        ),
        "Features_Change",Map(
            "Attack","0xF0,0xF1",
            "Dismount","0xEB,0x74",
            "Mining","0xF0,0xF1",
            "MiningGeode","0xF0,0xF1",
            "Breakblocks","0x01,0x00",
            "Map","0xEB,0x77",
            "Zoom","0x57,0x5F",
            "ClipCam","0x909090,0x0F,0x29,0x01",
            "LockCam","0xEB,0x74",
            "Animation","0x4C,0x44",  
        ),
    )
)
config.Load()

MainGui := Gui("-DPIScale","Trove辅助")
MainGui.Add("Tab3","vTab",["主页","面板","设置","关于"]) ; 监控,注册账号

; 主页内容
MainGui["Tab"].UseTab("主页")
MainGui.Add("Text","x+50","游戏路径:")
MainGui.Add("Edit","w200 vGamePath",config.data["Global"]["GamePath"])
MainGui.Add("Button","Section vGamePathBtn","获取游戏路径")
MainGui.Add("Button","ys vGameStartBtn","启动游戏")
MainGui.Add("Text","xs w200","说明: 当前使用Steam打开游戏会强制绑定账号, 直接使用官方启动器即可跳过绑定")
MainGui.Add("Button","w200 vModsPathBtn","Mods文件夹")
MainGui.Add("Link","w200","
    (
        说明: 本游戏支持模组, 可通过各公会群和Steam创意工坊等渠道下载, Mod制作或下载可使用
        <a href="https://github.com/DazoTrove/TroveTools.NET/">TroveTools.NET</a>等工具
    )"
)
MainGui.Add("Button","w200 vModCfgsPathBtn","ModCfgs文件夹")
MainGui.Add("Link","w200",Format("说明: Cfgs用于保存某些Mod的配置信息,一般位于<a href=`"file:///{1}\Trove\ModCfgs\`">%AppData%\Trove\ModCfgs\</a>中",A_AppData))
MainGui.Add("Text","w200","Mod使用教程: 后缀为.tmod的文件存放在Mods文件夹, 后缀为.cfg的文件存放在ModCfgs文件夹, 放置后重启游戏生效")
MainGui.Add("Link","w200","附: 官方邮箱<a href=`"mailto:support@gamigo.com`">support@gamigo.com</a>(通过此邮箱询问交易问题、账号问题等内容,注意使用英文描述")

; 面板内容
MainGui["Tab"].UseTab("面板")
MainGui.Add("Button","x+40 y+20 w50 Section vResetBtn","重置")
MainGui.Add("Button","ys w50 vRefreshBtn","刷新")
MainGui.Add("Button","ys x+50 vStartBtn","启动")
MainGui.Add("Text","xs w70 Section","玩家列表:")
MainGui.Add("DropDownList","ys w130 vSelectGame")
MainGui.Add("Text","xs w70 Section","脚本动作:")
MainGui.Add("DropDownList","ys w130 vSelectAction",["自动按键","钓鱼"])
MainGui.Add("GroupBox", "xs-20 y+20 w290 r6 Section", "自动按键配置区")
MainGui.Add("Text","xp+10 yp+30 Section","频率(毫秒):")
MainGui.Add("Edit","ys w100 vInterval")
MainGui.Add("Text","xs w70 Section","按键设置:")
MainGui.Add("Hotkey","ys w40 vAutoBtn_Key_1")
MainGui.Add("Hotkey","ys w40 vAutoBtn_Key_2")
MainGui.Add("Hotkey","ys w40 vAutoBtn_Key_3")
MainGui.Add("CheckBox","xs Section w130 vAutoBtn_Key_Click_LEFT","自动左击")
MainGui.Add("CheckBox","ys w130 vAutoBtn_Key_Click_RIGHT","自动右击")
MainGui.Add("CheckBox","xs Section w130 vAutoBtn_Key_PressR","自动物品栏1")
MainGui.Add("CheckBox","ys w130 vAutoBtn_Key_PressT","自动物品栏2")
MainGui.Add("CheckBox","xs Section w130 vAutoBtn_Key_PressE","自动拾取")
MainGui.Add("GroupBox", "xs-10 ys+50 w290 r6 Section", "功能区")
for key,value in Map(
        "Attack","自动攻击",
        "Dismount","保持骑乘",
        "Mining","快速挖矿",
        "MiningGeode","快速挖矿(晶洞)",
        "Breakblocks","打破障碍",
        "Map","地图放大",
        "Zoom","视野放大",
        "ClipCam","视角遮挡",
        "LockCam","视角固定",
        "Animation","隐藏特效",
    )
    MainGui.Add("CheckBox",(Mod(A_Index,2)?((A_Index==1?"xp+10 yp+30":"xs") " Section"):"ys") " w130 v" key,value)
MainGui.Add("GroupBox", "xs-10 ys+70 w290 r3 Section", "崩溃自启          实验性功能")
MainGui.Add("CheckBox","xp+80 yp vAutoRestart")
MainGui.Add("Text","xs+10 ys+30 Section","账号:")
MainGui.Add("Edit","ys w200 vAccount")
MainGui.Add("Text","xs Section","密码:")
MainGui.Add("Edit","ys w200 vPassword")
MainGui.Add("Text","xs+40 ys+50 cRed","任何脚本都有风险, 请慎用!")

; 设置内容
MainGui["Tab"].UseTab("设置")
MainGui.Add("Text","x+50 w100 Section","游戏标题:")
MainGui.Add("Edit","ys w100 vGameTitle",config.data["Global"]["GameTitle"])
for key,value in Map(
        "Name","账号",
        "Fish","钓鱼",
        "Attack","自动攻击",
        "Dismount","保持骑乘",
        "Mining","快速挖矿",
        "MiningGeode","快速挖矿(晶洞)",
        "Breakblocks","打破障碍",
        "Map","地图放大",
        "Zoom","视野放大",
        "ClipCam","视角遮挡",
        "LockCam","视角固定",
        "Animation","隐藏特效",
    ){
        MainGui.Add("Text","xs w100 Section",value "地址:")
        MainGui.Add("Edit","ys w100 v" key "Address",config.data["Address"][key])
    }
MainGui.Add("Text","xs w100 Section","交互按键:")
MainGui.Add("HotKey","ys w100 vPressEKey",config.data["Key"]["PressE"])
MainGui.Add("Text","xs w100 Section","物品1/2按键:")
MainGui.Add("HotKey","ys w40 vPressRKey",config.data["Key"]["PressR"])
MainGui.Add("HotKey","ys w40 vPressTKey",config.data["Key"]["PressT"])
MainGui.Add("Text","xs w100 Section","钓鱼按键:")
MainGui.Add("HotKey","ys w100 vFishKey",config.data["Key"]["Fish"])
MainGui.Add("Text","xs w100 Section","长按时间(毫秒):")
MainGui.Add("Edit","ys w100 vHoldTime",config.data["HoldTime"]["Value"])
MainGui.Add("Text","xs w100 Section","自启扫描(毫秒):")
MainGui.Add("Edit","ys w100 vRestartTime",config.data["RestartTime"]["Value"])
MainGui.Add("Button","xs w70 Section vSaveBtn","保存")
MainGui.Add("Button","ys w130 vUpdateBtn","获取更新")

; 关于内容
MainGui["Tab"].UseTab("关于")
MainGui.Add("ActiveX","w100 h100 y+50 Center",
    "mshtml:<img src='https://cdn.jsdelivr.net/gh/Angels-D/Angels-D.github.io/medias/avatar.jpg' style='width:100px;'/>")
MainGui.Add("Text",,"作者: AnglesD 游戏ID: D_FairyTail")
MainGui.Add("Text","cRed","本软件完全开源免费, 仅供学习使用！")
MainGui.Add("Link",,"
    (
        博客: `n<a href="https://Angels-D.github.io/">https://Angels-D.github.io/</a>`n
        源码: `n<a href="https://github.com/Angels-D/TroveAuto">https://github.com/Angels-D/TroveAuto</a>`n
        公会推广: `n<a target="_blank" href="https://qm.qq.com/cgi-bin/qm/qr?k=vOppyOHhd2WOrA6jJ9Yd-qi8EZQvHjnk&jump_from=webapi">AshesWithoutFire[群号:423933990]</a>
    )"
)
MainGui.Add("Button","y+30 w200 h60 vDownloadBtn","最新版脚本下载")

; 绑定交互
MainGui["GamePathBtn"].OnEvent("Click",GetGamePath)
MainGui["GameStartBtn"].OnEvent("Click",GameStart)
MainGui["ModsPathBtn"].OnEvent("Click",OpenModsPath)
MainGui["ModCfgsPathBtn"].OnEvent("Click",OpenModCfgsPath)
MainGui["ResetBtn"].OnEvent("Click",Reset)
MainGui["RefreshBtn"].OnEvent("Click",Refresh)
MainGui["StartBtn"].OnEvent("Click",Start)
MainGui["SaveBtn"].OnEvent("Click",Save)
MainGui["UpdateBtn"].OnEvent("Click",Update)
MainGui["DownloadBtn"].OnEvent("Click",DownloadExe)
MainGui["SelectGame"].OnEvent("Change",SelectGame)
MainGui["SelectAction"].OnEvent("Change",SelectAction)
MainGui["Interval"].OnEvent("Change",Interval)
MainGui["AutoBtn_Key_1"].OnEvent("Change",AutoBtn_Key_1)
MainGui["AutoBtn_Key_2"].OnEvent("Change",AutoBtn_Key_2)
MainGui["AutoBtn_Key_3"].OnEvent("Change",AutoBtn_Key_3)
MainGui["AutoBtn_Key_Click_LEFT"].OnEvent("Click",AutoBtn_Key_Click_LEFT)
MainGui["AutoBtn_Key_Click_RIGHT"].OnEvent("Click",AutoBtn_Key_Click_RIGHT)
MainGui["AutoBtn_Key_PressR"].OnEvent("Click",AutoBtn_Key_PressR)
MainGui["AutoBtn_Key_PressT"].OnEvent("Click",AutoBtn_Key_PressT)
MainGui["AutoBtn_Key_PressE"].OnEvent("Click",AutoBtn_Key_PressE)
MainGui["AutoRestart"].OnEvent("Click",AutoRestart)
MainGui["Account"].OnEvent("Change",Account)
MainGui["Password"].OnEvent("Change",Password)
for key in ["Attack","Dismount","Mining","MiningGeode"
        ,"Breakblocks","Map","Zoom","ClipCam","LockCam","Animation"]
    MainGui[key].OnEvent("Click",Features)

Reset()
MainGui.Show()

; 交互函数
GetGamePath(GuiCtrlObj, Info){
    try{
        GamePath := WinGetProcessPath("ahk_exe i)" config.data["Global"]["GameTitle"] "|Glyph.*")
        RegExMatch(GamePath, "i)^(.*?Trove)", &GamePath)
        MainGui["GamePath"].Value := GamePath[0]
    }
    Catch
        MsgBox("请运行游戏或登陆器以检测路径")
}
GameStart(GuiCtrlObj := unset, Info := unset){
    try Run(Format("{1}\GlyphClient.exe",config.data["Global"]["GamePath"]))
    Catch
        MsgBox("游戏启动失败, 请检查游戏路径")
}
OpenModsPath(GuiCtrlObj, Info){
    try Run(Format("explore {1}\Games\Trove\Live\mods",config.data["Global"]["GamePath"]))
    Catch
        MsgBox("Mods文件夹打开失败, 请检查游戏路径")
}
OpenModCfgsPath(GuiCtrlObj, Info){
    try Run(Format("explore {1}\Trove\ModCfgs\",A_AppData))
    Catch
        MsgBox("ModCfgs文件夹打开失败, 请检查文件夹是否存在")
}
Reset(GuiCtrlObj := unset, Info := unset){
    Game.Reset()
    for key in ["Attack","Dismount","Mining","MiningGeode"
        ,"Breakblocks","Map","Zoom","ClipCam","LockCam","Animation"
        ,"AutoBtn_Key_1","AutoBtn_Key_2","AutoBtn_Key_3"
        ,"AutoBtn_Key_Click_LEFT","AutoBtn_Key_Click_RIGHT","AutoBtn_Key_PressR","AutoBtn_Key_PressT","AutoBtn_Key_PressE"
        ,"Interval","SelectAction","StartBtn","AutoRestart","Account","Password"]
        MainGui[key].Enabled := false
    for key in ["Attack","Dismount","Mining","MiningGeode"
        ,"Breakblocks","Map","Zoom","ClipCam","LockCam","Animation"
        ,"AutoBtn_Key_1","AutoBtn_Key_2","AutoBtn_Key_3"
        ,"AutoBtn_Key_Click_LEFT","AutoBtn_Key_Click_RIGHT","AutoBtn_Key_PressR","AutoBtn_Key_PressT","AutoBtn_Key_PressE"
        ,"Interval","SelectAction","SelectGame","AutoRestart","Account","Password"]
        try MainGui[key].Value := ""
        Catch
            MainGui[key].Value := 0
}
Refresh(GuiCtrlObj := unset, Info := unset){
    Game.Refresh()
}
Start(GuiCtrlObj, Info){
    if(Game.Lists[MainGui["SelectGame"].Text].running){
        Func := Game.Lists[MainGui["SelectGame"].Text].Func
        MainGui["StartBtn"].Text := "启动"
        for key in ["SelectAction","Interval"]
            MainGui[key].Enabled := true
        Game.Lists[MainGui["SelectGame"].Text].running := false
        switch MainGui["SelectAction"].Text {
        Case "钓鱼":
            Func()
        Default:
            for key in ["AutoBtn_Key_1","AutoBtn_Key_2","AutoBtn_Key_3","AutoBtn_Key_Click_LEFT","AutoBtn_Key_Click_RIGHT","AutoBtn_Key_PressR","AutoBtn_Key_PressT","AutoBtn_Key_PressE"]
                MainGui[key].Enabled := true
            SetTimer(Func,false)
        }
    }
    else{
        Func := Game.Lists[MainGui["SelectGame"].Text].Func := ObjBindMethod(Game.Lists[MainGui["SelectGame"].Text], Game.ActionsMap[MainGui["SelectAction"].Text])
        MainGui["StartBtn"].Text := "关闭"
        for key in ["SelectAction","Interval"]
            MainGui[key].Enabled := false
        Game.Lists[MainGui["SelectGame"].Text].running := true
        switch MainGui["SelectAction"].Text {
        Case "钓鱼":
            Func()
        Default:
            for key in ["AutoBtn_Key_1","AutoBtn_Key_2","AutoBtn_Key_3","AutoBtn_Key_Click_LEFT","AutoBtn_Key_Click_RIGHT","AutoBtn_Key_PressR","AutoBtn_Key_PressT","AutoBtn_Key_PressE"]
                MainGui[key].Enabled := false
            SetTimer(Func,MainGui["Interval"].Value)
        }
    }
}
Save(GuiCtrlObj, Info){
    for sect,data in config.data{
        if(sect == "Address_Offset" or sect == "Features_Change")
            Continue
        for key in data
            try config.data[sect][key] := MainGui[key sect].Value
            Catch
                try config.data[sect][key] := MainGui[key].Value
    }
    config.Save()
}
Update(GuiCtrlObj, Info){
    Source := "https://github.com/Angels-D/TroveAuto/releases/latest/download/config.ini"
    Mirror := "https://gh.api.99988866.xyz/" Source
    if(config.Update(Mirror) Or config.Update(Source)){
        MainGui.Add("Text","x+50 w100 Section","游戏标题:")
        MainGui["GameTitle"].Text := config.data["Global"]["GameTitle"]
        for sect in ["Address","Key"]
            for key,value in config.data[sect]
                MainGui[key sect].Text := config.data[sect][key]
    }
    else MsgBox("更新失败, 请检查网络连接")

}
DownloadExe(GuiCtrlObj, Info){
    Source := "https://github.com/Angels-D/TroveAuto/releases/latest/download/TroveAuto.zip"
    Mirror := "https://gh.api.99988866.xyz/" Source
    try Download(Mirror,"Trove辅助" A_Now ".zip")
    catch
        try Download(Source,"Trove辅助" A_Now ".zip")
        catch 
            MsgBox("下载失败, 请检查网络连接")
        else MsgBox("应用下载成功, 请打开最新版本")
    else MsgBox("应用下载成功, 请打开最新版本")
}
SelectGame(GuiCtrlObj, Info){
    MainGui["SelectAction"].Text := Game.Lists[GuiCtrlObj.Text].action
    MainGui["StartBtn"].Text := Game.Lists[GuiCtrlObj.Text].running ? "关闭":"启动"
    for key in ["SelectAction","Interval"]
        MainGui[key].Enabled := !Game.Lists[GuiCtrlObj.Text].running
    MainGui["StartBtn"].Enabled := true
    SelectAction(MainGui["SelectAction"])
}
SelectAction(GuiCtrlObj, Info := unset){
    Game.Lists[MainGui["SelectGame"].Text].action := GuiCtrlObj.Text
    MainGui["AutoRestart"].Enabled := true
    MainGui["Account"].Value := Game.Lists[MainGui["SelectGame"].Text].setting["Account"]
    MainGui["Password"].Value := Game.Lists[MainGui["SelectGame"].Text].setting["Password"]
    MainGui["Account"].Enabled := MainGui["Password"].Enabled := !Game.Lists[MainGui["SelectGame"].Text].setting["AutoRestart"]
    MainGui["AutoRestart"].Value := Game.Lists[MainGui["SelectGame"].Text].setting["AutoRestart"]
    for key in ["Attack","Dismount","Mining","MiningGeode"
        ,"Breakblocks","Map","Zoom","ClipCam","LockCam","Animation"]{
        MainGui[key].Enabled := true
        MainGui[key].Value := Game.Lists[MainGui["SelectGame"].Text].setting["Features"][key]
    }
    for key in ["AutoBtn_Key_1","AutoBtn_Key_2","AutoBtn_Key_3","AutoBtn_Key_Click_LEFT","AutoBtn_Key_Click_RIGHT","AutoBtn_Key_PressR","AutoBtn_Key_PressT","AutoBtn_Key_PressE"]
        MainGui[key].Enabled := false
    for key in ["Key_1","Key_2","Key_3","Key_Click_LEFT","Key_Click_RIGHT","Key_PressR","Key_PressT","Key_PressE"]
        MainGui["AutoBtn_" key].Value := Game.Lists[MainGui["SelectGame"].Text].setting["AutoBtn"][key]
    Switch GuiCtrlObj.Text {
    Case "自动按键":
        MainGui["Interval"].Value := Game.Lists[MainGui["SelectGame"].Text].setting["AutoBtn"]["interval"]
        if(!Game.Lists[MainGui["SelectGame"].Text].running) 
            for key in ["AutoBtn_Key_1","AutoBtn_Key_2","AutoBtn_Key_3","AutoBtn_Key_Click_LEFT","AutoBtn_Key_Click_RIGHT","AutoBtn_Key_PressR","AutoBtn_Key_PressT","AutoBtn_Key_PressE"]
                MainGui[key].Enabled := true
    Case "钓鱼":
        MainGui["Interval"].Value := Game.Lists[MainGui["SelectGame"].Text].setting["Fish"]["interval"]
    }
}
Features(GuiCtrlObj, Info){
    Game.Lists[MainGui["SelectGame"].Text].setting["Features"][GuiCtrlObj.Name] := GuiCtrlObj.Value
    Switch GuiCtrlObj.Name {
    Case "ClipCam":
        if(GuiCtrlObj.Value)
            Game.Lists[MainGui["SelectGame"].Text].WriteMemory(
                config.data["Address"][GuiCtrlObj.Name],
                StrSplit(config.data["Features_Change"][GuiCtrlObj.Name],",")[1],3
            )
        else
            Loop 3
                Game.Lists[MainGui["SelectGame"].Text].WriteMemory(
                    config.data["Address"][GuiCtrlObj.Name] + A_Index - 1,
                    StrSplit(config.data["Features_Change"][GuiCtrlObj.Name],",")[A_Index + 1],1
                ) 
    Default:
        Game.Lists[MainGui["SelectGame"].Text].WriteMemory(
            config.data["Address"][GuiCtrlObj.Name],
            StrSplit(config.data["Features_Change"][GuiCtrlObj.Name],",")[GuiCtrlObj.Value?1:2],1
        )    
    }
}
Interval(GuiCtrlObj, Info){
    Switch MainGui["SelectAction"].Text{
    Case "自动按键":
        Game.Lists[MainGui["SelectGame"].Text].setting["AutoBtn"]["interval"] := GuiCtrlObj.value
    Case "钓鱼":
        Game.Lists[MainGui["SelectGame"].Text].setting["Fish"]["interval"] := GuiCtrlObj.value
    } 
}
AutoBtn_Key_1(GuiCtrlObj, Info){
    Game.Lists[MainGui["SelectGame"].Text].setting["AutoBtn"]["Key_1"] := GuiCtrlObj.Value
}
AutoBtn_Key_2(GuiCtrlObj, Info){
    Game.Lists[MainGui["SelectGame"].Text].setting["AutoBtn"]["Key_2"] := GuiCtrlObj.Value
}
AutoBtn_Key_3(GuiCtrlObj, Info){
    Game.Lists[MainGui["SelectGame"].Text].setting["AutoBtn"]["Key_3"] := GuiCtrlObj.Value
}
AutoBtn_Key_Click_LEFT(GuiCtrlObj, Info){
    Game.Lists[MainGui["SelectGame"].Text].setting["AutoBtn"]["Key_Click_LEFT"] := GuiCtrlObj.Value
}
AutoBtn_Key_Click_RIGHT(GuiCtrlObj, Info){
    Game.Lists[MainGui["SelectGame"].Text].setting["AutoBtn"]["Key_Click_RIGHT"] := GuiCtrlObj.Value
}
AutoBtn_Key_PressR(GuiCtrlObj, Info){
    Game.Lists[MainGui["SelectGame"].Text].setting["AutoBtn"]["Key_PressR"] := GuiCtrlObj.Value
}
AutoBtn_Key_PressT(GuiCtrlObj, Info){
    Game.Lists[MainGui["SelectGame"].Text].setting["AutoBtn"]["Key_PressT"] := GuiCtrlObj.Value
}
AutoBtn_Key_PressE(GuiCtrlObj, Info){
    Game.Lists[MainGui["SelectGame"].Text].setting["AutoBtn"]["Key_PressE"] := GuiCtrlObj.Value
}
AutoRestart(GuiCtrlObj, Info){
    MainGui["Account"].Enabled := MainGui["Password"].Enabled := !GuiCtrlObj.Value
    Game.Lists[MainGui["SelectGame"].Text].setting["AutoRestart"] := GuiCtrlObj.Value
    SetTimer(Game.Lists[MainGui["SelectGame"].Text].AutoRestartFunc,GuiCtrlObj.Value?config.data["RestartTime"]["Value"]:false)
}
Account(GuiCtrlObj, Info){
    Game.Lists[MainGui["SelectGame"].Text].setting["Account"] := GuiCtrlObj.Value
}
Password(GuiCtrlObj, Info){
    Game.Lists[MainGui["SelectGame"].Text].setting["Password"] := GuiCtrlObj.Value
}

; 核心类

; Config Class
class _Config{
    __New(path,data){
        this.path := path
        this.data := data
    }
    Load(path := unset){
        path := IsSet(path) ? path : this.path
        if((NewConfigVersion := IniRead(path,"Global","ConfigVersion",this.data["Global"]["ConfigVersion"])) < 
            (OldConfigVersion := this.data["Global"]["ConfigVersion"])){
            MsgBox(Format("警告: 配置文件非最新版本 {1} => {2}",OldConfigVersion,NewConfigVersion))
        }
        for sect,data in this.data
            for key,value in data
                this.data[sect][key] := IniRead(
                    path,sect,key,this.data[sect][key])
    }
    Save(path := unset){
        path := IsSet(path) ? path : this.path
        for sect,data in this.data
            for key,value in data
                IniWrite(this.data[sect][key],path,sect,key)
    }
    Update(url){
        try {
            Download(url,TempPath := A_Temp "\TroveAutoConfig.ini")
            if((NewConfigVersion := IniRead(TempPath,"Global","ConfigVersion")) > 
                (OldConfigVersion := this.data["Global"]["ConfigVersion"])){
                NewAppVersion := IniRead(TempPath,"Global","AppVersion")
                OldAppVersion := this.data["Global"]["AppVersion"]
                this.Load(TempPath)
                MsgBox(Format("配置版本 {1} => {2} 已完成{3}",OldConfigVersion,NewConfigVersion,
                    NewAppVersion > OldAppVersion?Format("`n警告: 程序本体存在最新版本 {1} => {2}",OldAppVersion,NewAppVersion):""))
            }
            else MsgBox("当前已是最新版本")
        }
        Catch
            Return false
        Else Return true
    }
}

; Game Class
class Game{
    static Lists := Map()
    static ActionsMap := Map(
        "钓鱼","AutoFish",
        "自动按键","AutoBtn",
    )
    action := "自动按键"
    running := false
    setting := Map(
        "Account","",
        "Password","",
        "AutoRestart",false,
        "Features",Map(),
        "Fish",Map(
            "interval","700",
            "take_address",Map(),
            "state_address",Map(),
        ),
        "AutoBtn",Map(
            "interval","10000",
            "Key_1","End",
            "Key_2","",
            "Key_3","",
            "Key_Click_LEFT",false,
            "Key_Click_RIGHT",false,
            "Key_PressR",false,
            "Key_PressT",false,
            "Key_PressE",false,
        ),
    )
    __New(id){
        this.GetBase(id)
        this.name := this.GetName(config.data["Address"]["Name"])
        for key in ["Attack","Dismount","Mining","MiningGeode"
            ,"Breakblocks","Map","Zoom","ClipCam","LockCam","Animation",]
            this.setting["Features"][key] := false
        this.AutoRestartFunc := ObjBindMethod(this, "AutoRestart")
        this.Func := ObjBindMethod(this, "AutoBtn")
    }
    GetBase(id){
        this.id := id
        this.pid := WingetPID("ahk_id " id)
        this.BaseaAddress := this.getProcessBaseAddress(id)
        for key in ["Water","Lava","Choco","Plasma"] {
            this.setting["Fish"]["take_address"][key] := this.GetAddressOffset(
                config.data["Address"]["Fish"],StrSplit(config.data["Address_Offset"]["Fish_" "Take_" key],",")
            )
            this.setting["Fish"]["state_address"][key] := this.GetAddressOffset(
                config.data["Address"]["Fish"],StrSplit(config.data["Address_Offset"]["Fish_" "State_" key],",")
            )
        }
    }
    AutoBtn(){
        try{
            for key in [1,2,3]
                if(this.setting["AutoBtn"]["Key_" key])
                    this.NatualPress(this.setting["AutoBtn"]["Key_" key])
            for key in ["LEFT","RIGHT"]
                if(this.setting["AutoBtn"]["Key_Click_" key])
                    if(WinGetPID("A") != this.pid)
                        ControlClick(,"ahk_pid " this.pid,,key,,"NA")
                    else Click(key)
            for key in ["PressR","PressT","PressE"]
                if(this.setting["AutoBtn"]["Key_" key])
                    this.NatualPress(config.data["Key"][key],config.data["HoldTime"]["Value"])
        }
    }
    AutoFish(){
        for key,value in this.setting["Fish"]["take_address"]
            Take_Address .= value ","
        for key,value in this.setting["Fish"]["state_address"]
            State_Address .= value ","
        ThreadAHK := Format("
        (
            #NoTrayIcon
            ReadMemoryINT(MADDRESS,PID) {
                MVALUE := Buffer(4,0)
                ProcessHandle := DllCall("OpenProcess", "Int", 24, "Char", 0, "UInt", PID, "UInt")
                DllCall("ReadProcessMemory", "UInt", ProcessHandle, "Ptr", MADDRESS, "Ptr", MVALUE, "UInt", 4)
                Return NumGet(Mvalue,"Int")
            }
            NatualPress(npbtn,pid) {
                ControlSend("{" npbtn " down}",, "ahk_pid " pid)
                Sleep(Random(66, 122))
                ControlSend("{" npbtn " up}",, "ahk_pid " pid)
                Sleep(Random(66, 122))
            }
            Running(Pid,FishKey,Interval,Take_Address,State_Address){
                Flag := true
                Loop{
                    Sleep(Interval)
                    TakeFlag := false
                    StateFlag := false
                    for key in Take_Address
                        TakeFlag |= ReadMemoryINT(key,Pid)
                    for key in State_Address
                        StateFlag |= ReadMemoryINT(key,Pid)
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
                }
            }
            Running({1},"{2}",{3},[{4}],[{5}])
        )"
            ,this.pid,config.data["Key"]["Fish"],this.setting["Fish"]["interval"],Take_Address,State_Address)
        try this.thread.ahkTerminate()
        if (this.running)
            this.thread := NewThread(ThreadAHK)
    }
    AutoRestart(){
        if not WinExist("ahk_id " this.id){
            if Game.Refresh()
                return
            try WinActivate("Glyph")
            catch{
                GameStart()
                Sleep(10)
            }
            try{
                if WinWaitActive("登录 Glyph",,3) or WinWaitActive("Glyph",,15) {
                    WinSetAlwaysOnTop(1,"Glyph")
                    WinGetPos(&X, &Y, &W, &H, "Glyph")
                    if(not WinWaitActive("登录 Glyph",,0.5) 
                        and not ImageSearch(&OutputVarX, &OutputVarY, 0, 0, W, H, "image/select1.png") 
                        and ImageSearch(&OutputVarX, &OutputVarY, 0, 0, W, H, "image/select2.png")){
                        ControlClick("x" OutputVarX " y" OutputVarY,"Glyph",,,,"NA")
                        ImageSearch(&OutputVarX, &OutputVarY, 0, 0, W, H, "image/logout.png")
                        ControlClick("x" OutputVarX " y" OutputVarY,"Glyph",,,,"NA")
                        Sleep(3)
                    }
                    if(not WinWaitActive("登录 Glyph",,3) and ImageSearch(&OutputVarX, &OutputVarY, 0, 0, W, H, "image/select1.png")){
                        ImageSearch(&OutputVarX, &OutputVarY, 0, 0, W, H, "image/start1.png") 
                        or ImageSearch(&OutputVarX, &OutputVarY, 0, 0, W, H, "image/start2.png")
                        ControlClick("x" OutputVarX " y" OutputVarY,"Glyph",,,,"NA")
                        Sleep(3)
                    }
                    WinGetPos(&X, &Y, &W, &H, "登录 Glyph")
                    if(ImageSearch(&OutputVarX, &OutputVarY, 0, 0, W, H, "image/login.png")){
                        SetKeyDelay(10,10)
                        ControlSend(this.setting["Account"] "{Tab}" this.setting["Password"],,"登录 Glyph")
                        ControlClick("x" OutputVarX " y" OutputVarY,"登录 Glyph",,,,"NA")
                        Sleep(30)
                    }
                }
            }
        }
    }
    static Reset(){
        for Key,Value in Game.Lists
            Value.stopAll()
        Game.Lists.Clear()
        Game.Refresh()
    }
    static Refresh(){
        LOADING := false
        GameIDs_HOLD := Map()
        MainGui["SelectGame"].Delete()
        GameIDs := WinGetList("ahk_exe " config.data["Global"]["GameTitle"])
        for Key,Value in Game.Lists.Clone(){
            if not WinExist("ahk_id " Value.id){
                Game.Lists[Key].stopAll(true)
            } else {
                GameIDs_HOLD[Value.id] := ""
                MainGui["SelectGame"].Add([Value.Name])
            }
        }
        for key in GameIDs{
            if not GameIDs_HOLD.Has(key){
                theGame := Game(key)
                if theGame.name != "" {
                    if Game.Lists.Has(theGame.name){
                        theGame := Game.Lists[theGame.name]
                        theGame.GetBase(key)
                        if theGame.running
                            switch theGame.action {
                            Case "钓鱼":
                                theGame.Func()
                            Default:
                                SetTimer(theGame.Func,theGame.setting["AutoBtn"]["interval"])
                            }
                    }
                    else Game.Lists[theGame.name] := theGame
                    MainGui["SelectGame"].Add([theGame.name])
                }
                else LOADING := true
            }
        }
        return LOADING
    }
    stopAll(keepStatus := false){
        running := this.running
        this.running := false
        Func := this.Func
        SetTimer(Func,false)
        try this.thread.ahkTerminate()
        if keepStatus 
            this.running := running
    }
    NatualPress(npbtn,holdtime := 0) {
        ControlSend("{" npbtn " down}",, "ahk_pid " this.pid)
        Sleep(Random(66, 122) + holdtime)
        ControlSend("{" npbtn " up}",, "ahk_pid " this.pid)
        Sleep(Random(66, 122))
    }
    GetName(Address){
        Address := this.GetAddressOffset(Address,StrSplit(config.data["Address_Offset"]["Name"],","))
        Return this.ReadMemory(Address,"Str")
    }
    GetAddressOffset(Address,Offset){
        Address := this.ReadMemory(this.BaseaAddress + Address,"Int")
        Loop Offset.Length - 1
            Address := this.ReadMemory(Address + Offset[A_Index],"Int")
        Return Address + Offset[-1]
    }
    getProcessBaseAddress(id) {
        Return DllCall( A_PtrSize = 4 ? "GetWindowLong" : "GetWindowLongPtr" , "Ptr", id , "Int", -6 , "Int64")
    }
    ReadMemory(Maddress,Readtype,Len := unset) {
        ProcessHandle := DllCall("OpenProcess", "Int", 24, "Char", 0, "UInt", this.pid, "UInt")
        if(Readtype == "Int"){
            Len := IsSet(Len)?Len:4
            Mvalue := Buffer(Len,0)
            DllCall("ReadProcessMemory", "UInt", ProcessHandle, "Ptr", Maddress, "Ptr", Mvalue, "UInt", Len)
            Return NumGet(Mvalue,"Int")
        }
        else if(Readtype == "Str"){
            Len := IsSet(Len)?Len:15
            Mvalue := Buffer(Len,0)
            ProcessHandle := DllCall("OpenProcess", "Int", 24, "Char", 0, "UInt", this.pid, "UInt")
            DllCall("ReadProcessMemory", "UInt", ProcessHandle, "Ptr", Maddress, "Ptr", Mvalue, "UInt", Len)
            Return StrGet(Mvalue,"utf-8")
        }
        throw ValueError("错误的读取类型", -1, Readtype)
    }
    WriteMemory(Address,Value,Len) {
        Mvalue := Buffer(Len, Value)
        ProcessHandle := DllCall("OpenProcess", "Int", 0x38, "Char", 0, "UInt", this.pid, "UInt")
        Return DllCall("WriteProcessMemory", "UInt", ProcessHandle, "Ptr", this.BaseaAddress + Address, "Ptr", Mvalue, "UInt", Len)
    }
}