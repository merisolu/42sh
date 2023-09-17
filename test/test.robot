*** Settings ***
Documentation   A unix shell test suite
Library         ShellLibrary.py

*** Variables ***
${shell}        ".././42sh"
${bash}         "bash"
${shell_output} Catenate    SEPARATOR=_     ${shell}    "ouput"
${bash_output}  Catenate    SEPARATOR=_     ${bash}     "ouput"
${test_string}  "This is a test!"
${return_OK}    ${0}

*** Test Cases ***
Test echo
    ${ret_val_sh}=      Echo    ${test_string}   ${shell}
    ${ret_val_bash}=    Echo    ${test_string}   ${bash}


*** Keywords ***
Echo
    [Arguments]     ${string}   ${target_shell}
    ${value}=    run echo    ${string}   ${target_shell}
    RETURN      ${value}