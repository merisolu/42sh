*** Settings ***
Documentation    A Unix Shell test suite
...              The idea here is to create the most flexible, versatile and
...              comprehensive 42 school shell project testing suite imaginable.
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
${return_OK}         ${0}

@{ECHO}    echo "hello world"    echo owowow    echo    echo h"el'lo' "world

*** Test Cases ***
Test Echo Loop
    FOR    ${case}    IN    @{ECHO}
        Simple Command    ${case}
    END

*** Keywords ***
Simple command
    [Documentation]    Sends a command to the test shell and compares its output and return
    ...                values with the reference shell
    [Arguments]        ${test_case}
    Create test files
    Command            ${test_case}       ${shell}        ${shell_output}    ${shell_return}
    Command            ${test_case}       ${bash}         ${bash_output}     ${bash_return}
    ${diff_output}=    Check diff         ${shell_output}    ${bash_output}
    ${diff_return}=    Check diff         ${shell_return}    ${bash_return}
    Should be equal    ${diff_output}     ${return_OK}
    Should be equal    ${diff_return}     ${return_OK}
    Delete test files

Command
    [Arguments]     ${arg_string}      ${target_shell}    ${output}    ${return}
    ${value}=       run command        ${arg_string}      ${target_shell}    ${output}    ${return}
    RETURN          ${value}

Check diff
    [Documentation]    Diffs the two files pased as arguments and returns the value
    [Arguments]    ${file_1}    ${file_2}
    ${value}=      diff    ${file1}    ${file_2}
    RETURN         ${value}

Create test files
    create file    ${shell_output}
    create file    ${bash_output}
    create file    ${shell_return}
    create file    ${bash_return}

Delete test files
    [Documentation]    The delete file function just passes test file paths to 'rm' cmd line
    ...                program and thus should be used with extreme caution
    delete file        ${shell_output}
    delete file        ${bash_output}
    delete file        ${shell_return}
    delete file        ${bash_return}
