from PIL import Image
from collections import deque
from time import perf_counter as counter
from heapq import heappop as hpop
from heapq import heappush as hpush
import matplotlib.pyplot as plt
import copy, math, os, platform

initial = (56,37)
target = (800,433)
images = []
#flag = 0                # 0 for manhattan, 1 for euclidean

group = 10

image_path = "./SmallMaze.jpg" 

""" CSC 361 term project  by $group  
          Maze navigation           """

class image:
    def __init__(self, img: Image, initial=(0,0), target=(0,0)):
        self.img       = img
        self.initial   = initial
        self.target    = target
        self.pixels    = img.load()
        self.w, self.h = img.size

class Node:
    def __init__(self, d: tuple, parent=None):
        self.xy     = d
        self.parent = parent
        if parent:
            self.g = parent.g + 1
        else:
            self.g = 0
        self.h = self.h()
        self.f = self.h + self.g

    def h(self):
        return h(self.xy)

    def goal(self):
        return self.xy == target

    def __lt__(self, other):
        return self.f < other.f

def manhattan(xy):
    """ manhattan distance """
    x, y   = xy
    x2, y2 = target
    return abs(x - x2) + abs(y - y2)

def euclidean(xy):
    """ euclidean distance """
    x, y   = xy
    x2, y2 = target
    return math.sqrt(abs(x - x2)**2 + abs(y - y2)**2)

def legal(rgb):
    return rgb > (254,254,254)

def move_list(xy):
    x, y = xy
    return [(x-1,y+1),   # down left               # debug -> add more
            (x-1,y),     # left
            (x-1,y-1),   # up left
            (x,y-1),     # up
            (x+1,y-1),   # up right
            (x+1,y),     # right
            (x+1,y+1),   # down right
            (x,y+1)]     # down

def BFS(img: image):
    """ BFS """
    queue = deque([Node(initial)])
    size, expand, mx, front = 1, 0, 0, 0
    pixels = img.pixels
    w, h = img.w, img.h
    while queue:
        node = queue.popleft()
        expand += 1
        if node.g > mx:
            mx = node.g
        if flag[-1] and size % 7000 == 0:
            images.append(copy.copy(img.img))     # debug -> Take too long
        if node.goal():
            print("  Done")    # debug
            return node, expand, mx, front
        for i in move_list(node.xy):
            x, y = i
            if x >= 0 and x < w and y >= 0 and y < h and legal(pixels[i]):
                pixels[i] = (90,90,90)
                queue.append(Node(i, node))
                size += 1
        if len(queue) > front:
            front = len(queue)
    print("NO SOLUTION")
    exit()

def DFS(img: image):
    """ DFS """
    stack = deque([Node(initial)])
    size, expand, mx, front = 1, 0, 0, 0
    pixels = img.pixels
    w, h = img.w, img.h
    while stack:
        node = stack.popleft()
        expand += 1
        if node.g > mx:
            mx = node.g
        if flag[-1] and size % 3000 == 0:
            images.append(copy.copy(img.img))     # debug -> Take too long
        if node.goal():
            print("  Done")    # debug
            return node, expand, mx, front
        for i in move_list(node.xy):
            x, y = i
            if x >= 0 and x < w and y >= 0 and y < h and legal(pixels[i]):
                pixels[i] = (90,90,90)
                stack.appendleft(Node(i, node))
                size += 1
        if len(stack) > front:
            front = len(stack)
    print("NO SOLUTION")
    exit()

def A_star(img: image):
    """ A* search """
    pq = [Node(initial)]
    size, expand, mx, front = 1, 0, 0, 0
    pixels = img.pixels
    w, h = img.w, img.h
    while pq:
        node = hpop(pq)
        expand += 1
        if node.g > mx:
            mx = node.g
        if flag[-1] and size % 7000 == 0:
            images.append(copy.copy(img.img))     # debug -> take time fix: add 0.1 sec
        if node.goal():
            print("  Done")    # debug
            return node, expand, mx, front
        for i in move_list(node.xy):
            x, y = i
            if x >= 0 and x < w and y >= 0 and y < h and legal(pixels[i]):
                pixels[i] = (90,90,90)
                hpush(pq, Node(i, node))
                size += 1
        if len(pq) > front:
            front = len(pq)
    print("NO SOLUTION")
    exit()

def Greedy(img: image):
    """ Greedy search """
    pq = [(0,Node(initial))]
    size, expand, mx, front = 1, 0, 0, 0
    pixels = img.pixels
    w, h = img.w, img.h
    while pq:
        node = hpop(pq)[-1]
        expand += 1
        if node.g > mx:
            mx = node.g
        if flag[-1] and size % 7000 == 0:
            images.append(copy.copy(img.img))     # debug -> take time fix: add 0.1 sec
        if node.goal():
            print("  Done")    # debug
            return node, expand, mx, front
        for i in move_list(node.xy):
            x, y = i
            if x < w and y < h and legal(pixels[i]):
                pixels[i] = (90,90,90)
                n = Node(i, node)
                hpush(pq, (n.h, n))
                size += 1
        if len(pq) > front:
            front = len(pq)
    print("NO SOLUTION")
    exit()

d = {0: manhattan, 1: euclidean}   # Acording to flag in main
def h(xy):
    if not flag[0] in d:
        print("flag NOT in h() methids ")
        exit()
    return d[flag[0]](xy)

def show_path(pixels, path: Node):
    n = path
    while n:
        pixels[n.xy] = (255,0,0)
        n = n.parent

def searching(func, attr: Image):
    print("""{} {} {}""".format("-"*5, func.__name__,"-"*5))
    t1 = counter()
    path, expand, mx, front = func(image(attr))
    t2 = counter()
    print("  Find solution path in  {:.4f}s\n   Total expanded nodes  {}\n   Max queue size        {}\n   Path cost is          {}\n   Maximum depth         {}\n".format(t2-t1, expand, front, path.g, mx))
    return path

def main():
    global flag 
    flag = (0,0)       # First bit: 0->manhattan, 1->euclidean # second bit: 0->create GIF, 1->Don't
    search = {0: BFS, 1: DFS, 2: A_star, 3: Greedy} # dictionary of searching strategies

    try:
        for i in range(3):
            #os.system("cls" if platform.system().lower() == 'windows' else "clear")   # debug take time
            os.system("clear")
            c = banner()
            if c in search:
                break
            print("Wring input!!")
        if i == 2:
            exit()
        m, g = input("Manhattan or Euclidean? [M:e] "), input("Create GIF? [y:N] ")
        flag = (1 if m == "e" or m == "E" else 0,
                1 if g == "y" or g == "Y" else 0)
    except Exception as e:
        print(e)
        exit()

    print("\nworking")
    img = Image.open(image_path)
    path = searching(search[c], img)

    if flag[-1]:        # create GIF for the search
            img.save(fp=search[c].__name__+".gif", format='GIF', append_images=images,
             save_all=True, duration=150, loop=0)                 

    img = Image.open(image_path)                # Reopen the image, clean start
    pixels = img.load()                         # Load imge pixels 
    show_path(pixels, path)                     # coloring the path with red
    plt.imshow(img)                             # build 
    plt.show()                                  # show

def banner():
    print("\n  {}\n/ Maze navigation \\\n\  by group #{}   /\n  {}\n Which search strategies?\n   0) BFS\n   1) DFS\n   2) A*\n   3) Greedy".format("-"*15,group, "-"*15))
    return int(input(" >>> "))

if __name__=="__main__":
    main()

