from typing import Iterable
from helps import _tokengetter, _datagetter
import pygments
from instructions import *

__non_mem_accessable_instructions = [
    hlt_,
    inv_,
    mem_,
]

__special_operands = [
    mem_inc,
    mem_dec,
    mem_set,
]

__non_operandable_instructions = [
    hlt_,
    inv_,
    sav_,
    swp_,
    read_,
    write_,
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

            # "all operandable" without operand
            case ((pygments.token.Keyword, str() as instr),) if instr not in __non_operandable_instructions:
                msg = "Line {}: Missings operand after: {}".format(str_count, instr)
                raise SemanticError(msg)

            # "any" num $
            case ((pygments.token.Keyword, str() as instr),
                  (pygments.token.Number, str() as num),
                  (pygments.token.Operator.Access, str() as oper)):
                  msg = "Line: {}: Access operator: '{}' cannot be after number".format(str_count, oper)
                  raise SemanticError(msg)

            # special without operand
            case ((pygments.token.Keyword.Special, str() as instr),) if instr not in __non_operandable_instructions:
                msg = "Line: {}: Special instruction '{}' can only with special operands".format(str_count, instr)
                raise SemanticError(msg)

            # special with nonspecial-operand
            case ((pygments.token.Keyword.Special, str() as instr),
                  (_, str() as operand)) if operand not in __special_operands:# and instr not in __non_operandable_instructions:
                msg = "Line: {}: Special instruction '{}' used with wrong operand: '{}'".format(str_count, instr, operand)
                raise SemanticError(msg)

            # special with access operator (mem $num)
            case ((pygments.token.Keyword.Special, str() as instr),
                  (pygments.token.Operator.Access, str() as oper),
                  (_, str() as operand)) if operand not in __special_operands:
                msg = "Line: {}: Special instruction '{}' wrong used with Access Operator: '{}'".format(str_count, instr, oper)
                raise SemanticError(msg)

            # special with access operator (mem num$)
            case ((pygments.token.Keyword.Special, str() as instr),
                  (_, str() as operand),
                  (pygments.token.Operator.Access, str() as oper)) if operand not in __special_operands:
                msg = "Line: {}: Special instruction '{}' wrong used with Access Operator: '{}'".format(str_count, instr, oper)
                raise SemanticError(msg)

            # special with access operator (mem $'any')
            case ((pygments.token.Keyword.Special, str() as instr),
                  (pygments.token.Operator.Access, str() as oper),
                  (_, str() as operand)):
                msg = "Line: {}: Special instruction '{}' wrong used with Access Operator: '{}'".format(str_count, instr, oper)
                raise SemanticError(msg)

            # special with access operator (mem 'any'$)
            case ((pygments.token.Keyword.Special, str() as instr),
                  (_, str() as operand),
                  (pygments.token.Operator.Access, str() as oper)):
                msg = "Line: {}: Special instruction '{}' wrong used with Access Operator: '{}'".format(str_count, instr, oper)
                raise SemanticError(msg)

            # special read/write with inc/dec/set
            case ((pygments.token.Keyword.Special, str() as instr),
                  (pygments.token.Keyword.Special.Operand, str() as spec_operand)) if instr in __non_operandable_instructions:
                msg = "Line: {}: This special instruction '{}' can't be used with special operand '{}'".format(str_count, instr, spec_operand)
                raise SemanticError(msg)

            # hlt is used
            case ((pygments.token.Keyword, str("hlt")),):
                is_hlt = 1

        str_count += 1

    if not is_hlt:
        msg = "'hlt' instruction must be in programm"
        raise SemanticError(msg)
