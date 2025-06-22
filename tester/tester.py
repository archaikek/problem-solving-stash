import math
import subprocess

from gen import gen
from subprocess import run
from os import path


def square(x):
    return x * x


def dist(p1: tuple[int, int], p2: tuple[int, int]):
    return math.sqrt(square(p1[0] - p2[0]) + square(p1[1] - p2[1]))


def convert_input(in_str: str) -> tuple[int, int, list[tuple[int, int]]]:
    lines = in_str.splitlines()

    nk = lines[1].split(" ")
    n, k = int(nk[0]), int(nk[1])

    xy = []
    for i in range(2, len(lines)):
        temp = lines[i].split(" ")
        xy.append((int(temp[0]), int(temp[1])))

    return n, k, xy


def convert_output(out_str: str) -> list[int]:
    lines = out_str.splitlines()

    result = lines[1].split(" ")
    result.pop()
    return [int(x) for x in result]


def verify_results(xy: list[tuple[int, int]], sol: list[int], opt: list[int]) -> float:
    result_sol = result_opt = 0
    for i in range(len(xy)):
        dist_sol = dist_opt = 100000000

        for dst in sol:
            dist_sol = min(dist_sol, dist(xy[i], xy[dst]))
        result_sol = max(result_sol, dist_sol)

        for dst in opt:
            dist_opt = min(dist_opt, dist(xy[i], xy[dst]))
        result_opt = max(result_opt, dist_opt)
    # print(f"??? {result_sol} / {result_opt}")
    if (result_opt == 0):
        return 1 if result_sol == 0 else 2221
    return result_sol / result_opt


for i in range(10000):

    print(f"Running test {i}...")

    in_str = gen(i)
    out_str = run(["../x64/Debug/Core.exe", '-'],
                  input=in_str.encode(), stdout=subprocess.PIPE).stdout.decode()
    brute_str = run(["../x64/Debug/Core.exe", '-brute'],
                    input=in_str.encode(), stdout=subprocess.PIPE).stdout.decode()

    # print(f"IN:\n{in_str}\nSOL:\n{out_str}\nOPT:\n{brute_str}\n")

    _, _, xy = convert_input(in_str)
    sol = convert_output(out_str)
    opt = convert_output(brute_str)

    ratio = verify_results(xy, sol, opt)
    # print(f"ratio = {ratio}")
    if (ratio > 2):
        print(f"Error on test {i}: ratio was {ratio} > 2. Aborting.")
        break
    print(f"Finished test {i}. Ratio = {ratio}")