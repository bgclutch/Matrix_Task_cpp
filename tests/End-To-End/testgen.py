import numpy
import random
import os

path = "input_data/"
os.makedirs(path, exist_ok=True)

def make_matrix_with_det(det_val, n):
    A = numpy.eye(n)
    A[numpy.arange(n), numpy.arange(n)] = numpy.random.randint(1, 7, size=n)
    det_now = numpy.linalg.det(A)
    scale = (det_val / det_now) ** (1 / n)
    A *= scale
    return A

def apply_random_row_ops(A, num_ops):
    n = A.shape[0]
    for _ in range(num_ops):
        op = random.choice(["add_row", "swap_rows", "add_col"])
        if op == "add_row":
            i, j = random.sample(range(n), 2)
            k = random.uniform(-3, 3)
            A[i] += k * A[j]
        elif op == "swap_rows":
            for _ in range(2):
                i, j = random.sample(range(n), 2)
                A[[i, j]] = A[[j, i]]
        elif op == "add_col":
            i, j = random.sample(range(n), 2)
            k = random.uniform(-3, 3)
            A[:, i] += k * A[:, j]
    return A

for test_number in range(4):
    test_size = random.randint(2, 10)
    A = numpy.random.uniform(-300, 300, size=(test_size, test_size))
    filename = os.path.join(path, f"test_{test_number+1:02}.in")
    with open(filename, 'w') as f:
        f.write(f"{test_size}\n")
        for row in A:
            f.write(" ".join(map(str, row)) + "\n")

for test_number in range(4, 6):
    test_size = random.randint(5, 15)
    A = make_matrix_with_det(42, test_size)
    apply_random_row_ops(A, random.randint(30, 100))
    filename = os.path.join(path, f"test_{test_number+1:02}.in")
    with open(filename, 'w') as f:
        f.write(f"{test_size}\n")
        for row in A:
            f.write(" ".join(map(str, row)) + "\n")

for test_number in range(6, 9):
    test_size = random.randint(5, 15)
    det_val = random.randint(2, 1000)
    A = make_matrix_with_det(det_val, test_size)
    apply_random_row_ops(A, random.randint(30, 100))
    filename = os.path.join(path, f"test_{test_number+1:02}.in")
    with open(filename, 'w') as f:
        f.write(f"{test_size}\n")
        for row in A:
            f.write(" ".join(map(str, row)) + "\n")

test_size = 100
A = numpy.random.uniform(-300, 300, size=(test_size, test_size))
filename = os.path.join(path, "test_10.in")
with open(filename, 'w') as f:
    f.write(f"{test_size}\n")
    for row in A:
        f.write(" ".join(map(str, row)) + "\n")
