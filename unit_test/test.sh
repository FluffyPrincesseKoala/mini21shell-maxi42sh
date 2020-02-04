#!/bin/bash

for entry in `ls ./unit_test/`; do
    echo $entry
    exec ./minishell < ./unit_test/$entry
done