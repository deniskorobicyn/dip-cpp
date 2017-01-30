@echo off

call ./bin/ssh.bat up -d agent

call ./bin/ssh.bat run --rm key
