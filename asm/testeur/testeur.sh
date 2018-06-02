dir="champs_test"
for entry in "$dir"/*
do
  filename=$(basename -- "$entry")
  extension="${filename##*.}"
  filename="$dir/${filename%.*}"
  if [ $extension = "s" ]; then
    echo "asm compiling $entry"
    ./real_asm "$entry"
    if [ -e "$filename.cor" ]; then
      mv "$filename.cor" "$filename.sav"
    else
      echo "la compilation de real_asm a echoue"
    fi
    ../asm "$entry"
    if [ -e "$filename.cor" ]; then
      if [ -e "$filename.sav" ]; then
        echo "***DIFF***\033[1;31m"
        diff "$filename.cor" "$filename.sav"
        echo "\033[0m**ENDIFF**" 
      fi
    else
      echo "la compilation de l' asm a echoue"
    fi
    if [ ! -e "$filename.cor" -o ! -e "$filename.sav" ]; then
      if [ -e "$filename.cor" -o -e "$filename.sav" ]; then
      echo "\033[1;35m**REAL XOU ASM PAS COMPILE**\033[0m"
      else
      echo "\033[1;33m**REAL ET ASM NON COMPILES**\033[0m" 
      fi
    fi
    echo "\n----------\n" 
  fi
done
rm $dir/*.sav
