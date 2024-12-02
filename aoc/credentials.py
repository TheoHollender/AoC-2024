
import json


class Credentials:
    def __init__(self) -> None:
        pass
    def get_session (self):
        raise NotImplementedError()

class FileCredentials(Credentials):
    def __init__(self, path = "credentials.json"):
        with open(path, "r") as file:
            self.session = json.loads(file.read())["token"]
    def get_session(self):
        return self.session
