import random
import math


def gen(seed: int) -> str:
    random.seed(seed)

    n = random.randint(2, 5)
    m = random.randint(2, 5)
    k = random.randint(2, max(2, (n * m) // 2))
    rocks = random.randint(1, (n * m) // 2)
    start = random.randint(0, m - 1)

    board = [['.' for _ in range(m)] for _ in range(n)]
    for i in range(rocks):
        row = random.randint(0, n - 1)
        col = random.randint(0, m - 1)
        board[row][col] = '@'
    board[0][start] = 'S'

    result = f"{k}\n{n} {m}\n"
    for i in range(n):
        result = result + f"{''.join(board[i])}\n"
    print(result)
    return f"{result}1"

gen(121)