;@Ahk2Exe-UpdateManifest 2
#SingleInstance,Prompt
#NoTrayIcon
global GameTitle := "Trove.exe"
global FishAddress := "0x113268C"
global NameAddress := "0x115EF64"
global TPAddress := ""
global Fish_Key := "f"
global Press_Key := "e"
class Game{
    static Lists
    __New(id){
        WinGet, pid,PID,ahk_id %id%
        this.id := id
        this.pid := pid
        this.BaseaAddress := this.getProcessBaseAddress(id)
        this.name := this.GetName(NameAddress)
        this.WaterAddress := this.GetAddressWater(FishAddress)
        this.LavaAddress := this.GetAddressLava(FishAddress)
        this.ChocoAddress := this.GetAddressChoco(FishAddress)
        this.PlasmaAddress := this.GetAddressPlasma(FishAddress)
        this.StateWaterAddress := this.GetAddressStateWater(FishAddress)
        this.StateLavaAddress := this.GetAddressStateLava(FishAddress)
        this.StateChocoAddress := this.GetAddressStateChoco(FishAddress)
        this.StatePlasmaAddress := this.GetAddressStatePlasma(FishAddress)
        this.Fish_Interval := 700
        this.AutoBtn_Interval := 10000
        this.TP_Interval := 100
        ; this.AutoCall_Interval := 5000
        ; this.AutoCall_Text := "�˴��༭��������"
        this.AutoPress := False
        this.AutoBtn_key := "End"
        this.Action := "�Զ�����"
        this.Status := False
        this.Func := ObjBindMethod(this, "AutoBtn")
        this.Fish_Thread := AhkThread()
    }
    AutoBtn(){
        this.NatualPress(this.AutoBtn_Key)
        Return
    }
    AutoCall(){
        this.NatualPress("Enter")
        ; δ�깤
        this.NatualPress("Enter")
        Return
    }
    AutoFish(){
        pid := this.pid
        Fish_Interval := this.Fish_Interval
        WaterAddress := this.WaterAddress
        LavaAddress := this.LavaAddress
        ChocoAddress := this.ChocoAddress
        PlasmaAddress := this.PlasmaAddress
        StateWaterAddress := this.StateWaterAddress
        StateLavaAddress := this.StateLavaAddress
        StateChocoAddress := this.StateChocoAddress
        StatePlasmaAddress := this.StatePlasmaAddress
        BaseaAddress := this.BaseaAddress
        AutoPress := this.AutoPress
        ThreadAHK =
        (
            #NoTrayIcon
            ReadMemoryINT(MADDRESS) {
                VarSetCapacity(MVALUE,4,0)
                ProcessHandle := DllCall("OpenProcess", "Int", 24, "Char", 0, "UInt", %pid%, "UInt")
                DllCall("ReadProcessMemory", "UInt", ProcessHandle, "Ptr", MADDRESS, "Int*", MVALUE, "UInt", 4)
                Return MVALUE
            }
            NatualPress(npbtn) {
                ControlSend, , {`%npbtn`% down}, ahk_pid %pid%
                Random, SleepTime, 66, 122
                Sleep, `%SleepTime`%
                ControlSend, , {`%npbtn`% up}, ahk_pid %pid%
                Random, SleepTime, 66, 122
                Sleep, `%SleepTime`%
                Return
            }
            Loop{
                Sleep, %Fish_Interval%
                CaughtWater := ReadMemoryINT("%WaterAddress%")
                CaughtLava := ReadMemoryINT("%LavaAddress%")
                CaughtChoco := ReadMemoryINT("%ChocoAddress%")
                CaughtPlasma := ReadMemoryINT("%PlasmaAddress%")
                StateWater := ReadMemoryINT("%StateWaterAddress%")
                StateLava := ReadMemoryINT("%StateLavaAddress%")
                StateChoco := ReadMemoryINT("%StateChocoAddress%")
                StatePlasma := ReadMemoryINT("%StatePlasmaAddress%")
                if( !StateWater && !StateLava && !StateChoco && !StatePlasma ) {
                    if (%AutoPress%){
                        NatualPress("%Press_Key%")
                        Sleep, 100
                    }
                    NatualPress("%Fish_Key%")
                    Flag := true
                }
                if (CaughtWater || CaughtLava || CaughtChoco || CaughtPlasma) {
                    if (Flag) {
                        Sleep, 1000
                        Flag := false
                    }
                    else {
                        NatualPress("%Fish_Key%")
                        Flag := true
                    }
                }
            }
            Return
        )
        this.Fish_Thread.AhkTerminate()
        If (this.Status)
            this.Fish_Thread := AhkThread(ThreadAHK)
        Return
    }
    NatualPress(npbtn) {
        pid := this.pid
        ControlSend, , {%npbtn% down}, ahk_pid %pid%
        Random, SleepTime, 66, 122
        Sleep, %SleepTime%
        ControlSend, , {%npbtn% up}, ahk_pid %pid%
        Random, SleepTime, 66, 122
        Sleep, %SleepTime%
        Return
    }
    GetID(){
        For Key,Value in Game.Lists{
            Func := Value.Func
            SetTimer % Func,Off
        }
        Game.Lists := Object()
        WinGet, GameIDs,List,ahk_exe %GameTitle%
        GuiControl,, SelectGame , |
        Loop, %GameIDs%{
            GameID := GameIDs%A_Index%
            NowGame := new Game(GameID)
            NowName := NowGame.name
            ObjRawSet(Game.Lists, NowGame.name,NowGame )
            GuiControl,, SelectGame , %NowName% 
        }
        Return
    }
    GetName(Address){
        y1 := this.ReadMemoryINT(this.BaseaAddress + Address)
        y2 := this.ReadMemoryINT(y1 + 0x10)
        Return Name := this.ReadMemoryStr(y2)
    }
    GetAddressWater(Address) {
        y1 := this.ReadMemoryINT(this.BaseaAddress + Address)
        y2 := this.ReadMemoryINT(y1 + 0x68)
        y3 := this.ReadMemoryINT(y2 + 0xe4)
        Return WaterAddress := (y3 + 0x3c4)
    }
    GetAddressLava(Address) {
        y1 := this.ReadMemoryINT(this.BaseaAddress + Address)
        y2 := this.ReadMemoryINT(y1 + 0x68)
        y3 := this.ReadMemoryINT(y2 + 0xe4)
        Return LavaAddress := (y3 + 0x898)
    }
    GetAddressChoco(Address) {
        y1 := this.ReadMemoryINT(this.BaseaAddress + Address)
        y2 := this.ReadMemoryINT(y1 + 0x68)
        y3 := this.ReadMemoryINT(y2 + 0xe4)
        Return ChocoAddress := (y3 + 0x62c)
    }
    GetAddressPlasma(Address){
        y1 := this.ReadMemoryINT(this.BaseaAddress + Address)
        y2 := this.ReadMemoryINT(y1 + 0x68)
        y3 := this.ReadMemoryINT(y2 + 0xe4)
        Return PlasmaAddress := (y3 + 0xb00)
    }
    GetAddressStateWater(Address) {
        y1 := this.ReadMemoryINT(this.BaseaAddress + Address)
        y2 := this.ReadMemoryINT(y1 + 0x68)
        y3 := this.ReadMemoryINT(y2 + 0xf4)
        Return WaterAddress := (y3 + 0xBA0)
    }
    GetAddressStateLava(Address) {
        y1 := this.ReadMemoryINT(this.BaseaAddress + Address)
        y2 := this.ReadMemoryINT(y1 + 0x68)
        y3 := this.ReadMemoryINT(y2 + 0xf4)
        Return LavaAddress := (y3 + 0x938)
    }
    GetAddressStateChoco(Address) {
        y1 := this.ReadMemoryINT(this.BaseaAddress + Address)
        y2 := this.ReadMemoryINT(y1 + 0x68)
        y3 := this.ReadMemoryINT(y2 + 0xf4)
        Return ChocoAddress := (y3 + 0xE08)
    }
    GetAddressStatePlasma(Address){
        y1 := this.ReadMemoryINT(this.BaseaAddress + Address)
        y2 := this.ReadMemoryINT(y1 + 0x68)
        y3 := this.ReadMemoryINT(y2 + 0xf4)
        Return PlasmaAddress := (y3 + 0x6CC)
    }
    getProcessBaseAddress(id) {
        Return DllCall( A_PtrSize = 4 ? "GetWindowLong" : "GetWindowLongPtr" , "Ptr", id , "Int", -6 , "Int64")
    }
    ReadMemoryINT(MADDRESS) {
        VarSetCapacity(MVALUE,4,0)
        ProcessHandle := DllCall("OpenProcess", "Int", 24, "Char", 0, "UInt", this.pid, "UInt")
        DllCall("ReadProcessMemory", "UInt", ProcessHandle, "Ptr", MADDRESS, "Int*", MVALUE, "UInt", 4)
        Return MVALUE
    }
    ReadMemoryStr(MADDRESS) {
        VarSetCapacity(MVALUE,15,0)
        ProcessHandle := DllCall("OpenProcess", "Int", 24, "Char", 0, "UInt", this.pid, "UInt")
        DllCall("ReadProcessMemory", "UInt", ProcessHandle, "Ptr", MADDRESS, "Str", MVALUE, "UInt", 15)
        Return StrGet(&MVALUE,"utf-8")
    }
}
Gui, New ,, Trove����
Gui, Add, Tab3,, ���|����|���� ; |���|ע���˺�
Gui, Tab, ���
Gui, Add, Button,, ˢ��
Gui, Add, Text,, ����б�:
Gui, Add, DropDownList, vSelectGame gSelectGame
Gui, Add, Text,, �ű�����:
Gui, Add, DropDownList, vSelectAction gSelectAction, �Զ�����|���� ; |�Զ�����
Gui, Add, Text,, Ƶ��(����):
Gui, Add, Edit,Number vInterval gInterval
Gui, Add, CheckBox, vAutoPress gAutoPress, �Զ�������
Gui, Add, Text,, ��������:
Gui, Add, Hotkey, vAutoBtn_Key gAutoBtn_Key
; Gui, Add, Text,, �ı�����:
; Gui, Add, Edit,vAutoCall_Text gAutoCall_Text
Gui, Add, Button,, ����
Gui, Tab, ����
Gui, Add, Text,, ��Ϸ����:
Gui, Add, Edit,vGameTitle,%GameTitle%
Gui, Add, Text,, �˺ŵ�ַ:
Gui, Add, Edit,vNameddress,%NameAddress%
Gui, Add, Text,, �����ַ:
Gui, Add, Edit,vFishAddress,%FishAddress%
Gui, Add, Text,, ��������:
Gui, Add, Hotkey,vPress_Key,%Press_Key%
Gui, Add, Text,, ���㰴��:
Gui, Add, Hotkey,vFish_Key,%Fish_Key%
Gui, Add, Button,, ����
Gui, Tab, ����
Gui, Add, ActiveX, w100 h100 Center, % "mshtml:<img src='https://cdn.jsdelivr.net/gh/Angels-D/Angels-D.github.io/medias/avatar.jpg' style='width:100px;'/>"
Gui, Add, Text,, ����: AnglesD  ��ϷID: D_FairyTail
Gui, Add, Text,cRed, �������ȫ��Դ��ѣ�����ѧϰʹ�ã�
Gui, Add, Link,, ����: `n<a href="https://Angels-D.github.io/">https://Angels-D.github.io/</a>
Gui, Add, Link,, Դ��: `n<a href="https://github.com/Angels-D/TroveAuto">https://github.com/Angels-D/TroveAuto</a>
Gui, Add, Link,, �����ƹ�: `n<a target="_blank" href="https://qm.qq.com/cgi-bin/qm/qr?k=vOppyOHhd2WOrA6jJ9Yd-qi8EZQvHjnk&jump_from=webapi">AshesWithoutFire[Ⱥ��:423933990]</a>
Gui, Show
Buttonˢ��: ; Reload
    Game.GetID()
    GuiControl, Choose ,SelectGame,0
    GuiControl, Choose ,SelectAction,0
    GuiControl,, AutoPress , 0
    GuiControl, Text ,Interval
    GuiControl, Text ,AutoBtn_Key
    GuiControl, Text ,AutoCall_Text
    GuiControl, Text, �ر�,����
    GuiControl, Disable, SelectAction
    GuiControl, Disable, Interval
    GuiControl, Disable ,AutoPress
    GuiControl, Disable, AutoBtn_Key
    GuiControl, Disable, AutoCall_Text
    GuiControl, Disable, ����
    Gui,Submit, NoHide
Return
SelectGame:
    GuiControlGet, SelectGame
    GuiControl, ChooseString, SelectAction, % Game.Lists[SelectGame].Action
    GuiControl, Text, �ر�,����
    GuiControl, Enable, SelectAction
    GuiControl, Enable, Interval
    GuiControl, Disable ,AutoPress
    GuiControl, Disable, AutoBtn_Key
    GuiControl, Disable, AutoCall_Text
    GuiControl, Enable, ����
    If (Game.Lists[SelectGame].Status){
        GuiControl, Text, ����,�ر�
        GuiControl, Disable, SelectAction
        GuiControl, Disable, Interval
    }
SelectAction:
    GuiControlGet, SelectAction
    Game.Lists[SelectGame].Action := SelectAction
    GuiControl, Disable ,AutoPress
    GuiControl, Disable, AutoBtn_Key
    GuiControl, Disable, AutoCall_Text
    GuiControl,, AutoPress , % Game.Lists[SelectGame].AutoPress
    GuiControl, Text, AutoBtn_Key, % Game.Lists[SelectGame].AutoBtn_Key
    GuiControl, Text, AutoCall_Text, % Game.Lists[SelectGame].AutoCall_Text
    Switch SelectAction{
    Case "�Զ�����":
        Game.Lists[SelectGame].Func := ObjBindMethod(Game.Lists[SelectGame], "AutoBtn")
        GuiControl, Text, Interval, % Game.Lists[SelectGame].AutoBtn_Interval
        If(!Game.Lists[SelectGame].Status) 
            GuiControl, Enable, AutoBtn_Key
    Case "����":
        Game.Lists[SelectGame].Func := ObjBindMethod(Game.Lists[SelectGame], "AutoFish")
        GuiControl, Text, Interval, % Game.Lists[SelectGame].Fish_Interval
        If(!Game.Lists[SelectGame].Status) 
            GuiControl, Enable, AutoPress
        ; Case "�Զ�����":
        ;     Game.Lists[SelectGame].Func := ObjBindMethod(Game.Lists[SelectGame], "AutoCall")
        ;     GuiControl, Text, Interval, % Game.Lists[SelectGame].AutoCall_Interval
        ;     If(!Game.Lists[SelectGame].Status) 
        ;         GuiControl, Enable, AutoCall_Text
    }
Return
Interval:
    GuiControlGet, Interval
    Switch SelectAction{
    Case "�Զ�����":
        Game.Lists[SelectGame].AutoBtn_Interval := Interval
    Case "����":
        Game.Lists[SelectGame].Fish_Interval := Interval
        ; Case "�Զ�����":
        ;     Game.Lists[SelectGame].AutoCall_Interval := Interval
    }
Return
AutoPress:
    GuiControlGet, AutoPress
    Game.Lists[SelectGame].AutoPress := AutoPress
Return
AutoBtn_Key:
    GuiControlGet, AutoBtn_Key
    Game.Lists[SelectGame].AutoBtn_Key := AutoBtn_Key
Return
AutoCall_Text:
    GuiControlGet, AutoCall_Text
    Game.Lists[SelectGame].AutoCall_Text := AutoCall_Text
Return
Button����:
    If (Game.Lists[SelectGame].Status){
        GuiControl, Text, �ر�,����
        GuiControl, Enable, SelectAction
        GuiControl, Enable, Interval
        Game.Lists[SelectGame].Status := False
        Func := Game.Lists[SelectGame].Func
        If (SelectAction = "����"){
            GuiControl, Enable ,AutoPress
            %Func%()
        }
        Else{
            GuiControl, Enable ,AutoBtn_Key
            SetTimer % Func,Delete
        }
    }
    Else{
        GuiControl, Text, ����,�ر�
        GuiControl, Disable, SelectAction
        GuiControl, Disable, Interval
        Game.Lists[SelectGame].Status := True
        Func := Game.Lists[SelectGame].Func
        If (SelectAction = "����"){
            GuiControl, Disable ,AutoPress
            %Func%()
        }
        Else{
            GuiControl, Disable ,AutoBtn_Key
            SetTimer % Func,% Interval
        }
    }
Return
Button����:
    Gui,Submit, NoHide
Return
GuiClose:
ExitApp