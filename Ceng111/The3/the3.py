
from math import exp
def relu(x):
    a = max(0,x)
    return a
def sigmoid(x):
    if x <= -700:
        return 0
    elif x >= 700:
        return 1
    else:
        sig = 1 / (1 + exp(1)**-x)
        return sig
def forward_pass(Network,X):
    cycle = 1
    a = 0
    n1 = 0
    layer = []
    layer2 = []
    while cycle < len(Network):
        if cycle == 1 and Network[cycle][0] == 'r':
            for j in Network[0][1]:
                for k in j:
                    a += k * X[n1]
                    n1 = n1 + 1
                n1 = 0
                layer.append(relu(a))
                a = 0
            cycle += 2
        elif cycle == 1 and Network[cycle][0] == 's':
            for j in Network[0][1]:
                for k in j:
                    a += k * X[n1]
                    n1 = n1 + 1
                n1 = 0
                layer.append(sigmoid(a))
                a = 0
            cycle += 2
        else:
            if Network[cycle][0] == 'r':
                for j in Network[cycle-1][1]:
                    for k in j:
                        a += k * layer[n1]
                        n1 = n1 + 1
                    n1 = 0
                    layer2.append(relu(a))
                    a = 0
                layer.clear()
                layer = layer2[:]
                layer2 = []
                cycle += 2
            else:
                for j in Network[cycle-1][1]:
                    for k in j:
                        a += k * layer[n1]
                        n1 = n1 + 1
                    n1 = 0
                    layer2.append(sigmoid(a))
                    a = 0
                layer.clear()
                layer = layer2[:]
                layer2 = []
                cycle += 2
    for i in Network[cycle-1][1]:
        for k in i:
            a += k *layer[n1]
            n1 = n1 + 1
        n1 = 0
        layer2.append(a)
        a = 0
    return layer2
