#!/bin/sh

#DELETE EXISTING .COR FILES
rm *.cor;
rm ./champions/*.cor;

for FILE in champions/*.s ; do
    echo "Processing ${FILE} file..."
    ./asm ${FILE}
    ./assembler ${FILE}
    echo "\n"
done;

for FILE in *.cor ; do
    echo "Checking diff for ${FILE} file..."
    diff ${FILE} champions/${FILE}
done