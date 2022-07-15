import os

order='127.0.0.1:5555'
pc_path = os.path.dirname(os.path.abspath(__file__))
source_cur_png = pc_path + '\\uma_current.png'
source_data_png = pc_path + '\\uma_data.png'
source_cht_path = pc_path + '\\..\\scdata\\cht\\'

#屏幕中部分按钮对应的位置
#属性按钮
BTN_SPEED = (100, 1650)
BTN_STAMINA = (300, 1650)
BTN_POWER = (500, 1650)
BTN_WILLPOWER = (700, 1650)
BTN_INTEL = (900, 1650)
#界面按钮
BTN_RETURN = (100, 1850)