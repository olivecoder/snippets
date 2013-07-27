class Enum:
    def __init__(self, value):
        self.value = value

    @classmethod
    def name(cls, value):
        return { v:k for k,v in cls.__dict__.items() 
                         if not k.startswith("_") } [value]

    def __str__(self):
        return self.name(self.value)

    def __repr__(self):
        return self.__str__()
