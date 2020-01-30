#!/bin/sh

echo build program srcs
for entry in `ls $PWD`; do
    if $entry == "minishell"
    then
        for tests in `ls ./unit_test/`; do
            exec ./minishell < tests
        done
    fi
done