from robot.api.logger import info, debug, trace, console
from os import system

def run_command(arg_string: str, shell_path: str, output_file: str, return_file: str):
    """
        Runs the given "arg_string" in the shell identified by "shell_path"
        Output is sent to the "output_file", silencing error messages
        Return value is sent to "return_file"
    """
    console(f"\nRunning test case: '{arg_string}' in '{shell_path}'")
    system(f"echo {arg_string} | {shell_path} > {output_file} 2>&- ; \
           echo \"echo $?\" | {shell_path} > {return_file}")

def diff(shell_output: str, bash_output: str):
    """
        Takes the paths to the output of the tested shell and the refernce shell,
        diffs them, returning the value.
    """
    console(f"Comparing files: {shell_output} and {bash_output}")
    return system(f"diff {shell_output} {bash_output}")
