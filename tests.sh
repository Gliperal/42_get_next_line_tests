make -C ../libft/ fclean && make -C ../libft/
gcc -Wall -Wextra -Werror -I ../libft/ -I ../ -L ../libft/ -lft test.c ../get_next_line.c -o test
read -p "Press enter..."
echo "\n\n"
./test test1.txt
read -p "Press enter..."
echo "\n\n"
./test -f
read -p "Press enter..."
echo "\n\n"
./test test1.txt test1.txt
read -p "Press enter..."
echo "\n\n"
./test -m test3a.txt test3b.txt test3c.txt
read -p "Press enter..."
echo "\n\n"
./test test4.txt
read -p "Press enter..."
echo "\n\n"
./test test5.txt | tail -c 100
read -p "Press enter..."
echo "\n\n"
#./test test6.txt
#./test -b
