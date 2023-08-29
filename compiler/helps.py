__import__ = [
    "_tokengetter",
    "_datagetter",
    "is_hex",
]

import operator as op
_tokengetter = op.itemgetter(0)
_datagetter = op.itemgetter(1)
__hex_symbols = "0123456789abcdefABCDEF"

def is_hex(value: str):
    res = False
    if value.startswith("0x") and all([symb in __hex_symbols for symb in value[2:]]):
        res = True

    return res

