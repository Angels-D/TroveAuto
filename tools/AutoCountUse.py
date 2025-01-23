from psutil import process_iter
from threading import Thread
from datetime import datetime
import time
import os
import sys
import pymem
import signal

try:
    SAVE_PATH = os.getcwd() + (sys.argv[1] if len(sys.argv) > 1 else "")
    os.makedirs(SAVE_PATH, exist_ok=True)
    Games = {}
    print(f"""
    ************* 欢迎使用 Trove 物品栏消耗自动计数脚本 - By とても残念だ *************
    * - 使用本工具之前，请知晓以下内容:
    *   0. 本工具需要管理员权限读取游戏内存, 继续使用代表您知晓并愿意承担风险
    *   1. 本工具会在你按下技能、药瓶、物品栏道具后记录剩余数量
    *   2. 本工具仅记录最近按下的道具剩余数量, 若是无下标技能则计数始为0
    *   3. 本工具仅在道具或技能按下后计数, 不触发则不计数
    *   4. 本工具仅记录变化的值, 若不消耗则不记录
    *   5. 由于技能会干扰计数, 故自动忽略小于等于5的计数
    *   6. 本工具支持多开, 断线后自动恢复计数
    *   7. 本工具使用后, 以下目录会生成各玩家的使用日志, 供后续分析
    *     路径: {SAVE_PATH}
    ************************** 本工具开源免费, 仅供学习使用 **************************
    """)

    while True:
        AUTO_SHUTDOWN = input(">> 物品剩余6-10个时自动关闭游戏(Y/N): ").upper()
        if (AUTO_SHUTDOWN == 'YES' or AUTO_SHUTDOWN == 'Y'):
            AUTO_SHUTDOWN = True
            break
        elif (AUTO_SHUTDOWN == 'NO' or AUTO_SHUTDOWN == 'N'):
            AUTO_SHUTDOWN = False
            break
        else:
            print("输入有误, 请输入重新输入")

    GAME = 'Trove.exe'
    FIND_NAME = ['FF 70 1C FF 70 18 8D 45 B0', [-0x9, 0x0, 0x10, 0x0]]
    FIND_USE = [['XX XX XX XX XX XX XX 40 A0 99 XX 4E 66 XX 51',
                'XX XX XX XX XX XX XX 40 80 EB XX XX XX XX 4D'], [0x40]]

    def run(game: pymem.Pymem):
        try:
            count_old = None
            count_check = 1
            while True:
                for pattern in FIND_USE[0]:
                    for address in game.pattern_scan_all(convert_pattern_to_regex(pattern), return_multiple=True):
                        count = read(game, game.read_double,
                                     address, FIND_USE[1])
                        if not (count % 1 == 0 and 5 < count <= 9999):
                            continue
                        if count_old and count_old == count:
                            break
                        if count_old and abs(count_old - count) > count_check:
                            count_check = min(9999, count_check*10)
                            continue
                        count_old = count
                        count_check = 10
                        game.write_bytes(address, b'', len(
                            pattern.replace(' ', ''))//2)
                        game.log.write(f'{datetime.now()} {
                                       int(count)}\n'.encode())
                        print(f'[{datetime.now()}] {game.name} {
                              int(count)}\n', end='')
                        if (5 < count <= 10 and AUTO_SHUTDOWN):
                            os.kill(game.pid, signal.SIGTERM)
                        break
                    else:
                        continue
                    break
                time.sleep(1)
        except Exception as e:
            # print(f'[{datetime.now()}] [Error] {e}\n',end='')
            game.log.close()
            Games.pop(game.name)

    def read(game: pymem.Pymem, func, address, offset):
        return read(game, func, game.read_int(address + offset[0]), offset[1:]) if len(offset) > 1 else func(address + offset[0])

    def convert_pattern_to_regex(byte_pattern):
        return b''.join(b"." if part == 'XX' else bytes.fromhex(part) for part in byte_pattern.split())

    def main():
        Games_Keys = []
        while True:
            try:
                for process in process_iter(["pid", "name"]):
                    if process.info["name"] != GAME:
                        continue
                    Game = pymem.Pymem(process.info["pid"])
                    Game.pid = process.info["pid"]
                    Game.name = read(Game, Game.read_string, Game.pattern_scan_module(
                        convert_pattern_to_regex(FIND_NAME[0]), GAME), FIND_NAME[1])
                    if Game.name in Games:
                        continue
                    Game.log = open(os.path.join(SAVE_PATH, f'{Game.name} {
                                    datetime.now().strftime("%Y-%m-%d")}.txt'), 'ab+', buffering=0)
                    Game.work = Thread(target=run, args=(Game,))
                    Game.work.daemon = True
                    Game.work.start()
                    Games[Game.name] = Game
            except Exception as e:
                pass
            New_Games_Keys = list(Games.keys())
            New_Games_Keys.sort()
            if (Games_Keys != New_Games_Keys):
                Games_Keys = New_Games_Keys
                print(f'-> {datetime.now().strftime("%Y-%m-%d %H:%M:%S")
                            } 玩家列表: {"| ".join(Games_Keys)}')
            time.sleep(5)

    Thread(target=main, daemon=True).start()

    while True:
        pass
except KeyboardInterrupt:
    pass
finally:
    [game.log.close() for game in Games]

# print('按ESC键退出')
# keyboard.wait('esc')
