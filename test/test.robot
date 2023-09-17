*** Settings ***
Documentation    A unix shell test suite
...              The idea here is to create the most flexible, versatile and
...              comprehensive 42 school shell project testing suite imaginable.
Library          ShellLibrary.py

*** Variables ***
# for some reason the Catenate builtin is not working, using hard-coded values for now
${shell_name}        42sh
${shell}             .././42sh
${bash}              bash
${shell_output}      42sh_output
${bash_output}       bash_output
${test_string}       ls
#echo This is a test!
${return_OK}         ${0}

*** Test Cases ***
Test Echo
    Create test files
    ${ret_val_sh}=          Command            ${test_string}     ${shell}        ${shell_output}
    ${ret_val_bash}=        Command            ${test_string}     ${bash}         ${bash_output}
    ${diff}=                Check Diff         ${shell_output}    ${bash_output}
    Should be equal         ${diff}            ${return_OK}
    Delete output files     ${shell_output}    ${bash_output}
    Should be equal         ${ret_val_sh}      ${ret_val_bash}

*** Keywords ***
Command
    [Arguments]     ${arg_string}      ${target_shell}    ${output}
    ${value}=       run command        ${arg_string}      ${target_shell}    ${output}
    RETURN          ${value}

Check Diff
    [Arguments]    ${shell_output}    ${bash_output}
    ${value}=      diff               ${shell_output}    ${bash_output}
    RETURN         ${value}

Create test files
    create file    ${shell_output}
    create file    ${bash_output}

Delete output files
    [Documentation]    The delete file function just passes args to 'rm' cmd line
    ...                program and thus should be used with extreme caution
    [Arguments]        ${shell_output}    ${bash_output}
    delete file        ${shell_output}
    delete file        ${bash_output}