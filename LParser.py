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
        pos, G = self.C(pos, G)
        pos, G2 = self.S(pos)
        return pos, G.merge_add(G2)

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
            pos, G2 = self.B(pos)
            G.merge_or(G2)
            pos, G = self.C(pos, G)
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
                pos = self.eat(pos, '*')
                G.euclide()
            case '?':
                pos = self.eat(pos, '?')
                G.end.add(0)
            case '!': #! is equivale at AA*
                pos = self.eat(pos, '!')
                G.euclide_plus()
        return pos, G

    def show(self):
        self.graphe.show()
    def __init__(self, regex):
        self.regex = regex
        self.graphe = self.Z()

    def __str__(self):
        return self.regex


# Test
print("Test 2")
lg = LParser("(a + b)c*")
print(lg)
print(lg.graphe)
lg.show()


