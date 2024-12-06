
import argparse
import webbrowser
import datetime
import time

now = datetime.datetime.now()

parser = argparse.ArgumentParser()
parser.add_argument("-year", default=str(now.year))
parser.add_argument("-day",  default=str(now.day))
parser.add_argument("-time", default="06:00")

args = parser.parse_args()

year  = int(args.year)
month = 12
day   = int(args.day)
trgs  = list(map(int, args.time.split(":")))

_time = datetime.datetime( year, month, day, *trgs )

delta = (_time - now).seconds + (_time - now).microseconds / 1_000_000

time.sleep(delta)
webbrowser.open("https://adventofcode.com/2024/day/5")
print("TIME IS UP !!!!")