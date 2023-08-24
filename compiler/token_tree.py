import helps
import pygments as pgm


class Node:
    def __init__(self, token, value):
        self.token = token
        self.value = value
        self._left = None
        self._right = None

    @property
    def right(self):
        return self._right

    @right.setter
    def right(self, value):
        if not isinstance(value, type(self)):
            raise Exception("Children of tree must have type 'Node'")

        self._right = value

    @property
    def left(self):
        return self._left

    @left.setter
    def left(self, value):
        if not isinstance(value, type(self)):
            raise Exception("Children of tree must have type 'Node'")

        self._left = value

    def __str__(self):
        left_str = "\tleft->{!r}\n".format(self.left)
        right_str = "\tright->{!r}\n".format(self.right)
        main_str = repr(self) + "\n"
        result = main_str + left_str + right_str
        return result

    def __repr__(self):
        cls_name = type(self).__name__
        return "{}(token='{}', value='{}')".format(cls_name, self.token, self.value)

    def radd(self, value):
        if not isinstance(value, type(self)):
            raise Exception("Children of tree must have type 'Node'")
        right = self
        while right.right is not None:
            right = right.right

        right.right = value

    def ladd(self, value):
        if not isinstance(value, type(self)):
            raise Exception("Children of tree must have type 'Node'")
        left = self
        while left.left is not None:
            left = left.left

        left.left = value

    def last_left(self):
        left = self
        while left.left is not None:
            left = left.left

        return left

    def last_right(self):
        right = self
        while right.right is not None:
            right = right.right

        return right


def build_trees(rows) -> tuple:
    result = list()
    for row in rows:
        tree = build_tree(row)
        result.append(tree)

    return tuple(result)


def build_tree(row):
    # build head
    head = build_head(row[0])

    #resolve other
    for pair in row[1:]:
        insert(head, pair)

    return head


def create_node(pair) -> Node:
    res = None
    match pair:
        case ((pgm.token.Keyword as tkn_type, str() as tkn_str), (pgm.token.Number as tkn_oper_type, str() as operand_str)):
            res = Node(token=tkn_type, value=tkn_str)
            res.ladd(Node(token=tkn_oper_type, value=operand_str))

        case ((pgm.token.Keyword as tkn_type, str() as tkn_str),):
            res = Node(token=tkn_type, value=tkn_str)

        case _: #unreachable
            raise Exception(f"Unknown token found: '{tkn_str}:{operand_str}'")

    return res
