from typing import Iterable
from helps import _tokengetter, _datagetter
import pygments


def error_validator(itr: Iterable):
    for pair in itr:
        if _tokengetter(pair) == pygments.token.Error:
            msg = "Unparsed value: '{}'"
            raise SyntaxError(msg.format(_datagetter(pair)))


def semantic_validator(pairs: Iterable):
    str_count = 1
    for pair in pairs:
        match pair:
            case ((pygments.token.Keyword, str("hlt") as instr), (pygments.token.Number, str() as num)):
                msg = "Line: {}: After '{}' cannot be number".format(str_count, instr)
                raise SyntaxError(msg)

            case ((pygments.token.Keyword, str() as instr ),) if instr != "hlt":
                msg = "Line {}: Missings operand after: {}".format(str_count, instr)
                raise SyntaxError(msg)

        str_count += 1
