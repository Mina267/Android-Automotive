# *Personal Lecture Notes*
# Run Bash file
```bash
./file_name.sh 
```
Create child process and the enviroment variables craete with this process will delete when process end

--- 

# Condition in bash

## Types of condition

### Integer condition
```
-eq: equal
-ne: not equal
-gt: greatr than
-lt: less than
-ge: greater or equal
-le: less or equal
```

### Strings condition
```
=
!=
-z: Zero characters
-n: Non-Zero characters
```

### File condition
```
-f: file exist
-d: directory
-x: File executable or not
```

### Syntax of test
```
test <Space> V1 <Space> -eq <Space> V2 <Space>
test [ <Space> V1 <Space> -eq <Space> V2 <Space> ]

```

`$?` store the return status of the last command.

---
### Logical operator
`(&&)` or `-a`

`(||)` or `-o`

### Syntax
```
[ condition ] Logical operator && or || [ condition ]

[[ condition Logical operator && or ||  condition ]]

[ condition Logical operator -a or -o  condition ]
```

## IF
### Syntax
```bash
if [Condition]

then

fi
```
``` bash
if [Condition];then

elif

else

fi
```

## For Loop
### Syntax
```bash
for var in list do

done
```

## While
### Syntax
```bash
while[[  ]] do

done
```

```bash
(( C-style code ))
```

## Until


# Array
## Index array
### Implicit declartion
By default index array
```bash
Fruits("Apple" "Banana" "Cherry")

echo ${Fruits[0]}

Fruits[10] = "melon"
```
You can add data in any index not mandatory to be contigous

### Print array elements
will not print the empty elements
```bash
echo ${Fruits[@]}     -> Apple Banana Cherry
echo "${Fruits[@]}"   -> "Apple" "Banana" "Cherry"
echo ${Fruits[*]}     -> Apple Banana Cherry
echo "${Fruits[*]}"   -> "Apple Banana Cherry"

```
### Print array elements numbers
```bash
echo ${#Fruits[@]}

```

### Array slicing
```bash
echo ${Fruits[@]:1:2}
```

### Print index not data
```bash
for index in &{!Fruits[@]}; do
echo $index
done
```

## Assotiative array
### Explicit declaretion
Explicity the type of data created.
```bash
declare -A Array = ([key]="value")
```
#### Example
```bash
declare -A Fruits = ([Apple]="red" [Banan]="yellow")
Fruits[cherry]="blue"
echo ${fruits[apple]}  Output: red
echo ${fruits[@]}  Output: red yellow blue

for key in ${[!fruits[@]]}
do
echo "key in $key, value is ${fruits[$key]}"
done
```



