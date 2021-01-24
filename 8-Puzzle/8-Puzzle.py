import math, re
from collections import deque
from copy import deepcopy
import time
    
class Setting:
    def __init__(obj, file_in='input.txt', file_out='output.txt', blank_char='0', h_function=0, input_type='comma'):
        obj.file_in = file_in           # input file name
        obj.file_out = file_out         # output file name
        obj.blank_char = blank_char     # The char represent blank
        obj.h_function = h_function     # which destance function to use
        obj.input_type = input_type     # if the input is one line comma separated or a matrix with empty line between goal

class Puzzle:
    def __init__(self, state: list, goal: list, setting=Setting()):
        self.state = state
        self.goal = goal 
        self.setting = setting

    def _index(self, b):
        for i, x in enumerate(self.state):
            if b in x:
                return (i, x.index(b))

    def move(self, to: tuple):
        target = deepcopy(self.state)
        x, y = self._index(self.setting.blank_char)
        i, j = to 
        target[x][y], target[i][j] = target[i][j], target[x][y]
        return target 

    def moves_list(self):
        x, y = self._index(self.setting.blank_char)
        possible = []
        if x-1 >= 0:                  # up
            possible.append((x-1, y))
        if x+1 < len(self.state):     # down
            possible.append((x+1, y))
        if y-1 >= 0:                  # left
            possible.append((x, y-1))
        if y+1 < len(self.state[x]):  # right
            possible.append((x, y+1))
        return possible

    def goal_index(self, b):   # return tuple index of element b in the goal puzzle
        for i, x in enumerate(self.goal):
            if b in x:
                return (i, x.index(b))

    def isGoal(self):
        return self.state == self.goal 

    def manhattan(self):   # using manhattan distance to estmate cost according to goal
        d = 0
        for i in range(len(self.state)):
            for j in range(len(self.state)):
                if self.state[i][j] != 0:     # not calculating blank to reduce cost
                    x, y = self.goal_index(self.state[i][j])
                    d += abs(x - i) + abs(y - j)
        return d

    def euclidean(self):   # Using Euclidean distance to estmate cost
        d = 0
        for x1 in range(len(self.state)):
            for y1 in range(len(self.state)):
                if self.state[x1][y1] != 0:
                    x2, y2 = self.goal_index(self.state[x1][y1])
                    d += int(math.sqrt(math.pow((x1-x2), 2) + math.pow((y1 - y2), 2)))
        return d            

    def write_output(self):
        with open(self.setting.file_out, 'a+') as f:
            f.write(self.print_state())
            f.close()

    def print_state(self):
        s = ""
        for i in self.state:
            for k in i:
                s += str(k) + " "     #debug
            s += "\n"
        s += "\n"
        return s

class Node:
    def __init__(self, data: Puzzle, parent=None):
        self.puzzle = data
        self.parent = parent
        if parent:
            self.g = parent.g +1
        else:
            self.g = 0

    def get_path(self):
        n, path = self, []
        while n:
            path.append(n)
            n = n.parent
        return reversed(path)

    def isGoal(self):
        return self.puzzle.isGoal()

    def move(self, to: tuple):
        return self.puzzle.move(to)

    def moves_list(self):
        return self.puzzle.moves_list()

    def h(self):                     # second thought   # debug
        return self.puzzle.manhattan() if self.puzzle.setting.h_function == 0 else self.puzzle.euclidean()

    def g(self):
        return self.g

    def f(self):
        return self.g + self.h()

    def print_state(self):
        return self.puzzle.print_state()

    def _str(self):
        return str(self)

