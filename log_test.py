import sys
import serial
import datetime
import csv

# シリアルポートセッティング。ポートとボーレートは利用中の環境に合わせる、IDE側ののシリアル通信は切っておく　
com = serial.Serial("COM7", 9600)

while True:
    # Serial.print()を文字列として出力します
    val = str(com.readline().decode("utf-8").rstrip("\n"))
    date = datetime.datetime.now().strftime("%Y-%m-%d %H:%M:%S")  # 現在時刻取得
    with open("test.csv", "a") as f:  # (ファイル名適宜変更してください)
        print("{},{}".format(date, val), file=f)  # CSVに出力！

# 満足したらCtl + C で止めてください！
# VScodeの場合はF5()で実行できるので便利です
