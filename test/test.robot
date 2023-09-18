*** Settings ***
Documentation    A Unix Shell test suite
Library          ShellLibrary.py
Library          OperatingSystem
Library          String

*** Variables ***
# shell_name should be the name of the binary being tested.
# shell should be the relative path to that binary
# bash can be changed to the name of another reference shell
${shell_name}        42sh
${shell}             .././${shell_name}
${bash}              bash
${shell_output}      temp/${shell_name}_output
${shell_return}      temp/${shell_name}_return
${bash_output}       temp/bash_output
${bash_return}       temp/bash_return
${diff_OK}           ${0}

${TEMP_DIR}          temp
${echo_file_path}    test_cases/echo_test_cases.txt

*** Test Cases ***
Test Builtin Echo
    [Documentation]    Testing for the builtin function 'echo'
    # TODO add a bit of visual pizazz to this, the console logs are a bit stale and hard to read
    @{ECHO}=           Get test cases    ${echo_file_path}
    Simple command test loop             @{ECHO}

# TODO errors will need to be handled differently due to differences in text of err message
# maybe create a different function to handle cases where errors are expected
*** Keywords ***
Simple command test loop
    [Documentation]    Takes a list of test cases and runs them using Simple Command
    [Arguments]        @{CASES}

    # just for debugging readability
    log                \n    console=yes

    FOR    ${case}    IN    @{CASES}
        Simple Command    ${case}
    END

Get test cases
    [Documentation]    Reads test case file given as argument and returns them
    ...                in list format
    [Arguments]        ${path}
    ${cases}=          Get file          ${path}
    @{case_list}=      Split to lines    ${cases}
    RETURN             @{case_list}

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
    ${value}=          diff         ${file_1}    ${file_2}
    RETURN             ${value}

Create simple test files
    [Documentation]    Test set-up, creates files for sending test case outputs and returns
    ...                The Create File function comes from OperatingSystem lib
    Create File        ${shell_output}
    Create File        ${bash_output}
    Create File        ${shell_return}
    Create File        ${bash_return}

Delete simple test files
    [Documentation]     Removes all the files created for comparing test outputs
    ...                 The Remove Directory function comes from OperatingSystem lib
    Remove Directory    ${TEMP_DIR}    recursive=True
