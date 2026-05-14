import ctypes
from enum import IntEnum

class TileType(IntEnum):
    NONE = 0
    SALT = 1
    AIR = 2
    FIRE = 3
    WATER = 4
    EARTH = 5
    LIFE = 6
    DEATH = 7
    QUICKSILVER = 8
    LEAD = 9
    TIN = 10
    IRON = 11
    COPPER = 12
    SILVER = 13
    GOLD = 14

class SigmarMove(ctypes.Structure):
    _fields_ = [
        ("a1", ctypes.c_int),
        ("b1", ctypes.c_int),
        ("t1", ctypes.c_int),
        ("a2", ctypes.c_int),
        ("b2", ctypes.c_int),
        ("t2", ctypes.c_int),
    ]

    def __repr__(self):
        return f"SigmarMove(a1={self.a1}, b1={self.b1}, t1={self.t1}, "+\
                          f"a2={self.a2}, b2={self.b2}, t2={self.t2})"

class SigmarSolution(ctypes.Structure):
    _fields_ = [
        ("n_moves", ctypes.c_uint),
    ]

    def __getitem__(self, i):
        # this keeps self in scope so long as a move obtained this way
        # is still in scope, ensuring the memory is not freed prematurely
        to_return = self.get_moves_array()[i]
        to_return._parent = self
        return to_return

    def get_moves_array(self):
        return ctypes.cast(
            ctypes.addressof(self) + ctypes.sizeof(SigmarSolution),
            ctypes.POINTER(ctypes.ARRAY(SigmarMove, self.n_moves))
        ).contents

    def __del__(self):
        _LIB.sigmarsolution_free(self)

    def __repr__(self):
        return f"SigmarSolution(n_moves={self.n_moves})"

    def __len__(self):
        return self.n_moves

class SigmarsGarden:
    def __init__(self):
        self._sg = _LIB.sigmarsgarden_init()

    def __del__(self):
        _LIB.sigmarsgarden_free(self._sg)

    def setTile(self, a, b, t):
        _LIB.sigmarsgarden_setTile(self._sg, a, b, t)

    def solve(self):
        sol = _LIB.sigmarsgarden_solve(self._sg)
        if not sol:
            return None
        return ctypes.cast(sol, ctypes.POINTER(SigmarSolution)).contents

_LIB = ctypes.cdll.LoadLibrary("./libsigmarsolver.so")

# Build the function prototypes
# void *sigmarsgarden_init();
_LIB.sigmarsgarden_init.restype = ctypes.c_void_p
_LIB.sigmarsgarden_init.argtypes = []
# void sigmarsgarden_free(void*);
_LIB.sigmarsgarden_free.restype = None
_LIB.sigmarsgarden_free.argtypes = [ctypes.c_void_p]
# void sigmarsgarden_setTile(void *p, const int a, const int b, const TileType type);
_LIB.sigmarsgarden_setTile.restype = None
_LIB.sigmarsgarden_setTile.argtypes = [ctypes.c_void_p, ctypes.c_int, ctypes.c_int, ctypes.c_int]
# SigmarSolution *sigmarsgarden_solve(const void*);
_LIB.sigmarsgarden_solve.restype = ctypes.POINTER(SigmarSolution)
_LIB.sigmarsgarden_solve.argtypes = [ctypes.c_void_p]
# void sigmarsolution_free(SigmarSolution*);
_LIB.sigmarsolution_free.restype = None
_LIB.sigmarsolution_free.argtypes = [ctypes.POINTER(SigmarSolution)]
# const char *sigmarsgarden_getTypeName(const TileType t);
_LIB.sigmarsgarden_getTypeName.restype = ctypes.c_char_p
_LIB.sigmarsgarden_getTypeName.argtypes = [ctypes.c_int]