class PuzzleTree:
    def __init__(self, root):
        self.root = root

    def A_star(self):
        goal, conf = self.root.goal, self.root.setting
        pQueue = deque([Node(self.root)])
        visted = set()
        visted.add(pQueue[0]._str())
        total, s = 1, 0
        while pQueue:
            pQueue = deque(sorted(list(pQueue), key=lambda node: node.f()))
            max_size = len(pQueue)
            node = pQueue.popleft()
            s += 1
            if node.isGoal():
                print("    Total node in queue: {:d},  total node expanded {:d}".format(total, s))
                return node.get_path()
            for i in node.moves_list():
                exten = node.move(i)
                leaf = Node(Puzzle(exten, goal, conf), node)
                if leaf._str() not in visted:
                    pQueue.append(leaf)
                    total += 1
            visted.add(node._str())

        #raise Exception("A* didn't find the solution!!")

    def BFS(self):
        goal, conf = self.root.goal, self.root.setting
        queue = deque([Node(self.root)])
        visted = set()
        visted.add(queue[0]._str())
        node = queue.popleft()
        total, s = 1, 0
        while node:
            if node.isGoal():
                print("    Total node in queue: {:d},  total node expanded {:d}".format(total, s))
                return node.get_path()
            for i in node.moves_list():
                t = Puzzle(node.move(i), goal, conf)
                c = Node(t, node)
                if c._str() not in visted:
                    queue.append(c)
                    total += 1
            visted.add(node._str())
            node = queue.popleft()
            s += 1
            
def read_state(conf:Setting):
    return read_input(conf.file_in) if conf.input_type == 'comma' else (matrix_input(conf.file_in))

def read_input(file_in):
    try:
        with open(file_in, 'r+') as f:
            state = format_input(f.readline())
            goal = format_input(f.readline())
            f.close()
            return state, goal
    except IOError as e:
        print(e)

def format_input(s): 
    return [s.strip('\n').split(',')[i:i+3] for i in range(0,9,3)]

def matrix_input(file_in):
    with open(file_in, 'r+') as f:
        state = ""
        for i in range(3):
            state += re.sub("\s+", ',',f.readline().strip('\n'))
            state += ','
        f.readline()
        goal = ""
        for i in range(3):
            goal += re.sub("\s+", ',',f.readline().strip('\n'))
            goal += ','
        f.close()
        return (format_input(state.rstrip(',')), format_input(goal.rstrip(',')))

def write_output(file_out, s):
        with open(file_out, 'a+') as f:
            f.write(s)
            f.close()

def print_state(state: list):
    s = ""
    for i in state:
        for k in i:
            s += str(k) + " "    # debug
        s += "\n"
    return s

def clear_output(conf: Setting):
    with open(conf.file_out, 'w') as f:
        f.write("")
        f.close()

def check(s, g):
    if len(s) != 3:
        return False
    if len(s) != len(g):
        return False
    for i in s:
        if len(i) != 3:
            return False
    return True

def A_star(tree: PuzzleTree, goal, conf: Setting):
    print("Solving with A* ...")
    t1 = time.perf_counter()
    path = tree.A_star()
    t2 = time.perf_counter()
    print("    find a solution path in   {:.5f}s\n".format(t2-t1))
    write_output(conf.file_out, "A*: \n\n")
    for i in path:
        i.puzzle.write_output()
        #print(i.print_state(), end='')
    """if j >= 6:
        #print("...")
        #print(print_state(goal), end='')
        write_output(conf.file_out, "...")
        path[-1].puzzle.write_output()"""
    return path

def BFS(tree: PuzzleTree, goal, conf: Setting):
    print("Solving with BFS ...")
    t1 = time.perf_counter()
    path = tree.BFS()
    t2 = time.perf_counter()
    print("    find a solution path in   {:.5f}s\n".format(t2-t1))
    write_output(conf.file_out, "BFS: \n\n")
    for i in path:
        i.puzzle.write_output()
    return path

def main():
    conf = Setting(input_type='matrix', h_function=0, blank_char='0')
    try:
        state, goal = read_state(conf)
        if not check(state, goal):
            raise Exception("input format is wrong")
        clear_output(conf);
    except Exception as e:
        print(e)
        return 
    p = Puzzle(state, goal, conf)
    g = Puzzle(goal, goal, conf)
    t = PuzzleTree(p)
    print("\nInitial state:\n{:s}".format(print_state(state)))
    p.write_output()
    print("Goal state:\n{:s}".format(print_state(goal)))
    g.write_output()
    try:
        # A* solver
        A_star(t, goal, conf)
        write_output(conf.file_out, "\n")
        # BFS solver
        BFS(t, goal, conf)
    except KeyboardInterrupt as e:
        print(e)
        return
    except:
        print("Something wrong")
        return
    print("\nOutput written in ", conf.file_out, "\n")


if __name__=="__main__":
    main()
