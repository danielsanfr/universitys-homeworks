import argparse
import numpy as np

def parse_args():
    parser = argparse.ArgumentParser()
    parser.add_argument("-q", "--question", type=str, help="")
    parser.add_argument("-a", "--alpha", type=float, help="")
    parser.add_argument("-b", "--beta", type=float, help="")
    parser.add_argument("-y", "--gama", type=float, help="")
    return parser.parse_args()


def questionA(args, showResult=True):
    a = np.deg2rad(args.alpha)
    b = np.deg2rad(args.beta)
    y = np.deg2rad(args.gama)

    ca, sa = np.cos(a), np.sin(a)
    cb, sb = np.cos(b), np.sin(b)
    cy, sy = np.cos(y), np.sin(y)

    Rz = np.matrix([[ca, -sa, 0], [sa, ca, 0], [0, 0, 1]])
    Ry = np.matrix([[cb, 0, sb], [0, 1, 0], [-sb, 0, cb]])
    Rx = np.matrix([[1, 0, 0], [0, cy, -sy], [0, sy, cy]])

    Rzy = np.matmul(Rz, Ry)
    Rzyx = np.matmul(Rzy, Rx)
    IRzyx = np.linalg.inv(Rzyx)
    TRzyx = np.matrix.transpose(Rzyx)

    Rz = np.matrix([[cy, -sy, 0], [sy, cy, 0], [0, 0, 1]])
    Ry = np.matrix([[cb, 0, sb], [0, 1, 0], [-sb, 0, cb]])
    Rx = np.matrix([[1, 0, 0], [0, ca, -sa], [0, sa, ca]])

    Rxy = np.matmul(Rx, Ry)
    Rxyz = np.matmul(Rxy, Rz)

    if showResult:
        print("Rzyx inverse:")
        print(IRzyx)
        print("Rzyx transposed:")
        print(TRzyx)
        print("Rxyz:")
        print(Rxyz)

    return Rzyx


def questionB(args, showResult=True):
    Rzyx = questionA(args, False)
    b = np.arcsin(-Rzyx.item((2, 0)))
    y = np.arcsin(Rzyx.item((2, 1)) / np.cos(b))
    a = np.arcsin(Rzyx.item((1, 0)) / np.cos(b))

    if showResult:
        print("alpha:")
        print(np.rad2deg(a))
        print("beta:")
        print(np.rad2deg(b))
        print("gama:")
        print(np.rad2deg(y))


def questionC(args, showResult=True):
    b = np.deg2rad(20)
    cb, sb = np.cos(b), np.sin(b)
    Ry = np.matrix([[cb, 0, sb], [0, 1, 0], [-sb, 0, cb]])
    P2 = np.matrix([[1], [0], [1]])
    P1 = np.linalg.lstsq(Ry, P2)[0]

    if showResult:
        print("P2 informed:")
        print(P2)
        print("P1 calculated:")
        print(P1)
        print("P2 calculated:")
        print(np.matmul(Ry, P1))


def main():
    args = parse_args()
    if args.question == 'a':
    	questionA(args)
    elif args.question == 'b':
    	questionB(args)
    elif args.question == 'c':
    	questionC(args)
    else:
        print("Without this question")

if __name__ == '__main__':
    main()

