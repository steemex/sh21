#include "list.h"

int		main(int argc, char **argv)
{
	t_list	*genesis_block;
	char	*first_str = "First string";

	printf("___Running___\n");
	if (argc > 1)
		printf("%s\n", argv[1]);

	genesis_block = create_list(first_str);	

	return (0);
}
