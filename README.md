# Trove自动脚本

## Auto-Hot-Key

* Fork 自 [MiraculousB](https://github.com/MiraculousB)/**[TroveAutoFish](https://github.com/MiraculousB/TroveAutoFish)** （master分支） — 2020 年

* 脚本功能：`自动钓鱼` `自动按键` `支持游戏多开` 

  ~~`防掉线`~~(包含在自动按键内) ~~`自动丢弃鞋子`~~(原功能测试不可用，暂未更新)

* 原理：使用CE进行内存检测游戏账号和钓鱼判定

  > 查找教程：https://www.youtube.com/watch?v=FYzix68bxFA

  * 账号指针偏移：`“Trove.exe” + 0xFDB95C + 0x10 + 0`
  * 钓鱼判定：`“Trove.exe” + 0xFAB834 + 0x68 + 0xe4`
    * 水：`+ 0x3c4`
    * 熔岩：`+ 0x898`
    * 巧克力：`+ 0x62c`
    * 等离子体：`+ 0xb00 `

## 按键精灵(2018)

* 脚本功能：`自动钓鱼` `支持游戏多开` 

* 原理：使用Win音量合成器图像检测钓鱼声音变化判定钓鱼
  * 需要开满音量
  * 游戏内需设置仅存效果音、开启背景播放
