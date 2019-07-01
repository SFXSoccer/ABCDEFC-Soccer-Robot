import sensor, image, time, pyb, ustruct
from pyb import UART

#
#   Variables
#

mode = 0                    # Field mode, 0 = normal, 1 = superteams

led_red = pyb.LED(1)
led_green = pyb.LED(2)
led_blue = pyb.LED(3)

led_red.off()
led_green.off()
led_blue.off()

pixels_threshold = 200 if mode == 0 else 5
area_threshold = 200 if mode == 0 else 5

goal_facing = 0             # What goal the robot is facing at startup, 0 = none, 1 = yellow, 2 = blue

# Color Tracking Thresholds (L Min, L Max, A Min, A Max, B Min, B Max)
thresholds = [(18, 30, 21, 46, 15, 40),     # Yellow goal
              (19, 35, 1, 33, -62, -32)]    # Blue goal

white = (85, 100, -5, 5, -5, 5)


#
#   Setup the camera
#

clock = time.clock()

sensor.reset()
sensor.set_pixformat(sensor.RGB565)
sensor.set_framesize(sensor.QVGA)
sensor.skip_frames(time = 1500)
sensor.set_auto_gain(False)     # Must be turned off for color tracking
sensor.set_auto_whitebal(False) # Must be turned off for color tracking

# Make corrections for the camera's physical rotation
sensor.set_hmirror(True)


#
#   Find the opposing teams goal color
#

def get_opposing_goal():
    blue = False
    yellow = False

    led_on = False
    t_prev = clock.avg()

    while (True):
        blue = False
        yellow = False

        #if clock.avg() - t_prev > 500:
        #    if led_on:
        #        t_prev = clock.avg();
        #        led_red.off()
        #        led_on = False
        #    else:
        #        t_prev = clock.avg();
        #        led_red.on()
        #        led_on = True

        img = sensor.snapshot()

        img.draw_rectangle(0, 0, img.width(), int(img.height() / 2))
        for blob in img.find_blobs([thresholds[0]], pixels_threshold=pixels_threshold, area_threshold=area_threshold, merge=True):
            if blob.y() + blob.h() < img.height() / 2 and blob.y() < img.height() / 2:
                img.draw_rectangle(blob.rect(), color=[255, 255, 0])
                img.draw_cross(blob.cx(), blob.cy(), color=[255, 255, 0])
                yellow = True   # found a yellow goal
        for blob in img.find_blobs([thresholds[1]], pixels_threshold=pixels_threshold, area_threshold=area_threshold, merge=True):
            if blob.y() + blob.h() < img.height() / 2 and blob.y() < img.height() / 2:
                img.draw_rectangle(blob.rect(), color=[0, 127, 255])
                img.draw_cross(blob.cx(), blob.cy(), color=[0, 127, 255])
                blue = True     # found a blue goal

        if yellow == True and blue == False:
            global goal_facing
            goal_facing = 1
            print(goal_facing)
            break
        elif yellow == False and blue == True:
            global goal_facing
            goal_facing = 2
            print(goal_facing)
            break
        print(goal_facing)
    led_red.off()

def get_goal_areas():
    clock.tick()
    img = sensor.snapshot()
    img.binary([thresholds[0]])

    prev_size = 0
    cx = -1
    cy = -1
    bx = -1
    by = -1
    bw = -1
    bh = -1

    for blob in img.find_blobs([white], pixels_threshold=pixels_threshold, area_threshold=area_threshold, merge=True):
        img.draw_rectangle(blob.rect(), color=[255, 255, 0])
        img.draw_cross(blob.cx(), blob.cy(), color=[255, 255, 0])
        if blob.area() > prev_size:
            cx = blob.cx()
            cy = blob.cy()
            bx = blob.x()
            by = blob.y()
            bw = blob.w()
            bh = blob.h()
            prev_size = blob.area()
    #if cx == -1 and cy == -1 and bx == -1 and by == -1 and bw == -1 and bh == -1:
    #    led_green.on()
    #else:
    #    led_green.off()

    img.draw_rectangle(bx, by, bw, bh, color=[255, 0, 0])
    img.draw_cross(cx, cy, color=[255, 0, 0])
    #send_i2c_data(cx, cy, cw, ch)
    print("FPS: ", clock.fps(), "| WIDTH ", img.width(), ": HEIGHT ", img.height(), " |", "CX ", cx, ": CY ", cy, ": X ", bx, ": Y ", by, ": W ", bw, ": H ", bh)

get_opposing_goal()

while (True):
    get_goal_areas()
