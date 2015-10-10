# wordfreak
prints JSON formatted word frequency data from the command line

Compile with GCC
```shell
gcc wordfreak.c -o wordfreak
```
Alias the binary in .profile
```shell
alias wordfreak="path/to/wordfreak/./wordfreak"
```

Run it on the test file included in this repo
```shell
wordfreak test.txt
```
you should see this output:
```javascript
{ "Hello,": 1, "this": 1, "is": 1, "a": 2, "test": 1, "text": 1, "It": 1, "has": 1, "few": 1, "lines": 1, "so": 1, "that": 1, "the": 1, "program": 1, "can": 1, "read": 1, "each": 1, "line": 1, "and": 1, "produce": 1, "output": 1}
```
