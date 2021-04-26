#include "libft.h"
#include <stdio.h>
#include <memory.h>

//int 	main()
//{
//	printf("length is: %d\n", ft_strlen(""));
//	return (0);
//}

//int main()
//{
//	char resource[] = "Howdy Neighbour *_*/";
//	char destination[100];
//	ft_memcpy(destination, resource, ft_strlen(resource)+1);
//	printf("Copied string is %s", destination);
//
//	int newResource[] = {11, 22, 33, 45, 55};
//	int n = sizeof(newResource)/sizeof(newResource[0]);
//	int newDestination[n], i;
//	ft_memcpy(newDestination, newResource,  sizeof(newResource));
//	printf("\nCopied array is ");
//	for (i=0; i<n; i++)
//		printf("\n%d\n", newDestination[i]);
//	return 0;
//}

//
//int main (int argc, char **argv) {
//
//	size_t n = 10;   /* length variaale */
//	char *s1 = argc > 1 ? argv[1] : "hello",    /* string 1 */
//	*s2 = argc > 2 ? argv[2] : "world",    /* string 2 */
//	str[30] = "hello2'\0'";   /* string to hold concatenated result */
//
//
//	ft_strlcat(str, s1, n); /* concatenate s1 -> str */
//	ft_strlcat(str, s2, n); /* concatenate s2 -> str */
//
//	printf ("src: %s\ndst: %s\nstr: %s\n", s1, s2, str);
//	printf ("len: %zu chars.\n", n);
//
//	free (str); /* don't forget to free allocated memory */
//
//	return 0;
//}

//int main()
//{
//	char a[] = "abcdefg";
//	char *s;
//	s = ft_substr(a, 10, 2);
//	printf("%s", s );
//	return (0);
//}

int main()
{
	char *str = "olol			";
	char **array = ft_split(str, ' ');
	while (*array != 0)
	{
		printf("%s\n", *array);
		array++;
	}
	return (0);
}
