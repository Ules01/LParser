import Graphe

class LParser:

    def token(self, pos):
        # Go search the first char != ' ' from the position pos int the regex
        while pos < len(self.regex):
            if self.regex[pos] != ' ':
                return self.regex[pos], pos
            pos += 1
        if pos == len(self.regex):
            return '$', pos
        raise ValueError("Error: reading out of the regex")

    def eat(self, pos, search):
        c, pos = self.token(pos)
        if c != search:
            raise ValueError("Synthax Error: wasn't expecting " + c + ", was expecting " + search + " at " + str(pos))
        return pos + 1
    def Z(self, pos=0):
        pos = self.S(pos)
        self.eat(pos, '$')


    """
    Set of parsing rule
    If the synthax is incorect, it will throw an error
    """
    def S(self,pos):
        c, pos = self.token(pos)
        if not c in ")!?*+$":
            return self.A(pos)
        return pos

    def A(self, pos):
        pos = self.B(pos)
        return self.C(pos)

    def B(self, pos):
        c, pos = self.token(pos)
        if c == '(':
            pos = self.eat(pos, '(')
            pos = self.A(pos)
            pos = self.eat(pos, ')')
        else:
            pos = self.D(pos)
        return self.E(pos)

    def C(self,pos):
        c, pos = self.token(pos)
        if c == '+':
            pos = self.eat(pos, '+')
            return self.A(pos)
        else:
            return self.S(pos)

    def D(self, pos):
        c, pos = self.token(pos)
        if c == '.':
            return self.eat(pos, '.')
        else:
            if c not in "().!?*+$":
                return self.eat(pos, c)

    def E(self, pos):
        c, pos = self.token(pos)
        match c:
            case '*':
                return self.eat(pos, '*')
            case '?':
                return self.eat(pos, '?')
            case '!': #! is equivale at AA*
                return self.eat(pos, '!')
        return pos

    def __init__(self, regex):
        self.regex = regex
        self.graphe = Graphe.Graphe()
        self.Z()

    def __str__(self):
        return self.regex


# Test 2
lg = LParser("a + (b) *")
print(lg)

