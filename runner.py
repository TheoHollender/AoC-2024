
from aoc.credentials import FileCredentials
from aoc.manager import Manager
from aoc.problem import Problem

def run ():
    credentials = FileCredentials()

    manager = Manager.instance()
    manager.credentials = credentials

    problem = Problem(2024, 9)
    problem.run_solve()

run()
