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

    def merge_add(self, G2):
        conv = {}
        for i in range(1,len(G2)):
            conv[i] = self.new_node()
        for i in G2:
            for c in G2.G.get(i):
                if i == 0:
                    for e in self.end:
                        self.G[e][c] = conv[G2.G.get(i).get(c)]
                else:
                    self.G[conv[i]][c] = conv[G2.G.get(i).get(c)]
        self.end = set()
        for e2 in G2.end:
            self.end.add(conv[e2])

    def merge_or(self, G2):
        #TODO
        pass
    def __init__(self):
        self.G = {0: {}}
        self.end = set()
        self.end.add(0)

