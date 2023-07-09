class Graphe:

    def new_node(self):
        node = len(self.G)
        self.G[node] = {}
        return node
    def add(self, c):
        node = self.new_node()
        while len(self.end) > 0:
            e = self.end.pop()
            self.G[e][c] = node
        self.end.add(node)
        return self

    def merge_add(self, G2):
        conv = {}
        for i in range(1,len(G2.G)):
            conv[i] = self.new_node()
        for i in G2.G:
            for c in G2.G.get(i):
                if i == 0:
                    for e in self.end:
                        self.G[e][c] = conv[G2.G.get(i).get(c)]
                else:
                    self.G[conv[i]][c] = conv[G2.G.get(i).get(c)]
        end = set()
        for e2 in G2.end:
            if e2 == 0:
                for e in self.end:
                    end.add(e)
            else:
                end.add(conv.get(e2))
        self.end = end
        return self

    def merge_or(self, G2):
        conv = {0:0}
        for i in G2.G:
            for c in G2.G.get(i):
                if not self.G.get(conv[i]).get(c, None) is None:
                    conv[self.G.get(conv[i]).get(c)] = self.G.get(conv[i]).get(c)
                else:
                    conv[G2.G.get(i).get(c)] = self.new_node()
                self.G[conv[i]][c] = conv[G2.G.get(i).get(c)]
        for e2 in G2.end:
            self.end.add(conv.get(e2))
        return self


        return self
    def __init__(self):
        self.G = {0: {}}
        self.end = set()
        self.end.add(0)

    def __str__(self):
        return "G: " + str(self.G) + "\nend: " + str(self.end)

