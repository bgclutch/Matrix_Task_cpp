import subprocess
import glob
import os

matrix = "../../build/matrix/./matrix"

input_dir = "input_data/"
output_file = "result.out"

test_files = sorted(glob.glob(os.path.join(input_dir, "test_*.in")))

with open(output_file, "w") as fout:
    for file in test_files:
        with open(file, "r") as fin:
            file_w_ext = os.path.basename(file)
            f_to_write = os.path.splitext(file_w_ext)[0]
            fout.write(f_to_write + ": ")
            run = subprocess.run(
                [matrix],
                stdin=fin,
                text=True,
                capture_output=True
            )
            if run.returncode != 0:
                fout.write(f"ERROR: {run.stderr}\n")
            else:
                fout.write(run.stdout)