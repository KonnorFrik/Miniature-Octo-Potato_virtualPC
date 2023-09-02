from pygments.lexer import RegexLexer, bygroups
from pygments import token


class SapLexer(RegexLexer):
    name = "SapLexer"
    filename = ["*.sap"]

    tokens = {
        "root": (
            (r"^\s*ld", token.Keyword),
            (r"^\s*sav", token.Keyword),
            (r"^\s*swp", token.Keyword),

            (r"^\s*add", token.Keyword),
            (r"^\s*sub", token.Keyword),
            (r"^\s*mul", token.Keyword),
            (r"^\s*div", token.Keyword),

            (r"^\s*and", token.Keyword),
            (r"^\s*or", token.Keyword),
            (r"^\s*xor", token.Keyword),
            (r"^\s*inv", token.Keyword),

            (r"^\s*jmp", token.Keyword),
            (r"^\s*jez", token.Keyword),
            (r"^\s*jnz", token.Keyword),

            (r"^\s*hlt", token.Keyword),

            (r"0x[0-9abcdef]+", token.Number),
            (r"\d+", token.Number),

            (r"\$", token.Operator.Access),

            (r"\s", token.Whitespace),
            (r"\#.*$", token.Comment),
        )
    }
