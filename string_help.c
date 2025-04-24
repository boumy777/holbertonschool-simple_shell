#include "shell.h"

/**
 * _strlen - returns the length of a string
 * @s: string to measure
 *
 * Return: length of string
 */
int _strlen(char *s)
{
	int i = 0;

	if (!s)
		return (0);

	while (s[i])
		i++;

	return (i);
}

/**
 * _strcmp - compares two strings
 * @s1: first string
 * @s2: second string
 *
 * Return: 0 if strings are equal, positive or negative value otherwise
 */
int _strcmp(char *s1, char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}

/**
 * _strdup - duplicates a string
 * @str: string to duplicate
 *
 * Return: pointer to the duplicated string
 */
char *_strdup(const char *str)
{
	int length = 0;
	char *ret;

	if (str == NULL)
		return (NULL);

	while (str[length])
		length++;

	ret = malloc(sizeof(char) * (length + 1));
	if (!ret)
		return (NULL);

	for (length = 0; str[length]; length++)
		ret[length] = str[length];

	ret[length] = '\0';
	return (ret);
}

/**
 * _strcpy - copies a string
 * @dest: destination string
 * @src: source string
 *
 * Return: pointer to destination
 */
char *_strcpy(char *dest, char *src)
{
	int i = 0;

	if (dest == src || src == NULL)
		return (dest);

	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

/**
 * _strcat - concatenates two strings
 * @dest: destination string
 * @src: source string
 *
 * Return: pointer to destination
 */
char *_strcat(char *dest, char *src)
{
	char *ret = dest;

	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = '\0';
	return (ret);
}
