import os
import re
from time import sleep
import cv2
import random
from . import apidef
from . import adbapi
import numpy as np

#匹配图像:返回-1为不存在匹配的图片
def game_png(image):
    image_current = cv2.imread(apidef.source_cur_png)
    image_source = cv2.imread(image)
    res = cv2.matchTemplate(image_source, image_current, cv2.TM_CCOEFF_NORMED)
    min_val, max_val, min_loc, max_loc = cv2.minMaxLoc(res)
    if(max_val < 0.85):
        #print('[ERROR]相似度过低!')
        return(-1, -1, -1, -1)
    return (min_val, max_val, min_loc, max_loc)

#匹配图像数量
def game_png_count(image):
    image_current = cv2.imread(apidef.source_data_png)
    image_source = cv2.imread(image)
    res = cv2.matchTemplate(image_source, image_current, cv2.TM_CCOEFF_NORMED)
    loc = np.argwhere(res >= 0.95)
    return len(loc)

#获取匹配图像区域并随机生成一个区域内的点:返回-1则没有可以返回的pos
def game_pos(image):
    image_source = cv2.imread(image)
    min_val, max_val, min_loc, max_loc = game_png(image)
    if(max_val == -1):
        return (-1, -1)
    height, width, color = image_source.shape
    return (max_loc[0] + random.randint(1,width), max_loc[1] + random.randint(1,height))

#判断训练数量
def game_active_num():
    adbapi.adb_screen_data()
    image_data = cv2.imread(apidef.source_data_png)
    #速度数量
    num = game_png_count(apidef.source_cht_path + 'speed.png')
    #耐力数量
    #num = num + game_png_count(apidef.source_cht_path + 'stamina.png')
    #力量数量
    num = num + game_png_count(apidef.source_cht_path + 'power.png')
    #毅力数量
    num = num + game_png_count(apidef.source_cht_path + 'willpower.png')
    #智力数量
    num = num + game_png_count(apidef.source_cht_path + 'intel.png')
    return num

#补充体力
def game_rest():
    pos = game_pos(apidef.source_cht_path + 'emo.png')
    if(pos[0] == -1):
        #心情不满,优先心情
        pos = game_pos(apidef.source_cht_path + 'out.png')
    else:
        pos = game_pos(apidef.source_cht_path + 'rest.png')
    adbapi.adb_screen_tap(pos[0], pos[1])
    return

#获取当前训练按钮
def game_cur_btn():
    pos = game_pos(apidef.source_cht_path + 'cur_active.png')
    if(pos[0] < 250 and pos[0] > 65):
        return apidef.BTN_SPEED
    elif(pos[0] < 445 and pos[0] > 250):
        return apidef.BTN_STAMINA
    elif(pos[0] < 635 and pos[0] > 445):
        return apidef.BTN_POWER
    elif(pos[0] < 835 and pos[0] > 635):
        return apidef.BTN_WILLPOWER
    elif(pos[0] > 835):
        return apidef.BTN_INTEL
    return (-1, -1)
    
#训练界面中
def game_active():
    #判断界面是否已经转到训练界面
    if(game_is_active() == -1):
        return 
    #开始计算训练数据(人头)
    if(game_cur_btn() != apidef.BTN_INTEL):
        adbapi.adb_screen_touch(apidef.BTN_INTEL[0], apidef.BTN_INTEL[1])
        adbapi.adb_screen()
        if(game_is_active() == -1):
            return 
    btn_pos = apidef.BTN_INTEL
    value = game_active_num()
    adbapi.adb_screen_touch(apidef.BTN_WILLPOWER[0], apidef.BTN_WILLPOWER[1])
    adbapi.adb_screen()
    if(game_is_active() == -1):
        return 
    if(game_active_num() > value):
        value = game_active_num()
        btn_pos = apidef.BTN_WILLPOWER
    adbapi.adb_screen_touch(apidef.BTN_POWER[0], apidef.BTN_POWER[1])
    adbapi.adb_screen()
    if(game_is_active() == -1):
        return 
    if(game_active_num() > value):
        value = game_active_num()
        btn_pos = apidef.BTN_POWER
    adbapi.adb_screen_touch(apidef.BTN_STAMINA[0], apidef.BTN_STAMINA[1])
    adbapi.adb_screen()
    if(game_is_active() == -1):
        return 
    if(game_active_num() > value):
        value = game_active_num()
        btn_pos = apidef.BTN_STAMINA
    adbapi.adb_screen_touch(apidef.BTN_SPEED[0], apidef.BTN_SPEED[1])
    adbapi.adb_screen()
    if(game_is_active() == -1):
        return 
    if(game_active_num() > value):
        value = game_active_num()
        btn_pos = apidef.BTN_SPEED
    #计算体力
    pos = game_pos(apidef.source_cht_path + 'fault30.png')
    if(pos[0] != -1):
        #如果体力不够,休息/外出
        adbapi.adb_screen_tap(apidef.BTN_RETURN[0], apidef.BTN_RETURN[1])
        game_rest()
        return
    adbapi.adb_screen_tap(btn_pos[0], btn_pos[1])
    adbapi.adb_screen_tap(btn_pos[0], btn_pos[1])
    return

#判断event界面:返回-1则不是event界面
def game_is_event():
    min_val, max_val, min_loc, max_loc = game_png(apidef.source_cht_path + 'event.png')
    return max_val

#判断主界面:返回-1则不是主界面
def game_is_main():
    min_val, max_val, min_loc, max_loc = game_png(apidef.source_cht_path + 'main.png')
    return max_val

#判断比赛界面:返回-1则不是比赛界面
def game_is_race():
    min_val, max_val, min_loc, max_loc = game_png(apidef.source_cht_path + 'race.png')
    return max_val

#判断锻炼界面:返回-1则不是锻炼界面
def game_is_active():
    min_val, max_val, min_loc, max_loc = game_png(apidef.source_cht_path + 'active.png')
    return max_val

#主界面中
def game_main():
    pos = game_pos(apidef.source_cht_path + 'main.png')
    adbapi.adb_screen_tap(pos[0], pos[1])
    return

#事件中
def game_event():
    pos = game_pos(apidef.source_cht_path + 'event.png')
    adbapi.adb_screen_tap(pos[0], pos[1])
    return

#比赛中
def game_race():
    pos = game_pos(apidef.source_cht_path + 'race.png')
    adbapi.adb_screen_tap(pos[0], pos[1] + 100)
    is_racing = True
    while(is_racing):
        #判断绿色参赛按钮
        #判断左下角跳过按钮
        #...
        sleep(1000)
    return

#事件循环
def game_exec():
    while(1):
        adbapi.adb_screen()
        if(game_is_main() != -1):
            game_main()
        elif(game_is_event() != -1):
            game_event()
        elif(game_is_active() != -1):
            game_active()
        elif(game_is_race() != -1):
            game_race()
    return