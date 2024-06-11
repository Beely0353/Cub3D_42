#include "cub3d.h"

size_t	ft_strlcpy(char *dest, char const *src, size_t n)
{
	size_t	i;

	i = 0;
	if ((!dest || !src) && !n)
		return (i);
	if (!n)
		return (ft_strlen(src));
	while (i < (n - 1) && src[i])
	{
		dest[i] = src[i];
		i ++;
	}
	dest[i] = '\0';
	return (ft_strlen(src));
}

size_t	ft_strlcat(char *dest, char const *src, size_t n)
{
	size_t	i;
	size_t	dest_len;

	if ((!dest || !src) && !n)
		return (n);
	if (ft_strlen(dest) >= n)
		return (ft_strlen(src) + n);
	dest_len = ft_strlen(dest);
	i = dest_len - 1;
	while (++i < (n - 1) && src[i - dest_len])
		dest[i] = src[i - dest_len];
	dest[i] = '\0';
	if (n > dest_len)
		return (ft_strlen(src) + dest_len);
	else
		return (ft_strlen(src) + n);
}

char	*ft_strjoin(char const *str, char const *s)
{
	char	*comp_str;

	if (!str || !s)
		return (NULL);
	comp_str = malloc(sizeof(char) * (ft_strlen(str) + ft_strlen(s) + 1));
	if (!comp_str)
		return (NULL);
	ft_strlcpy(comp_str, str, ft_strlen(str) + 1);
	ft_strlcat(comp_str, s, ft_strlen(s) + ft_strlen(str) + 1);
	return (comp_str);
}

int	ft_strncmp(char const *s1, char const *s2, size_t n)
{
	size_t	i;

	i = 0;
	while ((s1[i] || s2[i]) && i < (n - 1) && s1[i] == s2[i])
		i++;
	if (!n)
		return (0);
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

size_t	ft_strlen(char const *str)
{
	int	compt;

	compt = 0;
	while (str[compt] != '\0')
		compt ++;
	return (compt);
}

char	*ft_strdup(char *src)
{
	size_t	i;
	char	*ptr;

	i = 0;
	while (src[i])
		i++;
	ptr = malloc(sizeof(char) * (i + 1));
	if (!ptr)
		return (NULL);
	i = 0;
	while (src[i])
	{
		ptr[i] = src[i];
		i ++;
	}
	ptr[i] = '\0';
	return (ptr);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	i;

	if (!s)
		return (NULL);
	i = 0;
	if (start >= ft_strlen(s))
	{
		str = malloc(sizeof(char));
		if (!str)
			return (NULL);
		str[i] = '\0';
		return (str);
	}
	if (len < ft_strlen(s))
		str = malloc(sizeof(char) * (len + 1));
	else
		str = malloc (sizeof(char) * (ft_strlen(s) - start + 1));
	if (!str)
		return (NULL);
	start --;
	while (s[++start] && i < len)
		str[i++] = s[start];
	str[i] = '\0';
	return (str);
}
