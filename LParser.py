
import subprocess, sys

from IPython.display import SVG

def str_to_svg(str):
    try:
        dot = subprocess.Popen(['dot', '-Tsvg'],
                               stdin=subprocess.PIPE,
                               stdout=subprocess.PIPE,
                               stderr=subprocess.PIPE)
    except FileNotFoundError:
        print("The command 'dot' seems to be missing on your system.\n"
              "Please install the GraphViz package "
              "and make sure 'dot' is in your PATH.", file=sys.stderr)
        raise
    stdout, stderr = dot.communicate(str.encode('utf-8'))
    if stderr:
        print("Calling 'dot' for the conversion to SVG produced the message:\n"
              + stderr.decode('utf-8'), file=sys.stderr)
    ret = dot.wait()
    if ret:
        raise subprocess.CalledProcessError(ret, 'dot')
    return stdout.decode('utf-8')

def _show(n, edges, directed=False, highlight=[]):
    gv = "digraph {" if directed else "graph {";
    gv += 'rankdir=LR\nnode[shape=circle,style=filled,fillcolor="#ffffaa"]\n'
    if directed:
        gv += 'edge[arrowhead=vee, arrowsize=.7]\n'
    for s in range(n):
        gv += str(s) + '\n'
    fmt = "{} -> {} {}\n" if directed else "{} -- {} {}\n"
    for e in edges:
        hl = "[color=red]" if (e in highlight) or (not directed and (e[1],e[0]) in highlight) else ""
        gv += fmt.format(*e, hl)
    gv += "}"
    display(SVG(str_to_svg(gv)))

def _parse_regexp(reg, edges, current=0, c=0, out=None, block=False):
    before = -1
    while c < len(reg):
        match reg[c]:
            case '+':
                if c == 0:
                    raise ValueError("Syntax error: '+' whitout a first argument")
                edges,c = _parse_regexp(reg, edges, before, c + 1, current)
            case '(':
                edges, c = _parse_regexp(reg, edges, current, c + 1,out=out, block=True)
                if c == len(reg) and reg[c - 1] != ')':
                    raise ValueError("Synthax error: '(' without a ')'")
            case ')':
                if not block:
                    raise ValueError("Synthax error: ')' without a '('")
                return edges, c + 1
            case _:
                if reg[c] != ' ':
                    if edges.get(current, None) is None:
                        edges[current] = {}
                    if block and reg[c + 1] == ')':
                        edges[current][reg[c]] = out
                        return edges, c + 1
                    if not out is None and not block:
                        edges[current][reg[c]] = out
                        return edges, c
                    next = current + 1
                    while not edges.get(next, -1) == -1:
                        next += 1
                    edges[next] = {}
                    edges[current][reg[c]] = next
                    before = current
                    current = next
        c += 1
    return edges, c




def parse_regexp(reg, edges):
    edges = _parse_regexp(reg, edges)
    return edges
class LParser:

    def __init__(self, regex):
        self.regex = regex
        self.edges,_ = parse_regexp(self.regex, {})

    def __str__(self):
        return self.regex

    def show(self):
        l = []
        edges = self.edges
        for i in range(len(edges)):
            for j in edges.get(i):
                l.append((i, self.edges.get(i).get(j)))
        _show(len(edges), l, True)
