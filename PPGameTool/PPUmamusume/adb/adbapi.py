from ast import Import
import os
import re
import random
import cv2
from . import apidef

device = ''

#获取device信息
def adb_devices():
    device_list = os.popen('adb devices').readlines()
    if(len(device_list) == 1 or len(device_list) == 0):
        print('[ERROR]未找到开启了ADB的设备')
    else:
        print('[INFO]检测到至少一个设备,准备连接第一个设备')
        device_list.pop(len(device_list) - 1)
        device_list.pop(0)
    return device_list

#连接device
def adb_connect(cur_device):
    global device
    device = cur_device
    adb_info = os.popen(f'adb -s {device} connect {apidef.order}').read()
    return adb_info

#截取屏幕
def adb_screen():
    android_path = '/storage/emulated/0/Pictures/'
    img='uma_current.png'
    os.system(f'adb -s {device} shell screencap -p {android_path}{img}')
    os.system(f'adb -s {device} pull {android_path}{img} {apidef.pc_path}')
    return

#截取数据图
def adb_screen_data():
    image_current = cv2.imread(apidef.source_cur_png)
    image_current = image_current[276:1166, 886:1040]
    cv2.imwrite(apidef.source_data_png, image_current)
    return

#检测屏幕分辨率
def adb_screen_size():
    SCREEN_SIZES = os.popen(f'adb -s {device} shell wm size')
    for line in SCREEN_SIZES:
        SCREEN_SIZE = line
    if(SCREEN_SIZE.find('1920x1080') == -1):
        print('[ERROR]检测到屏幕分辨率不正确,请修改至(1080x1920)')
        return False
    print('[INFO]屏幕分辨率检测成功')
    return True

#点击屏幕
def adb_screen_tap(x, y):
    os.system(f'adb -s {device} shell input touchscreen tap {x} {y}')
    return

#点击(不弹起)屏幕
def adb_screen_touch(x, y):
    os.system(f'adb -s {device} shell input touchscreen swipe {x + random.randint(1,20)} {y + random.randint(1,20)} {x + random.randint(1,20)} {y + random.randint(1,20)}')
    return