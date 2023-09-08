# inc

CLI utility to increment/decrement number written in C.
Inspiration is to simplify incrementing/decrementing numbers/simple date values in Acme editor.

## Synopsis

```sh
inc (amount)
```

`inc` takes input from stdin or socket.
If no value is piped in, `1*amount` is returned, where `amount` is unsigned integer with `1` as the default value.
To increment, piped in value and `value` need to be positive.
To decrement, either the piped in value or `value` need to be negative.

## Getting started

```sh
cc -o inc inc.c
```

## Examples

Commands

```sh
echo "4" | ./inc # 5
echo "04" | ./inc # 05
echo "4" | ./inc 2 # 6
echo "4" | ./inc -2 # 2
echo "04" | ./inc 2 # 06
echo "04" | ./inc -2 # 02
#####
echo "-5" | ./inc # -4
echo "-05" | ./inc # -04
echo "-5" | ./inc 2 # -3
echo "-5" | ./inc -2 # -7
echo "-05" | ./inc 2 # -03
echo "-05" | ./inc -2 # -07
#####
echo "09" | ./inc # 10
echo "-09" | ./inc -1 # -10
echo "9" | ./inc # 10
echo "-9" | ./inc -1 # -10
#####
echo "01" | ./inc # 02
echo "-01" | ./inc -1 # -02
echo "1" | ./inc # 2
echo "-1" | ./inc -1 # -2
#####
echo "0" | ./inc # 1
```

## Author

Meelis Utt
