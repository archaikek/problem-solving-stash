import random
import math


def gen(seed: int) -> str:
    random.seed(seed)

    n = random.randint(2, 10)
    k = random.randint(1, n - 1)
    result = f"1\n{n} {k}\n"
    for i in range(n):
        x = random.randint(-10, 10)
        y = random.randint(-10, 10)
        result += f"{x} {y}\n"
    return result

# print(gen(15))