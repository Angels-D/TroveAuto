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
        ),
        "Key",Map(
            ; "Press","e",
            "Fish","f",
        ),
        "Address",Map(
            "Attack","0xAED288",
            "Dismount","0x42D6EE",
            "Mining","0x9C3F78",
            "MiningGeode","0x972147",
            "Breakblocks","0x9763C3",
            "Map","0x9F3E9D",
            "Zoom","0x8DE6E6",
            "ClipCam","0x8E077A",
            "LockCam","0xACC295",
            "Animation","0x7F7155",
            "Fish","0x117B02C",
            "Name","0x11821FC",
            ; "TP","",
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
MainGui.Add("Text","xs w200","说明: 当前使用Steam打开游戏会强制绑定账号, 直接使用官方启动器即可跳过绑定"
)
MainGui.Add("Button","w200 vModsPathBtn","Mods文件夹")
MainGui.Add("Link","w200","
    (
        说明: 本游戏支持模组, 可通过各公会群和Steam创意工坊等渠道下载, Mod制作可使用
        <a href="https://github.com/DazoTrove/TroveTools.NET/">TroveTools.NET</a>等工具
    )"
)
MainGui.Add("Button","w200 vModCfgsPathBtn","ModCfgs文件夹")
MainGui.Add("Link","w200",Format("说明: Cfgs用于保存某些Mod的配置信息,一般位于<a href=`"file:///{1}\Trove\ModCfgs\`">%AppData%\Trove\ModCfgs\</a>中",A_AppData))
MainGui.Add("Text","w200","Mod使用教程: 后缀为.tmod的文件存放在Mods文件夹, 后缀为.cfg的文件存放在ModCfgs文件夹, 放置后重启游戏生效")
MainGui.Add("Link","w200","附: 官方邮箱<a href=`"mailto:support@gamigo.com`">support@gamigo.com</a>(通过此邮箱询问交易问题、账号问题等内容,注意使用英文描述")

; 面板内容
MainGui["Tab"].UseTab("面板")
MainGui.Add("Button","x+40 y+80 w80 Section vRefreshBtn","刷新")
MainGui.Add("Button","ys x+80 vStartBtn","启动")
MainGui.Add("Text","xs w70 Section","玩家列表:")
MainGui.Add("DropDownList","ys w130 vSelectGame")
MainGui.Add("Text","xs w70 Section","脚本动作:")
MainGui.Add("DropDownList","ys w130 vSelectAction",["自动按键","钓鱼"]) ; 自动喊话
MainGui.Add("Text","xs w100 Section","频率(毫秒):")
MainGui.Add("Edit","ys w100 vInterval")
for key,value in Map(
        ; "AutoPress","自动接任务",
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
    MainGui.Add("CheckBox",(Mod(A_Index,2)?"xs Section":"ys") " w130 v" key,value)
MainGui.Add("Text","xs w70 Section","按键设置:")
MainGui.Add("Hotkey","ys w130 vAutoBtn_Key")
; MainGui.Add("Text",,"文本内容:")
; MainGui.Add("Hotkey","vAutoCall_Text")

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
; MainGui.Add("Text",,"交互按键:")
; MainGui.Add("HotKey","vPressKey",config.data["Key"]["Press"])
MainGui.Add("Text","xs w100 Section","钓鱼按键:")
MainGui.Add("HotKey","ys w100 vFishKey ",config.data["Key"]["Fish"])
MainGui.Add("Button","xs w200 vSaveBtn","保存")

; 关于内容
MainGui["Tab"].UseTab("关于")
MainGui.Add("ActiveX","w100 h100 y+80 Center",
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

; 绑定交互
MainGui["GamePathBtn"].OnEvent("Click",GetGamePath)
MainGui["GameStartBtn"].OnEvent("Click",GameStart)
MainGui["ModsPathBtn"].OnEvent("Click",OpenModsPath)
MainGui["ModCfgsPathBtn"].OnEvent("Click",OpenModCfgsPath)
MainGui["RefreshBtn"].OnEvent("Click",Refresh)
MainGui["StartBtn"].OnEvent("Click",Start)
MainGui["SaveBtn"].OnEvent("Click",Save)
MainGui["SelectGame"].OnEvent("Change",SelectGame)
MainGui["SelectAction"].OnEvent("Change",SelectAction)
MainGui["Interval"].OnEvent("Change",Interval)
MainGui["AutoBtn_Key"].OnEvent("Change",AutoBtn_Key)
; MainGui["AutoCall_Text"].OnEvent("Change",AutoCall_Text)
for key in ["Attack","Dismount","Mining","MiningGeode"
        ,"Breakblocks","Map","Zoom","ClipCam","LockCam","Animation"]
    MainGui[key].OnEvent("Click",Features)

Refresh()
MainGui.Show()

; 交互函数
GetGamePath(GuiCtrlObj, Info){
    Try{
        GamePath := WinGetProcessPath("ahk_exe i)" config.data["Global"]["GameTitle"] "|Glyph.*")
        RegExMatch(GamePath, "i)^(.*?Trove)", &GamePath)
        MainGui["GamePath"].Value := GamePath[0]
    }
    Catch
        MsgBox("请运行游戏或登陆器以检测路径")
}
GameStart(GuiCtrlObj, Info){
    Try Run(Format("{1}\GlyphClient.exe",config.data["Global"]["GamePath"]))
    Catch
        MsgBox("游戏启动失败, 请检查游戏路径")
}
OpenModsPath(GuiCtrlObj, Info){
    Try Run(Format("explore {1}\Games\Trove\Live\mods",config.data["Global"]["GamePath"]))
    Catch
        MsgBox("Mods文件夹打开失败, 请检查游戏路径")
}
OpenModCfgsPath(GuiCtrlObj, Info){
    Try Run(Format("explore {1}\Trove\ModCfgs\",A_AppData))
    Catch
        MsgBox("ModCfgs文件夹打开失败, 请检查文件夹是否存在")
}
Refresh(GuiCtrlObj := unset, Info := unset){
    Game.GetID()
    for key in ["Attack","Dismount","Mining","MiningGeode"
        ,"Breakblocks","Map","Zoom","ClipCam","LockCam","Animation"
        ,"AutoBtn_Key","Interval","SelectAction","StartBtn"] ; AutoPress AutoCall_Text
        MainGui[key].Enabled := False
    for key in ["Attack","Dismount","Mining","MiningGeode"
        ,"Breakblocks","Map","Zoom","ClipCam","LockCam","Animation"
        ,"AutoBtn_Key","Interval","SelectAction","SelectGame"] ; AutoPress AutoCall_Text
        Try MainGui[key].Value := ""
        Catch
            MainGui[key].Value := 0
}
Start(GuiCtrlObj, Info){
    Func := Game.Lists[MainGui["SelectGame"].Text].Func
    if(Game.Lists[MainGui["SelectGame"].Text].running){
        MainGui["StartBtn"].Text := "启动"
        for key in ["SelectAction","Interval"]
            MainGui[key].Enabled := True
        Game.Lists[MainGui["SelectGame"].Text].running := False
        switch MainGui["SelectAction"].Text {
        Case "钓鱼":
            ; MainGui["AutoPress"].Enabled := True
            Func()
        Default:
            MainGui["AutoBtn_Key"].Enabled := True
            SetTimer(Func,False)
        }
    }
    else{
        MainGui["StartBtn"].Text := "关闭"
        for key in ["SelectAction","Interval"]
            MainGui[key].Enabled := False
        Game.Lists[MainGui["SelectGame"].Text].running := True
        switch MainGui["SelectAction"].Text {
        Case "钓鱼":
            ; MainGui["AutoPress"].Enabled := False
            Func()
        Default:
            MainGui["AutoBtn_Key"].Enabled := False
            SetTimer(Func,MainGui["Interval"].Value)
        }
    }
}
Save(GuiCtrlObj, Info){
    for sect,data in config.data{
        if(sect == "Address_Offset" or sect == "Features_Change")
            Continue
        for key in data
            Try config.data[sect][key] := MainGui[key sect].Value
            Catch
                config.data[sect][key] := MainGui[key].Value
    }
    config.Save()
}
SelectGame(GuiCtrlObj, Info){
    MainGui["SelectAction"].Text := Game.Lists[GuiCtrlObj.Text].action
    MainGui["StartBtn"].Text := Game.Lists[GuiCtrlObj.Text].running ? "关闭":"启动"
    for key in ["SelectAction","Interval","StartBtn"]
        MainGui[key].Enabled := !Game.Lists[GuiCtrlObj.Text].running
    SelectAction(MainGui["SelectAction"])
}
SelectAction(GuiCtrlObj, Info := unset){
    Game.Lists[MainGui["SelectGame"].Text].action := GuiCtrlObj.Text
    for key in ["Attack","Dismount","Mining","MiningGeode"
        ,"Breakblocks","Map","Zoom","ClipCam","LockCam","Animation"]{
        MainGui[key].Enabled := True
        MainGui[key].Value := Game.Lists[MainGui["SelectGame"].Text].setting["Features"][key]
    }
    for key in ["AutoBtn_Key"] ; AutoPress AutoCall_Text
        MainGui[key].Enabled := False
    MainGui["AutoBtn_Key"].Value := Game.Lists[MainGui["SelectGame"].Text].setting["AutoBtn"]["key"]
    ; MainGui["AutoCall_Text"].Value := Game.Lists[MainGui["SelectGame"].Text].setting["AutoCall_Text"]["text"]
    Switch GuiCtrlObj.Text {
    Case "自动按键":
        Game.Lists[MainGui["SelectGame"].Text].Func := ObjBindMethod(Game.Lists[MainGui["SelectGame"].Text], "AutoBtn")
        MainGui["Interval"].Value := Game.Lists[MainGui["SelectGame"].Text].setting["AutoBtn"]["interval"]
        If(!Game.Lists[MainGui["SelectGame"].Text].running) 
            MainGui["AutoBtn_Key"].Enabled := True
    Case "钓鱼":
        Game.Lists[MainGui["SelectGame"].Text].Func := ObjBindMethod(Game.Lists[MainGui["SelectGame"].Text], "AutoFish")
        MainGui["Interval"].Value := Game.Lists[MainGui["SelectGame"].Text].setting["Fish"]["interval"]
        ; If(!Game.Lists[MainGui["SelectGame"].Text].running) 
        ;     MainGui["AutoPress"].Enabled := True
    ; Case "自动喊话":
    ;     Game.Lists[MainGui["SelectGame"].Text].Func := ObjBindMethod(Game.Lists[MainGui["SelectGame"].Text], "AutCall")
    ;     MainGui["Interval"].Value := Game.Lists[MainGui["SelectGame"].Text].setting["AutoCall"]["Interval"]
    ;     If(!Game.Lists[MainGui["SelectGame"].Text].running) 
    ;         MainGui["AutoCall_Text"].Enabled := True
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
        Game.Lists[MainGui["SelectGame"].Text].setting["AutoBtn"]["Interval"] := Interval
    Case "钓鱼":
        Game.Lists[MainGui["SelectGame"].Text].setting["Fish"]["Interval"] := Interval
        ; Case "自动喊话":
        ;     [Game.Lists[MainGui["SelectGame"].Text].setting["AutoCall"]["Interval"] := Interval
    } 
}
AutoBtn_Key(GuiCtrlObj, Info){
    Game.Lists[MainGui["SelectGame"].Text].setting["AutoBtn"]["key"] := GuiCtrlObj.Value
}
; AutoCall_Text(GuiCtrlObj, Info){
;     Game.Lists[MainGui["SelectGame"].Text].setting["AutoCall_Text"]["Text"] := GuiCtrlObj.Text
; }

; 核心类

; Config Class
class _Config{
    __New(path,data){
        this.path := path
        this.data := data
    }
    Load(path := unset){
        path := IsSet(path) ? path : this.path
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
}

; Game Class
class Game{
    static Lists := Map()
    action := "自动按键"
    running := False
    setting := Map(
        "Features",Map(),
        "Fish",Map(
            "interval","700",
            "take_address",Map(),
            "state_address",Map(),
        ),
        "AutoBtn",Map(
            "interval","10000",
            "key","End",
        ),
        ; "AutoCall",Map(
        ;     "interval","5000",
        ;     "text","此处编辑喊话内容",
        ; ),
    )
    __New(id){
        this.id := id
        this.pid := WingetPID("ahk_id " id)
        this.BaseaAddress := this.getProcessBaseAddress(id)
        this.name := this.GetName(config.data["Address"]["Name"])
        for key in ["Water","Lava","Choco","Plasma"] {
            this.setting["Fish"]["take_address"][key] := this.GetAddressOffset(
                config.data["Address"]["Fish"],StrSplit(config.data["Address_Offset"]["Fish_" "Take_" key],",")
            )
            this.setting["Fish"]["state_address"][key] := this.GetAddressOffset(
                config.data["Address"]["Fish"],StrSplit(config.data["Address_Offset"]["Fish_" "State_" key],",")
            )
        }
        for key in ["Attack","Dismount","Mining","MiningGeode"
            ,"Breakblocks","Map","Zoom","ClipCam","LockCam","Animation",] ; AutoPress
            this.setting["Features"][key] := False
        this.Func := ObjBindMethod(this, "AutoBtn")
    }
    AutoBtn(){
        this.NatualPress(this.setting["AutoBtn"]["key"])
    }
    ; AutoCall(){
    ;     this.NatualPress("Enter")
    ;     ; 未完工
    ;     this.NatualPress("Enter")
    ;     Return
    ; }
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
                Loop{
                    Sleep(Interval)
                    TakeFlag := False
                    StateFlag := False
                    for key in Take_Address
                        TakeFlag |= ReadMemoryINT(key,Pid)
                    for key in State_Address
                        StateFlag |= ReadMemoryINT(key,Pid)
                    if(!StateFlag) {
                        ; if (AutoPress){
                        ;     NatualPress(PressKey,Pid)
                        ;     Sleep(100)
                        ; }
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
        Try this.thread.ahkTerminate()
        If (this.running)
            this.thread := NewThread(ThreadAHK)
    }
    static GetID(){
        for Key,Value in Game.Lists{
            Value.running := False
            Func := Value.Func
            SetTimer(Func,False)
            Try Value.thread.ahkTerminate()
        }
        Game.Lists := Map()
        MainGui["SelectGame"].Delete()
        GameIDs := WinGetList("ahk_exe " config.data["Global"]["GameTitle"])
        for key in GameIDs{
            theGame := Game(key)
            Game.Lists[theGame.name] := theGame
            MainGui["SelectGame"].Add([theGame.name])
        }
    }
    NatualPress(npbtn) {
        ControlSend("{" npbtn " down}",, "ahk_pid " this.pid)
        Sleep(Random(66, 122))
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