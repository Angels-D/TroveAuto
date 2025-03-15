
StrCrypto(src, decode := false) {
    static chars := "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789!@#%*_+"
    static charsLen := StrLen(chars)
    key := "y(Hn,(}I+2209Zd^s5(E%vfpoKh.I="
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

name := ""
MsgBox(Format("<{1}:{2}>", name, StrCrypto(name)))
