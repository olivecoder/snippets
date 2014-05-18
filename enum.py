class Enum:

    @classmethod
    def keys(cls):
        return [key for key in dir(cls)
                      if not n.startswith('_') and
                         not callable(getattr(cls,key))]

    @classmethod
    def values(cls):
        return [getattr(cls,key) for key in cls.keys()]

    @classmethod
    def items(cls):
        return [(key, getattr(cls,key)) for key in cls.keys()]

    @classmethod
    def name(cls, value):
        for k, v in cls.items():
            if value == v:
                return k

    def __init__(self, value):
        self._value = value

    def __str__(self):
        return self.name(self._value)

