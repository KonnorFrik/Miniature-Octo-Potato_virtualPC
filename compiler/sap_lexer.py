from pygments.lexer import RegexLexer, bygroups
from pygments import token


class SapLexer(RegexLexer):
    name = "SapLexer"
    filename = ["*.sap"]

    tokens = {
        "root": (
            (r"^\s*ld", token.Keyword),

            (r"^\s*add", token.Keyword),
            (r"^\s*sub", token.Keyword),
            (r"^\s*mul", token.Keyword),
            (r"^\s*div", token.Keyword),
            #(r"^\s*neg", token.Keyword),

            (r"^\s*and", token.Keyword),
            (r"^\s*or", token.Keyword),
            (r"^\s*xor", token.Keyword),
            (r"^\s*inv", token.Keyword),

            (r"^\s*hlt", token.Keyword),
            (r"0x[\d+abcdef]+", token.Number),
            (r"\d+", token.Number),

            (r"\s", token.Whitespace),
            (r"\#.*$", token.Comment),
        )
    }
