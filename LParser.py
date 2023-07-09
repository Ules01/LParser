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
        pos, G = self.S(pos)
        self.eat(pos, '$')
        return G

    """
    Set of parsing rule
    If the synthax is incorect, it will throw an error
    """
    def S(self,pos):
        c, pos = self.token(pos)
        if not c in ")!?*+$":
            return self.A(pos)
        return pos, Graphe.Graphe()

    def A(self, pos):
        pos, G = self.B(pos)
        return self.C(pos, G)

    def B(self, pos):
        c, pos = self.token(pos)
        if c == '(':
            pos = self.eat(pos, '(')
            pos, G = self.A(pos)
            pos = self.eat(pos, ')')
        else:
            pos, G = self.D(pos)
        return self.E(pos, G)

    def C(self,pos, G):
        c, pos = self.token(pos)
        if c == '+':
            pos = self.eat(pos, '+')
            pos, G2 = self.A(pos)
            G.merge_or(G2)
        else:
            pos, G2 = self.S(pos)
            G.merge_add(G2)
        return pos, G

    def D(self, pos):
        c, pos = self.token(pos)
        G = Graphe.Graphe()
        if c == '.':
            return self.eat(pos, '.'), G.add(c)
        else:
            if c not in "().!?*+$":
                return self.eat(pos, c), G.add(c)

    def E(self, pos, G):
        c, pos = self.token(pos)
        match c:
            case '*':
                return self.eat(pos, '*')
            case '?':
                return self.eat(pos, '?')
            case '!': #! is equivale at AA*
                return self.eat(pos, '!')
        return pos, G

    def __init__(self, regex):
        self.regex = regex
        self.graphe = self.Z()

    def __str__(self):
        return self.regex


# Test 2
lg = LParser("a(bc) + d")
print(lg)
print(lg.graphe)


