import subprocess

cpp_program = "./prog"
output_file = "time.txt"

subprocess.run(["make"])

numThread = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]

with open(output_file, "w"):
    pass

for i in range(len(numThread)):
    num = numThread[i]
    output = subprocess.run([cpp_program, str(num)], capture_output=True, text=True).stdout.strip()
    numbers_list = output.split("\n")
    list = [int(num) for num in numbers_list if num]
    print(list)
    # with open(output_file, "a") as f:
        # f.write(f"Threads={num}, AVG_Time: {(output)}\n")

subprocess.run(["make", "clean"])
