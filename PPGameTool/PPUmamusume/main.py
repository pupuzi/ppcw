from time import sleep
from adb import adbapi
from adb import gameapi
from adb import apidef

#检测第一个设备
ADB_DEVICE = adbapi.adb_devices()[0]
ADB_NAME_INDEX = ADB_DEVICE.find('device') - 1
ADB_DEVICE = ADB_DEVICE[0:ADB_NAME_INDEX]
#连接ADB
adbapi.adb_connect(ADB_DEVICE)
#检测分辨率
ADB_SIZE = adbapi.adb_screen_size()
#进入事件循环
#if(ADB_SIZE == True):
    #检测事件
#    gameapi.game_exec()

adbapi.adb_screen()