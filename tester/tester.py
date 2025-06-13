import subprocess

from gen import gen
from subprocess import run
from os import path


def convert_input(in_str: str) -> tuple[int, int, int, list[str], int]:
    lines = in_str.splitlines()
    k = int(lines[0])

    sizes = lines[1].split(" ")
    n = int(sizes[0])
    m = int(sizes[1])

    board = ["" for _ in range(n)]
    for i in range(n):
        board[i] = lines[i + 2]
    mode = int(lines[-1])
    # print(f"{k}\n{n} {m}\n{board}\n{mode}")
    return k, n, m, board, mode


def convert_output(out_str: str) -> tuple[int, list[str]]:
    lines = out_str.splitlines()

    result = int(lines[0])
    lines.pop(0)
    solution = []
    for line in lines:
        solution.append(line)
    return result, solution


def verify_output(in_str: str, out_str: str) -> bool:
    k, n, m, board, _ = convert_input(in_str)
    result, solution = convert_output(out_str)

    collected = [[False for _ in range(m)] for _ in range(n)]
    start = 0
    for i in range(m):
        if board[0][i] == 'S':
            start = i
            break

    found_result = 0
    row = 0
    col = start
    while True:
        if col > 0 and solution[row][col - 1] == 'R':
            if solution[row][col] == 'L':
                print("Backtracking not allowed.")
                return False
            col = col - 1
            collected[row][col] = True
            found_result = found_result + (1 if board[row][col] == '.' else 0)
        elif col < m - 1 and solution[row][col + 1] == 'L':
            if solution[row][col] == 'R':
                print("Backtracking not allowed.")
                return False
            col = col + 1
            collected[row][col] = True
            found_result = found_result + (1 if board[row][col] == '.' else 0)
        elif row < n - 1 and solution[row + 1][col] == 'U':
            row = row + 1
            collected[row][col] = True
            found_result = found_result + (1 if board[row][col] == '.' else 0)
        else:
            break

    if found_result != result:
        print("Result doesn't match the provided solution")
        return False

    for i in range(n):
        for j in range(m):
            if collected[i][j] == False and solution[i][j] != board[i][j]:
                print("Solution modified the board outside of its path")
                return False

    return True

for i in range(5000):
    # print(".", "")
    if (i % 25 == 0):
        print(f'Running test {i}...')
    in_str = gen(i)
    out_str = run(["../x64/Debug/Core.exe", '-'],
                  input=in_str.encode(), stdout=subprocess.PIPE).stdout.decode()
    if not verify_output(in_str, out_str):
        print(f"Error on test {i}: inconsistent answer. Aborting.")
        break

    brute_str = run(["../x64/Debug/Core.exe", '-brute'],
                  input=in_str.encode(), stdout=subprocess.PIPE).stdout.decode()
    result = int(out_str.splitlines()[0])
    solution = int(brute_str.splitlines()[0])
    if result != solution:
        print(f"Error on test {i}: better solution found. Aborting.")
        print(in_str)
        print(f"-> {brute_str}")
        break