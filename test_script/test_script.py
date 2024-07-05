import subprocess


def run_echo(input_data):
    process = subprocess.Popen(
        ['/Users/anastasia_d/CLionProjects/Interpreter-implementation/cmake-build-debug/Interpreter_implementation'],
        stdin=subprocess.PIPE,
        stdout=subprocess.PIPE,
        stderr=subprocess.PIPE,
        text=True
    )
    stdout, stderr = process.communicate(input_data)
    return stdout.strip(), stderr.strip()


def test_echo():
    tests = [
        {
            "input": "5 + 3 * 2\n",
            "expected_output": "11"
        },
        {
            "input": "max(5, 2)\n",
            "expected_output": "5"
        },
        {
            "input": "min(3, 4)\n",
            "expected_output": "3"
        },
        {
            "input": "max(min(3 * 2, 2), 2)\n",
            "expected_output": "2"
        },
        {
            "input": "15 + (345 - 300 / 10) + min(10, max(3 * 2, 2))\n",
            "expected_output": "336"
        },
        {
            "input": "max(2*5, 4/4) * min(2, 4-1) / (3 + 2)\n",
            "expected_output": "4"
        },
        {
            "input": "var abc = min(3, 7-5)\nabc+10\n",
            "expected_output": "12"
        },
        {
            "input": "var a = 1+2*(2+5)\na+10*a\n",
            "expected_output": "165"
        },
        {
            "input": "def myfunc(c, d) { min(c, d) + max(c, d) }\nmyfunc(3, 4)\n",
            "expected_output": "7"
        },
        {
            "input": "def myfunc(c, d) { c * d + max(c, d) }\nmyfunc(5, 6)\n",
            "expected_output": "36"
        }
    ]

    for test in tests:
        input_data = test["input"]
        expected_output = test["expected_output"]
        output, error = run_echo(input_data)
        if error:
            print(f"Test failed for input:{input_data}")
            print(f"Error:{error}")
        elif output.strip() != expected_output:
            print(f"Test failed for input:{input_data}")
            print(f"Expected:{expected_output}")
            print(f"Got:{output}")
        else:
            print(f"Test passed for input:{input_data}")
        print("====================================")


if __name__ == "__main__":
    test_echo()
