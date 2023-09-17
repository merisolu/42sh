from robot.api.logger import info, debug, trace, console
from os import system

def run_command(arg_string: str, shell_path: str, output_file: str):
    """
        Runs the given "arg string" in the shell identified by "shell path"
        Output is sent to the "output file"
    """
    console(f"\nRunning test case: '{arg_string}' in '{shell_path}'")
    return system(f"echo {arg_string} | {shell_path} > {output_file}")

def diff(shell_output: str, bash_output: str):
    """
        Takes the paths to the output of the tested shell and the refernce shell,
        diffs them, returning the value.
    """
    console(f"\nComparing files: {shell_output} and {bash_output}")
    return system(f"diff {shell_output} {bash_output}")

def delete_file(file_path: str):
    """
        Takes a path to a file and deletes it
        NB. THIS FUNCTION IS DANGEROUS, at the moment it is just being used to delete output files.
        TODO add a check to make sure it is only deleting files created by this test suite
    """
    system(f"rm {file_path}")