echo "make -C ../libft/ fclean && make -C ../libft/"
make -C ../libft/ fclean && make -C ../libft/
echo "clang -Wall -Wextra -Werror -I ../ -I ../libft/includes -o ../get_next_line.o -c ../get_next_line.c"
clang -Wall -Wextra -Werror -I ../ -I ../libft/includes -o ../get_next_line.o -c ../get_next_line.c
echo "clang -Wall -Wextra -Werror -I ../ -I ../libft/includes -o test.o -c test.c"
clang -Wall -Wextra -Werror -I ../ -I ../libft/includes -o test.o -c test.c
echo "clang -o test test.o ../get_next_line.o -I ../libft/includes -L ../libft/ -lft"
clang -o test test.o ../get_next_line.o -I ../libft/includes -L ../libft/ -lft
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
