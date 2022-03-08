import random

with open("teste_generale.in", "w") as f:
    max_arr = [10000, 20000, 100000, 200000, 1000000, 2000000, 10000000, 20000000, 40000000, 50000000]
    n_arr = [100, 500, 1000, 5000, 5000, 10000, 1000000, 1000000, 1000000, 1000000]

    f.write(str(len(n_arr)) + "\n")

    for idx, n in enumerate(n_arr):
        f.write(str(n) + " ")
        f.write(str(max_arr[idx]) + "\n")

        t = [x for x in range(1, max_arr[idx] + 1)]
        random.shuffle(t)
        for x in range(0, n):
            f.write(str(t[x]) + " ")
        f.write("\n")
        print(idx)