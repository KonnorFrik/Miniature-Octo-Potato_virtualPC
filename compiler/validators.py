from typing import Iterable
from helps import _tokengetter, _datagetter
import pygments
from instructions import *

__non_mem_accessable_instructions = [
    hlt_,
    inv_,
]

__non_operandable_instructions = [
    hlt_,
    inv_,
    sav_,
    swp_,
]

class SemanticError(Exception):
    ...

def error_validator(itr: Iterable):
    for pair in itr:
        if _tokengetter(pair) == pygments.token.Error:
            msg = "Unparsed value: '{}'"
            raise SyntaxError(msg.format(_datagetter(pair)))


def semantic_validator(pairs: Iterable):
    str_count = 1
    is_hlt = 0
    for pair in pairs:
        match pair:
            # "non operandable" num
            case ((pygments.token.Keyword, str() as instr),
                  (pygments.token.Number, str() as num)) if instr in __non_operandable_instructions:
                msg = "Line: {}: After '{}' cannot be number".format(str_count, instr)
                raise SemanticError(msg)

            # [hlt, inv] num
            case ((pygments.token.Keyword, str() as instr),
                  (pygments.token.Operator.Access, str()),
                  (pygments.token.Number, str() as num)) if instr in __non_mem_accessable_instructions:
                msg = "Line: {}: After '{}' cannot be number".format(str_count, instr)
                raise SemanticError(msg)

            # "all operandable" ___
            case ((pygments.token.Keyword, str() as instr),) if instr not in __non_operandable_instructions:
                msg = "Line {}: Missings operand after: {}".format(str_count, instr)
                raise SemanticError(msg)

            # "any" num $
            case ((pygments.token.Keyword, str() as instr),
                  (pygments.token.Number, str() as num),
                  (pygments.token.Operator.Access, str() as oper)):
                  msg = "Line: {}: Access operator: '{}' cannot be after number".format(str_count, oper)
                  raise SemanticError(msg)

            # hlt is used
            case ((pygments.token.Keyword, str("hlt")),):
                is_hlt = 1

        str_count += 1

    if not is_hlt:
        msg = "'hlt' instruction must be in programm"
        raise SemanticError(msg)
