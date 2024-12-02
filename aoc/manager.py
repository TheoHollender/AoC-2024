
from aoc.credentials import Credentials


class Manager:
    __instance = None
    
    credentials: Credentials = None

    @staticmethod
    def instance ():
        if Manager.__instance is None:
            Manager.__instance = Manager()
        return Manager.__instance
