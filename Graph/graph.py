"""
    CSC 311 Project
    Phase 2
"""
__author__ = '0x0faisal'

filename = 'input.txt'

from matplotlib import pyplot as plt
import networkx as nx
from itertools import cycle
from collections import deque

class Graph:
    def __init__(self, edges):
        self.edges = edges
        self.nodes = set([i[0] for i in edges] + [i[1] for i in edges])

    def weight(self, u, v):
        for i in self.edges:
            if i[:-1] == (u,v) or i[:-1] == (v,u):
                return int(i[-1])

    def nighbors(self, u):
        s = []
        for i in self.edges:
            if i[0] == u:
                s.append(int(i[1]))
            elif i[1] == u:
                s.append(int(i[0]))
        return s

def read(filename):
    with open(filename, 'r+') as f:
        s = f.read()
        f.close()
        return s

def Format(o):
    s = o.split('\n')[:-1]
    v = int(s[0])
    xy = {}
    xy = xy.fromkeys(["V"+str(i) for i in range(v)])
    xy = {i-1: (int(s[i].split(',')[0]), int(s[i].split(',')[1])) for i in range(1, v+1)}
    e = []
    for i in range(v+1, len(s)):
        e.append((int(s[i].split(',')[0]),int(s[i].split(',')[1]),int(s[i].split(',')[2])))
    return v, xy, e

def build(v, xy, e):
    g = nx.Graph()
    g.add_nodes_from(xy)
    g.add_weighted_edges_from(e)
    pos = nx.spring_layout(g, seed=31)
    #nodes = nx.draw_networkx_nodes(g, pos, node_color ='white', node_size=600)
    nodes = nx.draw_networkx_nodes(g, pos, node_color='black', node_size=700)
    nodes.set_edgecolor("black")
    nx.draw_networkx_edges(g, pos)
    nx.draw_networkx_labels(g, pos, font_color='w')
    nx.draw_networkx_edge_labels(g, pos, edge_labels=nx.get_edge_attributes(g, 'weight'))
    return g

def dijkstra(g: Graph, frm):
    dist, road = {}, {}
    for i in g.nodes:
        dist[i] = float("inf")
    dist[frm] = 0
    S = set()
    Q = deque(g.nodes)
    while Q:
        u = min(list(Q), key=lambda n: dist[n])
        S.add(u)
        for v in g.nighbors(u):
            if v in S:
                continue
            if dist[v] > dist[u] + g.weight(u, v):
                dist[v] = dist[u] + g.weight(u, v)
                road[v] = u
        Q.remove(u)
    return road, dist

def shortest(g: Graph):
    print("\nFind shotest between")
    try:
        v1 = int(input("\tV: "))
        v2 = int(input("\tV: "))
    except KeyboardInterrupt as e:
        print(e)
        exit(1)
    except Exception as e:
        print("wrong input: {}".format(e))
        exit(1)
    print("")
    nodes = g.nodes
    if v1 not in nodes or v2 not in nodes:
        print("Node not found: Either source {} or target {} is not in Graph".format(v1,v2))
        exit(1)
    e, dist = dijkstra(g, v1)
    path = []
    v = v2
    while 1:
        n = e[v]
        path.append((v, n))
        if n == v1:
            break
        v = n
    print("Shrtest path cost to {} is  {}".format(v2, dist[v2]))
    return path

def main():
    v, xy, e = Format(read(filename))
    build(v, xy, e)
    plt.tight_layout(h_pad=4.0, w_pad=3.0)
    plt.show()
    # Find shorest
    g = Graph(e)
    edges = shortest(g)
    G = build(v, xy, e)
    pos = nx.spring_layout(G, seed=31)
    nx.draw_networkx_edges(G, pos, edgelist=edges, edge_color='red', width=6)
    plt.tight_layout(h_pad=4.0, w_pad=3.0)
    plt.show()

if __name__=="__main__":
    main()
