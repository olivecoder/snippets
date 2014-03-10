def singleton(cls):
    """
    Singleton design pattern decorator

    LIMITATIONS
    - works just with the new style classes
    - not thread safe

    USAGE:
        @singleton
        class SingletonClass(object):
            ...

    Robert Oliveira <olivecoder@gmail.com>
    """

    @classmethod
    def singleton_new(cls, *args, **kwargs):
        """create a new one just if not created yet"""
        if cls._instance is None:
            cls._instance = cls._org_new(cls, *args, **kwargs)
            cls._instance._is_initialized = False
        return cls._instance

    def singleton_init(self, *args, **kwargs):
        """initialize jist is not initialized ye"""
        if not self._is_initialized:
            self._is_initialized = True
            self._org_init(*args, **kwargs)

    cls._instance = None
    cls._org_init = cls.__init__
    cls._org_new = cls.__new__
    cls.__new__ = singleton_new
    cls.__init__ = singleton_init
    return cls
