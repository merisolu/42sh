from robot.api.logger import info, debug, trace, console
from subprocess import run, PIPE, Popen

# timeout in seconds for tests
TIMEOUT = 5

def run_command(arg_string: str, shell_path: str) -> dict:
    """
        Runs the given "arg_string" in the shell identified by "shell_path"
        run function: https://docs.python.org/3/library/subprocess.html#subprocess.run
        The command-line ran simply echoes the arg_string onto a pipe, which is then
        read from and executed by the shell binary.
        Run returns a class instance from which we can access the necessary outputs and
        return values for the purposes of testing.
    """
    ps = Popen(('echo', f'{arg_string}'), stdout=PIPE)
    result = run(
        f'{shell_path}',
        shell=True,
        capture_output=True,
        stdin=ps.stdout,
        text=True,
        timeout=TIMEOUT,
        executable="/bin/bash"
        )
    console(f'\ncase: {arg_string} | shell = {shell_path}')
    console(f"return = {result.returncode}")
    console(f"output = {result.stdout}")
    console(f"error = {result.stderr}")
    return dict(
        output=result.stdout,
        err_output=result.stderr,
        return_value=result.returncode
        )
