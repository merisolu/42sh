*** Settings ***
Documentation    A Unix Shell test suite
Library          ShellLibrary.py

*** Variables ***
# for some reason the Catenate builtin is not working, using hard-coded values for now
${shell_name}        42sh
${shell}             .././42sh
${bash}              bash
${shell_output}      42sh_output
${shell_return}      42sh_return
${bash_output}       bash_output
${bash_return}       bash_return
${diff_OK}           ${0}

@{ECHO}    echo "hello world"    echo owowow    echo    echo h"el'lo' "world

*** Test Cases ***
Test Builtin Echo
    [Documentation]    Testing for the builtin function 'echo'
    # TODO add a bit of visual pizazz to this, the console logs are a bit stale and hard to read
    FOR    ${case}    IN    @{ECHO}
        Simple Command    ${case}
    END

# TODO errors will need to be handled differently due to differences in text of err message
# maybe create a different function to handle cases where errors are expected
*** Keywords ***
Simple command
    [Documentation]    Sends a command to the test shell and compares its output and return
    ...                values with the reference shell
    [Arguments]        ${test_case}
    Create simple test files
    Command            ${test_case}       ${shell}           ${shell_output}    ${shell_return}
    Command            ${test_case}       ${bash}            ${bash_output}     ${bash_return}
    ${diff_output}=    Check diff         ${shell_output}    ${bash_output}
    ${diff_return}=    Check diff         ${shell_return}    ${bash_return}
    Should be equal    ${diff_output}     ${diff_OK}
    Should be equal    ${diff_return}     ${diff_OK}
    Delete simple test files

Command
    [Documentation]    Takes a command line string and runs it in the specified shell
    ...                Output from the command is sent to 'output' file
    ...                Return value of command is sent, as text, to 'return' file
    [Arguments]        ${arg_string}      ${target_shell}    ${output}    ${return}
    run command        ${arg_string}      ${target_shell}    ${output}    ${return}

Check diff
    [Documentation]    Diffs the two files pased as arguments and returns the value
    [Arguments]        ${file_1}    ${file_2}
    ${value}=          diff    ${file1}    ${file_2}
    RETURN             ${value}

Create simple test files
    [Documentation]    Test set-up, creates files for sending test case outputs and returns
    create file        ${shell_output}
    create file        ${bash_output}
    create file        ${shell_return}
    create file        ${bash_return}

Delete simple test files
    [Documentation]    The delete file function just passes test file paths to 'rm' cmd line
    ...                program and thus should be used with extreme caution.
    ...                Used in tear-down of simple command test
    delete file        ${shell_output}
    delete file        ${bash_output}
    delete file        ${shell_return}
    delete file        ${bash_return}
