#! /usr/local/bin/python3

from sap_lexer import SapLexer
from typing import Iterable
from helps import is_hex, _tokengetter, _datagetter
from instructions import *
import validators
import token_tree
import operator as op
import pygments

#_tokengetter = op.itemgetter(0)
#_datagetter = op.itemgetter(1)

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


#TODO
# try convert str inst to bin immediately with mapping
# ? on exception KeyError and try convert to hex like data it is
# or check 'type' of instr (is need data for this)
# Semantic Validation

def process_node(node) -> tuple[int, int]:
    byte_instr = None
    byte_operand_left = None

    if node.token == pygments.token.Keyword:
        byte_instr = instruction_code_map[node.value]

        if node.left is not None:
            base_ = None

            if is_hex(node.left.value):
                base_ = 16

            elif node.left.value.isdigit():
                base_ = 10

            else:
                raise Exception("Unknown type of operand: {}".format(node.left.value))

            byte_operand_left = int(node.left.value, base=base_)


    return byte_instr, byte_operand_left


def cmp_v2(tokens_splitted: Iterable[tuple[tuple, ...]]) -> tuple[bytes]:
    res = list()
    tree = list()
    for row in tokens_splitted:
        node = token_tree.create_node(row)
        tree.append(node)

    for node in tree:
        #print(node)
        byte_instr, byte_operand_left = process_node(node)
        try:
            if byte_instr:
                res.append(byte_instr.to_bytes())

                if byte_operand_left or node.left is not None:
                    res.append(byte_operand_left.to_bytes())

                #if byte_operand_right:
                    #res.append(byte_operand_right.to_bytes())
        except OverflowError as err:
            msg = "Maximum number is 255 (0xff)"
            raise OverflowError(msg) from err

    #print(res)
    return res


def compile(filename_in: str, filename_out: str):
    raw_data: str = open(filename_in, "r").read()
    tokens: tuple = tuple(SapLexer().get_tokens(raw_data))
    validators.error_validator(tokens)
    tokens_splitted = convert_to_rows(tokens)
    #for t in tokens_splitted:
        #print(t)
    validators.semantic_validator(tokens_splitted)


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
