__import__ = [
    "_tokengetter",
    "_datagetter",
]

import operator as op
_tokengetter = op.itemgetter(0)
_datagetter = op.itemgetter(1)

