from sap_lexer import SapLexer
from typing import Iterable
import token_tree
import operator as op
import pygments

instruction_code_map = {
    "ld": 0x01,
    "add": 0x11,
    "sub": 0x12,
    "mul": 0x13,
    "div": 0x14,
    "hlt": 0xff,
}

_tokengetter = op.itemgetter(0)
_datagetter = op.itemgetter(1)

def convert_to_rows(gen: Iterable) -> tuple[tuple[pygments.token._TokenType, str]]:
    """ Clear tokens from comments and whitespaces, splits tokens into lines """
    page = list()
    row = list()

    for pair in gen:
        is_whitespace = _tokengetter(pair) == pygments.token.Whitespace
        is_comment = _tokengetter(pair) == pygments.token.Comment

        if is_whitespace:
            if _datagetter(pair) == "\n":
                page.append(tuple(row))
                row.clear()
            continue

        if is_comment:
            continue

        row.append(pair)

    return tuple(page)


def error_validator(itr: Iterable):
    for pair in itr:
        if _tokengetter(pair) == pygments.token.Error:
            msg = "Unparsed value: '{}'"
            raise SyntaxError(msg.format(_datagetter(pair)))


def help_msg():
    print("Usage:")
    print("[your python] compiler.py [filename input] [filename output]")


def write_programm(bin_programm: Iterable[bytes], filename_out: str) -> int:
    writed = 0
    with open(filename_out, "wb") as file:
        for byte in bin_programm:
            file.write(byte)
            writed += 1

    return writed


#TODO compiler v2
# try convert str inst to bin immediately with mapping
# ? on exception KeyError and try convert to hex like data it is
# or check 'type' of instr (need or not data for this)
# Semantic Validation

def cmp_v2(tokens_splitted: Iterable[tuple[tuple, ...]]) -> tuple[bytes]:
    res = list()
    tree = list()
    for row in tokens_splitted:
        node = token_tree.create_node(row)
        tree.append(node)

    for node in tree:
        byte_instr = None
        byte_operand = None


        if node.token == pygments.token.Keyword:
            byte_instr = instruction_code_map[node.value]

            if node.value == "ld":
                if node.left.token == pygments.token.Number:
                    byte_operand = int(node.left.value, base=16)

        if byte_instr:
            res.append(byte_instr.to_bytes())

            if byte_operand:
                res.append(byte_operand.to_bytes())

    return res

def cmp_v1(tokens_splitted: Iterable[tuple[tuple, ...]]) -> tuple[bytes]:
    res = list()
    for row in tokens_splitted:
        match row:
            case ((_, str("ld") as instr), (_, str() as num_str)):
                #print("LD:", num_str, instruction_code_map[instr])
                res.append(instruction_code_map[instr].to_bytes())
                res.append(int(num_str, base=16).to_bytes())

            case ((_, str("add") as instr),):
                #print("ADD:", instruction_code_map[instr])
                res.append(instruction_code_map[instr].to_bytes())

            case ((_, str("sub") as instr),):
                #print("SUB:", instruction_code_map[instr])
                res.append(instruction_code_map[instr].to_bytes())

            case ((_, str("mul") as instr),):
                #print("MUL:", instruction_code_map[instr])
                res.append(instruction_code_map[instr].to_bytes())

            case ((_, str("div") as instr),):
                #print("DIV:", instruction_code_map[instr])
                res.append(instruction_code_map[instr].to_bytes())

            case ((_, str("hlt") as instr),):
                #print("HALT:", instruction_code_map[instr])
                res.append(instruction_code_map[instr].to_bytes())

    return tuple(res)


def compile(filename_in: str, filename_out: str):
    raw_data = open(filename_in, "r").read()
    tokens = tuple(SapLexer().get_tokens(raw_data))
    error_validator(tokens)
    tokens_splitted = convert_to_rows(tokens)


    bin_programm = cmp_v2(tokens_splitted)

    writed = write_programm(bin_programm, filename_out)

    print("Writed:", writed, "bytes to:", filename_out)

if __name__ == "__main__":
    import sys
    import argparse
    parser = argparse.ArgumentParser()
    parser.add_argument("file_in", help="Filepath with text programm")
    parser.add_argument("file_out", help="Filepath for compiled programm")
    args = parser.parse_args()

    filename_in = args.file_in
    filename_out = args.file_out

    compile(filename_in, filename_out)
