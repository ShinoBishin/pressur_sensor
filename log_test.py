import sys
import serial
import datetime
import csv

# シリアルポートセッティング。ボーレート合わせる、IDEのシリアル通信は切っておく
com = serial.Serial("COM7", 9600)

while True:
    val = str(com.readline().decode("utf-8").rstrip("\n"))  # データ型の指定に注意
    date = datetime.datetime.now().strftime("%Y-%m-%d %H:%M:%S")  # 現在時刻取得
    print(date, val)
    with open("test.csv", "a") as f:
        print("{},{}".format(date, val), file=f)
