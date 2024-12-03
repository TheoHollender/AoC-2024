
import json
import subprocess
import requests

from aoc.manager import Manager

target = "https://adventofcode.com"

def get_headers ():
    return { "Cookie": f"session={Manager.instance().credentials.get_session()}" }
def get_input (year: int, day: int):
    url = f"{target}/{year}/day/{day}/input"

    response = requests.get(url, headers = get_headers())
    assert response.status_code == 200

    return response.content
def get_content (year: int, day: int):
    url = f"{target}/{year}/day/{day}"

    response = requests.get(url, headers = get_headers())
    assert response.status_code == 200

    return response.content
def submit (year: int, day: int, part: int, answer: int):
    url = f"{target}/{year}/day/{day}/answer"

    fields   = { "level": str(part), "answer": str(answer) }
    session  = requests.Session()
    response = session.post(url, headers = get_headers(), data = fields)

    return 
def num_stars_on (year: int, day: int):
    bytes1 = b"It provides one gold star"
    bytes2 = b"They provide two gold stars"
    
    content = get_content(year, day)

    if bytes2 in content: return 2
    if bytes1 in content: return 1
    return 0

class Problem:
    __year: int
    __day : int

    def __init__(self, year: int, day: int) -> None:
        self.__year = year
        self.__day  = day

    def get_input (self):
        return get_input(self.__year, self.__day)
    def number_of_stars (self):
        return num_stars_on(self.__year, self.__day)
    def submit (self, part1: int | None = None, part2: int | None = None):
        number_of_stars = self.number_of_stars()
        print("Current number of stars :", number_of_stars)
        if part1 is not None and number_of_stars == 0:
            print("Attempting part 1 :", part1)
            submit( self.__year, self.__day, 1, part1 )
            number_of_stars = self.number_of_stars()
            print("New number of stars after part 1 :", number_of_stars)
            
        if part2 is not None and number_of_stars == 1:
            print("Attempting part 2 :", part2)
            submit( self.__year, self.__day, 2, part2 )
            number_of_stars = self.number_of_stars()
            print("New number of stars after part 2 :", number_of_stars)

    def run_solve (self):
        input = self.get_input()
        with open("input", "wb") as file:
            file.write(input)

        day_string = str(self.__day).rjust(2, "0")

        # Compile
        print("Compiling problem solver", f"solvers/day{day_string}.cpp")
        result = subprocess.run([ "g++", "-o", "out", f"./solvers/day{day_string}.cpp", "-I", "./" ])
        assert result.returncode == 0

        process = subprocess.Popen([ "./out" ], stdin = subprocess.PIPE, stdout = subprocess.PIPE)
        stdout, stderr = process.communicate( input )

        lines = stdout.decode(encoding = "utf-8").strip().split("\n")
        ints  = list(map(int, lines))

        parta = None
        partb = None
        if len(ints) >= 1: parta = ints[0]
        if len(ints) >= 2: partb = ints[1]
        
        self.submit(parta, partb)